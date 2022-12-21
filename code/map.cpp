#include "classes.h"
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
	// H or h (for healing the memebers of the player's team)
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