# Vectors

## Copy-Paste-Ready Functions
```c
void VectorFillAscending(vector<double>& data){
    // given a vector, fill it with ascending numbers
    for (int i=0; i<data.GetSize(); i++){
    	data[i] = i;
    }
}
```

```c
void VectorDisplay(vector<double> data){
    // display every element in a vector to the console
    for (int i=0; i<data.GetSize(); i++){
    	printf("[%d]: %f\n", i, data[i]);
    }
}
```
