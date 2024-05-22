'''
    Fatih Baskın
    150210710
'''
import numpy as np
import matplotlib.pyplot as plt


# Polynomial obtained is x^3 + 7x + 1
def poly(x):
    return x**3 + 7*x + 1

# Polynomial output to draw on the graph


def poly_out(x):
    dimension = x.shape[0]
    y = np.zeros(dimension)
    for i in range(dimension):
        y[i] = poly(x[i])
    return y


# Points given in the question
points = np.array([[0, 1, 2, 4, 6], [1, 9, 23, 93, 259]])

# Scattering points
plt.scatter(points[0], points[1], marker='x', c='r', label="actual values")

print("Polynomial is x^3 + 7x + 1")
print("Please provide the lower bound for the polynomial to be drawn:")
lb = float(input())
print("Please provide the upper bound for the polynomial to be drawn:")
ub = float(input())
print("Please provide the point x to be calculated on the polynomial:")
p_x = float(input())

# Settings for the polynomial to be drawn
plt.scatter([p_x], [poly(p_x)], marker='o', c='m',
            label="point x on the polynomial")
x_interval = np.linspace(lb, ub, 10000)
plt.plot(x_interval, poly_out(x_interval), '-b', label="p(x) = x^3 + 7x + 1")

# Plot settings
plt.legend()
plt.title("Question 2 Fatih Baskın 150210710")
plt.xlabel("x")
plt.ylabel("y")

plt.show()
