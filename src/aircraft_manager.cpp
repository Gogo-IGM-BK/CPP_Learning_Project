#include "aircraft_manager.hpp"

#include <utility>
#include <algorithm>
void AircraftManager::add(std::unique_ptr<Aircraft> aircraft)
{
    aircrafts.emplace_back(std::move(aircraft));
}

bool AircraftManager::update()
{
    std::sort(aircrafts.begin(), aircrafts.end(), [] (const std::unique_ptr<Aircraft>& a,const std::unique_ptr<Aircraft>& b) { return std::make_tuple(!a->has_terminal(),a->get_fuel()) < std::make_tuple(!b->has_terminal(),b->get_fuel()); } );
    aircrafts.erase(std::remove_if(aircrafts.begin(), aircrafts.end(), [](std::unique_ptr<Aircraft> &aircraft){ return !aircraft->update(); }), aircrafts.end());

    return true;
}

int AircraftManager::nbAirk(const std::string& airline){
    return std::count_if(aircrafts.begin(), aircrafts.end(),[airline](std::unique_ptr<Aircraft>& aircraft){return aircraft->get_flight_num().rfind(airline, 0)==0;});
    
}

