[Adaptive Cards Javascript SDK](README.md)

# Adaptive Cards Javascript SDK

## Index

### Enumerations

* [ActionAlignment](enums/actionalignment.md)
* [ActionIconPlacement](enums/actioniconplacement.md)
* [ContainerFitStatus](enums/containerfitstatus.md)
* [FillMode](enums/fillmode.md)
* [FontType](enums/fonttype.md)
* [HorizontalAlignment](enums/horizontalalignment.md)
* [ImageStyle](enums/imagestyle.md)
* [InputTextStyle](enums/inputtextstyle.md)
* [InputValidationNecessity](enums/inputvalidationnecessity.md)
* [Orientation](enums/orientation.md)
* [ShowCardActionMode](enums/showcardactionmode.md)
* [Size](enums/size.md)
* [SizeUnit](enums/sizeunit.md)
* [Spacing](enums/spacing.md)
* [TextColor](enums/textcolor.md)
* [TextSize](enums/textsize.md)
* [TextWeight](enums/textweight.md)
* [ValidationError](enums/validationerror.md)
* [VerticalAlignment](enums/verticalalignment.md)

### Classes

* [Action](classes/action.md)
* [ActionSet](classes/actionset.md)
* [ActionStyle](classes/actionstyle.md)
* [ActionTypeRegistry](classes/actiontyperegistry.md)
* [ActionsConfig](classes/actionsconfig.md)
* [AdaptiveCard](classes/adaptivecard.md)
* [AdaptiveCardConfig](classes/adaptivecardconfig.md)
* [BackgroundImage](classes/backgroundimage.md)
* [BaseTextBlock](classes/basetextblock.md)
* [CardElement](classes/cardelement.md)
* [CardElementContainer](classes/cardelementcontainer.md)
* [CardObject](classes/cardobject.md)
* [Choice](classes/choice.md)
* [ChoiceSetInput](classes/choicesetinput.md)
* [ColorDefinition](classes/colordefinition.md)
* [ColorSetDefinition](classes/colorsetdefinition.md)
* [Column](classes/column.md)
* [ColumnSet](classes/columnset.md)
* [Container](classes/container.md)
* [ContainerStyle](classes/containerstyle.md)
* [ContainerStyleDefinition](classes/containerstyledefinition.md)
* [ContainerStyleSet](classes/containerstyleset.md)
* [ContainerWithActions](classes/containerwithactions.md)
* [DateInput](classes/dateinput.md)
* [ElementTypeRegistry](classes/elementtyperegistry.md)
* [Fact](classes/fact.md)
* [FactSet](classes/factset.md)
* [FactSetConfig](classes/factsetconfig.md)
* [FactTextDefinition](classes/facttextdefinition.md)
* [FactTitleDefinition](classes/facttitledefinition.md)
* [FontTypeDefinition](classes/fonttypedefinition.md)
* [FontTypeSet](classes/fonttypeset.md)
* [HostCapabilities](classes/hostcapabilities.md)
* [HostConfig](classes/hostconfig.md)
* [HttpAction](classes/httpaction.md)
* [HttpHeader](classes/httpheader.md)
* [Image](classes/image.md)
* [ImageSet](classes/imageset.md)
* [ImageSetConfig](classes/imagesetconfig.md)
* [Input](classes/input.md)
* [InputValidationOptions](classes/inputvalidationoptions.md)
* [Media](classes/media.md)
* [MediaConfig](classes/mediaconfig.md)
* [MediaSource](classes/mediasource.md)
* [NumberInput](classes/numberinput.md)
* [OpenUrlAction](classes/openurlaction.md)
* [PaddingDefinition](classes/paddingdefinition.md)
* [RichTextBlock](classes/richtextblock.md)
* [SerializableObject](classes/serializableobject.md)
* [ShowCardAction](classes/showcardaction.md)
* [ShowCardActionConfig](classes/showcardactionconfig.md)
* [SizeAndUnit](classes/sizeandunit.md)
* [SpacingDefinition](classes/spacingdefinition.md)
* [StringWithSubstitutions](classes/stringwithsubstitutions.md)
* [StylableCardElementContainer](classes/stylablecardelementcontainer.md)
* [SubmitAction](classes/submitaction.md)
* [TextBlock](classes/textblock.md)
* [TextColorDefinition](classes/textcolordefinition.md)
* [TextInput](classes/textinput.md)
* [TextRun](classes/textrun.md)
* [TimeInput](classes/timeinput.md)
* [ToggleInput](classes/toggleinput.md)
* [ToggleVisibilityAction](classes/togglevisibilityaction.md)
* [TypeRegistry](classes/typeregistry.md)
* [UUID](classes/uuid.md)
* [ValidationFailure](classes/validationfailure.md)
* [ValidationResults](classes/validationresults.md)
* [Version](classes/version.md)

### Interfaces

* [IAdaptiveCard](interfaces/iadaptivecard.md)
* [ICardElement](interfaces/icardelement.md)
* [IFontSizeDefinitions](interfaces/ifontsizedefinitions.md)
* [IFontWeightDefinitions](interfaces/ifontweightdefinitions.md)
* [IInput](interfaces/iinput.md)
* [ILineHeightDefinitions](interfaces/ilineheightdefinitions.md)
* [IMarkdownProcessingResult](interfaces/imarkdownprocessingresult.md)
* [IResourceInformation](interfaces/iresourceinformation.md)
* [ISeparationDefinition](interfaces/iseparationdefinition.md)
* [ITypeRegistration](interfaces/ityperegistration.md)
* [IValidationError](interfaces/ivalidationerror.md)

### Type aliases

* [CardElementHeight](README.md#cardelementheight)
* [ColumnWidth](README.md#columnwidth)
* [Dictionary](README.md#dictionary)
* [HostCapabilityMap](README.md#hostcapabilitymap)
* [HostCapabilityVersion](README.md#hostcapabilityversion)

### Functions

* [appendChild](README.md#appendchild)
* [createActionInstance](README.md#createactioninstance)
* [createElementInstance](README.md#createelementinstance)
* [generateUniqueId](README.md#generateuniqueid)
* [getBoolValue](README.md#getboolvalue)
* [getEnumValue](README.md#getenumvalue)
* [getFitStatus](README.md#getfitstatus)
* [getNumberValue](README.md#getnumbervalue)
* [getStringValue](README.md#getstringvalue)
* [isNullOrEmpty](README.md#isnullorempty)
* [parseHostConfigEnum](README.md#parsehostconfigenum)
* [renderSeparation](README.md#renderseparation)
* [setArrayProperty](README.md#setarrayproperty)
* [setEnumProperty](README.md#setenumproperty)
* [setNumberProperty](README.md#setnumberproperty)
* [setProperty](README.md#setproperty)
* [stringToCssColor](README.md#stringtocsscolor)
* [truncate](README.md#truncate)

### Object literals

* [ContentTypes](README.md#const-contenttypes)

## Type aliases

###  CardElementHeight

Ƭ **CardElementHeight**: *"auto" | "stretch"*

*Defined in [card-elements.ts:293](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L293)*

___

###  ColumnWidth

Ƭ **ColumnWidth**: *[SizeAndUnit](classes/sizeandunit.md) | "auto" | "stretch"*

*Defined in [card-elements.ts:5819](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L5819)*

___

###  Dictionary

Ƭ **Dictionary**: *object*

*Defined in [shared.ts:22](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L22)*

#### Type declaration:

* \[ **key**: *string*\]: T

___

###  HostCapabilityMap

Ƭ **HostCapabilityMap**: *object*

*Defined in [host-config.ts:479](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L479)*

#### Type declaration:

* \[ **key**: *string*\]: [HostCapabilityVersion](README.md#hostcapabilityversion)

___

###  HostCapabilityVersion

Ƭ **HostCapabilityVersion**: *[Version](classes/version.md) | "*"*

*Defined in [host-config.ts:478](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L478)*

## Functions

###  appendChild

▸ **appendChild**(`node`: Node, `child`: Node): *void*

*Defined in [utils.ts:25](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L25)*

Appends `child` to `node` if `child` is valid

**Parameters:**

Name | Type |
------ | ------ |
`node` | Node |
`child` | Node |

**Returns:** *void*

___

###  createActionInstance

▸ **createActionInstance**(`parent`: [CardElement](classes/cardelement.md), `json`: any, `forbiddenActionTypes`: string[], `allowFallback`: boolean, `errors`: Array‹[IValidationError](interfaces/ivalidationerror.md)›): *[Action](classes/action.md)*

*Defined in [card-elements.ts:99](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L99)*

Instantiates an [`Action`](classes/action.md) for a [`CardElement`](classes/cardelement.md)

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`parent` | [CardElement](classes/cardelement.md) | The [`CardElement`](classes/cardelement.md) for which to create an [`Action`](classes/action.md) |
`json` | any | A json object containing [`Action`](classes/action.md) properties |
`forbiddenActionTypes` | string[] | A list of action types that are not allowed to be created |
`allowFallback` | boolean | Whether to allow element fallback to occur |
`errors` | Array‹[IValidationError](interfaces/ivalidationerror.md)› | A list of validation errors encountered while parsing the action  |

**Returns:** *[Action](classes/action.md)*

___

###  createElementInstance

▸ **createElementInstance**(`parent`: [CardElement](classes/cardelement.md), `json`: any, `allowFallback`: boolean, `errors`: Array‹[IValidationError](interfaces/ivalidationerror.md)›): *[CardElement](classes/cardelement.md)*

*Defined in [card-elements.ts:135](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/card-elements.ts#L135)*

Instantiates a [`CardElement`](classes/cardelement.md)

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`parent` | [CardElement](classes/cardelement.md) | The parent of this [`CardElement`](classes/cardelement.md) |
`json` | any | A json object containing [`CardElement`](classes/cardelement.md) properties |
`allowFallback` | boolean | Whether to allow element fallback to occur |
`errors` | Array‹[IValidationError](interfaces/ivalidationerror.md)› | A list of validation errors encountered while parsing the action  |

**Returns:** *[CardElement](classes/cardelement.md)*

___

###  generateUniqueId

▸ **generateUniqueId**(): *string*

*Defined in [utils.ts:10](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L10)*

Generate a UUID prepended with "__ac-"

**Returns:** *string*

___

###  getBoolValue

▸ **getBoolValue**(`value`: any, `defaultValue`: boolean): *boolean*

*Defined in [utils.ts:48](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L48)*

**Parameters:**

Name | Type |
------ | ------ |
`value` | any |
`defaultValue` | boolean |

**Returns:** *boolean*

`value` if it's a `boolean` or if it's `"true"` or `"false"`. Otherwise returns `defaultValue || undefined`

___

###  getEnumValue

▸ **getEnumValue**(`targetEnum`: object, `name`: string, `defaultValue`: number): *number*

*Defined in [utils.ts:82](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L82)*

Convert from a `string` to an `enum` value
``` typescript
enum Test {
     Pass,
     Fail,
     Unknown
}
getEnumValue(Test, "Fail", Test.Unknown); // returns 1 (Test.Fail)
getEnumValue(Test, "Not an enum value", Test.Unknown); // returns 2 (Test.Unknown)
```

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`targetEnum` | object | `enum` to resolve against |
`name` | string | `string` to look up |
`defaultValue` | number | value to use if lookup fails |

**Returns:** *number*

Numeric `enum` value if lookup succeeded. Otherwise `defaultValue`

___

###  getFitStatus

▸ **getFitStatus**(`element`: HTMLElement, `containerEnd`: number): *[ContainerFitStatus](enums/containerfitstatus.md)*

*Defined in [utils.ts:325](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L325)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |
`containerEnd` | number |

**Returns:** *[ContainerFitStatus](enums/containerfitstatus.md)*

___

###  getNumberValue

▸ **getNumberValue**(`obj`: any, `defaultValue`: number): *number*

*Defined in [utils.ts:41](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L41)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`obj` | any | - |
`defaultValue` | number | undefined |

**Returns:** *number*

`obj` if `obj` is of type `number`. Otherwise, returns `defaultValue || undefined`

___

###  getStringValue

▸ **getStringValue**(`obj`: any, `defaultValue`: string): *string*

*Defined in [utils.ts:34](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L34)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`obj` | any | - |
`defaultValue` | string | undefined |

**Returns:** *string*

`obj.toString()` if `obj` is of type `string`. Otherwise, returns `defaultValue || undefined`

___

###  isNullOrEmpty

▸ **isNullOrEmpty**(`value`: string): *boolean*

*Defined in [utils.ts:18](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L18)*

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`value` | string | string to test |

**Returns:** *boolean*

`true` if `string` is `undefined`, `null`, or `""`

___

###  parseHostConfigEnum

▸ **parseHostConfigEnum**(`targetEnum`: object, `value`: string | number, `defaultValue`: any): *any*

*Defined in [utils.ts:175](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L175)*

**Parameters:**

Name | Type |
------ | ------ |
`targetEnum` | object |
`value` | string &#124; number |
`defaultValue` | any |

**Returns:** *any*

___

###  renderSeparation

▸ **renderSeparation**(`hostConfig`: [HostConfig](classes/hostconfig.md), `separationDefinition`: [ISeparationDefinition](interfaces/iseparationdefinition.md), `orientation`: [Orientation](enums/orientation.md)): *HTMLElement*

*Defined in [utils.ts:187](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L187)*

**Parameters:**

Name | Type |
------ | ------ |
`hostConfig` | [HostConfig](classes/hostconfig.md) |
`separationDefinition` | [ISeparationDefinition](interfaces/iseparationdefinition.md) |
`orientation` | [Orientation](enums/orientation.md) |

**Returns:** *HTMLElement*

___

###  setArrayProperty

▸ **setArrayProperty**(`target`: object, `propertyName`: string, `propertyValue`: any[]): *void*

*Defined in [utils.ts:156](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L156)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | object |
`propertyName` | string |
`propertyValue` | any[] |

**Returns:** *void*

___

###  setEnumProperty

▸ **setEnumProperty**(`enumType`: object, `target`: object, `propertyName`: string, `propertyValue`: number, `defaultValue`: number): *void*

*Defined in [utils.ts:134](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L134)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`enumType` | object | - |
`target` | object | - |
`propertyName` | string | - |
`propertyValue` | number | - |
`defaultValue` | number | undefined |

**Returns:** *void*

___

###  setNumberProperty

▸ **setNumberProperty**(`target`: object, `propertyName`: string, `propertyValue`: number, `defaultValue`: number): *void*

*Defined in [utils.ts:125](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L125)*

**Parameters:**

Name | Type | Default | Description |
------ | ------ | ------ | ------ |
`target` | object | - | `object` to set property on |
`propertyName` | string | - | Name of property to set |
`propertyValue` | number | - | Value to set property to |
`defaultValue` | number | undefined | Value to use if `propertyValue` isn't valid  |

**Returns:** *void*

___

###  setProperty

▸ **setProperty**(`target`: object, `propertyName`: string, `propertyValue`: any, `defaultValue`: any): *void*

*Defined in [utils.ts:110](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L110)*

**Parameters:**

Name | Type | Default | Description |
------ | ------ | ------ | ------ |
`target` | object | - | `object` to set property on |
`propertyName` | string | - | Name of property to set |
`propertyValue` | any | - | Value to set property to |
`defaultValue` | any | undefined | Value to use if `propertyValue` isn't valid  |

**Returns:** *void*

___

###  stringToCssColor

▸ **stringToCssColor**(`color`: string): *string*

*Defined in [utils.ts:222](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L222)*

**Parameters:**

Name | Type |
------ | ------ |
`color` | string |

**Returns:** *string*

___

###  truncate

▸ **truncate**(`element`: HTMLElement, `maxHeight`: number, `lineHeight?`: number): *void*

*Defined in [utils.ts:240](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/utils.ts#L240)*

**Parameters:**

Name | Type |
------ | ------ |
`element` | HTMLElement |
`maxHeight` | number |
`lineHeight?` | number |

**Returns:** *void*

## Object literals

### `Const` ContentTypes

### ▪ **ContentTypes**: *object*

*Defined in [shared.ts:5](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L5)*

###  applicationJson

• **applicationJson**: *string* = "application/json"

*Defined in [shared.ts:6](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L6)*

###  applicationXWwwFormUrlencoded

• **applicationXWwwFormUrlencoded**: *string* = "application/x-www-form-urlencoded"

*Defined in [shared.ts:7](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/shared.ts#L7)*
