
#include "classes.h"
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Definitions of classes
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definition of 2D point 

Point:: Point(int a, int b) : x(a) , y(b) {}

Point::~Point(){}

void Point::set_x(int a){ x = a; }

int Point::get_x() const { return x;}

void Point::set_y(int b) { y = b;}

int Point::get_y() const { return y;}

void Point::set_point(int a , int b) {
	x=a;
	y=b;
}

void Point::set_point(Point& p) {
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definition of Object

Object::Object(Point& p, char t) : pos(p), type(t) {}

Object::~Object(){}

Point Object::get_pos() const {return pos;}

char Object::get_type() const {return type;}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Entity

Entity:: Entity(Point& p, char t) : pos(p), type(t) {}

Entity::~Entity() {}

Point Entity::get_pos() const {return pos;}

char Entity::get_type() const {return type;}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Player

Player::Player(Point& p, char tp, char tm) : Entity(p,tp), team(tm) {
	number_of_healing_spells = 1;
}

Player::~Player() {};

char Player::get_team() const {return team;}

// If it's the appropriate time of day for the player's team to be healed (day for vampires and night for werewolves)
// the player heals their teammates, which decreases the number of potions the have by one 
void Player::heal(Map& map) {
	
	if (number_of_healing_spells > 0) {

		if ( (team == 'W') && (!map.day_night_cycle) ) {

			for(int i = 0; i < map.werewolves.size(); i++) {

				if(map.werewolves.at(i).get_type() == 'W') {
					map.werewolves.at(i).set_health(MAX_HEALTH);
				}
			}
			number_of_healing_spells -- ;
		}  

		else if ( (team == 'V') && (map.day_night_cycle) ) {

			for(int i = 0; i < map.vampires.size(); i++) {
				
				if(map.vampires.at(i).get_type() == 'V') {
					map.vampires.at(i).set_health(MAX_HEALTH);
				}
			}
			number_of_healing_spells --;

		}  
	}

} 

void Player::move(Map& map) {
	
	Point position = get_pos();
    Point all_positions[5];

    // All the positions where it's possible for the werewolf to move:
    // Specifically it can move left,right,up and down as well as stay in the original position 
    Point available_positions[5];
    // The original position
    available_positions[0] = position;
    int size = 1;
    
    // One step to the right
    position.set_x(position.get_x()+1);
    all_positions[1] = position;

    // One step to the left
    position.set_x(position.get_x()-2);
    all_positions[2] = position;
    
    // Original Position
    position.set_x(position.get_x()+1);

    // One step up
    position.set_x(position.get_y()+1);
    all_positions[3] = position;
    
    // One step down
    position.set_x(position.get_y()-2);
    all_positions[4] = position;

    for (int i = 1; i < 5; i++){

        // Αποθηκεύουμε τις ελέυθερες θέσεις σ' εναν νέο πίνακα
        if ( map.is_free(all_positions[i]) ){
            available_positions[size] = all_positions[i];
            size ++;

        }
    }

    // Else we choose randomly out of the free positions
    pos.set_point(available_positions[(rand()%size)]) ;
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Vampire

Vampire::Vampire(Point& p, char tp ) : Entity(p,tp) {
	health =  MAX_HEALTH;
	attack = rand() % 3 + 1;
	defence = rand() % 2 +1;
	potions = rand() % 3;
}

Vampire::~Vampire() {};

int Vampire::get_health() const {return health;}

int Vampire::get_attack() const {return attack;}

int Vampire::get_defence() const {return defence;}

int Vampire::get_potions() const {return potions;}

void Vampire::set_health(int h) {health = h;}

void Vampire:: set_potions(int pot) { potions = pot;}

// A Vampire can move in 9 ways:
// Specifically it can move left, right, up, down, diagonally left and up, diagonally left and down,diagonally right and up 
// and diagonally right and down as well as stay in the original position 
// The function examines which of said positions are available, chooses one of them randomly, and moves the vampire to the new position
void Vampire::move(Map& map) {

	Point position = get_pos();

	// All the positions where it's possible for the vampire to move
    Point all_positions[9];

	// All the positions that are currently available		
    Point available_positions[9]; 	

    // The original position
    available_positions[0] = position;
    int size = 1;

    // Right
    position.set_x(position.get_x()+1);
    all_positions[1] = position;

    // Diagonal right(up)
    position.set_y(position.get_y()+1);
    all_positions[2] = position;

    // Up
    position.set_x(position.get_x()-1);
    all_positions[3] = position;

    // Diagonal left(up)
    position.set_x(position.get_x()-1);
    all_positions[4] = position;

    // Left
    position.set_y(position.get_y()-1);
    all_positions[5] = position;

    // Diagonal left(down)
    position.set_y(position.get_y()-1);
    all_positions[6] = position;

    // Down
    position.set_x(position.get_x()+1);
    all_positions[7] = position;

    // Diagonal right(down)
    position.set_x(position.get_x()+1);
    all_positions[8] = position;

    for (int i = 1; i < 9; i++)
	{
        // Store only the available positions in the second array and increase it's size
        if ( map.is_free(all_positions[i]) ) {

            available_positions[size] = all_positions[i];
            size ++;

        }
    }

    // We choose randomly out of the free positions
    pos.set_point(available_positions[(rand()%size)]) ;
}

void Vampire::heal()
{
	//To do
}

void Vampire::attack_enemy()
{
	//To do
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Werewolf

Werewolf::Werewolf(Point& p, char tp ) : Entity(p,tp) {
	health =  MAX_HEALTH;
	attack = rand() % 3 + 1;
	defence = rand() % 2 +1;
	potions = rand() % 3;
}

Werewolf::~Werewolf() {}

int Werewolf::get_health() const {return health;}

int Werewolf::get_attack() const {return attack;}

int Werewolf::get_defence() const {return defence;}

int Werewolf::get_potions() const {return potions;}

void Werewolf::set_health(int h) {health = h;}

void Werewolf:: set_potions(int pot) { potions = pot;}

// A Werewolf can move in 5 ways:
// Specifically it can move left, right, up and down as well as stay in the original position 
// The function examines which of said positions are available, chooses one of them randomly, and moves the werewolf to the new position
void Werewolf::move(Map& map) {

	Point position = get_pos();

	// All the positions where it's possible for the vampire to move
    Point all_positions[5];

	// All the positions that are currently available		
    Point available_positions[5];

    // The original position
    available_positions[0] = position;
    int size = 1;
    
    // Right
    position.set_x(position.get_x()+1);
    all_positions[1] = position;

    // Left
    position.set_x(position.get_x()-2);
    all_positions[2] = position;
    
    // Original Position
    position.set_x(position.get_x()+1);

    // Up
    position.set_y(position.get_y()+1);
    all_positions[3] = position;
    
    // Down
    position.set_y(position.get_y()-2);
    all_positions[4] = position;


    for (int i = 1; i < 5; i++) {

        // Store only the available positions in the second array and increase it's size
        if ( map.is_free(all_positions[i]) ) {

            available_positions[size] = all_positions[i];
            size ++;

        }
    }

    // We choose randomly out of the free positions
    pos.set_point(available_positions[(rand()%size)]) ;
}

void Werewolf::heal()
{
	//To do
}

void Werewolf::attack_enemy()
{
	//To do
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definition of Map

Map:: Map(Player& avtr,int h = 15, int w = 60) : avatar(avtr), height(h), width(w) {   

	// Initializing day-night cycle randomnly and clock
	srand(time(NULL));
	day_night_cycle = rand() % 2;
	clock = 0;

	// Deciding the quantity of obstacles and NPCs based on the map size
	int obst_num = (height + width)/2;
	int team_members_count = height * width / 40;
	
	Point pos;
	char type;

	// Adding obstacles to the map    
	for ( int i = 0; i < obst_num; i++ ) {
		
		// Randomizes positions until it finds an available one
		do{
			pos.set_x(rand() % width);
			pos.set_y(rand() % height);

		} while (!(is_free(pos))); 

		if (rand() % 2)
			type ='W';
		else
			type = 'T'; 

		objects.push_back(Object(pos,type));
			
	}

	// Adding Vampires to the map    
	type = 'V';
	for ( int i = 0; i < team_members_count; i++ ) {

		// Randomizes positions until it finds an available one
		do{
			pos.set_x(rand() % width);
			pos.set_y(rand() % height);

		} while ( !(is_free(pos)) );
		
		vampires.push_back(Vampire(pos,type));
	}
	
	// Adding werewolves to the map
	type = 'W';
	for ( int i = 0; i < team_members_count; i++) {

		// Randomizes positions until it finds an available one
		do{
			pos.set_x(rand() % width);
			pos.set_y(rand() % height);
		} while ( !(is_free(pos)) );
		
		werewolves.push_back(Werewolf(pos,type));
	}

	// Adding the healing potion to the map
	do{
		pos.set_x(rand() % width);
		pos.set_y(rand() % height);
	} while ( !(is_free(pos)) ); 
	type = 'P';
	objects.push_back(Object(pos,type));

}

int Map::get_height() const { return height; }

int Map::get_width() const { return width; }

// bool Map::get_daynight() const { return day_night_cycle; }

// Returns a pointer to the entity that is in position pos
// If it doesn't exist it returns NULL
Entity* Map :: find_entity(Point& pos) {
	if(pos == avatar.get_pos())
		return &avatar;
	for ( int j = 0; j < vampires.size(); j ++ ) {

		if(pos == vampires.at(j).get_pos())
			return &vampires.at(j);
	}
	for ( int j = 0; j < werewolves.size(); j ++ ) {

		if(pos == werewolves.at(j).get_pos())
			return &werewolves.at(j);
	}
	return NULL;
}

// Returns a pointer to the object that is in position pos
// If it doesn't exist it returns NULL
Object* Map:: find_object(Point& pos) {

	for ( int i = 0 ; i < objects.size(); i ++ ) {

		if(pos == objects.at(i).get_pos())
			return &objects.at(i);
	}
	return NULL;
}

// Takes a position and examines wheather or not it's available, meaning there's not any kind of objects (trees, water), 
// NPCs (werewolves, vampires) or the player's avatar in said position
bool Map:: is_free(Point& pos) {

	//Returns true if pos is free and false if it's occupied
	if (   ( find_entity(pos) == NULL ) && ( find_object(pos) == NULL ) && ( pos.get_x() >= 0 ) 
		&& ( pos.get_x() < width ) && ( pos.get_y() >= 0 ) && ( pos.get_y() < height)	)
		return true;
	else 
		return false;    

}

// Prints the map and it's contents
void Map::print_map() {

	// Resets the cursor at the beginning of Terminal
	cout << "\033[2J\033[1;5H";

	if (day_night_cycle)
        cout<<"DAY ☼\n";
    else
        cout<<"NIGHT ☾\n";

    Point p;

    for ( int i = 0; i < height; i++ ) {
        
        for ( int j = 0; j < width; j++ ) {

			p.set_point(j,i);
			
			if((find_entity(p) != NULL) && (find_entity(p)->get_type() == 'P')) {
				if(avatar.get_team() == 'W')
					cout << "\033[42;31mW\033[0m";
				else if(avatar.get_team() == 'V')	
					cout << "\033[42;31mV\033[0m";
			}	
			else if((find_entity(p) != NULL) && (find_entity(p)->get_type() == 'V'))
			 	cout << "\033[42;30m☼\033[0m";
			else if((find_entity(p) != NULL) && (find_entity(p)->get_type() == 'W'))
				cout << "\033[42;37m☾\033[0m";
            else if(find_object(p) == NULL)
                cout << "\033[42;32m \033[0m";
			else if (find_object(p)->get_type() == 'P')
				cout << "\033[42;31m♥\033[0m"; 
            else if(find_object(p)->get_type() == 'W')
                cout << "\033[44;32m░\033[0m";   
            else
                cout << "\033[42;33m♣\033[0m";

        }
        cout << endl;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//A temporary main function for tests
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Updates the game

void Map::update_and_draw(Map& map) {

	for(int i = 0; i < werewolves.size(); i++) {

		if(werewolves.at(i).get_type() == 'W') {
				werewolves.at(i).move(map);
			}
	}

	for(int i = 0; i < vampires.size(); i++) {

		if(vampires.at(i).get_type() == 'V') {
				vampires.at(i).move(map);
			}
	}


	print_map();
}

// Initializing the game
int main()
{
	int h,w;
	cout << "Give Map size (height/width)\n";
	cin >> h >> w;
	char team;
	cout <<"Give Player's team ('W' for werewolves and 'V for vampires\n";
	cin >> team;
	Point p(rand()% w, rand()% h);
	Player player(p,'P',team);
	Map map(player,h,w);
	// cout << "\033[2J\033[1;5H";

    map.print_map();

	for (int i = 0; i < 30 ; i ++){
		std::this_thread::sleep_for(2000ms);
		map.update_and_draw(map);
	}
	// Map map2(player,h,w);
	// cout << "\033[2J\033[1;5H";
	// map2.print_map();

    // std::this_thread::sleep_for(2000ms);
	// cout << "\033[2J\033[1;5H";

	// map.print_map();

	// cout << "check\n";

	return 0;
}

