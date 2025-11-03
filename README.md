# AsianOptionMethod
Allows users to input option parameters and runs Monte Carlo simulations to find a call option price. 

# Explaining the Different Files

1) The key file is the asionOptionMethod.cpp where it has methods like converting user inputed time in terms of years, simulating a single stock path, calculating the payoff per stock path, and running stock paths for user inputed number of times. Additionally, as the stock paths are being generated, they are being added to an 2d Array List that stores the simulation (0, 1, 2, ...) and the values for each simulation (stock movement).  

2) runningMonte.cpp asks user for input regarding the Asian Option which it then uses to run the Monte Carlo and generate a estimate for the asian option. Moreover, it also executes saveToCSV which generates a CSV file of the different stock simulations and how the stock moved in each simulation. 

3) monteCarloVisualizer.R is a R file where you can upload the CSV file and run a ggPlot program to visulaize the differnet stock paths over the different simulations. On top of that, the R program also generates an average stock movement line as well. 
