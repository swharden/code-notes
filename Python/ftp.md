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
    """recursively remove the ftp target path"""
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

## Recursively Upload a Folder
jeez this is dirty but it works
```py
def uploadRecursively(ftp, localFolderPath, remoteFolderPath, overwrite=True):
    """Copy a local folder tree to a remote target path."""

    # ensure the target doesn't exist (or delete it)
    if remoteFolderPath in ftp.nlst(dirname(remoteFolderPath)):
        if overwrite:
            print()
            print("### DELETING OLD FOLDER ###")
            removeRecursively(ftp, targetFolder)
        else:
            raise Exception("target already exists")

    print()
    print("### UPLOADING ###")
    ftp.mkd(remoteFolderPath)
    for root, dirs, files in walk(localFolderPath):
        for dir in dirs:
            localPath = join(root, dir)
            remotePath = remoteFolderPath + \
                localPath.replace(localFolderPath, "").replace("\\", "/")
            print("CREATE " + remotePath)
            ftp.mkd(remotePath)
        for filename in files:
            localPath = join(root, filename)
            remotePath = remoteFolderPath + \
                localPath.replace(localFolderPath, "").replace("\\", "/")
            ftpCommand = f'STOR {remotePath}'
            print(ftpCommand)
            with open(localPath, 'rb') as localBinary:
                ftp.storbinary(ftpCommand, localBinary)
```
