import time


def fib(n):

  if n == 0:
    return 0
  elif  n == 1:
    return 1
  else:
    return fib(n-1) + fib(n-2)






for i in range(0,100,10):
  start = time.perf_counter()

  print(i, "-", fib(i))

  end = time.perf_counter()

  print(end-start)




