# Schema validation
Schema validation is a powerful way of making authoring easier and enabling tooling.

## JSON Schema file
We have provided a complete (json schema file)(/schemas/adaptive-cards.json) for editing and validating 
adaptive cards in json.

In Visual Studio and Visual Studio Code you can get automatic intellisense by including a $schema reference like this:

![bad](/content/invalidjson1.png)

![autocomplete](/content/autocomplete.png)

Example:
```javascript
{
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": []
}
```

## Xsd Schema file
The Microsoft.AdaptiveCards .NET library has XML annotations so that you can serialize and deserialize XML 
as well as JSON, making it easy to use with XML based toolsets. 

We have provided a complete (xsd schema file)(/schemas/adaptive-cards.xsd) for editing and validating 
adaptive cards in xml.

In Visual Studio and Visual Studio Code you can get automatic intellisense by including a xsd reference like this:

```xml
<?xml version="1.0" encoding="utf-16"?>
<AdaptiveCard xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
    xmlns:xsd="http://www.w3.org/2001/XMLSchema"
    xsi:noNamespaceSchemaLocation="http://adaptivecards.io/schemas/adaptive-card.xsd">
  <TextBlock Text="Hello world" />
</AdaptiveCard>
```


# Tools & samples
There are some tools and samples in the source tree which are useful references as well as being useful tools.

## Visual Studio Code Extension
We have created a visual studio code extension which allows you to visualize the card you are editing in real time
inside the editor itself. 

![extension](/content/vscode-extension.png)

To Install, open Extensions Marketplace and search for **Adapative Card Viewer**

![marketplace](/content/vscode-extension-marketplace.png)


## WPF Visualizer Sample
The WPF visualizer lets you visualize cards using WPF/Xaml on a windows machine.  Built into it is a hostconfig
editor which allows you to edit and view host config settings and save as a json file so you can then use in rendering
in your application.

![wpf visualizer](/content/wpfvisualizer.png)

## Render2Image Sample
The Render2Image sample turn any card into a PNG from the command line.
