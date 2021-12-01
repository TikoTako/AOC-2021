#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int PartOne(ifstream* dataFile)
{
	std::string line;
	int prec, corr, tot = 0;
	std::getline(*dataFile, line);
	prec = std::stoi(line);
	while (std::getline(*dataFile, line))
	{
		corr = std::stoi(line);
		if (corr > prec)
			tot++;
		prec = corr;
	}
	std::cout << "PART ONE\r\nThere are " << tot << " measurements larger than the previous.\r\n";
	return tot;
}

int PartTwo(ifstream* dataFile)
{
	int tot = 0;
	std::string line;
	vector <int> data;
	dataFile->clear(); // eof flag durr
	dataFile->seekg(0, ios::beg);
	while (std::getline(*dataFile, line))
	{
		data.insert(data.end(), std::stoi(line));
	}
	int prec, curr;
	prec = data[0] + data[1] + data[2];
	cout << prec << endl;
	for (size_t i = 1; i < data.size() -2; i++)
	{
		curr = data[i] + data[i+1] + data[i+2];
		if (curr > prec)
			tot++;
		prec = curr;
	}
	std::cout << "PART TWO\r\nThere are " << tot << " measurements larger than the previous.\r\n";
	return tot;
}

int main()
{
	bool useExampleData = false;
	std::ifstream dataFile(useExampleData ? "example.txt" : "data.txt");
	std::cout << (useExampleData ? "Example d" : "D") << "ata file open [" << (dataFile.is_open() ? "ok" : "fail") << "]\r\n";

	if (dataFile.is_open())
	{
		int r;
		r = PartOne(&dataFile);
		if (useExampleData)
			std::cout << "Test [" << (r == 7 ? "PASSED" : "FAILED") << "]\r\n";
		r = PartTwo(&dataFile);
		if (useExampleData)
			std::cout << "Test [" << (r == 5 ? "PASSED" : "FAILED") << "]\r\n";
		dataFile.close();
	}
	cin.get();
}