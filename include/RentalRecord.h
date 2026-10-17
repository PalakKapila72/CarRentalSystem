#ifndef RENTAL_RECORD_H
#define RENTAL_RECORD_H

#include <string>
#include <iostream>
#include <iomanip>

class RentalRecord {
private:
    std::string recordId;
    std::string customerId;
    std::string customerName;
    std::string vehicleId;
    std::string vehicleModel;
    int rentalDays;
    double totalCost;
    std::string status; // "ACTIVE" or "RETURNED"
    std::string bookingDate;

public:
    RentalRecord(std::string recordId = "", std::string customerId = "", 
                 std::string customerName = "", std::string vehicleId = "", 
                 std::string vehicleModel = "", int rentalDays = 0, 
                 double totalCost = 0.0, std::string status = "ACTIVE", 
                 std::string bookingDate = "");

    std::string getRecordId() const { return recordId; }
    std::string getCustomerId() const { return customerId; }
    std::string getCustomerName() const { return customerName; }
    std::string getVehicleId() const { return vehicleId; }
    std::string getVehicleModel() const { return vehicleModel; }
    int getRentalDays() const { return rentalDays; }
    double getTotalCost() const { return totalCost; }
    std::string getStatus() const { return status; }
    std::string getBookingDate() const { return bookingDate; }

    void setStatus(const std::string& newStatus) { status = newStatus; }
    void setTotalCost(double newCost) { totalCost = newCost; }

    void display() const;
    std::string serialize() const;
    static RentalRecord deserialize(const std::string& line);
};

#endif // RENTAL_RECORD_H
