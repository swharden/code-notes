# Enumerations

## Creating
```C#
enum LineStyle { solid, dashed, dotted };
enum MarkerShape { circleSolid, circleOutline };
```

## Access, Index, Loop, and Assign by Name or Index
```cs
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
