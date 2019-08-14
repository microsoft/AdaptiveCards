# BaseElement element

Abstract class for the base element type.

| Property | Type | Required | Description | Version |
|--|--|--|--|--|
| type | `string` | Yes | The type of the element. | 1.0 |
| id | `string` | No, default `null` | An identifier to uniquely identify the element. | 1.0 |
| spacing | `Spacing` | No, default `default` | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| separator | `boolean` | No, default `false` | When `true`, draws a separating line between this element and the preceding element. | 1.0 |

# Rendering

1. If any required elements are missing or invalid, engage fallback and stop.
1. Else, render the element
1. If failed to render, engage fallback and stop.
1. Else, if there is a preceding element that has been rendered...
	1. Add the specified amount of `spacing` before this element.
	1. If `separator` is true, draw a separating line in the vertical center of the spacing.