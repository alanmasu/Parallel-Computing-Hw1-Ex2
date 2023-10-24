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


print(df_serial)

# Create a scatter plot
sns.lineplot(x='b', y='time', data=df_serial, label='Serial', color='red')
sns.lineplot(x='b', y='time', data=df_prefetch, label='Prefetch', color='blue')


# Add title and axis names
plt.title('Wall time')
plt.xlabel('Block size')
plt.ylabel('Time (s)')
plt.xscale('log')
plt.xticks([4, 8, 16, 32, 64, 128, 256], ['$2^2$', '$2^3$', '$2^4$', '$2^5$', '$2^6$', '$2^7$', '$2^8$'])
plt.legend()
plt.savefig(img_filename + '.png')
plt.show()
