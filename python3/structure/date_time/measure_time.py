import time

# measure process time
t0 = time.perf_counter()
time.sleep(2)
t1 = time.perf_counter()
print(t1 - t0, "seconds process time")

# measure wall time
t0 = time.time()
time.sleep(2)
t1 = time.time()
print(t1 - t0, "seconds wall time")
