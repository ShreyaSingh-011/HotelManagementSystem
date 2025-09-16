
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <cstdlib>
#include <vector>
#include <cctype>

using namespace std;

// -------------------- Room Struct --------------------

struct Room {
    int roomNumber;
    int price;
    bool booked;
    string typeOfRoom;
};

// -------------------- Global Variables --------------------
//to maintain room structure

vector<vector<Room>> hotel;

struct customer {
    string name;
    string phone;
    int numberrooms;
    int guests;
    string Date_check_in;
    string Date_check_out;
    string id;
    int nightstayed;
    int rateing;
    string recomendation;
};

customer person;
int totalroomcost = 0;
int totalfbcost = 0;

// -------------------- Functions --------------------

// Welcome screen
void Draw() {
    system("cls");
    system("color 0B");

    cout << "\t\t\t====================================\n";
    cout << "\t\t\t|                                  |\n";
    cout << "\t\t\t|   -----------------------------  |\n";
    cout << "\t\t\t|        Welcome To Our Hotel      |\n";
    cout << "\t\t\t|   -----------------------------  |\n";
    cout << "\t\t\t|                                  |\n";
    cout << "\t\t\t====================================\n";

    time_t currentDT = time(0);
    cout << "\n\t\t\tDate and Time : " << ctime(&currentDT);
    cout << "\n";
}

bool isValidNationalID(const string& id) {
    if (id.length() != 14) return false;
    for (char c : id) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void InitializeHotel(int floors, int roomsPerFloor) {
    int roomNumber = 100;

    for (int f = 0; f < floors; ++f) {
        vector<Room> floorRooms;
        for (int r = 0; r < roomsPerFloor; ++r) {
            Room room;
            room.roomNumber = roomNumber++;
            room.price = 300 + (r % 3) * 100;
            room.booked = false;
            room.typeOfRoom = (r % 2 == 0) ? "single" : "suite";
            floorRooms.push_back(room);
        }
        hotel.push_back(floorRooms);
    }
}

void DisplayAvailableRooms() {
    cout << "\nAvailable Rooms:\n";
    cout << "-------------------------------------------\n";
    cout << "Floor | Room No | Type   | Price | Booked\n";
    cout << "-------------------------------------------\n";

    bool anyAvailable = false;
    for (int f = 0; f < hotel.size(); ++f) {
        for (auto &room : hotel[f]) {
            if (!room.booked) {
                cout << setw(5) << f + 1 << " | "
                     << setw(7) << room.roomNumber << " | "
                     << setw(6) << room.typeOfRoom << " | $"
                     << setw(5) << room.price << " | "
                     << (room.booked ? "Yes" : "No") << endl;
                anyAvailable = true;
            }
        }
    }

    if (!anyAvailable) {
        cout << "Sorry, there are no available rooms now.\n";
    }
}

void BookRoom() {
    DisplayAvailableRooms();

    cout << "\nEnter Your Name: ";
    cin >> person.name;
    cout << "Enter Your Phone Number: ";
    cin >> person.phone;
    cout << "Enter Your National ID (14 digits): ";
    cin >> person.id;

    while (!isValidNationalID(person.id)) {
        cout << "Invalid ID. Try again: ";
        cin.clear();
        cin.ignore(100000, '\n');
        cin >> person.id;
    }

    cout << "Number of rooms to book: ";
    cin >> person.numberrooms;
    cout << "Number of guests: ";
    cin >> person.guests;
    cout << "Number of nights stayed: ";
    cin >> person.nightstayed;
    cout << "Check-in date (DD/MM/YYYY): ";
    cin >> person.Date_check_in;
    cout << "Check-out date (DD/MM/YYYY): ";
    cin >> person.Date_check_out;

    totalroomcost = 0;

    for (int i = 0; i < person.numberrooms; ++i) {
        int requestedRoomNumber;
        bool roomBooked = false;

        do {
            cout << "Enter Room Number to book (" << i+1 << "): ";
            cin >> requestedRoomNumber;

            bool found = false;

            for (auto &floor : hotel) {
                for (auto &room : floor) {
                    if (room.roomNumber == requestedRoomNumber) {
                        found = true;

                        if (!room.booked) {
                            room.booked = true;
                            cout << "Room " << requestedRoomNumber << " booked successfully.\n";
                            totalroomcost += room.price * person.nightstayed;
                            roomBooked = true;
                        } else {
                            cout << "Room is already booked. Choose another.\n";
                        }

                        break;
                    }
                }
                if (found) break;
            }

            if (!found) {
                cout << "Invalid room number. Try again.\n";
            }

        } while (!roomBooked);
    }
}

void cancelbooking() {
    int roomNumber;
    cout << "Enter Room Number to cancel booking: ";
    cin >> roomNumber;

    bool roomFound = false;

    for (auto &floor : hotel) {
        for (auto &room : floor) {
            if (room.roomNumber == roomNumber) {
                roomFound = true;
                if (room.booked) {
                    room.booked = false;
                    cout << "Booking for Room " << roomNumber << " has been canceled successfully.\n";
                } else {
                    cout << "Room " << roomNumber << " is not currently booked.\n";
                }
                break;
            }
        }
        if (roomFound) break;
    }

    if (!roomFound) {
        cout << "Room number does not exist.\n";
    }
}

void selection() {
    int choice;
    cout << "\n1 - Display Available Rooms\n";
    cout << "2 - Book Room\n";
    cout << "3 - Cancel Booking\n";
    cout << "0 - Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cout << "\n";

    switch (choice) {
        case 1:
            DisplayAvailableRooms();
            break;
        case 2:
            BookRoom();
            break;
        case 3:
            cancelbooking();
            break;
        case 0:
            cout << "Thank You!\n";
            break;
        default:
            cout << "Invalid choice.\n";
    }
}

void featuresMenu() {
    cout << "Features:\n";
    cout << "1) Rooms\n";
    cout << "2) Food and Beverage\n";
    cout << "3) Bill and Payment\n";
}

void Foodbeverage() {
    float foodnumber, price, quantity;
    char choice;
    int coffeestock = 20, teastock = 15, waterstock = 20, frenshtoaststock = 10;
    int omeletstock = 12, steakstock = 10, pizzastock = 10, cheesecakestock = 14, browniestock = 12;

    string food[13] = {
        "Beverage:\n", "1)Black Coffee  10$", "2)Tea  6$", "3)Water  3$\n",
        "Breakfast:\n", "5)French Toast  15$", "6)Omelet  12$\n",
        "Launch:\n", "8)Steak   30$", "9)Pizza  25$\n",
        "Desserts:\n", "11)Cheese Cake  12$", "12)Brownie  13$\n"
    };

    for (int i = 0; i < 13; ++i)
        cout << food[i] << "\n";

    do {
        cout << "Enter Food number: ";
        cin >> foodnumber;

        if (foodnumber <= 0 || (int)foodnumber != foodnumber) {
            cout << "Invalid number. Try again.\n";
            break;
        }

        cout << "Enter Quantity: ";
        cin >> quantity;

        if (quantity <= 0 || (int)quantity != quantity) {
            cout << "Invalid quantity. Try again.\n";
            continue;
        }

        price = 0;
        switch ((int)foodnumber) {
            case 1:
                if (quantity > coffeestock) { cout << "Not enough Coffee stock.\n"; continue; }
                price = 10; coffeestock -= quantity; break;
            case 2:
                if (quantity > teastock) { cout << "Not enough Tea stock.\n"; continue; }
                price = 6; teastock -= quantity; break;
            case 3:
                if (quantity > waterstock) { cout << "Not enough Water stock.\n"; continue; }
                price = 3; waterstock -= quantity; break;
            case 5:
                if (quantity > frenshtoaststock) { cout << "Not enough Toast stock.\n"; continue; }
                price = 15; frenshtoaststock -= quantity; break;
            case 6:
                if (quantity > omeletstock) { cout << "Not enough Omelet stock.\n"; continue; }
                price = 12; omeletstock -= quantity; break;
            case 8:
                if (quantity > steakstock) { cout << "Not enough Steak stock.\n"; continue; }
                price = 30; steakstock -= quantity; break;
            case 9:
                if (quantity > pizzastock) { cout << "Not enough Pizza stock.\n"; continue; }
                price = 25; pizzastock -= quantity; break;
            case 11:
                if (quantity > cheesecakestock) { cout << "Not enough Cheesecake stock.\n"; continue; }
                price = 12; cheesecakestock -= quantity; break;
            case 12:
                if (quantity > browniestock) { cout << "Not enough Brownie stock.\n"; continue; }
                price = 13; browniestock -= quantity; break;
            default:
                cout << "Invalid Food Number.\n"; continue;
        }

        totalfbcost += price * quantity;
        cout << "Order added.\n";

        cout << "Order another item? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');
}

void billpayment() {
    int totalamount = totalroomcost + totalfbcost;

    cout << "\n========================================\n";
    cout << "            HOTEL INVOICE\n";
    cout << "========================================\n";
    cout << "Customer Name: " << person.name << "\n";
    cout << "Nights Stayed: " << person.nightstayed << "\n";
    cout << "Total Room Cost: $" << totalroomcost << "\n";
    cout << "----------------------------------------\n";
    cout << "Total Food & Drinks Cost: $" << totalfbcost << "\n";
    cout << "----------------------------------------\n";
    cout << "Final Amount: $" << totalamount << "\n";
    cout << "========================================\n";
    cout << "Thank you for visiting!\n";
}

// -------------------- Main Program --------------------

int main() {
    Draw();
    featuresMenu();

    int floors = 3;
    int roomsPerFloor = 5;
    InitializeHotel(floors, roomsPerFloor);

    char answer;
    int featurenumber;

    do {
        cout << "\nChoose Feature Number: ";
        cin >> featurenumber;
        cout << "\n";

        switch (featurenumber) {
            case 1:
                selection();
                break;
            case 2:
                Foodbeverage();
                break;
            case 3:
                billpayment();
                break;
            default:
                cout << "Please Enter a Valid Feature Number!\n";
                break;
        }

        cout << "Do you want to select another feature? (y/n): ";
        cin >> answer;

    } while (answer == 'y' || answer == 'Y');

    cout << "Rate your visit (1 to 5): ";
    cin >> person.rateing;
    cin.ignore();

    if (person.rateing <= 3) {
        cout << "Please give us a recommendation to improve: ";
        getline(cin, person.recomendation);
    }

    cout << "Thanks for visiting!\n";
    return 0;
}

                             