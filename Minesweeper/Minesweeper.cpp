#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

// Struct for a tile on the board
struct Tile {
    // Indicates whether the tile is a mine
    bool isMine = false;
    // Indicates whether the tile has been revealed
    bool isRevealed = false;
    // Indicates whether the tile has been flagged by the player
    bool isFlagged = false;
    // The number of mines surrounding the tile
    int surroundingMines = 0;
};

// 2D vector to represent the board
vector<vector<Tile>> board;

// Constants for the size of the board and the number of mines
int Rows;
int Columns;
int Mines;
int minesLeft;


// Initializes the board with a set number of mines randomly placed on the board
void initializeBoard() {
    random_device rd;
    default_random_engine rng(rd());
    uniform_int_distribution<int> dist(0, Rows * Columns - 1);

    // Place the mines randomly on the board
    for (int i = 0; i < Mines; i++) {
        int pos = dist(rng);
        int row = pos / Columns;
        int col = pos % Columns;
        board[row][col].isMine = true;
    }
}
// Prints the board to the console
void printBoard() {
    // Print the column numbers
    cout << "  ";
    for (int i = 0; i < Columns; i++) {
        cout << i << " ";
    }
    cout << endl;

    // Print each row of the board
    for (int i = 0; i < Rows; i++) {
        // Print the row number
        cout << i << " ";
        // Print each column of the row
        for (int j = 0; j < Columns; j++) {
            // If the tile is flagged, print an "F"
            if (board[i][j].isFlagged) {
                cout << "F ";
            }
            // If the tile is not revealed, print a "*"
            else if (!board[i][j].isRevealed) {
                cout << "* ";
            }
            // If the tile is revealed, print the number of surrounding mines
            else {
                if (board[i][j].surroundingMines == 0)
                {
                    cout << " " << " ";
                }
                else
                    cout << board[i][j].surroundingMines << " ";
            }
        }
        cout << endl;
    }
}

// Reveals a tile and all adjacent tiles if the tile has no surrounding mines
void reveal(int row, int col) {
    // Return if the tile is out of bounds or has already been revealed or flagged
    if (row < 0 || row >= Rows || col < 0 || col >= Columns || board[row][col].isRevealed || board[row][col].isFlagged) {
        return;
    }

    // Reveal the tile
    board[row][col].isRevealed = true;

    // If the tile is a mine, end the game
    if (board[row][col].isMine) {
        cout << "You lost!" << endl;
        exit(0);
    }

    // If the tile has no surrounding mines, reveal all adjacent tiles
    if (board[row][col].surroundingMines == 0) {
        reveal(row - 1, col - 1);
        reveal(row - 1, col);
        reveal(row - 1, col + 1);
        reveal(row, col - 1);
        reveal(row, col + 1);
        reveal(row + 1, col - 1);
        reveal(row + 1, col);
        reveal(row + 1, col + 1);
    }
}

// Flags or unflags a tile
void flag(int row, int col) {
    // Return if the tile is out of bounds or has already been revealed
    if (row < 0 || row >= Rows || col < 0 || col >= Columns || board[row][col].isRevealed) {
        return;
    }

    // Toggle the flag on the tile
    board[row][col].isFlagged = !board[row][col].isFlagged;

    // Display the number of mines left
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            if (board[i][j].isFlagged) {
                minesLeft--;
            }
        }
    }
}

// Counts the number of mines surrounding each tile on the board
void countSurroundingMines() {
    // Iterate through each tile on the board
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            // If the tile is a mine, skip it
            if (board[i][j].isMine) {
                continue;
            }

            // Count the number of mines surrounding the tile
            int count = 0;
            if (i > 0 && j > 0 && board[i - 1][j - 1].isMine) { count++; }
            if (i > 0 && board[i - 1][j].isMine) { count++; }
            if (i > 0 && j < Columns - 1 && board[i - 1][j + 1].isMine) { count++; }
            if (j > 0 && board[i][j - 1].isMine) { count++; }
            if (j < Columns - 1 && board[i][j + 1].isMine) { count++; }
            if (i < Rows - 1 && j > 0 && board[i + 1][j - 1].isMine) { count++; }
            if (i < Rows - 1 && board[i + 1][j].isMine) { count++; }
            if (i < Rows - 1 && j < Columns - 1 && board[i + 1][j + 1].isMine) { count++; }

            // Set the number of surrounding mines for the tile
            board[i][j].surroundingMines = count;
        }
    }
}

// Returns true if all tiles that are not mines have been revealed
bool checkWin() {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            if (!board[i][j].isMine && !board[i][j].isRevealed) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    do {

    } while (true);

    // Display the main menu and prompt the player to choose the difficulty level
    cout << "Welcome to Minesweeper!" << endl;
    cout << "Choose the difficulty level:" << endl;
    cout << "1) Easy (8x8 board with 10 mines)" << endl;
    cout << "2) Medium (16x16 board with 40 mines)" << endl;
    cout << "3) Hard (30x16 board with 99 mines)" << endl;
    cout << "4) Create custom game" << endl;
    cout << "Enter the number of your choice: ";
    int choice;
    cin >> choice;

    // Set the size of the board and number of mines based on the chosen difficulty level
    if (choice == 1) {
        Rows = 8;
        Columns = 8;
        Mines = 10;
    }
    else if (choice == 2) {
        Rows = 16;
        Columns = 16;
        Mines = 40;
    }
    else if (choice == 3) {
        Rows = 30;
        Columns = 16;
        Mines = 99;
    }
    else if (choice == 4) {
        cout << "Enter the number of rows: ";
        cin >> Rows;
        cout << "Enter the number of columns: ";
        cin >> Columns;
        cout << "Enter the number of mines: ";
        cin >> Mines;
    }
    minesLeft = Mines;

    // Initialize the board and count the number of mines surrounding each tile
    board.resize(Rows, vector<Tile>(Columns));
    initializeBoard();
    countSurroundingMines();

    // Loop until the player loses or wins the game
    while (true) {
        system("cls");

        cout << "Mines left: " << minesLeft << endl;
        // Print the board
        printBoard();

        // Prompt the player for their move
        cout << "Enter row, column and action (r/f): ";
        int row, col;
        char action;
        cin >> row >> col >> action;

        // Reveal or flag the specified tile
        if (action == 'r') {
            reveal(row, col);
        }
        else if (action == 'f') {
            flag(row, col);
        }

        // If the player has won, end the game
        if (checkWin()) {
            cout << "You won!" << endl;
            exit(0);
        }
    }

    return 0;
}