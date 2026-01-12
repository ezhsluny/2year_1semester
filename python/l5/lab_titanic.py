import pandas as pd
import numpy as np


cinema_sessions = pd.read_csv("l5/cinema_sessions.csv", sep=' ')
cinema_sessions = cinema_sessions.set_index('check_number')
titanic_list = pd.read_csv("l5/titanic_with_labels.csv", sep=' ')
cinema_sessions = cinema_sessions.drop(columns=['Unnamed: 0'])
titanic_list = titanic_list.drop(columns=['Unnamed: 0'])


database = pd.merge(cinema_sessions, titanic_list, on = 'check_number')
for col in database.select_dtypes(include=['object']).columns:
    database[col] = database[col].str.lower()
database = database.query('sex != "не указан"')
database = database.query('sex != "-"')
database['sex'].replace('m', value=0, inplace=True)
database['sex'].replace('м', value=0, inplace=True)
database['sex'].replace('мужчина', value=0, inplace=True)
database['sex'].replace('ж', value=1, inplace=True)

print(database['sex'].unique())

database['row_number'].fillna(value=database['row_number'].max(), inplace=True)


tmp = database['liters_drunk']
tmp = tmp.where(tmp > 0)
tmp = tmp.where(tmp <= 3)
# tmp = tmp.dropna()
avg_liters_drunk = np.average(tmp.dropna())


# database['liters_drunk'] = database['liters_drunk'].where(database['liters_drunk'] > 0)
# database['liters_drunk'] = database['liters_drunk'].where(database['liters_drunk'] <= 3)
database['liters_drunk'] = tmp.fillna(avg_liters_drunk)


print(database.head())