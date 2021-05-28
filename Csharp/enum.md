# Enumerations

## Creating
```C#
enum LineStyle { solid, dashed, dotted };
enum MarkerShape { circleSolid, circleOutline };
```

## Access Enum by String Name
```cs
// sleek
Enum.TryParse("dashed", out LineStyle ls);

// cast
LineStyle ls = (LineStyle)Enum.Parse(typeof(LineStyle), "dashed");
```

## Access Enum by Index
```cs
string firstLineStyle = (LineStyle)0;
string secondLineStyle = (LineStyle)1;
```

## Get an enum from its string name
```cs
enum Colors {Red, Green, Blue}
Colors color = (Colors)System.Enum.Parse(typeof(Colors), "Green");
```

## Iterate Enumerations
```cs
foreach(InterpolationMode mode in Enum.GetValues(typeof(InterpolationMode)))
{
    Console.WriteLine(mode);
}
```

## Access, Index, Loop, and Assign by Name or Index
```cs
// this is weird... don't do this

public enum Action { actionOne, actionTwo, actionThree, error };

public static Action GetActionByName(string actionName)
{
    string[] enumNames = Enum.GetNames(typeof(Action));
    for (int i = 0; i < enumNames.Length; i++)
    {
        if (actionName == enumNames[i])
            return (Action)i;
    }
    return Action.error;
}
```
