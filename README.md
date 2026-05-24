# MicroSociety

A C++20 console-based agent simulation where a small society of autonomous citizens lives, works, eats, ages, reproduces, and dies — all driven by a needs-based AI decision engine and a fully configurable world.

---

## Overview

MicroSociety places a population of agents on a 2D grid and advances them through discrete time steps called **ticks**. On every tick, each living agent evaluates its own needs (hunger, energy, money, happiness, health) and autonomously picks an action. The world handles births, deaths, living costs, and population density — all within limits set by a plain-text config file. The full simulation state can be saved and reloaded between sessions.

---

## Features

- **Autonomous agents** — each citizen decides its own actions every tick with no manual intervention required
- **Three agent types** — Workers, Traders, and Students, each with distinct economic behaviour
- **Needs-based AI** — a priority-ordered decision strategy evaluates hunger, energy, money, and health before choosing an action
- **Life cycle** — agents age over time, reproduce when conditions are right, and die from old age or poor health
- **Living costs** — every tick deducts a maintenance fee; agents who can't pay suffer hunger, happiness, and health penalties
- **Event system** — an EventBus publishes typed simulation events (spawn, move, eat, work, rest, die, born) that are logged and displayed in-session
- **Statistics panel** — per-tick report covering population breakdown, averages for all stats, richest agent, oldest agent, and max cell density
- **Interactive map** — ASCII grid showing the number of agents in each cell
- **Save / Load** — full world state (all agent types with type-specific fields) persisted to and restored from `data/save.txt`
- **Runtime config editor** — view and change any simulation parameter mid-run without restarting
- **Structured menus** — hierarchical console UI for playing, inspecting, and managing the simulation

---

## Project Structure

```
MicroSociety/
├── src/
│   └── main.cpp                  # Entry point
├── core/
│   ├── Simulation.cpp/.h         # Main loop, menus, tick management
│   ├── World.cpp/.h              # Grid, agent collection, reproduction, living costs
│   ├── SimulationConfig.cpp/.h   # Singleton config loaded from data/config.txt
│   ├── Grid.h                    # Generic 2D grid template
│   ├── Position.h                # 2D coordinate type
│   ├── CellType.h                # Cell terrain enum
│   ├── RandomGenerator.cpp/.h    # Singleton Mersenne Twister RNG
│   └── Exceptions.h              # Custom exception hierarchy
├── agents/
│   ├── Agent.cpp/.h              # Abstract base class with all vital stats
│   ├── HumanAgent.cpp/.h         # Intermediate class wiring the decision strategy
│   ├── WorkerAgent.cpp/.h        # Earns a salary; job title randomised on spawn
│   ├── TraderAgent.cpp/.h        # Earns profit per trade
│   └── StudentAgent.cpp/.h       # Spends money; accumulates knowledge level
├── ai/
│   ├── DecisionStrategy.h        # Strategy interface
│   └── NeedsBasedStrategy.cpp/.h # Concrete priority-based decision logic
├── actions/
│   ├── Action.h                  # Action interface
│   ├── EatAction.cpp/.h          # Spends money, reduces hunger, boosts energy/happiness
│   ├── WorkAction.cpp/.h         # Delegates to agent's performWork(); guards age check
│   ├── RestAction.cpp/.h         # Restores energy; gentle hunger/happiness bump
│   └── MoveAction.cpp/.h         # Random cardinal-direction move; boundary-checked
├── patterns/
│   ├── AgentFactory.cpp/.h       # Factory for all three agent types with randomised stats
│   ├── EventBus.cpp/.h           # Singleton pub/sub event dispatcher
│   └── Event.h                   # SimulationEvent type and EventType enum
├── systems/
│   ├── SaveManager.cpp/.h        # Text-based serialisation / deserialisation (V3 format)
│   ├── StatisticsManager.cpp/.h  # Aggregates and prints per-tick population stats
│   └── EventLogger.cpp/.h        # Subscribes to EventBus; stores and replays recent events
├── utils/
│   └── TemplateUtils.h           # Generic helpers (countMatching, findMax, …)
└── data/
    ├── config.txt                # World parameters (see Configuration section)
    └── save.txt                  # Auto-generated save file (gitignored)
```

---

## Agent Types

| Type | Work behaviour | Earns money? | Special field |
|------|---------------|:---:|---------------|
| **Worker** | Performs a job (Builder / Engineer / Mechanic), receives salary | Yes | `salary`, `jobName` |
| **Trader** | Executes a trade, receives profit | Yes | `profitPerTrade` |
| **Student** | Studies, gains knowledge, pays tuition cost | No | `knowledgeLevel`, `university` |

All agents share the same vital stats: `hunger`, `energy`, `money`, `happiness`, `health`, `age`, and `ticksLived`. Stats are clamped to [0, 100] except `money` and `age`.

---

## Decision Logic (NeedsBasedStrategy)

Every tick each agent evaluates conditions in this priority order:

1. **Health < 45 or Energy < 30** → Rest
2. **Hunger > 65 and has money** → Eat
3. **Hunger > 65, no money, adult, can earn** → Work
4. **Hunger > 65, no money, otherwise** → Move
5. **Not adult** → Move
6. **Can earn money and money < 150** → Work
7. **Cannot earn but can work without pay, and energy/happiness/money thresholds met** → Work (Study)
8. **Happiness < 35** → Move
9. **Default** → Move

---

## Life Cycle

**Aging** — every `ticksPerYear` ticks an agent's age increments by 1.

**Health decay** — health decreases each tick if hunger > 80 (−5), energy < 20 (−3), or happiness < 20 (−2). It recovers (+1) when the agent is well-fed, rested, and happy.

**Death** — an agent dies when health reaches 0 or age exceeds `maxAge`.

**Reproduction** — two adjacent adults (age ≤ 60) with health > 60, happiness > 70, energy > 50, and money > 80 have a `reproductionChancePercent` chance each tick of producing a child. The child's type is chosen randomly; parents each lose 10 energy and 10 money. Births are capped at `maxBirthsPerTick` per tick and respect `maxPopulation`.

**Living cost** — every agent pays `livingCostPerTick` each tick. Agents who cannot afford it suffer hunger, happiness, and health penalties instead.

---

## Configuration

Edit `data/config.txt` before running, or use the in-game config editor (Manage World → Show / edit config).

| Key | Default | Description |
|-----|---------|-------------|
| `mapWidth` | 10 | Grid columns |
| `mapHeight` | 10 | Grid rows |
| `initialPopulation` | 6 | Agents spawned at startup |
| `maxTicks` | 10 | Simulation stops after this many ticks (editable in-game) |
| `foodPrice` | 10 | Cost to eat |
| `maxAge` | 90 | Agents older than this are removed |
| `maxPopulation` | 25 | Hard cap on total agents |
| `reproductionChancePercent` | 15 | Percent chance of birth per eligible pair per tick |
| `ticksPerYear` | 12 | Ticks required to age one year |
| `adultAge` | 18 | Minimum age to work or reproduce |
| `maxBirthsPerTick` | 2 | Maximum new births per tick |
| `livingCostPerTick` | 2 | Money deducted from every agent each tick |
| `maxStoredEvents` | 20 | Event log ring-buffer size |

---

## Building

**Requirements:** C++20 compiler (GCC 10+ / Clang 12+ / MSVC 2019+), CMake ≥ 3.26.

```bash
git clone <repo-url>
cd MicroSociety
cmake -S . -B build
cmake --build build
./build/MicroSociety
```

With CLion or another CMake-aware IDE, open the root folder and build the `MicroSociety` target directly.

---

## Running

```
./MicroSociety
```

On first run the world is initialised with `initialPopulation` agents (alternating Worker / Trader / Student). On subsequent runs, the save file at `data/save.txt` is loaded automatically if it exists.

### Main menu

```
1. Play simulation      — advance ticks (1, 5, or custom)
2. Inspect society      — map, statistics, agents, events, full report
3. Manage world         — spawn agents, save/load, edit config
0. Exit
```

---

## Save Format

Save files use a versioned plain-text format (`MICROSOCIETY_SAVE_V3`). Each line after the header encodes one agent's type, id, position, all vital stats, and type-specific fields (`salary`/`jobName` for Workers, `profitPerTrade` for Traders, `university`/`knowledgeLevel` for Students). The format is written and parsed by `SaveManager` and is forwards-incompatible with older versions.

---

## Design Patterns Used

| Pattern | Where |
|---------|-------|
| **Strategy** | `DecisionStrategy` / `NeedsBasedStrategy` — swappable AI behaviour per agent |
| **Factory** | `AgentFactory` — centralised agent creation with randomised stats |
| **Singleton** | `SimulationConfig`, `EventBus`, `RandomGenerator` |
| **Observer / Pub-Sub** | `EventBus` + `EventLogger` — decoupled event routing |
| **Template Method** | `Agent::update` dispatches to virtual `performWork` / `display` / `clone` |
| **Prototype** | `Agent::clone()` — deep copy via virtual method |

---

## Exception Hierarchy

```
std::runtime_error
└── MicroSocietyException
    ├── InvalidAgentException   — bad agent id or unknown type
    ├── WorldException          — out-of-bounds grid access
    └── ConfigException         — invalid configuration values
```
