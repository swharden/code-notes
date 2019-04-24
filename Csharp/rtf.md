# Rich Text Format (RTF) in the RichTextBox control

### Sample RTF
```rtf
{\rtf1\ansi\deff0
{\fonttbl{\f0\fnil\fcharset0 Calibri;}}
{\colortbl ;\red255\green255\blue0;\red0\green150\blue0;}
Let's start with a {\highlight1 highlighted} word.\line
Maybe we will get {\b bold} with it?\line
This is {\ul very} important you know...\line
I'm {\cf2 green} with envy!\line
This is a {\fs60 big} deal.
}
```

### RichTextBox RTF Tester
Download: [RTF RichTextBox tester.exe](rtf%20RichTextBox%20tester.exe)
![](rtf%20RichTextBox%20tester.png)

### RTF in a RichTextBox
```cs
// prepare the RichTextBox with a header (and colors) to accept RTF text
rtbConsole.Clear();
rtbConsole.Rtf = @"{\rtf1\ansi\deff0{\colortbl ;\red255\green255\blue0;\red0\green150\blue0;}}";
string message = "this is a {\b bold} example";

// appending text
rtbConsole.SelectedRtf = "{\\rtf1\\ansi "+ message.Replace("\n", "\\line") + "}";
```
