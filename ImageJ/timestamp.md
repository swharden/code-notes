# ImageJ macro to timestamp frames

```java
secPerFrame = 6.5867473;
x = 2;
y = 20;
setFont("Consolas", 20);

for (i = 1; i<=nSlices; i++){

    timeSec = secPerFrame * (i - 1);
    minutes = floor(timeSec / 60);
    seconds = timeSec - (minutes * 60);
    seconds = Math.round(seconds * 100) / 100;
    seconds = String.pad(seconds, 2);
    text = ""+minutes+":"+seconds ;
    setSlice(i);

    setColor("black");
    drawString(text, x + 1, y + 1);
    setColor("white");
    drawString(text, x, y);
}
```

![image](https://user-images.githubusercontent.com/4165489/188920173-a97741dd-d611-437c-85d5-694a52e408ae.png)
