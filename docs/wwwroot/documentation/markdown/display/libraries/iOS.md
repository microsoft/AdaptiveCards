# iOS Library
This renderer which targets iOS native controls.

## Add a renderer
This is available as a nuget packages. 
```csharp
nuget install AdaptiveCards.iOS
```

## Create an instance of the renderer
Create an instance of the renderer library. 
```csharp
var renderer = new iOSRenderer(hostConfig, this.Resources, onAction, OnMissingInput);
```

## Hook up action callback
To hook up action events, pass in a callback when you instantiate your renderer.
```csharp
var hostConfig = new HostConfig() { ... };
var renderer = new iOSRenderer(..., actionCallback:  _onAction);
```

## Render a card
Acquire a card from a source and render it.

```csharp
var uiCard = renderer.RenderAdaptiveCard(card);
// add it to your ui
myGrid.Children.Add(uiCard);
```

## Example
Here is an example from the iOS renderer.

```csharp
var hostConfig = new HostConfig() { ... };
var renderer = new iOSRenderer(hostConfig, this.Resources, _onAction, _OnMissingInput);
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
To customize the renderer, provide an instance of the HostConfig object. See the [Host Config Schema](../HostConfigSchema.md) for a full description. Since the HostConfig object is instantiated with defaults, you only have to set the properties you want to change from the defaults.
Passing it to the renderer sets the default HostConfig to use for every card you render.

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

### Changing per element rendering
The iOSRenderer has a registration mechanism which allows you to set a function that is called to perform the
rendering on a per-element basis.  It exposes a method called `SetRenderer<ElementT>(func);`. 

To override the rendering of a `Input.Date` element:
```csharp
iOSRenderer.SetRenderer<DateInput>(RenderMyCustomDate);
```
The new date renderer would look like this:
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
If you pass in a iOS ResourceDictionary you can customize the iOS behavior further. This
allows you to define roll over behaviors, animations, rounded buttons, and so on.  Here is a table of the 
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

Here is a sample resource dictionary which adds a hover effect to elements with an Action defined on them:
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

## Next steps

* [Implement a renderer](../ImplementingRenderer.md) 


