# Inconsistent Whitspace handling in Markdown 

## Related Issues

1. [#4914](https://github.com/microsoft/AdaptiveCards/issues/4914),
   **Closed [#3531](https://github.com/microsoft/AdaptiveCards/issues/3531)**, 
   [#3016](https://github.com/microsoft/AdaptiveCards/issues/3016)
   [#2842](https://github.com/microsoft/AdaptiveCards/issues/2842)

## Current State
1.	Leading and trailing whitespace characters
    - Some renderers trim leading and trailing  new line characters while others do not.
2.	New line characters in the middle of the text 
    -	Some renderers take two consecutive new line characters in the middle of the string to add a line break in TextBlock while others take just single new line char.
3.	Markdown collapses multiple consecutive spaces within a string into a single one
4.	Inconsistent handling of new line chars between RichTextBlock and TextBlock in the same renderer.
5.  These inconsistencies are due to the differences in the Markdown we are using.
6. There is also differences in whitespace character handling per platforms

## Options
1. Stay the current course 
2. Change JS's Markdown
3. Update SharedModel's Markdown

## Markdown WhiteSpace Handling
With option 3, we can solve the most of the issues; however, we have to investigate that the markdwon processed output produce consistent results across the platform which is tracked by [#5380](https://github.com/microsoft/AdaptiveCards/issues/5380)

### Blocks and Inlines
1. Markdown sees the document consisted of `Block` and `inline` according to [CommonMark Spec](https://spec.commonmark.org/0.29/#blocks-and-inlines).
    -   Blocks are structural elements like paragraphs, block quotations, lists, headings, rules, and code blocks and may contain *inline* content, blocks are further divded into container blocks and leaf blocks
        - **container blocks** can contain other blocks, lists
        - **leaf blocks** cannot, paragraphs
    -  inlines are links, emphasized text, images, code spans
### Scoping
Updating markdowns in shared models will update the handling whitespace characters for  
1. Blocks
    - **leaf blocks**: **paragraphs**, **container blocks**: **lists**
2. Inline
    - links, **empahsized text**
### Rules
The rules below should be respected whenever applicable to the elements mentioned in the Scoping section. Rules section will be expanded to include for inlines and lists in the future update. 
- A **line ending** is a newline (U+000A), a carriage return (U+000D) not followed by a newline, or a carriage return and a following newline.
- **blankline**, a line containing no characters, or a line containing only spaces (U+0020) or tabs (U+0009),
- **whitespace character**, a space (U+0020), tab (U+0009), newline (U+000A), line tabulation (U+000B), form feed (U+000C), or carriage return (U+000D).
- **Unicode whitespace character**, any code point in the Unicode Zs general category, or a tab (U+0009), carriage return (U+000D), newline (U+000A), or form feed (U+000C). 
- **line**, a sequence of zero or more characters other than newline (U+000A) or carriage return (U+000D), followed by a line ending or by the end of file. 
- **paragraphs**, sequences of non-blank lines that cannot be interpreted as other kinds of blocks. The contents of the paragraph are the result of parsing the paragraph’s raw content as inlines. *The paragraph’s raw content is formed by concatenating the lines and removing initial and final whitespace.*Paragraphs can contain multiple lines, but no blank lines:
   1. Paragraphs can contain multiple lines, but no blank lines
   2. Multiple blank lines between paragraph have no effect
   3. Leading spaces are skipped
   4. Lines after the first may be indented any amount
   5. the first line may be indented at most three spaces, or an indented code block will be triggered <-- we may have to skip this rule
   6. Final spaces are stripped before inline parsing, so a paragraph that ends with two or more spaces will not end with a hard line break:

### Implementation 
#### Option 1
1. Antlr Integration
2. Antlr Lexer
    * writing lexer rules 
3. Update Parser Rules
#### Option 2
1. Make core changes to Shared models to gain the behavior we want 

## Conculsion
We chose implementation option 2 to control the risk associated with the unknowns.  

1. Bring consisteny between Android and JS by removing android code that pulls newlines from rich text blocks. It also fiexes [#4914](https://github.com/microsoft/AdaptiveCards/issues/4914).

2. [Update shared model markdown processor to handle markdown whitespace](https://github.com/microsoft/AdaptiveCards/issues/5380)
   - Make sure alll platforms are handling the whitespace characters that come out of the markdown parser properly.
    
3. [Document the new whitespace handling](https://github.com/microsoft/AdaptiveCards/issues/5381)
    
4. Remove markdown process from rich text blocks. No separate task, but should be part of the task 1.