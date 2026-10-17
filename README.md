# C++ User Management System

A C++ console-based application for managing user accounts, client data, and system operations efficiently. Designed to demonstrate core C++ programming concepts, OOP principles, file handling, and structured data management.

## 🚀 Features
- **User & Admin Management:** Add, update, delete, and manage system administrators/users who manage accounts.
- **Authentication System:** Dedicated login page for authenticating users before giving access to the system.
- **Role & Permission Control:** Granular access permissions allowing specific features to be enabled or disabled per user.
- **Client Management:** Add, update, delete, and search client records.
- **Data Persistence:** Save and load account/user data using file I/O operations (`Clients.txt`, `Users.txt`).
- **Transactions System:** Perform deposit, withdrawal, and balance inquiries.
- **Interactive CLI:** Simple and intuitive command-line user interface.

---

## 🔑 Default Credentials

For initial testing and first-time login, use the following administrator account:

| Field | Value |
| :--- | :--- |
| **Username** | `Admin` |
| **Password** | `1234` |

> 💡 **Note:** It is recommended to create a new admin account with full permissions after your first login.

---

## 🛠️ Built With
- **Language:** C++
- **IDE / Environment:** Visual Studio / GCC / MSVC
- **Storage:** Text File Data Storage (`Clients.txt`, `Users.txt`)

## 📋 Prerequisites
To compile and run this project, you need:
- A C++ compiler supporting C++11 or higher (GCC, Clang, or MSVC).
- Visual Studio / VS Code or any preferred IDE.

## ⚙️ How to Build and Run

### Option 1: Using Visual Studio
1. Clone the repository:
   ```bash
   git clone https://github.com/a00ae/CPP-User-Management-System.git
   ```
2. Open `CPP-User-Management-System.sln` in Visual Studio.
3. Press `Ctrl + F5` to build and run the application.

### Option 2: Using Command Line (G++)
1. Clone the repository and navigate to the directory:
   ```bash
   git clone https://github.com/a00ae/CPP-User-Management-System.git
   cd CPP-User-Management-System
   ```
2. Compile the source file:
   ```bash
   g++ -std=c++11 CPP-User-Management-System.cpp -o UserManagement
   ```
3. Run the executable:
   - **Windows:** `.\UserManagement.exe`
   - **Linux / macOS:** `./UserManagement`

---

### Course & Certification Context
This project was built as a practical application to solidify C++ concepts, covering data structures, file streams, role-based security, and system architecture.
