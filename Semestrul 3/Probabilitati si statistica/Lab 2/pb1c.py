#1c
from matplotlib.pyplot import plot, grid, title, show

if __name__=='__main__':
  title('Plot test')
  xs = range(2, 51)
  ys = [simulare_zi_nastere(x, 5000) for x in xs]
  plot(xs,ys,'r*')
  grid()
  show()
