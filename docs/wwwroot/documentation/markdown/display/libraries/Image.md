# Image library
This is a WPF-based renderer which renders to an png image. 
The important part is that it correctly implements all of the magic STA UI goo so that it can be used on a server safely. 

> [!NOTE]
> This is defined as part of the AdaptiveCards.Xaml.WPF library

## Add a renderer
This is available as a nuget packages. 
```csharp
nuget install AdaptiveCards.Xaml.WPF
```
## Create an instance of your renderer
Create an instance of the renderer library. 
```csharp
var imageRenderer = new ImageRenderer(new HostConfig(), String.Empty);
```

## Hook up action callback
Since this is rendering to a bitmap, no interactive elements are supported.

## Render a card 
Acquire a card from a source and render it into an image safely, even from a server.

```csharp
var imageRenderer = new ImageRenderer(new HostConfig(), String.Empty);
var pngImageStream = await imageRenderer.RenderAdaptiveCardAsync(card, 480);
```

## Customization

### HostConfig 
To customize the renderer, provide an instance of the HostConfig object. See the [Host Config Schema](../HostConfigSchema.md) for a full description. Since the HostConfig object is instantiated with defaults, you only have to set the properties you want to change from the defaults.
Passing it to the renderer sets the default HostConfig to use for every card you render.

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

### Change per element rendering
The ImageRenderer is a wrapper around the XamlRenderer class from AdaptiveCards.Xaml.WPF library. 

If you want to customize the rendering, get access the renderer via the property **Renderer** and then call an alternate render function like this:
```csharp
imageRenderer.Renderer.SetRenderer<DateInput>(RenderMyCustomDate);
```

### UI Framework styling
If you pass in a Xaml ResourceDictionary, you can customize the Xaml behavior further. This
allows you to define roll over behaviors, animations, rounded buttons, and so forrth.  Here is a table of the 
style names that are used for each element.  

> [!IMPORTANT]
> If you are calling from a UI thread you can initialize the `ImageRenderer` with a `ResourceDictionary`.  **But** if you are calling from
> a server, you won't be on a UI thread, so you can't instantiate a `ResourceDictionary`.  Since `ImageRenderer` manages the STA threads, 
> you should pass in a path to a .XAML file which contains the resource dictionary instead.  When Render is called it will load the
> resource dictionary into the STA thread and make it all work correctly.

Example from UI thread:
```csharp
var imageRenderer = new ImageRenderer(new HostConfig(), myResourceDictionary);
```

Example from a server thread:
```csharp
var imageRenderer = new ImageRenderer(new HostConfig(), pathToXamlFileWithResourceDictionary);
```

Sample Xaml file which defines a round opacity mask on images of style "person".

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
## Next steps

* [Implement a renderer](../ImplementingRenderer.md) 
* <a href="/docs/wwwroot/documentation/markdown/display/libraries">Other libraries</a>



