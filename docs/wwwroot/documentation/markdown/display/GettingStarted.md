# Getting started adding cards to your application
To add the ability to display cards in your application:

1. **Add a renderer library** - add a reference to a renderer library appropriate to your application.
2. **Create an instance** - of the renderer configured with your app's style, and with action event handlers
3. **Render your card** -ask the renderer to render a card to your UI framework

## Add a renderer
In the adaptive cards github repo we have implemented a number of renderers that target various environments.

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
Over time, there may be more libraries available. 

## Create an instance of your renderer
The next step is to create an instance of the renderer library. 

### Hook up action events
If you want to the action buttons to do something you need to hook up an action handler.

* **Action.OpenUrl** - open the action.Url.  
* **Action.Submit** - take  the result of the submit and sending it to the source. How you 
send it to the source of the card is entirely up to you.
* **Action.Http** -For this action you should do submit an HTTP request to the approprite url with Headers and Body set
* **Action.ShowCard**  you should pop a dialog and render the sub card into that dialog. *(NOTE: You only need to handle this if you are using ShowCardActionMode set to popup)*
 

## Render a card
Now you get a card from some source, and simply call the renderer passing in the card to get back a native UI object which
represents your card rendered into your UI framework.  Add the card to your UI and you are done.

## Customization
There are several ways you can customize what is rendered. 

### Using HostConfig
The HostConfig is a cross library, cross platform group of settings which control how the cards are rendered.  Through this 
object you can define things like font sizes, separation between elements, colors, etc. 

### Changing per element rendering
Most libraries allow you to override a given elements rendering making it easy for you to substitute your own rendering
for that element.  For example, you can change the Input.Date renderer to emit your own custom control, while keeping
the rest of the output of the renderer.

### UI Framework styling
Most UI frameworks allow you to further style the output using UI framework styling.  For example, in HTML you can style
the output of the renderer using CSS, and in XAML you can style the output of the renderer using XAML Styles.

## Resources
* [Libraries](/documentation/#display-libraries) 
* [Implementing a renderer](/documentation/#disply-implementingrenderer) 
* [Customizing a renderer](/documentation/#display-customizingrenderer) 




