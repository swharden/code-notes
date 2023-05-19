# Navigating 5D Stacks Programmatically

* https://imagej.nih.gov/ij/developer/macro/functions.html `Stack (hyperstack) Functions`
* https://imagej.nih.gov/ij/macros/HyperStackDemo.txt

```java
getDimensions(w, h, channels, slices, frames);

for (i=0; i<slices; i++){
	Stack.setSlice(i + 1);
	break;
}
```
