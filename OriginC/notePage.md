# Notes

* https://www.originlab.com/doc/OriginC/ref/Note
* https://www.originlab.com/doc/OriginC/ref/Note-Note

## Create a new Notes page
```c
Note note;
note.Create();
note.SetLongName("this note is too cool for you", true, true);
note.TitleShow = WIN_TITLE_SHOW_BOTH;  
note.Text = "are you noting this?";
```
