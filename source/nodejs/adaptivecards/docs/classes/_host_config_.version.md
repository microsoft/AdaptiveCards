[Adaptive Cards Javascript SDK](../README.md) › ["host-config"](../modules/_host_config_.md) › [Version](_host_config_.version.md)

# Class: Version

## Hierarchy

* **Version**

## Index

### Constructors

* [constructor](_host_config_.version.md#constructor)

### Accessors

* [isValid](_host_config_.version.md#isvalid)
* [label](_host_config_.version.md#label)
* [major](_host_config_.version.md#major)
* [minor](_host_config_.version.md#minor)

### Methods

* [compareTo](_host_config_.version.md#compareto)
* [toString](_host_config_.version.md#tostring)
* [parse](_host_config_.version.md#static-parse)

## Constructors

###  constructor

\+ **new Version**(`major`: number, `minor`: number, `label?`: string): *[Version](_host_config_.version.md)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`major` | number | 1 |
`minor` | number | 1 |
`label?` | string | - |

**Returns:** *[Version](_host_config_.version.md)*

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

▸ **compareTo**(`otherVersion`: [Version](_host_config_.version.md)): *number*

**Parameters:**

Name | Type |
------ | ------ |
`otherVersion` | [Version](_host_config_.version.md) |

**Returns:** *number*

___

###  toString

▸ **toString**(): *string*

**Returns:** *string*

___

### `Static` parse

▸ **parse**(`versionString`: string, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *[Version](_host_config_.version.md)*

**Parameters:**

Name | Type |
------ | ------ |
`versionString` | string |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

**Returns:** *[Version](_host_config_.version.md)*
