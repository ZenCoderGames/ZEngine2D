//
// Created by srinavinnair on 1/29/20.
//

#ifndef ZCOREENGINE_LPIECE_H
#define ZCOREENGINE_LPIECE_H

#include "./Piece.h"

class LPiece:public Piece {
protected:
    void RotateForOrientation() override {
        if(m_currentRotation==0) {
            m_cells[0]->Set(0, 0);
            m_cells[1]->Set(0, -1);
            m_cells[2]->Set(0, 1);
            m_cells[3]->Set(-1, -1);
        }
        else if(m_currentRotation==1) {
            m_cells[0]->Set(0, 0);
            m_cells[1]->Set(-1, 0);
            m_cells[2]->Set(1, 0);
            m_cells[3]->Set(-1, 1);
        }
        else if(m_currentRotation==2) {
            m_cells[0]->Set(0, 0);
            m_cells[1]->Set(0, 1);
            m_cells[2]->Set(0, -1);
            m_cells[3]->Set(1, 1);
        }
        else if(m_currentRotation==3) {
            m_cells[0]->Set(0, 0);
            m_cells[1]->Set(1, 0);
            m_cells[2]->Set(-1, 0);
            m_cells[3]->Set(1, -1);
        }
    }
public:
    LPiece(Board* board, int row, int col):Piece(board, "redBlock", row, col) {
    }
};

#endif //ZCOREENGINE_LPIECE_H
