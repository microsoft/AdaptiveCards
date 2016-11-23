# Introducing Adaptive Cards

Adaptive Cards allow developers to describe a light-weight user experience that can be interpreted natively on multiple platforms and hosting applications.

For example:

* A Bot Framework developer can send an Adaptive Card to a Skype user, which would render beautifully on iOS, Android, Windows, and the web.
* An Outlook Connector developer can describe a rich Connector visualization with complex layout
* A Windows developer can create a rich Live Tile or Toast Notification on PC, Mobile, Xbox, and HoloLens
* A Cortana developer can describe a notification that can appear on a PC screen, a Car, or spoken aloud on a headless device

**TODO: add Screenshot of some good Cards**

# How it works

Developers author the experience they want using a generic yet powerful JSON payload. With a properly described payload we take on the burden of presenting the best experience to a user wherever they are.

The payload is designed to be expressive enough that it addresses the long-tail of scenarios, without imposing the burden of fine-grained design, development, and testing on a variety of platforms and applications. 

Adaptive Cards are comprised of `TextBlock`, `Pictures`, `Input`, and `Actions`, that may be `combined` together as necessary. 

* All content flows top-down in the order specified. 
* `TextBlocks` takes up a single line (by default) and will be truncated as necessary. 
* `Pictures` expand to the width of their container, while maintaining aspect ratio.
* `ColumnGroups` allow developers to create rows and columns to partition elements
* `Buttons` align horizontally if they fit; otherwise stack vertically.
* `Input` includes text, multi-line, selections, dates, etc.

# What's in the Toolkit

* The official Adaptive Card JSON schema (see /schema) *(coming soon)*
* Documentation of the schema (see /docs)
* An Interactive Visualizer to preview Card payloads
* Sample Cards (see /samples)
* Card Renderer libraries for multiple platforms (HTML, iOS, Android, .NET) *(more info on this effort coming soon)*
* Card Builders for .NET and Node *(coming soon)*

# Schema and Samples

Please see [the full schema](docs/Schema.md) for the list of elements and properties that we support.
The `/samples` folder also has a list of payloads to get started with.
 
# Render Hints

Certain applications will have specialized rendering features that aren't applicable everywhere. For example, Live Tiles allow for vertical text alignment, while others do not.

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

# Speech customizations

While we commonly focus on a Card being visual, it's important to consider how your bot might behave on a headless device that is purely speech enabled. By adorning your Card with speech-hints, you can influence how your Card is read aloud on headless devices that don't have a screen.

# Versioning and fallback

Versioning and Fallback are important topics and have a dedicated page/discussion. 

See the following page for more details on [Versioning and Graceful fallback](docs/GracefulFallback.md)

# Future Explorations

* Allow developers who **require** full UI customization to take on the burden of drawing their own UI: XAML, HTML, 3D 
* Inline update of Cards
* Contextual tailoring based on client-properties (e.g., if user is driving)

# Rendering Cards in your App or Web Site

If you have the need to render Adaptive Cards inside your app or web site, the Toolkit provides a couple Renderers to help achieve this.

We plan to cover this in greater detail on the [Rendering Cards page](docs/RenderingCards.md)