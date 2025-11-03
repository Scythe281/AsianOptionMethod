#include <iostream>
#include <string>
#include <cmath>
#include <random>

#include "asianOptionMethod.cpp"




int main() {
    std::cout << "\n";
    std::cout << "Begenning Simulation Now . . . " << "\n";

double stockPrice; 
double strikePrice;
double interestRate;
double volatility;

double time; 
std::string timeFrame;

int numberObservation; 


int numberSimulations;


std::cout << "Stock Price: ";
std::cin >> stockPrice; 

std::cout << "Strike Price: ";
std::cin >> strikePrice;

std::cout << "Intrest Rate: ";
std::cin >> interestRate; 

std::cout << "Volatility: ";
std::cin >> volatility; 

std::cout << "Time: ";
std::cin >> time; 

std::cout << "Time Frame (Weeks, Months, Year): ";
std::cin >> timeFrame; 

std::cout << "Number of Observations: ";
std::cin >> numberObservation; 

std::cout << "Number of Simulations: ";
std::cin >> numberSimulations; 

asianOptionMethod option (stockPrice, strikePrice, interestRate, volatility, time, timeFrame, numberObservation, numberSimulations);

double optionPrice = option.runAndPriceOption();
option.saveToCSV("monte_carlo_paths.csv");

std::cout << "\n" << "The option price from Monte Carlo simulations is " << optionPrice << "\n"; 

std::cout << ". . . Ending Simulation Now" << "\n";

    return 0;
} 
