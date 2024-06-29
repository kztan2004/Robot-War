#include "Controller.h"
#include <ctime>

// kztan2004
// 5/5/2024 - 27/6/2024
// Compile code below:
// g++ -o a *.cpp && .\a
int main()
{
    srand(time(0));
    try
    {
        Controller *C = new Controller("input.txt", "output.txt");
        C->run();
        delete C;
    }
    catch (const invalid_argument &e)
    {
        cerr << "Caught exception: " << e.what() << endl;
    }
    return 0;
}