
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

double getDistance() {

    double distance;

    while (true) {
        cout << "Enter journey distance in miles: ";

        if (cin >> distance && distance > 0) {
            return distance;
        }

        cout << "Enter a valid positive distance.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string getFuelType() {
    string fuel;

    while (true) {
        cout << "Enter fuel type (petrol/diesel): ";
        cin >> fuel;

        for (char &c : fuel)
            c = tolower(static_cast<unsigned char>(c));

        if (fuel == "petrol" || fuel == "diesel")
            return fuel;

        cout << "Invalid fuel type. Try again.\n";
    }
}

double calculateCO2(double distance, string fuel) {
    double fuelUsed = distance * 9.66 / 100;
    double emissionFactor = (fuel == "diesel") ? 2.68 : 2.31;

    return fuelUsed * emissionFactor;
}

int main() {
    cout << "----CO2 Emissions Calculator----\n";

    double distance = getDistance();
    string fuel = getFuelType();
    double emissions = calculateCO2(distance, fuel);

    cout << fixed << setprecision(2);
    cout << "\nDistance: " << distance << " miles\n";
    cout << "Fuel type: " << fuel << '\n';
    cout << "Estimated CO2 emissions: "
         << emissions << " kg\n";

    return 0;
}