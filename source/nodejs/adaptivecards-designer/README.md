# Adaptive Card Designer
The **Adaptive Card Designer** is a tool that makes it easy to craft Adaptive Cards from scratch (or from an existing sample) **without having to write any JSON**. It is built on top of the official TypeScript renderer in order to take advantage of existing rendering logic and let users see exactly what their cards will look like.

The designer is currently live at https://acdesignerbeta.azurewebsites.net

![Adaptive Card Designer](./screenshot.png)

## Current features
- Design cards visually without writing any JSON
- Drag and drop support to easily add new elements or reorganize elements within a card
- Immediately see the resulting JSON
- Modify the JSON and immediately see the changes applied to the card
- See cards as they would be displayed in Outlook, Cortana, Skype

## Coming features
- Easily edit a FactSet's facts, a ChoiceSet's choices, an ActionHttp's headers (currently these can only be done by manually modifying the JSON)
- Save and load cards
- Collapse the JSON editor and property sheet
- Additional hosts
- Host-specific functions:
  - Send a card to your own Office 365 account to see it as an Actionable Message in Outlook
- Library of card samples to quickly get started
- Ability to create snippets and add them to the tool palette
- And more...

## Designer vs. Visualizer
Currently, the Designer and the [Visualizer](adaptivecards.io/visualizer/) are two separate tools. Similarly, Outlook has its own [Playground Tool](https://messagecardplayground.azurewebsites.net/) to create Actionable Message cards. Eventually, all these tools will be merged into a single one, offering a one-stop-shop for all card design needs.

## How to build
The Designer uses both the official **TypeScript Adaptive Card renderer** as well as a **custom controls library**. The controls library is currently not available on NPM. While the renderer is available on NPM, it is best to build the designer using local dependencies on those two libraries.

To build, follow these steps:

```shell
cd adaptivecards

npm install
npm build
npm link

cd ..\adaptivecards-controls

npm install
npm build
npm link

cd ..\adaptivecards-designer

npm install
npm link adaptivecards-controls
npm link adaptivecards
npm build
```

Launch the designer by opening `index.html`

## Contributing
The Designer's codebase is currently a moving target as essential features are being added to reach the initial "ready to ship" milestone. For that reason, larger contributions might not make it into the product until it exits the preview stage.