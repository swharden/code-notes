# Command Line Parsing

* https://www.nuget.org/packages/CommandLineParser/
* `NuGet Install CommandLineParser`

```cs
﻿using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.Text;
using CommandLine;

public class CommandLineOptions
{
    [Option(longName: "scanFolder", Required = true, HelpText = "Root folder to scan for ABFs")]
    public string ScanFolder { get; set; }

    [Option(longName: "saveAs", Required = true, HelpText = "JSON file path")]
    public string SaveAs { get; set; }
}

static void Main(string[] args)
{
    CommandLine.Parser.Default.ParseArguments<CommandLineOptions>(args)
      .WithParsed(RunOptions)
      .WithNotParsed(HandleParseError);
}

static void RunOptions(CommandLineOptions opts)
{
    var rd = new RigDays(opts.ScanFolder);
    rd.SaveJson(opts.SaveAs);
}

static void HandleParseError(IEnumerable<Error> errs)
{
    foreach (var err in errs)
        Console.WriteLine(err);
}
```
