//
// Created by lijiahao on 9/10/16.
//

#include "CellCar.h"
#include "GameController.h"
#include "DrawHelper.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

vector<CellCar> createMap ()
{
    vector<CellCar> plat;
    for(int i = 0; i < CARNUM; ++i)
    {
        srand((int)time(0));
        int x = rand() % (RIGHTXLIM - LEFTXLIM + 1) + LEFTXLIM;
        srand((int)time(0));
        int y = rand() % (BOTTOMYLIM - TOPYLIM + 1) + TOPYLIM;
        CellCar temp(x, y);
        plat.push_back(temp);
    }
    return plat;
}

void loop(vector<CellCar>& plat)
{
    draw(plat);
    for(vector<CellCar>::iterator iter = plat.begin(); iter != plat.end(); ++iter)
    {
        iter->moveOn(plat.begin(), plat.end());
    }
}

void draw(vector<CellCar>& plat)
{
    CLEAR();
    for(int i = TOPYLIM; i <= BOTTOMYLIM; ++i )
    {
        for(int j = LEFTXLIM; j <= RIGHTXLIM; ++j)
        {
            CellCar temp(i, j);
            if(find(plat.begin(),plat.end(), temp) != plat.end())
                cout << '0';
            else
                cout << ' ';
        }
        cout << '\n';
    }
    cout << flush;
}