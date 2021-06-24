[Adaptive Cards Javascript SDK](../README.md) / [strings](../modules/strings.md) / Strings

# Class: Strings

[strings](../modules/strings.md).Strings

## Table of contents

### Constructors

- [constructor](strings.strings-1.md#constructor)

### Properties

- [defaults](strings.strings-1.md#defaults)
- [errors](strings.strings-1.md#errors)
- [hints](strings.strings-1.md#hints)

## Constructors

### constructor

\+ **new Strings**(): [*Strings*](strings.strings-1.md)

**Returns:** [*Strings*](strings.strings-1.md)

## Properties

### defaults

▪ `Readonly` `Static` **defaults**: *object*

#### Type declaration:

Name | Type |
:------ | :------ |
`inlineActionTitle` | () => *string* |

Defined in: [strings.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/strings.ts#L37)

___

### errors

▪ `Readonly` `Static` **errors**: *object*

#### Type declaration:

Name | Type |
:------ | :------ |
`actionAlreadyParented` | () => *string* |
`actionHttpHeadersMustHaveNameAndValue` | () => *string* |
`actionTypeNotAllowed` | (`typeName`: *string*) => *string* |
`choiceSetChoicesMustHaveTitleAndValue` | () => *string* |
`choiceSetMustHaveAtLeastOneChoice` | () => *string* |
`columnAlreadyBelongsToAnotherSet` | () => *string* |
`duplicateId` | (`id`: *string*) => *string* |
`elementAlreadyParented` | () => *string* |
`elementCannotBeUsedAsInline` | () => *string* |
`elementTypeNotAllowed` | (`typeName`: *string*) => *string* |
`elementTypeNotStandalone` | (`typeName`: *string*) => *string* |
`indexOutOfRange` | (`index`: *number*) => *string* |
`inlineAlreadyParented` | () => *string* |
`inputsMustHaveUniqueId` | () => *string* |
`interactivityNotAllowed` | () => *string* |
`invalidCardType` | () => *string* |
`invalidCardVersion` | (`defaultingToVersion`: *string*) => *string* |
`invalidColumnWidth` | (`invalidWidth`: *string*) => *string* |
`invalidPropertyValue` | (`value`: *any*, `propertyName`: *string*) => *string* |
`invalidVersionString` | (`versionString`: *string*) => *string* |
`markdownProcessingNotEnabled` | () => *string* |
`processMarkdownEventRemoved` | () => *string* |
`propertyMustBeSet` | (`propertyName`: *string*) => *string* |
`propertyNotSupported` | (`propertyName`: *string*, `supportedInVersion`: *string*, `versionUsed`: *string*) => *string* |
`propertyValueNotSupported` | (`value`: *any*, `propertyName`: *string*, `supportedInVersion`: *string*, `versionUsed`: *string*) => *string* |
`showCardMustHaveCard` | () => *string* |
`tooManyActions` | (`maximumActions`: *number*) => *string* |
`unknownActionType` | (`typeName`: *string*) => *string* |
`unknownElementType` | (`typeName`: *string*) => *string* |
`unsupportedCardVersion` | (`version`: *string*, `maxSupportedVersion`: *string*) => *string* |

Defined in: [strings.ts:2](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/strings.ts#L2)

___

### hints

▪ `Readonly` `Static` **hints**: *object*

#### Type declaration:

Name | Type |
:------ | :------ |
`dontUseWeightedAndStrecthedColumnsInSameSet` | () => *string* |

Defined in: [strings.ts:34](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/strings.ts#L34)
