# Rendering Cards

If you want to render Adaptive Cards inside your app or web site, the toolkit provides native platform Renderers to achieve this.

# Platforms 
* HTML
* Windows (UWP) 
* Windows (WPF)
* Android
* iOS
* Xamarin Forms


## RenderOptions

Each platform has a set of options to control how the renderer should behave. 
For example, Live Tiles show read-only content, so they set `SupportsInteractivity` to `false`, which will instruct the the renderer to strip any actions and inputs from the payload.

| Property | Type | Description |
|----------|------|-------------|
| **SupportsInteractivity** |bool | Toggles whether or not to render inputs and actions
| **SupportedActionTypes** | string[] | The types of Actions that you support (null for no actions)
| **SupportedContainerActionTypes** | string[] | The types of Actions you support in Containers (null for no Container actions)
| **ShowCardActionMode** | Inline/Popup | Toggles where a Action.ShowCard should render inline with the action, or as a popup
| **CardMaxActions** | int | Max number of actions to support on your Cards (e.g., 3)
| **ContainerMaxActions** | int | max number of actions to support inside Containers
| **Styling**| object | This property varies per platform, and influences the styling of the rendered UI. E.g., using the HTML Renderer you pass a link to a CSS stylesheet


## Events

| Event | Description |
|-------|-------------|
| **ActionExecuted** | Fires when an action is executed on the card
| **ValidationErrors** | raised on schema or configuration validation

