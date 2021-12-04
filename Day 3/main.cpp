#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


void PartOne(string fileName)
{
	ifstream dataFileStream(fileName);
	if (dataFileStream.is_open())
	{
		string line;
		size_t bitArraySize;
		vector<int> tmpGamma;

		std::getline(dataFileStream, line);
		bitArraySize = line.length();
		tmpGamma.resize(bitArraySize);

		for (int i = 0; i < bitArraySize; i++)
		{
			dataFileStream.clear();
			dataFileStream.seekg(0, ios::beg);
			while (std::getline(dataFileStream, line))
			{
				tmpGamma[i] += (line[i] == '0' ? -1 : +1);
			}
		}

		string gamma, epsilon;

		for (int i = 0; i < bitArraySize; i++)
		{
			// == 0 ???
			gamma.append(tmpGamma[i] > 0 ? "1" : tmpGamma[i] < 0 ? "0" : "?");
			//epsilon.append(tmpGamma[i] < 0 ? "1" : "0");
			epsilon.append(tmpGamma[i] < 0 ? "1" : tmpGamma[i] > 0 ? "0" : "?");
		}

		std::cout
			<< "PART ONE:\r\n"
			<< "Gamma " << gamma << " [" << stoul(gamma, nullptr, 2) << "] "
			<< "Epsilon " << epsilon << " [" << stoul(epsilon, nullptr, 2) << "]\r\n"
			<< "Power consumption " << " [" << stoul(gamma, nullptr, 2) * stoul(epsilon, nullptr, 2) << "]\r\n\r\n";

		dataFileStream.close();
	}
	else
	{
		cout << "Datafile is brrrr." << endl;
	}
}


void PartTwo()
{
}

int main()
{
	PartOne("data.txt");
	//PartOne("example.txt");
	PartTwo();
}

void oldPartOne()
{
	// work with example but not with data
	ifstream dataFileStream("example.txt");
	if (dataFileStream.is_open())
	{
		string line;
		size_t bitArraySize;
		vector<uint8_t> unos;
		vector<uint8_t> zeros;
		vector<uint8_t> lineData;
		vector <vector<uint8_t>> rawData{};

		std::getline(dataFileStream, line);
		bitArraySize = line.length();
		lineData.resize(bitArraySize);
		zeros.resize(bitArraySize);
		unos.resize(bitArraySize);

		do
		{
			for (int i = 0; i < bitArraySize; i++)
			{
				lineData[i] = line[i] - '0';
				if (lineData[i])
					unos[i]++;
				else
					zeros[i]++;
			}
			std::getline(dataFileStream, line);
			rawData.push_back(lineData);
		} while (dataFileStream.good());

		std::string a, b;
		for (int i = 0; i < bitArraySize; i++)
		{
			if (unos[i] == zeros[i])
				std::cout << "dindu nuffin" << "\r\n";
			a.append((unos[i] > zeros[i] ? "1" : "0"));
			b.append((unos[i] < zeros[i] ? "1" : "0"));
		}
		std::cout << rawData.size() << " [" << bitArraySize << "]\r\n"
			<< a << " [" << stoul(a, nullptr, 2) << "] "
			<< b << " [" << stoul(b, nullptr, 2) << "]\r\n"
			<< "Result [" << stoul(a, nullptr, 2) * stoul(b, nullptr, 2) << "]" << std::endl;

		dataFileStream.close();
	}
}