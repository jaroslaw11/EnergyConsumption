#ifndef FORECAST_HPP
#define FORECAST_HPP

#include <vector>

struct Observation {
    double temperature;  // Average temperature of the day
    int timeOfDay;       // Encoded as 0 = morning, 1 = afternoon, 2 = evening, 3 = night
    int dayOfWeek;       // 0 = Sunday, 1 = Monday, ..., 6 = Saturday
    double energyConsumption; // Energy consumption
};

class EnergyForecaster {
public:
    EnergyForecaster();
    void addObservation(const Observation& obs);
    double forecast(double temperature, int timeOfDay, int dayOfWeek);
private:
    std::vector<Observation> observations;
    std::vector<double> calculateCoefficients();
};

#endif
