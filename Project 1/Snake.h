
#ifndef __CS_32__snake__
#define __CS_32__snake__


class Pit;
class Snake
{
public:
    // Constructor
    Snake(Pit* pp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    
private:
    Pit* m_pit;
    int  m_row;
    int  m_col;
};


#endif /* defined(__CS_32__snake__) */
