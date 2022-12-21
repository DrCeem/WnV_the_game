#include "classes.h"
#include <chrono>
#include <thread>
#include <cstdio>
// #include <sys/ioctl.h> gia th malakia me tis synarthseis kbhit etc
// #include <termios.h>
// #include "curses.h"

using namespace std::chrono_literals;

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

