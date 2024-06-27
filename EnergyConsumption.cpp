#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "forecast.hpp"

// Function to read data from a CSV file
bool loadData(const std::string& filePath, EnergyForecaster& forecaster) {
    std::ifstream dataFile(filePath);
    std::string line;

    if (!dataFile.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }

    while (std::getline(dataFile, line)) {
        std::istringstream iss(line);
        double temp;
        int time, day;
        double consumption;
        char comma;  // to skip commas in the CSV format

        if (!(iss >> temp >> comma >> time >> comma >> day >> comma >> consumption)) {
            std::cerr << "Failed to parse line: " << line << std::endl;
            continue; // skip malformed lines
        }
        Observation obs{ temp, time, day, consumption };
        forecaster.addObservation(obs);
        //forecaster.addObservation({ temp, time, day, consumption });
    }
    dataFile.close();
    return true;
}

int main() {
    EnergyForecaster forecaster;
    std::string filePath = "energy_data.csv";

    if (!loadData(filePath, forecaster)) {
        std::cerr << "Error loading data." << std::endl;
        return 1;
    }

    double temp;
    int timeOfDay, dayOfWeek;

    std::cout << "Enter the current temperature in Celsius: ";
    std::cin >> temp;
    std::cout << "Enter the current time of day (0=Morning, 1=Afternoon, 2=Evening, 3=Night): ";
    std::cin >> timeOfDay;
    std::cout << "Enter the current day of the week (0=Sunday, 1=Monday, ..., 6=Saturday): ";
    std::cin >> dayOfWeek;

    // Ensure valid inputs for time of day and day of week
    if (timeOfDay < 0 || timeOfDay > 3 || dayOfWeek < 0 || dayOfWeek > 6) {
        std::cerr << "Invalid time of day or day of week entered. Please enter correct values." << std::endl;
        return 1;
    }

    double forecastedDemand = forecaster.forecast(temp, timeOfDay, dayOfWeek);
    std::cout << "Forecasted Energy Demand under conditions - Temperature: " << temp
        << "°C, Time of Day: " << timeOfDay << ", Day of Week: " << dayOfWeek
        << " is: " << forecastedDemand << " units." << std::endl;
    std::cout << "Press enter to continue . . .";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    std::cin.get(); // Wait for enter

    return 0;
}
