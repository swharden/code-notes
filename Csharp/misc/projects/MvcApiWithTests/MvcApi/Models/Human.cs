namespace MvcApi.Models;

public class Human
{
    public string Name { get; init; } = string.Empty;
    public string? FavoriteColor { get; init; }
    public DateTime? Birthday { get; init; }
}