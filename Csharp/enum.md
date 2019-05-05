# Enumerations

## Creating
```C#
enum LineStyle { solid, dashed, dotted };
enum MarkerShape { circleSolid, circleOutline };
```

## Access by String Name
```cs
LineStyle ls;
Enum.TryParse("dashed", true, out ls);
```

## Access by Index
```cs
string firstLineStyle = (LineStyle)0;
string secondLineStyle = (LineStyle)1;
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
