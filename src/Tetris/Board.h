//
// Created by srinavinnair on 2/7/20.
//

#ifndef ZCOREENGINE_BOARD_H
#define ZCOREENGINE_BOARD_H

#include "./Cell.h"

class Board {
private:
    int m_rows;
    int m_cols;
    std::vector<std::vector<Cell*>> m_grid;

public:
    Board() {
        m_rows = ROWS;
        m_cols = COLS;

        m_grid.resize(m_rows, std::vector<Cell*>(m_cols));
        for(int r=0; r<m_rows; ++r) {
            for (int c = 0; c < m_cols; ++c) {
                m_grid[r][c] = new Cell(r, c);
            }
        }
    }

    void DrawGrid() {
        for(int r=0; r<m_rows; ++r) {
            for(int c=0; c<m_cols; ++c) {
                std::string entityName = std::string("Grid_") + std::to_string(r) + std::string("_") + std::to_string(c);
                Entity *newBlock = Engine::entityManager->DuplicateEntity("emptyBlock", entityName.c_str(), true);
                TransformComponent *transformComponent = newBlock->GetComponent<TransformComponent>();
                transformComponent->position.x = START_X + c * 32;
                transformComponent->position.y = START_Y + r * 32;
            }
        }
    }

    void Draw() {
        for(int r=0; r<m_rows; ++r) {
            for (int c = 0; c < m_cols; ++c) {
                m_grid[r][c]->Draw();
            }
        }
    }

    bool CheckOverflow(int startRow, int startCol, std::vector<Cell*> cells) {
        for(int i=0; i<cells.size(); ++i) {
            int row = startRow + cells[i]->r;
            int col = startCol + cells[i]->c;
            if(col<0 || col>=COLS)
                return true;
            if(row<0 || row>=ROWS)
                return true;
            if(!m_grid[row][col]->IsEmpty())
                return true;
        }

        return false;
    }

    bool Set(int startRow, int startCol, std::vector<Cell*> cells) {
        for(int i=0; i<cells.size(); ++i) {
            int row = startRow + cells[i]->r;
            int col = startCol + cells[i]->c;
            m_grid[row][col]->SetBlock(cells[i]->block);
        }
    }

    int GetTotalLinesToClear() {
        int numLinesToClear = 0;
        for(int r=ROWS-1; r>=0; --r) {
            if(IsRowFull(r)) {
                numLinesToClear++;
            }
        }

        return numLinesToClear;
    }

    bool IsRowFull(int r) {
        int blocksInRow = 0;
        for(int c=0; c<COLS; ++c) {
            if(!m_grid[r][c]->IsEmpty()) {
                blocksInRow++;
            }
        }

        return blocksInRow==COLS;
    }

    bool IsRowEmpty(int r) {
        for(int c=0; c<COLS; ++c) {
            if(!m_grid[r][c]->IsEmpty()) {
                return false;
            }
        }

        return true;
    }

    void ClearLines() {
        int r = ROWS-1;
        while (r>=0) {
            if(IsRowFull(r)) {
                ClearRow(r);
                break;
            }
            r--;
        }
    }

    void RecursiveMoveDown() {
        int r = ROWS-1;
        while (r>0) {
            if(IsRowEmpty(r) && !IsRowEmpty(r-1)) {
                RecursiveMoveDown(r-1);
                r = ROWS-1;
                continue;
            }
            r--;
        }
    }

    void ClearRow(int r) {
        for(int c=0; c<COLS; ++c) {
            m_grid[r][c]->Clear();
        }
    }

    void RecursiveMoveDown(int r) {
        for(int c=0; c<COLS; ++c) {
            if(!m_grid[r][c]->IsEmpty()) {
                m_grid[r+1][c]->SetBlock(m_grid[r][c]->block);
                m_grid[r][c]->Clear(false);
            }
        }
    }
};

#endif //ZCOREENGINE_BOARD_H
