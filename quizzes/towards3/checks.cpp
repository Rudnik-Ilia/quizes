#include <iostream>

enum Type 
{
    NONE, 
    BLACK, 
    WHITE 
};
enum Direction 
{ 
    UP_LEFT, 
    UP_RIGHT, 
    DOWN_LEFT, 
    DOWN_RIGHT 
};

class Player
{
    public:
        Player(Type type): type(type)
        {

        }

        Type getType()
        {
            return type;
        }

    private:
        Type type;
};

class Piece 
{
    public:
        Piece(Type type = NONE) : type(type) {}

        Type getType()
        {
            return type;
        }

        bool isDamka() 
        {
            return damka;
        }

        void makeDamka() 
        {
            damka = true;
        }

    private:
        Type type;
        bool damka = false;
};

class Board
{
    public:
        Board()
        {

        }

    private:
        size_t size = 4;
};





int main()
{
    
    Player p1(BLACK);
    Player p2(WHITE);


    std::cout << (p1.getType() == BLACK )<< std::endl;
    std::cout << (p2.getType() == WHITE) << std::endl;


    return 0;
}