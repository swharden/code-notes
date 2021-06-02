# NUnit Test Notes

## Determine Test Folder
```cs
public static string DATA_FOLDER = Path.Combine(TestContext.CurrentContext.TestDirectory, "../../../data/");
```

## Asserting Exceptions

```cs
Assert.Throws<InvalidOperationException>(() => { spec.SaveImage("empty.png"); });
```
