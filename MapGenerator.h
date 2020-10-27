#pragma once
class MapGenerator
{


	// Tile Indexer
	struct TILE_INDEX {
		char tile;
		int colour;
	};

	// Tiles
	TILE_INDEX tiles[9] = {
		{ '~', 9},			// (0) deep water
		{ '~', 11 },		// (1) shallow water
		{ '.', 14 },		// (2) sand bank
		{ '.', 2 },			// (3) grass plains
		{ 'T', 10},			// (4) forest
		{ '~', 8 },			// (5) hill region
		{ '^', 15 },			// (6) mountain
	};
};

