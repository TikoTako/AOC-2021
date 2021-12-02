#include <format>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// std::format <- latest standard 

struct DataStruct
{
	char wut;
	int wat;
};

void PartOne(std::vector<DataStruct>* rawData)
{
	// example 150
	// data 1714950
	int forwards = 0, ups = 0, downs = 0;

	for (auto& data : *rawData)
	{
		switch (data.wut)
		{
			case 'f': // forward
				forwards += data.wat;
				break;
			case 'u': // up
				ups += data.wat;
				break;
			case 'd': // down
				downs += data.wat;
				break;
			default:
				break;
		}
	}
	std::cout << std::format("PART ONE:\r\n\tForwards [{}]\tDowns [{}]\tUps [{}]\r\n\tResult [{}]\r\n", forwards, downs, ups, (downs - ups) * forwards);
}

void PartTwo(std::vector<DataStruct>* rawData)
{
	// example 900
	// data 1281977850
	int forwards = 0, ups = 0, downs = 0, aim = 0, depth = 0, tmpForwards;

	for (auto& data : *rawData)
	{
		switch (data.wut)
		{
			case 'f': // forward
				tmpForwards = data.wat;
				forwards += tmpForwards;
				depth += tmpForwards * aim;
				break;
			case 'u': // up
				aim -= data.wat;
				break;
			case 'd': // down
				aim += data.wat;
				break;
			default:
				break;
		}
	}
	std::cout << std::format("PART TWO:\r\n\tForwards [{}]\tAim [{}]\tDepth [{}]\r\n\tResult [{}]\r\n", forwards, aim, depth, forwards * depth);
}

std::vector<DataStruct> LoadData(std::string fileName)
{
	std::vector<DataStruct> r{};
	std::ifstream dataFile(fileName);
	if (dataFile.is_open())
	{
		std::string line;
		while (dataFile.good())
		{
			std::getline(dataFile, line);
			switch (line[0])
			{
				case 'f':
					r.push_back(*(new DataStruct{ 'f', std::stoi(line.substr(7, line.length() - 7)) }));
					break;
				case 'd':
					r.push_back(*(new DataStruct{ 'd', std::stoi(line.substr(4, line.length() - 4)) }));
					break;
				case 'u':
					r.push_back(*(new DataStruct{ 'u', std::stoi(line.substr(3, line.length() - 3)) }));
					break;
				default:
					break;
			}
		}
	}
	return  r;
}

int main()
{
	std::string fileName = /*"example.txt"*/ "data.txt";
	std::vector<DataStruct> data = LoadData(fileName);
	if (data.size() > 0)
	{
		PartOne(&data);
		PartTwo(&data);
	}
	else
	{
		std::cout << "Can't get data from file [" << fileName << "] for some reason.\r\n";
	}
	std::cin.get();
}