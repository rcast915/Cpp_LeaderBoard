#include <iostream>      // For standard I/O (cin, cout)
#include <vector>        // For dynamic array (std::vector)
#include <string>        // For std::string
#include <sstream>       // For parsing strings using istringstream
#include <thread>        // For std::this_thread::sleep_for (pause execution)
#include <chrono>        // For std::chrono::milliseconds
#include <fstream>       // For writing to a CSV file

// g++ -std=c++17 -o leaderboard main2.cpp  

// Useless function just makes your program slower but your terminal is cool
void progressBar(int width = 20, int totalMs = 1000) {
    std::cout << "[";
    for (int i = 0; i < width; ++i) {
        std::cout << "#" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(totalMs / width));
    }
    std::cout << "]\n";
}

// TEMPLATE CLASS
// Allows the leaderboard to be used with any numeric type (int, float, double, etc.)
template <typename T>
class Leaderboard {
private:
    std::vector<std::pair<std::string, T>> entries;
    static int totalEntries;

public:
    void addEntry(const std::string& name, T score);
    void print() const;
    void sortByScore(); // Sorts entries by score in descending order
    void saveToCSV(const std::string& filename) const; // Saves entries to CSV
};

// SCOPE RESOLUTION OPERATOR + STATIC INITIALIZATION
template <typename T>
int Leaderboard<T>::totalEntries = 0;

template <typename T>
void Leaderboard<T>::addEntry(const std::string& name, T score) {
    entries.push_back({name, score});
    ++totalEntries;
}

template <typename T>
void Leaderboard<T>::print() const {
    std::cout << "\nLeaderboard\n";
    for (const auto& entry : entries) {
        std::cout << entry.first << ": " << entry.second << "\n";
    }
    std::cout << "Total entries: " << totalEntries << "\n";
}

template <typename T>
void Leaderboard<T>::sortByScore() {
    for (size_t i = 0; i < entries.size(); ++i) {
        for (size_t j = i + 1; j < entries.size(); ++j) {
            if (entries[i].second < entries[j].second) {
                std::swap(entries[i], entries[j]);
            }
        }
    }
}

template <typename T>
void Leaderboard<T>::saveToCSV(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "⚠️ Could not open file: " << filename << "\n";
        return;
    }

    outFile << "Name,Score\n";
    for (const auto& entry : entries) {
        outFile << entry.first << "," << entry.second << "\n";
    }

    outFile.close();
    std::cout << "✅ Leaderboard saved to " << filename << "\n";
}


int main() {
    Leaderboard<double> lb;
    std::string name;
    std::string input;
    double score;

    std::cout << "Enter player names and scores (e.g., Alice 95.5).\n";
    std::cout << "Type 'done' to finish.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "done") break;

        std::istringstream iss(input);
        iss >> name >> score;

        if (iss) {
            lb.addEntry(name, score);
        } else {
            std::cerr << "⚠️ Invalid input. Try again.\n";
        }
    }

    lb.sortByScore();             // Sort entries in descending order
    progressBar();                // Show loading animation
    lb.print();                   // Print the sorted leaderboard
    lb.saveToCSV("leaderboard.csv"); // Save to CSV

    return 0;
}
