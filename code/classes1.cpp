
#include <iostream>
#include <cstdlib>

using namespace std;



// 2D Point in Euclidean space
class Point {

    int x;
    int y;

    public:

        Point(int a = 0, int b = 0) : x(a) , y(b) {}
        ~Point(){}

        void set_x(int a){ x = a; }
        int get_x() const { return x;}
        void set_y(int b) { y = b;}
        int get_y() const { return y;}
        void print_pos() const { cout << x << "," << y ; }

};

// Hyperclass
// Three kinds of Objects: Potion, Water and Tress
class Object {

    const Point pos;

    public:

        // Object(){
        //     Point A;
        //     A.set_x(0);
        //     A.set_y(0);
        // }

        Object(Point& p): pos(p) {}
        ~Object(){}
        Point get_pos() const {return pos;}

};

class Potion: public Object {

    const Point pos;

    // Potion(){
    //     Point A;
    //         A.set_x(0);
    //         A.set_y(0);
    // };
    Potion(Point& p): Object(p), pos(p) {}
    ~Potion(){};

};

class Obstacle: public Object {

    const Point pos;
    const char type;    // Obstacles are either water or trees

    public:

        Obstacle(Point& p, char c) : Object(p), pos(p),type(c) {}
        ~Obstacle(){}
        char get_type() const {return type;}

}; 

// Hyperclass for classes Player and NPC and subclass from Object
class Entity: public Object{

    const Point pos;

    public:

        // Entity(){
        //     Object obj;
        // }
        Entity(Point& p) : Object(p), pos(p) {}
        ~Entity(){}
        virtual void move(); // Des ta
        void place_on_map();

};

class Player: public Entity{

    Point pos;
    const char team;    // Either 'W' or 'V' depending on which team the player chose
    int potions;     

    public:

        // Random default value for team 'N' = None
        Player(Point& p, char t = 'N', int num = 1) : Entity(p), pos(p), team(t), potions(num) {}
        ~Player(){}

        void move();
        void place_on_map();   //??? 
        void set_potions(int num) {potions = num;}
        int get_potions() const {return potions;}
        void heal() const;

};

class NPC: public Entity{

    Point pos;
    const char type;    // Either 'W' or 'V'
    int potions;     
    int health;
    int offence;
    int defence;

    public:

        // Default value for type 'N' = None
        NPC(Point& p, char t = 'N', int num = rand()% 2, int h = rand()% 3,  int o = rand()% 3 + 1,  int d = rand()% 2):
            Entity(p), pos(p), type(t), potions(num), health(h), offence(o), defence(d) {}
        ~NPC(){}

        void move();
        void place_on_map();   //??? 
        int get_potions() const {return potions;}
        int get_health() const {return health;}
        int get_offence() const {return offence;}
        int get_defence() const {return defence;}
        void attack();


};







int main(){

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