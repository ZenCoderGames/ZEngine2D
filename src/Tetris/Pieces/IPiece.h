//
// Created by srinavinnair on 1/29/20.
//

#ifndef ZCOREENGINE_IPIECE_H
#define ZCOREENGINE_IPIECE_H

#include "./Piece.h"

class IPiece:public Piece {
protected:
    void RotateForOrientation() override {
        if(m_currentRotation==0) {
            m_cells[0]->Set(0, -1);
            m_cells[1]->Set(0, 0);
            m_cells[2]->Set(0, 1);
            m_cells[3]->Set(0, 2);
        }
        else if(m_currentRotation==1) {
            m_cells[0]->Set(-1, 1);
            m_cells[1]->Set(0, 1);
            m_cells[2]->Set(1, 1);
            m_cells[3]->Set(2, 1);
        }
        else if(m_currentRotation==2) {
            m_cells[0]->Set(1, -1);
            m_cells[1]->Set(1, 0);
            m_cells[2]->Set(1, 1);
            m_cells[3]->Set(1, 2);
        }
        else if(m_currentRotation==3) {
            m_cells[0]->Set(-1, 0);
            m_cells[1]->Set(0, 0);
            m_cells[2]->Set(1, 0);
            m_cells[3]->Set(2, 0);
        }
    }
public:
    IPiece(Board* board, int row, int col):Piece(board, "blueBlock", row, col) {

    }
};

#endif //ZCOREENGINE_IPIECE_H
