//
// Created by srinavinnair on 1/13/20.
//

#include "Tetris.h"
#include <cstdlib>
#include <ctime>

#include <functional>

void Tetris::Initialize() {
    Game::Initialize();

    LoadLua("../../assets/scripts/Tetris.lua", "Tetris");

    DrawWall("left", 448, 32, ROWS, false);
    DrawWall("bot", 448, 672, COLS+2, true);
    DrawWall("right", 800, 32, ROWS, false);

    m_board = new Board();
    m_board->DrawGrid();

    srand(time(NULL));
    m_score = 0;
    m_isGameOver = false;
    m_isPaused = false;

    CreateNewPiece();
    if(!m_isGameOver && m_currentPiece != nullptr) {
        m_currentPiece->MoveDown();
    }

    m_gravityTimer = 0;
    m_textCounter = Engine::entityManager->AddEntity("scoreCounter", LAYER_UI, true);
    m_textCounterComponent = new TextComponent("charriot-font", "Score: 0", 100, 100, {255, 255, 255}, 300);
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
    // Don't update if game is over
    if(m_isGameOver) {
        m_board->Draw();
        return;
    }

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
                // Place the piece on the board
                bool hasBlocksAboveGrid = m_board->Set(m_currentPiece->GetRow(), m_currentPiece->GetCol(), m_currentPiece->GetCells());

                delete m_currentPiece;
                m_currentPiece = nullptr;

                // Check if placed blocks crossed the top - game over
                if(hasBlocksAboveGrid) {
                    m_isGameOver = true;
                    if(m_textCounterComponent != nullptr) {
                        m_textCounterComponent->ModifyText("End Game - Score: " + std::to_string(m_score) + "\n\nPress 'R' to Restart.");
                    }
                } else {
                    CreateNewPiece();
                }
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

    switch (event.type) {
        case SDL_KEYDOWN: {
            // Handle restart when game is over
            if (m_isGameOver && event.key.keysym.sym == SDLK_r) {
                RestartGame();
                return;
            }

            // Normal game controls
            if(m_currentPiece!= nullptr) {
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
            }
            break;
        }
        default: {
            break;
        }
    }
}

void Tetris::RestartGame() {
    // Clear the board
    m_board->ClearBoard();

    // Reset game state
    m_score = 0;
    m_isGameOver = false;
    m_isPaused = false;
    m_gravityTimer = 0;

    // Delete current piece if it exists
    if(m_currentPiece != nullptr) {
        delete m_currentPiece;
        m_currentPiece = nullptr;
    }

    // Create new piece and start game
    CreateNewPiece();
    if(m_currentPiece != nullptr) {
        m_currentPiece->MoveDown();
    }

    // Update score text
    m_textCounterComponent->ModifyText("Score: 0 \n\nControls: Arrow Keys or Spacebar.");
}

Tetris::~Tetris() {
}
