#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>
#include <iomanip>

class Customer {
private:
    std::string id;
    std::string name;
    std::string phone;
    std::string drivingLicense;
    std::string activeRentalVehicleId; // Empty if no active rental

public:
    Customer(std::string id = "", std::string name = "", 
             std::string phone = "", std::string drivingLicense = "", 
             std::string activeRentalVehicleId = "NONE");

    std::string getId() const { return id; }
    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }
    std::string getDrivingLicense() const { return drivingLicense; }
    std::string getActiveRentalVehicleId() const { return activeRentalVehicleId; }

    void setActiveRentalVehicleId(const std::string& vehicleId) { activeRentalVehicleId = vehicleId; }

    void display() const;
    std::string serialize() const;
    static Customer deserialize(const std::string& line);
};

#endif // CUSTOMER_H
