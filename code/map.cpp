
#include "classes.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definition of Map

Map:: Map(Player& avtr,int h = 15, int w = 60) : avatar(avtr), height(h), width(w) {   

	// Initializing day-night cycle randomly and clock
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
		do {
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
		do {
			pos.set_x(rand() % width);
			pos.set_y(rand() % height);

		} while ( !(is_free(pos)) );
		
		vampires.push_back(Vampire(pos,type));
	}
	
	// Adding werewolves to the map
	type = 'W';
	for ( int i = 0; i < team_members_count; i++) {

		// Randomizes positions until it finds an available one
		do {
			pos.set_x(rand() % width);
			pos.set_y(rand() % height);
		} while ( !(is_free(pos)) );
		
		werewolves.push_back(Werewolf(pos,type));
	}

	// Adding the healing potion to the map
	type = 'P';
	do {
		pos.set_x(rand() % width);
		pos.set_y(rand() % height);
	} while ( !(is_free(pos)) ); 

	objects.push_back(Object(pos,type));

}

Map:: ~Map() {}

int Map:: get_height() const { return height; }

int Map:: get_width() const { return width; }

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

	if (pos == avatar.get_pos())
		return &avatar;

	for ( int j = 0; j < vampires.size(); j ++ ) {

		if (pos == vampires.at(j).get_pos())
			return &vampires.at(j);
	}
	for ( int j = 0; j < werewolves.size(); j ++ ) {

		if (pos == werewolves.at(j).get_pos())
			return &werewolves.at(j);
	}
	return NULL;
}

// Returns a pointer to the Werewolf that is in position pos
// If it doesn't exist it returns NULL
Werewolf* Map :: find_Werewolf(Point& pos) {

	for ( int j = 0; j < werewolves.size(); j ++ ) {

		if (pos == werewolves.at(j).get_pos())
			return &werewolves.at(j);
	}
	return NULL;
}

// Returns a pointer to the Vampire that is in position pos
// If it doesn't exist it returns NULL
Vampire* Map :: find_Vampire(Point& pos) {

	for ( int j = 0; j < vampires.size(); j ++ ) {

		if (pos == vampires.at(j).get_pos())
			return &vampires.at(j);
	}
	return NULL;
}

// Returns a pointer to the object that is in position pos
// If it doesn't exist it returns NULL
Object* Map:: find_object(Point& pos) {

	for ( int i = 0 ; i < objects.size(); i ++ ) {

		if (pos == objects.at(i).get_pos())
			return &objects.at(i);
	}
	return NULL;
}

// Prints the map and it's contents
void Map::print_map() {

	// Resets the cursor at the beginning of Terminal
	cout << "\033[2J\033[1;5H" << endl;

	if (day_night_cycle)
        cout<<"DAY ☀\n";
    else
        cout<<"NIGHT ☾\n";

    Point p;

	// For each position on the Map, we examine whether or not there is land, water, trees, a werewolf, a vampire 
	// or the player's avatar on said position and prind the corresponding symbol
    for ( int i = 0; i < height; i++ ) {
        
        for ( int j = 0; j < width; j++ ) {
			
			p.set_point(j,i);
			
			// Entity is Player
			if ( (find_entity(p) != NULL) && (find_entity(p)->get_type() == 'P') ) {

				if(avatar.get_team() == 'W')
					cout << "\033[42;31mW\033[0m";
				else if(avatar.get_team() == 'V')	
					cout << "\033[42;31mV\033[0m";
			}
			// Entity is Vampire
			else if ( (find_entity(p) != NULL) && (find_entity(p)->get_type() == 'V') )
			 	cout << "\033[42;30m☀\033[0m";
			// Entity is Werewolf
			else if ( (find_entity(p) != NULL) && (find_entity(p)->get_type() == 'W') )
				cout << "\033[42;37m☾\033[0m";
			// Land
            else if (find_object(p) == NULL)
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

	int sum_w = 0;
	int sum_v = 0;

	// For calculating Werewolves's average health
	for (int i = 0; i < werewolves.size(); i++) 
		sum_w += werewolves.at(i).get_health();
	
	// For calculating Vampires's average health
	for (int i = 0; i < vampires.size(); i++) 
		sum_v += vampires.at(i).get_health();
	
	if (werewolves.size() > 0 )
		cout << "Werewolves' average health: " << sum_w/werewolves.size() << endl;
	if (vampires.size() > 0)
		cout << "Vampires' average health: " << sum_v/vampires.size()<< endl;

}

// Updates the Map based on the user's input (keys)
void Map::update_and_draw(Map& map, KeyState& keys) {

	clock ++;
	
	// Day and night switch every 10 frames
	if (clock%10 == 0)
		day_night_cycle = !day_night_cycle;
	

	// If any of the keys UP, DOWN, LEFT or RIGHT are pressed we call player's move function
	if ( (keys.DOWN) || (keys.UP) || (keys.LEFT) || (keys.RIGHT) )
		avatar.move(map,keys);
	
	// Calling move function for all alive Werewolves
	for (int i = 0; i < werewolves.size(); i++) 
		werewolves.at(i).move(map);
	
	// Calling move function for all alive Vampires
	for (int i = 0; i < vampires.size(); i++) 
		vampires.at(i).move(map);
	

	// If key H is pressed we call player's heal function
	if (keys.H)
		avatar.heal(map);

	// Afte moving, we call heal and attack_enemy functions for all alive Werewolves
	for (int i = 0; i < werewolves.size(); i++) {

		werewolves.at(i).heal(map);
		werewolves.at(i).attack_enemy(map);
			
	}
	// Afte moving, we call heal and attack_enemy functions for all alive Vampires
	for (int i = 0; i < vampires.size(); i++) {

		vampires.at(i).heal(map);
		vampires.at(i).attack_enemy(map);
			
	}

	// We print the updated Map
	print_map();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
