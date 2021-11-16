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

\+ **new Strings**(): [_Strings_](strings.strings-1.md)

**Returns:** [_Strings_](strings.strings-1.md)

## Properties

### defaults

▪ `Readonly` `Static` **defaults**: _object_

#### Type declaration:

| Name                | Type           |
| :------------------ | :------------- |
| `inlineActionTitle` | () => _string_ |

Defined in: [strings.ts:37](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/strings.ts#L37)

---

### errors

▪ `Readonly` `Static` **errors**: _object_

#### Type declaration:

| Name                                    | Type                                                                                                            |
| :-------------------------------------- | :-------------------------------------------------------------------------------------------------------------- |
| `actionAlreadyParented`                 | () => _string_                                                                                                  |
| `actionHttpHeadersMustHaveNameAndValue` | () => _string_                                                                                                  |
| `actionTypeNotAllowed`                  | (`typeName`: _string_) => _string_                                                                              |
| `choiceSetChoicesMustHaveTitleAndValue` | () => _string_                                                                                                  |
| `choiceSetMustHaveAtLeastOneChoice`     | () => _string_                                                                                                  |
| `columnAlreadyBelongsToAnotherSet`      | () => _string_                                                                                                  |
| `duplicateId`                           | (`id`: _string_) => _string_                                                                                    |
| `elementAlreadyParented`                | () => _string_                                                                                                  |
| `elementCannotBeUsedAsInline`           | () => _string_                                                                                                  |
| `elementTypeNotAllowed`                 | (`typeName`: _string_) => _string_                                                                              |
| `elementTypeNotStandalone`              | (`typeName`: _string_) => _string_                                                                              |
| `indexOutOfRange`                       | (`index`: _number_) => _string_                                                                                 |
| `inlineAlreadyParented`                 | () => _string_                                                                                                  |
| `inputsMustHaveUniqueId`                | () => _string_                                                                                                  |
| `interactivityNotAllowed`               | () => _string_                                                                                                  |
| `invalidCardType`                       | () => _string_                                                                                                  |
| `invalidCardVersion`                    | (`defaultingToVersion`: _string_) => _string_                                                                   |
| `invalidColumnWidth`                    | (`invalidWidth`: _string_) => _string_                                                                          |
| `invalidPropertyValue`                  | (`value`: _any_, `propertyName`: _string_) => _string_                                                          |
| `invalidVersionString`                  | (`versionString`: _string_) => _string_                                                                         |
| `markdownProcessingNotEnabled`          | () => _string_                                                                                                  |
| `processMarkdownEventRemoved`           | () => _string_                                                                                                  |
| `propertyMustBeSet`                     | (`propertyName`: _string_) => _string_                                                                          |
| `propertyNotSupported`                  | (`propertyName`: _string_, `supportedInVersion`: _string_, `versionUsed`: _string_) => _string_                 |
| `propertyValueNotSupported`             | (`value`: _any_, `propertyName`: _string_, `supportedInVersion`: _string_, `versionUsed`: _string_) => _string_ |
| `showCardMustHaveCard`                  | () => _string_                                                                                                  |
| `tooManyActions`                        | (`maximumActions`: _number_) => _string_                                                                        |
| `unknownActionType`                     | (`typeName`: _string_) => _string_                                                                              |
| `unknownElementType`                    | (`typeName`: _string_) => _string_                                                                              |
| `unsupportedCardVersion`                | (`version`: _string_, `maxSupportedVersion`: _string_) => _string_                                              |

Defined in: [strings.ts:2](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/strings.ts#L2)

---

### hints

▪ `Readonly` `Static` **hints**: _object_

#### Type declaration:

| Name                                          | Type           |
| :-------------------------------------------- | :------------- |
| `dontUseWeightedAndStrecthedColumnsInSameSet` | () => _string_ |

Defined in: [strings.ts:34](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/strings.ts#L34)
