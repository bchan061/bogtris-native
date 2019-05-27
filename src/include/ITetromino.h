#pragma once

#include "Tetromino.h"

class ITetromino : public Tetromino {
	public:
		ITetromino(bool* shape);
		void generateOffsets() override;
};
