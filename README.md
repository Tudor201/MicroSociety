# MicroSociety

MicroSociety is a C++20 console-based agent simulation project. It models a small society made of autonomous agents that live inside a grid world, choose actions based on their current needs, spend resources, age, reproduce, die, and generate events that can be inspected from an interactive menu.

The project was built as an Object-Oriented Programming project, so the focus is not only on the simulation itself, but also on demonstrating clean C++ design: inheritance, polymorphism, abstract classes, smart pointers, templates, custom exceptions, file I/O, and design patterns.

---

## Main Features

- Interactive console menu
- Grid-based world simulation
- Multiple agent types: `Worker`, `Trader`, `Student`
- Autonomous decision-making using a strategy object
- Agent actions: move, eat, rest, work/trade/study
- Agent needs system: hunger, energy, money, happiness, health, age
- Aging and life-status updates
- Living cost applied every tick
- Death system based on health and maximum age
- Reproduction system based on nearby compatible agents
- Save/load system using text files
- Configurable simulation values loaded from `data/config.txt`
- Event system using an `EventBus`
- Recent event logger
- Statistics system with population, type counts, averages, richest agent, oldest agent, and cell density
- Factory-based agent creation
- Singleton-based global configuration and random generator
- Custom exception hierarchy
- Template-based grid and utility functions

---

## How the Simulation Works

The program starts from `main.cpp`, creates a `Simulation` object, and calls `simulation.run()`.

At startup, the simulation tries to load the world from:

```txt
data/save.txt
```

If the save file does not exist, a new world is created and populated with the default initial population from `data/config.txt`.

Each simulation tick does the following:

1. Every living agent chooses an action using `NeedsBasedStrategy`.
2. The chosen action is executed.
3. Living costs are applied.
4. Dead agents are removed.
5. Reproduction is handled.
6. Population density is recalculated.
7. The world, statistics, and recent events can be displayed.

---

## Interactive Menu

The simulation is controlled through a console menu:

```txt
1. Run simulation (N ticks)
2. Spawn agent manual
3. Show all agents
4. Show statistics
5. Show recent events
6. Save / Load
7. Show / edit config
0. Exit
```

### Menu Options

| Option | Description |
|---|---|
| `1` | Runs the simulation for a chosen number of ticks. |
| `2` | Manually creates a `Worker`, `Trader`, or `Student` using `AgentFactory`. |
| `3` | Displays all agents through `vector<unique_ptr<Agent>>`, demonstrating polymorphism. |
| `4` | Displays statistics about the current world. |
| `5` | Displays recent events collected through the event system. |
| `6` | Saves or loads the world from `data/save.txt`. |
| `7` | Shows and edits selected values from the singleton `SimulationConfig`. |
| `0` | Exits the simulation. |

---

## Agent Types

All agent types inherit from the abstract base class `Agent`, through `HumanAgent`.

### WorkerAgent

A worker has:

- salary
- job name
- ability to earn money through `performWork()`

Workers randomly receive one of these job names when created:

```txt
Builder
Engineer
Mechanic
```

### TraderAgent

A trader has:

- profit per trade
- ability to earn money through trading

When `performWork()` is called, the trader performs a trade and gains money.

### StudentAgent

A student has:

- university name
- knowledge level

Students do not earn money from work. Their `performWork()` behavior represents studying, which increases knowledge but costs energy and a small amount of money.

---

## Agent Attributes

Each agent stores:

| Attribute | Meaning |
|---|---|
| `id` | Unique identifier. |
| `position` | Position inside the grid world. |
| `hunger` | Higher value means the agent is more hungry. |
| `energy` | Lower value means the agent is more tired. |
| `money` | Agent's available money. |
| `happiness` | Agent's happiness level. |
| `health` | Agent's health level. |
| `age` | Agent's current age. |
| `ticksLived` | Number of ticks lived. |
| `alive` | Whether the agent is still alive. |

Most bounded values are clamped between `0` and `100`.

---

## Actions

Actions inherit from the abstract class `Action`.

### MoveAction

Moves the agent randomly in one of four directions if the new position is inside the world.

Effects:

- increases hunger
- decreases energy
- publishes an event

### EatAction

Allows an agent to buy food if it has enough money.

Effects:

- decreases money
- decreases hunger
- increases energy
- increases happiness
- publishes an event

### RestAction

Allows an agent to recover energy.

Effects:

- increases energy
- slightly increases hunger
- increases happiness
- publishes an event

### WorkAction

Calls the virtual method:

```cpp
agent.performWork();
```

This avoids using chains of `dynamic_cast` and lets each derived agent type define its own work behavior polymorphically.

---

## Decision-Making System

Decision-making is handled by the abstract class:

```cpp
DecisionStrategy
```

The concrete strategy is:

```cpp
NeedsBasedStrategy
```

The strategy chooses actions based on the agent's current state:

- low health -> rest
- low energy -> rest
- high hunger and enough money -> eat
- high hunger and able to earn money -> work
- low money and able to earn money -> work
- student with enough resources -> study
- otherwise -> move

`HumanAgent` owns its strategy with `shared_ptr` and also keeps a `weak_ptr` observer to demonstrate non-owning smart pointer usage.

---

## World System

The `World` class manages:

- world dimensions
- terrain grid
- population density grid
- all agents
- movement boundaries
- updates per tick
- initial spawning
- reproduction
- death removal
- living costs

The world uses:

```cpp
Grid<CellType> terrain;
Grid<int> populationDensity;
```

This demonstrates the same template class instantiated with multiple types.

`World::display()` builds a temporary `Grid<char>` display map instead of searching through all agents for every cell.

---

## Reproduction and Death

Agents can reproduce when they satisfy conditions such as:

- alive
- adult age
- close enough to another valid agent
- good health
- good happiness
- enough energy
- enough money

The reproduction logic is split into helper methods:

```cpp
canReproduce(const Agent& agent)
createChild(const Agent& parent1, const Agent& parent2)
agentIsAlreadyParent(int id, const std::vector<int>& usedParentIds)
```

Agents can die when their health reaches zero or when they exceed the configured maximum age.

---

## Statistics

`StatisticsManager` displays:

- total population
- number of alive agents
- number of workers
- number of traders
- number of students
- maximum number of agents in one cell
- richest agent
- oldest agent
- average hunger
- average energy
- average money
- average happiness
- average health
- average age

It uses template utility functions such as:

```cpp
findMax(...)
countMatching(...)
```

---

## Event System

The event system is built around:

```cpp
EventBus
SimulationEvent
EventLogger
```

`EventBus` is a singleton that allows systems to subscribe to event types and receive notifications when events are published.

Events include:

- `AgentSpawned`
- `AgentChoseAction`
- `AgentMoved`
- `AgentWorked`
- `AgentAte`
- `AgentRested`
- `AgentFailedAction`
- `AgentDied`
- `AgentBorn`

`EventLogger` stores recent `SimulationEvent` objects and formats them only when displayed.

The number of stored events is configurable through:

```txt
maxStoredEvents
```

---

## Save and Load System

The save system is implemented in:

```txt
systems/SaveManager.h
systems/SaveManager.cpp
```

The world is saved to:

```txt
data/save.txt
```

The save file starts with:

```txt
MICROSOCIETY_SAVE_V3
```

Then it stores the number of agents and the state of each agent.

Saved data includes:

- agent type
- id
- position
- hunger
- energy
- money
- happiness
- health
- age
- ticks lived
- type-specific data

Type-specific data:

| Type | Extra saved data |
|---|---|
| Worker | salary, job name |
| Trader | profit per trade |
| Student | university, knowledge level |

If the save file is missing, loading returns `false`, which is treated as a normal first-run case.

If the save file exists but has invalid or corrupted data, the program throws a custom `MicroSocietyException` or one of its derived exception types.

---

## Configuration File

Simulation settings are loaded from:

```txt
data/config.txt
```

If the file does not exist, fallback hardcoded defaults are used.

Current config keys:

```txt
mapWidth 10
mapHeight 10
initialPopulation 6
maxTicks 10
foodPrice 10
maxAge 90
maxPopulation 25
reproductionChancePercent 15
ticksPerYear 12
adultAge 18
maxBirthsPerTick 2
livingCostPerTick 2
maxStoredEvents 20
```

The config object is implemented as a singleton:

```cpp
SimulationConfig::getInstance();
```

Selected values can also be edited from the interactive menu.

---

## Custom Exceptions

Custom exceptions are defined in:

```txt
core/Exceptions.h
```

The hierarchy is:

```cpp
MicroSocietyException
├── InvalidAgentException
├── WorldException
└── ConfigException
```

Examples of usage:

- invalid agent id
- unknown agent type
- invalid save file format
- corrupted save data
- invalid grid access

---

## Templates

The project uses templates in two places.

### Grid<T>

`Grid<T>` is a reusable two-dimensional grid class.

It is used as:

```cpp
Grid<CellType> terrain;
Grid<int> populationDensity;
Grid<char> displayMap;
```

It also contains a compile-time constraint:

```cpp
static_assert(std::is_default_constructible_v<T>, "Grid requires default constructible types.");
```

### Template Utility Functions

Defined in:

```txt
utils/TemplateUtils.h
```

Functions:

```cpp
template <typename T>
T findMax(const std::vector<T>& values);

template <typename T, typename Predicate>
int countMatching(const std::vector<T>& values, Predicate predicate);
```

These are used by the statistics system.

---

## Smart Pointers

The project uses modern C++ smart pointers:

| Smart pointer | Usage |
|---|---|
| `std::unique_ptr<Agent>` | Owns agents stored inside the world. |
| `std::unique_ptr<Action>` | Owns actions returned by decision strategies. |
| `std::shared_ptr<DecisionStrategy>` | Shared strategy ownership inside `HumanAgent`. |
| `std::weak_ptr<DecisionStrategy>` | Non-owning observer of the current strategy. |

---

## Design Patterns Used

### Factory Pattern

Implemented by:

```txt
patterns/AgentFactory.h
patterns/AgentFactory.cpp
```

Used to create agents without spreading constructor logic throughout the code.

Example:

```cpp
AgentFactory::createAgent(AgentType::Worker, id);
```

### Strategy Pattern

Implemented by:

```txt
ai/DecisionStrategy.h
ai/NeedsBasedStrategy.h
ai/NeedsBasedStrategy.cpp
```

Used to separate decision-making from the agent classes.

### Singleton Pattern

Used by:

```txt
SimulationConfig
RandomGenerator
EventBus
```

### Observer / Event Bus Pattern

Implemented through:

```txt
EventBus
EventLogger
SimulationEvent
```

Actions and world events publish messages, while `EventLogger` subscribes and stores recent events.

---

## Project Structure

```txt
MicroSociety/
├── actions/
│   ├── Action.h
│   ├── EatAction.cpp / EatAction.h
│   ├── MoveAction.cpp / MoveAction.h
│   ├── RestAction.cpp / RestAction.h
│   └── WorkAction.cpp / WorkAction.h
│
├── agents/
│   ├── Agent.cpp / Agent.h
│   ├── HumanAgent.cpp / HumanAgent.h
│   ├── WorkerAgent.cpp / WorkerAgent.h
│   ├── TraderAgent.cpp / TraderAgent.h
│   └── StudentAgent.cpp / StudentAgent.h
│
├── ai/
│   ├── DecisionStrategy.h
│   └── NeedsBasedStrategy.cpp / NeedsBasedStrategy.h
│
├── core/
│   ├── CellType.h
│   ├── Exceptions.h
│   ├── Grid.h
│   ├── Position.h
│   ├── RandomGenerator.cpp / RandomGenerator.h
│   ├── Simulation.cpp / Simulation.h
│   ├── SimulationConfig.cpp / SimulationConfig.h
│   └── World.cpp / World.h
│
├── data/
│   ├── .gitkeep
│   └── config.txt
│
├── patterns/
│   ├── AgentFactory.cpp / AgentFactory.h
│   ├── Event.h
│   └── EventBus.cpp / EventBus.h
│
├── src/
│   └── main.cpp
│
├── systems/
│   ├── EventLogger.cpp / EventLogger.h
│   ├── SaveManager.cpp / SaveManager.h
│   └── StatisticsManager.cpp / StatisticsManager.h
│
├── utils/
│   └── TemplateUtils.h
│
├── CMakeLists.txt
├── .gitignore
└── README.md
```

---

## Build Instructions

The project uses CMake and requires a C++20-compatible compiler.

### Build from terminal

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Run

From the build directory:

```bash
./MicroSociety
```

On Windows, the executable may be:

```bash
MicroSociety.exe
```

### CLion

1. Open the project folder in CLion.
2. Let CLion load the `CMakeLists.txt` file.
3. Build the project.
4. Run the `MicroSociety` target.

---

## Example Usage

A typical session can look like this:

1. Start the program.
2. Choose option `3` to view the initial agents.
3. Choose option `1` and run `5` ticks.
4. Choose option `4` to inspect statistics.
5. Choose option `5` to inspect recent events.
6. Choose option `2` to manually spawn another agent.
7. Choose option `6` to save the world.
8. Exit with option `0`.

---

## Notes for Submission

Before submitting or uploading the project, the archive should contain only the source project files. It should not include generated or local-only folders such as:

```txt
.git/
.idea/
cmake-build-debug/
build/
*.exe
```

These files are not needed to build the project and can make the submission unnecessarily large.

---

## Possible Future Improvements

- Use terrain types more deeply, for example making markets useful for eating and workplaces useful for work.
- Save and restore the current simulation tick.
- Add more agent types.
- Add more decision strategies.
- Add a graphical interface.
- Add more complex social relationships between agents.
