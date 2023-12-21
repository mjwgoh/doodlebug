# README for Doodlebug Simulation Program

## Overview
This Doodlebug Simulation Program is designed to simulate a basic ecosystem involving doodlebugs (predators) and ants (prey). It uses C++ and object-oriented programming principles to create an interactive grid world where organisms move, breed, eat, and die according to specific rules. 

## Files
- `doodlebug.h`: Header file containing the declarations of the `Organism`, `Ant`, `Doodlebug`, and `World` classes.
- `main.cpp`: Main program file that drives the simulation.

## Classes
- `Organism`: Base class for organisms in the world, with common properties and behaviors.
- `Ant`: Derived class representing an ant.
- `Doodlebug`: Derived class representing a doodlebug.
- `World`: Class that manages the grid and orchestrates the interactions between organisms.

## Key Methods
- `World::printWorld()`: Prints the current state of the world, including time step and organism counts.
- `World::rand_initialize(int, int)`: Randomly initializes organisms on the grid.
- `World::initialize()`: Sets up the initial state of the world.
- `World::swapOrganisms(Organism&, Organism&)`: Swaps two organisms on the grid.
- `Organism::move()`: Defines the movement behavior of organisms.
- `Organism::breed()`: Handles the breeding mechanism of organisms.
- `Organism::die(Organism&)`: Represents the death of an organism.
- `World::advanceTime()`: Advances the simulation by one time step, updating the state of the world.

## Compilation and Execution
To compile and run the program, use a C++ compiler. For example:
```bash
g++ -o doodlebug_simulation main.cpp
./doodlebug_simulation
