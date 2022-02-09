# FFmpeg Notes

* https://www.ffmpeg.org/download.html

## Speed-Up Video
```
ffmpeg -i input.mkv -vcodec h264 -vf "setpts=PTS/10" -an output.mp4
```

The `-an` means no audio (otherwise it would be original-speed audio)

## Add timecode to video
```
ffmpeg -i input.mkv -vcodec h264 -vf "drawtext=timecode='00\:00\:00\:00':r=30:x=(w-tw)/2:y=0:fontcolor=white:fontsize=(h/15):box=1:boxcolor=0x00000099" output.mp4
```
