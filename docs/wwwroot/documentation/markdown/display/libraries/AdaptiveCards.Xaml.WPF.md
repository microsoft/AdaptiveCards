# AdaptiveCards.Xaml.WPF Library
This is a WPF Xaml renderer which has no additional dependencies outside of standard windows components.  
Because of this, it does not support Date and Time controls aas rich controls, but falls back to plain textbox.

## Add a renderer
This is available as a nuget packages. 
```
nuget install AdaptiveCards.Xaml.WPF
```
## Create an instance of your renderer
The next step is to create an instance of the renderer library. 
```csharp
var renderer = new XamlRenderer(hostConfig, this.Resources, onAction, OnMissingInput);
```

## Hook up action callback
To hook up action events you pass in a callback when you instantiate your renderer
```csharp
var hostConfig = new HostConfig() { ... };
var renderer = new XamlRenderer(..., actionCallback:  _onAction);
```

## Render a card
Now you get a card from some source and you want to render it.  This is super easy:

```csharp
var uiCard = renderer.RenderAdaptiveCard(card);
// add it to your ui
myGrid.Children.Add(uiCard);
```

## Example
Here is an example from the Xaml renderer to give you a feel for how this works:

```csharp
var hostConfig = new HostConfig() { ... };
var renderer = new XamlRenderer(hostConfig, this.Resources, _onAction, _OnMissingInput);
var uiCard = renderer.RenderAdaptiveCard(_card);
myGrid.Children.Add(uiCard);
...
private void _onAction(object sender, ActionEventArgs e)
{
    if (e.Action is OpenUrlAction)
    {
        OpenUrlAction action = (OpenUrlAction)e.Action;
        Process.Start(action.Url);
    }
    else if (e.Action is ShowCardAction)
    {
        ShowCardAction action = (ShowCardAction)e.Action;
        ShowCardWindow dialog = new ShowCardWindow(action.Title, action, this.Resources);
        dialog.ShowDialog();
    }
    else if (e.Action is SubmitAction)
    {
        SubmitAction action = (SubmitAction)e.Action;
        // Send e.Data to the source...
        ...
    }
    else if (e.Action is AdaptiveCards.HttpAction)
    {
        AdaptiveCards.HttpAction action = (HttpAction)e.Action;
        ... 
        // action.Headers  has headers for HTTP operation
        // action.Body has content body
        // action.Method has method to use
        // action.Url has url to post to
    }
}

private void _OnMissingInput(object sender, MissingInputEventArgs args)
{
    MessageBox.Show($"Required input is missing.");
}
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

When you pass it in to the XamlRenderer you are setting the default HostConfig to use for every card you render.

### Changing per element rendering
The XamlRenderer has a registration mechanism which allows you to set a function which is called to perform the
rendering on a per element basis.  It exposes a method called SetRenderer<ElementT>(func); 

Let's say you want to override the rendering of a Input.Date element.  You would do something like this:
```csharp
xamlRenderer.SetRenderer<DateInput>(RenderMyCustomeDate);
```

And the new date renderer would look like this:
```csharp
public static FrameworkElement Render(TypedElement element, RenderContext context)
{
    DateInput input = (DateInput)element;
    var datePicker = new DatePicker();
    ...
    return datePicker;
}
```


### UI Framework styling
If you pass in a Xaml ResourceDictionary you can further customize the Xaml behavior. This
allows you to define roll over behaviors, animations, rounded buttons, etc.  Here is a table of the 
style names that are used for each element.  

| Element | Style names used|
|---|---|
| AdaptiveCard | Adaptive.Card| 
| Action.Http | Adaptive.Action.Http |
| Action.OpenUrl  | Adaptive.Action.OpenUrl  |
| Action.ShowCard | Adaptive.Action.ShowCard |
| Action.Submit  | Adaptive.Action.Submit  |
| ActionSet | Adaptive.ActionSet |
| Column | Adaptive.Column, Adaptive.Action.Tap |
| ColumnSet | Adaptive.ColumnSet, Adaptive.VerticalSeparator |
| Container | Adaptive.Container|
| Input.ChoiceSet | Adaptive.Input.ChoiceSet,  Adaptive.Input.ChoiceSet.ComboBox, Adaptive.Input.ChoiceSet.CheckBox,  Adaptive.Input.ChoiceSet.Radio,  Adaptive.Input.ChoiceSet.ComboBoxItem, |
| Input.Date | Adaptive.Input.Text.Date
| Input.Number | Adaptive.Input.Text.Number |
| Input.Text | Adaptive.Input.Text |
| Input.Time | Adaptive.Input.Text.Time |
| Input.Toggle| Adaptive.Input.Toggle|
| Image  | Adaptive.Image |
| ImageSet  | Adaptive.ImageSet |
| FactSet | Adaptive.FactSet, Adaptive.Fact.Title, Adaptive.Fact.Value|
| TextBlock  | Adaptive.TextBlock |

Here is a sample resource dictionary which adds a hover effect on elements with an Action defined on them:
```xml
<Window.Resources>
    <Style x:Key="Adaptive.Action.Tap" TargetType="Button">
        <Style.Triggers>
            <Trigger Property="IsMouseOver" Value="True">
                <Setter Property="Cursor" Value="Hand" />
            </Trigger>
            <EventTrigger RoutedEvent="UIElement.MouseEnter">
                <BeginStoryboard>
                    <Storyboard>
                        <DoubleAnimation Duration="0:0:0.2" Storyboard.TargetProperty="Opacity" To="0.7" />
                    </Storyboard>
                </BeginStoryboard>
            </EventTrigger>
            <EventTrigger RoutedEvent="UIElement.MouseLeave">
                <BeginStoryboard>
                    <Storyboard>
                        <DoubleAnimation Duration="0:0:0.2" Storyboard.TargetProperty="Opacity" To="1.0" />
                    </Storyboard>
                </BeginStoryboard>
            </EventTrigger>

        </Style.Triggers>
        <Setter Property="Template">
            <Setter.Value>
                <ControlTemplate TargetType="Button">
                    <Border Background="Transparent">
                        <ContentPresenter/>
                    </Border>
                </ControlTemplate>
            </Setter.Value>
        </Setter>
    </Style>
</Window.Resources>
```

## Resources
* [Libraries](/documentation/#display-libraries) 
* [Implementing a renderer](/documentation/#disply-implementingrenderer) 
* [Customizing a renderer](/documentation/#display-customizingrenderer) 


