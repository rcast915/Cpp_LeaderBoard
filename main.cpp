#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <thread> // for sleep_for


void progressBar(int width = 20, int totalMs = 1000) {
    std::cout << "[";
    for (int i = 0; i < width; ++i) {
        std::cout << "#" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(totalMs / width));
    }
    std::cout << "]\n";
}

// TEMPLATE CLASS
template <typename T>
class Leaderboard {
private:
    std::vector<std::pair<std::string, T>> entries;
    static int totalEntries;

public:
    void addEntry(const std::string& name, T score);
    void print() const;
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


    // Help me sort the leaderboard by score in descending order
    //lb.sortByScore();
    progressBar();
    lb.print();
    return 0;
}
