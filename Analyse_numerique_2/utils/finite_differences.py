import numpy as np
import math

def CoefDF(k, xbar, x):
    """
    Calculate the coefficients of the finite difference approximation for the k-th derivative at a given point xbar.
    Parameters:
    k (int): The order of the derivative.
    xbar (float): The point at which the derivative is to be approximated.
    x (array-like): The array of points used for the finite difference approximation.
    Returns:
    numpy.ndarray: The coefficients of the finite difference approximation for the k-th derivative at xbar.
    Notes:
    - If k is out of bounds (less than 0 or greater than or equal to the length of x), the function will print an error message and return None.
    - The function uses the smallest spacing between points in x and the distance from xbar to the nearest point in x to determine the step size h.
    - The function constructs a matrix A based on the points in x and solves the linear system A * coef = B to find the coefficients.
    """
    x = np.array(x)
    n = len(x)
    A = np.vander(x - xbar, n, increasing=True).T
    b = np.zeros(n)
    b[k] = math.factorial(k)
    h = np.min(x[1:n] - x[0 : n - 1])
    h2 = np.min(np.abs(x - xbar))
    if k < 0 or k >= n:
        raise ValueError(f"k must be between 0 and {n-1}")
    if h2 > 0:
        print("here")
        h = min(h, h2)
    return np.linalg.solve(A, b) * h**k