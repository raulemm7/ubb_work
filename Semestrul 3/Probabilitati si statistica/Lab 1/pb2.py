#problema 2
from random import sample
from math import factorial
from itertools import permutations

print(list(permutations('word', 4)))
print(factorial(len('word')))
print(sample(list(permutations('word', 4)), 1))
#sample('word', 4)
