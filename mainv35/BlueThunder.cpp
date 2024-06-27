#include "BlueThunder.h"

BlueThunder::BlueThunder(int x, int y, string n) : Robot(x, y, n)
{
    type = "BlueThunder";
    count = 0;
}

BlueThunder::BlueThunder(const Robot *other) : Robot(other) { type = "BlueThunder"; }

void BlueThunder::fire()
{
    while (Bptr->validTarget(DIR[count][0], DIR[count][1]))
    {
        count++;
        if (count >= 8)
            count = 0;
    }
    setTarget(getX() + DIR[count][0], getY() + DIR[count][1]);
    cout << "Fire at (" << getX() + DIR[count][0] << "," << getY() + DIR[count][1] << ")" << endl;
    *outfile << "Fire at (" << getX() + DIR[count][0] << "," << getY() + DIR[count][1] << ")" << endl;
    count++;
    if (count >= 8)
        count = 0;
}

void BlueThunder::action()
{
    fire();
}