// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// eslint-disable-next-line @typescript-eslint/no-extraneous-class
export class Strings {
    static readonly errors = {
        unknownElementType: (typeName: string) =>
            `Unknown element type "${typeName}". Fallback will be used if present.`,
        unknownActionType: (typeName: string) =>
            `Unknown action type "${typeName}". Fallback will be used if present.`,
        elementTypeNotAllowed: (typeName: string) =>
            `Element type "${typeName}" is not allowed in this context.`,
        actionTypeNotAllowed: (typeName: string) =>
            `Action type "${typeName}" is not allowed in this context.`,
        invalidPropertyValue: (value: any, propertyName: string) =>
            `Invalid value "${value}" for property "${propertyName}".`,
        showCardMustHaveCard: () =>
            `"An Action.ShowCard must have its "card" property set to a valid AdaptiveCard object.`,
        invalidColumnWidth: (invalidWidth: string) =>
            `Invalid column width "${invalidWidth}" - defaulting to "auto".`,
        invalidCardVersion: (defaultingToVersion: string) =>
            `Invalid card version. Defaulting to "${defaultingToVersion}".`,
        invalidVersionString: (versionString: string) =>
            `Invalid version string "${versionString}".`,
        propertyValueNotSupported: (
            value: any,
            propertyName: string,
            supportedInVersion: string,
            versionUsed: string
        ) =>
            `Value "${value}" for property "${propertyName}" is supported in version ${supportedInVersion}, but you are using version ${versionUsed}.`,
        propertyNotSupported: (
            propertyName: string,
            supportedInVersion: string,
            versionUsed: string
        ) =>
            `Property "${propertyName}" is supported in version ${supportedInVersion}, but you are using version ${versionUsed}.`,
        indexOutOfRange: (index: number) => `Index out of range (${index}).`,
        elementCannotBeUsedAsInline: () =>
            "RichTextBlock.addInline: the specified card element cannot be used as a RichTextBlock inline.",
        inlineAlreadyParented: () =>
            "RichTextBlock.addInline: the specified inline already belongs to another RichTextBlock.",
        interactivityNotAllowed: () => "Interactivity is not allowed.",
        inputsMustHaveUniqueId: () => "All inputs must have a unique Id.",
        choiceSetMustHaveAtLeastOneChoice: () =>
            "An Input.ChoiceSet must have at least one choice defined.",
        choiceSetChoicesMustHaveTitleAndValue: () =>
            "All choices in an Input.ChoiceSet must have their title and value properties set.",
        propertyMustBeSet: (propertyName: string) => `Property "${propertyName}" must be set.`,
        actionHttpHeadersMustHaveNameAndValue: () =>
            "All headers of an Action.Http must have their name and value properties set.",
        tooManyActions: (maximumActions: number) =>
            `Maximum number of actions exceeded (${maximumActions}).`,
        tooLittleTimeDelay: (minAutoplayDelay: number) =>
            `Autoplay Delay is too short (${minAutoplayDelay}).`,
        tooManyCarouselPages: (maxCarouselPages: number) =>
            `Maximum number of Carousel pages exceeded (${maxCarouselPages}).`,
        invalidInitialPageIndex: (initialPageIndex: number) =>
            `InitialPage for carousel is invalid (${initialPageIndex}).`,
        columnAlreadyBelongsToAnotherSet: () => "This column already belongs to another ColumnSet.",
        invalidCardType: () =>
            `Invalid or missing card type. Make sure the card's type property is set to "AdaptiveCard".`,
        unsupportedCardVersion: (version: string, maxSupportedVersion: string) =>
            `The specified card version (${version}) is not supported or still in preview. The latest released card version is ${maxSupportedVersion}.`,
        duplicateId: (id: string) => `Duplicate Id "${id}".`,
        markdownProcessingNotEnabled: () =>
            "Markdown processing isn't enabled. Please see https://www.npmjs.com/package/adaptivecards#supporting-markdown",
        processMarkdownEventRemoved: () =>
            "The processMarkdown event has been removed. Please update your code and set onProcessMarkdown instead.",
        elementAlreadyParented: () => "The element already belongs to another container.",
        actionAlreadyParented: () => "The action already belongs to another element.",
        elementTypeNotStandalone: (typeName: string) =>
            `Elements of type ${typeName} cannot be used as standalone elements.`,
        invalidInputLabelWidth: () =>
            `Invalid input label width. Defaulting to label width from host config.`,
    };
    static readonly magicCodeInputCard = {
        tryAgain: () => "That didn't work... let's try again.",
        pleaseLogin: () =>
            'Please login in the popup. You will obtain a magic code. Paste that code below and select "Submit"',
        enterMagicCode: () => "Enter magic code",
        pleaseEnterMagicCodeYouReceived: () => "Please enter the magic code you received.",
        submit: () => "Submit",
        cancel: () => "Cancel",
        somethingWentWrong: () => "Something went wrong. This action can't be handled.",
        authenticationFailed: () => "Authentication failed."
    };
    static readonly runtime = {
        automaticRefreshPaused: () => "Automatic refresh paused.",
        clckToRestartAutomaticRefresh: () => "Click to restart.",
        refreshThisCard: () => "Refresh this card"
    };
    static readonly hints = {
        dontUseWeightedAndStrecthedColumnsInSameSet: () =>
            "It is not recommended to use weighted and stretched columns in the same ColumnSet, because in such a situation stretched columns will always get the minimum amount of space."
    };
    static readonly defaults = {
        inlineActionTitle: () => "Inline Action",
        overflowButtonText: () => "...",
        overflowButtonTooltip: () => "More options",
        mediaPlayerAriaLabel: () => "Media content",
        mediaPlayerPlayMedia: () => "Play media",
        youTubeVideoPlayer: () => "YouTube video player",
        vimeoVideoPlayer: () => "Vimeo video player",
        dailymotionVideoPlayer: () => "Dailymotion video player",
        carouselNavigationPreviousTooltip: () => "Previous carousel page",
        carouselNavigationNextTooltip: () => "Next carousel page"
    };
}
