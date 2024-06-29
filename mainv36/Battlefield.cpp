#include "Battlefield.h"

Battlefield::Battlefield(int rows, int cols, ofstream *outfile) : rows(rows), cols(cols), outfile(outfile)
{
    fast = false;
    board = new char *[rows];
    for (int i = 0; i < rows; ++i)
    {
        board[i] = new char[cols];
    }
}

void Battlefield::INIT() // Initialization of Battlefield
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            board[i][j] = '.';
        }
    }
}

void Battlefield::clearScreen() // Suit Window and Mac
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Battlefield::displayPlayer(Node *Rptr)
{
    cout << "-------------------Robots------------------" << endl;
    *outfile << "-------------------Robots------------------" << endl;
    Node *ptr = Rptr;
    do
    {
        cout << setw(17) << ptr->r->getType() << setw(8) << ptr->r->getName() << " at Position (" << ptr->r->getX() << "," << ptr->r->getY() << ")" << endl;
        *outfile << setw(17) << ptr->r->getType() << setw(8) << ptr->r->getName() << " at Position (" << ptr->r->getX() << "," << ptr->r->getY() << ")" << endl;
        ptr = ptr->next;
    } while (ptr != Rptr);
    cout << "-------------------------------------------" << endl
         << endl;
    *outfile << "-------------------------------------------" << endl
             << endl;
}

void Battlefield::displayTurn(int turn, Node *Rptr)
{
    cout << "--------------- Turn " << turn << " ----------------" << endl;
    cout << Rptr->r->getType() << " " << Rptr->r->getName() << endl;
    cout << "Lives:" << Rptr->r->getLives() << endl;
    cout << "---------------------------------------" << endl;
    *outfile << "--------------- Turn " << turn << " ----------------" << endl;
    *outfile << Rptr->r->getType() << " " << Rptr->r->getName() << endl;
    *outfile << "Lives:" << Rptr->r->getLives() << endl;
    *outfile << "---------------------------------------" << endl;
}

void Battlefield::displayBoard()
{
    // Define Padding
    cout << "   ";
    for (int j = 0; j < cols; j++)
    {
        cout << " " << setw(2) << j << " ";
    }
    cout << endl;

    // Print the top border
    cout << "   +";
    for (int j = 0; j < cols; j++)
    {
        cout << "---+";
    }
    cout << endl;

    // Print the board with row headers and borders
    for (int i = 0; i < rows; i++)
    {
        cout << setw(2) << i << " |";
        for (int j = 0; j < cols; j++)
        {
            cout << " " << board[i][j] << " |";
        }
        cout << endl;

        // Print the row separator
        cout << "   +";
        for (int j = 0; j < cols; j++)
        {
            cout << "---+";
        }
        cout << endl;
    }
}

void Battlefield::displayOutput()
{
    // Define Padding
    *outfile << "   ";
    for (int j = 0; j < cols; j++)
    {
        *outfile << " " << setw(2) << j << " ";
    }
    *outfile << endl;

    // Print the top border
    *outfile << "   +";
    for (int j = 0; j < cols; j++)
    {
        *outfile << "---+";
    }
    *outfile << endl;

    // Print the board with row headers and borders
    for (int i = 0; i < rows; i++)
    {
        *outfile << setw(2) << i << " |";
        for (int j = 0; j < cols; j++)
        {
            *outfile << " " << board[i][j] << " |";
        }
        *outfile << endl;

        // Print the row separator
        *outfile << "   +";
        for (int j = 0; j < cols; j++)
        {
            *outfile << "---+";
        }
        *outfile << endl;
    }
}

void Battlefield::placeRobot(Node *Rptr) // place robot on board
{
    Node *ptr = Rptr;
    do
    {
        if (!ptr->r->getActive())
        {
            ptr = ptr->next;
            continue;
        }
        board[ptr->r->getX()][ptr->r->getY()] = ptr->r->getName()[0];
        ptr = ptr->next;
    } while (ptr != Rptr);
}

void Battlefield::Input()
{
    cout << endl;
    *outfile << endl;
    if (fast)
        return;
    int i;
    cout << "CONTROLLER (1=NEXT,-1=FAST): ";
    cin >> i;
    if (i == -1)
        fast = true;
}

Battlefield::~Battlefield()
{
    for (int i = 0; i < rows; ++i)
    {
        delete[] board[i];
    }
    delete[] board;
    board = nullptr;
    outfile->close(); // exception close outfile handler
    delete outfile;
}