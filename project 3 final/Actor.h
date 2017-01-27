#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"

class StudentWorld;

class Actor:public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* myWorld,Direction startDirection=none);
    virtual void doSomething();
    StudentWorld* getWorld() const;
    
    virtual int getHealth() const;
    virtual void pushed(Direction x);
    virtual bool blockActor() const;
    virtual bool blockBoulder() const;
    virtual bool isExit() const;
    virtual bool eatBullet() const;
    virtual void attacked();
    virtual bool isBoulder() const;
    virtual bool eatBoulder() const;
    virtual void setDead();
    virtual void setvisible();
    virtual bool isKlepto() const;
    virtual bool isGoodie() const;
    void nextPoint(int &x,int &y,Direction) const;
private:
    
    StudentWorld* stdWld;
    int m_health;
    
};

class mobileActor:public Actor
{
public:
    mobileActor(int imageID, int startX, int startY, StudentWorld* myWorld,int health,Direction startDirection=none);
    virtual int getHealth() const;
    virtual void attacked();
    virtual void recover();
    virtual bool eatBullet()const;
    virtual void setDead();
    virtual bool LegalMove(int &x,int &y,Direction dir);
    
private:
     int m_health;
};


class Player: public mobileActor
{
public:
    Player(int startX, int startY,StudentWorld *myWorld);
    virtual void doSomething();
    int getAmm() const;
    void pushBoulder(int x,int y, Direction dir);
    
    void getAmmo();
    virtual void attacked();
private:
    int  m_ammunition;
    };

class Wall: public Actor
{
public:
    Wall(int startX, int startY, StudentWorld* myWorld);
    virtual bool eatBullet() const;
private:
};

class Boulders:public mobileActor
{
public:
    Boulders(int startX, int startY, StudentWorld* myWorld);
    virtual void pushed(Direction x);
    virtual bool LegalMove(int &x,int &y,Direction dir,Actor*& pnt) const;
    virtual bool isBoulder() const;
};

class Bullet:public Actor
{
public:
    Bullet(int startX, int startY, StudentWorld *myWorld, Direction dir);
    virtual void doSomething();
    bool legalMove(int x,int y, Actor* &p)const;
    virtual bool eatBullet() const;
    virtual bool blockActor()const;
    void moveToADir(int x,int y,Direction dir);
};


class Hole:public Actor
{
public:
    Hole(int startX,int startY,StudentWorld *myWorld);
    virtual bool blockBoulder() const;
    virtual bool eatBoulder() const;
};

class pickUpable:public Actor
{
public:
    pickUpable(int imageID, int startX, int startY, StudentWorld* myworld);
    bool blockActor() const;
    bool eatenByPlayer() const;
    bool something(int score);
    
};
class Jewel:public pickUpable
{
public:
    Jewel(int startX,int startY, StudentWorld * myWorld);
    virtual void doSomething();
    virtual ~Jewel();
};

class Exit:public Actor
{
public:
    Exit(int startX, int startY, StudentWorld* myWorld);
    virtual bool blockBoulder() const;
    virtual bool blockActor() const;
    virtual void setvisible();
    virtual bool isExit() const;
    virtual void doSomething();
private:
    bool m_visible;
};

class Goodies:public pickUpable
{ public:
    Goodies(int imageID,int startX,int startY, StudentWorld * myWorld);
    virtual bool isGoodie() const;
};

class restoreHealthGoodie:public Goodies
{
public:
    restoreHealthGoodie(int startX,int startY, StudentWorld * myWorld);
    virtual void doSomething();
    
};

class extraLifeGoodie:public Goodies
{
  public:
    extraLifeGoodie(int startX,int startY, StudentWorld* myWorld);
    virtual void doSomething();
};

class Ammo:public Goodies
{
public:
    Ammo(int startX,int startY, StudentWorld * myWorld);
    virtual void doSomething();
};

class Robot: public mobileActor
{
public:
    Robot(int imageID, int startX, int startY, StudentWorld* myWorld,int health,Direction startDirection);
    void setTick(int tick);
    int getTick() const;
    bool fire(GraphObject::Direction dir);
    bool isObstacle(int x,int y) const;
    virtual void attacked();
    virtual void dying()=0;
    private:
    int ticks;
};

class SnarlBot:public Robot
{
public:
    SnarlBot(int startX, int startY, StudentWorld* myWorld,Direction dir);
    virtual void doSomething();
    virtual void dying();
    
private:
    int crt_ticks;
};

class KleptoBot:public Robot
{
public:
   KleptoBot(int startX, int startY, StudentWorld* myWorld, int imageID=IID_KLEPTOBOT, int health=5);
    void distanceBeforeTurn();
    void pickupAGoodie();
    virtual void doSomething();
    bool getPick() const;
    int getCrtTick() const;
    void decCrtTick();
    void decDisBT();
    void someThing();
    Actor* getPointer();
    virtual bool isKlepto() const;
    virtual bool Regular() const;
    virtual void dying();
    void setCurrentTick(int tick);
private:
    int crt_ticks;
    bool pickedUpGoodie;
    Actor* p;
    int distanceBeforeTurning;
};

class AngryKleptoBot: public KleptoBot
{public:
    AngryKleptoBot(int startX, int startY, StudentWorld* myWorld);
    virtual void doSomething();
    virtual bool Regular() const;

};

class KleptoBotFactory:public Actor
{
public:
    KleptoBotFactory(int startX,int startY, StudentWorld* myWorld,bool regular);
    virtual void doSomething();
    bool robotCount(int x, int y);
    virtual bool eatBullet() const;
private:
    bool isRegular;
};


#endif // ACTOR_H_


