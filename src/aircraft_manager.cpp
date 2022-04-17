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

int AircraftManager::get_required_fuel() const
{
    
    return std::accumulate(aircrafts.begin(),aircrafts.end(),0,[](const int acc,const std::unique_ptr<Aircraft> &a)
    {if( a->is_low_on_fuel() && !a->service_finished()) 
        return acc + (Aircraft::MAXI_FUEL - a->get_fuel()) ; 
    return acc;});
    
}

