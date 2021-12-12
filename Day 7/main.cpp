#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

typedef unsigned int uint;
typedef std::vector <uint> TinyCrabsSubmarines;

TinyCrabsSubmarines LoadTinySubmarinePosition(std::string fileName, int* maxPos)
{
	int i;
	std::string str;
	TinyCrabsSubmarines r;
	std::ifstream fileStream(fileName);
	while (std::getline(fileStream, str, ','))
	{
		if (!str.empty())
		{			
			if ((i = stoi(str)) > *maxPos)
				*maxPos = i;
			r.push_back(i);
		}
	}
	return r;
}


int main()
{
	int maxPos = 0;
	auto tinyCrabsSubemarines = LoadTinySubmarinePosition("example.txt", &maxPos);
	std::cout << tinyCrabsSubemarines.size() << " - " << maxPos << std::endl;
	for (auto tCS : tinyCrabsSubemarines)
		std::cout << tCS << " ";
	std::cout << std::endl << std::endl;

	std::map <int, int> leMap;
	for (auto tCS : tinyCrabsSubemarines)
		leMap[tCS]++;

	for (auto& tCS : leMap)
		std::cout << tCS.first << " " << tCS.second << std::endl;
	std::cout << std::endl;

	//                          ¯\_(?)_/¯
}