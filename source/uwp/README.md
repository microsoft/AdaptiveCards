# Adaptive Cards in UWP

This directory contains the renderers and tooling for the UWP platform. 

## Requirements

1. Visual Studio 2017 with C++ tooling

## Why C++?

Since Adaptive Cards are hosted directly within the Windows OS we had implementation requirements to use strictly unmanaged code. 

## How to test

To run the test project, see the [AdaptiveCardTestApp](AdaptiveCardTestApp/README.md) folder

## Testing

The UWP Renderer currently supports the following type of testing:

| Type | Project | Location |
| --- | --- | --- |
| Unit tests | UWPUnitTests | [Location](./UWPUnitTests) |
| UI tests | UWPUITests | [Location](./UWPUITests) |