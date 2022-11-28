#include "Board.h"
#include "Random.h"
#include <fstream>
#include <vector>


void board::defaultSettings()
{
    isLoser = false;
    isWinner = false;
    isHappy = true;
    minesLeft = 0;
    tilesLeft = 0;
    entireBoard.clear();
}

void board::noNeigborsMines(int i)
{
    if (entireBoard[i].neigborMines < 1)
    {
         int j = 0;
         while (j <= 7)
         {
             if (entireBoard[i].neigbors[j] != -1)
             {
                 Reveal(entireBoard[i].neigbors[j]);
             }
             j++;
         }    
    }

        
}
void board::reset(int height2N, int width2N, int minesLeftN)
{
    width2 = width2N;
    height2 = height2N;
    minesLeft = minesLeftN;
    tilesLeft = (width2 * height2) - minesLeftN;

    isHappy = true;
    isWinner = false;
    isLoser = false;

    entireBoard.clear();

    declareTilePos();

    randMines(minesLeftN, height2, width2);

    setNeighbors();


    //for (int i = 0; i < width2; i++)
    //{
    //    for (int j = 0; j < height2; j++)
    //    {
    //        t3.setPosition((width2 * 32 - 64), height2 * 32);
    //        t2.setPosition((width2 * 32 - 128), height2 * 32);
    //        t1.setPosition((width2 * 32 - 192), height2 * 32);
    //        debug.setPosition((width2 * 32 - 256), height2 * 32);
    //        happyFace.setPosition(((width2 * 32 - 64)) / 2, height2 * 32);
    //        loserFace.setPosition(((width2 * 32 - 64)) / 2, height2 * 32);
    //        winnerFace.setPosition(((width2 * 32 - 64)) / 2, height2 * 32);

    //    }
    //}

    int posy = height2 * 32;
    int posx = (width2 * 16);
    faceH.setPosition(posx - 32, posy);
    faceL.setPosition(posx - 32, posy);
    faceW.setPosition(posx - 32, posy);
    debug.setPosition(posx + 96, posy);
    t1.setPosition(posx + 160, posy);
    t2.setPosition(posx + 224, posy);
    t3.setPosition(posx + 288, posy);
}

void board::randMines(int totalMines, int height2, int width2)
{

    for (int i = 0; i < totalMines; i++)
    {
        int x = (Random::Int(0, (height2 * width2) - 1));
        if (!entireBoard[x].isMine) 
        {
            entireBoard[x].isMine = !(entireBoard[x].isMine);
            
        }
    }
}

void board::Reveal(int i) {
    if (entireBoard[i].isHidden)
    {
        if (!(entireBoard[i].isFlag))
        {        
            entireBoard[i].isHidden = !(entireBoard[i].isHidden);
            entireBoard[i].numShowing = true;
            tilesLeft --;
            noNeigborsMines(i);

        }

    }
}



void board::setSpritePositions(int x,int i, int j) 
{
    int y = 0;
    entireBoard[x].unrevealed.setPosition(j, i);
    entireBoard[x].revealed.setPosition(j, i);
    entireBoard[x].spriteF.setPosition(j, i);
    entireBoard[x].spriteM.setPosition(j, i);

    while (y <= 7)
    {
        entireBoard[x].numVec[y++].setPosition(j, i);
    }
}



void board::declareTilePos()
{
    int i = 0;
    while (i < (width2 * height2))
    {
        tile T = tile();

        if (i == (width2 * height2) - 1)
        {
            T.corner = true;
        }
        if (i == 0) 
        {
            T.corner = true;
        }
        if (i == (width2 * height2) - width2)
        {
            T.corner = true;
        }
        if (i == width2 - 1)
        {
            T.corner = true;
        }
        if (i % width2 == 0)
        {
            T.leftSide = true;
        }
        if ((i % width2 == width2 - 1))
        {
            T.rightSide = true;
        }
        if (i < width2)
        {
            T.top = true;
        }        
        if (i >=(width2 * height2) - width2)
        {
            T.bottom = true;
        }
        if ((!(T.corner) && (T.leftSide)) || (!(T.corner) && (T.rightSide)) || (!(T.corner) && (T.bottom)) || (!(T.corner) && (T.top)))
        {
            T.totalNeighborTiles = 5;
        }
        if (T.corner)
        {
            T.totalNeighborTiles = 3;
        }
        entireBoard.push_back(T);
        i++;
    }
}
void board::changeTiles(int i, sf::RenderWindow& window)
{
    if (entireBoard[i].isHidden)
    {
        window.draw(entireBoard[i].unrevealed);
    }
    else if(!(entireBoard[i].isHidden))
    {
        window.draw(entireBoard[i].revealed);

    }
}

void board::drawFlagandMine(int i, sf::RenderWindow& window)
{
    if (entireBoard[i].isFlag)
    {
        window.draw(entireBoard[i].spriteF);
    }
    if (isWinner)
    {
        if (entireBoard[i].isMine)
        {
            window.draw(entireBoard[i].spriteF);
        }
    }
    if (entireBoard[i].isMine)
    {
        if (debugOn)
        {
            window.draw(entireBoard[i].spriteM);
        }
        if (isLoser)
        {
            window.draw(entireBoard[i].spriteM);
        }
    }
}

void board::testBoards(string boardtype)
{
    unsigned char digit;
    int i = 0;
    defaultSettings();
    declareTilePos();
    string filename = "boards/" + boardtype + ".brd";

    ifstream test1file((filename));
    while (i < (width2 * height2))
    {
        test1file >> digit;
        if (digit == '0')
        {
            tilesLeft++;
        }
        else
        {
            entireBoard[i].isMine = true;
            minesLeft++;
        }
        i++;
    }
    setNeighbors();
}

void board::surroundingTiles(int position, int i, int spot)
{
    if (entireBoard[position].isMine)
    {
        entireBoard[i].neigborMines++;
        entireBoard[i].totalNeighborTiles--;
    }
    else if (!(entireBoard[position].isMine))
    {
        entireBoard[i].neigbors[spot] = position;
    }

}


void board::drawButtons(sf::RenderWindow& window)
{
    window.draw(debug);
    window.draw(t1);
    window.draw(t2);
    window.draw(t3);

}

void board::drawNumbers(int i, sf::RenderWindow& window)
{
    if (!(entireBoard[i].isHidden))
    {
        if (entireBoard[i].numShowing)
        {
            if (entireBoard[i].neigborMines > 0)
            {
                window.draw(entireBoard[i].numVec[(entireBoard[i].neigborMines)-1]);
            }
        
        }
    }
}

void board::changeFace(sf::RenderWindow& window)
{
    if (!isWinner && !isLoser)
    {
        window.draw(faceH);
    }
    else
    {
        if (isWinner)
        {
            window.draw(faceW);
        }
        else 
        {
            window.draw(faceL);
        }

    }


}

void board::changeFlagStatus(int j)
{

    if (entireBoard[j].isHidden)
    {
        if (entireBoard[j].isFlag || !(entireBoard[j].isFlag))
        {
            entireBoard[j].isFlag = !(entireBoard[j].isFlag);

            if (entireBoard[j].isFlag)
            {
                minesLeft--;
            }
            else if (!(entireBoard[j].isFlag))
            {
                minesLeft++;
            }

        }
    }
}

void board::setNeighbors() 
{
    int i = 0;
    while (i < (height2 * width2)) 
    {
        if (!(entireBoard[i].top))
        {
            if (!(entireBoard[i].leftSide))
            {
                surroundingTiles((i - width2 - 1), i, 0);
            }
        }
        if (!(entireBoard[i].top))
        {
            surroundingTiles((i - width2), i, 1);
        }
        if (!(entireBoard[i].top))
        {
            if (!(entireBoard[i].rightSide))
            {
                surroundingTiles((i - width2 + 1), i, 2);
            }
        }
        if (!(entireBoard[i].leftSide))
        {
            surroundingTiles((i-1), i, 3);
        }
        if (!(entireBoard[i].rightSide))
        {
            surroundingTiles((i+1), i, 4);

        }
        if (!(entireBoard[i].bottom)) 
        {
            if (!(entireBoard[i].leftSide))
            {
                surroundingTiles((i + width2 - 1), i, 5);
            }
        }
        if (!(entireBoard[i].bottom))
        {
            surroundingTiles((i + width2), i, 6);
        }
        if (!(entireBoard[i].bottom))
        {
            if (!(entireBoard[i].rightSide))
            {
                surroundingTiles((i + width2 + 1), i, 7);
            }
            
        }
        i++;
    }
}

void board::drawMineCounter(sf::RenderWindow& window)
{
    int numMines = minesLeft;
    int temp = 1;

    if (numMines <= -1)
    {
        temp = -1;
        numMines *= -1;
    }

    int hp = numMines / 100;
    int tp = (numMines % 100) / 10;
    int op = numMines % 10;

    if (temp <= -1)
    {
        negativeSign.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
        window.draw(negativeSign);
    }

    h.setTextureRect(sf::IntRect(21 * op, 0, 21, 32));
    window.draw(h);
    t.setTextureRect(sf::IntRect(21 * tp, 0, 21, 32));
    window.draw(t);
    o.setTextureRect(sf::IntRect(21 * hp, 0, 21, 32));
    window.draw(o);
}

void board::winCondition()
{
    if (tilesLeft == 0)
    {
        isHappy, isLoser, debugOn = false;
        minesLeft = 0;
        isWinner = true;
    }
}

void board::loseCondition()
{
    isLoser = true;
    for (int j = 0; j < (width2 * height2); j++)
    {
        entireBoard[j].isFlag = false;

    }
    for (int i = 0; i < (width2 * height2); i++)
    {
        if (entireBoard[i].isMine)
        {
            entireBoard[i].isHidden = false;
        }
    }
}




