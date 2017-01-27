#include "Actor.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include <list>
#include <cstdlib>
#include <ctime>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

//Actor

Actor:: Actor(int imageID, int startX, int startY, StudentWorld* myWorld,Direction startDirection):GraphObject(imageID,startX,startY,startDirection)
{
    
    stdWld=myWorld;
    
    if (imageID!=IID_EXIT) {
        GraphObject::setVisible(true);
    }
 
    m_health=1;
};

bool Actor::isKlepto() const
{
    return false;
}

void Actor::doSomething()
{
    return;
};

StudentWorld* Actor::getWorld() const
{
    return stdWld;
}


int Actor::getHealth() const
{
    return m_health;
}


void Actor::pushed(Direction dir)
{
    return;
}

bool Actor::blockActor() const
{
    return true;
}

bool Actor::blockBoulder() const
{
    return true;
}

bool Actor::isExit() const
{
    return false;
}

void Bullet::moveToADir(int x, int y, Direction dir)
{
    switch (dir) {
        case GraphObject::right:
            moveTo(x+1, y);
            break;
        case GraphObject::left:
            moveTo(x-1, y);
            break;
        case GraphObject::down:
            moveTo(x, y-1);
            break;
         case GraphObject::up:
            moveTo(x, y+1);
            break;
            
        default:
            break;
    }
}

void Actor::attacked()
{
    return;
}


bool Actor::eatBullet() const
{
    return false;
}

bool Actor::isBoulder() const
{
    return false;
}

bool Actor::eatBoulder() const
{
    return false;
}

void Actor::setDead()
{
    m_health=0;
}

void Actor::setvisible()
{
    return;
}

bool Actor::isGoodie() const
{
    return false;
}

//mobileActor
mobileActor::mobileActor(int imageID, int startX, int startY, StudentWorld* myWorld,int health,Direction startDirection):
Actor( imageID, startX, startY, myWorld,startDirection )
{m_health=health;}

int mobileActor::getHealth() const
{
    return m_health;
}

void mobileActor::attacked()
{
    m_health-=2;
    
}

void mobileActor::recover()
{
    m_health=20;
}

bool mobileActor::eatBullet() const
{
    return true;
}

void mobileActor::setDead()
{
    m_health=0;
}



bool mobileActor::LegalMove(int &x,int &y,Direction dir) 
{
    int tempX=x,tempY=y;
    nextPoint(tempX, tempY, dir);
    list<Actor*> temp=getWorld()->Ref(tempX, tempY);
    list<Actor*>::const_iterator it;
    it=temp.begin();
    while (it!=temp.end()) {
        if ((*it)!= nullptr&&(*it)->blockActor())
        {
            return false;
        }
        it++;
    }
    if (tempX==getWorld()->getPlayer()->getX()&&tempY==getWorld()->getPlayer()->getY()) {
        return false;
    }
    x=tempX;
    y=tempY;
    return true;
}


//implement Player member functions

void Player::doSomething()
{
    if (getHealth()<=0) {
        return;
    }
    int ch;
    if (getWorld()->getKey(ch))
    {
            int x=getX();
            int y=getY();
        // user hit a key this tick!
        switch (ch)
        {  
            case KEY_PRESS_LEFT:
               setDirection(left);
                pushBoulder(x-1,y,left);
                if (LegalMove(x,y,left)) {
                    moveTo(x,y);
                }
                //if the Player 
                break;
            case KEY_PRESS_RIGHT:
                setDirection(right);
                pushBoulder(x+1,y,right);
                if (LegalMove(x,y,right)) {
                    moveTo(x,y);
                }
                break;
            case KEY_PRESS_UP:
                setDirection(up);
                pushBoulder(x,y+1,up);
                if (LegalMove(x,y,up)) {
                    moveTo(x,y);
                }
                break;
            case KEY_PRESS_DOWN:
                setDirection(down);
                pushBoulder(x,y-1,down);
                if (LegalMove(x,y,down)) {
                    moveTo(x,y);
                }
                break;
            case KEY_PRESS_SPACE:
                if (m_ammunition>0) {
                    int coorX=getX(),coorY=getY();
                    nextPoint(coorX, coorY, getDirection());
                    getWorld()->creatABullet(coorX, coorY, getDirection());
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    m_ammunition--;
                    // ... add a Bullet in the square in front of the Player...;
                    //fire the bullet
                    //play sound
                }
                break;
            case KEY_PRESS_ESCAPE:
                setDead();
                break;
               
        }
    }
}

void Actor::nextPoint(int &x, int &y, Direction dir) const
{
    switch (dir) {
        case left:
            x--;
            break;
        case right:
            x++;
            break;
        case up:
            y++;
            break;
        case down:
            y--;
            break;
        default:
            break;
    }
}


Player::Player(int startX, int startY,StudentWorld *myWorld):mobileActor(IID_PLAYER, startX, startY,myWorld,20,right)
{
    
    m_ammunition=20;
    
    
}


int Player::getAmm() const
{
    return m_ammunition;
}

void Player::getAmmo()
{
    m_ammunition+=20;
}


void Player::pushBoulder(int x,int y,Direction dir)
{
    list<Actor*> temp=getWorld()->Ref(x, y);
    list<Actor*>::const_iterator it;
    it=temp.begin();
    while (it!=temp.end()) {
        if((*it)->isBoulder())
        {
            (*it)->pushed(dir);
            return;
        }
        it++;
    }

}

void Player::attacked()
{
    mobileActor::attacked();
    if (getHealth()>0) {
        getWorld()->playSound(SOUND_PLAYER_IMPACT);
    }
    else
        getWorld()->playSound(SOUND_PLAYER_DIE);
}


//Wall
Wall::Wall(int startX, int startY, StudentWorld* myWorld):Actor(IID_WALL, startX, startY,myWorld)
{}

bool Wall::eatBullet() const
{
    return true;
}
//Boulders
Boulders::Boulders(int startX, int startY, StudentWorld* myWorld):mobileActor(IID_BOULDER, startX, startY,myWorld,10)
{}

void Boulders::pushed(Direction dir)
{   bool b=true;
    Actor* p=nullptr;
    int x=getX();
    int y=getY();
    b=LegalMove(x, y, dir, p);
    if (b) {
        moveTo(x, y);
        if (p!=nullptr) {
            setDead();
            getWorld()->killAHole(p);
        }
        //if the boulder has the same position as the hole, kill the hole
    }
}

bool Boulders::LegalMove(int &x,int &y, Direction dir,Actor*& pnt)const
{
    int tempX=x,tempY=y;
    Actor::nextPoint(tempX, tempY, dir);
    list<Actor*> temp=getWorld()->Ref(tempX, tempY);
    list<Actor*>::const_iterator it;
    it=temp.begin();
    while (it!=temp.end()) {
        if ((*it)!=nullptr &&(*it)->blockBoulder()) {
            return false;
        }
        if ((*it)!=nullptr&&(*it)->eatBoulder()) {
            pnt=(*it);
        }
        it++;
    }
    x=tempX;
    y=tempY;
    return true;
}


bool Boulders::isBoulder() const
{
    return true;
}


//Bullet
Bullet::Bullet(int startX, int startY, StudentWorld *myWorld, Direction dir): Actor(IID_BULLET,startX,startY,myWorld,dir)
{}


bool Bullet::legalMove(int x,int y, Actor* &p) const
{
    list<Actor*> temp=getWorld()->Ref(x, y);
    list<Actor*>::const_iterator it;
    it=temp.begin();
    if (x==getWorld()->getPlayer()->getX()&&y==getWorld()->getPlayer()->getY())
    {
    p=getWorld()->getPlayer();
        return false;
        }
    if (temp.empty()) {
        return true;
    }
    while (it!=temp.end()) {
        if ((*it)->eatBullet()) {
            
            p=(*it);
            return false;
        }
        it++;
    }
    return true;
}

void Bullet::doSomething()
{
    if (getHealth()<=0) {
        return;
    }
    Actor* pnt=nullptr;
    if ((this!=pnt)&&(!legalMove(getX(), getY(),pnt))&& (pnt!=nullptr))
    {
        pnt->attacked();
        setDead();
        return;
    }
    moveToADir(getX(), getY(), getDirection());
    if ( (this!=pnt)&&(!legalMove(getX(), getY(),pnt))&&(pnt!=nullptr))
    {
        pnt->attacked();
        setDead();
    }

    
}

bool Bullet::blockActor() const
{
    return false;
}

bool Bullet::eatBullet() const
{
    return false;
}



//Implement hole
Hole::Hole(int startX,int startY,StudentWorld *myWorld):Actor(IID_HOLE,startX,startY,myWorld)
{}

bool Hole::blockBoulder() const
{
    return false;
}

bool Hole::eatBoulder() const
{
    return true;
}


//implement pickupable
pickUpable::pickUpable(int imageID, int startX, int startY, StudentWorld* myworld):Actor(imageID,startX,startY,myworld)
{}

bool pickUpable::blockActor() const
{
    return false;
}

bool pickUpable::eatenByPlayer() const
{
    if (getX()==getWorld()->getPlayer()->getX() && getY()==getWorld()->getPlayer()->getY()) {
        return true;
    }
    return false;
}

bool pickUpable::something(int score)
{
    if (eatenByPlayer())
    {
        getWorld()->increaseScore(score);
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        return true;
    }
    return false;
}
//implement jewel
Jewel::Jewel(int startX, int startY, StudentWorld* myWorld):pickUpable(IID_JEWEL,startX,startY,myWorld)
{}

void Jewel::doSomething()
{
    if (getHealth()<=0)
    {
        return;
    }
    something(50);
    
}


Jewel::~Jewel()
{
    getWorld()->decJewel();
}


//Exit implementation
Exit::Exit(int startX,int startY,StudentWorld* myWorld):Actor(IID_EXIT,startX,startY,myWorld)
{m_visible=false;}

bool Exit::blockActor() const
{
    return false;
}

bool Exit::blockBoulder() const
{
    return m_visible;
}


void Exit::setvisible()
{
    m_visible=true;
    GraphObject::setVisible(true);
    getWorld()->playSound(SOUND_REVEAL_EXIT);
}

bool Exit::isExit() const
{
    return true;
}

void Exit::doSomething()
{
    if (m_visible&&getX()==getWorld()->getPlayer()->getX()&& getY()==getWorld()->getPlayer()->getY())
    {getWorld()->playSound(SOUND_FINISHED_LEVEL);
        getWorld()->levelcompleted();
        getWorld()->increaseScore(2000);
    }
}

//Goodies implementation
Goodies::Goodies(int imageID,int startX,int startY, StudentWorld* myWorld):pickUpable(imageID,startX,startY,myWorld)
{}
bool Goodies::isGoodie() const
{
    return true;
}

//implement restoreHealthGoodie
restoreHealthGoodie::restoreHealthGoodie(int startX,int startY, StudentWorld * myWorld):Goodies(IID_RESTORE_HEALTH,startX,startY,myWorld)
{}
void restoreHealthGoodie::doSomething()
{
    if (getHealth()<=0)
    {
        return;
    }
    if (something(500))
    
        getWorld()->getPlayer()->recover();
    
}

//implement extra life goodie
extraLifeGoodie:: extraLifeGoodie(int startX,int startY, StudentWorld* myWorld):Goodies(IID_EXTRA_LIFE,startX,startY,myWorld)
{}

void extraLifeGoodie::doSomething()
{
    if (getHealth()<=0)
    {
        return;
    }
    if (something(1000))
     getWorld()->incLives();
    
  }

//implement Ammo
Ammo::Ammo(int startX,int startY, StudentWorld * myWorld):Goodies(IID_AMMO,startX,startY,myWorld)
{}

void Ammo::doSomething()
{
    if (getHealth()<=0)
    {
        return;
    }
    if (something(100))
        getWorld()->getPlayer()->getAmmo();
}

//implement Robot
Robot::Robot(int imageID, int startX, int startY, StudentWorld* myWorld,int health,Direction startDirection):mobileActor(imageID,startX,startY,myWorld,health,startDirection)
{ticks=1;}

void Robot::setTick(int tick)
{
    if (tick<3) {
        tick=3;
    }
    ticks=tick;
}

int Robot::getTick() const
{
    return ticks;
}

bool Robot::isObstacle(int x,int y) const
{
    list<Actor*> temp=getWorld()->Ref(x, y);
    list<Actor*>::iterator it=temp.begin();
    while (it!=temp.end()) {
        if ((*it)->eatBullet()) {
            return true;
        }
        it++;
    }
    return false;
}

bool Robot::fire(GraphObject::Direction dir)
{  int x=getX();
   int y=getY();
    do
    {
        nextPoint(x, y, dir);
        if ((getWorld()->getPlayer()->getX()==x)&&(getWorld()->getPlayer()->getY()==y))
        {   int tempX=getX();
            int tempY=getY();
            nextPoint(tempX, tempY, dir);
            getWorld()->creatABullet(tempX,tempY, dir);
            getWorld()->playSound(SOUND_ENEMY_FIRE);
            return true;
        }
    }
    while (!isObstacle(x, y)) ;
    return false;
}

void Robot::attacked()
{
    mobileActor::attacked();
    if (getHealth()>0) {
        getWorld()->playSound(SOUND_ROBOT_IMPACT);
    }
    else
    {getWorld()->playSound(SOUND_ROBOT_DIE);
        dying();}
}
//implement snarlBot
SnarlBot::SnarlBot(int startX, int startY, StudentWorld* myWorld, Direction dir):Robot(IID_SNARLBOT,startX,startY,myWorld,10,dir)
{setTick((28-getWorld()->getLevel())/4);
    crt_ticks=getTick();
}

void SnarlBot::doSomething()
{
    if (crt_ticks>=1) {
        crt_ticks--;
        return;
    }
    if (getHealth()<=0) {
        return;
    }
    crt_ticks=getTick();
    if(fire(getDirection()))
        return;
    int x=getX();
    int y=getY();
    switch (getDirection()) {
        case GraphObject::left:
            if (LegalMove(x, y,left))
                moveTo(x, y);
            else
                setDirection(right);
            break;
        case GraphObject::right:
            if (LegalMove(x, y,right))
                moveTo(x, y);
            else
                setDirection(left);
            break;
        case GraphObject::down:
            if (LegalMove(x, y,down))
                moveTo(x, y);
            else
                setDirection(up);
            break;
        case GraphObject::up:
            if (LegalMove(x,y,up))
                moveTo(x, y);
            else
                setDirection(down);
           
            break;
        default:
            break;
    }
}

void SnarlBot::dying()
{
    getWorld()->increaseScore(100);
}
//implement kleptoBot
KleptoBot::KleptoBot(int startX, int startY, StudentWorld* myWorld,int imageID,int health):Robot(IID_KLEPTOBOT,startX,startY,myWorld,health,right)
{setTick((28-getWorld()->getLevel())/4);
    crt_ticks=getTick();
    pickedUpGoodie=false;
    p=nullptr;
    distanceBeforeTurn();
}
void KleptoBot::distanceBeforeTurn()
{
    distanceBeforeTurning=rand()%6+1;
}

void KleptoBot::pickupAGoodie()
{   list<Actor*> temp=getWorld()->Ref(getX(), getY());
    list<Actor*>::iterator it=temp.begin();
    int seed=rand()%10;
    while (it!=temp.end()) {
        if ((*it)->isGoodie()&&seed==0) {
            (*it)->setVisible(false);
            getWorld()->playSound(SOUND_ROBOT_MUNCH);
            p=(*it);
            pickedUpGoodie=true;
        }
        it++;
    }

}

bool KleptoBot::getPick() const
{
    return pickedUpGoodie;
}

void KleptoBot::decDisBT()
{
    distanceBeforeTurning--;
}

void KleptoBot::doSomething()
{
    
    if (crt_ticks>=1) {
        crt_ticks--;
        return;
    }setCurrentTick(getTick());
    if (getHealth()<=0) {
        return;
    }
    someThing();
}



    
void KleptoBot::someThing()
{
        if (!pickedUpGoodie) {
            pickupAGoodie();
            if (pickedUpGoodie) {
                return;
            }
        }
        bool moved=false;
        if (distanceBeforeTurning!=0)
        {
            
            int x=getX();
            int y=getY();
            
            switch (getDirection())
            {
                case GraphObject::left:
                    if (LegalMove(x, y, left))
                        moveTo(x, y);
                        moved=true;
                    break;
                case GraphObject::right:
                    if (LegalMove(x, y,right))
                        moveTo(x, y);
                    moved=true;
                    break;
                case GraphObject::down:
                    if (LegalMove(x, y,down))
                        moveTo(x, y);
                    moved=true;
                    break;
                case GraphObject::up:
                    if (LegalMove(x, y,up))
                        moveTo(x, y);
                    moved=true;
                    break;
                default:
                    break;
            }
            
        }
        if (moved) {
            if (p!=nullptr) {
                p->moveTo(getX(), getY());
            }
            
            decDisBT();
            return;
        }
        int x=getX();
        int y=getY();
        distanceBeforeTurn();
        Direction dir[4]={left,right,up,down};
        int rdm=rand()%4;
        int crdm=rdm+1;
        setDirection(dir[rdm]);
        if (LegalMove(x, y, getDirection())) {
            moveTo(x, y);
            return;
        }
        
        while (crdm%4!=rdm) {
            if (LegalMove(x, y, dir[crdm%4]))
            {
                setDirection(dir[crdm%4]);
                moveTo(x, y);
                if (p!=nullptr) {
                    p->moveTo(x, y);
                }
                
                break;
            }
            crdm++;
        }
        
    }

int KleptoBot::getCrtTick()const
{
    return crt_ticks;
}

void KleptoBot::decCrtTick()
{
    crt_ticks--;
}

Actor* KleptoBot::getPointer()
{
    return p;
}

bool KleptoBot::isKlepto() const
{
    return true;
}

bool KleptoBot::Regular() const
{
    return true;
}

void KleptoBot::dying()
{   if (getPointer()!=nullptr)
    getPointer()->setVisible(true);
    if (Regular())
    getWorld()->increaseScore(10);
    else
    getWorld()->increaseScore(20);
}

void KleptoBot::setCurrentTick(int tick)
{
    crt_ticks=tick;
}
//implement angrykleptoBot
AngryKleptoBot::AngryKleptoBot(int startX, int startY, StudentWorld* myWorld):KleptoBot(startX,startY,myWorld,IID_ANGRY_KLEPTOBOT,8)
{}

void AngryKleptoBot::doSomething()
{
    if (getCrtTick()>=1) {
        decCrtTick();
        return;
    }
    setCurrentTick(getTick());
    if (getHealth()<=0) {
        return;
    }
    if(fire(getDirection()))
        return;
    someThing();
    
}

bool AngryKleptoBot::Regular() const
{
    return false;
}



//implement factory
KleptoBotFactory:: KleptoBotFactory(int startX,int startY, StudentWorld* myWorld,bool regular):Actor(IID_ROBOT_FACTORY,startX,startY,myWorld)
{isRegular=regular;}
void KleptoBotFactory::doSomething()
{
    int U=getY()+3,D=getY()-3,L=getX()-3,R=getY()+3;
    if(U>14)
        U=14;
    if (D<0)
        D=0;
    if  (L<0)
        L=0;
    if (R>14)
        R=14;
    int counter=0;
    for (int k=L; k<=R; k++) {
        for (int j=D; j<=U; j++) {
            counter+=robotCount(k, j);
        }
    }
    int seed=rand()%50;
    if (counter<3 && (!robotCount(getX(), getY()))&&seed==0) {
        if (isRegular)
            getWorld()->createAKleptoBot(getX(), getY());
         else
             getWorld()->createAngryKleptoBot(getX(), getY());
        getWorld()->playSound(SOUND_ROBOT_BORN);
    }
        }

bool KleptoBotFactory::robotCount(int x, int y)
{
    list<Actor*> temp=getWorld()->Ref(x, y);
    list<Actor*>::iterator it=temp.begin();
    while (it!=temp.end()) {
        if ((*it)->isKlepto())
            return true;
        it++;
    }
    return false;
}

bool KleptoBotFactory::eatBullet() const
{
    list<Actor*> temp=getWorld()->Ref(getX(),getY());
    list<Actor*>::const_iterator it=temp.begin();
    while (it!=temp.end()) {
        if ((*it)->isKlepto()) {
            return false;
        }
        it++;
    }
    return true;
}
