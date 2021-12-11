#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector <unsigned char> LoadTheFishes(std::string fileName)
{
	std::string fish;
	std::vector <unsigned char> lotsOfFishes;
	std::ifstream fileSea(fileName);

	while (std::getline(fileSea, fish, ','))
	{
		if (!fish.empty())
			lotsOfFishes.push_back(stoi(fish));
	}
	return lotsOfFishes;
}

// pc go brrr with 9001 mirion thousands ram used
void PartOneV1(std::vector <unsigned char>* lotsOfFishes, int days, bool wannaPrintAll)
{	
	int i = 0;

	if (wannaPrintAll)
	{
		std::cout << "Day [0] Fish count [" << lotsOfFishes->size() << "] -> ";
		for (auto f : *lotsOfFishes)
			std::cout << f << ",";
		std::cout << "\b " << std::endl;
	}

	for (; i < days; i++)
	{
		size_t leFishesNumbers = lotsOfFishes->size();
		for (int ii = 0; ii < leFishesNumbers; ii++) // -> size here change each loop
		{
			if ((*lotsOfFishes)[ii] == 0)
			{
				(*lotsOfFishes)[ii] = 6;
				lotsOfFishes->push_back(8);
				continue;
			}
			(*lotsOfFishes)[ii]--;
		}
		if (wannaPrintAll)
		{
			std::cout << "Day [" << i + 1 << "] - ";
			for (auto f : *lotsOfFishes)
				std::cout << f << ",";
			std::cout << "\b " << std::endl;
		}
	}

	std::cout << "Day [" << days << "] Fish count [" << lotsOfFishes->size() << "]." << std::endl;
}

unsigned long long PartOneV2(std::vector <unsigned char>* lotsOfFishes, int days)
{
	unsigned long long 
		FishesDividedByDay[9] = { 0 },
		tmpFishesDividedByDay[9] = { 0 };

	for (auto f : *lotsOfFishes)
		FishesDividedByDay[f]++;

	int i = 0;
	for (; i < days; i++)
	{
		memcpy(tmpFishesDividedByDay, FishesDividedByDay + 1, sizeof(FishesDividedByDay) - 1);
		tmpFishesDividedByDay[6] = FishesDividedByDay[7] + FishesDividedByDay[0];
		tmpFishesDividedByDay[8] = FishesDividedByDay[0];
		memcpy(FishesDividedByDay, tmpFishesDividedByDay, sizeof(FishesDividedByDay));
	}

	unsigned long long r = 0;
	for (auto f : FishesDividedByDay)
		r += f;
	return r;
}

int main()
{
	std::cout << "Day 6.\n";
	auto fileName = "data.txt";
	auto Fishes = LoadTheFishes(fileName);
	std::cout << "Fishes after 18 days: " << PartOneV2(&Fishes, 18) << std::endl;
	std::cout << "Fishes after 80 days: " << PartOneV2(&Fishes, 80) << std::endl;
	std::cout << "Fishes after 256 days: " << PartOneV2(&Fishes, 256) << std::endl;
}


