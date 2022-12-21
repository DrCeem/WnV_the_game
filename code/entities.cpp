#include "classes.h"
#include <vector>

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