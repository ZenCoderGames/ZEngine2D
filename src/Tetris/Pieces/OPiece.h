//
// Created by srinavinnair on 1/29/20.
//

#ifndef ZCOREENGINE_OPIECE_H
#define ZCOREENGINE_OPIECE_H

#include "./Piece.h"

class OPiece:public Piece {
    void RotateForOrientation() override {
        m_cells[0]->Set(0, 0);
        m_cells[1]->Set(0, 1);
        m_cells[2]->Set(1, 0);
        m_cells[3]->Set(1, 1);
    }
public:
    OPiece(Board* board, int row, int col):Piece(board, "yellowBlock", row, col) {
    }
};

#endif //ZCOREENGINE_OPIECE_H
