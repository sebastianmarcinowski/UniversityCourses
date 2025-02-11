import numpy as np
import scipy as sp
from sklearn import datasets, model_selection, base
from sklearn.preprocessing import KBinsDiscretizer
import pandas as pd

test_dataset = "wine"
if test_dataset == "lenses":
    # Zbior lenses
    data = np.genfromtxt('lenses/lenses.data', dtype=int)
    X = data[:,1:-1]
    y =  data[:,-1]
elif test_dataset == "nursery":
    # Zbior nursery
    data = np.genfromtxt('nursery/nursery.data', dtype=str, delimiter=',')
    X = data[:,:-1]
    y = data[:,-1]
elif test_dataset == "grzyby":
    # Zbior grzyby
    data = np.genfromtxt('mushroom/agaricus-lepiota.data', dtype=str, delimiter=',')
    X = data[:, 1:]
    y = data[:, 0]
elif test_dataset == "wine":
    # Zbiot wine
    data = np.genfromtxt('wine/wine.data', dtype=float, delimiter=',')
    data = KBinsDiscretizer(n_bins=10, encode='ordinal', strategy='uniform').fit_transform(data)
    X = data[:,1:]
    y = data[:,0]
X_train, X_test, y_train, y_test = model_selection.train_test_split(X, y, test_size=0.2)


def discretize(sample_data, numBins, refMin, refMax):
    if refMin > refMax:
        raise ValueError('refMin must be less than or equal to refMax')
    binWidth = (refMax - refMin) / numBins
    bins = np.floor((np.clip(sample_data, refMin, refMax) - refMin) / binWidth).astype(int)
    bins[bins==numBins] = numBins - 1
    return bins

class NBC (base.BaseEstimator, base.ClassifierMixin):
    def __init__(self, laplace_fix):
        # self.X_train = None
        # self.y_train = None
        self.laplace_fix = laplace_fix

    def fit(self, X, y):
        # funkcja ucząca
        self.X_train = X
        self.y_train = y
        self._classes, self.number_of_classes = np.unique(y, return_counts=True)
        self.X_atributes = [np.unique(x) for x in X.T]
        self.count_list = []
        if not self.laplace_fix:
            for j , j_value in enumerate(self.X_atributes):
                tmp_table = np.zeros((len(j_value), len(self.number_of_classes)))
                for i, i_value in enumerate(j_value):
                    for k, k_value in enumerate(self._classes):
                        tmp_table[i, k] = np.sum((X[:,j] == i_value) & (y == k_value))
                self.count_list.append(tmp_table)
        else:
            for j, j_value in enumerate(self.X_atributes):
                tmp_table = np.ones((len(j_value), len(self.number_of_classes)))
                for i, i_value in enumerate(j_value):
                    for k, k_value in enumerate(self._classes):
                        tmp_table[i, k] += np.sum((X[:, j] == i_value) & (y == k_value))
                self.count_list.append(tmp_table)

        return self

    def predict(self, X_test):
        return np.array([self._classes[np.argmax(self.predict_proba(x))] for x in X_test])

    def predict_proba(self, x):
        # Calculate posterior probabilities
        posteriors = []
        for i, c in enumerate(self._classes):
            # prior = np.log(self.number_of_classes[i] / np.sum(self.number_of_classes))
            prior = self.number_of_classes[i] / len(self.number_of_classes)
            likelihood = 0
            for j in range(len(x)):
                value_idx = np.where(self.X_atributes[j] == x[j])[0]
                if value_idx.size > 0:
                    value_idx = value_idx[0]
                    if not self.laplace_fix:
                        # likelihood += np.log((self.count_list[j][value_idx, i] + 1e-9) / (self.number_of_classes[i] + 1e-9))
                        likelihood *= self.count_list[j][value_idx, i] / self.number_of_classes[i]
                    else:
                        # likelihood += np.log((self.count_list[j][value_idx, i]) / (self.number_of_classes[i] + len(self.X_atributes) + 1e-9))
                        likelihood *= self.count_list[j][value_idx, i] / (self.number_of_classes[i] + len(self.X_atributes))
            posterior = prior * likelihood
            posteriors.append(posterior)
        probabilities = np.exp(posteriors - np.max(posteriors))
        return probabilities / np.sum(probabilities)

    def score(self, y_true, y_test):
        return sum(y_test == y_true)/len(y_test)

nb1 = NBC(laplace_fix=False)
nb2 = NBC(laplace_fix=True)
nb1.fit(X_train, y_train)
nb2.fit(X_train, y_train)

pred1 = nb1.predict(X_test)
pred2 = nb2.predict(X_test)

accuracy1 = nb1.score(y_test, pred1)
accuracy2 = nb2.score(y_test, pred2)
print("Accuracy on test set with LaPlace = False:", accuracy1,"\n")
print("Accuracy on test set with LaPlace = True:", accuracy2)
