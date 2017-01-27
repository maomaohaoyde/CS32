#include "StudentWorld.h"
#include <string>
#include <sstream>
#include <iomanip>
#include "Actor.h"
#include <list>
using namespace std;


GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

StudentWorld:: StudentWorld(std::string assetDir): GameWorld(assetDir)
{
    jewelCounter=0;
    levelCount=-1;
    levelcompleted();
}
// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
int StudentWorld::toLoadALevel()
{   ostringstream oss;
    if(levelCompleted) levelCount++;
    oss<<"level";
    oss.fill('0');
    oss<<setw(2)<<levelCount;
    oss<<".dat";
    string	curLevel	=	oss.str();
    
    Level	lev(assetDirectory());
    Level::LoadResult result	=	lev.loadLevel(curLevel);
    if (result	==	Level::load_fail_file_not_found)	return -1;
       if (result	==	Level:: load_fail_bad_format)
        return -2;
    Level::MazeEntry item;

    for (int x=0; x<VIEW_WIDTH; x++)
    {
        for (int y=0; y<VIEW_HEIGHT; y++)
        {
            item =	lev.getContentsOf(x,y);
            switch (item)
            {
                case Level::player:
                    m_player= new Player(x,y,this);
                    break;
                case Level::wall:
                    Actor* W;
                    W=new Wall(x,y,this);
                    m_actors.push_back(W);
                    break;
                case Level::hole:
                    Actor* H;
                    H=new Hole(x,y,this);
                    m_actors.push_back(H);
                    break;
                case Level::jewel:
                    //more code to be written
                    Actor* J;
                    J=new Jewel(x,y,this);
                    m_actors.push_back(J);
                    jewelCounter++;
                    break;
                case Level::boulder:
                    Actor *B;
                    B=new Boulders(x,y,this);
                    m_actors.push_back(B);
                    break;
                case Level::exit:
                    Actor *E;
                    E=new Exit(x,y,this);
                    m_actors.push_back(E);
                    break;
                    
                case Level::restore_health:
                    Actor *R;
                    R=new restoreHealthGoodie(x,y,this);
                    m_actors.push_back(R);
                    break;
                case Level::ammo:
                    Actor *A;
                    A=new Ammo(x,y,this);
                    m_actors.push_back(A);
                    break;
                    
                case Level::horiz_snarlbot:
                    Actor* HS;
                    HS=new SnarlBot(x,y,this,GraphObject::right);
                    m_actors.push_back(HS);
                    break;
                
                case Level::vert_snarlbot:
                    Actor* VS;
                    VS=new SnarlBot(x,y,this,GraphObject::down);
                    m_actors.push_back(VS);
                    break;
                case Level::extra_life:
                    Actor *EL;
                    EL=new extraLifeGoodie(x,y,this);
                    m_actors.push_back(EL);
                    break;
                case Level::kleptobot_factory:
                    Actor* KF;
                    KF=new KleptoBotFactory(x,y,this,true);
                    m_actors.push_back(KF);
                    break;
                case Level::angry_kleptobot_factory:
                    Actor* AKF;
                    AKF=new KleptoBotFactory(x,y,this,false);
                    m_actors.push_back(AKF);
                default:
                    break;
            }
        }
    }
    m_bonus=1000;
    
    return 0;
}

void StudentWorld::updateDisplayText()
{
    ostringstream oss;
    int score=getScore();
    int level= getLevel();
    unsigned int bonus= m_bonus;
    int livesLeft=getLives();
    int health=(m_player->getHealth())*5;
    int ammunition=m_player->getAmm();
    oss<<"Score: ";
    oss.fill('0');
    oss<<setw(7)<<score;
    oss<<"  Level: ";
    oss<<setw(2)<<level;
    oss<<"  Lives: ";
    oss.fill(' ');
    oss<<setw(2)<<livesLeft;
    oss<<"  Health: ";
    oss<<setw(3)<<health<<"%";
    oss<<"  Ammo: ";
    oss<<setw(3)<<ammunition;
    oss<<"  Bonus: ";
    oss<<setw(4)<<bonus;
    string s=oss.str();
    setGameStatText(s);
}

void StudentWorld::removeDeadObjects()
{
    list<Actor*>::iterator it;
    it=m_actors.begin();
    while (it!=m_actors.end()) {
        if ((*it)->getHealth()<=0) {
            
                
            delete *it;
            m_actors.erase(it);
                it--;
    
        }
        it++;
    }
}

void StudentWorld::reduceLevelBonusByOne()
{
    if (m_bonus>0) {
        m_bonus--;
    }
}

bool StudentWorld::AllOfJewelsCollected()const
{
    return (jewelCounter==0);
}

void StudentWorld::levelcompleted()
{
    levelCompleted=true;
}


int StudentWorld:: init()
{
    
    
    int a=toLoadALevel();levelCompleted=false;
    if (a==-2) {
        cerr<<"can't load the level file!";
        return GWSTATUS_LEVEL_ERROR;
    }
    if (a==-1) {
        return GWSTATUS_PLAYER_WON;
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld:: move()
{
		  // This code is here merely to allow the game to build, run, and terminate after hitting enter a few times
    updateDisplayText();
    m_player->doSomething();
    
        
    
    list<Actor*>::iterator it;
    it=m_actors.begin();
    while (it!= m_actors.end()) {
        
        (*it)->doSomething();
        
        if (m_player->getHealth()<=0)
        {
            decLives();
            return GWSTATUS_PLAYER_DIED;
        }
        it++;
    }
    if (m_player->getHealth()>0) {
        m_player->doSomething();
    }
    
    reduceLevelBonusByOne();
    removeDeadObjects();
    
    if (jewelCounter==0) {
        list<Actor*>::const_iterator it;
        it=m_actors.begin();
        while (it!=m_actors.end()) {
            if ((*it)->isExit()&&(!(*it)->GraphObject::isVisible())) {
                (*it)->setvisible();
            }
            it++;
        }
        
        
    }
    
    if (levelCompleted) {
        increaseScore(m_bonus);
        return GWSTATUS_FINISHED_LEVEL;
    }
        
    
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld:: cleanUp()
{
    delete m_player;
    list<Actor*>::iterator it=m_actors.begin();;
    list<Actor*>::iterator temp;
    
    while (it!=m_actors.end()) {
        if (*it!=nullptr) {
            temp=it;
             delete (*temp);
        m_actors.erase(temp);
        }
        it++;
    }
    
    
}

void StudentWorld::creatABullet(int x, int y, Actor::Direction dir)
{
    Actor* p;
    p=new Bullet(x,y,this,dir);
    m_actors.push_front(p);
    
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}

list<Actor*> StudentWorld::Ref(int x,int y) const
{
    list<Actor*> atThisPoint;
    list<Actor*>::const_iterator it;
    it=m_actors.begin();
    while (it!=m_actors.end())
    {if ((*it)->getX()==x && (*it)->getY()==y)
        atThisPoint.push_back(*it);
        it++;
    }
    return atThisPoint;
}

void StudentWorld::killAHole(Actor* pnt)
{
    list<Actor*>::iterator it;
    it=m_actors.begin();
    while (it!=m_actors.end()) {
        if (*it==pnt) {
            delete pnt;
            m_actors.erase(it);
            return;
        }
        it++;
    }
}

Player* StudentWorld::getPlayer()
{
    return m_player;
}

void StudentWorld::decJewel()
{
    jewelCounter--;
}

void StudentWorld:: createAKleptoBot(int x,int y)
{
    Actor* K;
    K=new KleptoBot(x,y,this);
    m_actors.push_back(K);
}
void StudentWorld:: createAngryKleptoBot(int x,int y)
{
    Actor *A;
    A=new AngryKleptoBot(x,y,this);
    m_actors.push_back(A);
}