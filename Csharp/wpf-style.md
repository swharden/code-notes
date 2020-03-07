# Using WPF Styles

Styles let you define the default styles of a component. This is useful for changing styles of many components all at one time.

```cs
<Window.Resources>
    <Style TargetType="TextBlock">
        <Setter Property="VerticalAlignment" Value="Center" />
        <Setter Property="TextWrapping" Value="Wrap" />
    </Style>
    <Style TargetType="Button">
        <Setter Property="Padding" Value="5" />
        <Setter Property="Margin" Value="5" />
    </Style>
</Window.Resources>
```
