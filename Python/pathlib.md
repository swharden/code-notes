# Pathlib Notes

### Join

```py
import os
fullPath = os.path.join(basePath, filename)
```

```py
from pathlib import Path
filePath = Path(folderPath) / filename
```

### Force Forward Slashes
```py
from pathlib import Path
filePath = Path(somePath).as_posix()
```
