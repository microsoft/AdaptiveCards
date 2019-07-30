# InputValidation

## Proposal Link
https://github.com/microsoft/AdaptiveCards/issues/3051

## Dependencies
No dependencies required

## Rendering

### UWP & .NET WPF

TextBlock has a property called [TextDecorations](https://docs.microsoft.com/en-us/uwp/api/windows.ui.xaml.controls.textblock.textdecorations) which include Underline

### Android

#### TextBlock

TextBlocks are rendered using TextViews, TextView has a property called PaintFlags which include [Paint.UNDERLINE_TEXT_FLAG](https://developer.android.com/reference/android/graphics/Paint)

#### RichTextBlock

TextRuns are rendered using SpannableStrings, between the possible spans to use there is [UnderlineSpan](https://developer.android.com/reference/android/text/style/UnderlineSpan) 

### iOS

NSMutableAttributedString are able to set underlines in the whole text and in some specific ranges using [NSUnderlineStyle](https://developer.apple.com/documentation/uikit/nsunderlinestyle)

### .NET HTML

The \<u> tag allows underlining

## Backwards Compatibility Concerns
Underline will be ignored if sent to an older version of the renderer. No breaking changes are introduced.

## Warning and Error States
None

## Open Issues
May include multiple line underlining at some point

## Testing

### Object Model
All Object model test suites should be updated to validate the new property. 

#### Test suites that should be updated:
- Shared model, via the EverythingBagel tests.
- UWP Object Model unit tests
- Android object model tests.

### Samples
The following samples will be added to validate rendering:
- TextBlock.Underline.json file which contains TextBlock with underline
- RichTextRun.Underline.json file which contains a RichTextBlock that contains a TextRun with underline