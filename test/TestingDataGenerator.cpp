#include "TestingDataGenerator.h"


using namespace Vroom;


void TestingDataGenerator::GenerateCheckBoardPattern( Volume &vol )
{
	vol.Create( 32, 32, 32 );

	for(int z=0; z< vol.GetDepth(); z++)
	{
		for(int y=0; y< vol.GetHeight(); y++)
		{
			for(int x=0; x< vol.GetDepth(); x++)
			{
				Color col( (x+y+z)%2 * 255, 0, 255 );
				vol.SetVoxel(x, y, z, col);
			}
		}
	}
}
