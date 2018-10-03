# C++ Code Notes

## Configuring GCC to Compile C++ from Visual Studio Code
* Install [MinGW-64](https://sourceforge.net/projects/mingw-w64/) (_Minimalist GNU for Windows_)
* Install the [C/C++ extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) in VS Code
* Add path to `g++.exe` to PATH in your environment variables
  * For me this file is located at: \
  `C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin`
* Create a build batch script like the one below
* Enable build-and-run with CTRL + SHIFT + B
  * Press CTRL + SHIFT + B to start a `tasks.json` file
  * Edit `tasks.json` to be like the one below
* Add include path to `c_cpp_properties.json`
  * My include path string (note escale characters) is:\
  `"C:\\Program Files (x86)\\mingw-w64\\i686-8.1.0-posix-dwarf-rt_v6-rev0\\mingw32\\lib\\gcc\\i686-w64-mingw32\\8.1.0\\include\\c++"`
### build-and-run.bat
```bat
@echo off
echo deleting old build...
del main.exe
echo building...
g++ main.cpp -o main.exe
echo launching...
main.exe
```

### tasks.json
```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "echo",
            "type": "shell",
            "command": "./build-and-run.bat",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "options": {
                "cwd": "${workspaceFolder}"
            }
        }
    ]
}
```

### main.cpp
```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, World!";
    return 0;
}
```
