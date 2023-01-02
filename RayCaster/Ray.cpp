//
// Created by riell on 4/30/2021.
//

#include "Ray.h"


//Constructor: Sets distance traveled to 0
ray::ray() {distanceTraveled = 0;}


//Getters: Pretty Self explanatory
double ray::GetX() const {return x;}
double ray::GetY() const {return y;}
double ray::GetDistanceTraveled() const {return distanceTraveled;}
char ray::GetWallHit() const {return wallHit;}


//Setters: Pretty Self explanatory
void ray::SetX(double x) {this->x = x;}
void ray::SetY(double y) {this->y = y;}
void ray::SetDistanceTraveled(double distance) {distanceTraveled = distance;}
void ray::SetWallHit(char wall) {wallHit = wall;}


//Vertical wall collision check function:
bool ray::CheckCollisionVertical(vector< vector<RectangleShape> > &mapSFML) const {
    for (int i = 0; i < mapSFML.size(); i++) {                                          //No data members modified, so const, PBR to save memory
        for (int j = 0; j < mapSFML.at(i).size(); j++) {                                //Looping through every block in map
            if ((mapSFML.at(i).at(j).getFillColor() == Color::White)                    //If the block is a wall
                && (((fabs(x - mapSFML.at(i).at(j).getPosition().x)) <= 1.5)        //and ray x within range of wall x position
                    || ((fabs(x - (mapSFML.at(i).at(j).getPosition().x+30))) <= 1.5))
                && ((y - mapSFML.at(i).at(j).getPosition().y) <= 30)                    //and ray is in correct vertical range of wall
                && ((y - mapSFML.at(i).at(j).getPosition().y) >= 0)){
                return true;                                                            //Then a vertical collision has occurred.
            }
        }
    }
    return false;
}
//Horizontal wall collision check function:
bool ray::CheckCollisionHorizontal(vector< vector<RectangleShape> > &mapSFML) const {
    for (int i = 0; i < mapSFML.size(); i++) {                                          //No data members modified, so const, PBR to save memory
        for (int j = 0; j < mapSFML.at(i).size(); j++) {                                //Looping through every block in map
            if ((mapSFML.at(i).at(j).getFillColor() == Color::White)                    //If block is a wall
                && (((fabs(y - mapSFML.at(i).at(j).getPosition().y)) <= 1.5)        //and ray y within range of wall y position
                    || ((fabs(y - (mapSFML.at(i).at(j).getPosition().y+30))) <= 1.5))
                && ((x - mapSFML.at(i).at(j).getPosition().x) <= 30)                    //and ray is in correct horizontal range of wall
                && ((x - mapSFML.at(i).at(j).getPosition().x) >= 0)){
                return true;                                                            //Then a horizontal collision has occurred.
            }
        }
    }
    return false;
}


//Update Position function, moves ray and update distance Traveled.
void ray::UpdatePosition(double dx, double dy) {
    x += dx;
    y += dy;
    distanceTraveled += sqrt((dx*dx)+(dy*dy));
}