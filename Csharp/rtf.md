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
rtbConsole.Clear();
string rtfBody = @"{\rtf1\ansi\deff0}";
rtfBody = rtfBody.Insert(rtfBody.Length - 1, @"{\fonttbl{\f0\fnil\fcharset0 Calibri;}}");
rtfBody = rtfBody.Insert(rtfBody.Length - 1, @"{\colortbl ;\red255\green255\blue0;\red0\green150\blue0;}");
rtbConsole.Rtf = rtfBody;
```

```cs
rtbConsole.SelectedRtf = @"{\rtf1\ansi Adding some {\b bold text} as a new line...\line}";
```
