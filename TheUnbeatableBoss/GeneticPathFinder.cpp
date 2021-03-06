#include"pch.h"
#include "GeneticPathFinder.h"
#include"TileMap.h"
DECLARE_GENOME(Dir)
GeneticPathFinder::GeneticPathFinder(sf::Vector2f start,sf::Vector2f end)
:GBrain(CROSSOVER_RATE,
	MUTATION_RATE,
	POP_SIZE,
	CHROMO_LENGTH,
	GENE_LENGTH)
{
	SourceIndex = TileMap::GetIndexForPosition(start);
	DestinationIndex = TileMap::GetIndexForPosition(end);
	Genome<Dir>::AddPossibleValue(Dir::DOWN,"DOWN");
	Genome<Dir>::AddPossibleValue(Dir::LEFT,"LEFT");
	Genome<Dir>::AddPossibleValue(Dir::UP,"UP");
	Genome<Dir>::AddPossibleValue(Dir::RIGHT,"RIGHT");
	Genome<Dir>::FitnessFunction = [this](vector<Dir> path)
	{
		
		auto currentIndex = SourceIndex;
		for (auto dir : path)
		{
				switch (dir)
				{
				case Dir::DOWN:
				{
					if (currentIndex.second < 0 || currentIndex.second > NO_OF_ROWS)
						break;
					currentIndex.second += 1;
					break;
				}
				case Dir::LEFT:
				{
					if (currentIndex.first <= 0 || currentIndex.first > NO_OF_COLS)
						break;
					currentIndex.first -= 1;
					break;
				}case Dir::UP:
				{
					if (currentIndex.second <= 0 || currentIndex.second > NO_OF_ROWS)
						break;
					currentIndex.second -= 1;
					break;
				}case Dir::RIGHT:
				{
					if (currentIndex.first < 0 || currentIndex.first > NO_OF_COLS)
						break;
					currentIndex.first += 1;
					break;
				}
				}
		}
		int diffX = abs(DestinationIndex.first - currentIndex.first);
		int diffY = abs(DestinationIndex.second - currentIndex.second);

		return (1 / ((double)diffX + diffY + 1));
	};
	
}

void GeneticPathFinder::FindPath()
{
	GBrain.Run();
}


GeneticPathFinder::~GeneticPathFinder()
{
}
