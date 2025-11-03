# Monte Carlo Stock Price Paths Visualization
library(ggplot2)
library(dplyr)

# Import the CSV file
stock_data <- monte_carlo_paths

# Step 1: Compute the average price at each time step
avg_path <- stock_data %>%
  group_by(Time_Step) %>%
  summarize(Average_Price = mean(Stock_Price))

# Step 2: Plot the simulations and the average path
ggplot() +
  # Plot all Monte Carlo simulation paths (thin and transparent)
  geom_line(
    data = stock_data,
    aes(x = Time_Step, y = Stock_Price, group = Simulation_Number, color = factor(Simulation_Number)),
    linewidth = 0.4,
    alpha = 0.4,
    show.legend = FALSE
  ) +
  
  # Overlay the average stock price path (bold black line)
  geom_line(
    data = avg_path,
    aes(x = Time_Step, y = Average_Price),
    color = "white",
    linewidth = 1
  ) +
  
  # Add labels and theme
  labs(
    title = "Monte Carlo Simulated Stock Price Paths with Average Path",
    x = "Time Step",
    y = "Stock Price"
  ) + 
  scale_x_continuous(limits = c(0, 12), expand = c(0, 0)) +
  theme_minimal(base_size = 10) +
  theme(
    panel.background = element_rect(fill = "black", color = NA),
    plot.background = element_rect(fill = "black", color = NA),
    panel.grid.major = element_line(color = "gray30", linewidth = 0.3),
    panel.grid.minor = element_line(color = "gray20", linewidth = 0.2),
    axis.text = element_text(color = "white"),
    axis.title = element_text(color = "white"),
    plot.title = element_text(color = "white", size = 12, face = "bold", hjust = 0.5, lineheight = 1.1)
    
  )

