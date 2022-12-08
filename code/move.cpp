
void Werewolf::move( vector<Obstacle> obstacles){
    
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
        if (is_free(all_positions[i],obstacles)){
            available_positions[size] = all_positions[i];
            size ++;

        }
    }

    // Else we choose randomly out of the free positions
    pos.set_pos(available_positions[(rand()%size)]) ;

}


void Vampire::move(vector<Obstacle> obstacles){

    Point position = get_pos();
    Point all_positions[9];

    // All the positions where it's possible for the vampire to move:
    // Specifically it can move left, right, up, down, diagonally left and up, diagonally left and down, ,diagonally right and up and
    // diagonally right and down as well as stay in the original position 
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

    for (int i = 0; i < 9; i++){

        // Αποθηκεύουμε τις ελέυθερες θέσεις σ' εναν νέο πίνακα
        if (is_free(all_positions[0],obstacles)){
            available_positions[size] = all_positions[i];
            size ++;

        }
    }
    // Else we choose randomly out of the free positions
    pos.set_pos(available_positions[(rand()%size)]) ;


}

// Πληροφορίες για το ποια πλήκτρα είναι πατημένα
struct key_state {
	bool up;						// true αν το αντίστοιχο πλήκτρο είναι πατημένο
	bool down;
	bool left;
	bool right;
	bool space;
	bool p;
};