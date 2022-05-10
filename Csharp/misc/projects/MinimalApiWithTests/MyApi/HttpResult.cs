namespace MyApi;

public abstract class HttpResult
{
    public System.Net.HttpStatusCode StatusCode { get; init; }
    public string? Problem { get; init; }
    public object? Data { get; init; }

    public IResult AsIResult(string? identifier = null)
    {
        return StatusCode == System.Net.HttpStatusCode.OK
            ? Results.Ok(Data)
            : Results.Problem(Problem, identifier, (int)StatusCode);
    }
}

public class HttpResultOK : HttpResult
{
    public HttpResultOK()
    {
        StatusCode = System.Net.HttpStatusCode.OK;
        Data = "OK";
    }

    public HttpResultOK(string message)
    {
        StatusCode = System.Net.HttpStatusCode.OK;
        Data = message;
    }

    public HttpResultOK(object data)
    {
        StatusCode = System.Net.HttpStatusCode.OK;
        Data = data;
    }
}

public class HttpResultBadRequest : HttpResult
{
    public HttpResultBadRequest(string problem)
    {
        StatusCode = System.Net.HttpStatusCode.BadRequest;
        Problem = problem;
    }
}

public class HttpResultServerError : HttpResult
{
    public HttpResultServerError(string problem)
    {
        StatusCode = System.Net.HttpStatusCode.InternalServerError;
        Problem = problem;
    }
}