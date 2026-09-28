# Smart Parking Management System

A robust C++ console-based Parking Management System that utilizes linked lists and dynamic arrays to manage parking slots and vehicles.

## Features

- **Dynamic Slot Configuration**: Configure total parking capacity at startup with robust input validation.
- **Vehicle Registration**: Automatically allocates the first available slot, validates for duplicates, and records owner details and check-in timestamps.
- **Unpark / Checkout**: Allows parked vehicles to leave, marks their assigned slot as available again, and frees memory.
- **Real-Time Slot Status**: View the occupancy status of every slot.
- **Parked Vehicles Directory**: Displays all parked vehicles with entry timestamps.
- **Vehicle Search**: Search for any parked vehicle by registration number.
- **Memory Safety**: Full cleanup of all dynamic arrays and linked list nodes to prevent memory leaks.

## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or higher (e.g., `g++`, `clang++`, or MSVC).

### Compilation and Execution

Compile the source code:

```bash
g++ -o parking_system main.cpp
```

Run the application:

- **Windows**:
  ```powershell
  .\parking_system.exe
  ```
- **Linux / macOS**:
  ```bash
  ./parking_system
  ```
