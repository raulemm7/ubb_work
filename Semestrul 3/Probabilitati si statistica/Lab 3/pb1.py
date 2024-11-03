from random import choices, sample
from math import comb, perm

def calculeazaBA(nrSimulari = 5000):
  listaCulori = ["red"] * 5 + 3 * ["blue"] + 2 * ["green"]
  ab = 0
  a = 0
  for _ in range(nrSimulari):
    extragere = sample(listaCulori, 3)
    if "red" in extragere:
      a += 1
      setExtragere = set(extragere)
      if(setExtragere == {"red"}):
        ab += 1
  return ab / a

def calculeazaBAteoretic():
  p_ab = comb(5, 3) / comb(10, 3)
  p_a = 1 - comb(5, 3) / comb(10, 3)
  return p_ab / p_a

if __name__ == '__main__':
  print(calculeazaBA())
  print(calculeazaBAteoretic())
