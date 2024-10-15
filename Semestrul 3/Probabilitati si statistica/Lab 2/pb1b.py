#1b
def samebirthday(n):
  p=1
  for i in range(n):
    p=p*(365-i)/365
  return 1-p

if __name__ == '__main__':
  n = 23
  rez = samebirthday(n)
  print(rez)
