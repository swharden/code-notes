# Random numbers

## Generate Random Numbers
https://www.originlab.com/doc/OriginC/ref/rnd
```c
// rnd() generates a random double between 0 and 1
printf("%f", rnd());
```

## Seed Random Number Generator
```c
rnd(GetTickCount()); // seed the RNG
```

## Generate Uniform Random Numbers
https://www.originlab.com/doc/OriginC/ref/Random-Number-Generators
```c
// create 1000 random numbers from -100 to 100
int sampleCount = 1000;
vector<double> fullSample(sampleCount);
unifrnd(fullSample, fullSample.GetSize(), -100, 100);    
```

## Generate Poisson Random Numbers
https://www.originlab.com/doc/OriginC/ref/poissrnd#Examples
```c
int n = 10;
long v[10];
double lamda=20.0;
int nRet = poissrnd(v, n, lamda);
```
