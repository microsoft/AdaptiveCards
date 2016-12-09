# Introducing Adaptive Cards

Adaptive Cards allow developers to describe a light-weight user experience that can be interpreted natively on multiple platforms and hosting applications.

For example:

* A Bot Framework developer can send an Adaptive Card to a Skype user, which would render beautifully on iOS, Android, Windows, and the web.
* An Outlook Connector developer can describe a rich Connector visualization with complex layout
* A Windows developer can create a rich Live Tile or Toast Notification on PC, Mobile, Xbox, and HoloLens
* A Cortana developer can describe a notification that can appear on a PC screen, a Car, or spoken aloud on a headless device

**TODO: add Screenshot of some good Cards**

## Install and build

To build and run the Visualizer:

1. Clone this repo
1. `npm install`
1. `npm run build` (to build on every change do `npm run watch`)
1. `npm start`

# How it works

Developers describe the experience they want using a generic yet powerful JSON payload. With a properly described payload we take on the burden of presenting the best experience to a user wherever they are.

The payload is designed to be expressive enough that it addresses the long-tail of scenarios, without imposing the burden of fine-grained design, development, and testing across every platform and application. 

Adaptive Cards are comprised of `TextBlock`, `Images`, `Input`, and `Actions`, that may be `combined` together as necessary. 

* All content flows top-down in the order specified. 
* `TextBlocks` takes up a single line (by default) and will be truncated as necessary. 
* `Images` expand to the width of their container, while maintaining aspect ratio.
* `ColumnGroups` allow developers to create rows and columns to partition elements
* `Actions` align horizontally if they fit; otherwise stack vertically.
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
 
# Documentation

Please see the `docs` folder for more information.

# Versioning and fallback

Versioning and Fallback are important topics and have a dedicated page/discussion. 

See the following page for more details on [Versioning and Graceful fallback](docs/GracefulFallback.md)

# Rendering Cards in your App or Web Site

If you have the need to render Adaptive Cards inside your app or web site, the Toolkit provides a couple Renderers to help achieve this.

We plan to cover this in greater detail on the [Rendering Cards page](docs/RenderingCards.md)
