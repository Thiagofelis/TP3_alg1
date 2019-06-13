import csv
import numpy as np
import Tkinter
import sys
import matplotlib.pyplot as plt
from scipy import stats

with open('saidas_t1.csv') as file:
	data1 = [row for row in csv.reader(file)]
with open('saidas_t2.csv') as file:
	data2 = [row for row in csv.reader(file)]

#with open('saidas_t2.csv') as file:
#	saida = [row for row in csv.reader(file)]

num_points = int(sys.argv[1])
num_it = int(sys.argv[2])
scaler = int(sys.argv[3])

out = open('graficos e dados/otimidade_t2.csv', 'w')

vec = np.zeros((num_points, num_it))
vec2 = np.zeros((num_points, num_it))

values = np.zeros(num_points)
stdev = np.zeros(num_points)

for i in range(num_points):
	for j in range(num_it):
		vec[i][j] = int(data1[i][j])
		vec2[i][j] = int(data2[i][j])
	values[i] = (vec2[i]/vec[i]).mean()
	out.write(str(values[i]) + '\n')


t = scaler * np.arange(0, num_points, 1) + scaler

plt.plot(t, values, '.')

plt.title("Tamanha normalizado da cobertura x Numero de vertices")
plt.xlabel("Numero de vertices")
plt.ylabel("Tamanha normalizado da cobertura")
plt.grid()
plt.savefig('graficos e dados/otimidade_t2.pdf')
plt.clf()
