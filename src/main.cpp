#include <iostream>
#include <string>
#include <limits>
#include "RentalManager.h"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printBanner() {
    std::cout << "\n=================================================================" << std::endl;
    std::cout << "        ____    _    ____    ____  _____ _   _ _____ _    _      " << std::endl;
    std::cout << "       / ___|  / \\  |  _ \\  |  _ \\| ____| \\ | |_   _/ \\  | |     " << std::endl;
    std::cout << "      | |     / _ \\ | |_) | | |_) |  _| |  \\| | | |/ _ \\ | |     " << std::endl;
    std::cout << "      | |___ / ___ \\|  _ <  |  _ <| |___| |\\  | | / ___ \\| |___  " << std::endl;
    std::cout << "       \\____/_/   \\_\\_| \\_\\ |_| \\_\\_____|_| \\_| |_/_/   \\_\\_____| " << std::endl;
    std::cout << "                   MANAGEMENT & BOOKING SYSTEM                    " << std::endl;
    std::cout << "=================================================================" << std::endl;
}

void printMenu() {
    std::cout << "\n [MAIN NAVIGATION MENU]" << std::endl;
    std::cout << " ------------------------------------------------------------" << std::endl;
    std::cout << "  1. Browse All Fleet Vehicles" << std::endl;
    std::cout << "  2. Browse Available Vehicles for Rent" << std::endl;
    std::cout << "  3. Search Vehicle (Model / Brand / Type)" << std::endl;
    std::cout << "  4. Book / Rent a Vehicle (Generate Invoice)" << std::endl;
    std::cout << "  5. Return a Vehicle (Generate Return Settlement)" << std::endl;
    std::cout << "  6. Register a New Customer" << std::endl;
    std::cout << "  7. View Registered Customers Directory" << std::endl;
    std::cout << "  8. View All Rental Transaction Logs" << std::endl;
    std::cout << "  9. Add New Vehicle to Fleet (Admin)" << std::endl;
    std::cout << " 10. Fleet Analytics & Revenue Dashboard" << std::endl;
    std::cout << "  0. Exit Application" << std::endl;
    std::cout << " ------------------------------------------------------------" << std::endl;
    std::cout << " Enter choice (0 - 10): ";
}

int main() {
    RentalManager manager;
    printBanner();

    int choice = -1;
    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cout << "\n [INVALID] Please enter a valid numerical option." << std::endl;
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        if (choice == 0) {
            std::cout << "\n Thank you for using Car Rental Management System. Have a safe journey!" << std::endl;
            break;
        }

        switch (choice) {
            case 1: {
                manager.displayFleet(false);
                break;
            }
            case 2: {
                manager.displayFleet(true);
                break;
            }
            case 3: {
                std::cout << "\n Enter vehicle search keyword (e.g. Fortuner, Sedan, Honda): ";
                std::string keyword;
                std::getline(std::cin, keyword);
                if (!keyword.empty()) {
                    manager.searchVehicles(keyword);
                } else {
                    std::cout << " Search keyword cannot be empty." << std::endl;
                }
                break;
            }
            case 4: {
                manager.displayFleet(true);
                std::cout << "\n Enter Customer ID (e.g. C101): ";
                std::string custId;
                std::getline(std::cin, custId);

                std::cout << " Enter Vehicle ID to Rent (e.g. V101): ";
                std::string vehId;
                std::getline(std::cin, vehId);

                std::cout << " Enter Rental Duration (in days): ";
                int days;
                if (!(std::cin >> days) || days <= 0) {
                    std::cout << " [ERROR] Invalid days entered." << std::endl;
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                manager.rentVehicle(custId, vehId, days);
                break;
            }
            case 5: {
                manager.displayFleet(false);
                std::cout << "\n Enter Vehicle ID being returned: ";
                std::string vehId;
                std::getline(std::cin, vehId);

                std::cout << " Any damage charges to bill? (Enter 0 if none): Rs. ";
                double damages = 0.0;
                if (!(std::cin >> damages) || damages < 0) {
                    damages = 0.0;
                }
                clearInputBuffer();

                std::cout << " Number of late days overdue? (Enter 0 if on time): ";
                int lateDays = 0;
                if (!(std::cin >> lateDays) || lateDays < 0) {
                    lateDays = 0;
                }
                clearInputBuffer();

                manager.returnVehicle(vehId, damages, lateDays);
                break;
            }
            case 6: {
                std::cout << "\n [NEW CUSTOMER REGISTRATION]" << std::endl;
                std::cout << " Enter Full Name: ";
                std::string name;
                std::getline(std::cin, name);

                std::cout << " Enter Contact Phone: ";
                std::string phone;
                std::getline(std::cin, phone);

                std::cout << " Enter Driving License Number: ";
                std::string license;
                std::getline(std::cin, license);

                if (name.empty() || phone.empty() || license.empty()) {
                    std::cout << " [ERROR] All fields are mandatory." << std::endl;
                } else {
                    manager.registerCustomer(name, phone, license);
                }
                break;
            }
            case 7: {
                manager.displayAllCustomers();
                break;
            }
            case 8: {
                manager.displayRentalHistory();
                break;
            }
            case 9: {
                std::cout << "\n [ADD NEW VEHICLE TO FLEET]" << std::endl;
                std::cout << " Select Category (1: Sedan, 2: SUV, 3: Hatchback): ";
                int catChoice;
                if (!(std::cin >> catChoice) || catChoice < 1 || catChoice > 3) {
                    std::cout << " [ERROR] Invalid category selection." << std::endl;
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                std::cout << " Enter Vehicle ID (e.g. V107): ";
                std::string id;
                std::getline(std::cin, id);

                std::cout << " Enter Brand (e.g. Tata, Skoda): ";
                std::string brand;
                std::getline(std::cin, brand);

                std::cout << " Enter Model (e.g. Harrier, Slavia): ";
                std::string model;
                std::getline(std::cin, model);

                std::cout << " Enter License Plate: ";
                std::string plate;
                std::getline(std::cin, plate);

                std::cout << " Enter Base Rental Rate per Day (Rs.): ";
                double rate;
                if (!(std::cin >> rate) || rate <= 0) {
                    std::cout << " [ERROR] Invalid rental rate." << std::endl;
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                if (catChoice == 1) {
                    std::cout << " Enter Boot Space Capacity in Liters (e.g. 520): ";
                    int boot;
                    std::cin >> boot;
                    clearInputBuffer();
                    manager.addVehicle(std::make_unique<Sedan>(id, brand, model, plate, rate, boot, true, false));
                } else if (catChoice == 2) {
                    std::cout << " Is 4x4 All-Wheel Drive equipped? (1 for Yes, 0 for No): ";
                    int is4x4;
                    std::cin >> is4x4;
                    std::cout << " Enter Seating Capacity (5 or 7): ";
                    int seats;
                    std::cin >> seats;
                    clearInputBuffer();
                    manager.addVehicle(std::make_unique<SUV>(id, brand, model, plate, rate, (is4x4 == 1), seats, false));
                } else if (catChoice == 3) {
                    std::cout << " Enter Fuel Mileage in km/l (e.g. 21.5): ";
                    double mileage;
                    std::cin >> mileage;
                    clearInputBuffer();
                    manager.addVehicle(std::make_unique<Hatchback>(id, brand, model, plate, rate, mileage, false));
                }
                break;
            }
            case 10: {
                manager.displayFleetAnalytics();
                break;
            }
            default:
                std::cout << "\n [INVALID] Please select an option from 0 to 10." << std::endl;
                break;
        }
    }

    return 0;
}
