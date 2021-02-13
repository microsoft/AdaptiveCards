[Adaptive Cards Javascript SDK](../README.md) › [RequiredInputLabelTextDefinition](requiredinputlabeltextdefinition.md)

# Class: RequiredInputLabelTextDefinition

## Hierarchy

* [BaseTextDefinition](basetextdefinition.md)

  ↳ **RequiredInputLabelTextDefinition**

## Index

### Constructors

* [constructor](requiredinputlabeltextdefinition.md#constructor)

### Properties

* [color](requiredinputlabeltextdefinition.md#color)
* [isSubtle](requiredinputlabeltextdefinition.md#issubtle)
* [size](requiredinputlabeltextdefinition.md#size)
* [suffix](requiredinputlabeltextdefinition.md#optional-suffix)
* [suffixColor](requiredinputlabeltextdefinition.md#suffixcolor)
* [weight](requiredinputlabeltextdefinition.md#weight)

### Methods

* [getDefaultWeight](requiredinputlabeltextdefinition.md#getdefaultweight)
* [toJSON](requiredinputlabeltextdefinition.md#tojson)

## Constructors

###  constructor

\+ **new RequiredInputLabelTextDefinition**(`obj?`: any): *[RequiredInputLabelTextDefinition](requiredinputlabeltextdefinition.md)*

*Overrides [BaseTextDefinition](basetextdefinition.md).[constructor](basetextdefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`obj?` | any |

**Returns:** *[RequiredInputLabelTextDefinition](requiredinputlabeltextdefinition.md)*

## Properties

###  color

• **color**: *[TextColor](../enums/textcolor.md)* = Enums.TextColor.Default

*Inherited from [BaseTextDefinition](basetextdefinition.md).[color](basetextdefinition.md#color)*

___

###  isSubtle

• **isSubtle**: *boolean* = false

*Inherited from [BaseTextDefinition](basetextdefinition.md).[isSubtle](basetextdefinition.md#issubtle)*

___

###  size

• **size**: *[TextSize](../enums/textsize.md)* = Enums.TextSize.Default

*Inherited from [BaseTextDefinition](basetextdefinition.md).[size](basetextdefinition.md#size)*

___

### `Optional` suffix

• **suffix**? : *undefined | string* = " *"

___

###  suffixColor

• **suffixColor**: *[TextColor](../enums/textcolor.md)* = Enums.TextColor.Attention

___

###  weight

• **weight**: *[TextWeight](../enums/textweight.md)* = Enums.TextWeight.Default

*Inherited from [BaseTextDefinition](basetextdefinition.md).[weight](basetextdefinition.md#weight)*

## Methods

###  getDefaultWeight

▸ **getDefaultWeight**(): *[TextWeight](../enums/textweight.md)*

*Inherited from [BaseTextDefinition](basetextdefinition.md).[getDefaultWeight](basetextdefinition.md#getdefaultweight)*

**Returns:** *[TextWeight](../enums/textweight.md)*

___

###  toJSON

▸ **toJSON**(): *any*

*Overrides [BaseTextDefinition](basetextdefinition.md).[toJSON](basetextdefinition.md#tojson)*

**Returns:** *any*
