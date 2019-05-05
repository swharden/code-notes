# Enumerations

## Creating
```C#
enum LineStyle { solid, dashed, dotted };
enum MarkerShape { circleSolid, circleOutline };
```

## Getting Names as Strings
```cs
public string[] RequestStrings()
{
    return Enum.GetNames(typeof(Request));
}
```
