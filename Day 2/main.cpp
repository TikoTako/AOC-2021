#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct DataStruct
{
	std::vector <int> Forwards;
	std::vector <int> Downs;
	std::vector <int> Ups;
};

void PartOne()
{	
	// example 150
	// data 1714950
	int forwards = 0, ups = 0, downs = 0;
	std::string dataFileName = "data.txt";
	std::ifstream dataFileStream(dataFileName);
	if (dataFileStream.is_open())
	{
		std::cout << "open ok" << std::endl;
		std::string line;
		while (dataFileStream.good())
		{
			std::getline(dataFileStream, line);
			switch (line[0])
			{
				case 'f': // forward
					forwards += std::atoi(line.substr(7, line.length() - 7).c_str());
					break;
				case 'u': // up
					ups += std::atoi(line.substr(3, line.length() - 3).c_str());
					break;
				case 'd': // down
					downs += std::atoi(line.substr(4, line.length() - 4).c_str());
					break;
				default:
					std::cout << "da fuq ??" << std::endl;
					break;
			}
		}
		std::cout << forwards << " - " << ups << " " << downs << " " << (downs - ups) * forwards << std::endl;
		dataFileStream.close();
	}
	else
	{
		std::cout << "open error" << std::endl;
	}
}

void PartTwo()
{
	// example 900
	// data 1281977850
	int forwards = 0, ups = 0, downs = 0, aim = 0, depth = 0;
	std::string dataFileName = "data.txt";
	std::ifstream dataFileStream(dataFileName);
	if (dataFileStream.is_open())
	{
		std::cout << "open ok" << std::endl;
		std::string line;
		while (dataFileStream.good())
		{
			std::getline(dataFileStream, line);
			switch (line[0])
			{
				case 'f': // forward
				{
					int f = std::atoi(line.substr(7, line.length() - 7).c_str());
					forwards += f;
					depth += f * aim;
					std::cout << forwards << " " << aim << " " << depth << std::endl;
				}
				break;
				case 'u': // up
					aim -= std::atoi(line.substr(3, line.length() - 3).c_str());
					std::cout << "u " << aim << " " << depth << std::endl;
					break;
				case 'd': // down
					aim += std::atoi(line.substr(4, line.length() - 4).c_str());
					std::cout << "d " << aim << " " << depth << std::endl;
					break;
				default:
					std::cout << "da fuq ??" << std::endl;
					break;
			}
		}
		std::cout << forwards << " - " << aim << " " << depth << " " << forwards * depth << std::endl;
		dataFileStream.close();
	}
	else
	{
		std::cout << "open error" << std::endl;
	}
}

int main()
{
	//PartOne();
	PartTwo();
	std::cin.get();
}