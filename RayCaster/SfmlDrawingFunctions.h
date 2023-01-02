//
// Created by riell on 4/30/2021.
//

#ifndef SFML_TEMPLATE_SFMLDRAWINGFUNCTIONS_H
#define SFML_TEMPLATE_SFMLDRAWINGFUNCTIONS_H

#include "Ray.h"

vector< vector<RectangleShape> > CreateMapSFML(vector< vector<int> > &binaryMap);
void DrawMiniMap(vector< vector<RectangleShape> > &sfmlMap, RenderWindow &window);
void DrawRays(vector<ray> rays, RectangleShape player, RenderWindow &window);
void DrawScene(vector<ray> rays, RenderWindow &window);

#endif //SFML_TEMPLATE_SFMLDRAWINGFUNCTIONS_H
