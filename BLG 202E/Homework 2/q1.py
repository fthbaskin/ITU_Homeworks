# Fatih Baskın
# 150210710
import math

# Implementation of f(x)
# f(x) = 4*ln(x) - x


def fx(xn):
    return 4*(math.log(xn)) - xn

# Implementation of f'(x)
# f'(x) = 4/x - 1


def dfx(xn):
    return 4/xn - 1

# Newton method error calculation


def newton_error_estimate(xn):
    # Formula was derived on the paper.
    return abs((4 * xn * math.log(xn) - xn**2) / (4 - xn))


# Secant method error calculation


def secant_error_estimate(xn, xn_1):
    return abs(xn - xn_1)


# Newton method starts here:

# Ask input for Newton method iteration count.
print("Please provide the maximum number of iterations for the Newton method: ")
NEWTON_ITERATIONS = int(input())

# Ask non-zero starting point for the Newton method.
newton_x0 = float(0)
while (newton_x0 == 0):
    print("Please provide a non-zero starting number x0 for the Newton method: ")
    newton_x0 = float(input())

# starting xn
xn = newton_x0
newton_error_list = []


# Calculating xn iteratively:
for i in range(NEWTON_ITERATIONS):
    # xn on the left of the equation is xn+1 and calculated as xn - f(xn)/f'(xn).
    # xn value printed on the message is the new calculated xnext.
    xnext = xn - fx(xn)/dfx(xn)
    # Calculation of error estimation.
    newton_error = newton_error_estimate(xnext)
    newton_error_list.append(newton_error)
    # Since counter starts counting from 0, adding 1 to i value in the message.
    print("Iteration " + str(i + 1) + " xn = " + str(xnext) +
          " error estimation: " + str(newton_error))
    # After printing message, xn = xnext for the next iteration.
    xn = xnext
    # If we have reached zero estimated error, break the loop since no further calculations needed
    if(newton_error == 0):
        print("Reached zero estimated error, breaking from the iterative calculation.")
        break
    # If i >= 2, we can calculate convergence rate, note that if error is zero then we can't calculate ln(0).
    if(i >= 2):
        # To be able to analyse convergence rate, we need to see the ratio between current error ratios and pevious error ratios.
        # Calculated as ln(e(n+1) / en) / ln(en / e(n-1)).
        newton_convergence_rate = math.log(
            newton_error_list[i] / newton_error_list[i-1]) / math.log(newton_error_list[i-1] / newton_error_list[i-2])
        print("    convergence rate : " + str(newton_convergence_rate))


# Secant method starts here:

# Ask input for secant method iteration count.
print("Please provide maximum number of iterations for the secant method: ")
SECANT_ITERATIONS = int(input())

# Ask non-zero starting point x0 for the secant method.
secant_x0 = float(0)
while (secant_x0 == 0):
    print("Please provide a non-zero starting number x0 for the secant method: ")
    secant_x0 = float(input())

# Ask non-zero starting point x1 for the secant method.
secant_x1 = float(0)
while (secant_x1 == 0):
    print("Please provide a non-zero starting number x1 for the secant method: ")
    secant_x1 = float(input())

# starting x(n-1) and xn
xprev = float(secant_x0)
xn = float(secant_x1)
secant_error_list = []

# Calculating xn iteratively:
for i in range(SECANT_ITERATIONS):
    # xn on the left of the equation is xn+1 and calculated as xn - f(xn)/f'(xn) but f'(xn) = f(xn) - f(x(n-1)) / (xn - x(n-1)).
    # xn value printed on the message is the new calculated xnext.
    xnext = xn - fx(xn)*(xn - xprev)/(fx(xn) - fx(xprev))
    # Calculation of error estimation
    secant_error = secant_error_estimate(xnext, xn)
    secant_error_list.append(secant_error)
    # Since counter starts counting from 0, adding 2 to i value in the message (x0 and x1 is given).
    print("Iteration " + str(i + 2) + " xn = " + str(xnext) +
          " error estimation : " + str(secant_error))
    # After printing message, xprev = xn and xn = xnext for the next iteration.
    xprev = xn
    xn = xnext
    # If we have reached zero convergence, break the loop since no further calculations needed
    if(secant_error == 0):
        print("Reached zero estimated error, breaking from the iterative calculation.")
        break
    # If i >= 2, we can calculate convergence rate, note that if error is zero then we can't calculate ln(0).
    if(i >= 2):
        # To be able to analyse convergence rate, we need to see the ratio between current error ratios and pevious error ratios.
        # Calculated as ln(e(n+1) / en) / ln(en / e(n-1)).
        secant_convergence_rate = math.log(
            secant_error_list[i] / secant_error_list[i-1]) / math.log(secant_error_list[i-1] / secant_error_list[i-2])
        print("    convergence rate : " + str(secant_convergence_rate))
