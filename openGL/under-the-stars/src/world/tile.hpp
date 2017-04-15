#include "block.hpp"

// a tile is a group of blocks
struct Tile {
	Block blocks[64][64][4];
};

class Tiles {
private:
public:
	void glDraw();
};
