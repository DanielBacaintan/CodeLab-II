
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

vector<string> loadJokes() {
    vector<string> jokes;
    ifstream file("randomJokes.txt");
    string line;

    if (!file) {
        cout << "Error: Cannot open randomJokes.txt\n";
        return jokes;
    }

    while (getline(file, line)) {
        if (!line.empty())
            jokes.push_back(line);
    }

    file.close();
    return jokes;
}

void tellJoke(const vector<string>& jokes) {
    string joke = jokes[rand() % jokes.size()];
    size_t position = joke.find('?');

    if (position == string::npos) {
        cout << "Invalid joke format.\n";
        return;
    }

    cout << "\n" << joke.substr(0, position + 1) << '\n';
    cout << "Press Enter to reveal the punchline...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    cout << joke.substr(position + 1) << "\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    vector<string> jokes = loadJokes();

    if (jokes.empty()) {
        cout << "No jokes available.\n";
        return 1;
    }

    string command;
    cout << "----Alexa, Tell Me a Joke----\n";

    while (true) {
        cout << "\nEnter 'Alexa, tell me a joke' or 'q' to quit: ";
        getline(cin, command);

        if (command == "q" || command == "Q") {
            cout << "Goodbye!\n";
            break;
        }
        else if (command == "Alexa, tell me a joke" ||
                 command == "alexa, tell me a joke") {
            tellJoke(jokes);
        }
        else {
            cout << "Invalid command. Please try again.\n";
        }
    }

    return 0;
}