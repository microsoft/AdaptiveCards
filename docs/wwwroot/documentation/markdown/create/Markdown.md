
# Text Formatting
Text formatting allows powerful expressiveness within cards.

## Markdown
* Bold
* Italic
* Underline
* TODO: Finish list

## Emojis
The schema supports text-friendly emoji translation, so each renderer should properly translate the text to it's unicode character.

TODO: Link to C# Map

* `:umbrella:` => ??

## Date and Time Localization
The schema supports client-localizable dates and time. Use the following regular expression to find {{DATE}} and {{TIME}} functions in the payload and localize to the client.

`\{\{(DATE|TIME){1}\((.+?){1}(?:,\s*(Short|Long){1}\s*)??\)\}\} `

