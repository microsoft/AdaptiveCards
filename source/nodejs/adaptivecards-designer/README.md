# Adaptive Card Designer (Beta)

The Adaptive Card Designer provides a rich, interactive design-time experience for authoring [adaptive cards](https://adaptivecards.io). 

Try it out at [https://adaptivecards.io/designer](https://adaptivecards.io/designer)

![Designer Screenshot](https://adaptivecards.io/images/designer.png)

## What is this package?

This package allows you to easily integrate the adaptive cards designer into your own experiences. 

## Beta notice 

**NOTE**: The designer is currently considered beta and **may have breaking changes** in the public API as we get feedback.

## Usage

There are two simple ways to consume the designer: CDN script reference or importing the module and using webpack.

### Option 1: CDN script references

The simplest way to get started it to include 3 script tags in your page. 

* **monaco-editor** - provides a rich JSON-editing experience
* **adaptivecards-designer** - the designer component
* **markdown-it** - [optional] automatic markdown support for the designer and cards

```html
<!-- markdown-it isn't required but enables out-of-the-box markdown support -->
<script src="https://unpkg.com/markdown-it@8.4.0/dist/markdown-it.min.js"></script>

<!-- NOTE: monaco-editor is required for the designer to work. We currently provide it in the CDN, but this may change later -->
<script src="https://unpkg.com/adaptivecards-designer@0.1.1/dist/monaco-editor/min/vs/loader.js"></script>

<script src="https://unpkg.com/adaptivecards-designer@0.1.1/dist/adaptivecards-designer.min.js"></script>

<script type="text/javascript">
	window.onload = function() {

		let hostContainers = [];

		// Optional: add the default Microsoft Host Apps (see docs below)
		// hostContainers.push(new ACDesigner.WebChatContainer("Bot Framework WebChat", "containers/webchat-container.css"));
		 
		let designer = new ACDesigner.CardDesigner(hostContainers);

		// The designer requires various CSS and image assets to work properly, 
		// If you've loaded the script from a CDN it needs to know where these assets are located
		designer.assetPath = "https://unpkg.com/adaptivecards-designer@0.1.1/dist";

		// Initialize monaco-editor for the JSON-editor pane. The simplest way to do this is use the code below, since we currently bundle monaco into our CDN distribution. 
		require.config({ paths: { 'vs': 'https://unpkg.com/adaptivecards-designer@0.1.0/dist/monaco-editor/min/vs' } });
		require(['vs/editor/editor.main'], function () {
			designer.monacoEditorLoaded();
		});

		designer.attachTo(document.getElementById("designerRootHost");
	};
</script>

<body>
   <div id="designerRootHost"></div>
</body>
```

### Option 2: Node + webpack

If you already use webpack and want to to bundle the designer, you need a few packages. **adaptivecards-designer**, **monaco-editor** for the JSON editor, and **markdown-it** for markdown handling. You can use another markdown processor if you choose.

```console
npm install adaptivecards-designer monaco-editor markdown-it --save
```

You also need some development dependencies to bundle monaco, and copy some CSS+image files into your output.

```console
npm install copy-webpack-plugin monaco-editor-webpack-plugin css-loader style-loader --save-dev
```

Then in your app, use the following imports and API. The code below was authored in TypeScript, but can be easily modified to plain JS. 

```js
import * as monaco from "monaco-editor/esm/vs/editor/editor.api";
import * as markdownit from "markdown-it";
import * as Designer from "adaptivecards-designer";

// if you want to bundle the designer CSS using mini-css-loader:
import "adaptivecards/dist/adaptivecards-default.css";
import "adaptivecards-controls/dist/adaptivecards-controls.css";
import "adaptivecards-designer/dist/adaptivecards-designer.css";

window.onload = function() {

	if (!Designer.SettingsManager.isLocalStorageAvailable) {
		console.log("Local storage is not available.");
	}

	let hostContainers = [];
	hostContainers.push(new Designer.WebChatContainer("Bot Framework WebChat", "containers/webchat-container.css"));

	let designer = new Designer.CardDesigner(hostContainers);
	designer.attachTo(document.getElementById("designerRootHost"));
	designer.monacoModuleLoaded(monaco);
};

```

#### Webpack.config.js

The following plugins and configuration should be enough to boostrap the designer and dependencies.

* **monaco-editor-webpack-plugin** - makes it easy to use monaco with webpack
* **copy-webpack-plugin** - the designer requires a few CSS and image assets to exist in your bundle. This plugin copies them from the designer into your output

```js
...
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

## Advanced configuration

For advanced configuration of the designer use the following APIs.

```js

	/* Add the default Microsoft Host Apps 	*/ 
 
	hostContainers.push(new ACDesigner.WebChatContainer("Bot Framework WebChat", "containers/webchat-container.css"));
	hostContainers.push(new ACDesigner.CortanaContainer("Cortana Skills", "containers/cortana-container.css"));
	hostContainers.push(new ACDesigner.OutlookContainer("Outlook Actionable Messages", "containers/outlook-container.css"));
	hostContainers.push(new ACDesigner.TimelineContainer("Windows Timeline", "containers/timeline-container.css"));
	hostContainers.push(new ACDesigner.DarkTeamsContainer("Microsoft Teams - Dark", "containers/teams-container-dark.css"));
	hostContainers.push(new ACDesigner.LightTeamsContainer("Microsoft Teams - Light", "containers/teams-container-light.css"));
	hostContainers.push(new ACDesigner.BotFrameworkContainer("Bot Framework Other Channels (Image render)", "containers/bf-image-container.css"));
	hostContainers.push(new ACDesigner.ToastContainer("Windows Notifications (Preview)", "containers/toast-container.css"));


	/* Modify the toolbar */
    let myButton = new Designer.ToolbarButton(
        "myButton",
        "My button",
        null,
        (sender) => { alert("My button was clicked"); });
    myButton.separator = true;
    designer.toolbar.insertElementAfter(myButton, Designer.CardDesigner.ToolbarCommands.HostAppPicker);


	/* Collapse certain panes by default (BEFORE designer attached)	*/
	designer.treeViewPane.collapse();
	designer.jsonEditorPane.collapse();
	

	/* Set the card payload in the designer: (AFTER designer attached) */ 
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
};
```

## Full sample code

See the [full example here](https://unpkg.com/adaptivecards-designer@0.1.0/dist/index-cdn.html)