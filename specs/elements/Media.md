# Media element

Displays a media player for audio or video content.

**Inherits from BaseElement**. Introduced in version 1.1.

| Property | Type | Required | Description | Version |
|--|--|--|--|--|
| type | `"Media"` | Yes | Must be `Media` | 1.1 |
| sources | `MediaSource[]` | Yes | Array of media sources to attempt to play. | 1.1 |
| poster | `string` | No | URL of an image to display before playing. | 1.1 |
| altText | `string` | No | Alternate text describing the audio or video. | 1.1 |


## Rendering

1. Iterate through the `sources` and find the first supported source. If there's no supported source present, engage fallback and stop.
1. If the `poster` is present...
	1. Display the `poster`
1. Else
	1. Display the default host poster
1. Upon user clicking the element, start playing the video and display media controls. Basic controls should include play/pause, a seek bar, volume/fullscreen.
1. Set the `altText` in accessibility properties.