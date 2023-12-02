#include <iostream>
#include "doodlebug.h"
#include <cstdlib>
#include <vector>

// const = read only!
void World::printWorld() {

    cout << "Time Period: " << time_step << endl;
    cout << "Number of ants left: " << ant_counter << endl;
    cout << "Number of bugs left: " << bug_counter << endl;

    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {

            if (grid[i][j] -> org_type() == Organism::ANT) cout << Organism::ANT << ' ';
            else if (grid[i][j] -> org_type() == Organism::BUG) cout << Organism::BUG << ' ';
            else cout << "- ";

        }
        cout << endl;
    }

}

Organism World::rand_initialize(int pos_x, int pos_y) {


    if (ant_counter < 100) {
        double random_number = rand();
        double temp_percent = random_number / RAND_MAX;
        if (temp_percent < 0.15) {
            grid[pos_x][pos_y] = new Organism(this, pos_x, pos_y, Organism::ANT);
            ant_counter++;
        }
    }

}

void World::initialize() {

    // clear initial grid
    for(int i = 0; i < grid_size; i++) {
        for(int j = 0; j < grid_size; j++) {
            grid[i][j] = new Organism(this, i,j, Organism::SPACE);
        }
    }

    grid[5][5] = new Organism(this, 5, 5, Organism::BUG);
    grid[10][10] = new Organism(this,10, 10, Organism::BUG);
    grid[15][5] = new Organism(this,15, 5, Organism::BUG);
    grid[15][15] = new Organism(this, 15, 15, Organism::BUG);
    grid[5][15] = new Organism(this, 5, 15, Organism::BUG);

    while(ant_counter < 100) {
        for (int i = 0; i < grid_size; i++) {
            for (int j = 0; j < grid_size; j++) {

                if((grid[i][j] -> org_type()) == Organism::SPACE) rand_initialize(i, j);

            }
        }
    }
}

void World::swapOrganisms(Organism &old_org, Organism &new_org) {
    Organism* temp_organism = grid[old_org.position_x][old_org.position_y];
    grid[old_org.position_x][old_org.position_y] = grid[new_org.position_x][new_org.position_y];
    grid[new_org.position_x][new_org.position_y] = temp_organism;

    // Update the positions after the swap
    grid[old_org.position_x][old_org.position_y]->position_x = old_org.position_x;
    grid[old_org.position_x][old_org.position_y]->position_y = old_org.position_y;
    grid[new_org.position_x][new_org.position_y]->position_x = new_org.position_x;
    grid[new_org.position_x][new_org.position_y]->position_y = new_org.position_y;
}

void Organism::move() {

    breeding_counter++;
    lifespan++;

    // random movement decision

    int new_x = position_x, new_y = position_y;
    int up = position_x + 1, down = position_x - 1, left = position_y - 1, right = position_y + 1;

    int random_number = fmod(rand(), 4);

    switch (random_number) {

        case 0:
            new_x = up;
            break;

        case 1:
            new_x = down;
            break;

        case 2:
            new_y = left;
            break;

        case 3:
            new_y = right;
            break;

    }

    Organism old_org = *(world -> grid[position_x][position_y]);

    // kill old org if hungry
    if (old_org.hunger > 3) {

        die(*(world->grid[position_x][position_y]));
        (world -> bug_counter) -= 1;

    }

    // eat if bug

    if(old_org.organism_type == BUG && !has_moved) {

        // if object north of original organism is an ant
        if(up < 20 && (world -> grid[up][position_y]) -> org_type() == ANT) {
            die(*(world -> grid[up][position_y])); //ant dies
            Organism new_org = *(world -> grid[up][position_y]);
            old_org.hunger = 0;
            old_org.breeding_counter++;
            has_moved = true;
            world -> ant_counter--;
            world -> swapOrganisms(old_org,new_org);
        }

        else if(down >= 0 && (world -> grid[down][position_y]) -> org_type() == ANT) {
            die(*(world -> grid[down][position_y])); //ant dies
            Organism new_org = *(world -> grid[down][position_y]);
            old_org.hunger = 0;
            old_org.breeding_counter++;
            has_moved = true;
            world -> ant_counter--;
            world -> swapOrganisms(old_org,new_org);
        }

        else if(left >= 0 && (world -> grid[position_x][left]) -> org_type() == ANT) {
            die(*(world -> grid[position_x][left])); //ant dies
            Organism new_org = *(world -> grid[position_x][left]);
            old_org.hunger = 0;
            old_org.breeding_counter++;
            has_moved = true;
            world -> ant_counter--;
            world -> swapOrganisms(old_org,new_org);
        }

        else if(up < 20 && (world -> grid[position_x][right]) -> org_type() == ANT) {
            die(*(world -> grid[position_x][right])); //ant dies
            Organism new_org = *(world -> grid[position_x][right]);
            old_org.hunger = 0;
            old_org.breeding_counter++;
            has_moved = true;
            world -> ant_counter--;
            world -> swapOrganisms(old_org,new_org);
        }
    }

    // swap positions if empty

    if(old_org.org_type() != SPACE && new_x < 20 && new_y < 20 && new_x >= 0 && new_y >= 0 && !has_moved) {

        has_moved = true;
        old_org.breeding_counter++;
        if (old_org.org_type() == BUG) hunger++;

        Organism new_org = *(world -> grid[new_x][new_y]);

        if (new_org.org_type() == SPACE) {

            world -> swapOrganisms(old_org, new_org);

        }

    }

}

void Organism::breed() {

    int up = position_x + 1;
    int down = position_x - 1;
    int left = position_y - 1;
    int right = position_y + 1;

    if ((organism_type == ANT && breeding_counter >= 3) || (organism_type == BUG && breeding_counter >= 8)) {

        if (up < 20 && (world->grid[up][position_y])->org_type() == SPACE) {

            breeding_counter = 0;
            (world->grid[up][position_y])->organism_type = organism_type;
            (world->grid[up][position_y])->breeding_counter = 0;
            (world->grid[up][position_y])->hunger = 0;
            (world->grid[up][position_y])->lifespan = 0;
            (world->grid[up][position_y])->has_moved = true;

            if(organism_type == ANT) (world->ant_counter)++;
            if(organism_type == BUG) (world->bug_counter)++;

        } else if (down >= 0 && (world->grid[down][position_y])->org_type() == SPACE) {

            breeding_counter = 0;
            (world->grid[down][position_y])->organism_type = organism_type;
            (world->grid[down][position_y])->breeding_counter = 0;
            (world->grid[down][position_y])->hunger = 0;
            (world->grid[down][position_y])->lifespan = 0;
            (world->grid[down][position_y])->has_moved = true;
            if(organism_type == ANT) (world->ant_counter)++;
            if(organism_type == BUG) (world->bug_counter)++;

        } else if (right < 20 && (world->grid[position_x][right])->org_type() == SPACE) {

            breeding_counter = 0;
            (world->grid[position_x][right])->organism_type = organism_type;
            (world->grid[position_x][right])->breeding_counter = 0;
            (world->grid[position_x][right])->hunger = 0;
            (world->grid[position_x][right])->lifespan = 0;
            (world->grid[position_x][right])->has_moved = true;
            if(organism_type == ANT) (world->ant_counter)++;
            if(organism_type == BUG) (world->bug_counter)++;

        } else if (left >= 0 && (world->grid[position_x][left])->org_type() == SPACE) {

            breeding_counter = 0;
            (world->grid[position_x][left])->organism_type = organism_type;
            (world->grid[position_x][left])->breeding_counter = 0;
            (world->grid[position_x][left])->hunger = 0;
            (world->grid[position_x][left])->lifespan = 0;
            (world->grid[position_x][left])->has_moved = true;
            if(organism_type == ANT) (world->ant_counter)++;
            if(organism_type == BUG) (world->bug_counter)++;

        }
    }
}

void Organism::die(Organism &dead_organism) {

    dead_organism.organism_type = SPACE;
    dead_organism.breeding_counter = 0;
    dead_organism.lifespan = 0;
    dead_organism.hunger = 0;
    dead_organism.has_moved = false;

}

void World::advanceTime() {

    time_step++;

    // move organisms / eat organisms

    for(int i = 0; i < grid_size; i++) {
        for(int j = 0; j < grid_size; j++) {

            if(grid[i][j] -> org_type() == Organism::ANT) {

                grid[i][j] -> move();
                grid[i][j] -> breed();

            }

            else if(grid[i][j] -> org_type() == Organism::BUG) {

                grid[i][j] -> move();
                grid[i][j] -> breed();

            }
        }
    }

    // reset has_moved
    for(int i = 0; i < grid_size; i++) {

        for (int j = 0; j < grid_size; j++) {
            (grid[i][j] -> has_moved) = false;
        }
    }

    printWorld();

}