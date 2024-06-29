#pragma once
#include <iomanip>
#include <cstdlib>
#include <string>
#include "Robot.h"

using namespace std;

class Robot;

struct Node
{
    Robot *r;
    Node *next;
};

class Battlefield // Battlefield handle display board and terminal
{
private:
    char **board;
    int rows;
    int cols;
    bool fast;
    ofstream *outfile;

public:
    Battlefield(int rows, int cols, ofstream *outfile);

    void INIT();

    void clearScreen();

    void displayPlayer(Node *Rptr);

    void displayTurn(int turn, Node *Rptr);

    void displayBoard();

    void displayOutput();

    void placeRobot(Node *Rptr);

    void Input();

    ~Battlefield();
};