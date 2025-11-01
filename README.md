# 🛒 Supermarket Billing System (C++)

A simple, console-based supermarket billing and inventory management system written in C++. This project allows an admin to add products to an inventory and a cashier to generate a bill for a customer. The inventory is automatically updated after each sale and saved persistently in a local text file.

## Features

* **Inventory Management:** Add new products (name, rate, quantity) to the inventory.
* **Bill Generation:** Create a customer bill by adding multiple items and quantities.
* **Automatic Inventory Update:** Product quantities are automatically decremented after a bill is finalized.
* **Persistent Storage:** All inventory data is saved to `bill.txt` in a simple CSV (Comma-Separated Value) format.
* **Input Validation:** Includes basic checks to prevent crashes from invalid (non-numeric) input.
* **Menu-Driven Interface:** Simple and easy-to-use console menu.

## 🛠️ Technologies Used

* **Language:** C++
* **Core Libraries:** `<iostream>`, `<fstream>`, `<sstream>`, `<string>`, `<map>`, `<vector>`, `<limits>`
* **Platform-Specific:** `<windows.h>` for `system("cls")` and `Sleep()`. This project is intended for a Windows environment.

## 📋 Prerequisites

To compile and run this project, you will need:
* A Windows operating system.
* A C++ compiler, such as g++ (MinGW) or the Visual Studio C++ toolset.

## 🚀 How to Compile and Run

1.  **Clone the repository:**
    ```sh
    git clone [https://github.com/your-username/your-repository-name.git](https://github.com/your-username/your-repository-name.git)
    cd your-repository-name
    ```

2.  **IMPORTANT: Update File Path**
    Before you compile, you **must** open the `.cpp` file and change the file path constant at the top.

    *Change this line:*
    ```cpp
    const string BILL_FILE = "D:\\ALZABIR(CPP)\\CPP_Project\\Billing_management_system\\bill.txt";
    ```
    *To a location on your computer, or simply use a local file:*
    ```cpp
    // This will save "bill.txt" in the same folder as your .exe
    const string BILL_FILE = "bill.txt"; 
    ```

3.  **Compile the code:**
    Open a terminal or command prompt in the project folder and run your compiler.

    *Example using g++:*
    ```sh
    g++ main.cpp -o billing.exe
    ```
    *(Replace `main.cpp` with the name of your C++ file)*

4.  **Run the application:**
    ```sh
    ./billing.exe
    ```
    *(Or just `billing.exe` in some Windows terminals)*
    
    The first time you add an item, the `bill.txt` file will be created automatically.

## 📖 How to Use

Once the application is running, you will see the main menu:

1.  **Add Item to Inventory:**
    * Use this option to add new products or stock to your store's inventory.
    * You will be prompted to enter the Item Name, Rate (Price), and Quantity.

2.  **Print Customer Bill:**
    * Use this option to generate a bill for a customer.
    * The system will load the inventory. You can add items one by one to the customer's cart.
    * The system will check if there is enough stock.
    * When you "Finish Bill," a final receipt is shown, and the inventory file (`bill.txt`) is updated with the new quantities.

3.  **Exit:**
    * Closes the application.
