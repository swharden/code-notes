## Access system time
https://www.originlab.com/doc/OriginC/ref/GetTickCount

## Timers

```c
DWORD timerStart=GetTickCount();
/* do stuff */
DWORD timerEnd=GetTickCount();
printf("Timer took: %3.3f seconds.\n",(timerEnd-timerStart)/1000.00);
```

## Seed Random Number Generator
```c
rnd(GetTickCount()); // seed the RNG
```

