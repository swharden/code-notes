# File/Folder Path Operations

https://www.originlab.com/doc/OriginC/ref/File-Management-GlobalFunction

many of those functions don't work with forward slashes!

```c
string somePath = GetFullPath(somePartialPath);
string fname = GetFilenameWithoutExt(somePath);
```

## Basename & Dirname Functions
```c
string basename(string path){
  // return the basename of the given path (folder or file)
  path.TrimRight('\\');
  StringArray pathParts;
  path.GetTokens(pathParts, '\\');
  return pathParts[pathParts.GetSize()-1];
}
```

```c
string dirname(string path){
  // return the path to the folder containing the path
  StringArray pathParts;
  path.TrimRight('\\');
  path.GetTokens(pathParts, '\\');
  path="";
  for (int i=0; i<pathParts.GetSize()-1; i++)
    path+=pathParts[i]+"\\";
  return path;
}
```
