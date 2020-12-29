# Passing Data Between Blazor Components: Cascading Value

Cascading allows a parent component to set a value in all child components, and the value in children is updated when it's updated in the parent.

Children _can_ modify the value locally, but the next time it's changed by the parent it will get replaced.

## Parent

```xml
<h3>My house has @TotalPetCount pets</h3>
<button @onclick="Buy">buy</button>
<button @onclick="Sell">sell</button>

<CascadingValue Value="@TotalPetCount">
    <Child Name="Bobbie" />
    <Child Name="Susie" />
    <Child Name="Richard" />
</CascadingValue>
```

```cs
@code {
    public int TotalPetCount = 0;
    private void Sell() => TotalPetCount -= 1;
    private void Buy() => TotalPetCount += 1;
}
```

## Child

```xml
```

```cs
<div style="margin: 3em;">
    @Name lives in a home with @TotalPetCount pets 
</div>

@code {

    [Parameter]
    public string Name { get; set; } = "?";

    [CascadingParameter] 
    int TotalPetCount { get; set; }
}
```