import os
import glob
with open("readme.md") as f:
    readme = f.read()
icons = glob.glob("./*.png")
icons = [os.path.basename(x) for x in icons]
for icon in icons:
    if not icon in readme:
        print("![](%s) %s\\"%(icon, icon))