#pragma once

#include "GL/texture.hpp"
#include "img/image.hpp"
#include "img/media_path.hpp"
#include "aircraft.hpp"
#include "aircraft_types.hpp"
#include "aircraft_manager.hpp"
#include "airport.hpp"

class AircraftFactory
{
    private:
        
        
        std::set<std::string> flying_nb = {};
        
        const std::array<AircraftType,3> aircraft_types {   AircraftType { .02f, .05f, .02f, MediaPath { "l1011_48px.png" } },
        AircraftType { .02f, .05f, .02f, MediaPath { "b707_jat.png" } },
        AircraftType { .02f, .08f, .04f, MediaPath { "concorde_af.png" } } };



    public:
    
    const std::array<std::string,AIRLINES_NUMBER> airlines = { "AF", "LH", "EY", "DL", "KL", "BA", "AY", "EY" }; 

     std::unique_ptr<Aircraft> create_random_aircraft(Airport& airport ) 
    {
       return  create_aircraft(aircraft_types[rand() % 3],airport);
    }


    std::unique_ptr<Aircraft> create_aircraft(const AircraftType& type,Airport& airport )
    {
        
        const std::string flight_number = airlines[std::rand() % 8] + std::to_string(1000 + (rand() % 9000));
        if(flying_nb.count(flight_number)>=1){
            return nullptr;
        }
        flying_nb.insert(flight_number);
        const float angle       = (rand() % 1000) * 2 * 3.141592f / 1000.f; // random angle between 0 and 2pi
        const Point3D start     = Point3D { std::sin(angle), std::cos(angle), 0 } * 3 + Point3D { 0, 0, 2 };
        const Point3D direction = (-start).normalize();

        
        // La gestion des Aircrafts se fait maintenant via des unique_ptr de bout en bout.
        return std::make_unique<Aircraft>(type, flight_number, start, direction, airport.get_tower());
    }
















};
