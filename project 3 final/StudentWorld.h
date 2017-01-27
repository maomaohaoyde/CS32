#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include <string>
#include <list>
#include "Level.h"
#include "Actor.h"
using namespace std;

class Actor;
class Player;
// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld: public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    
    int toLoadALevel();
    
    void updateDisplayText();
    
    void removeDeadObjects();
    
    void reduceLevelBonusByOne();
    
    bool AllOfJewelsCollected() const;
    
    void levelcompleted();
    
    void creatABullet(int x, int y, Actor::Direction dir);
    
    void killAHole(Actor * pnt);
    
    Player* getPlayer();
    
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    list<Actor*> Ref(int x, int y) const;
    void decJewel();
    
    virtual ~StudentWorld();
    
    void createAKleptoBot(int x,int y);
    void createAngryKleptoBot(int x, int y);
    
private:
    list<Actor*> m_actors;
    Player* m_player;
    unsigned int m_bonus;
    int jewelCounter;
    bool levelCompleted;
    int levelCount;

};



#endif // STUDENTWORLD_H_
