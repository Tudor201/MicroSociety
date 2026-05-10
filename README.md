# MicroSociety

MicroSociety is a C++ project that simulates a small society using autonomous agents.

The project is built for an Object-Oriented Programming course and focuses on applying important OOP concepts such as classes, inheritance, polymorphism, abstract classes, dynamic casting, smart pointers, templates, and design patterns.

The idea of the project is to create a simplified world where agents can move, make decisions, and interact with the simulation over time.

---

## Project Idea

MicroSociety is a small agent-based simulator.

The simulation contains agents that represent people in a simplified society. Each agent can have different attributes, such as:

- hunger
- energy
- money
- happiness
- position in the world
- role in society

During the simulation, each agent updates its state and chooses an action. For example, an agent may move, work, rest, or perform another action depending on its needs.

The project does not try to perfectly simulate real society. It is a simplified model created to demonstrate object-oriented design and autonomous behavior.

---

## Main Goals

The main goals of this project are:

- to create a clean C++ project structure;
- to use object-oriented programming concepts correctly;
- to implement a simple simulation loop;
- to create different types of agents;
- to allow agents to choose actions automatically;
- to use modern C++ features such as smart pointers;
- to include design patterns in a natural way.

---

## Planned Features

- Basic simulation loop
- World that stores and updates agents
- Multiple types of agents
- Agent movement
- Agent needs system
- Actions performed by agents
- Decision-making strategies
- Factory for creating agents
- Singleton for configuration
- Template-based utility class
- Save/load system
- Basic statistics about the simulation

---

## OOP Concepts Used

This project is planned to include the following OOP concepts:

- classes and objects
- constructors and destructors
- encapsulation
- inheritance
- abstract classes
- virtual functions
- polymorphism
- dynamic casting
- smart pointers
- templates
- design patterns

---

## Design Patterns

The project will use several design patterns:

### Factory Pattern

Used to create agents without placing object creation logic everywhere in the code.

Example:

```cpp
AgentFactory::createAgent(AgentType::Worker);
```

### Strategy Pattern

Used for agent decision-making.

Different agents may use different strategies for choosing their next action.

### Singleton Pattern

Used for global configuration, such as simulation settings.

Example:

```cpp
SimulationConfig::getInstance();
```

---

## Project Structure

```txt
MicroSociety/
│
├── src/
│   └── main.cpp
│
├── core/
│   ├── Position.h
│   ├── Simulation.h
│   ├── Simulation.cpp
│   ├── World.h
│   └── World.cpp
│
├── agents/
│   ├── Agent.h
│   ├── Agent.cpp
│   ├── HumanAgent.h
│   ├── HumanAgent.cpp
│   ├── WorkerAgent.h
│   └── WorkerAgent.cpp
│
├── actions/
│   ├── Action.h
│   ├── MoveAction.h
│   └── MoveAction.cpp
│
├── ai/
│   ├── DecisionStrategy.h
│   ├── NeedsBasedStrategy.h
│   └── NeedsBasedStrategy.cpp
│
├── patterns/
│   ├── AgentFactory.h
│   └── AgentFactory.cpp
│
├── CMakeLists.txt
├── .gitignore
└── README.md
```

---

## Architecture

The basic architecture of the project is:

```txt
main
 ↓
Simulation
 ↓
World
 ↓
Agent
 ↓
DecisionStrategy
 ↓
Action
```

### Simulation

The `Simulation` class controls the main loop of the program.

It is responsible for:

- starting the simulation;
- updating the world;
- displaying the current state;
- controlling whether the simulation is running.

### World

The `World` class represents the environment where agents exist.

It is responsible for:

- storing agents;
- updating all agents;
- managing world-level information.

### Agent

The `Agent` class is the base class for all agents.

It defines common data and behavior for all agent types.

### Action

The `Action` class is the base class for actions that agents can perform.

Examples of actions:

- moving;
- working;
- resting;
- eating.

### DecisionStrategy

The `DecisionStrategy` class is used to decide what an agent should do next.

This separates the decision-making logic from the agent class.

---

## Technologies Used

- C++
- CMake
- CLion
- Git
- GitHub

---

## Build Instructions

The project uses CMake.

To build the project manually:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

To run the project:

```bash
./MicroSociety
```

On Windows, the executable may be:

```bash
MicroSociety.exe
```

---

## Current Status

The project is currently in development.

Current stage:

- project structure created;
- basic files prepared;
- first simulation classes are being implemented.

---

## Future Improvements

Possible future improvements:

- graphical interface;
- more agent types;
- more actions;
- economy system;
- event system;
- save/load functionality;
- statistics display;
- better decision-making logic.

---

## Author

Tudor Dumitrache

Computer Science student  
Faculty of Mathematics and Computer Science, University of Bucharest

GitHub: [Tudor201](https://github.com/Tudor201)