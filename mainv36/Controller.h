#pragma once
#include <sstream>
#include <memory>
#include <stdexcept>
#include "Queue.h"
#include "LinkedList.h"
#include "RoboCop.h"
#include "Terminator.h"
#include "TerminatorRoboCop.h"
#include "BlueThunder.h"
#include "Madbot.h"
#include "RoboTank.h"
#include "UltimateRobot.h"
#include "Joker.h"

class Controller // Controller Handle the Logic of Robot War
{
private:
    shared_ptr<LinkedList> l;
    shared_ptr<Queue> q;
    shared_ptr<Battlefield> b;
    Node *Rptr;
    int rows;
    int cols;
    int nums;
    int steps;
    int turn;
    ofstream *outfile;

public:
    Controller(string inputFile, string outputFile);

    ~Controller();

    void resetRobot();

    void connectRobot();

    bool validTarget(int kX, int kY);

    bool validPos(int posX, int posY);

    void checkKill();

    void checkLook();

    void checkUpgrade();

    void randomPos();

    void returnRobot();

    void run();

    int getROWS() const;

    int getCOLS() const;

    ofstream *getOutput() const;

    string trimLeft(string s);

    string trimRight(string s);

    string trim(string s);
};
