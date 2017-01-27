class Character
{
public:
    Character(string nam)
    {
        m_name=nam;
    }
    string name() const
    {
        return m_name;
    }
    virtual void printWeapon()const =0;
    virtual string attackAction() const
    {
        return "rushes toward the enemy";
    };
    virtual ~Character()
    {
        
    }
private:
    string m_name;
};

class Dwarf: public Character
{
public:
    Dwarf(string nam):Character(nam)
    {}
    virtual void printWeapon() const
    {
        cout<<"an axe";
    }
    virtual ~Dwarf()
    {
        cout<<"Destroying "<< name()<<" the dwarf"<<endl;
    }
};

class Elf:public Character
{
public:
    Elf(string nam, int numOfArrows):Character(nam)
    {
        m_num=numOfArrows;
    }
    virtual void printWeapon() const
    {
        cout<<"a bow and quiver of "<<m_num<<" arrows";
    }
    virtual ~Elf()
    {
        cout<<"Destroying "<< name() <<" the elf"<<endl;
    }
    
private:
    int m_num;
};

class Boggie:public Character
{
public:
    Boggie(string nam):Character(nam)
    {}
    virtual void printWeapon() const
    {
        cout<<"a short sword";
    }
    virtual string attackAction () const
    {
        return "whimpers";
    }
    virtual ~Boggie()
    {
        cout<<"Destroying "<< name() <<" the boggie"<<endl;
    }
};
