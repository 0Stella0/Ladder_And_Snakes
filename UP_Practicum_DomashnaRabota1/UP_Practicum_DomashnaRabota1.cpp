//TRUST
#include <iostream>
#include <cstdlib>
#include <ctime>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int rollDice() {
    return rand() % 6 + 1;
}

bool inputValidation(int players, char symbols[]) {
    int flag = true;
    for (int i = 0; i < players; i++) {
        for (int j = i + 1; j < players; j++) {
            if (symbols[i] == symbols[j]) {
                flag = false;
            }
        }
    }
    return flag;
}

void printBoard(int n, char** board, char symbols[], int players, int** snakes, int** ladders, int s, int l) {
    for (int rows = 0; rows < n; rows++) {
        for (int columns = 0; columns < n; columns++) {
            int position = rows * n + columns;
            bool printed = false;

            for (int i = 0; i < l; i++) {
                if ((ladders[i][0] - 1) == position) {
                    cout << "L ";
                    printed = true;
                    break;
                }
            }
            if (!printed) {
                for (int i = 0; i < s; i++) {
                    if ((snakes[i][0] - 1) == position) {
                        cout << "S ";
                        printed = true;
                        break;
                    }
                }
            }
            if (!printed) {
                for (int i = 0; i < players; i++) {
                    if (board[rows][columns] == symbols[i]) {
                        cout << symbols[i] << " ";
                        printed = true;
                        break;
                    }
                }
            }
            if (!printed) {
                cout << "- ";
            }
        }
        cout << endl;
    }
}

void boardMovement(int n, char** board, char symbols[], int players, int** snakes, int** ladders, int s, int l) {
    bool end = false;
    int playersPosition[4] = { 0 };

    while (!end) {
        for (int i = 0; i < players; i++) {
            int roll = rollDice();
            cout << "Player " << symbols[i] << " rolled: " << roll << "\n";

            int position_after_roll = playersPosition[i] + roll;
            if (position_after_roll > n * n - 1)
                continue;
           
            for (int j = 0; j < players; j++) {
                while (position_after_roll == playersPosition[j] && j != i) {
                    roll = rollDice();
                    position_after_roll = playersPosition[i] + roll;
                }
            }
           
            for (int j = 0; j < l; j++) {
                if ((ladders[j][0] - 1) == position_after_roll) {
                    cout << "The player encounter a ladder! " << endl;
                    position_after_roll = ladders[j][1] - 1;
                    break;
                }
            }

            for (int j = 0; j < s; j++) {
                if ((snakes[j][0] - 1) == position_after_roll) {
                    cout << "The player encounter a snake! " << endl;
                    position_after_roll = snakes[j][1] - 1;
                    break;
                }
            }
            int changed_row = position_after_roll / n;
            int changed_column = position_after_roll % n;
            board[changed_row][changed_column] = symbols[i];
            board[playersPosition[i] / n][playersPosition[i] % n] = '-';
            playersPosition[i] = position_after_roll;
            printBoard(n, board, symbols, players, snakes, ladders, s, l);
            
            if (position_after_roll == (n * n - 1)) {
                cout << " ~~ " << symbols[i] << " has won the game! gj ~~" << endl;
                board[n - 1][n - 1] = symbols[i];
                end = true;
                break;
            }
        }
    }
}

bool edgeCaseSnakeLaddersEndless(int s, int** snakes, int l, int** ladders) {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < l; j++) {
            if (snakes[i][0] == ladders[i][0]){
                return false;
            }
            if (snakes[i][1] == ladders[j][0]) {
                return false;
            }
        }
    }
    return true;
}

void laddersInput(int l, int** ladders, int n) {
    int board_size = (n * n) - 1;
    if (l > 0) {
        for (int i = 0; i < l; i++) {
            ladders[i] = new int[2];
            while (true) {
                cout << "Enter the start and end cell of ladder" << i + 1 << ": ";
                cin >> ladders[i][0];
                cin >> ladders[i][1];
                if (ladders[i][0] < 2 || ladders[i][0] > board_size - 1 || ladders[i][1] < 2 || ladders[i][1] > board_size - 1) {
                    cerr << "Can't be bigger than the size of the board. Enter again: " << endl;
                }
                else if (ladders[i][0] > ladders[i][1]) {
                    cerr << "The starting point must me less than the ending point. Enter again: " << endl;
                }
                else {
                    break;
                }
            }
        }
    }
}

void snakesInput(int s, int** snakes, int n) {
    int board_size = (n * n) - 1;
    if (s > 0) {
        for (int i = 0; i < s; i++) {
            snakes[i] = new int[2];
            while (true) {
                cout << "Enter the start and end cell of snake" << i + 1 << ": ";
                cin >> snakes[i][0];
                cin >> snakes[i][1];
                if (snakes[i][0] < 2 || snakes[i][0] > board_size - 1 || snakes[i][1] < 2 || snakes[i][1] > board_size - 1) {
                    cerr << "Can't be bigger than the size of the board. Enter again: " << endl;
                }
                else if (snakes[i][0] < snakes[i][1]) {
                    cerr << "The starting point must me less than the ending point. Enter again: " << endl;
                }
                else {
                    break;
                }
            }
        }
    }
}

int main() {
    std::srand(time(0));
    int n;
    cout << "Enter the size of the board (NxN): ";
    cin >> n;
    if ((!(n % 5 == 0)) || n > 15) {
        cerr << "  ~The board can only be sizes 5x5/10x10/15x15." << endl;
        return 1;
    }

    int players;
    cout << "Enter the number of players: ";
    cin >> players;
    if (players < 2 || players > 4) {
        cerr << "  ~The number of players must be between 2 and 4." << endl;
        return 0;
    }

    char symbols[4];
    cout << "Enter the symbols of the players: ";

    while (true) {
        for (int i = 0; i < players; i++) {
            cin >> symbols[i];
        }
        if (inputValidation(players, symbols)) {
            break;
        }
        else {
            cerr << "The symbols need to be unique." << endl;
            cout << "Enter the symbols of the players: ";
        }
    }


    char** board = new char* [n];
    for (int rows = 0; rows < n; rows++) {
        board[rows] = new char[n];
        for (int columns = 0; columns < n; columns++) {
            board[rows][columns] = '-';
        }
    }
        
    int ladders;
    cout << "Enter the number of ladders: ";
    cin >> ladders;
    int** ladders_coordinates = new int* [ladders];
    laddersInput(ladders, ladders_coordinates, n);

    int snakes;
    cout << "Enter the number of snakes: ";
    cin >> snakes;
    int** snakes_coordinates = new int* [snakes];
    snakesInput(snakes, snakes_coordinates, n);

    if (!edgeCaseSnakeLaddersEndless(snakes, snakes_coordinates, ladders, ladders_coordinates)) {
        cerr << "The snakes and ladders cannot be the same or create endless rotations.";
        return 0;
    }

   
   /*for (int i = 0; i < players; i++) {
        board[0][0] == symbols[i];
    }*/

    printBoard(n, board, symbols, players, snakes_coordinates, ladders_coordinates, snakes, ladders);
    boardMovement(n, board, symbols, players, snakes_coordinates, ladders_coordinates, snakes, ladders);

    for (int i = 0; i < n; i++) {
        delete[] board[i];
    }
    delete[] board;

    for (int i = 0; i < ladders; i++) {
        delete[] ladders_coordinates[i];
    }
    delete[] ladders_coordinates;

    for (int i = 0; i < snakes; i++) {
        delete[] snakes_coordinates[i];
    }
    delete[] snakes_coordinates;

    return 0;
}

//Samo ne mi izkarva v nachaloto vsichki characters na [0,0]