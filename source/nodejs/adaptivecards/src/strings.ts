export class Strings {
    static readonly errors = {
        unknownElementType: "Unknown element type \"{0}\". Fallback will be used if present.",
        unknownActionType: "Unknown action type \"{0}\". Fallback will be used if present.",
        elementTypeNotAllowed: "Element type \"{0}\" is not allowed in this context.",
        actionTypeNotAllowed: "Action type \"{0}\" is not allowed in this context.",
        invalidPropertyValue: "Invalid value \"{0}\" for property \"{1}\"",
        showCardMustHaveCard: "An Action.ShowCard must have its \"card\" property set to a valid AdaptiveCard object.",
        invalidColumnWidth: "Invalid column width \"{0}\" - defaulting to \"auto\"",
        invalidCardVersion: "Invalid card version. Defaulting to \"{0}\"",
        invalidVersionString: "Invalid version string \"{0}\"",
        propertyValueNotSupported: "Value \"{0}\" for property \"{1}\" is supported in version {2}, but you are using version {3}",
        propertyNotSupported: "`Property \"{0}\" is supported in version {1}, but you are using version {2}",
        indexOutOfRange: "Index out of range ({0}).",
        elementCannotBeUsedAsInline: "RichTextBlock.addInline: the specified card element cannot be used as a RichTextBlock inline.",
        inlineAlreadyParented: "RichTextBlock.addInline: the specified inline already belongs to another RichTextBlock.",
        interactivityNotAllowed: "Interactivity is not allowed.",
        inputsMustHaveUniqueId: "All inputs must have a unique Id.",
        choiceSetMustHaveAtLeastOneChoice: "An Input.ChoiceSet must have at least one choice defined.",
        choiceSetChoicesMustHaveTitleAndValue: "All choices in an Input.ChoiceSet must have their title and value properties set.",
        propertyMustBeSet: "Property \"{0}\" must be set.",
        actionHttpHeadersMustHaveNameAndValue: "All headers of an Action.Http must have their name and value properties set.",
        tooManyActions: "Maximum number of actions exceeded ({0}).",
        columnAlreadyBelongsToAnotherSet: "This column already belongs to another ColumnSet.",
        invalidCardType: "Invalid or missing card type. Make sure the card's type property is set to \"AdaptiveCard\".",
        unsupportedCardVersion: "The specified card version ({0}) is not supported. The maximum supported card version is {1}",
        duplicateId: "Duplicate Id \"{0}\"",
        markdownProcessingNotEnabled: "Markdown processing isn't enabled. Please see https://www.npmjs.com/package/adaptivecards#supporting-markdown",
        processMarkdownEventRemoved: "The processMarkdown event has been removed. Please update your code and set onProcessMarkdown instead.",
        elementAlreadyParented: "The element already belongs to another container.",
        actionAlreadyParented: "The action already belongs to another element.",
        elementTypeNotStandalone: "Elements of type {0} cannot be used as standalone elements."
    };
    static readonly hints = {
        dontUseWeightedAndStrecthedColumnsInSameSet: "It is not recommended to use weighted and stretched columns in the same ColumnSet, because in such a situation stretched columns will always get the minimum amount of space."
    }
}
