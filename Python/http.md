# HTTP

## Download a text file

```python
import urllib.request
text = urllib.request.urlopen(url).read().decode("utf-8")
```
