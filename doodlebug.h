#ifndef MAIN_CPP_DOODLEBUG_H
#define MAIN_CPP_DOODLEBUG_H

#include <iostream>
#include <vector>

using namespace std;

class World;
class Organism;

class World {

private:
    int time_step = 0;

    Organism rand_initialize(int pos_x, int pos_y);

public:
    static const int grid_size = 20;
    Organism *grid[grid_size][grid_size];
    int bug_counter = 5;
    int ant_counter = 0;

    void initialize();
    void printWorld();
    void swapOrganisms(Organism &old_org, Organism &new_org);

    void advanceTime();
};

class Organism {

private:

public:
    World *world = nullptr; // initializes a new pointer *world, which is supposed to point to an object of type World
    bool has_moved = false;

    int position_x, position_y;
    int breeding_counter = 0, lifespan = 0, hunger = 0;
    char organism_type;
    static const char ANT = 'o', BUG = 'X', SPACE = '-';

    // constructor, such that when Organism is called as a variable and initialized
    // with pos_x and pos_y, position_x and position_y are stored within the variable Organism
    // and can be used accordingly!
    Organism(World* input_world, int pos_x, int pos_y, char org_type)
            : world(input_world), position_x(pos_x), position_y(pos_y), organism_type(org_type),
              breeding_counter(0), lifespan(0), hunger(0), has_moved(false) {};


    void move();
    void breed();
    void die(Organism &dead_organism);
    char org_type() {return organism_type;};

};

#endif //MAIN_CPP_DOODLEBUG_H