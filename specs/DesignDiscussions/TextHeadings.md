# Text Headings

Need to indicate to screen reader software that certain text acts as a heading, for accessible card navigation.

![Sample Card with Headings](https://user-images.githubusercontent.com/4442788/110691207-db662b80-81b2-11eb-9265-856d1885ad64.png)

Web - `<h2>` or `aria-level="2"` supports levels 1-6 (though aria-level has no max, per spec)

UWP - [`AutomationHeadingLevel.HeadingLevel2`](https://docs.microsoft.com/en-us/uwp/api/windows.ui.xaml.automation.automationproperties.headinglevelproperty) supports levels 1-9

Android - [`android:accessibilityHeading="true"`](https://developer.android.com/guide/topics/ui/accessibility/principles#headings_within_text) no level support

iOS - [`UIAccessibilityTraitHeader`]() no level support

## Outcome

Add `style` property with enum options `Paragraph` (default) and `Heading` to the `TextBlock` element. (See various usages of this property: Input.Text.style, Action.x.style, Container.style, Column.style, Image.style, Input.ChoiceSet.style). When set to `Heading`, renderers must surface that to the platform's accessibility tree. Will need discussion with Accessibility team to confirm what the default heading-level should be on desktop platforms, and whether this binary option is sufficient for our purpose.

```json
{
    "type": "AdaptiveCard",
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "version": "1.3",
    "body": [
        {
            "type": "TextBlock",
            "text": "Lorem Ipsum",
            "style": "heading"
        },
        {
            "type": "TextBlock",
            "text": "dolor sit amet"
        },
        {
            "type": "TextBlock",
            "text": "Consectetur adipiscing elit",
            "style": "heading"
        },
        {
            "type": "TextBlock",
            "text": "sed do eiusmod tempor incididunt",
            "style": "paragraph"
        }
    ]
}
```

## Other options considered

### A.) No Schema Change

As `TextBlock` already renders Markdown, there is already a way for card authors to convey that certain text is a heading. Each renderer would have to correctly surface this information to the platform's accessibility tree.

* Commonmark has two formats for headings - leading `#` or underlined by `===`/`---` (see below card)
* Supports heading levels 1-6 (only levels 1 & 2 with underline syntax)
* Though awkward, can technically mix-and-match headings and paragraphs at once, so a single TextBlock can contain an entire passage
* Authors are forced to accept the larger styling associated with a heading. They cannot choose to expose regularly styled text as a heading to screen readers.

```json
{
    "type": "AdaptiveCard",
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "version": "1.3",
    "body": [
        {
            "type": "TextBlock",
            "text": "## Lorem Ipsum"
        },
        {
            "type": "TextBlock",
            "text": "dolor sit amet"
        },
        {
            "type": "TextBlock",
            "text": "## Consectetur adipiscing elit\nsed do eiusmod tempor incididunt\n\nUt labore et dolore\n---\nmagna aliqua"
        }
    ]
}
```


### B.) Add property to `TextBlock` and `TextRun`

Add a `headingLevel` property to TextBlock. Zero and negative numbers indicate regular text (non-headings). Any positive number is acceptable. If number exceeds platform's max level, that max level will be used.

* Unlimited heading levels
* With TextRun, authors can decouple heading role from text size/weight, and additionally able to add rich text styling to headings

```json
{
    "type": "AdaptiveCard",
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "version": "1.3",
    "body": [
        {
            "type": "TextBlock",
            "text": "Lorem Ipsum",
            "headingLevel": 2,
        },
        {
            "type": "TextBlock",
            "text": "dolor sit amet"
        },
        {
            "type": "RichTextBlock",
            "inlines": [
                {
                    "type": "TextRun",
                    "text": "Consectetur adipiscing elit",
                    "headingLevel": 2
                },

                {
                    "type": "TextRun",
                    "text": "sed do eiusmod tempor incididunt"
                },
                {
                    "type": "TextRun",
                    "text": "Ut labore et dolore",
                    "headingLevel": 2
                },
                {
                    "type": "TextRun",
                    "text": "magna aliqua"
                }
            ]
        }
    ]
}
```

### C.) Add property to `TextRun` only

Use above option B. only for `TextRun`, and combine with option A. for `TextBlock`. This avoids adding conflict between Markdown and our property in `TextBlock`, while still allowing `RichTextBlock` to contain headings.
