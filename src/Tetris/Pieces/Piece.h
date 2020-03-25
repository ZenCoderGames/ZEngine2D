//
// Created by srinavinnair on 1/28/20.
//

#ifndef ZCOREENGINE_PIECE_H
#define ZCOREENGINE_PIECE_H

#include "../TetrisConfig.h"
#include "../Board.h"

class Piece {
protected:
    const char* m_baseEntityId;
    std::vector<Cell*> m_cells, m_helperCells;

    int m_row, m_col, m_helperRow;
    Board* m_parentBoard;
    bool m_hasBeenPlaced;

    int m_currentRotation;

    virtual void RotateForOrientation() {}

    void RotateLeft() {
        m_currentRotation--;
        if(m_currentRotation<0)
            m_currentRotation = 3;
        RotateForOrientation();
    }

    void RotateRight() {
        m_currentRotation++;
        if(m_currentRotation>3)
            m_currentRotation = 0;
        RotateForOrientation();
    }
public:
    Piece(Board* parentBoard, const char* baseEntityId, int row, int col) {
        m_parentBoard = parentBoard;
        m_baseEntityId = baseEntityId;
        m_row = row;
        m_col = col;
        m_hasBeenPlaced = false;

        for(int i=0; i<4; ++i) {
            CreateBlock();
            CreateHelperBlock();
        }
    }

    ~Piece() {
        for(int i=0; i<4; ++i) {
            m_helperCells[i]->block->Destroy();
            delete m_helperCells[i];
        }
    }

    void Initialize() {
        m_currentRotation = 0;
        RotateForOrientation();
    }

    int GetRow() { return m_row; }

    int GetCol() { return m_col; }

    void CreateBlock() {
        Cell* newCell = new Cell(0, 0);
        m_cells.push_back(newCell);

        std::string entityName = std::string("Block_") + std::to_string(m_cells.size()+1);
        Entity *newBlock = Engine::entityManager->DuplicateEntity(m_baseEntityId, entityName.c_str(), true);
        newCell->SetBlock(newBlock);

        newBlock->SetActive(false);
    }

    std::vector<Cell*> GetCells() {
        return m_cells;
    }

    void Update() {
        for(int i=0; i<m_cells.size(); ++i) {
            UpdateCell(m_cells[i], m_row);
        }

        UpdateHelperLocation();

        for(int i=0; i<m_helperCells.size(); ++i) {
            UpdateCell(m_helperCells[i], m_helperRow);
        }
    }

    void UpdateCell(Cell* cell, int row) {
        Entity* block = cell->block;

        if(!block->IsActive()) {
            block->SetActive(true);
        }

        TransformComponent *transformComponent = block->GetComponent<TransformComponent>();
        transformComponent->position.x = START_X + (m_col + cell->c) * 32;
        transformComponent->position.y = START_Y + (row + cell->r) * 32;
    }

    void MoveLeft() {
        m_col--;
        if(m_parentBoard->CheckOverflow(m_row, m_col, m_cells)) {
            m_col++;
        }
    }

    void MoveRight() {
        m_col++;
        if(m_parentBoard->CheckOverflow(m_row, m_col, m_cells)) {
            m_col--;
        }
    }

    void RotateCCW() {
        RotateLeft();

        if(m_parentBoard->CheckOverflow(m_row, m_col, m_cells)) {
            // Failed so return
            RotateRight();

            // Wall kick R
            MoveRight();
            RotateLeft();
            if(m_parentBoard->CheckOverflow(m_row, m_col, m_cells)) {
                MoveLeft();
                RotateRight();
            }
            else {
                // Wall kick L
                MoveLeft();
                RotateLeft();
                if (m_parentBoard->CheckOverflow(m_row, m_col, m_cells)) {
                    MoveRight();
                    RotateRight();
                }
            }
        }
    }

    void RotateCW() {
        RotateRight();

        if(m_parentBoard->CheckOverflow(m_row, m_col, m_cells)) {
            // Failed so return
            RotateLeft();

            // Wall kick R
            MoveRight();
            RotateRight();
            if(m_parentBoard->CheckOverflow(m_row, m_col, m_cells)) {
                MoveLeft();
                RotateLeft();
            }
            else {
                // Wall kick L
                MoveLeft();
                RotateRight();
                if (m_parentBoard->CheckOverflow(m_row, m_col, m_cells)) {
                    MoveRight();
                    RotateLeft();
                }
            }
        }
    }

    bool MoveDown() {
        m_row++;
        if(m_parentBoard->CheckOverflow(m_row, m_col, m_cells)) {
            m_row--;
            m_hasBeenPlaced = true;
            return false;
        }
        return true;
    }

    void Drop() {
        while(MoveDown()) {

        }
    }

    bool HasBeenPlaced() {
        return m_hasBeenPlaced;
    }

    void CreateHelperBlock() {
        Cell* newCell = new Cell(0, 0);
        m_helperCells.push_back(newCell);

        std::string entityName = std::string("HelperBlock_") + std::to_string(m_helperCells.size()+1);
        Entity *newBlock = Engine::entityManager->DuplicateEntity(m_baseEntityId, entityName.c_str(), true);
        newBlock->GetComponent<SpriteComponent>()->SetAlpha(96);
        newCell->SetBlock(newBlock);

        newBlock->SetActive(false);
    }

    void UpdateHelperLocation() {
        for(int i=0; i<m_cells.size(); ++i) {
            m_helperCells[i]->r = m_cells[i]->r;
            m_helperCells[i]->c = m_cells[i]->c;
        }

        // Predict downwards
        m_helperRow = m_row;
        while(true) {
            m_helperRow++;
            if (m_parentBoard->CheckOverflow(m_helperRow, m_col, m_cells)) {
                m_helperRow--;
                break;
            }
        }


    }
};

#endif //ZCOREENGINE_PIECE_H
