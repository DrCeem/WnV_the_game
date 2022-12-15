
#include <iostream>
#include <cstdlib>
#include <vector>

#define MAX_HEALTH 10

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declarations of classes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Point;
class Entity;
class Entity;
class Player;
class Vampire;
class Werewolf;
class Object;
class Map;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of a struct that represents which keys are pressed

struct KeyState {
	bool KEY_UP;
	bool KEY_DOWN;
	bool KEY_LEFT;
	bool KEY_RIGHT;
	bool KEY_SPACE;
	bool KEY_P;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of 2D Point in Euclidean space

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Decleration of Object

class Object {

	const Point pos;
	const char type;	// Either 'P' for potion, 'T' for tree, 'W' for water 

	public:

		Object(Point& p, char t);
		~Object();
		Point get_pos() const;
		char get_type() const;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Decleration of Entity 

class Entity {

	protected: 
		Point pos;
		const char type;	// Either 'P' for Player, 'W' for Werewolf or 'V' for Vampire

	public:

		Entity(Point& p, char t);
		~Entity();
		Point get_pos() const;
		char get_type() const;
		void move();
		void heal();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Decleration of Player

class Player : public Entity {

	const char team;	// Either 'W' for Werewolves or 'V' for Vampires, depending on which team the playe chooses
	int number_of_healing_spells;

	public:

		Player(Point& p, char tp, char tm);
		~Player();
		char get_team() const;
		void move(Map& map);
		void heal(Map& map);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of Map

class Map {

	const int height;
	const int width;
	bool day_night_cycle; 	// True if it's daytime, false if it's nighttime
	int clock;
	vector <Object> objects;
	vector <Vampire> vampires;
	vector <Werewolf> werewolves;
	Player avatar;

    friend class Player;
	
	public:

		Map(Player& avtr, int h, int w);
		~Map() {};
		int get_height() const;
		int get_width() const;
        // bool get_daynight() const;
		bool is_free(Point& x);
		void print_map();
        void update_and_draw(Map& map);
		Object* find_object(Point& pos);
		Entity* find_entity(Point& pos);
		
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of Vampire

class Vampire : public Entity {

	int health;
	int attack;
	int defence;
	int potions;

	public:

		Vampire(Point& p, char tp);
		~Vampire();
		int get_health() const;
		int get_attack() const;
		int get_defence() const;
		int get_potions() const;
		void set_health(int h);
		void set_potions(int p);
		void move(Map& map);
		void heal();
		void attack_enemy();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Declaration of Werewolf

class Werewolf : public Entity {
	int health;
	int attack;
	int defence;
	int potions;

	public:

		Werewolf(Point& p,char tp);
		~Werewolf();
		int get_health() const;
		int get_attack() const;
		int get_defence() const;
		int get_potions() const;
		void set_health(int h);
		void set_potions(int p);
		void move(Map& map) ;
		void heal();
		void attack_enemy();
};

