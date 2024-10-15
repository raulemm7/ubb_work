#1c
from matplotlib.pyplot import plot, grid, title, show

if __name__=='__main__':
  title('Plot test')
  xs = range(2, 51)
  ys = [samebirthday(x) for x in xs]
  plot(xs,ys,'r*')
  grid()
  show()
