
#include "Tile.h"
#include <vector>
using namespace std;

class board 
{
public:
    int width2,height2;
    int tilesLeft, minesLeft;
    bool isHappy = true;
    bool isLoser, isWinner, debugOn = false;

    sf::Sprite faceH, faceL, faceW;
    sf::Sprite h, o , t, digits, negativeSign;
    sf::Sprite t1, t2, t3, debug;
    vector <tile> entireBoard;

    void setTexturesB();
    void reset(int height2N, int width2N, int  minesLeftN);
    void drawFlagandMine(int i, sf::RenderWindow& window);
    void declareTilePos();
    void setSpritePositions(int x, int i, int j);
    void Reveal(int i);
    void changeFace(sf::RenderWindow& window);
    void setNeighbors();
    void drawButtons(sf::RenderWindow& window);
    void defaultSettings();
    void randMines(int minesLeft, int rows, int columns);
    void noNeigborsMines(int i);
    void changeTiles(int i, sf::RenderWindow& window);
    void drawNumbers(int i, sf::RenderWindow& window);
    void winCondition();
    void loseCondition();
    void changeFlagStatus(int i);
    void drawMineCounter(sf::RenderWindow& window);
    void testBoards(string boardtype);
    void surroundingTiles(int position, int i, int spot);
    board(int height, int width, int minesLeft)
    {
        debug.setTexture(TextureManager::GetTexture("debug"));
        digits.setTexture(TextureManager::GetTexture("digits"));
        t1.setTexture(TextureManager::GetTexture("test_1"));
        t2.setTexture(TextureManager::GetTexture("test_2"));
        t3.setTexture(TextureManager::GetTexture("test_3"));
        faceH.setTexture(TextureManager::GetTexture("face_happy"));
        faceL.setTexture(TextureManager::GetTexture("face_lose"));
        faceW.setTexture(TextureManager::GetTexture("face_win"));
        negativeSign.setTexture(TextureManager::GetTexture("digits"));
        negativeSign.setPosition(sf::Vector2f(0, 32 * height));
        o.setTexture(TextureManager::GetTexture("digits"));
        t.setTexture(TextureManager::GetTexture("digits"));
        h.setTexture(TextureManager::GetTexture("digits"));
        h.setPosition(sf::Vector2f(63, 32 * height));
        t.setPosition(sf::Vector2f(42, 32 * height));
        o.setPosition(sf::Vector2f(21, 32 * height));
        reset(height, width, minesLeft);
    }
    bool getLoser()
    {
        return isLoser;
    }
    bool getWinner()
    {
        return isWinner;
    }
    bool getHappy()
    {
        return isHappy;
    }
};