/* To run: 
first: g++ runningMonte.cpp asianOptionMethod.cpp -o runMonte
second: ./runMonte */
#include <string>
#include <cmath>
#include <random>
#include <iostream>
#include <vector> 
#include <fstream>

class asianOptionMethod {

private: 

    std::random_device rd; 
    std::mt19937 gen;
    std::normal_distribution<> normal;
    

    double stockPrice; 
    double strikePrice;
    double interestRate;
    double volatility;

    double time; 
    std::string timeFrame;

    std::vector<std::vector<double>> allPaths;

    int numberObservation; 
   // std::string observationFrame;

    int numberSimulations;

    // Helper functions (now private since only used internally)
    double convertToYears(double time, const std::string& timeFrame) {
        if (timeFrame == "Weeks" || timeFrame == "Week") {
            return time / 52.0;
        }
        else if (timeFrame == "Months" || timeFrame == "Month") {
            return time / 12.0;
        }
        else if (timeFrame == "Years" || timeFrame == "Year") {
            return time;
        }
        else if (timeFrame == "Days" || timeFrame == "Day") {
            return time / 365.0;
        }
        return time; // Default: assume years
    }
 

public: 

    asianOptionMethod(double sP, double stP, double iR, double vol, double t, std::string tf, int numObs, int sim)
    : stockPrice(sP), strikePrice(stP), interestRate(iR), volatility(vol), numberObservation(numObs), numberSimulations(sim), rd(), gen(rd()), normal(0.0,1.0) {
        time = convertToYears(t, tf);
      }

    double simulateSinglePath () {
        double dt = time/numberObservation;

        double drift = (interestRate - .5*volatility*volatility)*dt;
        double diffusion = volatility*(std::sqrt(dt));
                
        double sum = 0; 
        double newSTKPrice = stockPrice;

        std::vector<double> currentPath;
        currentPath.reserve(numberObservation +1);
        currentPath.push_back(newSTKPrice);

        for (int i = 0; i < numberObservation; i++) {
            double z = normal(gen);
            newSTKPrice *=  std::exp(drift+ diffusion*z);
            currentPath.push_back(newSTKPrice);
            sum += newSTKPrice;
        }
        
        allPaths.push_back(currentPath);
        double averagePrice = sum/numberObservation;
    return averagePrice;
    }

// only for calls right now, for puts need extra parameter of call/put + braching if-else statements
    double calculatePayoff (double avgPrice) {
      
        double payoff = std::max(avgPrice - strikePrice, 0.0);

        return payoff;
    }
 
    double monteCarloResults() {
        double cumulativePayoff = 0.0;
        
        for (int i = 0; i < numberSimulations; i++) {
            double onePathPayoff = calculatePayoff(simulateSinglePath());
            cumulativePayoff += onePathPayoff;

        }

        double allSimPayoff = cumulativePayoff/numberSimulations;
        
        return allSimPayoff;

    }

    double discountToPresent(double monteCarloAVGPayoff) {
        double multiplicationFactor = std::exp(-interestRate*time);
        double dicountedPayoff = monteCarloAVGPayoff*multiplicationFactor;
        return dicountedPayoff; 
    }

    double runAndPriceOption () {
        double monteCarlo = monteCarloResults();
        return discountToPresent(monteCarlo);
    }

    void saveToCSV(std::string fileName) {
        
        std::ofstream file(fileName);

        file << "Simulation_Number,Time_Step,Stock_Price\n";

        for (size_t sim = 0; sim < allPaths.size(); sim++) {
            for (size_t step = 0; step < allPaths[sim].size(); step++) {

                file << sim << "," << step << "," << allPaths[sim][step] << "\n";

            }

        }
        file.close();


    }





};


