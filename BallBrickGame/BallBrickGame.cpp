#include "BallBrickGame.h"

#include <iostream>

using namespace std;

BallBrickGame::BallBrickGame()
{

}

BallBrickGame::~BallBrickGame()
{
    if(mpGameWall != nullptr)
    {
        destroyWall();
    }
}

void BallBrickGame::setWallSize()
{
    cout << "Enter size of the NxN matrix : " ;

    cin >> mWallSize;

    createWall();
}

void BallBrickGame::setBallCount()
{
    cout << "Enter ball Count : ";
    cin >> mBallCount;
}

unsigned short BallBrickGame::getWallSize() const
{
    return mWallSize;
}

void BallBrickGame::addBricks()
{
    string add_bric = "Y";
    while(add_bric == "Y")
    {
        cout << "Enter the brick's position and the brick type : " << endl;

        unsigned short m = 0U;
        unsigned short n = 0U;
        string brick_value = "";

        cin >> m;
        cin >> n;
        cin >> brick_value;

        if(validateRow(m) && validateCol(n))
        {
            if(brick_value.length() == 1U)
            {
                mpGameWall[m]->at(n+n) = brick_value[0];
            }
            else
            {
                mpGameWall[m]->at(n+n) = brick_value[0];
                mpGameWall[m]->at(n+n+1) = brick_value[1];
            }
        }

        cout << "Do you want to continue(Y or N)?";
        cin >> add_bric;
    }
}

void BallBrickGame::createWall()
{
    if( mWallSize > 0U)
    {
        if(mpGameWall != nullptr)
        {
            destroyWall();
        }
        else
        {
            mpGameWall = new string*[mWallSize];

            for (unsigned short i = 0; i < mWallSize; i++)
            {
                string row1 = "";
                if(i == 0)
                {
                    for(unsigned short i = 0; i < mWallSize; i++)
                    {
                        row1.append("W ");
                    }
                }
                else if(i < (mWallSize - 1U))
                {
                    for(unsigned short i = 0U; i < mWallSize; i++)
                    {
                        if((i == 0U) || (i == mWallSize - 1U))
                        {
                            row1.append("W ");
                        }
                        else
                        {
                            row1.append("  ");
                        }
                    }
                }
                else
                {
                    for(unsigned short i = 0U; i < mWallSize; i++)
                    {
                        if((i == 0U) || (i == mWallSize - 1U))
                        {
                            row1.append("W ");
                        }
                        else if(i == (mWallSize/2))
                        {
                            row1.append("o ");
                        }
                        else
                        {
                            row1.append("G ");
                        }
                    }
                }
                mpGameWall[i] = new string(row1);
            }
        }
    }
    else
    {
        //Do nothing
    }
}

void BallBrickGame::destroyWall()
{
    for(unsigned short i = 0; i < mWallSize; i++)
    {
        delete [] mpGameWall[i];
    }
    delete [] mpGameWall;

    mpGameWall = nullptr;
}

bool BallBrickGame::validateRow(unsigned short row_val) const
{
    return ((row_val != 0) && (row_val < (mWallSize - 1u)));
}

bool BallBrickGame::validateCol(unsigned short col_val) const
{
    return ((col_val != 0) && (col_val < (mWallSize - 1U)));
}

void BallBrickGame::displayGame() const
{
    for(unsigned short i = 0U; i < mWallSize; i++)
    {
        cout << *mpGameWall[i] << endl;
    }
}

void BallBrickGame::playGame()
{
    while (gameStatus() == 0)
    {
        string ball_direction = "";

        while((ball_direction != "ST") && (ball_direction != "LD") && (ball_direction != "RD"))
        {
            cout << "Enter the direction in which the ball need to traverse :";
            cin >> ball_direction;
        }

        const auto ball_pos = mpGameWall[mWallSize - 1U]->find("o ");

        mBallCount--;

        if(ball_direction == "ST")
        {
            for(unsigned short i = (mWallSize - 2U); i > 0U; i-- )
            {
                const auto val_at_pos = mpGameWall[i]->at(ball_pos);
                if(val_at_pos > '0' && val_at_pos <= '9')
                {
                    mpGameWall[i]->at(ball_pos) = (val_at_pos - 1) == '0' ? ' ' : (val_at_pos - 1);
                    mBallCount++;
                    break;
                }
            }
        }
        else if(ball_direction == "LD")
        {
            for(unsigned short i = (mWallSize - 2U), j = (ball_pos - 2); (i > 0U) && (j > 0); i-- )
            {
                const auto val_at_pos = mpGameWall[i]->at(j);
                if((val_at_pos > '0') && (val_at_pos <= '9'))
                {
                    mpGameWall[i]->at(j) = (val_at_pos - 1) == '0' ? ' ' : (val_at_pos - 1);
                    mBallCount++;
                    break;
                }
                else
                {
                    j = j - 2;
                }
            }
        }
        else if(ball_direction == "RD")
        {
            for(unsigned short i = (mWallSize - 2U),j = (ball_pos + 2); (i > 0U) && (j < ((mWallSize*2) - 2)); i-- )
            {
                const auto val_at_pos = mpGameWall[i]->at(j);
                if((val_at_pos > '0') && (val_at_pos <= '9'))
                {
                    mpGameWall[i]->at(j) = (val_at_pos - 1) == '0' ? ' ' : (val_at_pos - 1);
                    mBallCount++;
                    break;
                }
                else
                {
                    j = j + 2;
                }
            }
        }

        displayGame();
    }
}

int BallBrickGame::gameStatus() const
{
    if(mBallCount == 0)
    {
        cout << "you lose GAME OVER..!!" << endl;
        return -1; //loose
    }
    else
    {
        for(unsigned short i = 1U; i < (mWallSize - 1U); i++)
        {
            for(unsigned short j = 1U; j < (mpGameWall[i]->length() - 2U); j++)
            {
                const auto ch = mpGameWall[i]->at(j);
                if((ch > '0') && (ch <= '9'))
                {
                    return 0; //In progress
                }
            }
        }

        cout << "You win HURRAY..!!" << endl;
        return 1; //Win
    }
}
