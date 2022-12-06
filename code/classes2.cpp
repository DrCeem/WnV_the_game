#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <thread>
 


using namespace std;

// Temporary until the other classes are ready for use
class Point
{
    int x;
    int y;
public:
    Point(int a = 0, int b = 0) : x(a) , y(b) {};
    ~Point(){};
    void set_x(int a){ x = a; }
    int get_x() const { return x;}
    void set_y(int b) { y = b;}
    int get_y() const {return y;}
    void print_point() {cout<<"("<< x << "," << y << ")";}
};

class Obstacle 
{
    const Point pos;
    const char type;
public:
    Obstacle(Point& p, char c) : pos(p),type(c) {};
    ~Obstacle(){};
    Point get_pos() const {return pos;}
    char get_type() const {return type;}
}; 

class  Map {
    const int height;
    const int width;
    vector<Obstacle> obstacles;
    bool day_night_cycle;
    int clock;
    //vector<NPC> vamp_n_ww;            

     
public:
    Map(int h, int w);
    ~Map() {};
    int get_height() const {return height;}
    int get_width() const {return width;} 
    bool is_free(Point x);
    Obstacle* find_obstacle(Point pos);
    void print_map();
};


Map:: Map(int h = 30, int w = 60) : height(h), width(w) 
{   
    //Initializing day-night cycle randomnly and clock
    srand(time(NULL));
    day_night_cycle = rand() % 2;
    clock = 0;

    int obst_num = (height + width);
   // int team_members_count = height * width / 20;
    
    
    Point pos;
    char type;
    for(int i = 0; i < obst_num; i++)
    {
        //j is a modifier so the random number generator changes seed every time it checks the vector for the same cordinates
        int j = 1000;
        do{
            srand(time(NULL) * j);
            pos.set_x(rand() % height);
            pos.set_y(rand() % width);
            j += 1000;
        }
        while (!(is_free(pos))); 

        if (rand() % 2)
            type ='W';
        else
            type = 'T'; 

        obstacles.push_back(Obstacle(pos,type));
            
    }
} 

bool Map::is_free(Point pos)
{

    for(auto i = obstacles.begin(); i < obstacles.end(); i++)
    { 
        if(i->get_pos().get_x() == pos.get_x() && (i->get_pos().get_y() == pos.get_y()))
            return false;
    }    
    return true;
}

Obstacle* Map::find_obstacle(Point pos) {
   int j = 0;
   for(auto i = obstacles.begin(); i != obstacles.end(); i++)
    {
        //pos.print_point();
        if((pos.get_x() == i->get_pos().get_x()) && (pos.get_y() == i->get_pos().get_y()))
        {
           return &obstacles.at(j);
        }
        j++;
    }
    return NULL;

}

 void Map::print_map() {
    if(day_night_cycle)
        cout<<"DAY\n";
    else
        cout<<"NIGHT\n";
    
     for(int i = 0; i < height; i++ )
     {
        
        for(int j = 0; j < width; j++ )
         {
           if(find_obstacle(Point(i,j)) == NULL)
                 cout << "\033[42;32m \033[0m";
             else if(find_obstacle(Point(i,j))->get_type() == 'W')
                cout << "\033[44;32m \033[0m";   
             else
                 cout << "\033[42;33m♣\033[0m";

         }
         cout << endl;
     }

 }


int main()
{
    Map map;
    cout << "check\n";
    map.print_map();
    return 0;
}
