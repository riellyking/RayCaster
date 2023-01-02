//
// Created by riell on 4/30/2021.
//

#include "SfmlDrawingFunctions.h"

//Create Map SFML function:
vector< vector<RectangleShape> > CreateMapSFML(vector< vector<int> > &binaryMap) {
    vector< vector<RectangleShape> > mapSFML;                                            //Takes in 2D int vector
    for (int i = 0; i < binaryMap.size(); i++) {
        vector<RectangleShape> newMapRow;
        for (int j = 0; j < binaryMap.at(i).size(); j++) {                               //Creates a map block to draw to window for each
            RectangleShape mapGridElement;                                               //0 and 1 in 2D map vector
            mapGridElement.setSize(Vector2f(30, 30));
            if (binaryMap.at(i).at(j) == 1) {
                mapGridElement.setFillColor(Color::White);
            } else {
                mapGridElement.setFillColor((Color::Black));
            }
            mapGridElement.setOutlineThickness(1);
            mapGridElement.setOutlineColor(Color(128, 128, 128));
            mapGridElement.setPosition((j + 1) * 30, (i + 1) * 30);
            newMapRow.push_back(mapGridElement);
        }
        mapSFML.push_back(newMapRow);
    }
    return mapSFML;
}


//Draw Mini Map function:
void DrawMiniMap(vector< vector<RectangleShape> > &sfmlMap, RenderWindow &window) {
    for (int i = 0; i < sfmlMap.size(); i++) {                                          //PBR on map to save memory, PBR on window bc it can't be copied.
        for (int j = 0; j < sfmlMap.at(i).size(); j++) {
            window.draw(sfmlMap.at(i).at(j));                                           //for each block in map, draw it to the screen
        }
    }
}


//Draw ray function:
void DrawRays(vector<ray> rays, RectangleShape player, RenderWindow &window) {
    for (int i = 0; i < rays.size(); i++) {                                             //creates 1 ray per 1 degree in FOV.
        RectangleShape line;
        line.setSize(Vector2f(1,rays.at(i).GetDistanceTraveled()));             //For each ray, create a thin line to represent it
        line.setOrigin(0.5,rays.at(i).GetDistanceTraveled());
        line.setPosition(player.getPosition());                                         //Set line position to player
        if (rays.at(i).GetWallHit() == 'v') {
            line.setFillColor(Color(204,102,0));                   //rays that hit vertical walls will be colored different
        } else {
            line.setFillColor(Color(255,128,0));
        }
        line.setRotation((player.getRotation() - (FOV / 2.0) + i));               //rotating line to player angle + offset based on FOV and which ray it is
        window.draw(line);
    }
}


//Main scene drawing function, turns this from top down 2d game to illusion of 3d game.
void DrawScene(vector<ray> rays, RenderWindow &window) {
    for (int i = 0; i < rays.size(); i++) {
        //Fixing fisheye camera effect:
        rays.at(i).SetDistanceTraveled(rays.at(i).GetDistanceTraveled() * cos(fabs((-FOV / 2.0) + i) * M_PI / 180));

        double wallHeight = (MAP_SIZE * 900) / rays.at(i).GetDistanceTraveled(); //Wall Height is determined by how far the ray traveled before hitting a wall
        double wallWidth = (1600 / FOV);                                         //farther walls have small height, close walls have large height

        RectangleShape wall;
        wall.setSize(Vector2f(wallWidth,wallHeight));                       //creating wall for each ray
        wall.setOrigin(0, wallHeight / 2);                                 //putting vert origin in center of wall
        wall.setPosition(wallWidth * i,450);                               //Centering wall vertically, horizontal position dependent on angle
        if (rays.at(i).GetWallHit() == 'v') {
            wall.setFillColor(Color(204,102,0));            //coloring walls different so its easier to see
        } else {
            wall.setFillColor(Color(255,128,0));
        }
        window.draw(wall);                                                       //drawing the wall

        RectangleShape floor;
        floor.setSize(Vector2f(wallWidth,(900.0 - wallHeight) / 2.0));   //creating floor
        floor.setFillColor(Color(96,96,96));
        floor.setPosition(wallWidth * (i),900 - floor.getSize().y );       //positioning at the bottom of each wall
        floor.setOrigin(0, 0);
        window.draw(floor);                                                      //drawing the floor

        RectangleShape sky;                                                      //creating sky
        sky.setSize(floor.getSize());
        sky.setFillColor(Color(51,153,255));                 //positioning at the top of each wall
        sky.setOrigin(0,0);
        sky.setPosition(wallWidth * (i),0);
        window.draw(sky);                                                        //drawing the sky
    }
}