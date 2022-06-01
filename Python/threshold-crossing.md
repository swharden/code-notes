# Identify Threshold Crossings with Numpy

```py
def thresholdCross(ys: np.ndarray, threshold: float) -> np.ndarray:
    """
    Return each index where the given array crosses the threshold in the positive direction.
    """
    indicesAboveThreshold = np.where(ys > threshold)[0]
    nonConsecutiveIndices = np.where(np.diff(indicesAboveThreshold) != 1)[0]+1
    nonConsecutiveIndices = np.append([0], nonConsecutiveIndices)
    return indicesAboveThreshold[nonConsecutiveIndices]
```

Although there may be a better way: https://danielmuellerkomorowska.com/2020/05/30/threshold-detection-in-numpy/
