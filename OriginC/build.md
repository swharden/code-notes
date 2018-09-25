## Adding C files from the command window

* https://www.originlab.com/doc/LabTalk/ref/Run-obj
* This command compiles the source file
* This command then edits `%Y/Origin.ini` to add the source file to the auto-load folder

```
run.LoadOC(OriginLab\fft_utils.c, 2048)
```