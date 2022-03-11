#pragma once
#include "aircraft_manager.hpp"

class Airport;
struct AircraftType;

class TowerSimulation
{
private:
    bool help        = false;
    Airport* airport = nullptr;
    AircraftManager manager;

    TowerSimulation(const TowerSimulation&) = delete;
    TowerSimulation& operator=(const TowerSimulation&) = delete;

    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type) const;
    std::unique_ptr<Aircraft> create_random_aircraft() const;

    void create_keystrokes() const;
    void display_help() const;

    void init_airport();

public:
    TowerSimulation(int argc, char** argv);
    ~TowerSimulation();

    void launch();
};
