#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int PartOne(std::vector <int>* data)
{
	int prec = (*data)[0],
		corr = 0,
		tot = 0;

	for (size_t i = 1; i < data->size(); i++)
	{
		corr = (*data)[i];
		tot += corr > prec ? 1 : 0;
		prec = corr;
	}
	return tot;
}

int PartTwo(std::vector <int>* data)
{
	int prec = (*data)[0] + (*data)[1] + (*data)[2],
		curr = 0,
		tot = 0;
	for (size_t i = 1; i < data->size() - 2; i++)
	{
		curr = (*data)[i] + (*data)[i + 1] + (*data)[i + 2];
		tot += curr > prec ? 1 : 0;
		prec = curr;
	}
	return tot;
}

std::vector <int> LoadData(std::string fileName)
{
	std::vector <int> data{};
	std::ifstream dataFile(fileName);
	if (dataFile.is_open())
	{
		std::string line;
		while (std::getline(dataFile, line))
		{
			data.insert(data.end(), std::stoi(line));
		}
		dataFile.close();
	}
	return data;
}

int main()
{
	std::string fileName = /*"example.txt";*/ "data.txt";
	std::vector <int> data = LoadData(fileName);

	if (!data.empty())
	{
		std::cout << "Data file loaded [" << fileName << "]" << std::endl
			<< "Part one: " << PartOne(&data) << std::endl
			<< "Part two: " << PartTwo(&data) << std::endl;
	}
	else
	{
		std::cout << "Can't load data file." << std::endl;
	}
	cin.get();
}