# Smart Parking Management System

A C++ console-based Parking Management System that utilizes linked lists and dynamic arrays to manage parking slots and parked vehicles.

## Features

- **Dynamic Slot Allocation**: Allows configuring total parking slots at runtime.
- **Vehicle Registration**: Assigns the first available parking slot and registers vehicle details with entry timestamps.
- **Parking Slot Status**: Displays real-time availability of all parking slots.
- **Parked Vehicles List**: Displays records of all currently parked vehicles using a linked list.
- **Search Functionality**: Quickly search for any vehicle by its registration number.

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
  ```bash
  .\parking_system.exe
  ```
- **Linux / macOS**:
  ```bash
  ./parking_system
  ```
