#problema 4
from itertools import combinations_with_replacement

lista = list(combinations_with_replacement('ABCDE', 4))
for li in lista:
  print("".join(li))
