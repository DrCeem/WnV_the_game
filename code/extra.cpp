
#include<raylib.h>
// Πληροφορίες για το ποια πλήκτρα είναι πατημένα
struct key_state {
	bool up;						// true αν το αντίστοιχο πλήκτρο είναι πατημένο
	bool down;
	bool left;
	bool right;
	bool space;
	bool enter;
	bool n;
	bool p;
};

int main() {

	key_state* keys = new (key_state);
	keys->down = false;
	keys->enter = false;
	keys->left = false;
	keys->n = false;
	keys->p = false;
	keys->right = false;
	keys->space = false;
	keys->up = false;

	if (IsKeyDown(KEY_DOWN)){
		keys->down = true;
	}

	if (IsKeyDown(KEY_ENTER)){
		keys->enter = true;
	}

	if (IsKeyDown(KEY_LEFT)){
		keys->left = true;
	}

	if (IsKeyDown(KEY_N)){
		keys->n = true;
	}

	if (IsKeyPressed(KEY_P)){
		keys->p = true;
	}

	if (IsKeyDown(KEY_RIGHT)){
		keys->right = true;
	}

	if (IsKeyDown(KEY_SPACE)){
		keys->space = true;
	}

	if (IsKeyDown(KEY_UP)){
		keys->up = true;
	}

	return 0;
}










// int main() {
// 	state = state_create();
// 	interface_init();

// 	// Η κλήση αυτή καλεί συνεχόμενα την update_and_draw μέχρι ο χρήστης να κλείσει το παράθυρο
// 	start_main_loop(update_and_draw);

// 	interface_close();

// 	return 0;
// }