# Load Image as an Array with Python

Lean on PIL you can acquire by installing Pillow

```bash
pip install pillow
```

```py
with Image.open("ladder.png") as im:
    data = np.array(im)
```
