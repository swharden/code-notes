# File/Folder Path Operations

https://www.originlab.com/doc/OriginC/ref/File-Management-GlobalFunction

many of those functions don't work with forward slashes!

```c
string somePath = GetFullPath(somePartialPath);
string fname = GetFilenameWithoutExt(somePath);
```
