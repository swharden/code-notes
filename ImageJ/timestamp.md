# ImageJ macro to timestamp frames

## Basic Timestamp

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

## Fancy Timestamp

```java
// Draw the time on every frame of a time series stack.
// To make a video file that plays in the browser, save as a BMP sequence then:
// ffmpeg.exe -framerate 10 -y -i "./video%%04d.bmp" -c:v libx264 -pix_fmt yuv420p "video.mp4"

// SETTINGS ///////////////////////////////////////////////
framesPerSecond = 1.53;
fontSize=12;
blackBehindText = false;
///////////////////////////////////////////////////////////

run("RGB Color");
getDimensions(width, height, channels, slices, frames);
for (i=0;i<nSlices;i++){
	setSlice(i+1);
	framePeriodSec = 1.0/framesPerSecond;
	frameTimeSeconds=framePeriodSec*i;
	frameTimeMinutes=frameTimeSeconds/60;
	
	showTimeAsMinutesOnly = false;
	if (showTimeAsMinutesOnly){
		// f1234 | 123.45 min
		frameTimeMsg=round(100*frameTimeMinutes)/100;
		frameTimeMsgWhole=IJ.pad(frameTimeMsg,3);
		frameTimeMsgFrac=IJ.pad(100*(frameTimeMsg-frameTimeMsgWhole),2);
		msg="f"+IJ.pad(i+1,4)+" | "+frameTimeMsgWhole+"."+frameTimeMsgFrac+" min";
	} else {
		// f1234 1:23
		frameTime=IJ.pad(framePeriodSec*i/60,2)+":"+IJ.pad(i%60,2)+'.'+IJ.pad(100*((framePeriodSec*i)%1),2);	
		msg="frame "+IJ.pad(i+1,4)+" "+frameTime;
	}

	// add custom messages for certain frame ranges (useful for annotating drugs)
	if (i>=100 && i<=150){
		msg=msg+" STIM";
	}

	// draw a black rectangle behind the text
	if (blackBehindText){
		makeRectangle(0, 0, width, fontSize * 3 / 2); 
		setForegroundColor(0, 0, 0); 
		run("Fill", "slice");	
	}

	msgX = fontSize/2;
	msgY = fontSize*3/2;
	
	// draw black background shadow
	setFont("Monospaced",fontSize,"bold");
	setForegroundColor(0, 0, 0);
	drawString(msg,msgX+1,msgY+1);
	
	// draw yellow foreground
	setForegroundColor(255, 255, 0);
	drawString(msg,msgX,msgY);
}
```

![image](https://user-images.githubusercontent.com/4165489/225075625-481cd069-3609-49e5-9963-9782d106e6b4.png)
