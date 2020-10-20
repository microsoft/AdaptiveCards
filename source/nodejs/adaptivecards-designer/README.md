# Adaptive Card Designer

The Adaptive Card Designer provides a rich, interactive design-time experience for authoring [adaptive cards](https://adaptivecards.io). 

Try it out at [https://adaptivecards.io/designer](https://adaptivecards.io/designer)

![Designer Screenshot](https://adaptivecards.io/images/designer.png)

## What is this package?

This package allows you to easily integrate the adaptive cards designer into your own experiences. 

## Usage

There are two simple ways to consume the designer: CDN script reference or importing the module and using webpack.

### Option 1: CDN script references

The simplest way to get started it to include 3 script tags in your page. 

1. **monaco-editor** - provides a rich JSON-editing experience
2. **markdown-it** - [optional] automatic markdown support for the designer and cards

To load the designer component you have 2 options:

3. 
   * **adaptivecards-designer** - the designer component, with default Microsoft hosts included (Teams, Outlook, Cortana, etc)
   * **adaptivecards-designer-standalone** - the standalone designer component, without any standard Host Config containers

```html
<!-- OPTIONAL: markdown-it isn't required but enables out-of-the-box markdown support -->
<script src="https://unpkg.com/markdown-it@8.4.0/dist/markdown-it.min.js"></script>

<!-- REQUIRED: monaco-editor is required for the designer to work -->
<script src="https://unpkg.com/monaco-editor@0.17.1/min/vs/loader.js"></script>

<!-- DESIGNER OPTION A: Card Designer + Standard Hosts 
	(replace <VERSION> with the version you want to load, or "latest" for latest)
-->
<script src="https://unpkg.com/adaptivecards-designer@<VERSION>/dist/adaptivecards-designer.min.js"></script>

<!-- DESIGNER OPTION B: Standalone Card Designer, without standard Hosts 
	(replace <VERSION> with the version you want to load, or "latest" for latest)
	<script src="https://unpkg.com/adaptivecards-designer@<VERSION>/dist/adaptivecards-designer-standalone.min.js"></script>
-->

<script type="text/javascript">
	window.onload = function() {
		let hostContainers = [];

		// Optional: add the default Microsoft Host Apps (see docs below)
		// hostContainers = ACDesigner.defaultMicrosoftHosts;
		 
		let designer = new ACDesigner.CardDesigner(hostContainers);

		// The designer requires various CSS and image assets to work properly, 
		// If you've loaded the script from a CDN it needs to know where these assets are located
		// Use the same <VERSION> that you used above
		designer.assetPath = "https://unpkg.com/adaptivecards-designer@<VERSION>/dist";

		// Initialize monaco-editor for the JSON-editor pane. The simplest way to do this is use the code below
		require.config({ paths: { 'vs': 'https://unpkg.com/monaco-editor@0.17.1/min/vs' } });
		require(['vs/editor/editor.main'], function () {
			designer.monacoModuleLoaded();
		});

		designer.attachTo(document.getElementById("designerRootHost"));
	};
</script>

<body>
   <div id="designerRootHost"></div>
</body>
```

### Option 2: Node + webpack

If you already use webpack and want to to bundle the designer, you need a few packages. **adaptivecards-designer**, **monaco-editor** for the JSON editor, and **markdown-it** for markdown handling. You can use another markdown processor if you choose.

```console
npm install adaptivecards-designer monaco-editor markdown-it
```

You also need some development dependencies to bundle monaco, and copy some CSS+image files into your output.

```console
npm install copy-webpack-plugin monaco-editor-webpack-plugin css-loader style-loader
```

Then in your app, use the following imports and API. The code below was authored in TypeScript, but can be easily modified to plain JS. 

```js
import * as monaco from "monaco-editor";
import * as markdownit from "markdown-it";
import * as ACDesigner from "adaptivecards-designer";

// if you want to bundle the designer CSS using something like mini-css-loader:
import "adaptivecards-designer/dist/adaptivecards-designer.css";

// Uncomment below if you choose to pass an empty hostContainers array
//import "adaptivecards-designer/dist/adaptivecards-defaulthost.css";

window.onload = function() {
	ACDesigner.CardDesigner.onProcessMarkdown = (text, result) => {
		result.outputHtml = new markdownit().render(text);
		result.didProcess = true;
	}

	let hostContainers = [];
	
	// Optional: add the default Microsoft Host Apps (see docs below)
	// hostContainers = ACDesigner.defaultMicrosoftHosts;

	let designer = new ACDesigner.CardDesigner(hostContainers);
	designer.attachTo(document.getElementById("designerRootHost"));
	designer.monacoModuleLoaded(monaco);
};

```

#### Webpack.config.js

The following plugins and configuration should be enough to boostrap the designer and dependencies.

* **monaco-editor-webpack-plugin** - makes it easy to use monaco with webpack
* **copy-webpack-plugin** [OPTIONAL] - If you use any of the default Host Configs, then the designer requires a few CSS and image assets be available. This plugin as described below copies them from the designer package into your output bundle

```js
const MonacoWebpackPlugin = require('monaco-editor-webpack-plugin');
const CopyWebpackPlugin = require('copy-webpack-plugin');

module.exports = {
	...
	module: {
		rules: [
			{
				test: /\.css$/,
				use: [
					'style-loader',
					'css-loader'
				]
			}
		]
	},
	plugins: [
		new CopyWebpackPlugin([{
			from: 'node_modules/adaptivecards-designer/dist/containers/*',
			to: 'containers/',
			flatten: true
		}]),
		new MonacoWebpackPlugin({
			languages: ['json']
		})
	]
};
```

## Open Sample button

The Designer makes it easy to load a sample from a catalog. Simply create a file on your web host with the following structure

```json
[
    {
        "displayName": "My Sample Payload",
		"cardPayloadUrl": "url/to/the/payload.json",
		"dataSampleUrl": "optional/url/to/sample/data.json
    }
]
```

And then set the `sampleCatalogueUrl` to the location of that file:

```js
/* Configure "Open Sample" tooobar button */
designer.sampleCatalogueUrl = window.location.origin + "/sample-catalogue.json";
```

## Advanced configuration

For advanced configuration of the designer use the following APIs.

```js
// Turn general support for data binding (templating) on or off. When set to false, this flag overrides showDataStructureToolbox and showSampleDataEditorToolbox.
ACDesigner.GlobalSettings.enableDataBindingSupport: boolean = true;

// Show or hide the "Data structure" toolbox. NOTE: the "Data structure" toolbox is currently non functional and will likely be removed in a future release
ACDesigner.GlobalSettings.showDataStructureToolbox: boolean = false;

// Show or hide the "Sample Data" toolbox.
ACDesigner.GlobalSettings.showSampleDataEditorToolbox: boolean = true;

// Show or hide the target version picker.
ACDesigner.GlobalSettings.showVersionPicker: boolean = true;

// Controls whether the target version should change according to the selected  host application. Each host application is associated with a maximum supported target version.
ACDesigner.GlobalSettings.selectedHostContainerControlsTargetVersion: boolean = true;

// Controls whether a warning message should be displayed when the selected target version is greater than the version supported by the selected host application. This warning is meant to inform the user that not all features they're designing their card with will work in the target host.
ACDesigner.GlobalSettings.showTargetVersionMismatchWarning: boolean = true;

/* Configure toolbox titles */
ACDesigner.Strings.toolboxes.cardEditor.title = "Custom card editor title";
ACDesigner.Strings.toolboxes.cardStructure.title = "Custom card structure title";
ACDesigner.Strings.toolboxes.dataStructure.title = "Custom data structure title";
ACDesigner.Strings.toolboxes.propertySheet.title = "Custom property sheet title";
ACDesigner.Strings.toolboxes.sampleDataEditor.title = "Custom sample data editor title";
ACDesigner.Strings.toolboxes.toolPalette.title = "Custom tool palette title";

/* To configure custom Pic2Card endpoint */
ACDesigner.Pic2Card.pic2cardService = "https://<<your-pic2Card-service-endpoint>> ";

/* Modify the Element toolbox (BEFORE calling attachTo) */
Adaptive.GlobalRegistry.elements.unregister("RichTextBlock");
ACDesigner.CardDesignerSurface.cardElementPeerRegistry.unregisterPeer(Adaptive.RichTextBlock);

/* Modify the Actions flyout (BEFORE called attachTo) */
Adaptive.GlobalRegistry.actions.unregister("Action.ToggleVisibility");
ACDesigner.CardDesignerSurface.actionPeerRegistry.unregisterPeer(Adaptive.ToggleVisibilityAction);

/* Include all built-in host apps */
let hostContainers: ACDesigner.HostContainer[] = ACDesigner.defaultMicrosoftHosts;
let designer = new ACDesigner.CardDesigner(hostContainers);

/* Or pick and choose which built-in host apps to include, and/or add your custom host app */
let hostContainers: ACDesigner.HostContainer[] = [
	new ACDesigner.WebChatContainer("Bot Framework WebChat", "containers/webchat-container.css"),
	new ACDesigner.OutlookContainer("Outlook Actionable Messages", "containers/outlook-container.css"),
	new MyCustomContainerClass("My Custom Container", "path-to-my-custom-container-stylesheet.css")
];
let designer = new ACDesigner.CardDesigner(hostContainers);

/* Modify the toolbar */
let myButton = new Designer.ToolbarButton(
	"myButton",
	"My button",
	null,
	(sender) => { alert("My button was clicked"); });
myButton.separator = true;

designer.toolbar.insertElementAfter(myButton, Designer.CardDesigner.ToolbarCommands.HostAppPicker);

/* Collapse certain panes by default (AFTER calling attachTo)	*/
designer.treeViewToolbox.collapse();
designer.jsonEditorToolbox.collapse();

/* Set the card payload in the designer: (AFTER calling attachTo */ 
designer.setCard(
	{
		type: "AdaptiveCard",
		version: "1.0",
		body: [
			{
				type: "TextBlock",
				text: "Hello world"
			}
		]
	}
);

/* Set sample data (AFTER calling attachTo) */ 
designer.sampleData = {
	name: "John Doe",
	phone: "123-123-1234"
};
```

## Hosting Pic2Card Service

Pic2Card is a ML based service which converts a graphical image (such as a PNG or JPEG) into an Adaptive Card JSON payload.

To setup the pic2card ML service follow the instructions given in the below link.

[pic2card service](https://github.com/microsoft/AdaptiveCards/tree/main/source/pic2card#run-the-pic2card-service-in-docker-container)

Once your pic2card ML service is up and running, update the host configuration(PIC_TO_CARD_PREDICTION_API)
in `.env` file in the adaptivecards-designer root directory and rebuild this project.
