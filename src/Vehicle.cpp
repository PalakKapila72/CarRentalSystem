#include "Vehicle.h"
#include "Sedan.h"
#include "SUV.h"
#include "Hatchback.h"
#include <sstream>

// ==========================================
// Base Class: Vehicle
// ==========================================
Vehicle::Vehicle(std::string id, std::string brand, std::string model, 
                 std::string licensePlate, double baseRatePerDay, bool isRented)
    : id(id), brand(brand), model(model), licensePlate(licensePlate), 
      baseRatePerDay(baseRatePerDay), isRented(isRented) {}

void Vehicle::displayDetails() const {
    std::cout << " | " << std::left << std::setw(6)  << id
              << " | " << std::setw(10) << getCategory()
              << " | " << std::setw(12) << (brand + " " + model)
              << " | " << std::setw(14) << licensePlate
              << " | Rs. " << std::right << std::setw(7) << std::fixed << std::setprecision(2) << baseRatePerDay
              << " | " << std::setw(12) << (isRented ? "RENTED" : "AVAILABLE")
              << " | " << std::left << std::setw(22) << getSpecialFeature()
              << " |" << std::endl;
}

std::string Vehicle::serialize() const {
    std::ostringstream oss;
    oss << getCategory() << "|" << id << "|" << brand << "|" 
        << model << "|" << licensePlate << "|" << baseRatePerDay << "|" 
        << (isRented ? "1" : "0");
    return oss.str();
}

// ==========================================
// Derived Class: Sedan
// ==========================================
Sedan::Sedan(std::string id, std::string brand, std::string model, 
             std::string licensePlate, double baseRatePerDay, 
             int bootSpaceLiters, bool hasLeatherSeats, bool isRented)
    : Vehicle(id, brand, model, licensePlate, baseRatePerDay, isRented),
      bootSpaceLiters(bootSpaceLiters), hasLeatherSeats(hasLeatherSeats) {}

double Sedan::calculateRentalCost(int days) const {
    double comfortFee = 300.0; // Daily executive comfort surcharge
    return (baseRatePerDay + comfortFee) * days;
}

std::string Sedan::getSpecialFeature() const {
    return std::to_string(bootSpaceLiters) + "L Boot" + (hasLeatherSeats ? ", Leather" : "");
}

void Sedan::displayDetails() const {
    Vehicle::displayDetails();
}

std::string Sedan::serialize() const {
    return Vehicle::serialize() + "|" + std::to_string(bootSpaceLiters) + "|" + (hasLeatherSeats ? "1" : "0");
}

// ==========================================
// Derived Class: SUV
// ==========================================
SUV::SUV(std::string id, std::string brand, std::string model, 
         std::string licensePlate, double baseRatePerDay, 
         bool is4x4, int seatingCapacity, bool isRented)
    : Vehicle(id, brand, model, licensePlate, baseRatePerDay, isRented),
      is4x4(is4x4), seatingCapacity(seatingCapacity) {}

double SUV::calculateRentalCost(int days) const {
    // 15% rugged capability and power surcharge
    return (baseRatePerDay * 1.15) * days;
}

std::string SUV::getSpecialFeature() const {
    return std::to_string(seatingCapacity) + "-Seater" + (is4x4 ? ", 4x4 AWD" : ", FWD");
}

void SUV::displayDetails() const {
    Vehicle::displayDetails();
}

std::string SUV::serialize() const {
    return Vehicle::serialize() + "|" + (is4x4 ? "1" : "0") + "|" + std::to_string(seatingCapacity);
}

// ==========================================
// Derived Class: Hatchback
// ==========================================
Hatchback::Hatchback(std::string id, std::string brand, std::string model, 
                     std::string licensePlate, double baseRatePerDay, 
                     double mileageKmpl, bool isRented)
    : Vehicle(id, brand, model, licensePlate, baseRatePerDay, isRented),
      mileageKmpl(mileageKmpl) {}

double Hatchback::calculateRentalCost(int days) const {
    // 10% economy city-commute discount
    return (baseRatePerDay * 0.90) * days;
}

std::string Hatchback::getSpecialFeature() const {
    std::ostringstream oss;
    oss << "Mileage: " << std::fixed << std::setprecision(1) << mileageKmpl << " km/l";
    return oss.str();
}

void Hatchback::displayDetails() const {
    Vehicle::displayDetails();
}

std::string Hatchback::serialize() const {
    std::ostringstream oss;
    oss << Vehicle::serialize() << "|" << mileageKmpl;
    return oss.str();
}
