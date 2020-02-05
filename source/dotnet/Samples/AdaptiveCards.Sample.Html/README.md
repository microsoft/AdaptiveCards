# AdaptiveCards HTML Sample

This provides a CLI to exercise the .NET HTML Renderer (`AdaptiveCards.Rendering.Html`)

## Usage

If you cloned this repo, run the following command to generate HTML from the Scenario samples. The tool scans a directory for .json files that contain Adaptive Card payloads.

```console
Usage: dotnet run [payload-path] [options]
```

```console
$ dotnet run
```

Or output to a file 

```console
$ dotnet run -o ./scenarios.html
$ start ./scenarios.html
```


### Arguments

Name | Description
---|---
path | The path that contains JSON card payloads

### Options

Short | Long | Description
---|---|---
-h |--help | Show help information
-r |--recursive | Recurse the directory for all JSON files
-o |--out | The file to output the HTML to
-i | --supports-interactivity  | Include actions and inputs in the output
n/a | --host-config | Specify a host config file

## Example to use Windows Notification host config

```console
dotnet run ../../../../samples -r -i -o ./samples.html --host-config ../../../../samples/hostconfig/windows-notification.json
```