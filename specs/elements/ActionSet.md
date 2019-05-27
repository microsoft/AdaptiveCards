<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# ActionSet

#### Introduced in version 1.2

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **items** | `array[]` | Yes | The actions to include in the `ActionSet` | 1.2 |
| **type** | `string` | Yes | &nbsp; | 1.2 |
| **id** | `string` |  No | A unique identifier associated with the element. | 1.2 |
| **spacing** | `string` |  No | Controls the amount of spacing between this element and the preceding element. | 1.2 |
| **separator** | `boolean` |  No, default: `false` | When `true`, draw a separating line at the top of the element. | 1.2 |
<!-- END AUTO-GENERATED -->

## Rendering

### Icon style of buttons

1. If ALL actions have a valid `iconUrl`...
	1. Respect the `hostConfig.actions.iconPlacement` property.
	1. If `iconPlacement` is `aboveTitle` then the `hostConfig.actions.iconSize` should be used as the **height** of the image, while maintaining aspect ratio. Card Authors should use square images for ideal portability between Hosts.
	1. If `iconPlacement` is `leftOfTitle` then the image **SHOULD BE** as close as possible to the height of the text in the action. If that isn't reasonable then `hostConfig.actions.iconSize` should be used for the height.
1. Else if only SOME have a valid `iconUrl`...
	1. Use `leftOfTitle` to ensure that all buttons are rendered with the same height.
1. Else if NONE have a valid `iconUrl`...
	1. Display as text-only buttons

Renderers must set the per-platform styling name corresponding to the style chosen, so that hosts can style accordingly. For example, if the style ended up being `aboveTitle`, then the platform style should be something like `ActionWithIconAboveTitle`.


### Orientation and alignment of buttons

The orientation and alignment is determined by a combination of `hostConfig.actions.actionsOrientation` and `hostConfig.actions.actionAlignment`.

| | Horizontal | Vertical |
|--|--|--|
| **Stretch** | | |
| **Left** | | |
| **Center** | | |
| **Right** | | |