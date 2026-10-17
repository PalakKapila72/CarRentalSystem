#ifndef SUV_H
#define SUV_H

#include "Vehicle.h"

class SUV : public Vehicle {
private:
    bool is4x4;
    int seatingCapacity;

public:
    SUV(std::string id, std::string brand, std::string model, 
        std::string licensePlate, double baseRatePerDay, 
        bool is4x4 = true, int seatingCapacity = 7, bool isRented = false);

    double calculateRentalCost(int days) const override;
    std::string getCategory() const override { return "SUV"; }
    std::string getSpecialFeature() const override;

    void displayDetails() const override;
    std::string serialize() const override;

    bool getIs4x4() const { return is4x4; }
    int getSeatingCapacity() const { return seatingCapacity; }
};

#endif // SUV_H
