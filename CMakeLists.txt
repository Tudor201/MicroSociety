cmake_minimum_required(VERSION 3.26)
project(MicroSociety)

set(CMAKE_CXX_STANDARD 20)

add_executable(MicroSociety src/main.cpp
        core/Position.h
        core/Simulation.cpp
        core/Simulation.h
        core/World.cpp
        core/World.h
        agents/Agent.cpp
        agents/Agent.h
        agents/HumanAgent.cpp
        agents/HumanAgent.h
        agents/WorkerAgent.cpp
        agents/WorkerAgent.h
        actions/Action.h
        actions/MoveAction.cpp
        actions/MoveAction.h
        ai/DecisionStrategy.h
        ai/NeedsBasedStrategy.cpp
        ai/NeedsBasedStrategy.h
        patterns/AgentFactory.cpp
        patterns/AgentFactory.h)
