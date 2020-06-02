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

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[FactTitleDefinition](facttitledefinition.md)*

## Properties

###  color

• **color**: *[TextColor](../enums/textcolor.md)* = Enums.TextColor.Default

*Inherited from [FactTextDefinition](facttextdefinition.md).[color](facttextdefinition.md#color)*

___

###  isSubtle

• **isSubtle**: *boolean* = false

*Inherited from [FactTextDefinition](facttextdefinition.md).[isSubtle](facttextdefinition.md#issubtle)*

___

### `Optional` maxWidth

• **maxWidth**? : *undefined | number* = 150

___

###  size

• **size**: *[TextSize](../enums/textsize.md)* = Enums.TextSize.Default

*Inherited from [FactTextDefinition](facttextdefinition.md).[size](facttextdefinition.md#size)*

___

###  weight

• **weight**: *[TextWeight](../enums/textweight.md)* = Enums.TextWeight.Bolder

*Overrides [FactTextDefinition](facttextdefinition.md).[weight](facttextdefinition.md#weight)*

___

###  wrap

• **wrap**: *boolean* = true

*Inherited from [FactTextDefinition](facttextdefinition.md).[wrap](facttextdefinition.md#wrap)*

## Methods

###  getDefaultWeight

▸ **getDefaultWeight**(): *[TextWeight](../enums/textweight.md)*

*Overrides [FactTextDefinition](facttextdefinition.md).[getDefaultWeight](facttextdefinition.md#getdefaultweight)*

**Returns:** *[TextWeight](../enums/textweight.md)*

___

###  toJSON

▸ **toJSON**(): *any*

*Inherited from [FactTextDefinition](facttextdefinition.md).[toJSON](facttextdefinition.md#tojson)*

**Returns:** *any*
