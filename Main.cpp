//
// Created by lijiahao on 9/10/16.
//

#include "GameController.h"
#include <vector>
#include <unistd.h>
#include <iostream>

using namespace std;

int main()
{
    vector<CellCar> stage = createMap();
    while(1)
    {
        loop(stage);
        getchar();
        //usleep(2000 * 1000);
    }
    return 0;
}
