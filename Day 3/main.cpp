#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


vector <vector<uint8_t>> LoadData(std::string fileName)
{
	std::cout << "Loading data file [" << fileName << "]" << std::endl;
	vector <vector<uint8_t>> tmpRawData{};
	ifstream dataFileStream(fileName);
	if (dataFileStream.is_open())
	{
		size_t dataLineSize;
		std::string dataLine;
		std::getline(dataFileStream, dataLine);
		dataLineSize = dataLine.length();
		vector<uint8_t> tmpData(dataLineSize);
		do
		{
			for (int i = 0; i < dataLineSize; i++)
			{
				tmpData[i] = dataLine[i] - '0';
			}
			tmpRawData.push_back(tmpData);
		} while (std::getline(dataFileStream, dataLine));
	}
	else
	{
		std::cout << "Datafile is brrrr." << std::endl;
	}
	return tmpRawData;
}

int GetMostCommon(vector <vector<uint8_t>>* tmpData, unsigned int pos)
{
	int r = 0;
	for (vector<uint8_t> tmpLine : (*tmpData))
	{
		r += (tmpLine[pos] == 0 ? -1 : +1);
	}
	return r;
}

int GetMostCommon(vector <vector<uint8_t>>* tmpData, unsigned int pos, bool isOGR)
{
	int r = GetMostCommon(tmpData, pos);
	return isOGR ?
		(r > 0 ? 1 : (r == 0 ? 1 : 0)) :
		(r > 0 ? 0 : (r == 0 ? 0 : 1));
}

void PartOne(vector <vector<uint8_t>>* rawData)
{
	int mc = 0;
	std::string gamma, epsilon;

	for (int i = 0; i < (*rawData)[0].size(); i++)
	{
		mc = GetMostCommon(rawData, i/*, true*/);
		mc = mc > 0 ? 1 : (mc < 0 ? 0 : -1);
		gamma.append(mc == -1 ? "1" : to_string(mc));
		epsilon.append(mc == -1 ? "0" : to_string(mc == 0 ? 1 : 0));
	}

	std::cout
		<< "PART ONE:\r\n"
		<< "Gamma " << gamma << " [" << stoul(gamma, nullptr, 2) << "] "
		<< "Epsilon " << epsilon << " [" << stoul(epsilon, nullptr, 2) << "]\r\n"
		<< "Power consumption " << " [" << stoul(gamma, nullptr, 2) * stoul(epsilon, nullptr, 2) << "]\r\n\r\n";
}

vector <uint8_t> GetRating(vector <vector<uint8_t>> rawDataCopy, bool isOxigen)
{
	int i = 0, mc;
	while (rawDataCopy.size() > 1)
	{
		mc = GetMostCommon(&rawDataCopy, i, isOxigen);
		auto tmpData = rawDataCopy.begin();
		while (tmpData != rawDataCopy.end())
		{
			if ((*tmpData)[i] == mc)
			{
				tmpData++;
			}
			else
			{
				tmpData = rawDataCopy.erase(tmpData);
			}
		}
		i++;
	}
	return rawDataCopy[0];
}

uint32_t BitVecToUint(vector <uint8_t>* uve)
{
	// inverted bits derp
	size_t b = (*uve).size() - 1;
	uint32_t r = 0;
	for (auto v : (*uve))
	{
		r += v << b;
		b--;
	}
	return r;
}

std::string BitVecToString(vector <uint8_t>* uve)
{
	std::string r;
	for (auto v : (*uve))
	{
		r.push_back(v + '0');
	}
	return r;
}

void PartTwo(const vector <vector<uint8_t>>* rawData)
{
	std::cout << "PART TWO -- data lines " << rawData->size() << " data size " << (*rawData)[0].size() << std::endl;
	vector <uint8_t> OGR = GetRating(*rawData, true); // oxygen generator rating
	vector <uint8_t> CO2SR = GetRating(*rawData, false); // CO2 scrubber rating
	cout << "Oxygen Generator Rating: " << BitVecToString(&OGR) << " [" << BitVecToUint(&OGR) << "]" << endl;
	cout << "CO2 Srubber Rating: " << BitVecToString(&CO2SR) << " [" << BitVecToUint(&CO2SR) << "]" << endl;
	cout << "Life support rating: " << BitVecToUint(&OGR) * BitVecToUint(&CO2SR) << endl;
}

int main()
{
	//vector <vector<uint8_t>> rawData = LoadData("example.txt");
	vector <vector<uint8_t>> rawData = LoadData("data.txt");
	PartOne(&rawData);
	PartTwo(&rawData);
}

///////////////************************************ old crap

void PartOne_V0()
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

void PartOne_V1(std::string fileName)
{
	//work with both data
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