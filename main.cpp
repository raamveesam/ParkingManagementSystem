#include <iostream>
#include <string>
#include <ctime>
#include <limits>

using namespace std;

// Structure to represent a parked vehicle
struct Vehicle
{
    string vehicleNumber;
    string ownerName;
    int slotNumber;
    time_t entryTime;

    Vehicle* next;
};

// Global pointers and state
int totalSlots = 0;
int* parkingSlots = nullptr;
Vehicle* head = nullptr;


// ==================================================
// HELPER: SAFELY READ STRING WITH SPACES
// ==================================================
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


// ==================================================
// FIND THE FIRST AVAILABLE PARKING SLOT
// ==================================================
int findAvailableSlot()
{
    for (int i = 0; i < totalSlots; i++)
    {
        if (parkingSlots[i] == 0)
        {
            return i + 1; // 1-based index
        }
    }
    return -1;
}


// ==================================================
// CHECK IF VEHICLE IS ALREADY PARKED
// ==================================================
bool isVehicleParked(const string& number)
{
    Vehicle* current = head;
    while (current != nullptr)
    {
        if (current->vehicleNumber == number)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}


// ==================================================
// REGISTER AND PARK VEHICLE
// ==================================================
void registerVehicle()
{
    string number;
    string owner;

    cout << "\nEnter vehicle number: ";
    cin >> number;
    clearInputBuffer();

    // Check for duplicate vehicle
    if (isVehicleParked(number))
    {
        cout << "\n[Error] Vehicle " << number << " is already registered and parked!\n";
        return;
    }

    // Check for available slot
    int slot = findAvailableSlot();
    if (slot == -1)
    {
        cout << "\n[Alert] Parking is full! Vehicle cannot be parked.\n";
        return;
    }

    cout << "Enter owner name: ";
    getline(cin, owner);

    // Create new vehicle node
    Vehicle* newVehicle = new Vehicle;
    newVehicle->vehicleNumber = number;
    newVehicle->ownerName = owner;
    newVehicle->slotNumber = slot;
    newVehicle->entryTime = time(nullptr);

    // Insert at beginning of linked list
    newVehicle->next = head;
    head = newVehicle;

    // Mark slot as occupied
    parkingSlots[slot - 1] = 1;

    cout << "\n====================================";
    cout << "\n   VEHICLE PARKED SUCCESSFULLY";
    cout << "\n====================================";
    cout << "\nVehicle Number : " << number;
    cout << "\nOwner Name     : " << owner;
    cout << "\nAssigned Slot  : " << slot;
    cout << "\nEntry Time     : " << ctime(&newVehicle->entryTime);
}


// ==================================================
// UNPARK / CHECKOUT VEHICLE
// ==================================================
void unparkVehicle()
{
    if (head == nullptr)
    {
        cout << "\nNo vehicles are currently parked.\n";
        return;
    }

    string number;
    cout << "\nEnter vehicle number to unpark: ";
    cin >> number;
    clearInputBuffer();

    Vehicle* current = head;
    Vehicle* prev = nullptr;

    while (current != nullptr && current->vehicleNumber != number)
    {
        prev = current;
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << "\n[Error] Vehicle with number " << number << " was not found.\n";
        return;
    }

    // Free the parking slot
    parkingSlots[current->slotNumber - 1] = 0;

    // Unlink the node from the list
    if (prev == nullptr)
    {
        head = current->next;
    }
    else
    {
        prev->next = current->next;
    }

    cout << "\n====================================";
    cout << "\n   VEHICLE UNPARKED SUCCESSFULLY";
    cout << "\n====================================";
    cout << "\nVehicle Number : " << current->vehicleNumber;
    cout << "\nOwner Name     : " << current->ownerName;
    cout << "\nFreed Slot     : " << current->slotNumber << endl;

    // Free heap memory for this vehicle
    delete current;
}


// ==================================================
// DISPLAYS THE PARKING SLOTS STATUS
// ==================================================
void displayParkingSlots()
{
    cout << "\n====================================";
    cout << "\n         PARKING SLOT STATUS";
    cout << "\n====================================\n";

    for (int i = 0; i < totalSlots; i++)
    {
        cout << "Slot " << (i + 1) << " : "
             << (parkingSlots[i] == 0 ? "Available" : "Occupied") << endl;
    }
}


// ==================================================
// DISPLAYS ALL THE PARKED VEHICLES
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
    cout << "\n          PARKED VEHICLES";
    cout << "\n====================================";

    while (current != nullptr)
    {
        cout << "\nVehicle Number : " << current->vehicleNumber;
        cout << "\nOwner Name     : " << current->ownerName;
        cout << "\nParking Slot   : " << current->slotNumber;
        cout << "\nEntry Time     : " << ctime(&current->entryTime);
        cout << "------------------------------------";

        current = current->next;
    }
    cout << endl;
}


// ==================================================
// SEARCH THE VEHICLE BY ITS NUMBER
// ==================================================
void searchVehicle()
{
    if (head == nullptr)
    {
        cout << "\nNo vehicles are currently parked.\n";
        return;
    }

    string number;
    cout << "\nEnter vehicle number to search: ";
    cin >> number;
    clearInputBuffer();

    Vehicle* current = head;
    while (current != nullptr)
    {
        if (current->vehicleNumber == number)
        {
            cout << "\n====================================";
            cout << "\n          VEHICLE FOUND";
            cout << "\n====================================";
            cout << "\nVehicle Number : " << current->vehicleNumber;
            cout << "\nOwner Name     : " << current->ownerName;
            cout << "\nParking Slot   : " << current->slotNumber;
            cout << "\nEntry Time     : " << ctime(&current->entryTime);
            return;
        }
        current = current->next;
    }

    cout << "\nVehicle with number " << number << " was not found.\n";
}


// ==================================================
// FREE ALL ALLOCATED MEMORY (PREVENTS MEMORY LEAKS)
// ==================================================
void cleanupMemory()
{
    // Free all linked list vehicle nodes
    Vehicle* current = head;
    while (current != nullptr)
    {
        Vehicle* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;

    // Free slot array
    delete[] parkingSlots;
    parkingSlots = nullptr;
}


// ==================================================
// MAIN FUNCTION
// ==================================================
int main()
{
    int choice;

    cout << "====================================";
    cout << "\n     SMART PARKING MANAGEMENT";
    cout << "\n====================================";

    cout << "\n\nEnter total number of parking slots: ";
    while (!(cin >> totalSlots) || totalSlots <= 0)
    {
        cout << "Invalid input! Please enter a positive integer: ";
        clearInputBuffer();
    }
    clearInputBuffer();

    // Dynamically create parking slot array initialized to 0
    parkingSlots = new int[totalSlots]();

    cout << "\nParking system initialized successfully!";
    cout << "\nTotal Slots: " << totalSlots << endl;

    do
    {
        cout << "\n====================================";
        cout << "\n     SMART PARKING MANAGEMENT";
        cout << "\n====================================";
        cout << "\n1. Register Vehicle";
        cout << "\n2. Unpark / Checkout Vehicle";
        cout << "\n3. Display Parking Slots";
        cout << "\n4. Display Parked Vehicles";
        cout << "\n5. Search Vehicle";
        cout << "\n0. Exit";
        cout << "\n\nEnter your choice: ";

        if (!(cin >> choice))
        {
            cout << "\nInvalid choice! Please enter a number.\n";
            clearInputBuffer();
            continue;
        }

        switch (choice)
        {
            case 1:
                registerVehicle();
                break;
            case 2:
                unparkVehicle();
                break;
            case 3:
                displayParkingSlots();
                break;
            case 4:
                displayVehicles();
                break;
            case 5:
                searchVehicle();
                break;
            case 0:
                cout << "\nThank you for using Smart Parking Management System!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 0);

    // Free all dynamic memory
    cleanupMemory();

    return 0;
}
