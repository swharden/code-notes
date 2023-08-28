# Matplotlib notes

## Modern Subplots

Stop creating subplots like you're in 2007 😬

```py
import numpy as np
import matplotlib.pyplot as plt

xs = np.linspace(0, 20, 100)
ys = np.sin(xs)

fig, (ax1, ax2) = plt.subplots(2, 1)
ax1.plot(xs, ys, '-')
ax2.plot(xs, ys, '.')

fig.suptitle('multiple plots')
plt.tight_layout()
plt.show()
```

* https://matplotlib.org/stable/gallery/subplots_axes_and_figures/subplots_demo.html

## Get a color from a colormap

```py
cmap = matplotlib.cm.get_cmap('Spectral')
myColor = cmap(.5)
```

* [matplotlib colormaps](https://matplotlib.org/stable/tutorials/colors/colormaps.html)

## Remove Frame and Ticks

```py
def remove_frame(ax: matplotlib.axes._axes.Axes):
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.spines['bottom'].set_visible(False)
    ax.spines['left'].set_visible(False)
    ax.get_xaxis().set_ticks([])
    ax.get_yaxis().set_ticks([])
```

## Error Bars with Markers
```py
plt.errorbar(times, means, yerr=errs, capsize=3, fmt='o-')
```
