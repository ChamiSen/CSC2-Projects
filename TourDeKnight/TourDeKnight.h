/** ***************************************************************************
* @file
*
* @brief contains protoypes needed for knights tour program
******************************************************************************/



#include <iostream>
#include <iomanip>
#include <fstream>



using namespace std;


// prototype required for the program to run
void printMenu(int& boardSize, int& startX, int& startY);
bool recurKT(int startX, int startY, int moveCount, int boardSize, int** grid, int argc, ostream& fout);
bool validSquare(int nextX, int nextY, int boardSize, int**& grid);
void printBoard(int** grid, int boardSize, ostream& out);
int** allocate2d(int** chessBoard, int boardSize);
void deAllocate2d(int** grid, int boardSize);
void readFile(ifstream& fin, int moveCount, int& boardSize, int& startX, int& startY, int** grid, int** chessBoard, int argc, ofstream& fout);
void menuItems(int& boardSize, int& startX, int& startY);