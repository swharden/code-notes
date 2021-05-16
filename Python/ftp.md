# FTP

* https://docs.python.org/3/library/ftplib.html

## SFTP

Use `FTP_TLS` and the `ftplib` module for secure authentication.

```py
from ftplib import FTP_TLS
from pathlib import Path

with FTP_TLS(hostname, username, password) as ftp:
    ftp.set_debuglevel(1)
    folderPath = ftp.pwd()
    for filename in ftp.nlst():
        filePath = Path(folderPath) / filename
        print(filePath.as_posix())
```

## Recursively Delete a Folder
```py
def removeRecursively(ftp, path):
    for (name, properties) in ftp.mlsd(path=path):
        if name in ['.', '..']:
            continue
        elif properties['type'] == 'file':
            filePath = f"{path}/{name}"
            print(f"DELETING {filePath}")
            ftp.delete(filePath)
        elif properties['type'] == 'dir':
            removeRecursively(ftp, f"{path}/{name}")

    print(f"DELETING {path}/")
    ftp.rmd(path)
```
