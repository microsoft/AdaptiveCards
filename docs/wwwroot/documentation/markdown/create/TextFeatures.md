# Extended Text features
TextBlock is one of the core elements and has some special features in the interpretation of text.

## Markdown
To support inline markup adaptive cards supports a subset of *markdown*.  

Currently the following are supported:
* **Bold**
* *Italic*
* Bulleted Lists
* Numbered Lists

Headers, tables and images are not supported.

## Emojis
The schema supports text-friendly emoji translation, so each renderer should properly translate the text to it's unicode character.

> ":umbrella:" => *unicode umbrella emojii character in the text*

## Formatting Functions

When sending TextBlock items with date or time information you need to be able to translate the date or time to the
recipients timezone using their locale.  This is a task which is almost always way easier for the client to do then
for the sender.  To make it easy for clients to do this we have the ability to invoke a DATE() and TIME() function
inside text of the textblock.

These functions can be invoked anywhere in the text of a text block like this:

```
    "Your order was shipped {{DATE(2017-02-13T20:46:30Z, Long)}} and will arrive at {{TIME(2017-02-13T20:00:00Z, Short)}}" 
```

### Date Formatting Function

The DATE function is passed an ISO-8601 formatted date-time record (example: 2017-02-13T20:46:30Z), and an optional hint expressing
how you would like the date to be formatted for the user in the text string.

The format is expressed as a binding clause like this:

```
    {{DATE(..iso-8601.., Short|Long)}}
```

Example for (en-us):
```
    {{DATE(2017-02-13T20:46:30Z, Short)}} => 2/13/2017
    {{DATE(2017-02-13T20:46:30Z, Long)}} => Monday, February 13, 2017
```
> NOTE: The hint part of the function is optional and can be omitted like this:
```
    {{DATE(2017-02-13T20:46:30z)}}
```

### Time Formatting Function

The TIME function is passed an ISO-8601 formatted date-time record (example: 2017-02-13T20:46:30Z), and an optional hint expressing
how you would like the time to be formatted for the user in the text string.

The format is expressed as a binding clause like this:

```
    {{TIME(..iso-8601.., Short|Long)}}
```
Example for (en-us):
```
    {{TIME(2017-02-13T20:46:30Z, Short)}} => 8:46 PM
    {{TIME(2017-02-13T20:46:30Z, Long)}} => 8:46:30 PM
```
> NOTE: The hint part of the function is optional and can be omitted like this:

```
    {{TIME(2017-02-13T20:46:30z)}}
```
