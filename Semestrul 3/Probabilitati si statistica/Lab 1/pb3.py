#problema 3
from random import sample
from math import perm, comb
from itertools import permutations, combinations

def aranjamente(cuv, nr_lit, nr_total=False, aleator=False):
  if nr_total==False and aleator==False:
    return list(permutations(cuv, nr_lit))
  elif nr_total:
    return len(list(permutations(cuv, nr_lit)))
  elif aleator:
    return sample(cuv, nr_lit)

def combinari(cuv, nr_lit, nr_total=False, aleator=False):
  if nr_total==False and aleator==False:
    return list(combinations(cuv, nr_lit))
  elif nr_total==True:
    return comb(len(cuv), nr_lit)
  elif aleator==True:
    return sample(list(combinations(cuv, nr_lit)), 1)

if __name__=='__main__':
  print(aranjamente('word', 2))
  print(aranjamente('word', 2, nr_total=True))
  print(aranjamente('word', 2, aleator=True))

  print(combinari('word', 2))
  print(combinari('word', 2, nr_total=True))
  print(combinari('word', 2, aleator=True))
