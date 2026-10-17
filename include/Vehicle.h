#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <iomanip>

class Vehicle {
protected:
    std::string id;
    std::string brand;
    std::string model;
    std::string licensePlate;
    double baseRatePerDay;
    bool isRented;

public:
    Vehicle(std::string id, std::string brand, std::string model, 
            std::string licensePlate, double baseRatePerDay, bool isRented = false);
    
    virtual ~Vehicle() = default;

    // Pure virtual functions (Abstraction & Polymorphism)
    virtual double calculateRentalCost(int days) const = 0;
    virtual std::string getCategory() const = 0;
    virtual std::string getSpecialFeature() const = 0;

    // Virtual display and serialization methods
    virtual void displayDetails() const;
    virtual std::string serialize() const;

    // Getters
    std::string getId() const { return id; }
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    std::string getLicensePlate() const { return licensePlate; }
    double getBaseRatePerDay() const { return baseRatePerDay; }
    bool getIsRented() const { return isRented; }

    // Setters
    void setRented(bool rented) { isRented = rented; }
    void setBaseRate(double rate) { baseRatePerDay = rate; }
};

#endif // VEHICLE_H
