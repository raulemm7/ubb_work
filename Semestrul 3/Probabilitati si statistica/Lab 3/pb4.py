from random import randrange
from matplotlib.pyplot import bar, hist, grid, show, legend
from scipy.stats import binom

nrSim = 2500

data = [randrange(1,7) + randrange(1, 7) + randrange(1, 7) for _ in range(nrSim)]
bin_edges = [k+0.5 for k in range(3, 19)]
hist(data, bin_edges, density = True, rwidth = 0.9, color = 'green', edgecolor = 'black',
alpha = 0.5, label = 'frecvente relative')

distribution = dict([(i, 0) for i in range(3,19)])
bar(distribution.keys(), distribution.values(), width = 0.85, color = 'red', edgecolor = 'black',
alpha= 0.6, label = 'probabilitati')

legend(loc = 'lower left')
grid()
show()
