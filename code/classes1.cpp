
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <raylib.h>

using namespace std;

// #define KEY_UP 72
// #define KEY_DOWN 80
// #define KEY_LEFT 75
// #define KEY_RIGHT 77

// Πληροφορίες για το ποια πλήκτρα είναι πατημένα
struct key_state {
	bool up;						// true αν το αντίστοιχο πλήκτρο είναι πατημένο
	bool down;
	bool left;
	bool right;
	bool space;
	bool enter;
	bool n;
	bool p;
};
// 2D Point in Euclidean space
class Point {

    int x;
    int y;

    public:

        Point(int a = 0, int b = 0) : x(a) , y(b) {}
        ~Point(){}

        void set_x(int a){ x = a; }
        void set_y(int b) { y = b;}
        int get_x() const { return x;}
        int get_y() const { return y;}
        void print_pos() const { cout << x << "," << y ; }

};

// Hyperclass
// Three kinds of Objects: Potion, Water and Tress
class Object {

    Point pos;

    public:

        Object(Point& p): pos(p) {}
        ~Object(){}
        Point get_pos() const {return pos;}

};


class Obstacle: public Object {

    const Point pos;
    const char type;    // Obstacles are either water, trees or potion

    public:

        Obstacle(Point& p, char c) : Object(p), pos(p),type(c) {}
        ~Obstacle(){}
        char get_type() const {return type;}

}; 

// Hyperclass for classes Player and NPC and subclass from Object
class Entity: public Object{

    Point pos;

    public:

        Entity(Point& p) : Object(p), pos(p) {}
        ~Entity(){}
        virtual void move(); // Des ta

};

class Player: public Entity{

    Point pos;
    const char team;    // Either 'W' or 'V' depending on which team the player chose
    int potions;     

    public:

        // Random default value for team 'N' = None
        Player(Point& p, char t = 'N', int num = 1) : Entity(p), pos(p), team(t), potions(num) {}
        ~Player(){}

        void set_potions(int num) {potions = num;}
        int get_potions() const {return potions;}
        void move();
        void heal() const;

};



void Player::move(){


    

}

// class NPC: public Entity{

//     Point pos;
//     const char type;    // Either 'W' or 'V'
//     int potions;     
//     int health;
//     int offence;
//     int defence;

//     public:

//         // Default value for type 'N' = None
//         NPC(Point& p, char t = 'N', int h = 5): Entity(p), type(t), health(h)  {

//                 // pos = p; xreiazeta
//                 potions = rand()% 2 + 1;
//                 offence = rand()% 3 + 1;
//                 defence =  rand()% 2 + 1;
//             }
//         ~NPC(){}

//         int get_potions() const {return potions;}
//         int get_health() const {return health;}
//         int get_offence() const {return offence;}
//         int get_defence() const {return defence;}
//         void move();
//         void attack();


// };

class Werewolve: public Entity{

    Point pos;
    const char type;
    int potions;     
    int health;
    int offence;
    int defence;

    public:
        Werewolve(Point& p, int h = 5, char t = 'W', int pot = (rand()% 3), int o = (rand()% 3 + 1), int d = (rand()% 2 + 1)):
                Entity(p), type(t), health(h), potions(pot), offence(o), defence(d) {}
        ~Werewolve(){}

        int get_potions() const {return potions;}
        int get_health() const {return health;}
        int get_offence() const {return offence;}
        int get_defence() const {return defence;}
        void move();
        void attack();


};

void Werewolve::move(){


    

}


class Vampire: public Entity{

    Point pos;
    const char type;
    int potions;     
    int health;
    int offence;
    int defence;

    public:
        Vampire(Point& p, int h = 5, char t = 'V', int pot = (rand()% 3), int o = (rand()% 3 + 1), int d = (rand()% 2 + 1)):
                Entity(p), type(t), health(h), potions(pot), offence(o), defence(d) {}
        ~Vampire(){}

        int get_potions() const {return potions;}
        int get_health() const {return health;}
        int get_offence() const {return offence;}
        int get_defence() const {return defence;}
        void move();
        void attack();


};




int main(){

    srand(time(NULL));

    Point A;
    A.set_x(2);
    A.set_y(3);
    cout << "For point A coordinates are: " << A.get_x() << "," << A.get_y() << endl;

    Object obj2(A);

    Point B = obj2.get_pos();
    B.print_pos();
    cout << endl;

    // Potion pot(A);
    cout << "Everything check\n";
    return 0;
}