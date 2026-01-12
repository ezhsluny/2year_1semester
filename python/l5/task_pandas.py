import pandas as pd
import numpy as np


#1
data = np.random.random(size = (10, 5))
df = pd.DataFrame(data)
df_t = np.transpose(df)

av_values = []
for i in range(10):
    line_av = 0
    n = 0
    for j in range(5):
        if df_t[i][j] > 0.3:
            line_av += df_t[i][j]
            n += 1
    line_av /= n
    av_values.append(line_av)

print(df)
av_values = pd.Series(av_values)
av_values.to_csv("l5/output1.csv")


#2
df = pd.read_csv("l5/wells_info.csv")
df = df.set_index('API')
print(df.shape)
df['CompletionDate'] = pd.to_datetime(df['CompletionDate'])
df['FirstProductionDate'] = pd.to_datetime(df['FirstProductionDate'])
res = (df['CompletionDate'] - df['FirstProductionDate'])
res = pd.DataFrame((res.dt.components['days'] / 30).apply(np.floor))
res.to_csv("l5/output2.csv")


#3
df = pd.read_csv("l5/wells_info_na.csv")
print(df)
for column_name in df.columns:
  if column_name == 'API':
    continue
  if df[column_name].dtype == 'float64':
    df[column_name].fillna(df[column_name].median(), inplace=True)
  else:
    df[column_name].fillna(df[column_name].mode()[0], inplace=True)
print(df)

