# Image element

**Inherits from Element**.

Displays an image.

| Property | Type | Required | Description | Version |
| altText | string | No | Alternate text describing the image | 1.0 |
| selectAction | object | No | An action invoked when the image is tapped or selected. | 1.1 |
| url | string | Yes | The URL to the image | 1.0 |

## Rendering

A host must perform a GET request on the `url` specified to obtain the image.

For sizes `small`, `medium`, and `large`, the image should preserve aspect ratio while scaling to fit the width corresponding to each of those sizes (height will be determined by image's aspect ratio).