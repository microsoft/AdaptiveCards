# BaseElement element

Abstract class for the base element type.

| Property | Type | Required | Description | Version |
|--|--|--|--|--|
| type | `string` | Yes | The type of the element. | 1.0 |
| id | `string` | No, default `null` | An identifier to uniquely identify the element. | 1.0 |
| spacing | `Spacing` | No, default `default` | Controls the amount of spacing between this element and the preceding element. | 1.0 |
| separator | `boolean` | No, default `false` | When `true`, draws a separating line between this element and the preceding element. | 1.0 |

# Rendering

1. If the element is going to render without any contents, renderers MUST **drop** the element, SHOULD trigger a warning, and MUST NOT trigger fallback.
	1. What counts for "not rendering any contents"?
		1. Container that has `spacing` and `separator` but nothing else --> **DROP**
		1. Container that has `minHeight` but nothing else --> **Keep**. Author might be using it for explicit spacing?
		1. Image who's image fails to load --> **DROP**
		1. Image who's image fails to load but `width` is specified --> **Keep**. UI might require the width of the image to look correct.
		1. Container that has `backgroundImage` but no inherit or explicit height --> **DROP**
		1. Column that has nothing --> **KEEP**. Author might be using it for explicit spacing.
	1. So in summary...
		1. `width`/`height`/`minHeight` all count as "contents" and should preserve
		1. Basically, the rule is kind of simply if the element consumes height or width, it should be kept
1. Render the element
1. If failed to render (like an unexpected exception occurred), (undeclared behavior) should we engage fallback and stop?
1. Else, if there is a preceding element that has been rendered...
	1. Add the specified amount of `spacing` before this element.
	1. If `separator` is true, draw a separating line in the vertical center of the spacing.
