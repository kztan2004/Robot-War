#include "Controller.h"

Controller::Controller(string inputFile, string outputFile)
{
    turn = 0;
    // Joey Code
    ifstream infile(inputFile);
    outfile = new ofstream(outputFile);
    if (!infile.is_open()) // check if open successful
    {
        throw invalid_argument("File Error: file is not found");
    }

    // Controller dimension
    string line;
    getline(infile, line);
    sscanf(line.c_str(), "M by N : %d %d", &rows, &cols);

    // steps
    getline(infile, line);
    sscanf(line.c_str(), "steps : %d", &steps);

    // number of robots
    getline(infile, line);
    sscanf(line.c_str(), "robots : %d", &nums);

    if (rows < 0 || cols < 0 || steps < 0 || nums < 0) // exception handler
    {
        throw invalid_argument("Invalid value: must be non-negative");
    }

    // LinkedList and Queue
    l = make_shared<LinkedList>();
    q = make_shared<Queue>(nums);
    // Robot Pointer initialize
    Rptr = l->getNode();
    // board initialize
    b = make_shared<Battlefield>(rows, cols, outfile);

    // information for each robot
    for (int i = 0; i < nums; ++i)
    {
        getline(infile, line);
        stringstream ss(line); // initialize ss with the line
        string word;
        bool isLineParsed = false;

        while (getline(ss, word, ' ') && !isLineParsed)
        {
            word = trim(word); // trim : remove whitespace
            string robotType = word;
            string valueX, valueY;
            int x, y;
            string name;

            if (ss >> name >> valueX >> valueY)
            {
                if (isdigit(valueX[0]) && isdigit(valueY[0]))
                {
                    x = stoi(valueX);
                    y = stoi(valueY);
                }
                else
                {
                    if ((valueX == "random" || isdigit(valueX[0])) && (valueY == "random" || isdigit(valueY[0])))
                    {
                        do
                        {
                            x = (valueX == "random") ? rand() % rows : stoi(valueX);
                            y = (valueY == "random") ? rand() % cols : stoi(valueY);
                        } while (i != 0 && !validPos(x, y));
                    }
                    else
                    {
                        throw invalid_argument("Invalid Robot Value: must be non-negative or random");
                    }
                }
                if (robotType == "RoboCop")
                {
                    l->append(l->getNode(), new RoboCop(x, y, name));
                }
                else if (robotType == "Terminator")
                {
                    l->append(l->getNode(), new Terminator(x, y, name));
                }
                else if (robotType == "TerminatorRoboCop")
                {
                    l->append(l->getNode(), new TerminatorRoboCop(x, y, name));
                }
                else if (robotType == "BlueThunder")
                {
                    l->append(l->getNode(), new BlueThunder(x, y, name));
                }
                else if (robotType == "Madbot")
                {
                    l->append(l->getNode(), new Madbot(x, y, name));
                }
                else if (robotType == "RoboTank")
                {
                    l->append(l->getNode(), new RoboTank(x, y, name));
                }
                else if (robotType == "UltimateRobot")
                {
                    l->append(l->getNode(), new UltimateRobot(x, y, name));
                }
                else if (robotType == "Joker")
                {
                    l->append(l->getNode(), new Joker(x, y, name));
                }
                else // add other type of robot
                {
                    throw invalid_argument("Invalid Robot Type: Invalid");
                }
                isLineParsed = true;
            }
        }
    }
    infile.close(); // close infile
    connectRobot();
}

Controller::~Controller()
{
    l->setNode(Rptr); // set Node to clear remained Node of LinkedList
}

void Controller::resetRobot() // Initialization of a simulation
{
    Node *ptr = Rptr;
    do
    {
        ptr->r->resetTarget();
        ptr = ptr->next;
    } while (ptr != Rptr);
}

void Controller::connectRobot() // Initialization of a simulation
{
    Node *ptr = Rptr;
    do
    {
        ptr->r->setConnect(this, getOutput());
        ptr = ptr->next;
    } while (ptr != Rptr);
}

bool Controller::validTarget(int kX, int kY) // check ValidTarget
{
    if ((kX == 0 && kY == 0))
        return true;
    int fireX = Rptr->r->getX() + kX;
    int fireY = Rptr->r->getY() + kY;
    if (fireX < 0 || fireX > rows - 1 || fireY < 0 || fireY > rows - 1)
        return true;
    if (Rptr->r->checkTarget(fireX, fireY)) // check if duplicated target
        return true;
    return false;
}

bool Controller::validPos(int posX, int posY)
{
    Node *ptr = Rptr;
    do
    {
        if (posX == ptr->r->getX() && posY == ptr->r->getY())
            return false;
        ptr = ptr->next;
    } while (ptr != Rptr); // check if collide with others robots;
    return true;
}

void Controller::checkKill() // kill and looked logic in game
{
    Node *ptr = Rptr;
    while (ptr->next != Rptr)
    {
        bool kill = false;
        if (!ptr->next->r->getActive())
        {
            ptr = ptr->next;
            continue;
        }
        if (*(Rptr->r) != *(ptr->next->r)) // check kill
        {
            Rptr->r->addKill();
            cout << Rptr->r->getType() << " " << Rptr->r->getName() << " killed " << ptr->next->r->getType() << " " << ptr->next->r->getName() << endl;
            *outfile << Rptr->r->getType() << " " << Rptr->r->getName() << " killed " << ptr->next->r->getType() << " " << ptr->next->r->getName() << endl;
            checkUpgrade();
            ptr->next->r->kill();
            if (!ptr->next->r->getStatus()) // if killed robot have remained lives
            {
                q->push(ptr->next->r); // killed robot push to queue
            }
            l->pop(ptr); // removed robot from linked list
            kill = true;
        }
        if (!kill)
            ptr = ptr->next;
    }
}

void Controller::checkLook() // look and push looked Robot position into Robot
{
    Node *ptr = Rptr;
    while (ptr->next != Rptr)
    {
        if (!ptr->next->r->getActive())
        {
            ptr = ptr->next;
            continue;
        }
        if (*(Rptr->r) == *(ptr->next->r) && Rptr != ptr->next)
        { // check looked
            Rptr->r->addLook(ptr->next->r->getX(), ptr->next->r->getY());
            cout << Rptr->r->getType() << " " << Rptr->r->getName() << " looked " << ptr->next->r->getType() << " " << ptr->next->r->getName() << " at (" << ptr->next->r->getX() << "," << ptr->next->r->getY() << ")" << endl;
            *outfile << Rptr->r->getType() << " " << Rptr->r->getName() << " looked " << ptr->next->r->getType() << " " << ptr->next->r->getName() << " at (" << ptr->next->r->getX() << "," << ptr->next->r->getY() << ")" << endl;
        }
        ptr = ptr->next;
    }
}

void Controller::checkUpgrade() // Handle Robot Upgrade
{
    Robot *upgrade;
    if (Rptr->r->getUpgrade())
    {
        string type = Rptr->r->getType();
        if (type == "RoboCop" || type == "Terminator")
        {
            upgrade = new TerminatorRoboCop(Rptr->r);
        }
        else if (type == "BlueThunder")
        {
            upgrade = new Madbot(Rptr->r);
        }
        else if (type == "Madbot")
        {
            upgrade = new RoboTank(Rptr->r);
        }
        else if (type == "TerminatorRoboCop" || type == "RoboTank")
        {
            upgrade = new UltimateRobot(Rptr->r);
        }
        else
        {
            return;
        }
        delete Rptr->r;
        Rptr->r = upgrade; // replace robot by upgraded robot
        cout << Rptr->r->getName() << " upgrade to " << Rptr->r->getType() << endl;
        *outfile << Rptr->r->getName() << " upgrade to " << Rptr->r->getType() << endl;
    }
}

void Controller::randomPos()
{
    // assigned valid position for return robot
    Rptr->r->switchActive();
    int posX;
    int posY;
    do
    {
        posX = rand() % rows;
        posY = rand() % cols;
    } while (!validPos(posX, posY));
    Rptr->r->setX(posX);
    Rptr->r->setY(posY);
    cout << Rptr->r->getType() << " " << Rptr->r->getName() << " return at (" << Rptr->r->getX() << "," << Rptr->r->getY() << ")" << endl;
    *outfile << Rptr->r->getType() << " " << Rptr->r->getName() << " return at (" << Rptr->r->getX() << "," << Rptr->r->getY() << ")" << endl;
}

void Controller::returnRobot()
{
    if (!q->isEmpty()) // append the return robot from queue back to linkedlist
    {
        l->append(Rptr, q->Front());
        q->pop();
    }
}

void Controller::run()
{
    b->clearScreen();
    b->displayPlayer(Rptr);
    b->INIT();
    b->placeRobot(Rptr);
    b->displayBoard();
    b->displayOutput();
    b->Input();
    for (int i = 0; i <= steps; i++)
    {
        b->clearScreen();
        resetRobot();
        b->INIT();
        b->displayTurn(turn, Rptr);
        if (!Rptr->r->getActive())
            randomPos();
        Rptr->r->action();
        checkKill();
        cout << "---------------------------------------" << endl;
        *outfile << "---------------------------------------" << endl;
        b->placeRobot(Rptr);
        b->displayBoard();
        b->displayOutput();
        if (Rptr == Rptr->next && q->isEmpty()) // end when one robot remained
        {
            cout << Rptr->r->getType() << " " << Rptr->r->getName() << " WIN" << endl;
            *outfile << Rptr->r->getType() << " " << Rptr->r->getName() << " WIN" << endl;
            break;
        }
        Rptr = Rptr->next; // point to next Robot
        returnRobot();     // append the return robot from queue back to linkedlist
        b->Input();
        turn++;
    }
}

int Controller::getROWS() const { return rows; }

int Controller::getCOLS() const { return cols; }

ofstream *Controller::getOutput() const { return outfile; }

string Controller::trimLeft(string s)
{
    for (int c = 0; c < s.length(); c++)
    {
        if (s[c] == ' ')
        {
            s.erase(c, 1);
        }
    }
    return s;
}
string Controller::trimRight(string s)
{
    for (int c = s.length() - 1; c >= 0; c--)
    {
        if (s[c] == ' ')
        {
            s.erase(c, 1);
        }
    }
    return s;
}
// Function to trim whitespace from a string
string Controller::trim(string s)
{
    s = trimLeft(s);
    s = trimRight(s);
    return s;
}
