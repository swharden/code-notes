# Resources

## For version tracking
I like to define my versions manually. Right-click on a _project_, select _properties_, go to _resources_, and add a variable "version". I like using a string such as `0.1.3`. This variable can then be accessed in code by:
```cs
string version = Properties.Resources.ResourceManager.GetString("version");
```
