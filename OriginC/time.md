## Access system time
https://www.originlab.com/doc/OriginC/ref/GetTickCount
```c
DWORD dw1 = GetTickCount();
```

## Seed Random Number Generator
```c
rnd(GetTickCount()); // seed the RNG
```

## Timers

```c
// something like
DWORD dwBegin=GetTickCount();
DWORD dwEnd=GetTickCount();
printf("\n  Total RunTime: %3.2f seconds.\n",(dwEnd-dwBegin)/1000.00);
```
