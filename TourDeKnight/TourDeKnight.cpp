/** ***************************************************************************
* @file TourDeKnight.cpp
*
* @brief contains main function and handles file opening and closing
******************************************************************************/

/** **************************************************************************
 * @mainpage Program 3 - Knight's Tour
 *
 * @section course_section Course Information
 *
 * @authors Chami Senarath
 *
 * @par Professor:
 *         Professor Roger Schrader
 *
 * @par Course:
 *         CSC215 - M003 - Computer Science 2
 *
 * @par Location:
 *         McLaury - 306
 *
 * @date Due April 30, 2021
 *
 * @section program_section Program Information
 *
 * @details
 * In essence, this program is about a sequence of moves of a knight on a
 * chessboad such that visits every square onc and only once. Given the size
 * of the board and a starting position we to show the path the knight
 * would move to complete its tour.  Its starting spot would be labeled with a
 * 1 and the next move would be labeled as 2 and so on.  If the n was equal to
 * 8, the final step would be 64 (8x8).
 *
 * There are two ways how this program can be started.
 * Option 1:
 *          This will present a menu to the user. We show the board size and
 * default coordinates of where the knight will start.  The default board size
 * is 8x8 and the default starting position is in row 7 column 7.  As the user
 * make changes, the menu updates.  When the user selects option 3, the tour
 * starts with the selected values and show the solution to the screen. (If a
 * solution exists). Error checking is done such that, when the board size is
 * changed to 5 while starting position is 7,7 in not allowed. Also, cannot
 * change the starting location to 9,7 on an 8x8 board.
 *
 * Option 2:
 *          When an input file is given at the command prompt, it will contain
 * tours in the following format. We are not guaranteed that a tour will be in
 * the file (empty) but we are guaranteed that if one exists, it is valid.
 * There are many tours inside this file and we process every tour.  The first
 * number in the file is the size of the board (n). The next two numbers are
 * the starting row and starting column respectively. This pattern repeats until
 * the end of file is reached. We output the solution to an output file called
 * "Solutions.tours". The formatting in the output file is done in the following
 * way
   @verbatim
   Tour # 1
           5x5 starting at (0 , 0)
            1   20  17  12  3
           16   11   2   7 18
           21   24  19   4 13
           10   15   6  23  8
           25   22   9  14  5
   @endverbatim
 *
 * If no solution is found, it is recorded as follows:
   @verbatim
   Tour # 6
           4x4 starting at (0 , 0)

           No solution for this case.
   @endverbatim
 *
 * Other than prog3.cpp, this program 4 other files. They are prog3.h,
 * prints.cpp, TourDeKnight.cpp, and allocDealloc.cpp. Usage of each file can
 * be found in its own documentation.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None - a straight compile and link with no external libraries.
 *
 * @par Usage: For option 2 of this program, the following usage has to be used
   @verbatim
   c:\> prog3.exe knights.pz
            knights.pz - contains information on size of the board (n) and two
                         numbers for starting row and starting column
                         respectively
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug
 *
 * @todo Verifying input file contains numbers only
 *
 * @par Modifications and Development Timeline:
 * <a href="https://gitlab.mcs.sdsmt.edu/7319139/csc215s21programs/-/commits/master" target=_blank>
 * Gitlab Commit Log</a>
 *
 *****************************************************************************/
#include "TourDeKnight.h"



 /** ***************************************************************************
  * @author Chami Senarath
  *
  * @par Description:
  * This is the starting point to the program. It will open files that are given
  * by command line arguments. Checks if the files are opened properly or not.
  * Once the files have been used, this function safely closes all opened files
  * and exit the program. It also checks for which option to run.
  *
  * @param[in] argc - hold a number that represents how many arguments need to
  *                   passed in to execute the program.
  * @param[in] argv - contains the program path and files (both binary and text)
  *                   necessary to run the program
  *
  * @returns 0 No fatal errors enounted. Program ends.
  *
  *****************************************************************************/
int main(int argc, char** argv)
{
    int boardSize = 8;
    int moveCount = 1;
    int startX = 7;
    int startY = 7;
    ifstream fin;
    ofstream fout;
    int** chessBoard = nullptr;
    int** grid = nullptr;


    if (argc > 2 && argc < 1)
    {
        cout << "Usage: m0020.exe inputfile outputfile" << endl;
        return 0;
    }


    if (argc == 1)
    {
        printMenu(boardSize, startX, startY);

        grid = allocate2d(chessBoard, boardSize);
        //initializing starting point
        grid[startX][startY] = 1;

        if (recurKT(startX, startY, moveCount, boardSize, grid, argc, cout) == false)
            cout << "No solution for this case." << endl;

        deAllocate2d(grid, boardSize);
    }


    if (argc == 2)
    {
        fin.open("knights.pz");
        if (!fin.is_open())
        {
            fin.close();
            cout << "Unable to open input file: " << argv[1] << endl;
            return 0;
        }

        readFile(fin, moveCount, boardSize, startX, startY, grid, chessBoard, argc, fout);
        fin.close();
    }

    return 0;
}



/** ***************************************************************************
 * @author Chami Senarath
 *
 * @par Description:
 * When option 2 is run, this function will read in the content from nights.pz
 * file and will output solutions (formatted) to a file called Solutions.tours.
 *
 * @param[in] fin        - argument to read in the input file
 * @param[in] moveCount  - keep tracks of how many steps are taken
 * @param[in] boardSize  - a number to provide the size of a side of a board
 * @param[in] startX     - provides the starting position for row
 * @param[in] startY     - provides the starting position for column
 * @param[in] grid       - contains the 2d array
 * @param[in] chessBoard - a double pointer to create a "chess board"
 * @param[in] argc       - argument to determine if the recursion is done for
 *                         menu option or input file option
 * @param[in] fout       - argument for prinitng into an output file
 *
 *****************************************************************************/
void readFile(ifstream& fin, int moveCount, int& boardSize, int& startX, int& startY, int** grid, int** chessBoard, int argc, ofstream& fout)
{
    int count = 1;

    fout.open("Solution.tours");
    while (fin >> boardSize && fin >> startX && fin >> startY)
    {
        fout << "Tour # " << count++ << endl;
        fout << setw(9) << boardSize << "x" << boardSize << " starting at (" << startX << ", " << startY << ")" << endl;

        grid = allocate2d(chessBoard, boardSize);

        grid[startX][startY] = 1;
        if (recurKT(startX, startY, moveCount, boardSize, grid, argc, fout) == true)
        {
            fout << endl;
        }
        else
        {
            fout << "No Solution for this case." << endl << endl;
        }

        deAllocate2d(grid, boardSize);
    }
    fout.close();
}



/** ***************************************************************************
 * @author Chami Senarath
 *
 * @par Description:
 * This function is written to print the menu for the knight's tour game
 *
 * @param[in] boardSize - a number to provide the size of a side of a
 *                        board
 * @param[in] startX    - provides the starting position for row
 * @param[in] startY    - provides the starting position for column
 *
 *****************************************************************************/
void printMenu(int& boardSize, int& startX, int& startY)
{
    char choice;
    int newBoardSize = boardSize;
    int newStartX = startX;
    int newStartY = startY;
    int c = 4;


    do
    {
        menuItems(boardSize, startX, startY);
        cin >> choice;

        if (!isdigit(choice))
        {
            cout << "Please enter a valid number. (Valid numbers are 1, 2, and 3)." << endl << endl;
            c = 4;
            continue;
        }

        c = choice - '0';

        if (c >= 4)
        {
            cout << "Please enter a valid number. (Valid numbers are 1, 2, and 3)." << endl << endl;
            menuItems(boardSize, startX, startY);
            cin >> choice;
        }

        switch (c)
        {
        case 1:
            cout << "Enter the size of the NxN Board (>3): ";
            cin >> newBoardSize;
            if (newBoardSize <= 3)
                cout << "Your board size is not an acceptable size. Please enter a number greater than 3." << endl << endl;
            else if (startX >= newBoardSize && startY >= newBoardSize)
                cout << "Your starting position is not valid." << endl << endl;
            else
            {
                boardSize = newBoardSize;
                cout << endl;
            }
            break;

        case 2:
            cout << "Enter Starting Coordinated [row, col]: ";
            cin >> newStartX;
            cin >> newStartY;
            if (newStartX >= boardSize && newStartY >= boardSize)
            {
                cout << "Not a valid starting location. Please try again." << "\n";
                newStartX = startX;
                newStartY = startY;
            }
            startX = newStartX;
            startY = newStartY;
            cout << endl;
            break;
        }
    } while (c != 3);
}



/** ***************************************************************************
 * @author Chami Senarath
 *
 * @par Description:
 * This function is written to provide items in the menu
 *
 * @param[in] boardSize - a number to provide the size of a side of a
 *                        board
 * @param[in] startX    - provides the starting position for row
 * @param[in] startY    - provides the starting position for column
 *
 *****************************************************************************/
void menuItems(int& boardSize, int& startX, int& startY)
{
    cout << "\t" << "1) Change Board Size from " << boardSize << "x" << boardSize << "\n";
    cout << "\t" << "2) Change starting location from [" << startX << ", " << startY << "]" << "\n";
    cout << "\t" << "3) Exit and Solve Tour" << "\n";
    cout << "Enter Choice: ";
}


/** ***************************************************************************
 * @author Chami Senarath
 *
 * @par Description:
 * This function is written to dynamically allocate a 2 dimentional array when
 * a board size is given
 *
 * @param[in, out] chessBoard - a double pointer to create a "chess board"
 * @param[in] boardSize       - a number to provide the size of a side of a
 *                              board
 *
 * @return a double pointer to an 2 dimentional array
 *
 *****************************************************************************/
int** allocate2d(int** chessBoard, int boardSize)
{
    int i, j;
    chessBoard = new int* [boardSize];

    for (i = 0; i < boardSize; i++)
    {
        chessBoard[i] = new int[boardSize];
        if (chessBoard[i] == nullptr)
        {
            cout << "Unable to allocate columns." << endl;
            return 0;
        }
    }


    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
        {
            chessBoard[i][j] = -1;
        }
    }

    return chessBoard;
}



/** ***************************************************************************
 * @author Chami Senarath
 *
 * @par Description:
 * This function is written deallocate memory that was dynamically allocated
 *
 * @param[in] grid      - the grid to be deallocated
 * @param[in] boardSize - a number to provide the size of a side of a board
 *
 *****************************************************************************/
void deAllocate2d(int** grid, int boardSize)
{
    int j;

    for (j = 0; j < boardSize; j++)
        delete[] grid[j];
    delete[] grid;
}


/** ***************************************************************************
 * @author Chami Senarath
 *
 * @par Description:
 * This function is written to print the solved board with steps
 *
 * @param[in] grid      - contains the 2d array with move numbers
 * @param[in] boardSize - provides the size of a side of a
 *                        board
 * @param[in] out       - provides outputting to either the console or output
 *                        file
 *
 *****************************************************************************/
void printBoard(int** grid, int boardSize, ostream& out)
{
    int i, j;

    out << endl;
    out << "\t";
    for (i = 0; i < boardSize; i++)
    {
        for (j = 0; j < boardSize; j++)
            out << setw(4) << grid[i][j];
        out << endl;
        out << "\t";
    }
}



/** ***************************************************************************
 * @author Chami Senarath
 *
 * @par Description:
 * This function is written to solve the knight's tour by recursion
 *
 * @param[in] startX    - provides the starting position for row
 * @param[in] startY    - provides the starting position for column
 * @param[in] boardSize - a number to provide the size of a side of a
 *                        board
 * @param[in] moveCount - keep tracks of how many steps are taken
 * @param[in] grid      - contains the 2d array
 * @param[in] argc      - argument to determine if the recursion is done for
 *                        menu option or input file option
 * @param[in] fout      - argument for prinitng into an output file
 *
 * @return true if there is a solution, false otherwise
 *
 *****************************************************************************/
bool recurKT(int startX, int startY, int moveCount, int boardSize, int** grid, int argc, ostream& fout)
{
    int k;
    int nextX, nextY;
    int moveX[8] = { -2, -2, 2,  2, -1, -1, 1,  1 };
    int moveY[8] = { 1, -1, 1, -1,  2, -2, 2, -2 };


    if (moveCount == boardSize * boardSize)
    {
        if (argc == 1)
        {
            cout << "Tour # 1" << endl;
            cout << setw(9) << boardSize << "x" << boardSize << " starting at (" << startX << ", " << startY << ")" << endl;
            printBoard(grid, boardSize, cout);
        }
        else if (argc == 2)
            printBoard(grid, boardSize, fout);
        return true;
    }

    for (k = 0; k < 8; k++)
    {
        nextX = startX + moveX[k];
        nextY = startY + moveY[k];
        if (validSquare(nextX, nextY, boardSize, grid) == true)
        {
            grid[nextX][nextY] = moveCount + 1;
            if (recurKT(nextX, nextY, moveCount + 1, boardSize, grid, argc, fout) == true)
                return true;
            grid[nextX][nextY] = -1;
        }
    }

    return false;
}



/** ***************************************************************************
 * @author Chami Senarath
 *
 * @par Description:
 * This function is written to check if a square in the 2d array has already
 * been occupied or not
 *
 * @param[in] nextX     - provides the row position to validate
 * @param[in] nextY     - provides the column position to validate
 * @param[in] boardSize - a number to provide the size of a side of a board
 * @param[in] grid      - contains the 2d array
 *
 * @return true if there is a solution, false otherwise
 *
 *****************************************************************************/
bool validSquare(int nextX, int nextY, int boardSize, int**& grid)
{
    return (nextX >= 0 && nextX < boardSize&& nextY >= 0 && nextY < boardSize&& grid[nextX][nextY] == -1);
}