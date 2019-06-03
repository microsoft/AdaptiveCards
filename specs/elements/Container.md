<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# Container

| Property | Type | Required | Description | Version |
| -------- | ---- | -------- | ----------- | ------- |
| **type** | `string` | Depends | Must be `"Container"`. | 1.0 |
| **items** | `BlockElement[]` | Yes | The card elements to render inside the `Container`. | 1.0 |
| **selectAction** | `ISelectAction` | No | An Action that will be invoked when the `Container` is tapped or selected. `Action.ShowCard` is not supported. | 1.0 |
| **style** | `ContainerStyle?` | No | Style hint for `Container`. | 1.0 |
| **verticalContentAlignment** | `VerticalContentAlignment` | No, default: top | Defines how the content should be aligned vertically within the container. | 1.0 |
| **bleed** | `boolean` | No | Determines whether the element should bleed through its parent's padding. | 1.0 |
| **backgroundImage** | `BackgroundImage` | No | Specifies the background image. | 1.0 |
| **id** | `string` | No | A unique identifier associated with the element. | 1.0 |
| **spacing** | `Spacing` | No | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| **separator** | `boolean` | No | When `true`, draw a separating line at the top of the element. | 1.0 |
<!-- END AUTO-GENERATED -->

## Rendering

1. Determine the padding...
	1. If 