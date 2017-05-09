# Image Library
This is a WPF based renderer which renders to an png image. 
The importnt part is it correctly implements all of the magic STA UI goo so that it can be used on a server safely. 

>NOTE: This is defined as part of the AdaptiveCards.Xaml.WPF library

## Add a renderer
This is available as a nuget packages. 
```
nuget install AdaptiveCards.Xaml.WPF
```
## Create an instance of your renderer
The next step is to create an instance of the renderer library. 
```csharp
var imageRenderer = new ImageRenderer(new HostConfig(), String.Empty);
```

## Hook up action callback
Since this is rendering to a bitmap, not interactive elements are supported.

## Render a card 
Now you get take a card and render to an image safely even from a server.

```csharp
var imageRenderer = new ImageRenderer(new HostConfig(), String.Empty);
var pngImageStream = await imageRenderer.RenderAdaptiveCardAsync(card, 480);
```

## Customization

### HostConfig 
To customize the renderer you provide an instance of the HostConfig object. (See [Host Config Schema](/documentation/#display-hostconfigschema) for the full description.)

> The HostConfig object will be instantiated with defaults, so you can set just the properties you want to change.

Example:
```csharp
var hostConfig = new HostConfig() 
{
    FontSizes = {
        Small = 15,
        Normal =20,
        Medium = 25,
        Large = 30,
        ExtraLarge= 40
    }
};
```

When you pass it in to the ImageRenderer you are setting the default HostConfig to use for every card you render.

### Changing per element rendering
The ImageRenderer is a wrapper around the XamlRenderer class from AdaptiveCards.Xaml.WPF library. If you want to customize the rendering you can get access the renderer
via the property **Rendererer**.  

You can then call register an alternate render function like this:
```csharp
imageRenderer.Renderer.SetRenderer<DateInput>(RenderMyCustomDate);
```

### UI Framework styling
If you pass in a Xaml ResourceDictionary you can further customize the Xaml behavior. This
allows you to define roll over behaviors, animations, rounded buttons, etc.  Here is a table of the 
style names that are used for each element.  

> !IMPORTANT NOTE! If you are calling from a UI thread you can initialize the ImageRenderer with a ResourceDictionary.  But if you are calling from
a server you won't be on a UI thread, and you can't instantiate a ResourceDictionary.  Since ImageRenderer manages the STA threads, you should instead
pass in a path to a .XAML file which contains the resource dictionary.  When call Render it will load the resource dictionary into the STA thread and make it all work right.

Example from UI thread:
```csharp
var imageRenderer = new ImageRenderer(new HostConfig(), myResourceDictionary);
```

Example from a server thread:
```csharp
var imageRenderer = new ImageRenderer(new HostConfig(), pathToXamlFileWithResourceDictionary);
```

Sample Xaml file which definesa round opacity mask on images of style person

```xml
<ResourceDictionary xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
                    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
                    xmlns:core="clr-namespace:System;assembly=mscorlib"
>

    <!-- Circular Person mask -->
    <RadialGradientBrush x:Key="PersonMask" GradientOrigin="0.5,0.5" Center="0.5,0.5" RadiusX="0.5" RadiusY="0.5">
        <GradientStop Color="#ffffffff" Offset="0.9" />
        <GradientStop Color="#00ffffff" Offset="1.0" />
    </RadialGradientBrush>

    <Style x:Key="Adaptive.Image.Person" TargetType="Image" >
        <Setter Property="OpacityMask" Value="{StaticResource PersonMask}"/>
    </Style>

</ResourceDictionary>
```

## Resources
* [Libraries](/documentation/#display-libraries) 
* [Implementing a renderer](/documentation/#disply-implementingrenderer) 
* [Customizing a renderer](/documentation/#display-customizingrenderer) 


