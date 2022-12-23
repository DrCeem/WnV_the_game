
#include <iostream>
#include <cstdlib>
#include <vector>

#define MAX_HEALTH 5

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Declarations of classes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Point;
class Entity;
class Player;
class Vampire;
class Werewolf;
class Object;
class Map;
class GameState;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of a struct that represents which keys are pressed

struct KeyState {

	bool UP;
	bool DOWN;
	bool LEFT;
	bool RIGHT;
	bool H;
	bool P;

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of a 2D Point in Euclidean space

class Point {

	int x;
	int y;

	public:

		Point(int a = 0, int b = 0); 	// Constructor
		~Point();						// Destructor

		friend bool operator==(Point const& p1, Point const& p2); // Overloaded operator
		void set_x(int a);
		int get_x() const; 				// Accessors
		void set_y(int b);
		int get_y() const;
		void set_point(int x, int y);
		void set_point(Point& p);
		void print_point() const;		// Print Function

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of Object

class Object {

	const Point pos;
	const char type;	// Either 'P' for potion, 'T' for tree, 'W' for water 

	public:

		Object(Point& p, char t);		// Constructor
		~Object();						// Destructor

		Point get_pos() const;			// Accessors
		char get_type() const;

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Declaration of Entity 

class Entity {

	protected: 

		Point pos;
		char type;	// Either 'P' for Player, 'W' for Werewolf or 'V' for Vampire

	public:

		Entity(Point& p, char t);		// Constructor
		~Entity();						// Destructor

		Point get_pos() const;			// Accessors
		char get_type() const;

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of Player

class Player : public Entity {

	const char team;	// Either 'W' for Werewolves or 'V' for Vampires, depending on which team the player chooses
	int number_of_healing_spells;

	public:

		Player(Point& p, char tp, char tm);		// Constructor
		~Player();								// Destructor

		char get_team() const;					// Accessors
		int get_potions() const;
		void move(Map& map, KeyState& keys);	// Player move ability
		void heal(Map& map);					// Player heal ability

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
	friend class Vampire;
	friend class Werewolf;
	friend class GameState;
	
	public:

		Map(Player& avtr, int h, int w); 	// Constructor
		~Map();								// Destructor

		int get_height() const;				// Accessors
		int get_width() const;
		bool is_free(Point& x);
		void print_map();					// Prints Map
        void update_and_draw(Map& map, KeyState& keys); 	// Updates map and calls print_map
		Object* find_object(Point& pos);			// Returns pointer to object if not found returns NULL
		Entity* find_entity(Point& pos);			// Returns pointer to entity if not found returns NULL
		Vampire* find_Vampire(Point& pos);			// Returns pointer to vampire if not found returns NULL
		Werewolf* find_Werewolf(Point& pos);		// Returns pointer to werewolf if not found returns NULL
		
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of Vampire

class Vampire : public Entity {
	
	int health;
	int attack;
	int defence;
	int potions;

	public:

		Vampire(Point& p, char tp);			// Constuctor
		~Vampire();							// Destructor

		char get_type() const;				// Accessors
		int get_health() const;
		int get_attack() const;
		int get_defence() const;
		int get_potions() const;
		void set_health(int h);
		void set_potions(int p);
		void move(Map& map);				// Vampire's move ability
		void heal(Map& map);				// Vampire's heal ability
		void attack_enemy(Map& map);		// Vampire's attack ability
		void bail(Map& map,Point& z);		// Vampire's bail ability

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of Werewolf

class Werewolf : public Entity {
	
	int health;
	int attack;
	int defence;
	int potions;

	public:

		Werewolf(Point& p,char tp);			// Constuctor
		~Werewolf();						// Destructor

		char get_type() const;				// Accessors
		int get_health() const;
		int get_attack() const;
		int get_defence() const;
		int get_potions() const;
		void set_health(int h);
		void set_potions(int p);
		void move(Map& map) ;				// Werewolf's move ability
		void heal(Map& map);				// Werewolf's heal ability
		void attack_enemy(Map& map);		// Werewolf's attack ability
		void bail(Map& map, Point& z);		// Werewolf's bail ability

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Declaration of GameState

class GameState {

	KeyState keys;
	bool playing;
	bool paused;
	Map map;

	public:

		GameState(Map& m);			// Constuctor
		~GameState();				// Destructor
		bool is_playing() const;	// Accessors
		bool is_paused() const;
		void update_keys();			// Updates the keys
		void update();				// Updates the game

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
