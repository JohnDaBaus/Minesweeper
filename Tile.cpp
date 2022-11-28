#include "Tile.h"
using namespace std;

void tile::setTextures() 
{
    unrevealed.setTexture(TextureManager::GetTexture("tile_hidden"));
    revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
    n1.setTexture(TextureManager::GetTexture("number_1"));
    n2.setTexture(TextureManager::GetTexture("number_2"));
    n3.setTexture(TextureManager::GetTexture("number_3"));
    n4.setTexture(TextureManager::GetTexture("number_4"));
    n5.setTexture(TextureManager::GetTexture("number_5"));
    n6.setTexture(TextureManager::GetTexture("number_6"));
    n7.setTexture(TextureManager::GetTexture("number_7"));
    n8.setTexture(TextureManager::GetTexture("number_8"));
    spriteF.setTexture(TextureManager::GetTexture("flag"));
    spriteM.setTexture(TextureManager::GetTexture("mine"));
}

void tile::putIntoVector() 
{
    numVec.push_back(n1);
    numVec.push_back(n2);
    numVec.push_back(n3);
    numVec.push_back(n4);
    numVec.push_back(n5);
    numVec.push_back(n6);
    numVec.push_back(n7);
    numVec.push_back(n8);
}

void tile::defaultSettings()
{
    corner, top, bottom, leftSide, rightSide = false;
    totalNeighborTiles, neigborMines = 0;
    isMine, isFlag, numShowing = false;
    isHidden = true;
}







