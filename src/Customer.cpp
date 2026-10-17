#include "Customer.h"
#include <sstream>
#include <vector>

Customer::Customer(std::string id, std::string name, 
                   std::string phone, std::string drivingLicense, 
                   std::string activeRentalVehicleId)
    : id(id), name(name), phone(phone), 
      drivingLicense(drivingLicense), activeRentalVehicleId(activeRentalVehicleId) {}

void Customer::display() const {
    std::cout << " | " << std::left << std::setw(8)  << id
              << " | " << std::setw(20) << name
              << " | " << std::setw(15) << phone
              << " | " << std::setw(16) << drivingLicense
              << " | " << std::setw(14) << (activeRentalVehicleId == "NONE" ? "None (Active)" : activeRentalVehicleId)
              << " |" << std::endl;
}

std::string Customer::serialize() const {
    return id + "|" + name + "|" + phone + "|" + drivingLicense + "|" + activeRentalVehicleId;
}

Customer Customer::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string segment;
    std::vector<std::string> tokens;

    while (std::getline(ss, segment, '|')) {
        tokens.push_back(segment);
    }

    if (tokens.size() >= 5) {
        return Customer(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
    } else if (tokens.size() == 4) {
        return Customer(tokens[0], tokens[1], tokens[2], tokens[3], "NONE");
    }

    return Customer();
}
