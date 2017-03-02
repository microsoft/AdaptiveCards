# Rendering Cards

If you want to render Adaptive Cards inside your app or web site, the Toolkit provides native platform Renderers to achieve this.

# Platforms 
* [Html](renderers/Html)
* React *coming soon*
* [WPF Xaml](Renderers/XamlRenderer)
* UWP *coming soon*
* iOS *coming soon*
* Android *coming soon*
* *appropriate xamarin versions*

# API

## Options
	1. SupportsInteractivity: true/false (render inputs + actions)
	2. SupportedActionTypes: string[]
	3. SupportedContainerActionTypes: string[]
	4. ShowCardActionMode: Inline/Popup
	5. CardMaxActions = 3;
	6. ContainerMaxActions = 3;
	7. Styling resource dictionary
	8. Styling buttons (David wants to deep dive)
	
## Events
	1. ActionExecuted
	2. ValidationErrors (raised on schema or configuration validation)


# Implementation Details
(This will be moved somewhere later)

	1. Can we keep styling/naming similar?
	2. Render all Card Elements
	3. Input fields
	4. Actions
	5. Renderer Styling
	6. Renderer Customization
	7. DATE and TIME function parsing
	8. Data binding in HTTP Post for Headers/Body/URL

	1. Override the renderer for custom types, to owner draw my own elements, like DateInput
	2. Collapsible text region, what about a card that sends a ton of text in Skype?
	3. How to escape during input data binding?
	4. Should fallback text apply if the client rejects the payload?



