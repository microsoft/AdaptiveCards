# AdaptiveCards Image Renderer Sample

This provides a CLI to exercise the .NET WPF Renderer to render to images (`AdaptiveCards.Rendering.Wpf`)

## Usage

If you cloned this repo, run the following command to generate HTML from the Scenario samples. The tool scans a directory for .json files that contain Adaptive Card payloads.

```console
Usage: dotnet run [payload-path] [options]
```

```console
$ dotnet run
```

Or output to a specific directory

```console
$ dotnet run -o ./out
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
-o |--out | The directory to output the image(s) to
-i | --supports-interactivity  | Include actions and inputs in the output
n/a | --host-config | Specify a host config file

## Example to use Windows Notification host config

```console
dotnet run ../../../../samples -r -i -o ./out --host-config ../../../../samples/hostconfig/windows-notification.json
```