#include <tuple>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct LeBoard
{
private:

	int c = 0;
	int* pointer = nullptr;
	std::tuple <int, int*> R1;
	std::tuple <int, int*> R2;
	std::tuple <int, int*> R3;
	std::tuple <int, int*> R4;
	std::tuple <int, int*> R5;
	bool izWin = false;

	LeBoard()
	{
		pointer = (int*)malloc(5 * 5 * 4);
		R1 = std::make_tuple(0, pointer);
		R2 = std::make_tuple(0, pointer + 5);
		R3 = std::make_tuple(0, pointer + 5 * 2);
		R4 = std::make_tuple(0, pointer + 5 * 3);
		R5 = std::make_tuple(0, pointer + 5 * 4);
	}

public:

	int* GetThis()
	{
		return pointer;
	}

	LeBoard(int* n) : LeBoard()
	{
		//LeBoard();
		memcpy(pointer, n, 5 * 5 * 4);
	}

	~LeBoard()
	{
		free(pointer);
	}

	void prnt()
	{
		for (auto& R : { R1, R2, R3, R4,R5 })
		{
			for (int i = 0; i < 5; i++)
			{
				std::cout << std::get<1>(R)[i] << " ";
			}
			std::cout << std::endl;
		}
	}

	int SumRemaining()
	{
		int r = 0;
		for (auto& R : { &R1, &R2, &R3, &R4, &R5 })
			for (int i = 0; i < 5; i++)
				r += (std::get<1>(*R)[i] > -1 ? std::get<1>(*R)[i] : 0);
		izWin = true;
		return r;
	}

	int CheckWinner(int n)
	{
		if (izWin)
			return -1;
		// rows
		for (auto& R : { &R1, &R2, &R3, &R4, &R5 })
		{
			for (int i = 0; i < 5; i++)
			{
				if (std::get<1>(*R)[i] == n)
				{
					std::get<1>(*R)[i] = -1; // overwrite derp
					std::get<0>(*R)++;
					if (std::get<0>(*R) == 5)
						return SumRemaining();
				}
			}
		}

		// cols n in cell is -1 due to rows check
		for (int col = 0; col < 5; col++)
		{
			int colSums = 0;
			for (auto& R : { &R1, &R2, &R3, &R4, &R5 })
			{
				if (std::get<1>(*R)[col] == -1)
				{
					colSums++;
				}
			}
			if (colSums == 5)
				return SumRemaining();
		}

		return 0;
	}
};

struct LeBingo
{
	std::vector <unsigned int> Draws;
	std::vector <LeBoard*> Boards;

private:
	void GetTheWinner(bool isLastinner)
	{
		int lastOne = 0, lastDraw = 0, lastWin = 0;
		auto totBoards = (*this).Boards.size();

		if (totBoards > 0)
		{
			/* make a copy cuz potato code change n to -1*/
			std::vector <LeBoard*> tmpBoards;
			for (auto b : (*this).Boards)
			{
				tmpBoards.push_back(new LeBoard(b->GetThis()));
			}

			for (int draw : (*this).Draws)
			{
				for (int i = 0; i < totBoards; i++)
				{
					int iHazWin = tmpBoards[i]->CheckWinner(draw);
					//std::cout << (iHazWin > 0 ? (std::string("winner [").append(std::to_string(i + 1)).append("]")) : "losinner") << std::endl;
					if (iHazWin > 0)
					{
						if (!isLastinner)
						{
							std::cout << "winner [" << i + 1 << "] " << iHazWin << " * " << draw << " = " << iHazWin * draw << std::endl;
							tmpBoards[i]->prnt();
							(*this).Boards[i]->prnt();
							return;
						}
						else
						{
							lastOne = i;
							lastDraw = draw;
							lastWin = iHazWin;
						}
					}
				}
			}
			std::cout << "last winner [" << lastOne + 1 << "] " << lastWin << " * " << lastDraw << " = " << lastWin * lastDraw << std::endl;
			tmpBoards[lastOne]->prnt();
			(*this).Boards[lastOne]->prnt();
		}
		else
		{
			std::cout << "Theres no boards." << std::endl;
		}
	}

public:
	void GetTheWinner()
	{
		GetTheWinner(false);
	}

	void GetTheLastinner()
	{
		GetTheWinner(true);
	}

	void PrintDraws()
	{
		std::cout << "Draws:" << std::endl;
		for (int draw : (*this).Draws)
		{
			std::cout << draw << ",";
		}
		std::cout << "\b \r\n\r\n";
	}

	void PrintBoards()
	{
		if ((*this).Boards.size() > 0)
		{
			for (auto board : (*this).Boards)
			{
				board->prnt();
				std::cout << std::endl;
			}
		}
		else
		{
			std::cout << "Theres no boards." << std::endl;
		}
	}
};

LeBingo LoadData(std::string leFileName)
{
	LeBingo leBingo;
	std::ifstream leDataFile(leFileName);
	if (leDataFile.is_open())
	{
		std::string line;
		std::streampos a, p;

		while (std::getline(leDataFile, line, ','))
		{
			leBingo.Draws.push_back(std::stoi(line));
			p = leDataFile.tellg();
			if (p != -1)
				a = p;
		}

		leDataFile.clear();
		leDataFile.seekg(a, std::ios::beg);

		int ii = 0;
		int aigooo[5 * 5] = {};

		while (!leDataFile.eof())
		{
			while (std::getline(leDataFile, line))
			{
				if (line.length() > 4)
				{
					int temp_int;
					std::string temp_str;
					std::stringstream str_strm(line);
					while (!str_strm.eof())
					{
						str_strm >> temp_str; //take words into temp_str one by one
						if (std::stringstream(temp_str) >> temp_int)
						{
							aigooo[ii++] = temp_int;
						}
					}
					if (ii == 25)
					{
						ii = 0;
						leBingo.Boards.push_back(new LeBoard(aigooo));
					}
				}
			}
		}
		leBingo.PrintDraws();
		//leBingo.PrintBoards();
		leBingo.GetTheWinner();
		leBingo.GetTheLastinner();
		std::cout << leBingo.Boards.size() << std::endl;
	}
	else
	{
		std::cout << "Le erròr has appéned with le data file [" << leFileName << "]." << std::endl;
	}
	return LeBingo();
}


int main()
{
	//LoadData("example.txt");
	LoadData("data.txt");
}