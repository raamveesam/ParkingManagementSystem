#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Global variables
int totalSlots;
int* parkingSlots;

// Head pointer for linked list
struct Vehicle
{
    string vehicleNumber;
    string ownerName;
    int slotNumber;
    time_t entryTime;

    Vehicle* next;
};

Vehicle* head = nullptr;


// ==================================================
// FIND THE AVAILABLE PARKING SLOT
// ==================================================

int findAvailableSlot()
{
    for (int i = 0; i < totalSlots; i++)
    {
        if (parkingSlots[i] == 0)
        {
            return i + 1;
        }
    }

    return -1;
}


// ==================================================
// REGISTER AND PARK VEHICLE HERE
// ==================================================

void registerVehicle()
{
    string number;
    string owner;

    cout << "\nEnter vehicle number: ";
    cin >> number;

    cout << "Enter owner name: ";
    cin >> owner;

    // Check for available slot
    int slot = findAvailableSlot();

    if (slot == -1)
    {
        cout << "\nParking is full!";
        cout << "\nVehicle cannot be parked.\n";
        return;
    }

    // Create new vehicle node
    Vehicle* newVehicle = new Vehicle;

    newVehicle->vehicleNumber = number;
    newVehicle->ownerName = owner;
    newVehicle->slotNumber = slot;

    // Store current entry time
    newVehicle->entryTime = time(nullptr);

    // Insert vehicle at beginning of linked list
    newVehicle->next = head;
    head = newVehicle;

    // Mark slot as occupied
    parkingSlots[slot - 1] = 1;

    cout << "\n====================================";
    cout << "\n     VEHICLE GOT  PARKED SUCCESSFULLY";
    cout << "\n====================================";

    cout << "\nVehicle Number : " << number;
    cout << "\nOwner Name     : " << owner;
    cout << "\nAssigned Slot  : " << slot << endl;
}


// ==================================================
// DISPLAYS THE PARKING SLOTS
// ==================================================

void displayParkingSlots()
{
    cout << "\n====================================";
    cout << "\n         PARKING SLOT STATUS";
    cout << "\n====================================\n";

    for (int i = 0; i < totalSlots; i++)
    {
        cout << "Slot " << i + 1 << " : ";

        if (parkingSlots[i] == 0)
        {
            cout << "Available";
        }
        else
        {
            cout << "Occupied";
        }

        cout << endl;
    }
}


// ==================================================
// DISPLAYS ALL THE  PARKED VEHICLES
// ==================================================

void displayVehicles()
{
    if (head == nullptr)
    {
        cout << "\nNo vehicles are currently parked.\n";
        return;
    }

    Vehicle* current = head;

    cout << "\n====================================";
    cout << "\n          PARKED VEHICLES INFO GET STORED HERE";
    cout << "\n====================================";

    while (current != nullptr)
    {
        cout << "\n\nVehicle Number : " << current->vehicleNumber;
        cout << "\nOwner Name     : " << current->ownerName;
        cout << "\nParking Slot   : " << current->slotNumber;

        cout << "\n------------------------------------";

        current = current->next;
    }

    cout << endl;
}


// ==================================================
// SEARCH THE VEHICLE BY ITS NUMBER
// ==================================================

void searchVehicle()
{
    string number;

    cout << "\nEnter vehicle number to search: ";
    cin >> number;

    Vehicle* current = head;

    while (current != nullptr)
    {
        if (current->vehicleNumber == number)
        {
            cout << "\n====================================";
            cout << "\n          VEHICLE HAD BEEN FOUND";
            cout << "\n====================================";

            cout << "\nVehicle Number : " << current->vehicleNumber;
            cout << "\nOwner Name     : " << current->ownerName;
            cout << "\nParking Slot   : " << current->slotNumber;

            cout << endl;

            return;
        }

        current = current->next;
    }

    cout << "\nVehicle was not parked\n";
}



// MAIN FUNCTION STARTS HERE
// ==================================================

int main()
{
    int choice;

    // ----------------------------------------------
    // GET THE  NUMBER OF PARKING SLOTS ACCORDING TO THE SPACE 
    // ----------------------------------------------

    cout << "====================================";
    cout << "\n     SMART PARKING MANAGEMENT";
    cout << "\n====================================";

    cout << "\n\nEnter total number of parking slots: ";
    cin >> totalSlots;

    // Validate number of slots
    if (totalSlots <= 0)
    {
        cout << "\nInvalid number of slots!";
        cout << "\nProgram terminated.\n";

        return 0;
    }

    // Dynamically create parking slot array
    parkingSlots = new int[totalSlots];

    // Initially all slots are available
    for (int i = 0; i < totalSlots; i++)
    {
        parkingSlots[i] = 0;
    }

    cout << "\nParking system created successfully!";
    cout << "\nTotal Slots: " << totalSlots << endl;


    // ----------------------------------------------
    // --__________MAIN MENU______________--
    // ----------------------------------------------

    do
    {
        cout << "\n\n====================================";
        cout << "\n     SMART PARKING MANAGEMENT";
        cout << "\n====================================";

        cout << "\n1. Register Vehicle";
        cout << "\n2. Display Parking Slots";
        cout << "\n3. Display Parked Vehicles";
        cout << "\n4. Search Vehicle";
        cout << "\n0. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;


        switch (choice)
        {
            case 1:
                registerVehicle();
                break;

            case 2:
                displayParkingSlots();
                break;

            case 3:
                displayVehicles();
                break;

            case 4:
                searchVehicle();
                break;

            case 0:
                cout << "\nThank you for using Smart Parking Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 0);


    // ----------------------------------------------
    // FREE THE  DYNAMIC MEMORY
    // ----------------------------------------------

    delete[] parkingSlots;

    return 0;
}
