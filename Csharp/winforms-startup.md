This code demonstrates how to start a slow action at startup without delaying appearance of the Form

```cs
  public Form1()
  {
      InitializeComponent();
      Shown += (s, e) =>
      {
          Application.DoEvents();
          DoSlowThing();
      };
  }
```
