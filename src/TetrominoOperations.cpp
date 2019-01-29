#include "include/TetrominoOperations.h"

bool TetrominoOperations::tryMove(Board& board, Tetromino& tetromino, SDL_Point& currentLocation, SDL_Point& offset) {
    SDL_Point attempt;
    attempt.x = currentLocation.x + offset.x;
    attempt.y = currentLocation.y + offset.y;
    if (!board.tetrominoCollides(tetromino, attempt)) {
        currentLocation.x = attempt.x;
        currentLocation.y = attempt.y;
        return true;
    } else {
        return false;
    }
}

bool TetrominoOperations::softDrop(Board& board, Tetromino& tetromino, SDL_Point& currentLocation) {
    SDL_Point offset;
    offset.x = 0;
    offset.y = 1;
    if (!TetrominoOperations::tryMove(board, tetromino, currentLocation, offset)) {
        return true;
    }
    return false;
}

bool TetrominoOperations::hardDrop(Board& board, Tetromino& tetromino, SDL_Point& currentLocation) {
    SDL_Point offset;
    offset.x = 0;
    offset.y = 1;
    while (TetrominoOperations::tryMove(board, tetromino, currentLocation, offset)) {

    }
    board.renderTetromino(tetromino, currentLocation);

    return true;
}

int TetrominoOperations::tryRotate(Board& board, Tetromino& tetromino, SDL_Point& currentLocation, bool clockwise) {
    int nextRotationBox = -1;
    if (clockwise) {
        nextRotationBox = 1;
    }

    int nextRotationState = (
        (tetromino.getShapeIndex() + nextRotationBox) + Tetromino::AMOUNT_OF_ROTATION_BOXES
    ) % Tetromino::AMOUNT_OF_ROTATION_BOXES;
    /*
     * Test each of the offsets in order.
     * If the next offset is B, and the current offset is A, we calculate A - B.
     */
    std::vector<std::vector<int>> offsetA = tetromino.getOffsets()->at(tetromino.getShapeIndex());
    std::vector<std::vector<int>> offsetB = tetromino.getOffsets()->at(nextRotationState);
    for (unsigned int i = 0; i < Tetromino::AMOUNT_OF_KICKS; i++) {
        std::vector<int> kickA = offsetA.at(i);
        std::vector<int> kickB = offsetB.at(i);
        std::vector<int> kick = { kickA.at(0) - kickB.at(0), kickA.at(1) - kickB.at(1) };

        if (clockwise) {
            tetromino.rotateRight();
        } else {
            tetromino.rotateLeft();
        }

        SDL_Point newPossibleLocation = {
            currentLocation.x + kick.at(0),
            /* Flip the y-values of the kick. */
            currentLocation.y - kick.at(1)
        };

        if (
            !board.tetrominoCollides(
                tetromino,
                newPossibleLocation
            )
        ) {
            currentLocation = newPossibleLocation;
            return i;
        } else {
            /* Reverse the rotation. */
            if (clockwise) {
                tetromino.rotateLeft();
            } else {
                tetromino.rotateRight();
            }
        }
    }

    /* No kicks work. */
    return -1;
}
