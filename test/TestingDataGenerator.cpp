#include "TestingDataGenerator.h"

void TestingDataGenerator::GenerateCheckBoardPattern( Volume &vol )
{

	vol.Create( 32, 32, 32 );

	for(int z=0; z< vol.GetDepth(); z++)
	{
		for(int y=0; y< vol.GetHeight(); y++)
		{
			for(int x=0; x< vol.GetDepth(); x++)
			{
				//vol.Set
			}
		}
	}
}