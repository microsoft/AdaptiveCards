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
* [toString](version.md#tostring)
* [parse](version.md#static-parse)

## Constructors

###  constructor

\+ **new Version**(`major`: number, `minor`: number, `label?`: string): *[Version](version.md)*

*Defined in [host-config.ts:397](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L397)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`major` | number | 1 |
`minor` | number | 1 |
`label?` | string | - |

**Returns:** *[Version](version.md)*

## Accessors

###  isValid

• **get isValid**(): *boolean*

*Defined in [host-config.ts:473](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L473)*

**Returns:** *boolean*

___

###  label

• **get label**(): *string*

*Defined in [host-config.ts:461](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L461)*

**Returns:** *string*

___

###  major

• **get major**(): *number*

*Defined in [host-config.ts:465](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L465)*

**Returns:** *number*

___

###  minor

• **get minor**(): *number*

*Defined in [host-config.ts:469](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L469)*

**Returns:** *number*

## Methods

###  compareTo

▸ **compareTo**(`otherVersion`: [Version](version.md)): *number*

*Defined in [host-config.ts:440](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L440)*

**Parameters:**

Name | Type |
------ | ------ |
`otherVersion` | [Version](version.md) |

**Returns:** *number*

___

###  toString

▸ **toString**(): *string*

*Defined in [host-config.ts:436](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L436)*

**Returns:** *string*

___

### `Static` parse

▸ **parse**(`versionString`: string, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *[Version](version.md)*

*Defined in [host-config.ts:405](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L405)*

**Parameters:**

Name | Type |
------ | ------ |
`versionString` | string |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

**Returns:** *[Version](version.md)*
