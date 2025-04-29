#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>

using namespace std;

struct FailedOrder {
    string productId;
    int quantity;
    string reason;
};

// Load inventory from CSV
bool loadInventory(const string& filename, map<string, int>& inventory) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No existing inventory file found. Starting with empty inventory.\n";
        return false;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string productId;
        string quantityStr;
        
        if (getline(ss, productId, ',') && getline(ss, quantityStr)) {
            try {
                int quantity = stoi(quantityStr);
                inventory[productId] = quantity;
            } catch (const exception& e) {
                cout << "Warning: Invalid quantity for product " << productId << "\n";
            }
        }
    }
    
    file.close();
    return true;
}

// Save inventory to CSV
bool saveInventory(const string& filename, const map<string, int>& inventory) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << " for writing.\n";
        return false;
    }
    
    for (const auto& item : inventory) {
        file << item.first << "," << item.second << "\n";
    }
    file.close();
    return true;
}

// Save failed orders to CSV
bool saveFailedOrders(const string& filename, const vector<FailedOrder>& failedOrders) {
    ofstream file(filename, ios::out | ios::trunc);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << " for writing.\n";
        return false;
    }
    
    file << "ProductID,Quantity,Reason\n";
    for (const auto& order : failedOrders) {
        // Ensure reason doesn't contain commas that would break CSV format
        string sanitizedReason = order.reason;
        replace(sanitizedReason.begin(), sanitizedReason.end(), ',', ';');
        
        file << order.productId << "," << order.quantity << "," << sanitizedReason << "\n";
        file.flush(); // Ensure data is written immediately
    }
    file.close();
    
    // Verify file was written correctly
    ifstream checkFile(filename);
    if (!checkFile.is_open() || checkFile.peek() == ifstream::traits_type::eof()) {
        cout << "Warning: Failed orders file may be empty or not written correctly.\n";
        return false;
    }
    checkFile.close();
    
    return true;
}

// Helper function to safely get integer input
int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            // Clear the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (value >= 0) {
                return value;
            }
            cout << "Invalid input. Please enter a non-negative number.\n";
        } else {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Helper function to safely get string input
string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    // Remove any commas that could break CSV format
    input.erase(remove(input.begin(), input.end(), ','), input.end());
    return input;
}

// Helper function to log failed order and display message
void recordFailedOrder(vector<FailedOrder>& failedOrders, const string& productId, int quantity, const string& reason) {
    failedOrders.push_back({productId, quantity, reason});
    cout << "❌ " << reason << "\n";
    cout << "This order has been recorded in the failed orders log.\n";
}

int main() {
    map<string, int> inventory;
    vector<FailedOrder> failedOrders;
    string inventoryFile = "inventory.csv";
    string failedOrdersFile = "failed_orders.csv";

    cout << "=== Inventory Management System ===\n";

    // Attempt to load existing inventory
    if (loadInventory(inventoryFile, inventory)) {
        cout << "Existing inventory loaded from " << inventoryFile << ".\n";
        cout << "Current inventory contains " << inventory.size() << " products.\n";
    }

    // Ask if user wants to add new items
    char addItems;
    cout << "Do you want to add new items to inventory? (y/n): ";
    cin >> addItems;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after character input
    
    if (tolower(addItems) == 'y') {
        int numItems = getIntInput("Enter number of products to add to inventory: ");

        for (int i = 0; i < numItems; ++i) {
            cout << "\nProduct " << (i + 1) << ":\n";
            string productId = getStringInput("Enter Product ID: ");
            int stock = getIntInput("Enter Stock Count: ");
            
            // If product already exists, add to existing stock
            if (inventory.find(productId) != inventory.end()) {
                cout << "Product already exists. Adding to current stock.\n";
                inventory[productId] += stock;
            } else {
                inventory[productId] = stock;
            }
        }
    }

    // Display current inventory
    cout << "\nCurrent Inventory:\n";
    cout << "-------------------\n";
    cout << "Product ID | Quantity\n";
    for (const auto& item : inventory) {
        cout << item.first << " | " << item.second << "\n";
    }
    cout << "-------------------\n";

    char cont = 'y';
    while (tolower(cont) == 'y') {
        cout << "\nPlace an Order\n";
        string productId = getStringInput("Enter Product ID: ");
        int quantity = getIntInput("Enter Quantity: ");

        if (inventory.find(productId) == inventory.end()) {
            recordFailedOrder(failedOrders, productId, quantity, "Product not found");
        } else if (inventory[productId] >= quantity) {
            inventory[productId] -= quantity;
            cout << "✅ Order processed. Remaining stock: " << inventory[productId] << "\n";
        } else {
            string reason = "Insufficient stock (requested: " + to_string(quantity) + 
                           ", available: " + to_string(inventory[productId]) + ")";
            recordFailedOrder(failedOrders, productId, quantity, reason);
        }

        cout << "Place another order? (y/n): ";
        cin >> cont;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer after character input
    }

    // Save updated data
    if (saveInventory(inventoryFile, inventory)) {
        cout << "\n📦 Inventory saved to " << inventoryFile << ".\n";
    }
    
    // Save failed orders if any exist
    if (!failedOrders.empty()) {
        if (saveFailedOrders(failedOrdersFile, failedOrders)) {
            cout << "📝 " << failedOrders.size() << " failed orders saved to " << failedOrdersFile << ".\n";
        }
    } else {
        cout << "📝 No failed orders to save.\n";
    }

    return 0;
}
