#include "classes.h"
#include <chrono>
#include <thread>
#include <cstdio>
// #include <sys/ioctl.h> gia th malakia me tis synarthseis kbhit etc
// #include <termios.h>
// #include "curses.h"

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
// the player heals their teammates, which decreases the number of potions they have by one 
void Player::heal(Map& map) {
	
	if (number_of_healing_spells > 0) {

		// 
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
	
	Point new_pos( pos.get_x(),pos.get_y() );

	// A or a
	if (map.keys.KEY_LEFT) {

		new_pos.set_x(pos.get_x() - 1);

		if ( map.find_object(new_pos) != NULL ) {
			// If the new position leads to the potion, the player takes it, increasing the amount of potions he owns by 1
			Object* obj = map.find_object(new_pos);

			if (obj->get_type() == 'P'){

				number_of_healing_spells ++;
				// Potion is the last object on vector objects 
				map.objects.pop_back();
				// Player moves to new position
				pos.set_point(new_pos);
			}
		}
		// If the position left of the current one is empty, player moves there
		if ( map.is_free(new_pos) )
			pos.set_point(new_pos);
		
	}
	// D or d
	else if (map.keys.KEY_RIGHT) {

		new_pos.set_x(pos.get_x() + 1);

		if ( map.find_object(new_pos) != NULL ) {
			// If the new position leads to the potion, the player takes it, increasing the amount of potions he owns by 1
			Object* obj = map.find_object(new_pos);

			if (obj->get_type() == 'P'){

				number_of_healing_spells ++;
				// Potion is the last object on vector objects 
				map.objects.pop_back();
				// Player moves to new position
				pos.set_point(new_pos);
			}
		}
		// If the position right of the current one is empty, player moves there
		else if ( map.is_free(new_pos) )
			pos.set_point(new_pos);
		
	}
	// W or w
	else if (map.keys.KEY_UP) {

		// new_pos.set_y(pos.get_y() + 1);
		new_pos.set_y(pos.get_y() - 1);

		if ( map.find_object(new_pos) != NULL ) {
			// If the new position leads to the potion, the player takes it, increasing the amount of potions he owns by 1
			Object* obj = map.find_object(new_pos);

			if (obj->get_type() == 'P'){

				number_of_healing_spells ++;
				// Potion is the last object on vector objects 
				map.objects.pop_back();
				// Player moves to new position
				pos.set_point(new_pos);
			}
		}
		// If the position above the current one is empty, player moves there
		if ( map.is_free(new_pos) )
			pos.set_point(new_pos);
		
	}
	// S or s
	else if (map.keys.KEY_DOWN) {
		// den kserw gt doyleyei etsi alla 
		new_pos.set_y(pos.get_y() + 1);
		if ( map.find_object(new_pos) != NULL ) {
			// If the new position leads to the potion, the player takes it, increasing the amount of potions he owns by 1
			Object* obj = map.find_object(new_pos);

			if( (obj->get_type() == 'P')){

				number_of_healing_spells ++;
				// Potion is the last object on vector objects 
				map.objects.pop_back();
				// Player moves to new position
				pos.set_point(new_pos);
			}
		}
		// If the position below the current one is empty, player moves there
		if ( map.is_free(new_pos) )
			pos.set_point(new_pos);
		
	}

	return;
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Vampire

int Vampire::count = 0;

Vampire::Vampire(Point& p, char tp ) : Entity(p,tp) {
	health =  MAX_HEALTH;
	attack = rand() % 3 + 1;
	defence = rand() % 2 +1;
	potions = rand() % 3;
	count++;
}

Vampire::~Vampire() {count--;}

int Vampire::get_count() const{return count;}

void Vampire::set_count(int c) {count = c;} 

char Vampire::get_type() const {return type;}

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

	Point position = pos;

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

void Vampire::heal(Map& map) {

	Point position = pos;

	// All 4 positions next to the Vampire
    Point nearby_positions[4];
 
    // Right
    position.set_x(position.get_x()+1);
    nearby_positions[0] = position;

    // Left
    position.set_x(position.get_x()-2);
    nearby_positions[1] = position;
    
    // Original Position
    position.set_x(position.get_x()+1);

    // Up
    position.set_y(position.get_y()+1);
    nearby_positions[2] = position;
    
    // Down
    position.set_y(position.get_y()-2);
    nearby_positions[3] = position;

	for (int i = 0; i < 4; i++) {
		
		Vampire* vamp = map.find_Vampire(nearby_positions[i]);

		// If the vampire has one or more potions and it's ally's health is below MAX_HEALTH, the fist one chooses wheather
		// or not it will heal the second one (randomly)
		if ((vamp !=NULL) && (potions > 0 ) && (vamp->get_health() < MAX_HEALTH)) {

			if(rand()%2){
				vamp->set_health( vamp->get_health() + 1 );
				potions --;
			}

			return;
		}	
    }
}


void Vampire::attack_enemy(Map& map)
{
	    
	Point position = pos;

	// All 4 positions next to the Vampire
    Point nearby_positions[4];
 
    // Right
    position.set_x(position.get_x()+1);
    nearby_positions[0] = position;

    // Left
    position.set_x(position.get_x()-2);
    nearby_positions[1] = position;
    
    // Original Position
    position.set_x(position.get_x()+1);

    // Up
    position.set_y(position.get_y()+1);
    nearby_positions[2] = position;
    
    // Down
    position.set_y(position.get_y()-2);
    nearby_positions[3] = position;
	
	for (int i = 0; i < 4; i++) {
			
		Werewolf* w = map.find_Werewolf(nearby_positions[i]);

		// If there's a werewolf in the nearby position, it's attack is lower or the same as the vampire's, and it's defence
		// is lower than the vampire's attack, the vampire attacks it and the weewolf attempts to bail
		if ((w != NULL) && ( attack >= w->get_attack() ) && ( attack > w->get_defence() ) ){
			
			int damage = abs(attack - w->get_defence());
			w->set_health(get_health() - damage);

			//The attacked tries to bail
			w->bail(map,pos);

			// If victim's health gets to zero or below we delete the werewolf from the vector, and call the destructor
			if (w->get_health() <= 0){
				for ( int j = 0; j < map.werewolves.size(); j ++ ){
					if (map.werewolves.at(j).get_pos() == w->get_pos() ){
						map.werewolves.erase(map.werewolves.begin() + j);
					}
				}
			}
			return;
		}
	}

}	

// If the vampire is being attacked and has a lower attack level than it's opponent, this function will be called
// The vampire will attempt to escape in the opposite direction from which it is being attacked
// If that direction in anaivalable he will attempt to escape diagonaly in that direction
// If that also fails his bailing attempts have failed
void Vampire::bail(Map& map, Point& z)
{
	int new_x, new_y;

	// The new x value is the symmetrical value to the entity's x position  (if z.x = 5 and pos.x = 6 ==> new_x = 7)
	new_x = 2 * pos.get_x() - z.get_x();
	// The new y value is the symmetrical value to the entity's y position  (if z.y = 5 and pos.y = 6 ==> new_y = 7)
	new_y  = 2 * pos.get_y() - z.get_y();

	Point posible_new_pos(new_x,new_y);		
	
	// If the position is available the vampire moves there
	if(map.is_free(posible_new_pos)) {
		pos.set_x(posible_new_pos.get_x());
		pos.set_y(posible_new_pos.get_y());
		return;
	}	
	
	// It attempts to move on the x axis
	if(new_x != 0) {

		posible_new_pos.set_y(pos.get_y() + 1);
		
		if (map.is_free(posible_new_pos)) {
			pos.set_x(posible_new_pos.get_x());
			pos.set_y(posible_new_pos.get_y());
			return;
		}
		posible_new_pos.set_y(pos.get_y() - 1);
		
		if (map.is_free(posible_new_pos)) {
			pos.set_x(posible_new_pos.get_x());
			pos.set_y(posible_new_pos.get_y());
			return;
		}
	}
	// Else it attempts to move on the y axis
	else if(new_y != 0)	{
		
		posible_new_pos.set_x(pos.get_x() + 1);
		
		if(map.is_free(posible_new_pos)) {
			pos.set_x(posible_new_pos.get_x());
			pos.set_y(posible_new_pos.get_y());
			return;
		}
		posible_new_pos.set_x(pos.get_x() - 1);
		
		if(map.is_free(posible_new_pos)) {
			pos.set_x(posible_new_pos.get_x());
			pos.set_y(posible_new_pos.get_y());
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Werewolf

int Werewolf::count = 0;

Werewolf::Werewolf(Point& p, char tp ) : Entity(p,tp) {
	health =  MAX_HEALTH;
	attack = rand() % 3 + 1;
	defence = rand() % 2 +1;
	potions = rand() % 3;
	count++;
}

Werewolf::~Werewolf() {count--;}

int Werewolf::get_count() const{return count;}

void Werewolf::set_count(int c) {count = c;} 

char Werewolf::get_type() const{return type;}

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

	Point position = pos;

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

void Werewolf::heal(Map& map) {

	Point position = pos;

	// All 4 positions next to the Vampire
    Point nearby_positions[4];
 
    // Right
    position.set_x(position.get_x()+1);
    nearby_positions[0] = position;

    // Left
    position.set_x(position.get_x()-2);
    nearby_positions[1] = position;
    
    // Original Position
    position.set_x(position.get_x()+1);

    // Up
    position.set_y(position.get_y()+1);
    nearby_positions[2] = position;
    
    // Down
    position.set_y(position.get_y()-2);
    nearby_positions[3] = position;

	for (int i = 0; i < 4; i++) {
		
		Werewolf* were = map.find_Werewolf(nearby_positions[i]);
		
		// If the werewolf has one or more potions and it's ally's health is below MAX_HEALTH, the fist one chooses wheather
		// or not it will heal the second one (randomly)
		if ((were !=NULL) && (potions > 0 ) && were->get_health() < MAX_HEALTH) {

			if(rand()%2){
				were->set_health( were->get_health() + 1 );
				potions --;
			}

			return;
		}	
    }
}


void Werewolf::attack_enemy(Map& map)
{
	Point position = pos;

	// All 4 positions next to the Vampire
    Point nearby_positions[4];
 
    // Right
    position.set_x(position.get_x()+1);
    nearby_positions[0] = position;

    // Left
    position.set_x(position.get_x()-2);
    nearby_positions[1] = position;
    
    // Original Position
    position.set_x(position.get_x()+1);

    // Up
    position.set_y(position.get_y()+1);
    nearby_positions[2] = position;
    
    // Down
    position.set_y(position.get_y()-2);
    nearby_positions[3] = position;
	
	for (int i = 0; i < 4; i++) {
			
		Vampire* vamp = map.find_Vampire(nearby_positions[i]);

		// If there's a vampire in the nearby position, it's attack is lower or the same as the werewolf's, and it's defence
		// is lower than the werewolf's attack, the werewolf attacks it and the vampire attempts to bail
		if ((vamp != NULL) && ( attack >= vamp->get_attack() ) && ( attack > vamp->get_defence() ) ){
			
			int damage = abs(attack - vamp->get_defence());
			vamp->set_health(vamp->get_health() - damage);

			//The attacked tries to bail
			// mhpos na prospathei na bailaei prin tis faei
			vamp->bail(map,pos);

			// If victim's health gets to zero or below we delete the werewolf from the vector, and call the destructor
			if (vamp->get_health() <= 0){
				for ( int j = 0; j < map.vampires.size(); j ++ ){
					if (map.vampires.at(j).get_pos() == vamp->get_pos() ){
						map.vampires.erase(map.vampires.begin() + j);
					}
				}
			}
			return;
		}
	}

}	

// If the werewolf is being attacked and has a lower attack level than it's opponent, this function will be called
// The werewolf will atempt to escape in the opposite direction from which it is being attacked.
// If that direction in anaivalable his bailing attempt has failed
void Werewolf::bail(Map& map, Point& z)
{
	int new_x, new_y;

	// The new x value is the symmetrical value to the entity's x position  (if z.x = 5 and pos.x = 6 ==> new_x = 7)
	new_x = 2 * pos.get_x() - z.get_x();
	// The new y value is the symmetrical value to the entity's y position  (if z.y = 5 and pos.y = 6 ==> new_y = 7)		
	new_y  = 2 * pos.get_y() - z.get_y();

	Point posible_new_pos(new_x,new_y);
	// If the position is available the werewolf moves there
	if(map.is_free(posible_new_pos)) {
		pos.set_x(posible_new_pos.get_x());
		pos.set_y(posible_new_pos.get_y());
	}	

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definition of Map

Map:: Map(Player& avtr,int h = 15, int w = 60) : avatar(avtr), height(h), width(w) {   

	// Initializing keys 
	// theoritika den xeiazetai
	keys.KEY_DOWN = false;
	keys.KEY_UP = false;
	keys.KEY_LEFT = false;
	keys.KEY_RIGHT = false;
	keys.KEY_H = false;
	keys.KEY_P = false;
	keys.paused = false;


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
	type = 'P';
	do{
		pos.set_x(rand() % width);
		pos.set_y(rand() % height);
	} while ( !(is_free(pos)) ); 

	objects.push_back(Object(pos,type));

}

int Map::get_height() const { return height; }

int Map::get_width() const { return width; }

// bool Map::get_daynight() const { return day_night_cycle; }

// Takes a position and examines wheather or not it's available, meaning there's not any kind of objects (trees, water), 
// NPCs (werewolves, vampires) or the player's avatar in said position
bool Map:: is_free(Point& pos) {

	
	// Returns true if pos is free and inside Map's limits and false if it's occupied or outside said limits
	if ( ( find_entity(pos) == NULL ) && ( find_object(pos) == NULL ) && ( pos.get_x() >= 0 ) 
		&& ( pos.get_x() < width ) && ( pos.get_y() >= 0 ) && ( pos.get_y() < height)	)
		return true;
	else   
		return false;

}

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

// Returns a pointer to the Werewolf that is in position pos
// If it doesn't exist it returns NULL
Werewolf* Map :: find_Werewolf(Point& pos) {

	for ( int j = 0; j < werewolves.size(); j ++ ) {

		if(pos == werewolves.at(j).get_pos())
			return &werewolves.at(j);
	}
	return NULL;
}

// Returns a pointer to the Vampire that is in position pos
// If it doesn't exist it returns NULL
Vampire* Map :: find_Vampire(Point& pos) {

	for ( int j = 0; j < vampires.size(); j ++ ) {

		if(pos == vampires.at(j).get_pos())
			return &vampires.at(j);
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

// Prints the map and it's contents
void Map::print_map() {

	// Resets the cursor at the beginning of Terminal
	cout << "\033[2J\033[1;5H";

	if (day_night_cycle)
        cout<<"DAY ☀\n";
    else
        cout<<"NIGHT ☾\n";

    Point p;

	// For each position on the Map, we examine wheather or not there is land, water, trees, a werewolf, a vampire 
	// or the player's avatar on said position and we prind the corresponding symbol
    for ( int i = 0; i < height; i++ ) {
        
        for ( int j = 0; j < width; j++ ) {
			
			p.set_point(j,i);
			
			// Entity is Player
			if((find_entity(p) != NULL) && (find_entity(p)->get_type() == 'P')) {

				if(avatar.get_team() == 'W')
					cout << "\033[42;31mW\033[0m";
				else if(avatar.get_team() == 'V')	
					cout << "\033[42;31mV\033[0m";
			}
			// Entity is Vampire
			else if((find_entity(p) != NULL) && (find_entity(p)->get_type() == 'V'))
			 	cout << "\033[42;30m☀\033[0m";
			// Entity is Werewolf
			else if((find_entity(p) != NULL) && (find_entity(p)->get_type() == 'W'))
				cout << "\033[42;37m☾\033[0m";
			// Land
            else if(find_object(p) == NULL)
                cout << "\033[42;32m \033[0m";
			// Object is Potion
			else if (find_object(p)->get_type() == 'P')
				cout << "\033[42;31m♥\033[0m"; 
			// Object is Water
            else if(find_object(p)->get_type() == 'W')
                cout << "\033[44;32m░\033[0m";  
			// Object is Tree 
            else
                cout << "\033[42;33m♣\033[0m";

        }
        cout << endl;
    }
	cout << "time: " << clock << endl;

	int sum_w =0;
	int sum_v =0;

	// Calling move function for all alive Werewolves
	for(int i = 0; i < werewolves.size(); i++) {
		sum_w += werewolves.at(i).get_health();
	}
	// Calling move function for all alive Vampires
	for(int i = 0; i < vampires.size(); i++) {
		sum_v += vampires.at(i).get_health();
	}
	
	// mporoume kai na mn to xoume gia na deixnei pote ftasei sto 0
	if (werewolves.size() > 0) {
		cout << "Werewolves alive: " << werewolves.at(0).get_count() << endl;
		cout << "Werewolves' average health: " << sum_w/werewolves.size() << endl;
	}
	if (vampires.size() > 0) {
		cout << "Vampires alive: " << vampires.at(0).get_count() << endl;
		cout << "Vampires' average health: " << sum_v/vampires.size()<< endl;
	}

}

void Map::update_keys(int input) {

	// P or p (for pausing the game)
	if ( (input == 80) || (input == 112) ) {

		keys.KEY_P = true;

		// If game isn't paused, pause it
		if (keys.paused = false)
			keys.paused = true;
		// If game is paused, unpause it
		else
			keys.paused = false;
		return;

	}
	// H or h (for pausing the game)
	if ( (input == 72) || (input == 104) ) {
		keys.KEY_H = true;
		return;
	}

	// A or a
	if ( (input == 65) || (input == 97) ) {
		keys.KEY_LEFT = true;
		return;
	}
	// D or d
	else if ( (input == 68) || (input == 100) ) {
		keys.KEY_RIGHT = true;
		return;
	}
	// W or w
	else if ( (input == 87) || (input == 119) ) {
		keys.KEY_UP = true;
		return;
	}
	else if ( (input == 83) || (input == 115) ) {
		keys.KEY_DOWN = true;
		return;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Initializing an updating the game
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Updates the game 
// Returns true while the game is running and false when it's over
bool Map::update_and_draw(Map& map) {

	// If one of the teams has lost we stop updating and return to main
	if ( werewolves.empty() ) {

		if (avatar.get_team() == 'W')
			cout << "Team Werewolves was defeted! You lost loseraki:(\n";
		else
			cout << "Team Vampire came out Victorious! You won ;) \n";

		cout << "Game Over! \n";

		return false;
	}
	else if ( vampires.empty() ) {

		if (avatar.get_team() == 'V')
			cout << "Team Vampires was defeted! You lost loseraki:(\n";
		else
			cout << "Team Werewolves came out Victorious! You won ;) \n";

		cout << "Game Over! \n";
		
		return false;
	}

	clock ++;
	
	if (clock%10 == 0)
		day_night_cycle = !day_night_cycle;
	

	// se kathe frame ta jana kanei false
	keys.KEY_DOWN = false;
	keys.KEY_UP = false;
	keys.KEY_LEFT = false;
	keys.KEY_RIGHT = false;
	keys.KEY_H = false;
	keys.KEY_P = false;
	// keys.paused = false; ayto menei idio

	// αυτο θεωργητικα δουλεευι αλλα πετα ερρορ στο τελος
	// enable_raw_mode();

	// if ( kbhit() ){
	// 	int input = getchar();
	// 	update_keys(input);

	// }
	// disable_raw_mode();

	int input = getchar();

	if (input!= EOF)
		update_keys(input);

	if (keys.paused)
		return true;

	if ( (keys.KEY_DOWN) || (keys.KEY_UP) || (keys.KEY_LEFT) || (keys.KEY_RIGHT) )
		avatar.move(map);
	// paizei na pethnoyn taytoxrona oloi apo tis omades oxi mallon alla des to ayrio
	
	// Calling move function for all alive Werewolves
	for(int i = 0; i < werewolves.size(); i++) {
		werewolves.at(i).move(map);
	}
	// Calling move function for all alive Vampires
	for(int i = 0; i < vampires.size(); i++) {
		vampires.at(i).move(map);
	}

	if (keys.KEY_H)
		avatar.heal(map);

	// Afte moving, we call heal and attack_enemy functions for all alive Werewolves
	for(int i = 0; i < werewolves.size(); i++) {

		werewolves.at(i).heal(map);
		werewolves.at(i).attack_enemy(map);
			
	}
	// Afte moving, we call heal and attack_enemy functions for all alive Vampires
	for(int i = 0; i < vampires.size(); i++) {

		vampires.at(i).heal(map);
		vampires.at(i).attack_enemy(map);
			
	}

	// We print the updated Map, as well as the number of alive membes of each team
	print_map();

	// Returning true means the game is still running
	return true;
	
}

// void enable_raw_mode()
// {
//     termios term;
//     tcgetattr(0, &term);
//     term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
//     tcsetattr(0, TCSANOW, &term);
// }

// void disable_raw_mode()
// {
//     termios term;
//     tcgetattr(0, &term);
//     term.c_lflag |= ICANON | ECHO;
//     tcsetattr(0, TCSANOW, &term);
// }

// bool kbhit()
// {
//     int byteswaiting;
//     ioctl(0, FIONREAD, &byteswaiting);
//     return byteswaiting > 0;
// }

// Initializing the game
int main() {

	// Asks user for Map size
	int h,w;
	do {
		cout << "Give Map size (height/width)\n";
		cin >> h >> w;

	// Smallest possible sizes for Map are 5x10 and 10x5
	} while( ( (h<5) || (w<10) ) && ( (h<10) || (w<5) ) );

	// Asks user for their team
	char team;
	do {
		cout <<"Give Player's team ('W' for werewolves and 'V for vampires\n";
		cin >> team;

	} while ( (team != 'W') and (team != 'V') );

	// Initializing player's position randomly
	Point p(rand()% w, rand()% h);
	Player player(p,'P',team);

	// Initializing the game Map
	Map map(player,h,w);

	// Calls the update function until a team looses
	bool running;
	do {
		running = map.update_and_draw(map);
		std::this_thread::sleep_for(500ms);

	} while (running);


	return 0;

}

