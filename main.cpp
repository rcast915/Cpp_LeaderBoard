#include <iostream>      // For standard I/O (cin, cout)
#include <vector>        // For dynamic array (std::vector)
#include <string>        // For std::string
#include <sstream>       // For parsing strings using istringstream
#include <thread>        // For std::this_thread::sleep_for (pause execution)

/*
FUNCTION sortByScore(entries)
    FOR i FROM 0 TO length(entries) - 1
        FOR j FROM i + 1 TO length(entries)
            IF entries[i].value > entries[j].value THEN
                SWAP entries[i] AND entries[j]
            END IF
        END FOR
    END FOR
    RETURN entries
END FUNCTION
*/

// Useless function just makes your program slower but your terminal is cool
void progressBar(int width = 20, int totalMs = 1000) {
    std::cout << "[";
    for (int i = 0; i < width; ++i) {
        std::cout << "#" << std::flush; // Flush forces output immediately instead of buffering
        std::this_thread::sleep_for(std::chrono::milliseconds(totalMs / width)); // Sleep for part of total time
    }
    std::cout << "]\n";
}

// TEMPLATE CLASS
// Allows the leaderboard to be used with any numeric type (int, float, double, etc.)
template <typename T>
class Leaderboard {
private:
    std::vector<std::pair<std::string, T>> entries; // Stores name and score pairs
    static int totalEntries; // Shared across all instances (C++ quirk: must be defined outside class)

public:
    void addEntry(const std::string& name, T score); // Adds entry to list
    void print() const;                              // Prints the leaderboard
};

// SCOPE RESOLUTION OPERATOR + STATIC INITIALIZATION
// Static member needs to be defined outside the class template
template <typename T>
int Leaderboard<T>::totalEntries = 0;

template <typename T>
void Leaderboard<T>::addEntry(const std::string& name, T score) {
    entries.push_back({name, score}); // Adds name-score pair to vector
    ++totalEntries;                   // Increments static counter
}

template <typename T>
void Leaderboard<T>::print() const {
    std::cout << "\nLeaderboard\n";
    for (const auto& entry : entries) {
        std::cout << entry.first << ": " << entry.second << "\n"; // Print each entry
    }

    std::cout << "Total entries: " << totalEntries << "\n"; // Print static count
}

int main() {
    Leaderboard<double> lb; // Instantiate Leaderboard with double scores
    std::string name;
    std::string input;
    double score;

    std::cout << "Enter player names and scores (e.g., Alice 95.5).\n";
    std::cout << "Type 'done' to finish.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input); // Reads full line of input (safer than std::cin)

        if (input == "done") break;

        std::istringstream iss(input); // Use string stream to parse input
        iss >> name >> score;          // Extract name and score from string

        if (iss) {
            lb.addEntry(name, score);  // Add valid input to leaderboard
        } else {
            std::cerr << "⚠️ Invalid input. Try again.\n"; // Input parse failed (extra or missing tokens)
        }
    }

    // Help me sort the leaderboard by score in descending order
    //lb.sortByScore(); // Placeholder for future sorting implementation

    progressBar(); // Display fake loading bar for effect
    lb.print();    // Show the leaderboard
    return 0;
}

