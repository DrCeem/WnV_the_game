
#include "classes.h"
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Entity

Entity:: Entity(Point& p, char t) : pos(p), type(t) {}

Entity:: ~Entity() {}

Point Entity:: get_pos() const {return pos;}

char Entity:: get_type() const {return type;}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Player (derived from Entity)

Player:: Player(Point& p, char tp, char tm) : Entity(p,tp), team(tm) {
	// Player starts off with one healing potion
	number_of_healing_spells = 1;
}

Player:: ~Player() {};

char Player:: get_team() const {return team;}

int Player:: get_potions() const {return number_of_healing_spells;}

// If it's the appropriate time of day for the player's team to be healed (day for vampires and night for werewolves)
// the player heals their teammates, which decreases the number of potions they have by one 
void Player:: heal(Map& map) {
	
	if (number_of_healing_spells > 0) {

		// If Player is team Werewolves and it's nighttime, we set every Werewolf's health to MAX_HEALTH
		if ( (team == 'W') && (!map.day_night_cycle) ) {

			for (int i = 0; i < map.werewolves.size(); i++) {

				map.werewolves.at(i).set_health(MAX_HEALTH);
				
			}
			number_of_healing_spells -- ;
		}  
		// If Player is team Vampires and it's daytime, we set every Vampire's health to MAX_HEALTH
		else if ( (team == 'V') && (map.day_night_cycle) ) {

			for (int i = 0; i < map.vampires.size(); i++) {
				
				map.vampires.at(i).set_health(MAX_HEALTH);
				
			}
			number_of_healing_spells -- ;
		}  
	}

} 

// Depending on user's input (stored in struct keys), the player's Avatar can move up, down, left and right
void Player:: move(Map& map, KeyState& keys) {
	
	Point new_pos( pos.get_x() , pos.get_y() );

	// A or a
	if (keys.LEFT) {

		// New position is one move to the left from the original
		new_pos.set_x(pos.get_x() - 1);

		if ( map.find_object(new_pos) != NULL ) {

			// If the new position leads to the potion, the player takes it, increasing the amount of potions they own by 1
			Object* obj = map.find_object(new_pos);

			if (obj->get_type() == 'P') {

				number_of_healing_spells ++;

				// Potion is the last object in vector objects 
				map.objects.pop_back();

				// The position is now empty
			}
		}
		// If the position left of the current one is empty, player moves there
		if ( map.is_free(new_pos) )
			pos.set_point(new_pos);
		
	}
	// D or d
	else if (keys.RIGHT) {

		// New position is one move to the right from the original
		new_pos.set_x(pos.get_x() + 1);

		if ( map.find_object(new_pos) != NULL ) {

			// If the new position leads to the potion, the player takes it, increasing the amount of potions they own by 1
			Object* obj = map.find_object(new_pos);

			if (obj->get_type() == 'P') {

				number_of_healing_spells ++;

				// Potion is the last object in vector objects 
				map.objects.pop_back();

				// The position is now empty

			}
		}
		// If the position right of the current one is empty, player moves there
		if ( map.is_free(new_pos) )
			pos.set_point(new_pos);
		
	}
	// W or w
	else if (keys.UP) {

		// New position is one move above the original
		new_pos.set_y(pos.get_y() - 1);

		if ( map.find_object(new_pos) != NULL ) {

			// If the new position leads to the potion, the player takes it, increasing the amount of potions they own by 1
			Object* obj = map.find_object(new_pos);

			if (obj->get_type() == 'P'){

				number_of_healing_spells ++;

				// Potion is the last object in vector objects 
				map.objects.pop_back();

				// The position is now empty

			}
		}
		// If the position above the current one is empty, player moves there
		if ( map.is_free(new_pos) )
			pos.set_point(new_pos);
		
	}
	// S or s
	else if (keys.DOWN) {

		// New position is one move below the original
		new_pos.set_y(pos.get_y() + 1);

		if ( map.find_object(new_pos) != NULL ) {

			// If the new position leads to the potion, the player takes it, increasing the amount of potions they own by 1
			Object* obj = map.find_object(new_pos);

			if (obj->get_type() == 'P') {

				number_of_healing_spells ++;

				// Potion is the last object on vector objects 
				map.objects.pop_back();

				//  The position is now empty

			}
		}
		// If the position below the current one is empty, player moves there
		if ( map.is_free(new_pos) )
			pos.set_point(new_pos);
		
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Vampire (derived from Entity)

Vampire:: Vampire(Point& p, char tp ) : Entity(p,tp) {
	health =  MAX_HEALTH;
	attack = rand() % 3 + 1;
	defence = rand() % 2 +1;
	potions = rand() % 3;
}

Vampire:: ~Vampire() {}

char Vampire:: get_type() const {return type;}

int Vampire:: get_health() const {return health;}

int Vampire:: get_attack() const {return attack;}

int Vampire:: get_defence() const {return defence;}

int Vampire:: get_potions() const {return potions;}

void Vampire:: set_health(int h) {health = h;}

void Vampire:: set_potions(int pot) { potions = pot;}

// A Vampire can move in 9 ways
// Specifically it can move left, right, up, down, diagonally left and up, diagonally left and down, diagonally right and up 
// and diagonally right and down as well as stay in the original position 
// The function examines which of said positions are available, chooses one of them randomly, and moves the vampire to the new position
void Vampire:: move(Map& map) {

	Point position = pos;

	// All the positions where it's possible for the vampire to move
    Point all_positions[9];

	// All the positions that are currently available		
    Point available_positions[9]; 	

    // The original position (we already now it's available)
    available_positions[0] = position;
    int size = 1;

    // Right
    position.set_x(position.get_x()+1);
    all_positions[1] = position;

    // Diagonal right(down)
    position.set_y(position.get_y()+1);
    all_positions[2] = position;

    // Down
    position.set_x(position.get_x()-1);
    all_positions[3] = position;

    // Diagonal left(down)
    position.set_x(position.get_x()-1);
    all_positions[4] = position;

    // Left
    position.set_y(position.get_y()-1);
    all_positions[5] = position;

    // Diagonal left(up)
    position.set_y(position.get_y()-1);
    all_positions[6] = position;

    // Up
    position.set_x(position.get_x()+1);
    all_positions[7] = position;

    // Diagonal right(up)
    position.set_x(position.get_x()+1);
    all_positions[8] = position;

    for (int i = 1; i < 9; i++) {

        // Store only the available positions in the second array and increase it's size
        if ( map.is_free(all_positions[i]) ) {

            available_positions[size] = all_positions[i];
            size ++;

        }
    }

    // We choose randomly out of the available positions
    pos.set_point(available_positions[(rand()%size)]) ;

}

// If a Vampire is next to a member of their team, and they have one or more potions,
// they choose whether or not they'll heal their ally (randomly)
void Vampire:: heal(Map& map) {

	Point position = pos;

	// All 4 positions next to the Vampire
    Point nearby_positions[4];
 
    // Right
    position.set_x(position.get_x()+1);
    nearby_positions[0] = position;

    // Left
    position.set_x(position.get_x()-2);
    nearby_positions[1] = position;
    
    // Reset to original position
    position.set_x(pos.get_x());

    // Down
    position.set_y(position.get_y()+1);
    nearby_positions[2] = position;
    
    // Up
    position.set_y(position.get_y()-2);
    nearby_positions[3] = position;

	for (int i = 0; i < 4; i++) {
		
		Vampire* vamp = map.find_Vampire(nearby_positions[i]);

		// If the vampire has one or more potions and it's ally's health is below MAX_HEALTH, the fist one chooses wheather
		// or not it will heal the second one (randomly)
		if ( (vamp !=NULL) && (potions > 0 ) && (vamp->get_health() < MAX_HEALTH) ) {

			if (rand()%2){
				vamp->set_health( vamp->get_health() + 1 );
				potions --;
			}

			return;
		}	
    }
}

// If a Vampire is next to a Werewolf it chooses whether or not to attack based on their attack and defence level
void Vampire:: attack_enemy(Map& map) {
	    
	Point position = pos;

	// All 4 positions next to the Vampire
    Point nearby_positions[4];
 
    // Right
    position.set_x(position.get_x()+1);
    nearby_positions[0] = position;

    // Left
    position.set_x(position.get_x()-2);
    nearby_positions[1] = position;
    
    // Reset to original position
    position.set_x(pos.get_x());

    // Down
    position.set_y(position.get_y()+1);
    nearby_positions[2] = position;
    
    // Up
    position.set_y(position.get_y()-2);
    nearby_positions[3] = position;
	
	for (int i = 0; i < 4; i++) {
			
		Werewolf* wolf = map.find_Werewolf(nearby_positions[i]);

		// If there's a werewolf in the nearby position, it's attack is lower or the same as the vampire's, and it's defence
		// is lower than the vampire's attack, the vampire attacks it and the werewolf attempts to bail
		if ( (wolf != NULL) && ( attack >= wolf->get_attack() ) && ( attack > wolf->get_defence() ) ) {
			
			int damage = abs(attack - wolf->get_defence());
			wolf->set_health(get_health() - damage);

			//The attacked tries to bail
			wolf->bail(map,pos);

			// If victim's health gets to zero or below we delete the werewolf from the vector
			if (wolf->get_health() <= 0) {

				for ( int j = 0; j < map.werewolves.size(); j ++ ) {

					if ( map.werewolves.at(j).get_pos() == wolf->get_pos() ) {
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
// If that direction in unaivalable it will attempt to escape diagonaly in that direction
// If that also fails his bailing attempts have failed
// Point z is the attacker's position
void Vampire:: bail(Map& map, Point& z) {

	int new_x, new_y;

	// The new x value is the symmetrical value to the entity's x position (if z.x = 5 and pos.x = 6 ==> new_x = 7)
	new_x = 2 * pos.get_x() - z.get_x();
	// The new y value is the symmetrical value to the entity's y position (if z.y = 5 and pos.y = 6 ==> new_y = 7)
	new_y  = 2 * pos.get_y() - z.get_y();

	Point posible_new_pos(new_x,new_y);		
	
	// If the position is available the vampire moves there
	if ( map.is_free(posible_new_pos) ) {

		pos.set_x(posible_new_pos.get_x());
		pos.set_y(posible_new_pos.get_y());

		return;
	}	
	
	// If the new x value is different from the current one (same y,different x), it means the Vampire tried to move 
	// on the same row and failed
	// Therefore it now attempts to move on the y axis (diagonally up or down)
	if ( new_x != pos.get_x() ) {

		// One position above the original
		posible_new_pos.set_y(pos.get_y() + 1);
		
		if (map.is_free(posible_new_pos)) {

			pos.set_x(posible_new_pos.get_x());
			pos.set_y(posible_new_pos.get_y());

			return;
		}
		// One position below the original
		posible_new_pos.set_y(pos.get_y() - 1);
		
		if (map.is_free(posible_new_pos)) {

			pos.set_x(posible_new_pos.get_x());
			pos.set_y(posible_new_pos.get_y());

			return;
		}
	}
	// Else if the new y value is different from the current one (same x,different y), it means the Vampire tried to move 
	// on the same collumn and failed
	// Therefore it now attempts to move on the x axis (diagonally left or right)	
	else if ( new_y != pos.get_y() ) {
		
		// One position to the right from the original
		posible_new_pos.set_x(pos.get_x() + 1);
		
		if (map.is_free(posible_new_pos)) {

			pos.set_x(posible_new_pos.get_x());
			pos.set_y(posible_new_pos.get_y());

			return;
		}

		// One position to the left from the original
		posible_new_pos.set_x(pos.get_x() - 1);
		
		if (map.is_free(posible_new_pos)) {

			pos.set_x(posible_new_pos.get_x());
			pos.set_y(posible_new_pos.get_y());

			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definition of Werewolf (derived from Entity)

Werewolf:: Werewolf(Point& p, char tp ) : Entity(p,tp) {
	health =  MAX_HEALTH;
	attack = rand() % 3 + 1;
	defence = rand() % 2 +1;
	potions = rand() % 3;
}

Werewolf:: ~Werewolf() {}

char Werewolf:: get_type() const{return type;}

int Werewolf:: get_health() const {return health;}
 
int Werewolf:: get_attack() const {return attack;}

int Werewolf:: get_defence() const {return defence;}

int Werewolf:: get_potions() const {return potions;}

void Werewolf:: set_health(int h) {health = h;}

void Werewolf:: set_potions(int pot) {potions = pot;}

// A Werewolf can move in 5 ways:
// Specifically it can move left, right, up and down as well as stay in the original position 
// The function examines which of said positions are available, chooses one of them randomly, and moves the werewolf to the new position
void Werewolf:: move(Map& map) {

	Point position = pos;

	// All the positions where it's possible for the werewolf to move
    Point all_positions[5];

	// All the positions that are currently available		
    Point available_positions[5];

    // The original position (we already now it's available)
    available_positions[0] = position;
    int size = 1;
    
    // Right
    position.set_x(position.get_x()+1);
    all_positions[1] = position;

    // Left
    position.set_x(position.get_x()-2);
    all_positions[2] = position;
    
    // Reset to original Position
    position.set_x(pos.get_x());

    // Down
    position.set_y(position.get_y()+1);
    all_positions[3] = position;
    
    // Up
    position.set_y(position.get_y()-2);
    all_positions[4] = position;

    for (int i = 1; i < 5; i++) {

        // Store only the available positions in the second array and increase it's size
        if ( map.is_free(all_positions[i]) ) {

            available_positions[size] = all_positions[i];
            size ++;

        }
    }

    // We choose randomly out of the available positions
    pos.set_point(available_positions[(rand()%size)]) ;
}

// If a Werewolf is next to a member of their team, and they have one or more potions,
// they choose whether or not they'll heal their ally (randomly)
void Werewolf:: heal(Map& map) {

	Point position = pos;

	// All 4 positions next to the Vampire
    Point nearby_positions[4];
 
    // Right
    position.set_x(position.get_x()+1);
    nearby_positions[0] = position;

    // Left
    position.set_x(position.get_x()-2);
    nearby_positions[1] = position;
    
    // Reset to original position
    position.set_x(pos.get_x());

    // Down
    position.set_y(position.get_y()+1);
    nearby_positions[2] = position;
    
    // Up
    position.set_y(position.get_y()-2);
    nearby_positions[3] = position;

	for (int i = 0; i < 4; i++) {
		
		Werewolf* were = map.find_Werewolf(nearby_positions[i]);
		
		// If the werewolf has one or more potions and it's ally's health is below MAX_HEALTH, the fist one chooses wheather
		// or not it will heal the second one (randomly)
		if ( (were !=NULL) && (potions > 0 ) && (were->get_health() < MAX_HEALTH) ) {

			if (rand()%2){
				were->set_health( were->get_health() + 1 );
				potions --;
			}

			return;
		}	
    }
}

// If a Werewolf is next to a Vampire it chooses whether or not to attack based on their attack and defence level
void Werewolf:: attack_enemy(Map& map) {

	Point position = pos;

	// All 4 positions next to the Vampire
    Point nearby_positions[4];
 
    // Right
    position.set_x(position.get_x()+1);
    nearby_positions[0] = position;

    // Left
    position.set_x(position.get_x()-2);
    nearby_positions[1] = position;
    
    // Reset to original position
    position.set_x(pos.get_x());

    // Down
    position.set_y(position.get_y()+1);
    nearby_positions[2] = position;
    
    // Up
    position.set_y(position.get_y()-2);
    nearby_positions[3] = position;
	
	for (int i = 0; i < 4; i++) {
			
		Vampire* vamp = map.find_Vampire(nearby_positions[i]);

		// If there's a vampire in the nearby position, it's attack is lower or the same as the werewolf's, and it's defence
		// is lower than the werewolf's attack, the werewolf attacks it and the vampire attempts to bail
		if ( (vamp != NULL) && ( attack >= vamp->get_attack() ) && ( attack > vamp->get_defence() ) ) {
			
			int damage = abs(attack - vamp->get_defence());
			vamp->set_health(vamp->get_health() - damage);

			//The attacked tries to bail
			vamp->bail(map,pos);

			// If victim's health gets to zero or below we delete the vampire from the vector
			if (vamp->get_health() <= 0) {
				
				for ( int j = 0; j < map.vampires.size(); j ++ ) {

					if ( map.vampires.at(j).get_pos() == vamp->get_pos() ) {
						map.vampires.erase(map.vampires.begin() + j);
					}
				}
			}

			return;
		}
	}

}	

// If the werewolf is being attacked and has a lower attack level than it's opponent, this function will be called
// The werewolf will atempt to escape in the opposite direction from which it is being attacked
// If that direction in unaivalable his bailing attempt has failed
// Point z is the attacker's position
void Werewolf:: bail(Map& map, Point& z) {

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