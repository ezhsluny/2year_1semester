from xgboost import XGBClassifier
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
import pandas as pd
import numpy as np


df_main = pd.read_csv("l9/titanic_prepared.csv")
df_y = df_main['label']
df_x = df_main.drop(['label'], axis=1)


X_train, X_test, y_train, y_test = train_test_split(df_x,
                                                    df_y,
                                                    test_size=0.1,
                                                    random_state=1)


rf = RandomForestClassifier()
# rf.fit(X_train, y_train)
# rf_pred = rf.predict(X_test)
# rf_accuracy = accuracy_score(y_test, rf_pred)
# print(rf_accuracy)
'''0.8975903614457831'''


xgb = XGBClassifier()
# xgb.fit(X_train, y_train)
# xgb_pred = xgb.predict(X_test)
# xgb_accuracy = accuracy_score(y_test, xgb_pred)
# print(xgb_accuracy)
'''0.8885542168674698'''


lr = LogisticRegression()
# lr.fit(X_train, y_train)
# lr_pred = lr.predict(X_test)
# lr_accuracy = accuracy_score(y_test, lr_pred)
# print(lr_accuracy)
'''0.8659638554216867'''


dtc = DecisionTreeClassifier()
dtc.fit(X_train, y_train)
feat_imp = dtc.feature_importances_
indices = np.argsort(feat_imp)[::-1][:2]
columns = df_x.columns[indices]

X_sel = X_train[columns]
X_sel_test = X_test[columns]

rf.fit(X_sel, y_train)
xgb.fit(X_sel, y_train)
lr.fit(X_sel, y_train)

rf_pred = rf.predict(X_sel_test)
rf_acc = accuracy_score(y_test, rf_pred)
print("rf: ", rf_acc)

xgb_pred = xgb.predict(X_sel_test)
xgb_acc = accuracy_score(y_test, xgb_pred)
print("xgb: ", xgb_acc)

lr_pred = lr.predict(X_sel_test)
lr_acc = accuracy_score(y_test, lr_pred)
print("lr: ", lr_acc)