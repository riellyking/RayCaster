//
// Created by riell on 4/30/2021.
//

#ifndef SFML_TEMPLATE_RAY_H
#define SFML_TEMPLATE_RAY_H

#include <vector>
#include <cmath>
using namespace std;

#include <SFML\Graphics.hpp>
using namespace sf;


const int FOV = 60;
const int MAP_SIZE = 36;

class ray {
public:
    ray();
    double GetX() const;
    double GetY() const;
    double GetDistanceTraveled() const;
    char GetWallHit() const;
    void SetX(double x);
    void SetY(double y);
    void SetDistanceTraveled(double distance);
    void SetWallHit(char wall);
    bool CheckCollisionVertical(vector< vector<RectangleShape> > &mapSFML) const;
    bool CheckCollisionHorizontal(vector< vector<RectangleShape> > &mapSFML) const;
    void UpdatePosition(double dx, double dy);
private:
    double x;
    double y;
    double distanceTraveled;
    char wallHit;
};


#endif //SFML_TEMPLATE_RAY_H
