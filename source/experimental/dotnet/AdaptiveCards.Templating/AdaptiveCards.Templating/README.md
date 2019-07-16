# Adaptive Cards Templating Engine for .NET (Preview)

This library implements a JSON-to-JSON templating/data-binding engine. While it is designed to be used with Adaptive Cards, it is not dependent on Adaptive Cards and can therefore be used in many contexts and applications.

For more information about the data binding language implemented by this library, [please refer to GitHub](https://github.com/microsoft/AdaptiveCards/issues/2448)

## Install via NuGet

Coming soon

## Usage

### Hello World example

Here is a simplistic "Hello World" example on how to use the library to generate an Adaptive Card using a template bound to a data object.

```csharp
AdaptiveTransformer transformer = new AdaptiveTransformer();

string jsonTemplate = @"{
	""type"": ""AdaptiveCard"",
	""version"": ""1.0"",
	""body"": [
		{
			""type"": ""TextBlock"",
			""text"": ""Hello, {person.firstName}!""
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
string cardJson = transformer.Transform(jsonTemplate, jsonData);
```

### Built-in functions

This library provides a set of built-in functions for use in data binding expressions. Note that any function parameter can itself be an expression.

#### substr
Extracts a substring from a string.

```typescript
substr(s: string, index: number, count: number)
```

|Parameter|Description|
|---|---|
|s|The input string|
|index|The index (zero based) where to start the extraction|
|count|The number of characters to extract|

#### JSON.parse
Converts a string representing JSON data into an object to make it possible to access its individual properties within an expression.

```typescript
JSON.parse(input: string)
```

|Parameter|Description|
|---|---|
|input|The input string. Must be a valid JSON payload.|

#### if
Returns a value that depends on whether a condition evaluates to true or false.

```typescript
if(condition: boolean, ifTrue: any, ifFalse: any)
```

|Parameter|Description|
|---|---|
|condition|The condition to evaluate.|
|ifTrue|The value to return if the condition evaluates to true.|
|ifFalse|The value to return if the condition evaluates to false.|

#### toUpper
Converts a string to its upper case representation.

```typescript
toUpper(input: string)
```

|Parameter|Description|
|---|---|
|input|The string to convert.|

#### toLower
Converts a string to its lower case representation.

```typescript
toLower(input: string)
```

|Parameter|Description|
|---|---|
|input|The string to convert.|

#### Date.format
Formats an ISO 8601 date/time string into a human redable date.

```typescript
Date.format(input: string, format: "long" | "short" | "compact")
```

|Parameter|Description|
|---|---|
|input|The string to format.|
|format|The format to use. Must be "short", "long" or "compact". Defaults to "compact"|

#### Time.format
Formats an ISO 8601 date/time string into a human redable time.

```typescript
Time.format(input: string)
```

|Parameter|Description|
|---|---|
|input|The string to format.|

### Custom functions
Currently not supported, if you need this, let us know



## Building

To build the library, first you need to build the nodejs libraries in release mode. See the nodejs folder readme for more info.