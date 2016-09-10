//
// Created by lijiahao on 9/10/16.
//

#include "CellCar.h"
#include "GameController.h"
#include "DrawHelper.h"
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;

vector <CellCar> createMap() {
    vector <CellCar> plat;
    random_device rd;
    for (int i = 0; i < CARNUM; ++i) {
        int x = rd() % (RIGHTXLIM - LEFTXLIM + 1) + LEFTXLIM;
        int y = rd() % (BOTTOMYLIM - TOPYLIM + 1) + TOPYLIM;
        cout << x << ' ' << y << endl;
        CellCar temp(x, y);
        plat.push_back(temp);
    }
    return plat;
}

void loop(vector <CellCar> &plat) {
    draw(plat);
    for (vector<CellCar>::iterator iter = plat.begin(); iter != plat.end(); ++iter) {
        iter->moveOn(plat.begin(), plat.end());
    }
}

void draw(vector <CellCar> &plat) {

    //CLEAR();
    static int temp[BOTTOMYLIM - TOPYLIM + 1][RIGHTXLIM - LEFTXLIM +1];
    for(int i = 0; i < BOTTOMYLIM - TOPYLIM + 1; ++i)
    {
        for(int j = 0; j < RIGHTXLIM - LEFTXLIM + 1; ++j)
        {
            temp[i][j] = 0;
        }
    }
    for(vector<CellCar>::iterator iter = plat.begin(); iter != plat.end(); ++iter)
    {
        temp[iter->getY() - TOPYLIM][iter->getX() - LEFTXLIM] = 1;
    }
    for(int i = 0; i < BOTTOMYLIM - TOPYLIM + 1; ++i)
    {
        for(int j = 0; j < RIGHTXLIM - LEFTXLIM + 1; ++j)
        {
            cout << temp[i][j];
        }
        cout << '\n';
    }

    //buggy
    /* for(int i = TOPYLIM; i <= BOTTOMYLIM; ++i )
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
     } */
    cout << flush;
}