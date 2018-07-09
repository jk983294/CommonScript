import pandas as pd
import numpy as np

tips = pd.read_csv('tips.csv', index_col='index')
print tips.head()

# SELECT total_bill, tip, smoker, time FROM tips LIMIT 5;
print tips[['total_bill', 'tip', 'smoker', 'time']].head(5)

# SELECT * FROM tips WHERE time = 'Dinner' LIMIT 5;
print tips[tips['time'] == 'Dinner'].head(5)

# SELECT * FROM tips WHERE time = 'Dinner' AND tip > 5.00;
print tips[(tips['time'] == 'Dinner') & (tips['tip'] > 5.00)]

# SELECT * FROM tips WHERE size >= 5 OR total_bill > 45;
print tips[(tips['size'] >= 5) | (tips['total_bill'] > 45)]

# SELECT sex, count(*) FROM tips GROUP BY sex;
print tips.groupby('sex').size()

# SELECT day, AVG(tip), COUNT(*) FROM tips GROUP BY day;
print tips.groupby('day').agg({'tip': np.mean, 'day': np.size})

# SELECT smoker, day, COUNT(*), AVG(tip) FROM tips GROUP BY smoker, day;
print tips.groupby(['smoker', 'day']).agg({'tip': [np.size, np.mean]})

# Top N rows with offset
# SELECT * FROM tips ORDER BY tip DESC LIMIT 10 OFFSET 5;
print tips.nlargest(10 + 5, columns='tip').tail(10)

# Top N rows per group
# SELECT * FROM ( SELECT t.*, ROW_NUMBER() OVER(PARTITION BY day ORDER BY total_bill DESC) AS rn FROM tips t )
# WHERE rn < 3 ORDER BY day, rn;
print (tips.assign(rn=tips.sort_values(['total_bill'], ascending=False).groupby(['day']).cumcount() + 1)
       .query('rn < 3').sort_values(['day', 'rn']))

# update
# UPDATE tips SET tip = tip*2 WHERE tip < 2;
print tips.loc[170, :]
tips.loc[tips['tip'] < 2, 'tip'] *= 2
print tips.loc[170, :]

# delete
# DELETE FROM tips WHERE tip > 9;
tips = tips.loc[tips['tip'] <= 9]
