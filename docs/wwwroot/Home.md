# Introducing adaptive cards 

Adaptive Cards is a JSON format which gives developers the ability to deliver great looking cards to any device or client.

### Developer Features
* Simple but expresive JSON layout gives developers ability to easily create rich great looking cards across any device or client!
* Rich Input controls (text, date, time, etc.) allows developer to collect information 
* Speech enabled from day one!
* Nuget and NPM libraries to make it easy to build cards in code

### Client application Features
* Client controls the rendered style, so cards from multiple sources look great together and like they were designed for the application.
* Client doesn't have to keep updating itself to support new cards

## How it works

Developers describe the experience they want using a generic yet powerful JSON payload. With a properly described payload we take on the burden of presenting the best experience to a user wherever they are.

The payload is designed to be expressive enough that it addresses the long-tail of scenarios, without imposing the burden of fine-grained design, development, and testing across every platform and application. 

Adaptive Cards are comprised of `TextBlock`, `Images`, `Input`, and `Actions`, that may be `combined` together as necessary. 

* All content flows top-down in the order specified. 
* `TextBlocks` takes up a single line (by default) and will be truncated as necessary. 
* `Images` expand to the width of their container, while maintaining aspect ratio.
* `Columns` allow developers to create rows and columns to partition elements
* `Actions` align horizontally if they fit; otherwise stack vertically.
* `Input` includes text, multi-line, selections, dates, etc.

## What's in the Toolkit

* Documentation of the schema (see [Schema.md](docs/wwwroot/markdown/Schema.md))
* Learn about the elements with the [Element Explorer](https://microsoft.github.io/AdaptiveCards/explorer)
* An online live previewer  [Interactive Visualizer](https://microsoft.github.io/AdaptiveCards) to preview and design Card payloads
* Sample Cards (see [samples](samples/Scenarios))
* The official Adaptive Card JSON schema (see [schemas/adaptive-card.json](schemas/adaptive-card.json))
* The official Adaptive Card XML schema (see [schemas/adaptive-card.xsd](schemas/adaptive-card.xsd))
* A Visual Code Live Preview Extension so you can see edits as you type (see [source/vscode](source/vscode))
* Nuget and NPM libraries
