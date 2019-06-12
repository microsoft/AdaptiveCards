<!-- AUTO-GENERATED: This section is auto-generated from schemas/adaptive-card.json. Do NOT add anything above this or edit anything inside, it MUST be the first thing in the document and will be overwritten. -->

# ImageFillMode enum

| Value | Description |
| ----- | ----------- |
| `"cover"` | The background image covers the entire width of the container. Its aspect ratio is preserved. Content may be clipped if the aspect ratio of the image doesn't match the aspect ratio of the container. **verticalAlignment** is respected (**horizontalAlignment** is meaningless since it's stretched width). This is the default mode and is the equivalent to the current model. |
| `"repeatHorizontally"` | The background image isn't stretched. It is repeated in the x axis as many times as necessary to cover the container's width. **verticalAlignment** is honored (default is **top**), **horizontalAlignment** is ignored. |
| `"repeatVertically"` | The background image isn't stretched. It is repeated in the y axis as many times as necessary to cover the container's height. **verticalAlignment** is ignored, **horizontalAlignment** is honored (default is **left**). |
| `"repeat"` | The background image isn't stretched. It is repeated first in the x axis then in the y axis as many times as necessary to cover the entire container. Both **horizontalAlignment** and **verticalAlignment** are honored (defaults are **left** and **top**). |
<!-- END AUTO-GENERATED -->

