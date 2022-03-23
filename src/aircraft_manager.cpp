#include "aircraft_manager.hpp"

#include <utility>
#include <algorithm>
void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    // for (auto aircraft_it = aircrafts.begin(); aircraft_it != aircrafts.end();)
    // {
    //     // On doit déréférencer 2x pour obtenir une référence sur l'Aircraft : une fois pour déréférencer
    //     // l'itérateur, et une deuxième fois pour déréférencer le unique_ptr.
    //     auto& aircraft = **aircraft_it;
    //     if (aircraft.update())
    //     {
    //         ++aircraft_it;
    //     }
    //     else
    //     {
    //         aircraft_it = aircrafts.erase(aircraft_it);
    //     }
    // }

    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [](std::unique_ptr<Aircraft> &aircraft){ return !aircraft->update(); }), aircrafts.end());



    return true;
}

int AircraftManager::nbAirk(const std::string& airline){
    return std::count_if(aircrafts.begin(), aircrafts.end(),[airline](std::unique_ptr<Aircraft>& aircraft){return aircraft->get_flight_num().rfind(airline, 0)==0;});
    
}