#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // To handle string streams
#include <iomanip> // For std::setw()
#include <cstdio> // For remove() and rename()

// Function to create and initialize the database file
void createDatabase() {
    std::ofstream outFile("database.txt");
    if (outFile.is_open()) {
        std::cout << "\nCreating new database file." << std::endl;
        outFile << "ID,Name,Email,City\n";
        outFile << "1,Alice,alice@example.com,New York\n";
        outFile << "2,Bob,bob@example.com,London\n";
        outFile << "3,Charlie,charlie@example.com,Paris\n";
        outFile.close();
        std::cout << "Database file created with initial data." << std::endl;
    } else {
        std::cerr << "Error: Unable to create database file." << std::endl;
    }
}

void readDatabase() {
    std::ifstream inFile("database.txt");
    std::string line;

    if (inFile.is_open()) {
        std::cout << "\n--- Database Records ---\n\n";

        // Read and format the header line
        std::getline(inFile, line);
        std::stringstream headerStream(line);
        std::string headerItem;
        std::cout << std::left; // Align output to the left

        // Print header with fixed widths
        while (std::getline(headerStream, headerItem, ',')) {
            std::cout << std::setw(20) << headerItem;
        }
        std::cout << std::endl;
        std::cout << "-----------------------------------------------------------------------------------" << std::endl;

        // Loop through and read each data row
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string item;
            
            // Print each item with the same fixed width
            while (std::getline(ss, item, ',')) {
                std::cout << std::setw(20) << item;
            }
            std::cout << std::endl;
        }

        inFile.close();
        std::cout << "\nEnd of database content." << std::endl;
    } else {
        std::cerr << "Error: Unable to open the database file for reading. Please create it first." << std::endl;
    }
}

// Function to append a new record to the database
void addRecord() {
    std::ofstream outFile("database.txt", std::ios::app);
    std::string newId, newName, newEmail, newCity, Phone;
    if (outFile.is_open()) {
        std::cout << "\nEnter new record details:\n";
        std::cout << "ID: ";
        std::cin >> newId;
        std::cout << "Name: ";
        std::cin >> newName;
        std::cout << "Email: ";
        std::cin >> newEmail;
        std::cout << "City: ";
        std::cin >> newCity;
        // std::cout << "Phone: ";    Modification has to be done for this logic using a global boolean variable
        // std::cin >> Phone;
        outFile << newId << "," << newName << "," << newEmail << "," << newCity << "," << Phone << "\n";
        outFile.close();
        std::cout << "\nNew record added successfully to the database." << std::endl;
    } else {
        std::cerr << "Error: Unable to open the database file for writing." << std::endl;
    }
}

void addColumn() {
    std::ifstream inFile("database.txt");
    std::ofstream tempFile("temp.txt");
    std::string line;
    std::string newColumnName = "Phone";
    std::string newColumnValue = "N/A";

    // Check if both files can be opened
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open the original database file." << std::endl;
        return;
    }
    if (!tempFile.is_open()) {
        std::cerr << "Error: Unable to create temporary file." << std::endl;
        inFile.close();
        return;
    }

    // 1. Read the header, add the new column name, and write to the temporary file
    if (std::getline(inFile, line)) {
        tempFile << line << "," << newColumnName << "\n";
    }

    // 2. Read the remaining data, add the new column value, and write to the temporary file
    while (std::getline(inFile, line)) {
        tempFile << line << "," << newColumnValue << "\n";
    }

    // 3. Close both file streams
    inFile.close();
    tempFile.close();

    // 4. Replace the old file with the new one
    std::remove("database.txt");
    std::rename("temp.txt", "database.txt");

    std::cout << "\n'Phone' column added successfully with default value 'N/A'." << std::endl;
}

// ... (previous functions: createDatabase, readDatabase, addRecord)

// New function to add column goes here (see above)

int main() {
    int choice;
    do {
        // Display the menu
        std::cout << "\n--- Simple Database Menu ---\n";
        std::cout << "1. Create/Reset Database\n";
        std::cout << "2. Read Database (formatted)\n";
        std::cout << "3. Add New Record\n";
        std::cout << "4. Add a New Column\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                createDatabase();
                break;
            case 2:
                readDatabase();
                break;
            case 3:
                addRecord();
                break;
            case 4:
                addColumn(); // New case to call the new function
                break;
            case 5:
                std::cout << "\nExiting program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "\nInvalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 5);

    return 0;
}