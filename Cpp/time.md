# Time
```cpp
#include <ctime>
double timeElapsedSec = (clock() - clockStart) / CLOCKS_PER_SEC;
```

## Benchmarking
```cpp
#include <ctime>
std::clock_t BenchmarkTimer(std::clock_t clockStart = 0, bool display = true){
	if (clockStart == 0){
		return clock();
	} else {
		double timeElapsedSec = (clock() - clockStart) / CLOCKS_PER_SEC;
		if (display)
			printf("%f sec\n", timeElapsedSec);
		return timeElapsedSec;
	}
}
```

```cpp
int main()
{
    auto timer = BenchmarkTimer();
    Sleep(1000);
    BenchmarkTimer(timer);
    return 0;
}
```
