# Reading ABF Files in Origin C

```c
#include <..\Originlab\pCLAMPFile.h>
```

```c
pCLAMPFile pcFile(abfFilePath);
vector <float> data;
pcFile.ReadOneChannel(0,data);
printf("Channel 0 has %d values", data.GetSize());
```
