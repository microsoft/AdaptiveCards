# Speech and Advanced Customization

## **THIS WORK NOT FINAL**
Please check back soon for updates.

# Client customization

Some clients expose functionality only appliacable to them. For example, Toast notifications have a Hero image and can play Audio when popped.

We plan to allow the payload to include client-specific metadata to support this.

# Adaptive Rendering Support

Some clients have specialized rendering features that aren't applicable everywhere. For example, Live Tiles allow for vertical text alignment, while others do not.

To accomodate this requirement we partitioned the properties of each element to must-have, and nice-to-have. A "nice-to-have" property will be prefixed with `hint-*`

What this means is that each client will make a best-effort approach to render the Card as the developer specified, but may have some loss of fidelity under some circumstances.

## Hints Example

Take the following payload which describes a line of text that will be vertically aligned *if possible*

```
{
    "text": "Great. What time would you like to see it?",
    "hint-verticalAligment": "bottom",
}
```

The `hint-verticalAligment` property may not be rendered on an older Skype client, but the `text` itself will be preserved.

# Speech

While we commonly focus on a Card being visual, it's important to consider how your bot might behave on a headless device that is purely speech enabled. By adorning your Card with speech-hints, you can influence how your Card is read aloud on headless devices that don't have a screen.
