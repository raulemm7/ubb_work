#1a
from random import randint

def simulare_zi_nastere(n, nr_sim = 3000):
  nr_total_sim = 0
  nr_caz_fav = 0
  for i in range(nr_sim):   # nr de simulari
    lista = []
    for j in range(n):            # generez zile de nastere pt persoane
      lista.append(randint(1, 365))
    if(len(set(lista)) < n):
      nr_caz_fav = nr_caz_fav + 1
    nr_total_sim = nr_total_sim + 1

  return nr_caz_fav / nr_total_sim

if __name__ == '__main__':
  n = 23
  rez = simulare_zi_nastere(n)
  print(rez)
