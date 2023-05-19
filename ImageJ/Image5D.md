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

```java
// Delete the highlighted area at this Z level from every frame

getDimensions(w, h, channels, slices, frames);

for (frame=1; frame<=frames; frame++){
	Stack.setFrame(frame);
	for (channel=1; channel<=channels; channel++){
		Stack.setChannel(channel);
		run("Cut");
	}
}
```
