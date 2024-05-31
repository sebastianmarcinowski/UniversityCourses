import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB
from sklearn.discriminant_analysis import QuadraticDiscriminantAnalysis
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
from sklearn import metrics
import time

# Zadanie 1
X,y = make_classification(
    n_samples=1000,
    n_features=2,
    n_informative=2,
    n_redundant=0,
    n_clusters_per_class=2)

# Zadanie 2
# plt.scatter(X[:,0],X[:,1],c=y)
# plt.show()

# Zadanie 3
clf = [GaussianNB(), QuadraticDiscriminantAnalysis(), KNeighborsClassifier(), SVC(probability=True), DecisionTreeClassifier()]
klasyfikatory = ["GaussianNB","QudraticDiscriminantAnalysis","KNeighboursClassifier","SVC","DecisionTreeClassifier"]
df = pd.DataFrame({"Klasyfikator":klasyfikatory,"Dokladnosc":[None]*len(klasyfikatory),"Czulosc":[None]*len(klasyfikatory),"Precyzja":[None]*len(klasyfikatory),"F1":[None]*len(klasyfikatory),"Pole ROC":[None]*len(klasyfikatory),"Czas uczenia":[None]*len(klasyfikatory),"Czas testowania":[None]*len(klasyfikatory)})
df.loc[df["Klasyfikator"]=="SVC","Precyzja"]=0.9

for i in range(len(clf)):
    dokladnosc=[]
    czulosc=[]
    precyzja=[]
    f1=[]
    poleROC=[]
    for j in range(10):
        X_train,X_test,y_train,y_test = train_test_split(X,y)
        time1 = time.time()
        clf[i].fit(X_train,y_train)
        time2 = time.time()
        y_pred = clf[i].predict(X_test)
        time3 = time.time()
        dokladnosc.append(metrics.accuracy_score(y_test,y_pred))
        czulosc.append(metrics.recall_score(y_test,y_pred))
        precyzja.append(metrics.precision_score(y_test,y_pred))
        f1.append(metrics.f1_score(y_test,y_pred))
        poleROC.append(metrics.roc_auc_score(y_test,y_pred))
    df.loc[df["Klasyfikator"]==klasyfikatory[i],"Dokladnosc"]=np.mean(dokladnosc)
    df.loc[df["Klasyfikator"]==klasyfikatory[i],"Czulosc"]=np.mean(czulosc)
    df.loc[df["Klasyfikator"]==klasyfikatory[i],"Precyzja"]=np.mean(precyzja)
    df.loc[df["Klasyfikator"]==klasyfikatory[i],"F1"]=np.mean(f1)
    df.loc[df["Klasyfikator"]==klasyfikatory[i],"Pole ROC"]=np.mean(poleROC)
    df.loc[df["Klasyfikator"]==klasyfikatory[i],"Czas uczenia"]=time2-time1
    df.loc[df["Klasyfikator"]==klasyfikatory[i],"Czas testowania"]=time3-time2

    # Błedy klasyfikacji
    plt.subplot(1,3,1)
    plt.scatter(X[:,0],X[:,1],c=y)
    plt.title("Oryginalne dane")
    plt.subplot(1,3,2)
    plt.scatter(X[:,0],X[:,1],c=y)
    plt.title("Dane z predykcji")
    plt.subplot(1,3,3)
    plt.scatter(X[:,0],X[:,1],c=y)
    plt.title("Błąd klasyfikacji: " + klasyfikatory[i])
    plt.show()

    # Krzywa ROC
    y_prob = clf[i].predict_proba(X_test)[:,1]
    fpr,tpr,tresholds = metrics.roc_curve(y_test,y_prob)
    plt.plot(fpr, tpr, color='blue')
    plt.plot([0, 1], [0, 1], color='red', linestyle='--')
    plt.title("Krzywa ROC dla: " + klasyfikatory[i])
    plt.show()

    # Krzywa dyskryminacyjna
    xx, yy = np.meshgrid(np.linspace(X[:,0].min(), X[:,0].max(), 100),
                    np.linspace(X[:,1].min(), X[:,1].max(), 100))
    Z = clf[i].predict(np.c_[xx.ravel(), yy.ravel()])
    Z = np.array(Z).reshape(xx.shape)
    plt.contourf(xx, yy, Z)
    plt.scatter(X[:,0],X[:,1],c=y)
    plt.title(klasyfikatory[i])
    plt.show()
# print(df)

miary = ["Dokladnosc", "Czulosc", "Precyzja", "F1", "Pole ROC","Czas uczenia", "Czas testowania"]
x = np.arange(len(klasyfikatory))
f, ax = plt.subplots(figsize=(12, 6))
for i, m in enumerate(miary):
    ax.bar(x + i * 0.1, df[m], 0.1, label=m)
ax.set_xlabel('Klasyfikator')
ax.set_ylabel('Wartość')
ax.set_title('Wyniki miar jakości klasyfikacji')
ax.set_xticks(x + 0.1 * (len(miary) - 1) / 2)
ax.set_xticklabels(klasyfikatory)
ax.legend(title="Miary",loc='lower right')
plt.show()