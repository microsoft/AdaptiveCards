# AdaptiveCard element

An AdaptiveCard is the top-level element, but also can be used in ShowCards.

| Property | Type | Required | Description | Version |
|--|--|--|--|--|
| type | `"AdaptiveCard"` | Yes | Must be `"AdaptiveCard"` | 1.0 |
| body | `ICardBodyElement[] | No | The card elements to show in the primary card region. | 1.0 |
| actions | `Action[]` | No | The actions to show in the card's action bar. | 1.0 |
| selectAction | `Action` | No | An action that will be invoked if the card is tapped or selection. `Action.ShowCard` is not supported. | 1.1 |
| version | `string` | Yes | Minimum version of Adaptive Cards that this card requires. If the renderer is **lower** than this version, the `fallbackText` will be rendered instead. NOTE: For cards within an `Action.ShowCard`, the `version` property is NOT required. | 1.0 |
| fallbackText | `string` | No | Text shown when the version specified is greater than the renderer's version. This text supports markdown. | 1.0 |
| backgroundImage | `string` | No | An image applied to the background of the card. | 1.0 |
| speak | `string` | No | Specifies what text should be spoken for the entire card. Supports both simple text and SSML fragment. | 1.0 |
| lang | `string` | No | The 2-letter ISO-639-1 language used in the card. Used to localize any date/time functions. | 1.0 |


## Rendering

1. First check that all required properties are present and valid. If not, return a rendering error.
1. Then, check the `version` value. It is formatted as a string like `1.2`. If the `version` value is greater than your current Adaptive Cards supported version of your renderer...
	1. Display the `fallbackText` instead. Use the same markdown and text processing support as described in `TextBlock`.
	1. If the `fallbackText` wasn't provided, return a rendering error.
1. Else, start creating the card...
1. Create a native UI container with the padding specified in `hostConfig.spacing.padding`.
1. If `body` is specified, render each element following the same rules as `Container`.
1. If `actions` is specified, render each action following the same rules as `ActionSet`. Typically the actions should be rendered BELOW the `body`, but renderers can choose where to render them depending on what makes the most sense.
1. If both `body` and `actions` were rendered, ensure spacing between the `body` and `actions` is set to the value specified in `hostConfig.actions.spacing`.
1. If `selectAction` was specified and valid, make the entire card clickable, invoking that action when clicked.
1. If supporting reading cards aloud, use the `speak` tag if specified and process it as SSML fragment text.