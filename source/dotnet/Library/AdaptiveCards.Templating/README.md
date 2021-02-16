# Adaptive Cards Templating Engine for .NET (Preview)

This library implements a JSON-to-JSON templating/data-binding. While it is designed to be used with Adaptive Cards, it is not dependent on Adaptive Cards and can therefore be used in many contexts and applications.

For more information about the data binding language implemented by this library, [please refer to GitHub](https://github.com/microsoft/AdaptiveCards/issues/2448)

## Install via NuGet

Coming soon

## Usage

### Hello World example

Here is a simplistic "Hello World" example on how to use the library to generate an Adaptive Card using a template bound to a data object.

```csharp
string jsonTemplate = @"{
	""type"": ""AdaptiveCard"",
	""version"": ""1.0"",
	""body"": [
		{
			""type"": ""TextBlock"",
			""text"": ""Hello, ${person.firstName}!""
		}
	]
}";

string jsonData = @"{
	""person"": {
		""firstName"": ""Andrew"",
		""lastName"": ""Leader""
	}
}";

// The final JSON, it'll have "text": "Hello, Andrew!" in it!
var template = new AdaptiveCardsTemplate(jsonTemplate);
var context = new AdaptiveCardsEvaluationContext() {
	Root = jsonData
};

string cardJson = template.Expand(context);
```

### AdaptiveExpression 

This library provides a set of built-in functions via AdaptiveExpression. [please refer to GitHub](https://github.com/Microsoft/BotBuilder-Samples/tree/master/experimental/common-expression-language)

Here is an example of simple use case
```json
{
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "TextBlock",
            "text": "Game Score: {if( score >= 70, 'Excellent', 'Try Again')}"
        }
    ],
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json"
}

{
    "score" : 95
}
```

With given template and data, expanded json will be an adaptive cards as shown.

```json
{
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "TextBlock",
            "text": "Game Score: Excellent"
        }
    ],
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json"
}
```


