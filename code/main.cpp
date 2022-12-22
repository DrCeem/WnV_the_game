#include "classes.h"
#include <chrono>
#include <thread>
#include <cstdio>

using namespace std::chrono_literals;

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

	GameState state(map);

	// Calls the update function until a team looses (Game Over)
	do {

		state.update();
		std::this_thread::sleep_for(600ms);

	} while ( state.is_playing() );

	return 0;

}

