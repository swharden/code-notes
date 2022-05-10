namespace MyApi;

public static class Program
{
    public static void Main(string[] args)
    {
        var builder = WebApplication.CreateBuilder(args);
        builder.Services.AddEndpointsApiExplorer();
        builder.Services.AddSwaggerGen();

        var app = builder.Build();
        app.UseSwagger();
        app.UseSwaggerUI();

        app.MapGet("/humans", (string filePath) => Humans.Get(filePath).AsIResult())
            .Produces<Human[]>()
            .Produces((int)System.Net.HttpStatusCode.BadRequest)
            .Produces((int)System.Net.HttpStatusCode.OK);

        app.MapPut("/humans", (string filePath, Human human) => Humans.Put(filePath, human).AsIResult())
            .Produces((int)System.Net.HttpStatusCode.BadRequest)
            .Produces((int)System.Net.HttpStatusCode.OK);

        app.Run();
    }
}