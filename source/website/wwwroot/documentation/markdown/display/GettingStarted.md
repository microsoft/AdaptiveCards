# Get started adding cards to your application
To add the ability to display cards in your application:

1. **Add a renderer library** - add a reference to a renderer library appropriate to your application.
2. **Create an instance** - of the renderer configured with your app's style, and with action event handlers
3. **Render your card** -ask the renderer to render a card to your UI framework

## Add a renderer
In the adaptive cards Github repo we have implemented a number of renderers that target various environments.

* Android native
* iOS native
* Html in browser
* Html server side
* Xamarin Forms
  * iOs
  * Android
  * Windows
* UWP Windows/Xaml
* WPF Windows/Xaml
* Image renderer


## Create an instance of the renderer
The next step is to create an instance of the renderer library. 

### Hook up action events
If you want to the action buttons to do something, hook up an action handler.

* **Action.OpenUrl** - opens the `action.Url`.  
* **Action.Submit** - takes the result of the submit and send it to the source. How you send it to the source of the card is entirely up to you.
* **Action.Http** - for this action, submit an HTTP request to the appropriate url with Headers and Body set.
* **Action.ShowCard**  invokes a dialog and renders the sub-card into that dialog. Note that you only need to handle this if `ShowCardActionMode` is set to `popup`.

## Render a card
After you acquire a card from some source, simply call the renderer and pass in the card. You will to get back a native UI object which
represents your card rendered into your UI framework.  Add the card to your UI and you are done.

## Customization
There are several ways you can customize what is rendered. 

### Configure HostConfig
The HostConfig is a cross-library, cross-platform group of settings which control how the cards are rendered.  Through this 
object you can define things like font sizes, separation between elements, colors, and so forth. 

### Change per-element rendering
Most libraries allow you to override the rendering of any element, making it easy for you to substitute your own rendering
for that element.  For example, you can change the `Input.Date` renderer to emit your own custom control while still retaining
the rest of the output of the renderer.

### Style UI Framework
Most UI frameworks allow you to style the output further using UI framework styling.  For example, in HTML you can style
the output of the renderer using CSS, and in XAML you can style the output of the renderer using XAML Styles.

## Resources
* [Implement a renderer](ImplementingRenderer.md) 




