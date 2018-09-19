# Reading ABF Files in Origin C

```c
#include <..\Originlab\pCLAMPFile.h>
```

## Read a sweep
```c
pCLAMPFile pcFile(abfFilePath);
vector <float> data;

int channel=0;
int sweep=0;
pcFile.ReadOneSweep(channel ,sweep, data);

printf("Sweep has %d values", data.GetSize());
```

## Get all data for a channel
```c
pCLAMPFile pcFile(abfFilePath);
vector <float> data;
pcFile.ReadOneChannel(0,data);
printf("Channel 0 has %d values", data.GetSize());
```

