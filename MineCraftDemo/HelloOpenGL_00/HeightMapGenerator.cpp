#include "HeightMapGenerator.h"
#include "noise.h"
#include "WorldInfo.h"


void HeightMapGenerator::heightMapGenerate(Chunk * chunk)
{
	int minHeight = 25535;
	int maxHeight = -25535;
	for (int x = (chunk->getLoc()->x*WorldInfo::chunkSize); x < ((chunk->getLoc()->x + 1)*WorldInfo::chunkSize); x++) {
		for (int z = (chunk->getLoc()->z*WorldInfo::chunkSize); z < ((chunk->getLoc()->z + 1)*WorldInfo::chunkSize); z++) {
			float f = simplex2(x * 0.01, z * 0.01, 4, 0.5, 2);
			float g = simplex2(-x * 0.01, -z * 0.01, 2, 0.9, 2);
			int mh = g * 32 + 16;
			int h = f * mh;
			if (h < minHeight) {
				minHeight = h;
			}
			if (h > maxHeight) {
				maxHeight = h;
			}
			chunk->heightMap[vector<int>{ x, z }] = h;
		}
	}
	chunk->setMinHeight(minHeight);
	chunk->setMaxHeight(maxHeight);
}
