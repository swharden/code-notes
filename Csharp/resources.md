# Resources in C#

Resources let you configure a project to include variables or files which are accessible from compiled code at run-time.

```cs
var myThing = Properties.Resources.TheThing;
```

```cs
// If you include a text file, this is how you convert it to a string
var mdTableBytes = Properties.Resources.IonTable;
string mdTable = System.Text.Encoding.Default.GetString(mdTableBytes);
```
