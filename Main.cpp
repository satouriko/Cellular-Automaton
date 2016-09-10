//
// Created by lijiahao on 9/10/16.
//

#include "GameController.h"
#include <vector>
#include <unistd.h>

using namespace std;

int main()
{
    vector<CellCar> stage = createMap();
    while(1)
    {
        loop(stage);
        usleep(100 * 1000);
    }
    return 0;
}
