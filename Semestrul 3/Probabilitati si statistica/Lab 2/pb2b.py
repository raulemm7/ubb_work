#2b
from matplotlib.pyplot import axis, plot, show
from random import random
from math import dist, pi

def funct(n=1000):
  nr_red = 0
  axis('square')
  axis((0, 1, 0, 1))
  for i in range(n):
    x = random()
    y = random()
    dist_centru = dist((0.5, 0.5), (x, y))
    if dist_centru < min(dist((x, y), (0, 0)), dist((x, y), (0, 1)),
                         dist((x, y), (1, 0)), dist((x, y), (1, 1))) :
      plot(x, y, 'r*')
      nr_red = nr_red + 1
    else:
      plot(x, y, 'b*')
  show()
  return nr_red / n

if __name__ == '__main__':
  rez = funct(6000)
  print("Frecventa relativa: " + str(rez))
  print("Probabilitatea geometrica: " + str(2/4))
