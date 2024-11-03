from random import randrange
from matplotlib.pyplot import bar, hist, grid, show, legend
from scipy.stats import binom

def subpct_a():
  nrSimulari = 1000
  n = 5
  p = 0.6
  x = binom.rvs(n, p, size = nrSimulari)
  print(x)

def subpct_b():
  nrSimulari = 1000
  n = 5
  p = 0.6
  x = binom.rvs(n, p, size = nrSimulari)

  data = x
  bin_edges = [k+0.5 for k in range(-1, 6)]
  hist(x, bin_edges, density = True, rwidth = 0.9, color = 'green', edgecolor = 'black',
  alpha = 0.5, label = 'frecvente relative')

  distribution = dict([(i,binom.pmf(i, n, p)) for i in range(1,5)])
  bar(distribution.keys(), distribution.values(), width = 0.85, color = 'red', edgecolor = 'black',
  alpha= 0.6, label = 'probabilitati')

  legend(loc = 'upper left')
  grid()
  show()

if __name__=='__main__':
  subpct_a()
  subpct_b()
