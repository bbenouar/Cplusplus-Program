#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cctype> // Include this header for isalpha() function
#include <limits> // Include this header for numeric_limits

using namespace std;
// ANSI escape code for red color
const string RED_COLOR = "\x1B[31m";
const string RESET_COLOR = "\x1B[0m";

// Class definition for CornerGrocer
class CornerGrocer {
private:
    map<string, int> frequencyMap;

public:
    // Constructor to initialize the frequency map from input file and create the data file
        CornerGrocer(const string& inputFileName, const string& dataFileName) {
        createFrequencyData(inputFileName);
        createDataFile(dataFileName);
    }
    // Function to display the frequency of a specific item
    int displayFrequency(const string& item) const {
        if (frequencyMap.count(item) == 0) {
            return 0;
        }
        return frequencyMap.at(item);
    }
    // Function to display a list of all items and their frequencies
    void displayAllFrequencies() const {
        for (const auto& item : frequencyMap) {
            cout << item.first << " " << RED_COLOR << item.second << RESET_COLOR << endl;
        }
    }
    // Function to display a histogram of all items
    void displayHistogram() const {
        cout <<RED_COLOR << "Histogram of all items:" << RESET_COLOR << endl;
        cout << "======================" << endl;
        for (const auto& item : frequencyMap) {
            cout << item.first << " ";
            for (int i = 0; i < item.second; ++i) {
                cout << RED_COLOR << "*" << RESET_COLOR;
            }
            cout << endl;
        }
    }
    // Function to run the menu for user interaction
    void runMenu() {
        int choice;
        while (true) {
            cout << "Corner Grocer" << endl;
            cout << "==============" << endl;
            cout << "1. Display frequency for a specific item from list" << endl;
            cout << "2. Display a list of all items and their frequencies" << endl;
            cout << "3. Display histogram of all items" << endl;
            cout << "4. Exit Application" << endl;
            cout << "Please enter your selection as a number 1-4: ";
            cin >> choice;

            if (cin.fail()) {
                cout << "Invalid input. Please enter a valid number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            // Only numbers between 1 and 4 are accepted ( inclusif)
            if (choice < 1 || choice > 4) {
                cout << "Invalid input. Please enter a number between 1 and 4." << endl;
                continue;
            }

            if (choice == 1) {
                string itemToSearch;
                cout << "Enter the item name to search: ";
                cin >> itemToSearch;
                // Check for Letters only
                if (cin.fail() || !all_letters(itemToSearch)) {
                    cout << "Invalid input. Please enter a valid item name." << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                int frequency = displayFrequency(itemToSearch);
                if (frequency > 0) {
                    cout << RED_COLOR << "Frequency of " << itemToSearch << ": " << frequency << RESET_COLOR << endl;
                }
                else {
                    cout << "Item not found in the records." << endl;
                }
            }
            else if (choice == 2) {
                cout << RED_COLOR << "List of items and their frequencies:" << RESET_COLOR << endl;
                cout << "====================================" << endl;
                displayAllFrequencies();
            }
            else if (choice == 3) {
                displayHistogram();
            }
            else if (choice == 4) {
                break;
            }
            else {
                cout << "Invalid input. Please try again." << endl;
            }
        }
    }

private:
    // Function to read the input file and create the frequency map
    void createFrequencyData(const string& inputFileName) {
        ifstream inputFile(inputFileName);
        if (!inputFile) {
            cout << "Error: Unable to open the input file." << endl;
            exit(1);
        }

        string item;
        while (inputFile >> item) {
            frequencyMap[item]++;
        }

        inputFile.close();
    }
    // Function to create the data file for backup purposes
    void createDataFile(const string& outputFileName) const {
        ofstream outputFile(outputFileName);
        if (!outputFile) {
            cout << "Error: Unable to create the data file." << endl;
            exit(1);
        }

        for (const auto& item : frequencyMap) {
            outputFile << item.first << " " << item.second << endl;
        }

        outputFile.close();
    }
    // Function to check if a string consists of all letters
    bool all_letters(const string& str) const {
        for (char c : str) {
            if (!isalpha(c)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    // The given list of items file.
    const string inputFileName = "CS210_Project_Three_Input_File.txt";
    // The program created frequency data file.
    const string dataFileName = "frequency.dat";

    CornerGrocer cornerGrocer(inputFileName, dataFileName);
    cornerGrocer.runMenu();

    return 0;
}
