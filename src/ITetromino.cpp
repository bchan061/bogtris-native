#include "include/ITetromino.h"
#include "include/Constants.h"

ITetromino::ITetromino(bool* shape) : Tetromino("I", Constants::Colors::CYAN, shape, 4)  {
	this->generateOffsets();
}

void ITetromino::generateOffsets() {
	/*
	 * These offsets are assuming that as y points up.
	 * We'll need to flip the y-values later.
	 */
	this->offsets = std::vector<std::vector<std::vector<int>>>{
		{
			{ {0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0} },
			{ {-1, 0}, {0, 0}, {0, 0}, {0, 1}, {0, -2} },
			{ {-1, 1}, {1, 1}, {-2, 1}, {1, 0}, {-2, 0} },
			{ {0, 1}, {0, 1}, {0, 1}, {0, -1}, {0, 2} }
		}
	};
}