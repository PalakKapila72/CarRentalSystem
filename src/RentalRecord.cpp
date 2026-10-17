#include "RentalRecord.h"
#include <sstream>
#include <vector>

RentalRecord::RentalRecord(std::string recordId, std::string customerId, 
                           std::string customerName, std::string vehicleId, 
                           std::string vehicleModel, int rentalDays, 
                           double totalCost, std::string status, 
                           std::string bookingDate)
    : recordId(recordId), customerId(customerId), customerName(customerName), 
      vehicleId(vehicleId), vehicleModel(vehicleModel), rentalDays(rentalDays), 
      totalCost(totalCost), status(status), bookingDate(bookingDate) {}

void RentalRecord::display() const {
    std::cout << " | " << std::left << std::setw(8)  << recordId
              << " | " << std::setw(8)  << customerId
              << " | " << std::setw(18) << customerName
              << " | " << std::setw(8)  << vehicleId
              << " | " << std::setw(16) << vehicleModel
              << " | " << std::right << std::setw(4)  << rentalDays << " d"
              << " | Rs. " << std::setw(9) << std::fixed << std::setprecision(2) << totalCost
              << " | " << std::left << std::setw(10) << status
              << " | " << std::setw(12) << bookingDate
              << " |" << std::endl;
}

std::string RentalRecord::serialize() const {
    std::ostringstream oss;
    oss << recordId << "|" << customerId << "|" << customerName << "|" 
        << vehicleId << "|" << vehicleModel << "|" << rentalDays << "|" 
        << totalCost << "|" << status << "|" << bookingDate;
    return oss.str();
}

RentalRecord RentalRecord::deserialize(const std::string& line) {
    std::stringstream ss(line);
    std::string segment;
    std::vector<std::string> tokens;

    while (std::getline(ss, segment, '|')) {
        tokens.push_back(segment);
    }

    if (tokens.size() >= 9) {
        int days = std::stoi(tokens[5]);
        double cost = std::stod(tokens[6]);
        return RentalRecord(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], days, cost, tokens[7], tokens[8]);
    }

    return RentalRecord();
}
