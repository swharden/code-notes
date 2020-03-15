# Execute command and get output in C#

```cs
ProcessStartInfo processInfo = new ProcessStartInfo("cmd.exe", "/c " + command) { UseShellExecute = false, };
Process process = Process.Start(processInfo);
process.WaitForExit();
if (process.ExitCode != 0)
    throw new OperationCanceledException($"ERROR: exit code {process.ExitCode}");
process.Close();
```

```cs
static void ExecuteCommand(string command)
{
    int exitCode;
    ProcessStartInfo processInfo;
    Process process;

    processInfo = new ProcessStartInfo("cmd.exe", "/c " + command);
    processInfo.CreateNoWindow = true;
    processInfo.UseShellExecute = false;
    processInfo.RedirectStandardError = true;
    processInfo.RedirectStandardOutput = true;

    process = Process.Start(processInfo);
    process.WaitForExit();

    string output = process.StandardOutput.ReadToEnd();
    string error = process.StandardError.ReadToEnd();

    exitCode = process.ExitCode;

    Console.WriteLine("output>>" + (String.IsNullOrEmpty(output) ? "(none)" : output));
    Console.WriteLine("error>>" + (String.IsNullOrEmpty(error) ? "(none)" : error));
    Console.WriteLine("ExitCode: " + exitCode.ToString(), "ExecuteCommand");
    process.Close();
}
```
