#include <iostream>
#include "doodlebug.h"

using namespace std;


int main() {

    srand((unsigned) time(NULL));

    World world;
    world.initialize();
    world.printWorld();

    string temp;

    while (temp != "exit") {

        cout << "To move to the next time step, press enter. Else, type any key and press enter." << endl;
        getline(cin, temp);
        if (!temp.empty()) return 0;

        // new time step function, which moves all ants and bugs
        world.advanceTime();

    }

    return 0;
}
