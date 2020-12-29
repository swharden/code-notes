# Passing Data Between Blazor Components: Callbacks

Callbacks allow one-way communication from a child to a parent.

In this scheme the parent has a function it wants called any time a child has updated data. We can create this function in the parent, pass it into the child, and the child will invoke it when it wants. The child can also send data as an argument.

## Parent

```xml
<h3>My house has @TotalPetCount pets</h3>
<Child Name="Bobbie" OnPetChange="UpdatePetCount" />
<Child Name="Susie" OnPetChange="UpdatePetCount"/>
<Child Name="Richard" OnPetChange="UpdatePetCount"/>
```

```cs
@code {
    public int TotalPetCount = 0;

    public void UpdatePetCount(int change) => TotalPetCount += change;
}
```

## Child

```xml```
<div style="margin: 3em;">
    @Name has @PetCount pets
    <button @onclick="Buy">buy</button>
    <button @onclick="Sell">sell</button>
</div>
```

```cs
@code {

    [Parameter]
    public string Name { get; set; } = "?";

    [Parameter]
    public EventCallback<int> OnPetChange { get; set; }

    public int PetCount { get; set; } = 0;

    private void Sell()
    {
        PetCount -= 1;
        OnPetChange.InvokeAsync(-1);
    }
    private void Buy()
    {
        PetCount += 1;
        OnPetChange.InvokeAsync(+1);
    }
}
```