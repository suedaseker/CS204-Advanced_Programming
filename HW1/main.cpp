#include <iostream>
#include <string>
#include <vector>
#include "randgen.h"
#include <iomanip>
using namespace std;

//this function will be used to print any matrix
void PrintMatrix(vector<vector<char>> &a)
{
	for(int j = 0; j < a.size(); j++)
	{
		for(int k = 0; k < a[0].size(); k++)
		{
			cout << setw(4) << a[j][k];
		}
		cout << endl;
	}
}

//with this 2 functions below, we obtain the option from the user and chek if it's valid
bool OptionCheck(string &option)
{
	if(option == "1" || option == "2" || option == "3"){
		return true;
	}else{
		return false;
	}
}

string GetOption()
{
	string option;
	cout << "Press:" << endl 
		 << "1. If you want to find out the surrounding of a cell" << endl
		 << "2. If you want to open the cell" << endl 
		 << "3. If you want to exit." << endl;
	cin >> option;

	//if the option is not valid, displaying an error message and getting new input
	//using the above funtion to create a loop that continues utill the option is valid
	while(OptionCheck(option) == false)
	{
		cout << "Your input is wrong. Please select one of the options: 1, 2 or 3." << endl;
		cin >> option;
	}
	return option;
}

//with this 2 functions, we obtain a coordinate from the user and check if it's in the range
bool RangeCheck(int	&row, int &col, int &x, int &y)
{
	if(x < 0 || x > row-1 || y < 0 || y > col-1){
		return false;
	}else{
		return true;
	}
}

int GetRange(int &row, int &col, int &x, int &y)
{
	cout << "Give the coordinates: ";
	cin >> x >> y;

	//using the above funtion to create a loop that continues to ask for the coordinates utill the coordinate is in the range
	while(RangeCheck(row, col, x, y) == false)
	{
		cout << "It is out of range. Please give a valid coordinates: ";
		cin >> x >> y;
	}
	return x,y;
}

int main()
{
	//taking inputs from the user for row, colmumn and bomb numbers
	int row, col, bombnum;
	cout << "Give the dimensions of the matrix: ";
	cin >> row >> col;
	cout << "How many bombs: ";
	cin >> bombnum;
	cout << endl;

	//checking if the number of bombs is valid
	//creating a loop that will continue untill a valid bomb number is entered
	while((bombnum > row*col) || (bombnum < 1))
	{
		//if the number of bombs is out of range, displaying an error message and getting new input
		if (bombnum > (row*col))
		{
			cout << "The number of bombs can not be greater than the whole number of cells minus one. "
				 << "Please give the number of bombs again: ";
			cin >> bombnum;
		}
		else if(bombnum < 1)
		{
			cout << "The number of bombs could not be less than one. Please give the number of bombs again: ";
			cin >> bombnum;
		}
	}

	//distributing bombs randomly in to the matrix as much as the given number of bombs
	vector<vector<char>> minesweeper(row, vector<char>(col, '0')); //initializing a matrix to store the locations of bombs
	int bombcounter = 0;
	RandGen rnd; //using RandGen library to get random coordinates to put the bombs 
	while(bombcounter < bombnum)
	{
		int j = rnd.RandInt(row);
		int k = rnd.RandInt(col);
		if (minesweeper[j][k] == '0') //if the coordinate hasen't been putted any bombs, we put a new bomb
		{
			minesweeper[j][k] = 'B';
			bombcounter ++;
		}
	}
	//
	PrintMatrix(minesweeper);
	cout << endl;
	//

	//calculating the number of bombs in all of the adjacent (neighboring) cells and storing them in the bombscount matrix
	vector<vector<char>> bombcounts(row, vector<char>(col, '0'));
	//chechking all the cells in minesweeper matrix one by one with 2 for loops
	for(int j = 0; j < minesweeper.size(); j++)
	{
		for(int k = 0; k < minesweeper[0].size(); k++)
		{
			//checking all the surroundings of a cell with 2 more for loops
			for(int m = j-1; m < j+2; m++)
			{
				if(m != -1 && m < row)
				{
					for(int n = k-1; n < k+2; n++)
					{
						if(n != -1 && n < col)
						{
							//if we come across to the cell we are already checking for, we avoid that cell
							if( !(m ==j && n == k))
							{
								//if there is a bomb around the cell,
								//we add the number of bombs to the cell in the new matrix bombscount
								if(minesweeper[m][n] == 'B')
								{
									bombcounts[j][k] ++; 
								}
							}
						}
					}
				}
			}
		}
	}
	//
	PrintMatrix(bombcounts);
	cout << endl;
	//

	vector<vector<char>> gameMatrix(row, vector<char>(col, 'X')); //initializing a matrix to display in the game
	string option = GetOption(); //getting a valid option from the user
	bool game = true; //creating a bool to form a loop untill the game is finished
	int gamecount = 0; //counting the opened cells without a bomb to decide wether the user opened all the cells correctly
	int wingame = (row*col) - bombnum; //the user will win the game if they open all the cells without a bomb

	while(game)
	{
		if(option == "1") //if the user chose option 1, we temporarily open a cell which the user will give the coordinates for
		{
			int x, y;
			GetRange(row, col, x, y); //getting a valid coordinate from the user to display
			cout << endl;
			cout << "Displaying the surrounding of " << "(" << x << "," << y << "):" << endl;

			vector<vector<char>> temp(row, vector<char>(col, 'X')); //initializing a temporary matrix to display
			temp = gameMatrix;
			temp[x][y] = bombcounts[x][y]; //getting the number of bombs around the cell to display

			PrintMatrix(temp);
			cout << "Around " << "(" << x << "," << y << ")" << " you have " << temp[x][y] << " bomb(s)";
			cout << endl << endl;

			option = GetOption();
		}

		else if(option == "2") //if the user chose option2, we permanently open the cell which the user will give the coordinates for
		{
			int x, y;
			GetRange(row, col, x, y); //getting a valid coordinate from the user to open
			cout << endl;
			cout << "Opening cell  " << "(" << x << "," << y << "):" << endl;

			if(minesweeper[x][y] != 'B') //if the opened cell is not a bomb, we continue the game
			{	
				gameMatrix[x][y] = bombcounts[x][y];
				PrintMatrix(gameMatrix);
				cout << endl << endl;
				gamecount++; //incrementing the gamecount since the user opened a cell successfully

				if(gamecount == wingame) //if all the cells without a bomb is opened, the user won the game
				{
					cout << "Congratulations! All the non-mined cells opened successfully" << endl
							<< "You won!" << endl << endl << ">>>>> Game Over! <<<<<" << endl;
					game = false; //game finished, so we end the loop
				}

				else //if there are still cells without a bomb that hasn't been opened, we continue the game
				{
					option = GetOption();
				}
			}

			else //if the opened cell is a bomb, the game is over, the user has lost the game
			{
				gameMatrix[x][y] = minesweeper[x][y];
				PrintMatrix(gameMatrix);
				cout << endl << endl; 
				cout << "Unfortunately, you stepped on a mine" << endl << "Arrangement of mines:" << endl;

				//to display the ending matrix with the bombs and the counts of the bombs, 
				//we'll merge minesweeper and bombcounts matrices
				for(int j = 0; j < minesweeper.size(); j++)
				{
					for(int k = 0; k < minesweeper[0].size(); k++)
					{
						if(minesweeper[j][k] == 'B')
						{
							bombcounts[j][k] = minesweeper[j][k];
						}
					}
				}
				PrintMatrix(bombcounts);
				cout << ">>>>> Game Over! <<<<<" << endl;
				game = false; //getting out of the loop because the game is over
			}
		}

		else if(option == "3") //if the user chose option 3, we terminate the game
		{
			cout << "Program exiting ..." << endl;
			game = false; //getting out of the loop because the game has ended
		}
	}

	//In order to see it on the console
	cin.get();
	cin.ignore();
	return 0;
}
