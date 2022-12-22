#include "classes.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Definition of GameState

GameState::GameState(Map& m) : map(m) {

    // Initializing keys
    keys.DOWN = false;
	keys.UP = false;
	keys.LEFT = false;
	keys.RIGHT = false;
	keys.H = false;
	keys.P = false;

    // Initializing state of game (playing, paused, game over) ++
    playing = true;
	paused = false;
}

GameState::~GameState() {}

bool GameState::is_playing() const { return playing; }

bool GameState::is_paused() const { return paused; }

void GameState::update_keys() {

    // Starts by setting all keys's values to false, and then changes them according to user's input
    keys.DOWN = false;
	keys.UP = false;
	keys.LEFT = false;
	keys.RIGHT = false;
	keys.H = false;
	keys.P = false;

	char input;

    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);

	while (1) {
		
        int ret = scanf("%c", &input);
		
        if (ret > 0){


    // scanf("%c", &input);
       
    // int input = getchar();

    // P or p (for pausing the game)
		if ( (input == 'P') || (input == 'p') ) {
			keys.P = true;
			return;
		}
	
		// H or h (for healing the memebers of the player's team)
		if ( (input == 'H') || (input == 'h') ) {
			keys.H = true;
			return;
		}
		// A or a
		if ( (input == 'A') || (input == 'a') ) {
			keys.LEFT = true;
			return;
		}
		// D or d
		else if ( (input == 'D') || (input == 'd') ) {
			keys.RIGHT = true;
			return;
		}
		// W or w
		else if ( (input == 'W') || (input == 'w') ) {
			keys.UP = true;
			return;
		}
		//  S or s
		else if ( (input == 'S') || (input == 's') ) {
			keys.DOWN = true;
			return;
		}
	}
	else
		return;
	}

}

void GameState::update() {

	// If one of the teams has lost we stop updating and return to main
    if (map.werewolves.empty() ) {

		if (map.avatar.get_team() == 'W')
			cout << "Team Werewolves was defeted! You lost :(\n";
		else
			cout << "Team Vampire came out Victorious! You won ;) \n";

		cout << "Game Over! \n";

		playing = false;
		return;
	}
	else if ( map.vampires.empty() ) {

		if (map.avatar.get_team() == 'V')
			cout << "Team Vampires was defeted! You lost :(\n";
		else
			cout << "Team Werewolves came out Victorious! You won ;) \n";

		cout << "Game Over! \n";

		playing = false;
		return ;
	}

    // We update the key input from user first, and then update the Game State accordingly
    update_keys();

    // If game isn't paused, pause it and if it is paused, unpause it
	if (keys.P)
		paused = !paused;

	if (!paused) {
		map.update_and_draw(map,keys);
	}
	else {
		// Resets the cursor at the beginning of Terminal
		cout << "\033[2J\033[1;5H" << endl;
		cout << "The Game is paused\n";
		cout << "Werewolves alive: " << map.werewolves.at(0).get_count() << endl;
		cout << "Vampires alive: " << map.vampires.at(0).get_count() << endl;
	}
	

}
















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////