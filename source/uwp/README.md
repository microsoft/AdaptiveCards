

# Adaptive Cards in UWP

This directory contains the renderers and tooling for the UWP platform. 

## Requirements

1. Visual Studio 2017 with C++ tooling

## Why C++?

Since Adaptive Cards are hosted directly within the Windows OS we had implementation requirements to use strictly unmanaged code. 

## How to test

To run the test project, see the [AdaptiveCardTestApp](AdaptiveCardTestApp/README.md) folder

## How to add a new NuGet package

Due to limitations in our build system and Test infrastructure libraries used for UI tests, the process to add new NuGet packages has changed. The new process requires us to push any NuGet packages to a new NuGet feed called `AdaptiveCards-public` where we can have packages that come from any number of sources.

### Adding / Updating a new NuGet package locally

To add or update a NuGet package locally you have to add `nuget.org` as a NuGet package source:

1. Add the following line to the NuGet.config file located under `AdaptiveCards/source/`: 

``` <add key="nuget.org" value="https://api.nuget.org/v3/index.json" protocolVersion="3" /> ```

2. Restart Visual Studio to load the changes

### Pushing the NuGet package to the AdaptiveCards-public feed

Once the new package has been tested locally and is ready to be merged:

1. If you already have NuGet, you can skip to step 3, otherwise download the [lastest NuGet version](https://www.nuget.org/downloads)
2. [Optional] Add the nuget.exe location to the PATH environment variable
3. Open Visual Studio and start a Package Manager Console (Tools -> NuGet Package Manager -> Package Manager Console)
4. Manually push any nuget packages you added by typing the following into the Package manager console. You must do this from a directory under AdaptiveCards2\source, the location of Nuget.config:

``` nuget.exe push -Source "AdaptiveCards-Public" -ApiKey az <PackagePath\PackageName.nupkg> -SkipDuplicate```

> * You may be prompted to login before pushing any NuGet packages into the public feed
>
> * Downloaded NuGet packages are usually located at `C:\Users\<UserName>\.nuget\packages`

### Troubleshooting:

If you see the following, you may be trying to run nuget.exe from a path not under AdaptiveCards\source:

>c:\nuget.exe : The specified source 'AdaptiveCards-Public' is invalid. Provide a valid source.
>
>At line:1 char:1
>
>c:\nuget.exe push -Source "AdaptiveCards-Public" -ApiKey az C:\Users\ ...
>
>     CategoryInfo          : NotSpecified: (A task was canceled.:String) [], RemoteException
>     FullyQualifiedErrorId : NativeCommandError
>

If you see the following error, you may not have permissions to push to "AdaptiveCards-Public" 

>   [CredentialProvider]VstsCredentialProvider - Acquired bearer token using 'ADAL Device Code'
    [CredentialProvider]VstsCredentialProvider - Attempting to exchange the bearer token for an Azure DevOps session token.
Please provide credentials for: https://pkgs.dev.azure.com/ms/AdaptiveCards/_packaging/AdaptiveCards-Public/nuget/v3/index.json
UserName: An error was encountered when fetching 'PUT https://pkgs.dev.azure.com/ms/2045544b-a6e3-4bb5-b011-e5c8612f1b74/_packaging/e500b8f1-3593-4d2b-af62-bf7f3d4c9ef1/nuget/v2/'. The request will now be retried.
>
>The HTTP request to 'PUT https://pkgs.dev.azure.com/ms/2045544b-a6e3-4bb5-b011-e5c8612f1b74/_packaging/e500b8f1-3593-4d2b-af62-bf7f3d4c9ef1/nuget/v2/' has timed out after 300000ms.
>
>c:\nuget.exe : A task was canceled.
>
>At line:1 char:1
>
> c:\nuget.exe push -Source "AdaptiveCards-Public" -ApiKey az C:\Users\ ...
>
>     CategoryInfo          : NotSpecified: (A task was canceled.:String) [], RemoteException
>     FullyQualifiedErrorId : NativeCommandError
> 
>  Pushing took too long. You can change the default timeout of 300 seconds by using the -Timeout <seconds> option with the push command.