#include <iostream>
#include <fstream>      // For file I/O
#include <sstream>      // For string parsing
#include <windows.h>
#include <string>       // For using string
#include <map>          // For in-memory inventory
#include <vector>       // For storing the customer's bill
#include <limits>       // For input validation

using namespace std;

// --- File Paths (Constants) ---
// We define these here so they are easy to change and not hardcoded everywhere.
const string BILL_FILE = "D:\\CPP_Project\\Billing_management_system\\bill.txt";

/**
 * @class Product
 * @brief Represents a single product in the inventory.
 * (Renamed from Bill for clarity)
 */
class Product {
private:
    string Name;
    int Rate, Quantity;
public:
    // Constructor
    Product() : Name(""), Rate(0), Quantity(0) {}

    // Setters
    void setName(string name) { Name = name; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }

    // Getters
    string getName() const { return Name; }
    int getRate() const { return Rate; }
    int getQuant() const { return Quantity; }
};

/**
 * @brief Helper function to safely get an integer input from the user.
 * Prevents crashing if the user enters text.
 */
int getIntegerInput() {
    int input;
    while (!(cin >> input)) {
        cout << "\tInvalid input. Please enter a number: ";
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the bad input
    }
    return input;
}

/**
 * @brief Adds a new product or updates an existing one in the inventory file.
 */
void addItem() {
    bool close = false;
    while (!close) {
        system("cls");
        cout << "\t--- Add Item to Inventory ---" << endl;
        cout << "\t1.Add." << endl;
        cout << "\t2.Back to Main Menu." << endl;
        cout << "\t Enter Choice: ";
        int choice = getIntegerInput();

        if (choice == 1) {
            system("cls");
            Product p; // Create a new product
            string name;
            int rate, quant;

            cout << "\t Enter Item name: ";
            cin.ignore(); // IMPORTANT: Consumes the newline left by "cin >> choice"
            getline(cin, name); // Now we can read names with spaces
            p.setName(name);

            cout << "\t Enter Rate Of Item: ";
            rate = getIntegerInput();
            p.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            quant = getIntegerInput();
            p.setQuant(quant);

            // Open file in append mode
            ofstream out(BILL_FILE, ios::app);
            if (!out) {
                cout << "\tError: File Can't Open!" << endl;
            } else {
                // Write in CSV (Comma-Separated Value) format
                // "Ice Cream,10,50"
                out << p.getName() << "," << p.getRate() << "," << p.getQuant() << endl;
            }
            out.close();
            cout << "\tItem Added Successfuly" << endl;
            Sleep(2000);
        }
        else if (choice == 2) {
            system("cls");
            close = true;
            cout << "\tBack to Main Menu!" << endl;
            Sleep(2000);
        }
    }
}

/**
 * @brief Handles the customer billing process.
 * Reads inventory once, processes the bill, and writes inventory back once.
 */
void printBill() {
    system("cls");
    map<string, Product> inventory; // In-memory storage for inventory
    
    // 1. --- Load Inventory from File into Map ---
    ifstream in(BILL_FILE);
    if (!in) {
        cout << "\tError: Cannot open inventory file. Add items first." << endl;
        Sleep(3000);
        return;
    }

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        string name, segment;
        int rate, quant;

        // Parse the CSV line
        if (getline(ss, name, ',') &&             // Get name
            getline(ss, segment, ',') &&          // Get rate (as string)
            (stringstream(segment) >> rate) &&  // Convert rate to int
            getline(ss, segment, ',') &&          // Get quantity (as string)
            (stringstream(segment) >> quant))   // Convert quantity to int
        {
            Product p;
            p.setName(name);
            p.setRate(rate);
            p.setQuant(quant);
            inventory[name] = p; // Add to our map
        }
    }
    in.close();

    if (inventory.empty()) {
        cout << "\tInventory is empty. Please add items." << endl;
        Sleep(3000);
        return;
    }

    // 2. --- Start the Customer Billing Process ---
    double totalBill = 0;
    bool close = false;
    vector<string> billItems; // To store the lines of the receipt
    billItems.push_back("\t Item | Rate | Quantity | Amount");
    billItems.push_back("\t---------------------------------");


    while (!close) {
        system("cls");
        cout << "\t--- Current Bill Total: " << totalBill << " ---" << endl << endl;
        cout << "\t1.Add Item to Bill." << endl;
        cout << "\t2.Finish Bill." << endl;
        cout << "\t Enter Choice: ";
        int choice = getIntegerInput();

        if (choice == 1) {
            string item;
            int quant;
            
            cout << "\tEnter Item: ";
            cin.ignore();
            getline(cin, item);
            
            // Check if item exists in our map
            if (inventory.find(item) == inventory.end()) {
                cout << "\tSorry, item '" << item << "' not found!" << endl;
            } else {
                cout << "\tEnter Quantity: ";
                quant = getIntegerInput();

                // Get a reference to the product in the map
                Product& p = inventory[item]; 

                if (quant <= 0) {
                    cout << "\tInvalid quantity." << endl;
                } else if (quant > p.getQuant()) {
                    cout << "\tSorry, only " << p.getQuant() << " available." << endl;
                } else {
                    // Success!
                    int amount = p.getRate() * quant;
                    totalBill += amount;
                    
                    // Add to our printable receipt
                    stringstream billLine;
                    billLine << "\t " << p.getName() << " | " << p.getRate() << " | " << quant << " | " << amount;
                    billItems.push_back(billLine.str());

                    // Update the quantity IN THE MAP (in memory)
                    p.setQuant(p.getQuant() - quant);
                    cout << "\tItem added to bill." << endl;
                }
            }
        } else if (choice == 2) {
            close = true;
            cout << "\tFinalizing Bill..." << endl;
        }
        Sleep(2000);
    }

    // 3. --- Write the Updated Inventory (from map) Back to the File ---
    // This time, we open in "out" mode (not "app") to OVERWRITE the old file
    ofstream out(BILL_FILE); 
    if (!out) {
        cout << "\tCRITICAL ERROR: Could not save updated inventory!" << endl;
    } else {
        // Loop through the map and write each product back to the file
        for (auto const& pair : inventory) {
            const Product& p = pair.second;
            out << p.getName() << "," << p.getRate() << "," << p.getQuant() << endl;
        }
        out.close();
    }

    // 4. --- Print the Final Bill ---
    system("cls");
    cout << endl << "\t--- FINAL RECEIPT ---" << endl << endl;
    for (const string& s : billItems) {
        cout << s << endl;
    }
    cout << "\t---------------------------------" << endl;
    cout << "\t TOTAL BILL: " << totalBill << endl << endl;
    cout << "\tThanks For Shopping!" << endl;
    Sleep(5000); // Give user time to see the total

}

// --- Main Function ---
int main() {
    bool exit = false;
    while (!exit) {
        system("cls");
        int val;

        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t\t1.Add Item to Inventory." << endl;
        cout << "\t\t2.Print Customer Bill." << endl;
        cout << "\t\t3.Exit." << endl;
        cout << "\t\tEnter Choice: ";
        
        val = getIntegerInput();

        if (val == 1) {
            system("cls");
            addItem(); // Call updated function
        }
        else if (val == 2) {
            printBill();
        }
        else if (val == 3) {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(3000);
        }
    }
    return 0;
}