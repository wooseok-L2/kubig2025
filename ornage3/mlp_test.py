import numpy as np
import pandas as pd
from sklearn.metrics import accuracy_score
from sklearn.neural_network import MLPClassifier

df = pd.read_csv('/home/lws/kulws2025/kubig2025/ornage3/data/healthcare-dataset-3.csv')
print(df.shape)
print(df.info())
print(df.columns)
clf_mlp = MLPClassifier(max_iter=2000, random_state=0)

Y = df[df.columns[5]]
X = df.drop(df.columns[5], axis=1)
clf_mlp.fit(X, Y)
pred_y = clf_mlp.predict(X)
accuracy = accuracy_score(Y, pred_y)
print(accuracy)

