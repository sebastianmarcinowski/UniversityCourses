import numpy as np
import matplotlib.pyplot as plt

class LinearPerceptron:
    def __init__(self, max_iter=1000, learn_coef=0.01):
        self.k = 0
        self.weights = None
        self.max_iter = max_iter
        self.learn_coef = learn_coef

    def fit(self, X, y):
        X = np.hstack((np.ones((X.shape[0], 1)), X))
        num_samples, num_features = X.shape
        self.weights = np.zeros(num_features)
        self.k = 0
        E = np.nonzero(y * self.decision_function(X) <= 0)
        while len(E[0]) > 0 and self.k < self.max_iter:
            i = np.random.choice(E[0])
            self.weights += y[i] * X[i]
            E = np.nonzero(y * self.decision_function(X) <= 0)
            self.k += 1

    def predict(self, X):
        X = np.hstack((np.ones((X.shape[0], 1)), X))
        return np.where(self.decision_function(X) >= 0.0, 1, -1)

    def decision_function(self, X):
        return np.dot(X, self.weights)


class NonlinearPerceptron:
    def __init__(self, n_centers=50, sigma=0.5, max_iter=1000):
        self.n_centers = n_centers
        self.sigma = sigma
        self.max_iter = max_iter
        self.weights = None
        self.k = 0

    def fit(self, X, y):
        # Add bias
        X = np.hstack((np.ones((X.shape[0], 1)), X))
        num_samples, num_features = X.shape
        # Inicjalizacja wektora wag
        self.weights = np.zeros(num_features)

        E = np.nonzero(y * self.decision_function(X) <= 0)
        while len(E[0]) > 0 or self.k < self.max_iter:
            i = np.random.choice(E[0])
            self.weights += y[i] * X[i]
            E = np.nonzero(y * self.decision_function(X) <= 0)
            self.k += 1

        # for _ in range(self.max_iter):
            # errors = 0
            # for x_i, y_i in zip(X, y):
            #     weight_fix = y_i - self.predict(x_i)
            #     self.weights += weight_fix * x_i
            #     errors += int(weight_fix != 0.0)
            # if errors == 0:
            #     break
            # self.k += 1

    def predict(self, x):
        result = np.dot(x, self.weights.T)
        return np.where(result > 0, 1.0, -1.0)

    def decision_function(self, X):
        return np.dot(X, self.weights)