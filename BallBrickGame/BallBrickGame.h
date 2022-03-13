#ifndef BALLBRICKGAME_H
#define BALLBRICKGAME_H

#include <string>

class BallBrickGame
{
public:
    BallBrickGame();
    ~BallBrickGame();

    void setWallSize();
    void setBallCount();
    void addBricks();

    unsigned short getWallSize() const;
    void displayGame() const;
    void playGame();

private:
    unsigned short mWallSize = 0U;
    unsigned short mBallCount = 0U;
    std::string **mpGameWall= nullptr;

    void createWall();
    void destroyWall();
    bool validateRow(unsigned short row_val) const;
    bool validateCol(unsigned short col_val) const;
    int gameStatus() const;
};

#endif // BALLBRICKGAME_H
