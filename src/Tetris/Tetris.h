#ifndef TETRIS_H
#define TETRIS_H

#include "../Engine/Core/Game.h"

#include "./Pieces/IPiece.h"
#include "./Pieces/OPiece.h"
#include "./Pieces/LPiece.h"
#include "./Pieces/TPiece.h"
#include "./Pieces/ZPiece.h"
#include "./Pieces/JPiece.h"
#include "./Pieces/SPiece.h"

#include "./Board.h"
#include "../Engine/Components/TextComponent.h"

class Tetris: public Game {
    private:
        Board* m_board;
        Piece* m_currentPiece;
        float m_gravityTimer;
        bool m_isPaused;
        Entity* m_textCounter;
        TextComponent* m_textCounterComponent;
        int m_score;

        void ClearLines();
        void ClearLineSequenceCompleted();
    protected:
        void Initialize() override;
    public:
        ~Tetris();

        void ProcessInput(SDL_Event event) override;
        void Update(float deltaTime) override;

        void DrawWall(std::string name, int x, int y, int count, bool isHorizontal);

        enum PIECE_TYPE {I, O, T, Z, L, S, J};
        Piece* CreatePiece(PIECE_TYPE pieceType, int r, int c) {
            Piece* newPiece = nullptr;

            switch (pieceType) {
                case I: newPiece = new IPiece(m_board, r, c); break;
                case O: newPiece = new OPiece(m_board, r, c); break;
                case L: newPiece = new LPiece(m_board, r, c); break;
                case T: newPiece = new TPiece(m_board, r, c); break;
                case Z: newPiece = new ZPiece(m_board, r, c); break;
                case S: newPiece = new SPiece(m_board, r, c); break;
                case J: newPiece = new JPiece(m_board, r, c); break;
            }

            newPiece->Initialize();

            return newPiece;
        }

        void CreateNewPiece();

        void AddToScore(int val) {
            m_score += val;
            m_textCounterComponent->ModifyText("Score: " + std::to_string(m_score));
        }
};

#endif //TETRIS_H
