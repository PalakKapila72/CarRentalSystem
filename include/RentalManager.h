#ifndef RENTAL_MANAGER_H
#define RENTAL_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include "Vehicle.h"
#include "Sedan.h"
#include "SUV.h"
#include "Hatchback.h"
#include "Customer.h"
#include "RentalRecord.h"

class RentalManager {
private:
    std::vector<std::unique_ptr<Vehicle>> vehicles;
    std::vector<Customer> customers;
    std::vector<RentalRecord> records;

    const std::string VEHICLES_FILE = "data/vehicles.txt";
    const std::string CUSTOMERS_FILE = "data/customers.txt";
    const std::string RENTALS_FILE = "data/rentals.txt";

    void seedInitialFleetIfEmpty();
    std::string getCurrentDate() const;

public:
    RentalManager();
    ~RentalManager() = default;

    // File Handling operations
    void loadData();
    void saveData();

    // Customer Operations
    bool registerCustomer(const std::string& name, const std::string& phone, const std::string& license);
    Customer* findCustomerById(const std::string& id);
    void displayAllCustomers() const;

    // Vehicle Operations
    void displayFleet(bool availableOnly = false) const;
    Vehicle* findVehicleById(const std::string& id);
    bool addVehicle(std::unique_ptr<Vehicle> vehicle);
    void searchVehicles(const std::string& keyword) const;

    // Booking & Rental Operations
    bool rentVehicle(const std::string& customerId, const std::string& vehicleId, int days);
    bool returnVehicle(const std::string& vehicleId, double damageCharges = 0.0, int lateDays = 0);
    void displayRentalHistory() const;

    // Analytics and Fleet Metrics
    void displayFleetAnalytics() const;
};

#endif // RENTAL_MANAGER_H
