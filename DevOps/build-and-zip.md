# Build and Zip

This batch script for Windows builds a .NET project and zips it using `tar.exe`

```bat
@echo off

echo.
echo ### Deleting previous builds...
rmdir /s /q -r QrssDownloader
del *.zip

echo.
echo ### Building Release...
dotnet build ..\src\ --configuration Release --output QrssDownloader

echo.
echo ### Zipping...
tar.exe -a -cf QrssDownloader.zip QrssDownloader

echo.
echo ### DONE
pause
```
