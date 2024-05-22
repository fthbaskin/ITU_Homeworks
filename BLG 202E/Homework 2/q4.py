# Fatih Baskın
# 150210710
import matplotlib.pyplot as plt
import numpy as np
import math

# Declaring the elements in the table as points using a 20x2 matrix.
points = np.array([[0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5,
                   5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10],
                   [0.72, 1.63, 1.88, 3.39, 4.02, 3.89, 4.25, 3.99, 4.68, 5.03,
                    5.27, 4.82, 5.67, 5.95, 5.72, 6.01, 5.5, 6.41, 5.83, 6.33]])

# Scatter graph, scatter values with red x'es.
plt.scatter(points[0], points[1], marker='x', c='r', label="actual values")

# Defining the line equation, outputs an array consisting of yi values for each xi.


def lx_output(x):
    # Creating a numpy array consisting of zeroes.
    dimension = x.shape[0]
    y = np.zeros(dimension)
    for i in range(dimension):
        # Then filling those zero values with line values.
        y[i] = 1.925 + 0.501*x[i]
    return y


# Plotting the line equation. Line is blue.
plt.plot(points[0], lx_output(points[0]), '-b', label="l(x) = 1.915 + 0.501x")

# Declaring an x interval for continous functions p(x) and f(x) starting from 0.25 and goes to 100
# Doesn't start from 0 intentionally, because lnx goes to infinity at x = 0.
x_interval = np.linspace(0.25, 10, 100)

# Defining p(x) equation, outputs its corresponding values as an array according to the interval provided.


def px_output(x):
    # Creating a numpy array consisting of zeroes.
    dimension = x.shape[0]
    y = np.zeros(dimension)
    for i in range(dimension):
        y[i] = -0.068*x[i]**2 + 1.219*x[i] + 0.599
    return y


# Plotting the polinomial equation. Polynomial is green.
plt.plot(x_interval, px_output(x_interval), '-g',
         label="p(x) = -0.068*x^2 + 1.219x + 0.599")

# Defifing f(x) equation,  outputs its corresponding values as an array according to the interval provided.


def fx_output(x):
    # Creating a numpy array consisting of zeroes.
    dimension = x.shape[0]
    y = np.zeros(dimension)
    for i in range(dimension):
        y[i] = 1.775 + 1.947*math.log(x[i])
    return y


# Plotting the logarithm equation. Logarithm is magenta.
plt.plot(x_interval, fx_output(x_interval), '-m',
         label="f(x) = 1.775 + 1.947*ln(x)")

# Last settings for the graph
plt.legend()
plt.title("Question 4 Fatih Baskın 150210710")
plt.xlabel("x")
plt.ylabel("y")

plt.show()
