#pragma once

#include "GL/dynamic_object.hpp"
#include "aircraft.hpp"

#include <memory>
#include <vector>

class AircraftManager : public GL::DynamicObject
{
private:
    std::vector<std::unique_ptr<Aircraft>> aircrafts;

public:
    void add(std::unique_ptr<Aircraft> aircraft);

    bool update() override;
    void sort() ;
    bool compare(const std::unique_ptr<Aircraft> &a, const std::unique_ptr<Aircraft> &b) const;
    int nbAirk(const std::string& airline);

};