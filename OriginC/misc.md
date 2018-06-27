## Timers

If you want to use built in timer in labtalk you can type ‘sec’ in the command window onces.  Then type ‘watch’. You can the run ‘watch’ repeatedly without typing sec each time to get time since last watch command. There is also a way to do that in C. 

Something like:
```c
DWORD dwBegin=GetTickCount();
DWORD dwEnd=GetTickCount();
printf("\n  Total RunTime: %3.2f seconds.\n",(dwEnd-dwBegin)/1000.00);
```
