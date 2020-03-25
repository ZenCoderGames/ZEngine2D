//
// Created by srinavinnair on 1/13/20.
//

#include "Tetris.h"
#include <cstdlib>
#include <ctime>

#include <functional>

void Tetris::Initialize() {
    Game::Initialize();

    LoadLua("../assets/scripts/Tetris.lua", "Tetris");

    DrawWall("left", 448, 32, ROWS, false);
    DrawWall("bot", 448, 672, COLS+2, true);
    DrawWall("right", 800, 32, ROWS, false);

    m_board = new Board();
    m_board->DrawGrid();

    srand(time(NULL));
    CreateNewPiece();
    m_currentPiece->MoveDown();

    m_gravityTimer = 0;
    m_textCounter = Engine::entityManager->AddEntity("scoreCounter", LAYER_UI, true);
    m_textCounterComponent = new TextComponent("charriot-font", "Score: 0", 100, 100, {255, 255, 255});
    m_textCounter->AddComponent(m_textCounterComponent);
}

void Tetris::CreateNewPiece() {
    m_currentPiece = nullptr;

    int randomVal = rand() % 7;
    auto randomPieceType = static_cast<PIECE_TYPE >(randomVal);
    m_currentPiece = CreatePiece(randomPieceType, START_ROW, START_COL);
}

void Tetris::DrawWall(std::string name, int x, int y, int count, bool isHorizontal) {
    for(int i=0; i<count; ++i) {
        std::string entityName = name + std::string("_Wall_") + std::to_string(i);
        Entity* newBlock = Engine::entityManager->DuplicateEntity("wallPiece", entityName.c_str(), true);
        TransformComponent* transformComponent = newBlock->GetComponent<TransformComponent>();
        if(isHorizontal) {
            transformComponent->position.x = x + 32 * i;
            transformComponent->position.y = y;
        }
        else {
            transformComponent->position.x = x;
            transformComponent->position.y = y + 32 * i;
        }
    }
}

void Tetris::Update(float deltaTime) {
    if(m_isPaused) {
        m_gravityTimer = 0;
    }
    else {
        if (m_currentPiece != nullptr) {
            m_gravityTimer += deltaTime;

            if (m_gravityTimer > GRAVITY_TIME) {
                m_currentPiece->MoveDown();
                m_gravityTimer = 0;
            }

            m_currentPiece->Update();

            if (m_currentPiece->HasBeenPlaced()) {
                m_board->Set(m_currentPiece->GetRow(), m_currentPiece->GetCol(), m_currentPiece->GetCells());
                delete m_currentPiece;
                m_currentPiece = nullptr;
                CreateNewPiece();
            }

            int numLinesToClear = m_board->GetTotalLinesToClear();
            if (numLinesToClear > 0) {
                m_isPaused = true;

                Sequence* sequence = Engine::sequenceManager->CreateSequence(std::bind(&Tetris::ClearLineSequenceCompleted, this), 0.5f + (numLinesToClear-1) * 0.25f);
                for(int i=0; i<numLinesToClear; ++i)
                    sequence->AddSequenceItem(std::bind(&Tetris::ClearLines, this), i * 0.25f);
                sequence->Start();
            }
        }
    }

    m_board->Draw();
}

void Tetris::ClearLines() {
    m_board->ClearLines();
    AddToScore(1);
}

void Tetris::ClearLineSequenceCompleted() {
    m_board->RecursiveMoveDown();
    m_isPaused = false;
}

void Tetris::ProcessInput(SDL_Event event) {
    Game::ProcessInput(event);

    if(m_currentPiece!= nullptr) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                if (event.key.keysym.sym == SDLK_LEFT) {
                    m_currentPiece->MoveLeft();
                }
                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    m_currentPiece->MoveRight();
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    m_currentPiece->RotateCCW();
                }
                else if (event.key.keysym.sym == SDLK_DOWN) {
                    m_currentPiece->RotateCW();
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    m_currentPiece->Drop();
                }
                if (event.key.keysym.sym == SDLK_p) {
                    m_isPaused = !m_isPaused;
                }
                break;
            }
            default: {
                break;
            }
        }
    }
}

Tetris::~Tetris() {
}
