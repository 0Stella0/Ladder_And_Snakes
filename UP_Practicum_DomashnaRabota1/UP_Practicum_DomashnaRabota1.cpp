#include <iostream>
#include <cstdlib>
#include <ctime>
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

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

void printBoard(int n, char** board,char symbols[], int players,int** snakes, int** ladders,int s, int l) {
    for (int rows = 0; rows < n; rows++) {
        for (int columns = 0; columns < n; columns++) {
            int position = rows*n + columns;
            if (rows == 0 && columns == 0) {
                for (int i = 0; i < players; i++) {
                    cout << symbols[i];
                }
                cout << " ";
            }
            if (l > 0) {
                for (int i = 0; i < l; i++) {
                    if ((ladders[i][0] - 1) == position) {
                        cout << "L";
                        break;
                    }
                    if (i == l - 1) {    //ako ne e namerena stulba na poslednoto zavurtane
                        for (int j = 0; j < s; j++) {
                            if ((snakes[j][0] - 1) == position) {
                                cout << "S";
                                break;
                            }
                            if (j == s - 1) { //same here
                                cout << board[rows][columns] << " ";
                            }
                        }
                    }
                }
            }
            else {
                for (int i = 0; i < s; i++) {
                    if ((snakes[i][0] - 1) == position) {
                        cout << "S ";
                        break;
                    }
                    if (i == s - 1) {
                        cout << board[rows][columns] << " ";
                    }
                }
            }
        }
        cout << endl;
    }
}

void boardMovement(int n, char** board, char symbols[], int players, int** snakes, int** ladders, int s, int l) {

}

void laddersInput( int a, int** arr,int n) {
    int board_size = (n * n) - 1;
    if (a > 0) {
        for (int i = 0; i < a; i++) {
           arr[i] = new int[2];
              while (true) {
                  cout << "Enter the start and end cell of ladder" << i + 1 << ": ";
                  cin >> arr[i][0];
                  cin >> arr[i][1];
                    if (arr[i][0] < 1 || arr[i][0] > board_size || arr[i][1] < 1 || arr[i][1] > board_size) {
                         cerr << "Can't be bigger than the size of the board. Enter again: " << endl;
                     }
                    else if (arr[i][0] > arr[i][1]) {
                        cerr << "The starting point must me less than the ending point. Enter again: " << endl;
                    }
                    else {
                        break;
                    }
              }
        }
    }
}

void snakesInput(int a, int** arr, int n) {
    int board_size = (n * n) - 1;
    if (a > 0) {
        for (int i = 0; i < a; i++) {
            arr[i] = new int[2];
            while (true) {
                cout << "Enter the start and end cell of snake" << i + 1 << ": ";
                cin >> arr[i][0];
                cin >> arr[i][1];
                if (arr[i][0] < 1 || arr[i][0] > board_size || arr[i][1] < 1 || arr[i][1] > board_size) {
                    cerr << "Can't be bigger than the size of the board. Enter again: " << endl;
                }
                else if (arr[i][0] < arr[i][1]) {
                    cerr << "The starting point must me less than the ending point. Enter again: " << endl;
                }
                else {
                    break;
                }
            }
        }
    }
}

int rollDice() {
    return rand() % 6 + 1;
}

int main() {
    int n;
    cout << "Enter the size of the board (NxN): ";
    cin >> n;
    if ((!(n%5==0)) || n > 15) {
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
    for (int i = 0; i < players; i++) {
        cin >> symbols[i];
    }


    if (inputValidation(players,symbols) == false) {
        cerr << "The symbols need to be unique." << endl;
        return -1;
    }

   
    char** board = new char*[n];
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
    snakesInput(snakes, snakes_coordinates,n);


    srand(time(0));
    cout << "Rolling dice:";
    for (int i = 0; i < players; i++) {
        int roll = rollDice();
        cout <<"Player " << symbols[i] <<" rolled: "<< roll << "\n";
    }

    printBoard(n, board, symbols, players, snakes_coordinates, ladders_coordinates, snakes, ladders);

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