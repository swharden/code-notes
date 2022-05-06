# Minimal APIs with .NET

```cs
var builder = WebApplication.CreateBuilder(args);
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

var app = builder.Build();
app.UseSwagger();
app.UseSwaggerUI();

List<int> Numbers = new() { 1, 2, 3 };

app.MapGet("/numbers", () =>
{
    return Numbers;
})
.Produces<List<int>>();

app.MapPut("/numbers", (int number) =>
{
    Numbers.Add(number);
    return Results.Ok;
});

app.Run();
```
