[Adaptive Cards Javascript SDK](../README.md) › [FactTitleDefinition](facttitledefinition.md)

# Class: FactTitleDefinition

## Hierarchy

* [FactTextDefinition](facttextdefinition.md)

  ↳ **FactTitleDefinition**

## Index

### Constructors

* [constructor](facttitledefinition.md#constructor)

### Properties

* [color](facttitledefinition.md#color)
* [isSubtle](facttitledefinition.md#issubtle)
* [maxWidth](facttitledefinition.md#optional-maxwidth)
* [size](facttitledefinition.md#size)
* [weight](facttitledefinition.md#weight)
* [wrap](facttitledefinition.md#wrap)

### Methods

* [getDefaultWeight](facttitledefinition.md#getdefaultweight)
* [toJSON](facttitledefinition.md#tojson)

## Constructors

###  constructor

\+ **new FactTitleDefinition**(`obj?`: any): *[FactTitleDefinition](facttitledefinition.md)*

*Overrides [FactTextDefinition](facttextdefinition.md).[constructor](facttextdefinition.md#constructor)*

*Defined in [host-config.ts:128](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L128)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[FactTitleDefinition](facttitledefinition.md)*

## Properties

###  color

• **color**: *[TextColor](../enums/textcolor.md)* = Enums.TextColor.Default

*Inherited from [FactTextDefinition](facttextdefinition.md).[color](facttextdefinition.md#color)*

*Defined in [host-config.ts:96](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L96)*

___

###  isSubtle

• **isSubtle**: *boolean* = false

*Inherited from [FactTextDefinition](facttextdefinition.md).[isSubtle](facttextdefinition.md#issubtle)*

*Defined in [host-config.ts:97](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L97)*

___

### `Optional` maxWidth

• **maxWidth**? : *number* = 150

*Defined in [host-config.ts:127](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L127)*

___

###  size

• **size**: *[TextSize](../enums/textsize.md)* = Enums.TextSize.Default

*Inherited from [FactTextDefinition](facttextdefinition.md).[size](facttextdefinition.md#size)*

*Defined in [host-config.ts:95](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L95)*

___

###  weight

• **weight**: *[TextWeight](../enums/textweight.md)* = Enums.TextWeight.Bolder

*Overrides [FactTextDefinition](facttextdefinition.md).[weight](facttextdefinition.md#weight)*

*Defined in [host-config.ts:128](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L128)*

___

###  wrap

• **wrap**: *boolean* = true

*Inherited from [FactTextDefinition](facttextdefinition.md).[wrap](facttextdefinition.md#wrap)*

*Defined in [host-config.ts:99](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L99)*

## Methods

###  getDefaultWeight

▸ **getDefaultWeight**(): *[TextWeight](../enums/textweight.md)*

*Overrides [FactTextDefinition](facttextdefinition.md).[getDefaultWeight](facttextdefinition.md#getdefaultweight)*

*Defined in [host-config.ts:139](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L139)*

**Returns:** *[TextWeight](../enums/textweight.md)*

___

###  toJSON

▸ **toJSON**(): *any*

*Inherited from [FactTextDefinition](facttextdefinition.md).[toJSON](facttextdefinition.md#tojson)*

*Defined in [host-config.ts:115](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L115)*

**Returns:** *any*
