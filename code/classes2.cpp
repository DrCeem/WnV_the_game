#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>

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

//class NPC{};




bool is_free(Point& pos, vector<Obstacle> obstcls)
{
    for(auto i = obstcls.begin(); i != obstcls.end(); i++){
        if( (pos.get_x() == i->get_pos().get_x()) && (pos.get_y() == i->get_pos().get_y()) );
            return false;
    }
    return true;        
}

// Obstacle* find_obstacle(Point pos, vector<Obstacle> obstcls) {

//     for(auto i = obstcls.begin(); i != obstcls.end(); i++)
//     {
//         if((pos.get_x() == i->get_pos().get_x()) && (pos.get_x() == i->get_pos().get_x()));
//         {
//             return obstcls.at(i);
//         }
//     }
//     return NULL; 

// }

class  Map {
    const int height;
    const int width;
    vector<Obstacle> obstacles;
    //vector<NPC> vamp_n_ww;            

     
public:
    Map(int h, int w);
    ~Map() {};
    int get_height() const {return height;}
    int get_width() const {return width;} 
    // void print_map();
};


Map:: Map(int h = 15, int w = 10) : height(h), width(w) 
{
    int obst_num = (height + width);
   // int team_members_count = height * width / 20;

    
    Point pos;
    char type;
    for(int i = 0; i < obst_num; i++)
    {
        do{
            srand(time(NULL));
            pos.set_x(rand() % width);
            pos.set_y(rand() % height);
        }
        while (!(is_free(pos , obstacles))); 

        if (rand() % 2)
            type ='W';
        else
            type = 'T'; 

       // Obstacle obstacle(*pos, type);
        obstacles.push_back(Obstacle(pos,type));     // edw to thema 
        
            
    }
} 
// void Map::print_map() {
//     for(int i = 0; i < height; i++ )
//     {
//         for(int j = 0; j < width; j++ )
//         {
//             Point p(i,j);
//             if(find_obstacle(p,obstacles) == NULL)
//                 cout << "\033[42;32m \033[0m";
//             else if(find_obstacle(p,obstacles) == 'W')
//                 cout << "\033[42;34m \033[0m";   
//             else
//                 cout << "\033[42;33m♣\033[0m";

//         }
//         cout << endl;
//     }

// }


int main()
{
    Map map;
    cout << "check\n" ;
    // map.print_map();
    return 0;
}
