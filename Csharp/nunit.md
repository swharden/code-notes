# NUnit Test Notes

```cs
namespace NUnit.Tests
{
  using System;
  using NUnit.Framework;

  [TestFixture]
  public class SuccessTests
  {
    [OneTimeSetUp]
    public void Init()
    { /* ... */ }

    [OneTimeTearDown]
    public void Cleanup()
    { /* ... */ }

    [Test]
    public void Add()
    { /* ... */ }
  }
}
```

## Determine Test Folder
```cs
public static string DATA_FOLDER = Path.Combine(TestContext.CurrentContext.TestDirectory, "../../../data/");
```

## Asserting Exceptions

```cs
Assert.Throws<InvalidOperationException>(() => { spec.SaveImage("empty.png"); });
```
