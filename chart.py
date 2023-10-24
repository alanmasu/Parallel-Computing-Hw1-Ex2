#importo le librerie
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns

filename = 'resoults'
img_filename = 'resoults'

# Set the style
sns.set_style("whitegrid")
# sns.set_context("paper", font_scale=1.5, rc={"lines.linewidth": 2.5})

# Read the data
df = pd.read_csv(filename + '.csv')

print(df)

# Filter the data
df_serial = df[df['notes'] == 'whitout-vectorization-or-prefetch']
df_prefetch = df[df['notes'] == 'whit-prefetch']
df_vectorization = df[df['notes'] == 'whit-prefetch-and-vectorization']
df_only_vectorization = df[df['notes'] == 'only-vectorization']


print(df_serial)

# Create a scatter plot
sns.lineplot(x='b', y='time', data=df_serial, label='Serial', color='red')
sns.lineplot(x='b', y='time', data=df_prefetch, label='Prefetch', color='blue')
sns.lineplot(x='b', y='time', data=df_vectorization, label='PF + Vectrization', color='green')
sns.lineplot(x='b', y='time', data=df_only_vectorization, label='Vectrization', color='purple')


# Add title and axis names
plt.title('Wall time')
plt.xlabel('Block size')
plt.ylabel('Time (s)')
plt.xscale('log')
plt.legend(loc='upper left')
plt.xticks([4, 8, 16, 32, 64, 128, 256], ['$2^2$', '$2^3$', '$2^4$', '$2^5$', '$2^6$', '$2^7$', '$2^8$'])
plt.savefig(img_filename + '.png')
plt.show()
