#include <iostream>
#include <cstdlib>
#include <vector>
//#include <windows.h>

#define MAX_HEALTH 10

using namespace std;

class Point;
class Object;
class Entity;
class Player;
class Werewolf;
class Vampire;

//Namespace that contains all the game objects as well as functions to access and proccess these objects

//namespace game_objects


    // vector<Object> objects;     // Contains all the objects of the class object( Trees, Water & the healing potion )
    // vector<Entity*> npcs;       //Contains pointers to all the objects of the class entity (Maybe player as well(?)     )

    // Entity* find_entity(Point& pos)         //Returns the pointer to the entity that has posiotion pos if it doesn't exist returns NULL
    // {
    //     for(int j = 0; j < npcs.size(); j ++)
    //     {
    //         if(pos == npcs.at(j)->get_pos())
    //             return npcs.at(j);
    //     }
    //     return NULL;
    // }

    // Object* find_object(Point& pos)         //Returns the pointer to the object that has posiotion pos if it doesn't exist returns NULL
    // {
    //     for(int i = 0 ; i < objects.size(); i ++)
    //     {
    //         if(pos == objects.at(i).get_pos())
    //             return &objects.at(i);
    //     }
    //     return NULL;
    // }

    // bool is_free(Point& pos)                //Returns true if pos is free false if an object is occupying that position 
    // {
    //     if((find_entity(pos)== NULL) && (find_object(pos) == NULL))
    //         return true;
    //     else 
    //         return false;    
    // }

struct KeyState
{
    bool KEY_UP;
    bool KEY_DOWN;
    bool KEY_LEFT;
    bool KEY_RIGHT;
    bool KEY_SPACE;
    bool KEY_P;
};






// Declaration of 2D Point in Euclidean space
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Point {

    int x;
    int y;

    public:

        Point(int a = 0, int b = 0);
        ~Point();
        friend bool operator==(Point const& p1, Point const& p2);
        void set_x(int a);
        int get_x() const; 
        void set_y(int b);
        int get_y() const;
        void set_point(int x, int y);
        void set_point(Point& p);
        void print_point() const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of 2D point 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Point:: Point(int a, int b) : x(a) , y(b) {}
Point::~Point(){}
void Point::set_x(int a){ x = a; }
int Point::get_x() const { return x;}
void Point::set_y(int b) { y = b;}
int Point::get_y() const { return y;}
void Point::set_point(int a , int b)
{
    x=a;
    y=b;
}
void Point::set_point(Point& p)
{
    x = p.get_x();
    y = p.get_y();
}

void Point::print_point() const { cout <<"("<< x << "," << y << ")" ; }

bool operator==(Point const& p1, Point const& p2) {
    if((p1.get_x() == p2.get_x()) && (p1.get_y() == p2.get_y()))
        return true;
    else
        return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Decleration of object
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Object {

    const Point pos;
    const char type; //P for potion, T for tree, W for water 
    public:
        Object(Point& p, char t);
        ~Object();
        Point get_pos() const;
        char get_type() const;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Object
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Object::Object(Point& p, char t) : pos(p), type(t) {}
Object::~Object(){}
Point Object::get_pos() const {return pos;}
char Object::get_type() const {return type;}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Decleration of Entity 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Entity{

protected: 
    Point pos;
    const char type;      //Either 'P' for player 'W' for werewolf and 'V' for Vampire
public:
    Entity(Point& p, char t);
    ~Entity();
    Point get_pos() const;
    char get_type() const;
    virtual void move() = 0;
    virtual void heal() = 0;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Definition of Entity
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Entity:: Entity(Point& p, char t) : pos(p), type(t) {}
Entity::~Entity() {}
Point Entity::get_pos() const {return pos;}
char Entity::get_type() const {return type;}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Decleration of Player
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Player : public Entity{
    const char team;            // Either 'W' for werewolves or 'V' for Vampires
    int number_of_healing_spells;
    public:
        Player(Point& p, char tp, char tm);
        ~Player();
        void move(vector<Object> objs, vector<Entity*> npcs, KeyState keys);
        void heal(vector<Entity*> npcs);

};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Player
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Player::Player(Point& p, char tp, char tm) : Entity(p,tp), team(tm)
{
    number_of_healing_spells = 1;
}
Player::~Player() {};

void Player::heal(vector<Entity*> npcs){
    // if(team == 'W')
    // {
    //     Werewolf* were;
    //     for(int i = 0; i < npcs.size(); i++)
    //     {
    //         if(npcs.at(i)->get_type() == 'W')
    //         {
    //             were = npcs.at(i);
    //             were->set_health(MAX_HEALTH);
    //         }
    //     }
    // }  
    // else if (team == 'V')
    // {
    //     Vampire* vamp;
    //     for(int i = 0; i < npcs.size(); i++)
    //     {
    //         if(npcs.at(i)->get_type() == 'V')
    //         {
    //             vamp = npcs.at(i);
    //             vamp->set_health(MAX_HEALTH);
    //         }
    //     }

    // }  
} 

void Player::move(vector<Object> objs, vector<Entity*> npcs, KeyState keys)
{


    
}


//Declaration of Vampire
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Vampire : public Entity{
    int health;
    const int attack;
    const int defence;
    int potions;
    public:
        Vampire(Point& p, char tp, int hp , int at, int def,int pot);
        ~Vampire();
        int get_attack() const;
        int get_defence() const;
        int get_health() const;
        void set_health(int h);
        int get_potions() const;
        void set_potions(int p);

        void move();
        void heal();
        void attack_enemy();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Vampire
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Vampire::Vampire(Point& p , char tp, int hp,int at, int def, int pot) : Entity(p,tp), health(hp = MAX_HEALTH),
attack(at = rand() % 3 + 1), defence(def = rand() % 2 +1), potions(pot = rand() % 3) {};

Vampire::~Vampire() {};

int Vampire::get_attack() const {return attack;}

int Vampire::get_defence() const {return defence;}

int Vampire::get_health() const {return health;}

void Vampire::set_health(int h) {health = h;}

int Vampire::get_potions() const {return potions;}

void Vampire:: set_potions(int pot) { potions = pot;}

void Vampire::move()
{
    //To do...
}

void Vampire::heal()
{
    //To do
}

void Vampire::attack_enemy()
{
    //To do
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//Declaration of Werewolf
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Werewolf : public Entity{
    int health;
    const int attack;
    const int defence;
    int potions;
    public:
        Werewolf(Point& p,char tp,int hp,int at,int def,int pot);
        ~Werewolf();
        int get_attack() const;
        int get_defence() const;
        int get_health() const;
        void set_health(int h);
        int get_potions() const;
        void set_potions(int p);

        void move();
        void heal();
        void attack_enemy();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Werewolf
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Werewolf::Werewolf(Point& p , char tp, int hp,int at, int def, int pot) : Entity(p,tp), health(hp = MAX_HEALTH), 
attack(at = rand() % 3 + 1), defence(def = rand() % 2 +1), potions(pot = rand() % 3) {}

Werewolf::~Werewolf() {}

int Werewolf::get_attack() const {return attack;}

int Werewolf::get_defence() const {return defence;}

int Werewolf::get_health() const {return health;}

void Werewolf::set_health(int h) {health = h;}

int Werewolf::get_potions() const {return potions;}

void Werewolf:: set_potions(int pot) { potions = pot;}

void Werewolf::move()
{
    //To do...
}

void Werewolf::heal()
{
    //To do
}

void Werewolf::attack_enemy()
{
    //To do
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//A temporary main function for tests
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Point A(1,2);
    Point B;
    A.print_point();
    B.print_point();
    B.set_x(1);
    B.set_y(2);
    B.print_point();
    Point C(4,4);
    B.set_point(C);
    A.set_point(C.get_x(), C.get_y());
    B.print_point();
    A.print_point();

    if(A==B)
        cout<<"Same Point\n";
    return 0;
}

