#ifndef SEDAN_H
#define SEDAN_H

#include "Vehicle.h"

class Sedan : public Vehicle {
private:
    int bootSpaceLiters;
    bool hasLeatherSeats;

public:
    Sedan(std::string id, std::string brand, std::string model, 
          std::string licensePlate, double baseRatePerDay, 
          int bootSpaceLiters = 450, bool hasLeatherSeats = true, bool isRented = false);

    double calculateRentalCost(int days) const override;
    std::string getCategory() const override { return "Sedan"; }
    std::string getSpecialFeature() const override;

    void displayDetails() const override;
    std::string serialize() const override;

    int getBootSpace() const { return bootSpaceLiters; }
    bool getLeatherSeats() const { return hasLeatherSeats; }
};

#endif // SEDAN_H
