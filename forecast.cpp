#include "forecast.hpp"
#include <cmath>
#include <numeric>
#include <iostream>

EnergyForecaster::EnergyForecaster() {}

void EnergyForecaster::addObservation(const Observation& obs) {
    observations.push_back(obs);
}

double EnergyForecaster::forecast(double temperature, int timeOfDay, int dayOfWeek) {
    if (observations.empty()) return 0;

    std::vector<double> coefficients = calculateCoefficients();
    double result = coefficients[0] + coefficients[1] * temperature + coefficients[2] * timeOfDay + coefficients[3] * dayOfWeek;

    std::cout << "Using Coefficients: " << coefficients[0] << ", " << coefficients[1] << ", " << coefficients[2] << ", " << coefficients[3] << std::endl;
    std::cout << "Forecast Input: Temperature = " << temperature << ", Time of Day = " << timeOfDay << ", Day of Week = " << dayOfWeek << std::endl;
    std::cout << "Calculated Forecast Result: " << result << std::endl;

    return result;
}


std::vector<double> EnergyForecaster::calculateCoefficients() {
    int n = observations.size();
    double x_sum = 0, y_sum = 0, xy_sum = 0, xx_sum = 0;

    for (const auto& obs : observations) {
        x_sum += obs.temperature;
        y_sum += obs.energyConsumption;
        xy_sum += obs.temperature * obs.energyConsumption;
        xx_sum += obs.temperature * obs.temperature;
    }

    std::cout << "Sum of x: " << x_sum << ", Sum of y: " << y_sum << ", Sum of xy: " << xy_sum << ", Sum of xx: " << xx_sum << std::endl;

    double temperature_coef = (n * xy_sum - x_sum * y_sum) / (n * xx_sum - x_sum * x_sum);
    double intercept = (y_sum - temperature_coef * x_sum) / n;

    std::cout << "Temperature Coef: " << temperature_coef << ", Intercept: " << intercept << std::endl;

    // Simplified coefficients for demonstration
    return { intercept, temperature_coef, 0.1, 0.05 };
}

