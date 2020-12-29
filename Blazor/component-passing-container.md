# Passing Data Between Blazor Components: Container Injection

One way to bidirectionally share state between components is using a singleton state manager which can trigger events. In this scheme we create a singleton in main and use dependency injection to deliver it to each of the components. The singleton contains an event which can be subscribed to so updates from any component can notify all other components of state changes (by calling the [ComponentBase.StateHasChanged Method](https://docs.microsoft.com/en-us/dotnet/api/microsoft.aspnetcore.components.componentbase.statehaschanged?view=aspnetcore-5.0) already present in all components).

### Program.cs

```cs
public static async Task Main(string[] args)
{
    var builder = WebAssemblyHostBuilder.CreateDefault(args);
    builder.RootComponents.Add<App>("app");
    builder.Services.AddScoped(sp => new HttpClient { BaseAddress = new Uri(builder.HostEnvironment.BaseAddress) });
            
    // create a singleton at the top level of the program
    builder.Services.AddSingleton<Shared.PetInventory>();

    await builder.Build().RunAsync();
}
```

### Parent

```xml
<h3>My house has @Inventory.TotalPetCount pets</h3>
<button @onclick="Inventory.BuyRandomPet">buy</button>
<button @onclick="Inventory.SellRandomPet">sell</button>

<Child Name="Bobbie" KidIndex="0" />
<Child Name="Susie" KidIndex="1" />
<Child Name="Richard" KidIndex="2" />
```

```cs
@code {
    [Inject]
    private PetInventory Inventory { get; set; }

    protected override void OnInitialized()
    {
        Inventory.OnStateChange += StateHasChanged;
    }
}
```

### Child

```xml
<div style="margin: 3em;">
    @Name has @PetCount pets
    <button @onclick="Buy">BUY</button>
    <button @onclick="Buy">SELL</button>
</div>
```

```cs
@code {

    [Parameter]
    public string Name { get; set; }

    [Parameter]
    public int KidIndex { get; set; }

    [Inject]
    protected PetInventory Inventory { get; set; }

    private int PetCount => Inventory.GetPetCountForKid(KidIndex);

    private void Buy() => Inventory.Buy(KidIndex);

    private void Sell() => Inventory.Sell(KidIndex);

    protected override void OnInitialized()
    {
        Inventory.OnStateChange += StateHasChanged;
    }
}
```