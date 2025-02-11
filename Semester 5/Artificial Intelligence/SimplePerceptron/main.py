import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from perc import LinearPerceptron, NonlinearPerceptron
import random

liniowa = False
if liniowa:
    # Generowanie danych liniowo separowalnych
    gamma = 0.1
    alfa = np.random.rand(1).squeeze() * 2 * np.pi
    data = np.random.rand(100, 2) * 2 - 1
    for i in range(len(data[:, 0])):
        if data[i, 0] >= 0:
            data[i, 0] += gamma/2
        else:
            data[i, 0] -= gamma/2
    y = 2*(data[:, 0] > 0) - 1
    rotate_matrix = np.array([[np.cos(alfa), -np.sin(alfa)], [np.sin(alfa), np.cos(alfa)]])
    data = np.dot(data, rotate_matrix)
    plt.scatter(data[:,0], data[:,1], c=y)

    perc = LinearPerceptron()
    perc.fit(data, y)
    x_values = np.linspace(min(data[:, 0]), max(data[:, 0]), 100)
    y_values = -(perc.weights[1] / perc.weights[2]) * x_values - (perc.weights[0] / perc.weights[2])
    plt.plot(x_values, y_values, label='Perceptron decision boundary', color='green')
    plt.xlabel('Feature 1')
    plt.ylabel('Feature 2')
    plt.legend()
    plt.show()
else:
    sample_size = 1000
    number_of_centers = 100
    sigma = 0.5
    max_iterations = 2500

    # Generowanie danych nieseparowalnych liniowo
    xi1 = np.random.uniform(0, 2 * np.pi, sample_size)
    xi2 = np.random.uniform(-1, 1, sample_size)
    xi = np.column_stack((np.ones(sample_size), xi1, xi2))
    y = np.where(np.abs(np.sin(xi1)) > np.abs(xi2), -1, 1)

    # Normalizacja danych
    x_min, x_max = xi.min(axis=0), xi.max(axis=0)
    range_vals = x_max - x_min
    range_vals[range_vals == 0] = 1
    X = 2 * (xi - x_min) / range_vals - 1

    # Podniesienie wymiarowości
    centers = random.sample(list(zip(xi1, xi2)), number_of_centers)
    centers = np.array(centers)
    zi = np.zeros((len(xi), len(centers)))
    for i in range(len(xi)):
        for j in range(len(centers)):
            zi[i, j] = np.exp(-np.linalg.norm(xi[i, 1:] - centers[j]) ** 2 / (2 * (sigma ** 2)))

    # Train the perceptron
    perc = NonlinearPerceptron(n_centers=number_of_centers, sigma=sigma, max_iter=max_iterations)
    perc.fit(zi, y)

    # Create the meshgrid
    x_min, x_max = xi1.min() - 0.1, xi1.max() + 0.1
    y_min, y_max = xi2.min() - 0.1, xi2.max() + 0.1
    xx, yy = np.meshgrid(np.linspace(x_min, x_max, 500), np.linspace(y_min, y_max, 500))
    grid_points = np.c_[xx.ravel(), yy.ravel()]

    # Map each point in the meshgrid to the feature space using the Gaussian kernel
    zi_grid = np.zeros((grid_points.shape[0], len(centers)))
    for i in range(grid_points.shape[0]):
        for j in range(len(centers)):
            zi_grid[i, j] = np.exp(-np.linalg.norm(grid_points[i] - centers[j]) ** 2 / (2 * (sigma ** 2)))
    zi_grid = np.hstack((np.ones((zi_grid.shape[0], 1)), zi_grid))

    # Use the perceptron to predict the class for each mapped point
    Z = perc.predict(zi_grid)
    Z = Z.reshape(xx.shape)

    # Plot the decision boundary using contourf
    plt.figure(figsize=(10, 6))
    plt.contourf(xx, yy, Z, alpha=0.75, levels=np.linspace(Z.min(), Z.max(), 3), cmap=plt.cm.Paired)
    plt.colorbar(label="Class probability")

    # Plot data points
    plt.scatter(xi1[y == -1], xi2[y == -1], c='red', label='Class -1', edgecolor='k', alpha=0.8)
    plt.scatter(xi1[y == 1], xi2[y == 1], c='blue', label='Class 1', edgecolor='k', alpha=0.8)

    # Plot centers
    plt.scatter(centers[:, 0], centers[:, 1], c='black', label='Centers', edgecolor='white', s=100, linewidths=1)

    # Enhance plot details
    plt.title("Nonlinear Perceptron Decision Boundary")
    plt.xlabel("Feature 1 (Normalized)")
    plt.ylabel("Feature 2 (Normalized)")
    plt.legend(loc='upper right')
    plt.grid(True)
    plt.tight_layout()
    plt.show()