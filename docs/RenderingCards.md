# Rendering Cards

If you want to render Adaptive Cards inside your app or web site, the toolkit provides native platform Renderers to achieve this.

# Platforms 
* HTML
* Windows (UWP) 
* Windows (WPF)
* Android
* iOS
* Xamarin Forms


## HostOptions

There is a standardized [HostOptions](HostOptions.md) object which allows the host of an adaptive card to control lhow each renderer library renders a card. 

Here is a [Sample HostConfig](samples/themes/HostConfig.json) definition.

## Events

| Event | Description |
|-------|-------------|
| **ActionExecuted** | Fires when an action is executed on the card
| **ValidationErrors** | raised on schema or configuration validation

