[Adaptive Cards Javascript SDK](../README.md) › ["host-config"](../modules/_host_config_.md) › [HostCapabilities](_host_config_.hostcapabilities.md)

# Class: HostCapabilities

## Hierarchy

* **HostCapabilities**

## Index

### Properties

* [capabilities](_host_config_.hostcapabilities.md#capabilities)

### Methods

* [areAllMet](_host_config_.hostcapabilities.md#areallmet)
* [hasCapability](_host_config_.hostcapabilities.md#hascapability)
* [parse](_host_config_.hostcapabilities.md#parse)

## Properties

###  capabilities

• **capabilities**: *[HostCapabilityMap](../modules/_host_config_.md#hostcapabilitymap)* = null

## Methods

###  areAllMet

▸ **areAllMet**(`hostCapabilities`: [HostCapabilities](_host_config_.hostcapabilities.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`hostCapabilities` | [HostCapabilities](_host_config_.hostcapabilities.md) |

**Returns:** *boolean*

___

###  hasCapability

▸ **hasCapability**(`name`: string, `version`: [HostCapabilityVersion](../modules/_host_config_.md#hostcapabilityversion)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`version` | [HostCapabilityVersion](../modules/_host_config_.md#hostcapabilityversion) |

**Returns:** *boolean*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/_host_config_.ivalidationerror.md)› |

**Returns:** *void*
