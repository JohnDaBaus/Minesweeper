
#pragma once
#include "TextureManager.h"
#include <vector>
using namespace std;

class tile
{
public:
    sf::Sprite unrevealed, revealed;
    sf::Sprite spriteF, spriteM;
    sf::Sprite n1, n2, n3, n4, n5, n6, n7, n8;
    bool isMine, isFlag, isHidden, numShowing, corner, top, bottom, leftSide, rightSide;
    int totalNeighborTiles, neigborMines;
    int neigbors[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
    vector <sf::Sprite> numVec;

    tile()
    {

        corner, top, bottom, leftSide, rightSide = false;
        totalNeighborTiles, neigborMines = 0;

        isMine, isFlag, numShowing = false;
        isHidden = true;

        defaultSettings();
        setTextures();
        putIntoVector();
    }
    void setTextures();
    void putIntoVector();
    void defaultSettings();
};

