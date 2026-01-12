'''
Задания
Разделите данные Титаника (train.csv) на тренировочную, валидационную и
тестовую часть. С помощью валидационной части подберите гиперпараметры
для моделей Random Forest, XGBoost, Logistic Regression и KNN. 
Получите точность этих моделей на тестовой части.

С помощью RandomForest выберите 2, 4, 8 самых важных признаков и 
проверьте точность моделей только на этих признаках.
'''


import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import accuracy_score
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.neighbors import KNeighborsClassifier


#-------------------------------------------------------------------
def prepare_num(df):
    df_num = df.drop(['Sex', 'Embarked', 'Pclass'], axis=1)
    df_sex = pd.get_dummies(df['Sex'])
    df_emb = pd.get_dummies(df['Embarked'], prefix='Emb')
    df_pcl = pd.get_dummies(df['Pclass'], prefix='Pclass')

    df_num = pd.concat((df_num, df_sex, df_emb, df_pcl), axis=1)
    return df_num
#-------------------------------------------------------------------


#-------------------------------------------------------------------
df_main = pd.read_csv('l9/train.csv')

df_prep_x = df_main.drop(['PassengerId', 'Survived', 
                          'Name', 'Ticket', 'Cabin'], 
                          axis=1)
df_prep_y = df_main['Survived']
df_prep_x_num = prepare_num(df_prep_x)
df_prep_x_num = df_prep_x_num.fillna(df_prep_x_num.median())
#-------------------------------------------------------------------


#-------------------------------------------------------------------
#split train, test and val data
X_train, X_test, y_train, y_test = train_test_split(df_prep_x_num, 
                                                    df_prep_y, 
                                                    test_size=0.3, 
                                                    random_state=1)
X_train, X_val, y_train, y_val = train_test_split(X_train, 
                                                  y_train, 
                                                  test_size=0.4, 
                                                  random_state=1)
#-------------------------------------------------------------------


#-------------------------------------------------------------------
#--------------Random Forest---------------
from sklearn.ensemble import RandomForestClassifier


rf = RandomForestClassifier()
rf.fit(X_train, y_train)
rf_pred = rf.predict(X_test)
rf_accuracy = accuracy_score(y_test, rf_pred) 
print('Random Forest accuracy without hyperparameters', rf_accuracy)
'''0.7761194029850746'''


# param_grid_rf = {
#     'n_estimators': range(60, 661, 200),
#     'max_depth': range(5, 26, 10),
# }
# rf = RandomForestClassifier()
# grid_search_rf = GridSearchCV(estimator=rf, param_grid=param_grid_rf, cv=5) 
# #cv - number of folds in cross-validation. k-1 iter-s, then test on k-th
# repeat k times
# grid_search_rf.fit(X_val, y_val)

# print("Best parameters for Random Forest:", grid_search_rf.best_params_)
# rf_best = grid_search_rf.best_estimator_

# Best parameters for Random Forest: {'max_depth': None, 'n_estimators': 100}
'''0.7649253731343284'''


rf2 = RandomForestClassifier(n_estimators=260, max_depth=5)
rf2.fit(X_train, y_train)
rf2_pred = rf2.predict(X_test)
rf2_accuracy = accuracy_score(y_test, rf2_pred)
print('Random Forest accuracy with hyperparameters', rf2_accuracy)
'''0.7761194029850746'''
#-------------------------------------------------------------------


#-------------------------------------------------------------------
#------------------------XGBoost------------------------------------
from xgboost import XGBClassifier


xgb = XGBClassifier()
xgb.fit(X_train, y_train)
xgb_pred = xgb.predict(X_test)

xgb_accuracy = accuracy_score(y_test, xgb_pred)
print("XGBoost accuracy without parameters: ", xgb_accuracy)
'''0.7686567164179104'''


# param_grid_rf = {
#     'n_estimators': range(60, 661, 200),
#     'max_depth': range(5, 26, 10),
# }

# xgb1 = XGBClassifier()
# grid_search_xgb = GridSearchCV(estimator=xgb1, param_grid=param_grid_rf, cv=5)
# grid_search_xgb.fit(X_val, y_val)
# print("Best parameters for XGBoost:", grid_search_xgb.best_params_)


#parameters from stackoverflow
xgb = XGBClassifier(max_depth=3, n_estimators=100) 
'''0.7798507462686567'''
xgb.fit(X_train, y_train)
xgb_pred = xgb.predict(X_test)

xgb_accuracy = accuracy_score(y_test, xgb_pred)
'''Best parameters for XGBoost: {'max_depth': 5, 'n_estimators': 60}'''
print("XGBoost accuracy with hyperparameters: ", xgb_accuracy)
'''0.7723880597014925'''
#-------------------------------------------------------------------


#-------------------------------------------------------------------
#------------------------LogisticRegression-------------------------
from sklearn.linear_model import LogisticRegression


lr = LogisticRegression()
lr.fit(X_train, y_train)
lr_pred = lr.predict(X_test)

lr_accuracy = accuracy_score(y_test, lr_pred)
print("Logistic Regression accuracy without hyperparameters: ", lr_accuracy)
'''0.7835820895522388'''


lr1 = LogisticRegression(C=0.2976351441631313, 
                         solver='liblinear', 
                         max_iter=100,
                         penalty='l1')
lr1.fit(X_train, y_train)
lr1_pred = lr1.predict(X_test)

lr1_accuracy = accuracy_score(y_test, lr1_pred)
print("Logistic Regression accuracy with hyperparameters: ", lr1_accuracy)
'''0.7761194029850746'''


# param_grid_lr = [    
#     {'penalty' : ['l1', 'l2', 'elasticnet', 'none'],
#     'C' : np.logspace(-10, 10, 20),
#     'solver' : ['lbfgs','newton-cg','liblinear','sag','saga'],
#     'max_iter' : [100, 1000,2500, 5000]
#     }
# ]

# lr = LogisticRegression(random_state=42)
# grid_search_lr = GridSearchCV(estimator=lr, param_grid=param_grid_lr, cv=5, n_jobs=-1)
# grid_search_lr.fit(X_val, y_val)

# print("Best parameters for Logistic Regression:", grid_search_lr.best_params_)
'''Best parameters for Logistic Regression: {'C': 0.2976351441631313, 
                                             'max_iter': 100, 
                                             'penalty': 'l1', 
                                             'solver': 'liblinear'}'''
#-------------------------------------------------------------------


#-------------------------------------------------------------------
#-----------------------------KNN-----------------------------------
from sklearn.neighbors import KNeighborsClassifier


knn = KNeighborsClassifier()
knn.fit(X_train, y_train)
knn_pred = knn.predict(X_test)

knn_accuracy = accuracy_score(y_test, knn_pred)
print("KNN accuracy without hyperparameters: ", knn_accuracy)
'''0.6865671641791045'''


# param_grid_knn = {
#     'n_neighbors': [3, 5, 7, 10],
#     'weights': ['uniform', 'distance'],
#     'algorithm': ['auto', 'ball_tree', 'kd_tree', 'brute']
# }

# knn = KNeighborsClassifier()
# grid_search_knn = GridSearchCV(estimator=knn, param_grid=param_grid_knn, cv=5, n_jobs=-1)
# grid_search_knn.fit(X_val, y_val)

# print("Best parameters for KNN:", grid_search_knn.best_params_)
'''Best parameters for KNN: {'algorithm': 'auto', 
'n_neighbors': 7, 'weights': 'distance'}'''


knn1 = KNeighborsClassifier(algorithm='auto', n_neighbors=7, weights='distance')
knn1.fit(X_train, y_train)
knn1_pred = knn1.predict(X_test)

knn1_accuracy = accuracy_score(y_test, knn1_pred)
print("KNN accuracy with hyperparameters: ", knn1_accuracy)
'''0.7126865671641791'''
#-------------------------------------------------------------------


#-------------------------------------------------------------------
#---------------------feature importances---------------------------
rf2 = RandomForestClassifier(n_estimators=260, max_depth=5)
rf2.fit(X_train, y_train)


feature_importances = rf2.feature_importances_
n = [2, 4 ,8]

for i in n:
    indices = np.argsort(feature_importances)[::-1][:i]
    columns = df_prep_x_num.columns[indices]

    X_selected = X_train[columns]
    X_sel_test = X_test[columns]

    rf_selected = RandomForestClassifier(n_estimators=260, max_depth=5)
    rf_selected.fit(X_selected, y_train)
    rf_pred = rf_selected.predict(X_sel_test)
    rf_accuracy = accuracy_score(y_test, rf_pred)
    print(f'accuracy with {i} features: {rf_accuracy}')