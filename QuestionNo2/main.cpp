#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Define structure to hold package info
struct Package {
    string id;
    int priority;
    float weight;
};

// Comparator for sorting
bool comparePackages(const Package &a, const Package &b) {
    if (a.priority == b.priority)
        return a.weight < b.weight;
    return a.priority < b.priority;
}

int main() {
    vector<Package> packages;

    // Sample input (can also take from user)
    packages.push_back({"PKG1", 3, 5.2});
    packages.push_back({"PKG2", 1, 7.5});
    packages.push_back({"PKG3", 2, 4.0});
    packages.push_back({"PKG4", 1, 2.3});
    packages.push_back({"PKG5", 3, 5.2});

    // Sort using custom comparator
    sort(packages.begin(), packages.end(), comparePackages);

    // Display result
    cout << "=== Sorted Conveyor Belt ===\n";
    cout << left << setw(10) << "ID" 
         << setw(10) << "Priority" 
         << setw(10) << "Weight (kg)" << "\n";

    for (const auto &pkg : packages) {
        cout << left << setw(10) << pkg.id 
             << setw(10) << pkg.priority 
             << setw(10) << fixed << setprecision(1) << pkg.weight << "\n";
    }

    return 0;
}

