[Adaptive Cards Javascript SDK](../README.md) › [FactTitleDefinition](facttitledefinition.md)

# Class: FactTitleDefinition

## Hierarchy

  ↳ [FactTextDefinition](facttextdefinition.md)

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

*Inherited from [BaseTextDefinition](basetextdefinition.md).[color](basetextdefinition.md#color)*

___

###  isSubtle

• **isSubtle**: *boolean* = false

*Inherited from [BaseTextDefinition](basetextdefinition.md).[isSubtle](basetextdefinition.md#issubtle)*

___

### `Optional` maxWidth

• **maxWidth**? : *undefined | number* = 150

___

###  size

• **size**: *[TextSize](../enums/textsize.md)* = Enums.TextSize.Default

*Inherited from [BaseTextDefinition](basetextdefinition.md).[size](basetextdefinition.md#size)*

___

###  weight

• **weight**: *[TextWeight](../enums/textweight.md)* = Enums.TextWeight.Bolder

*Overrides [BaseTextDefinition](basetextdefinition.md).[weight](basetextdefinition.md#weight)*

___

###  wrap

• **wrap**: *boolean* = true

*Inherited from [FactTextDefinition](facttextdefinition.md).[wrap](facttextdefinition.md#wrap)*

## Methods

###  getDefaultWeight

▸ **getDefaultWeight**(): *[TextWeight](../enums/textweight.md)*

*Overrides [BaseTextDefinition](basetextdefinition.md).[getDefaultWeight](basetextdefinition.md#getdefaultweight)*

**Returns:** *[TextWeight](../enums/textweight.md)*

___

###  toJSON

▸ **toJSON**(): *any*

*Inherited from [FactTextDefinition](facttextdefinition.md).[toJSON](facttextdefinition.md#tojson)*

*Overrides [BaseTextDefinition](basetextdefinition.md).[toJSON](basetextdefinition.md#tojson)*

**Returns:** *any*
