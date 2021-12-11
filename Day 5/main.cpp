#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Line
{
	int X_1;
	int Y_1;
	int X_2;
	int Y_2;

	Line(int x1, int y1, int x2, int y2)
	{
		X_1 = x1;
		Y_1 = y1;
		X_2 = x2;
		Y_2 = y2;
	}
};

std::vector<Line> LoadData(std::string fileName, int* max_X, int* max_Y)
{
	std::vector<Line> r;
	std::ifstream dataFileStream(fileName);
	if (dataFileStream.is_open())
	{
		std::string tmpstr;
		do
		{
			// 0,9 -> 5,9
			int x1, y1, x2, y2;
			std::getline(dataFileStream, tmpstr, ',');
			if (tmpstr.empty()) // data.txt end with an empty line
				break;
			x1 = std::stoi(tmpstr);
			std::getline(dataFileStream, tmpstr, ' ');
			y1 = std::stoi(tmpstr);
			dataFileStream >> tmpstr;
			std::getline(dataFileStream, tmpstr, ',');
			x2 = std::stoi(tmpstr);
			std::getline(dataFileStream, tmpstr);
			y2 = std::stoi(tmpstr);
			r.push_back(*(new Line(x1, y1, x2, y2)));
			if (*max_X < x1 || *max_X < x2)
			{
				*max_X = x1 > x2 ? x1 : x2;
			}
			if (*max_Y < y1 || *max_Y < y2)
			{
				*max_Y = y1 > y2 ? y1 : y2;
			}

		} while (!dataFileStream.eof()); // example end with a data line
	}
	else
	{
		std::cout << "Something went wrong with the data file [" << fileName << "]\r\n";
	}
	(*max_X)++;
	(*max_Y)++;
	return r;
}

void PrintMatrix(std::vector<std::vector<int>>* vec, int x, int y, bool printmatrix)
{
	int overlaps = 0;
	std::stringstream ss;
	if (printmatrix)
		ss << "Matrix" << std::endl;
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (printmatrix)
				ss << (*vec)[i][j] << " ";
			overlaps += (*vec)[i][j] > 1 ? 1 : 0;
		}
		if (printmatrix)
			ss << "\b " << std::endl;
	}
	if (printmatrix)
		std::cout << ss.str();
	std::cout << "Overlaps: " << overlaps << std::endl;
}

std::vector<std::vector<int>> PartOne(std::vector<Line>* RawData, int max_X, int max_Y, bool printmatrix)
{
	std::cout << "Part One" << std::endl;
	std::vector<std::vector<int>> Matrix(max_Y, std::vector<int>(max_X, 0));
	for (auto& a : *RawData)
	{
		if (a.X_1 == a.X_2)
		{
			int y_h = a.Y_1 > a.Y_2 ? a.Y_1 : a.Y_2;
			int y_l = a.Y_1 < a.Y_2 ? a.Y_1 : a.Y_2;
			for (int y = y_l; y <= y_h; y++)
				Matrix[y][a.X_1]++;
		}
		else if (a.Y_1 == a.Y_2)
		{
			int x_h = a.X_1 > a.X_2 ? a.X_1 : a.X_2;
			int x_l = a.X_1 < a.X_2 ? a.X_1 : a.X_2;
			for (int x = x_l; x <= x_h; x++)
				Matrix[a.Y_1][x]++;
		}
	}
	PrintMatrix(&Matrix, max_X, max_Y, printmatrix);
	return Matrix;
}

void PartTwo(std::vector<Line>* RawData, std::vector<std::vector<int>>* Matrix, int max_X, int max_Y, bool printmatrix)
{
	std::cout << "Part Two" << std::endl;

	for (auto& a : *RawData)
	{
		if (a.X_1 != a.X_2 && a.Y_1 != a.Y_2)
		{
			int
				start_X = a.X_1,
				stop_X = a.X_2,
				start_Y = a.Y_1,
				stop_Y = a.Y_2,
				// plz no bully for potato names
				fronk = start_X > stop_X ? -1 : 1,
				frenk = start_Y > stop_Y ? -1 : 1,
				wut = 0; 
			do
			{
				(*Matrix)[start_Y][start_X]++;
				if (start_X != stop_X)
					start_X += fronk;
				if (start_Y != stop_Y)
					start_Y += frenk;
				if (start_X == stop_X && start_Y == stop_Y)
					wut++;
			} while (wut < 2);
		}
	}
	PrintMatrix(Matrix, max_X, max_Y, printmatrix);
}

void PrintRawData(std::vector<Line>* RawData, bool yuprintdis)
{
	if (yuprintdis)
	{
		std::cout << "Imported raw data:\r\n";
		for (auto& a : *RawData)
		{
			std::cout << a.X_1 << "," << a.Y_1 << " -> " << a.X_2 << "," << a.Y_2 << std::endl;
		}
	}
}

int main()
{
	std::cout << "Day 5" << std::endl;

	std::string fileName = "data.txt";

	int max_X = 0, max_Y = 0;
	std::vector<Line> RawData = LoadData(fileName, &max_X, &max_Y);

	PrintRawData(&RawData, fileName[0] == 'd' ? false : true);

	std::cout << "Grid size: " << max_X << " x " << max_Y << " [" << RawData.size() << "]" << std::endl;

	auto Matrix = PartOne(&RawData, max_X, max_Y, fileName[0] == 'd' ? false : true);
	PartTwo(&RawData, &Matrix, max_X, max_Y, fileName[0] == 'd' ? false : true);
}