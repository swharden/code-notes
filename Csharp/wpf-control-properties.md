# WPF Control Properties

## Set Values with XAML

```xaml
<MyThing Text="testing 123" />
```

```cs
public string Text
{
    get => MainLabel.Content.ToString()!;
    set => MainLabel.Content = value;
}
```

## Configure Actions with XAML

```xaml
<MyThing Click="MyThing_Click" />
```

```cs
private void MyThing_Click(object sender, RoutedEventArgs e) { /* ... */ }
```

```cs
public static readonly RoutedEvent ClickEvent = EventManager.RegisterRoutedEvent("Click", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(MyThing));

public event RoutedEventHandler Click
{
    add => AddHandler(ClickEvent, value);
    remove => RemoveHandler(ClickEvent, value);
}
```

```cs
RaiseEvent(new RoutedEventArgs(ClickEvent));
```
