# Icons

## System Icons
http://csharphelper.com/blog/2015/09/display-the-predefined-system-icons-in-c/

```cs
ImageList images = new ImageList();
images.Images.Add(new Icon(System.Drawing.SystemIcons.Application, new Size(16, 16)));
images.Images.Add(new Icon(System.Drawing.SystemIcons.Information, new Size(16, 16)));
treeViewDir.ImageList = images;
```

## Visual Studio Image Library
The Visual Studio Image Library contains application images that appear in Microsoft Visual Studio, Microsoft Windows, the Office system and other Microsoft software. The libraries for Visual Studio 2012, Visual Studio 2013, Visual Studio 2015, and Visual Studio 2017 are available and each library contains over thousands of images which can be used to create applications that look visually consistent with Microsoft software. 

### View PDF:
https://github.com/swharden/code-notes/raw/master/Csharp/misc/Visual%20Studio%20Image%20Library%202017.pdf

### Download:
https://www.microsoft.com/en-us/download/details.aspx?id=35825
