//Rielly King
//CSCI - 261 - Final Project - Simple Ray Cast Engine
//Section C

#include "Ray.h"
#include "SfmlDrawingFunctions.h"
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    RenderWindow window(VideoMode(1600,900), "Ray Caster");
    window.setFramerateLimit(40);


    ifstream mapInput("map2.txt"); //To change maps, this needs to be changed to map1.txt or map2.txt
    if (!mapInput.is_open()) {
        cerr << "Error, map could not be loaded from file" << endl;
        return -1;
    }


    vector< vector<int> > mapBinary(8);                                       //creating binary map
    for (int i = 0; i < 8; i++) {
        vector<int> newMapRow(8);
        for (int j = 0; j < 8; j++) {                                            //filling map vector with map from file
            mapInput >> newMapRow.at(j);
        }
        mapBinary.at(i) = newMapRow;
    }
    mapInput.close();                                                            //done reading in map, so closing file stream


    vector< vector<RectangleShape> > mapSFML = CreateMapSFML(mapBinary);      //turning binary map into one that can be drawn


    RectangleShape player;
    player.setSize(Vector2f(6,6));                                     //making shape for player
    player.setOrigin(3,3);
    player.setPosition(150,225);
    player.setFillColor(Color::Red);


    while (window.isOpen()) {                                                    //Main game loop
        Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == Event::Closed) {                                    //checking for window closing
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {                       //checking for keyboard events to move the player
            player.rotate(3);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            player.rotate(-3);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            player.move((2 * sin(player.getRotation() * M_PI / 180)),-(2 * cos(player.getRotation() * M_PI / 180)));
        }                                                                         //doing math to determine X and Y offset based on player angle
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            player.move(-(2 * sin(player.getRotation() * M_PI / 180)),(2 * cos(player.getRotation() * M_PI / 180)));
        }


        vector<ray> rays(FOV+2); //Needed extra 2 rays to fill screen nicely
        for (int i = 0; i < rays.size(); i++) {
            ray newRay;                                                           //Creating 1 ray per 1 degree in FOV
            newRay.SetX(player.getPosition().x);                                  //ray initial position set to player position
            newRay.SetY(player.getPosition().y);
            while (true) {
                if (newRay.CheckCollisionVertical(mapSFML)) {                  //Until collision happens, ray is moved a small amount then checks for collision again.
                    newRay.SetWallHit('v');
                    rays.at(i) = newRay;
                    break;
                }
                if (newRay.CheckCollisionHorizontal(mapSFML)) {
                    newRay.SetWallHit('h');
                    rays.at(i) = newRay;
                    break;
                }                                                                //shoots the ray 1.5 pixels in direction that it should be going in
                newRay.UpdatePosition(1.5 * sin((player.getRotation() + i - (FOV/2.0)) * M_PI / 180),-1.5 * cos((player.getRotation() + i - (FOV/2.0)) * M_PI / 180));
            }
        }


        DrawScene(rays,window);          //Drawing 3d scene first
        DrawMiniMap(mapSFML,window);  //Drawing minimap over 3d scene
        DrawRays(rays,player,window);     //drawing rays over minimap
        window.draw(player);                 //drawing player over rays
        window.display();                    //displaying and clearing
        window.clear();
    }
    return 0;
}