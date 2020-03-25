//
// Created by srinavinnair on 1/29/20.
//

#ifndef ZCOREENGINE_JPIECE_H
#define ZCOREENGINE_JPIECE_H

#include "./Piece.h"

class JPiece:public Piece {
    void RotateForOrientation() override {
        if(m_currentRotation==0) {
            m_cells[0]->Set(0, 0);
            m_cells[1]->Set(0, 1);
            m_cells[2]->Set(0, -1);
            m_cells[3]->Set(-1, 1);
        }
        else if(m_currentRotation==1) {
            m_cells[0]->Set(0, 0);
            m_cells[1]->Set(-1, 0);
            m_cells[2]->Set(1, 0);
            m_cells[3]->Set(1, 1);
        }
        else if(m_currentRotation==2) {
            m_cells[0]->Set(0, 0);
            m_cells[1]->Set(0, -1);
            m_cells[2]->Set(0, 1);
            m_cells[3]->Set(1, -1);
        }
        else if(m_currentRotation==3) {
            m_cells[0]->Set(0, 0);
            m_cells[1]->Set(-1, 0);
            m_cells[2]->Set(1, 0);
            m_cells[3]->Set(-1, -1);
        }
    }
public:
    JPiece(Board* board, int row, int col):Piece(board, "greenBlock", row, col) {
    }
};

#endif //ZCOREENGINE_JPIECE_H
