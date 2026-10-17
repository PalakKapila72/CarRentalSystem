#include "RentalManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <algorithm>

RentalManager::RentalManager() {
    loadData();
}

std::string RentalManager::getCurrentDate() const {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d-%m-%Y", ltm);
    return std::string(buffer);
}

void RentalManager::seedInitialFleetIfEmpty() {
    // 6 Realistic vehicles representing Sedan, SUV, and Hatchback
    vehicles.push_back(std::make_unique<Sedan>("V101", "Honda", "City ZX", "CH-01-AB-1011", 2200.0, 506, true, false));
    vehicles.push_back(std::make_unique<Sedan>("V102", "Hyundai", "Verna Turbo", "PB-65-AX-2022", 2400.0, 528, true, false));
    vehicles.push_back(std::make_unique<SUV>("V103", "Toyota", "Fortuner 4x4", "HR-26-DJ-3033", 4500.0, true, 7, false));
    vehicles.push_back(std::make_unique<SUV>("V104", "Mahindra", "Thar LX", "CH-01-TC-4044", 3200.0, true, 4, false));
    vehicles.push_back(std::make_unique<Hatchback>("V105", "Maruti", "Swift ZXi", "PB-10-BZ-5055", 1400.0, 23.2, false));
    vehicles.push_back(std::make_unique<Hatchback>("V106", "Hyundai", "i20 Asta", "HR-70-DA-6066", 1600.0, 20.3, false));

    // 2 Sample registered customers
    customers.push_back(Customer("C101", "Aman Sharma", "+91 98765 11223", "DL-CH01-2022001", "NONE"));
    customers.push_back(Customer("C102", "Priya Verma", "+91 98140 44556", "DL-PB65-2021008", "NONE"));

    saveData();
}

void RentalManager::loadData() {
    // 1. Load Vehicles
    std::ifstream vFile(VEHICLES_FILE);
    if (!vFile.is_open()) {
        seedInitialFleetIfEmpty();
        return;
    }

    std::string line;
    vehicles.clear();

    while (std::getline(vFile, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> tokens;
        while (std::getline(ss, segment, '|')) {
            tokens.push_back(segment);
        }

        if (tokens.size() >= 7) {
            std::string cat = tokens[0];
            std::string id = tokens[1];
            std::string brand = tokens[2];
            std::string model = tokens[3];
            std::string plate = tokens[4];
            double rate = std::stod(tokens[5]);
            bool rented = (tokens[6] == "1");

            if (cat == "Sedan" && tokens.size() >= 9) {
                int boot = std::stoi(tokens[7]);
                bool leather = (tokens[8] == "1");
                vehicles.push_back(std::make_unique<Sedan>(id, brand, model, plate, rate, boot, leather, rented));
            } else if (cat == "SUV" && tokens.size() >= 9) {
                bool is4x4 = (tokens[7] == "1");
                int seats = std::stoi(tokens[8]);
                vehicles.push_back(std::make_unique<SUV>(id, brand, model, plate, rate, is4x4, seats, rented));
            } else if (cat == "Hatchback" && tokens.size() >= 8) {
                double mileage = std::stod(tokens[7]);
                vehicles.push_back(std::make_unique<Hatchback>(id, brand, model, plate, rate, mileage, rented));
            }
        }
    }
    vFile.close();

    if (vehicles.empty()) {
        seedInitialFleetIfEmpty();
        return;
    }

    // 2. Load Customers
    std::ifstream cFile(CUSTOMERS_FILE);
    customers.clear();
    if (cFile.is_open()) {
        while (std::getline(cFile, line)) {
            if (line.empty()) continue;
            customers.push_back(Customer::deserialize(line));
        }
        cFile.close();
    }

    // 3. Load Rental Records
    std::ifstream rFile(RENTALS_FILE);
    records.clear();
    if (rFile.is_open()) {
        while (std::getline(rFile, line)) {
            if (line.empty()) continue;
            records.push_back(RentalRecord::deserialize(line));
        }
        rFile.close();
    }
}

void RentalManager::saveData() {
    // 1. Save Vehicles
    std::ofstream vFile(VEHICLES_FILE);
    if (vFile.is_open()) {
        for (const auto& v : vehicles) {
            vFile << v->serialize() << "\n";
        }
        vFile.close();
    }

    // 2. Save Customers
    std::ofstream cFile(CUSTOMERS_FILE);
    if (cFile.is_open()) {
        for (const auto& c : customers) {
            cFile << c.serialize() << "\n";
        }
        cFile.close();
    }

    // 3. Save Rentals
    std::ofstream rFile(RENTALS_FILE);
    if (rFile.is_open()) {
        for (const auto& r : records) {
            rFile << r.serialize() << "\n";
        }
        rFile.close();
    }
}

bool RentalManager::registerCustomer(const std::string& name, const std::string& phone, const std::string& license) {
    std::string newId = "C" + std::to_string(101 + customers.size());
    customers.push_back(Customer(newId, name, phone, license, "NONE"));
    saveData();

    std::cout << "\n [SUCCESS] Customer registered successfully!" << std::endl;
    std::cout << " Assigned Customer ID: " << newId << std::endl;
    return true;
}

Customer* RentalManager::findCustomerById(const std::string& id) {
    for (auto& c : customers) {
        if (c.getId() == id) return &c;
    }
    return nullptr;
}

void RentalManager::displayAllCustomers() const {
    std::cout << "\n==================================================================================" << std::endl;
    std::cout << "                             REGISTERED CUSTOMERS                                  " << std::endl;
    std::cout << "==================================================================================" << std::endl;
    std::cout << " | " << std::left << std::setw(8) << "Cust ID"
              << " | " << std::setw(20) << "Full Name"
              << " | " << std::setw(15) << "Contact Phone"
              << " | " << std::setw(16) << "Driving License"
              << " | " << std::setw(14) << "Active Rental"
              << " |" << std::endl;
    std::cout << "----------------------------------------------------------------------------------" << std::endl;

    for (const auto& c : customers) {
        c.display();
    }
    std::cout << "==================================================================================" << std::endl;
}

void RentalManager::displayFleet(bool availableOnly) const {
    std::cout << "\n========================================================================================================" << std::endl;
    std::cout << "                                        CURRENT FLEET STATUS                                            " << std::endl;
    std::cout << "========================================================================================================" << std::endl;
    std::cout << " | " << std::left << std::setw(6) << "ID"
              << " | " << std::setw(10) << "Category"
              << " | " << std::setw(12) << "Vehicle"
              << " | " << std::setw(14) << "License Plate"
              << " | " << std::setw(11) << "Base Rate"
              << " | " << std::setw(12) << "Status"
              << " | " << std::setw(22) << "Specifications"
              << " |" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;

    int displayedCount = 0;
    for (const auto& v : vehicles) {
        if (availableOnly && v->getIsRented()) continue;
        v->displayDetails();
        displayedCount++;
    }

    if (displayedCount == 0) {
        std::cout << " | No vehicles match the selected criteria.                                                            |" << std::endl;
    }
    std::cout << "========================================================================================================" << std::endl;
}

Vehicle* RentalManager::findVehicleById(const std::string& id) {
    for (auto& v : vehicles) {
        if (v->getId() == id) return v.get();
    }
    return nullptr;
}

bool RentalManager::addVehicle(std::unique_ptr<Vehicle> vehicle) {
    vehicles.push_back(std::move(vehicle));
    saveData();
    std::cout << "\n [SUCCESS] New vehicle added to fleet successfully!" << std::endl;
    return true;
}

void RentalManager::searchVehicles(const std::string& keyword) const {
    std::string lowerKeyword = keyword;
    std::transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    std::cout << "\n [SEARCH RESULTS FOR: \"" << keyword << "\"]" << std::endl;
    std::cout << "========================================================================================================" << std::endl;
    int count = 0;
    for (const auto& v : vehicles) {
        std::string brand = v->getBrand();
        std::string model = v->getModel();
        std::string cat = v->getCategory();
        std::string id = v->getId();

        std::transform(brand.begin(), brand.end(), brand.begin(), ::tolower);
        std::transform(model.begin(), model.end(), model.begin(), ::tolower);
        std::transform(cat.begin(), cat.end(), cat.begin(), ::tolower);
        std::transform(id.begin(), id.end(), id.begin(), ::tolower);

        if (brand.find(lowerKeyword) != std::string::npos ||
            model.find(lowerKeyword) != std::string::npos ||
            cat.find(lowerKeyword) != std::string::npos ||
            id.find(lowerKeyword) != std::string::npos) {
            v->displayDetails();
            count++;
        }
    }
    if (count == 0) {
        std::cout << " | No matching vehicles found in the fleet.                                                            |" << std::endl;
    }
    std::cout << "========================================================================================================" << std::endl;
}

bool RentalManager::rentVehicle(const std::string& customerId, const std::string& vehicleId, int days) {
    Customer* cust = findCustomerById(customerId);
    if (!cust) {
        std::cout << "\n [ERROR] Customer ID not found. Please register customer first." << std::endl;
        return false;
    }

    if (cust->getActiveRentalVehicleId() != "NONE") {
        std::cout << "\n [ERROR] Customer already has an active rental: " << cust->getActiveRentalVehicleId() << std::endl;
        std::cout << " Please return the current vehicle before booking another." << std::endl;
        return false;
    }

    Vehicle* veh = findVehicleById(vehicleId);
    if (!veh) {
        std::cout << "\n [ERROR] Vehicle ID not found." << std::endl;
        return false;
    }

    if (veh->getIsRented()) {
        std::cout << "\n [ERROR] Vehicle " << vehicleId << " is already rented to another customer." << std::endl;
        return false;
    }

    if (days <= 0) {
        std::cout << "\n [ERROR] Rental duration must be at least 1 day." << std::endl;
        return false;
    }

    // Dynamic Polymorphic Cost Calculation
    double totalEstimatedCost = veh->calculateRentalCost(days);
    double gstTax = totalEstimatedCost * 0.18; // 18% GST
    double grandTotal = totalEstimatedCost + gstTax;

    std::string recordId = "R" + std::to_string(1001 + records.size());
    std::string today = getCurrentDate();

    // Update statuses
    veh->setRented(true);
    cust->setActiveRentalVehicleId(vehicleId);

    RentalRecord newRecord(recordId, customerId, cust->getName(), 
                           vehicleId, veh->getBrand() + " " + veh->getModel(), 
                           days, grandTotal, "ACTIVE", today);
    records.push_back(newRecord);

    saveData();

    // Print Professional ASCII Invoice Receipt
    std::cout << "\n==============================================================" << std::endl;
    std::cout << "               CAR RENTAL SYSTEM - BOOKING INVOICE            " << std::endl;
    std::cout << "==============================================================" << std::endl;
    std::cout << " Invoice ID     : " << recordId << std::endl;
    std::cout << " Date           : " << today << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << " Customer ID    : " << cust->getId() << std::endl;
    std::cout << " Customer Name  : " << cust->getName() << std::endl;
    std::cout << " Phone          : " << cust->getPhone() << std::endl;
    std::cout << " Driving License: " << cust->getDrivingLicense() << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << " Vehicle ID     : " << veh->getId() << " (" << veh->getCategory() << ")" << std::endl;
    std::cout << " Model          : " << veh->getBrand() << " " << veh->getModel() << std::endl;
    std::cout << " License Plate  : " << veh->getLicensePlate() << std::endl;
    std::cout << " Rental Duration: " << days << " Day(s)" << std::endl;
    std::cout << " Base Rate/Day  : Rs. " << std::fixed << std::setprecision(2) << veh->getBaseRatePerDay() << std::endl;
    std::cout << " Subtotal       : Rs. " << totalEstimatedCost << std::endl;
    std::cout << " GST (18%)      : Rs. " << gstTax << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << " GRAND TOTAL    : Rs. " << grandTotal << std::endl;
    std::cout << " Status         : CONFIRMED & ACTIVE" << std::endl;
    std::cout << "==============================================================" << std::endl;

    return true;
}

bool RentalManager::returnVehicle(const std::string& vehicleId, double damageCharges, int lateDays) {
    Vehicle* veh = findVehicleById(vehicleId);
    if (!veh) {
        std::cout << "\n [ERROR] Vehicle ID not found." << std::endl;
        return false;
    }

    if (!veh->getIsRented()) {
        std::cout << "\n [ERROR] Vehicle " << vehicleId << " is not marked as currently rented." << std::endl;
        return false;
    }

    // Find active rental record
    RentalRecord* activeRecord = nullptr;
    for (auto& r : records) {
        if (r.getVehicleId() == vehicleId && r.getStatus() == "ACTIVE") {
            activeRecord = &r;
            break;
        }
    }

    Customer* cust = nullptr;
    if (activeRecord) {
        cust = findCustomerById(activeRecord->getCustomerId());
    }

    double lateFee = 0.0;
    if (lateDays > 0) {
        lateFee = lateDays * (veh->getBaseRatePerDay() * 1.5); // 1.5x penalty for late days
    }

    double finalAdditionalCharges = damageCharges + lateFee;
    double finalCost = activeRecord ? (activeRecord->getTotalCost() + finalAdditionalCharges) : finalAdditionalCharges;

    // Update statuses
    veh->setRented(false);
    if (cust) {
        cust->setActiveRentalVehicleId("NONE");
    }
    if (activeRecord) {
        activeRecord->setStatus("RETURNED");
        activeRecord->setTotalCost(finalCost);
    }

    saveData();

    // Print Return Settlement Receipt
    std::cout << "\n==============================================================" << std::endl;
    std::cout << "             VEHICLE RETURN SETTLEMENT SUMMARY                " << std::endl;
    std::cout << "==============================================================" << std::endl;
    std::cout << " Vehicle Returned : " << veh->getId() << " (" << veh->getBrand() << " " << veh->getModel() << ")" << std::endl;
    if (cust) {
        std::cout << " Customer Name    : " << cust->getName() << " (" << cust->getId() << ")" << std::endl;
    }
    std::cout << " Return Date      : " << getCurrentDate() << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << " Late Return Days : " << lateDays << " (Late Fee: Rs. " << lateFee << ")" << std::endl;
    std::cout << " Damage Charges   : Rs. " << damageCharges << std::endl;
    std::cout << " Additional Total : Rs. " << finalAdditionalCharges << std::endl;
    std::cout << " Final Bill Total : Rs. " << finalCost << std::endl;
    std::cout << " Vehicle Status   : AVAILABLE IN FLEET" << std::endl;
    std::cout << "==============================================================" << std::endl;

    return true;
}

void RentalManager::displayRentalHistory() const {
    std::cout << "\n================================================================================================================" << std::endl;
    std::cout << "                                         ALL RENTAL TRANSACTION LOGS                                            " << std::endl;
    std::cout << "================================================================================================================" << std::endl;
    std::cout << " | " << std::left << std::setw(8)  << "Log ID"
              << " | " << std::setw(8)  << "Cust ID"
              << " | " << std::setw(18) << "Customer Name"
              << " | " << std::setw(8)  << "Veh ID"
              << " | " << std::setw(16) << "Vehicle Model"
              << " | " << std::setw(6)  << "Days"
              << " | " << std::setw(13) << "Total Amount"
              << " | " << std::setw(10) << "Status"
              << " | " << std::setw(12) << "Date"
              << " |" << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;

    for (const auto& r : records) {
        r.display();
    }
    std::cout << "================================================================================================================" << std::endl;
}

void RentalManager::displayFleetAnalytics() const {
    int totalCars = vehicles.size();
    int rentedCars = 0;
    int availableCars = 0;
    double totalRevenue = 0.0;

    for (const auto& v : vehicles) {
        if (v->getIsRented()) rentedCars++;
        else availableCars++;
    }

    for (const auto& r : records) {
        totalRevenue += r.getTotalCost();
    }

    double utilizationRate = (totalCars > 0) ? (static_cast<double>(rentedCars) / totalCars) * 100.0 : 0.0;

    std::cout << "\n==============================================================" << std::endl;
    std::cout << "                FLEET ANALYTICS & REVENUE DASHBOARD           " << std::endl;
    std::cout << "==============================================================" << std::endl;
    std::cout << " Total Fleet Vehicles       : " << totalCars << std::endl;
    std::cout << " Available Vehicles         : " << availableCars << std::endl;
    std::cout << " Currently Rented Vehicles  : " << rentedCars << std::endl;
    std::cout << " Fleet Utilization Rate     : " << std::fixed << std::setprecision(1) << utilizationRate << " %" << std::endl;
    std::cout << " Total Bookings Completed   : " << records.size() << std::endl;
    std::cout << " Gross Rental Revenue Earned: Rs. " << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
    std::cout << " Registered Customers Count : " << customers.size() << std::endl;
    std::cout << " Storage Data Files Status  : PERSISTENT ON DISK (OK)" << std::endl;
    std::cout << "==============================================================" << std::endl;
}
