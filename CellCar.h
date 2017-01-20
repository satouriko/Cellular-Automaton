//
// Created by lijiahao on 9/10/16.
//

#ifndef CA_CELLCAR_H
#define CA_CELLCAR_H

#define FORWARD 0
#define BACK 2
#define LEFT 1
#define RIGHT 3

#define SAFEGAP 2
#define SPEEDLIMIT 5
#define ACC 1.0

#include <vector>

class CellCar {
    double speed;
    double x, y;
    int _dir;

    void turn(int direction);

public:
    CellCar(int x, int y);

    void moveOn(std::vector<CellCar>::iterator begin, std::vector<CellCar>::iterator end);

    void turn();

    const int getX() const ;

    const int getY() const ;

    void syncSpeed(std::vector<CellCar>::iterator begin, std::vector<CellCar>::iterator end);
};

bool operator==(const CellCar &objstruct1, const CellCar &objstruct2);  //重载“==”操作符
#endif //CA_CELLCAR_H
