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

*Defined in [host-config.ts:138](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L138)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[FactTitleDefinition](facttitledefinition.md)*

## Properties

###  color

• **color**: *[TextColor](../enums/textcolor.md)* = Enums.TextColor.Default

*Inherited from [FactTextDefinition](facttextdefinition.md).[color](facttextdefinition.md#color)*

*Defined in [host-config.ts:106](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L106)*

___

###  isSubtle

• **isSubtle**: *boolean* = false

*Inherited from [FactTextDefinition](facttextdefinition.md).[isSubtle](facttextdefinition.md#issubtle)*

*Defined in [host-config.ts:107](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L107)*

___

### `Optional` maxWidth

• **maxWidth**? : *undefined | number* = 150

*Defined in [host-config.ts:137](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L137)*

___

###  size

• **size**: *[TextSize](../enums/textsize.md)* = Enums.TextSize.Default

*Inherited from [FactTextDefinition](facttextdefinition.md).[size](facttextdefinition.md#size)*

*Defined in [host-config.ts:105](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L105)*

___

###  weight

• **weight**: *[TextWeight](../enums/textweight.md)* = Enums.TextWeight.Bolder

*Overrides [FactTextDefinition](facttextdefinition.md).[weight](facttextdefinition.md#weight)*

*Defined in [host-config.ts:138](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L138)*

___

###  wrap

• **wrap**: *boolean* = true

*Inherited from [FactTextDefinition](facttextdefinition.md).[wrap](facttextdefinition.md#wrap)*

*Defined in [host-config.ts:109](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L109)*

## Methods

###  getDefaultWeight

▸ **getDefaultWeight**(): *[TextWeight](../enums/textweight.md)*

*Overrides [FactTextDefinition](facttextdefinition.md).[getDefaultWeight](facttextdefinition.md#getdefaultweight)*

*Defined in [host-config.ts:149](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L149)*

**Returns:** *[TextWeight](../enums/textweight.md)*

___

###  toJSON

▸ **toJSON**(): *any*

*Inherited from [FactTextDefinition](facttextdefinition.md).[toJSON](facttextdefinition.md#tojson)*

*Defined in [host-config.ts:125](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/host-config.ts#L125)*

**Returns:** *any*
