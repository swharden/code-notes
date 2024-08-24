# FFmpeg Notes

* https://www.ffmpeg.org/download.html

## Speed-Up Video
```sh
ffmpeg -i input.mkv -vcodec h264 -vf "setpts=PTS/10" -an output.mp4
```

```sh
set filename=2022-02-18 12-06-15.mkv
ffmpeg -i "%filename%" -vcodec h264 -vf "setpts=PTS/30" -an "%filename%-fast.mp4"
```

The `-an` means no audio (otherwise it would be original-speed audio)

## Add timecode to video
```sh
ffmpeg -i input.mkv -vcodec h264 -vf "drawtext=timecode='00\:00\:00\:00':r=30:x=(w-tw)/2:y=0:fontcolor=white:fontsize=(h/15):box=1:boxcolor=0x00000099" output.mp4
```

## Images to Video (MP4 supported by HTML5)

```
ffmpeg.exe -framerate 10 -y -i "./video2/video%%04d.bmp" -c:v libx264 -pix_fmt yuv420p "video.mp4"
```

## Jamie Taylor Podcast WAV to FLAC
```
ffmpeg -i  input.wav -ar 44100 -ac 1 -sample_fmt s16 -vn output.flac
```
