#ifndef HATCHBACK_H
#define HATCHBACK_H

#include "Vehicle.h"

class Hatchback : public Vehicle {
private:
    double mileageKmpl;

public:
    Hatchback(std::string id, std::string brand, std::string model, 
              std::string licensePlate, double baseRatePerDay, 
              double mileageKmpl = 20.5, bool isRented = false);

    double calculateRentalCost(int days) const override;
    std::string getCategory() const override { return "Hatchback"; }
    std::string getSpecialFeature() const override;

    void displayDetails() const override;
    std::string serialize() const override;

    double getMileage() const { return mileageKmpl; }
};

#endif // HATCHBACK_H
