[Adaptive Cards Javascript SDK](../README.md) › [Version](version.md)

# Class: Version

## Hierarchy

* **Version**

## Index

### Constructors

* [constructor](version.md#constructor)

### Accessors

* [isValid](version.md#isvalid)
* [label](version.md#label)
* [major](version.md#major)
* [minor](version.md#minor)

### Methods

* [compareTo](version.md#compareto)
* [toJSON](version.md#tojson)
* [toString](version.md#tostring)
* [parse](version.md#static-parse)

## Constructors

###  constructor

\+ **new Version**(`major`: number, `minor`: number, `label?`: undefined | string): *[Version](version.md)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`major` | number | 1 |
`minor` | number | 1 |
`label?` | undefined &#124; string | - |

**Returns:** *[Version](version.md)*

## Accessors

###  isValid

• **get isValid**(): *boolean*

**Returns:** *boolean*

___

###  label

• **get label**(): *string*

**Returns:** *string*

___

###  major

• **get major**(): *number*

**Returns:** *number*

___

###  minor

• **get minor**(): *number*

**Returns:** *number*

## Methods

###  compareTo

▸ **compareTo**(`otherVersion`: [Version](version.md)): *number*

**Parameters:**

Name | Type |
------ | ------ |
`otherVersion` | [Version](version.md) |

**Returns:** *number*

___

###  toJSON

▸ **toJSON**(): *any*

**Returns:** *any*

___

###  toString

▸ **toString**(): *string*

**Returns:** *string*

___

### `Static` parse

▸ **parse**(`versionString`: string, `context`: [BaseSerializationContext](baseserializationcontext.md)): *[Version](version.md) | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`versionString` | string |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[Version](version.md) | undefined*
