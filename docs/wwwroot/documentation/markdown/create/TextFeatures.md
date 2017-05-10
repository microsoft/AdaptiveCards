# Text features
TextBlock is one of the core elements and has some special features in the interpretation of text.

## Markdown
To support inline markup, adaptive cards supports a subset of Markdown syntax.

Supported:

**Bold** </br>
*Italic*
* Bulleted Lists
1. Numbered Lists

Not supported:
Headers, tables and images.

## Emojis
The schema supports text-friendly emoji translation, so each renderer should properly translate the text to its unicode character.

> `":umbrella:"`  => ":umbrella:" => *unicode umbrella emoji character in the text*

## Formatting Functions

When sending TextBlock items with date or time information, the date or time must be translated to the
recipient's timezone.  This is a much easier task for the client than for the sender. To make it easy, the client can invoke a `DATE()` and `TIME()` function inside the text of a textblock.

These functions can be invoked anywhere in the text of a text block.

```javascript
"Your order was shipped {{DATE(2017-02-13T20:46:30Z, Long)}} and will arrive at {{TIME(2017-02-13T20:00:00Z, Short)}}" 
```

### Date formatting function

The DATE function is passed an [ISO-8601](https://en.wikipedia.org/wiki/ISO_8601) formatted date-time record (example: 2017-02-13T20:46:30Z), and an optional hint expressing how to format the date in the text string.

The format is expressed as a binding clause like this:

```javascript
{{DATE(..iso-8601.., Short|Long)}}
```

Example for (en-us):
```javascript
{{DATE(2017-02-13T20:46:30Z, Short)}} => 2/13/2017
{{DATE(2017-02-13T20:46:30Z, Long)}} => Monday, February 13, 2017
```
The Hint part of the function is optional and can be omitted.

```javascript
{{DATE(2017-02-13T20:46:30z)}}
```

### Time formatting function

The TIME function is passed an ISO-8601 formatted date-time record (example: 2017-02-13T20:46:30Z), and an optional hint expressing how to format the time in the text string.

The format is expressed as a binding clause like this:

```javascript
{{TIME(..iso-8601.., Short|Long)}}
```
Example for (en-us):
```javascript
{{TIME(2017-02-13T20:46:30Z, Short)}} => 8:46 PM
{{TIME(2017-02-13T20:46:30Z, Long)}} => 8:46:30 PM
```
The Hint part of the function is optional and can be omitted.

```javascript
{{TIME(2017-02-13T20:46:30z)}}
```
