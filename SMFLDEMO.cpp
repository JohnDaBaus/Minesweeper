
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <fstream>
#include "TextureManager.h"
#include "Board.h"
#include <string>

using namespace std;
int main()
{

    //sf::Sprite faceH;
    //sf::Sprite faceL;
    //sf::Sprite faceW;
    //sf::Sprite debug;
    //sf::Sprite digits;
    //sf::Sprite h;
    //sf::Sprite t;
    //sf::Sprite o;
    //sf::Sprite t1;
    //sf::Sprite t2;
    //sf::Sprite t3;


    //happyFace.setTexture(TextureManager::GetTexture("face_happy"));
    //loserFace.setTexture(TextureManager::GetTexture("face_lose"));
    //winnerFace.setTexture(TextureManager::GetTexture("face_win"));
    //debug.setTexture(TextureManager::GetTexture("debug"));
    //digits.setTexture(TextureManager::GetTexture("digits"));
    //t1.setTexture(TextureManager::GetTexture("test_1"));
    //t2.setTexture(TextureManager::GetTexture("test_2"));
    //t3.setTexture(TextureManager::GetTexture("test_3"));

    ifstream openFile;
    openFile.open("boards/config.cfg");

    string tempW;
    string tempH;
    string mines;

    getline(openFile, tempW);
    getline(openFile, tempH);
    getline(openFile, mines);

    int width = stoi(tempW);
    int height = stoi(tempH);
    int totalMines = stoi(mines);


    sf::RenderWindow window(sf::VideoMode((stoi(tempW) * 32), ((stoi(tempH) * 32) + 100)), "Minesweeper");
    board gameBoard = board(height, width, totalMines);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (!gameBoard.isLoser && !gameBoard.isWinner)
                {
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        sf::Vector2i position = sf::Mouse::getPosition(window);
                        auto mouse = window.mapPixelToCoords(position);

                        for (int i = 0; i < (width * height); i++)
                        {
                            sf::FloatRect hiddenTile = gameBoard.entireBoard[i].unrevealed.getGlobalBounds();

                            if (hiddenTile.contains(mouse))
                            {
                                gameBoard.changeFlagStatus(i);
                            }
                        }
                    }
                }

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i position = sf::Mouse::getPosition(window);
                    auto mouse = window.mapPixelToCoords(position);
                    sf::FloatRect happyButton = gameBoard.faceH.getGlobalBounds();
                    sf::FloatRect test1Button = gameBoard.t1.getGlobalBounds();
                    sf::FloatRect test2Button = gameBoard.t2.getGlobalBounds();
                    sf::FloatRect test3Button = gameBoard.t3.getGlobalBounds();
                    sf::FloatRect debugButton = gameBoard.debug.getGlobalBounds();

                    if (happyButton.contains(mouse))
                    {
                        gameBoard.reset(height, width, totalMines);
           
                    }
                    if (!gameBoard.isLoser && !gameBoard.isWinner)
                    {

                        if (debugButton.contains(mouse))
                        {
                                gameBoard.debugOn = !(gameBoard.debugOn);
                              
                        }

                        for (int i = 0; i < (width * height); i++)
                        {
                            sf::FloatRect tile = gameBoard.entireBoard[i].unrevealed.getGlobalBounds();
                            if (tile.contains(mouse))
                            {
                                if (!(gameBoard.entireBoard[i].isMine) && !(gameBoard.entireBoard[i].isFlag))
                                {                                    
                                   if(gameBoard.entireBoard[i].isHidden)
                                   {
                                       gameBoard.Reveal(i);

                                    }
                                }  
                            }
                        }

                        for (int i = 0; i < (width * height); i++)
                        {
                            sf::FloatRect tile = gameBoard.entireBoard[i].unrevealed.getGlobalBounds();
                            if (tile.contains(mouse))
                            {
                                if (gameBoard.entireBoard[i].isMine)
                                {
                                    if (!(gameBoard.entireBoard[i].isFlag))
                                    {
                                        gameBoard.loseCondition();
                                    }
                                }
                                
                            }
                        }
                    }
                    if (test1Button.contains(mouse))
                    {
                        gameBoard.testBoards("testboard1");
                    }
                    if (test2Button.contains(mouse))
                    {   
                        gameBoard.testBoards("testboard2");
                    }
                    if (test3Button.contains(mouse))
                    {
                        gameBoard.testBoards("testboard3");
                    }
                }
            }
        }

        window.clear();


        int y = 0;
        int completeHeight = height * 32;
        for (int i = 0; i < completeHeight; i =  i + 32)
        {
            for (int j = 0; j < width; j++) 
            {
                int x = j * 32;
                gameBoard.setSpritePositions(y, i, x);
                gameBoard.changeTiles(y, window);
                gameBoard.drawNumbers(y, window);
                gameBoard.drawFlagandMine(y, window);
                y++;
            }
        }
        gameBoard.winCondition();
        gameBoard.drawMineCounter(window);
        gameBoard.changeFace(window);
        gameBoard.drawButtons(window);

        window.display();
    }

    TextureManager::Clear();
    return 0;
}