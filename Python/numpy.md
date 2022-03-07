# Numpy Cheat Sheet

Things I commonly forget how to do using Numpy and Scipy

## Index of Minimum Value

```py
import numpy as np
import matplotlib.pyplot as plt

np.random.seed(0)
ys = np.random.random_sample(20)
xs = np.arange(len(ys))
plt.plot(xs, ys, '.-')

minIndex = np.argmin(ys)
minX = xs[minIndex]
minY = ys[minIndex]
plt.plot(minX, minY, 'r.', ms=20, mew=3, mfc='none')

plt.show()
```

![min](https://user-images.githubusercontent.com/4165489/157109319-ae68be8d-0b84-4786-a9f0-4b10c3b21daa.png)
