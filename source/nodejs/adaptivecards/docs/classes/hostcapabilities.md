[Adaptive Cards Javascript SDK](../README.md) › [HostCapabilities](hostcapabilities.md)

# Class: HostCapabilities

## Hierarchy

* **HostCapabilities**

## Index

### Properties

* [capabilities](hostcapabilities.md#capabilities)

### Methods

* [areAllMet](hostcapabilities.md#areallmet)
* [hasCapability](hostcapabilities.md#hascapability)
* [parse](hostcapabilities.md#parse)

## Properties

###  capabilities

• **capabilities**: *[HostCapabilityMap](../README.md#hostcapabilitymap)* = null

*Defined in [host-config.ts:490](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L490)*

## Methods

###  areAllMet

▸ **areAllMet**(`hostCapabilities`: [HostCapabilities](hostcapabilities.md)): *boolean*

*Defined in [host-config.ts:525](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L525)*

**Parameters:**

Name | Type |
------ | ------ |
`hostCapabilities` | [HostCapabilities](hostcapabilities.md) |

**Returns:** *boolean*

___

###  hasCapability

▸ **hasCapability**(`name`: string, `version`: [HostCapabilityVersion](../README.md#hostcapabilityversion)): *boolean*

*Defined in [host-config.ts:513](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L513)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`version` | [HostCapabilityVersion](../README.md#hostcapabilityversion) |

**Returns:** *boolean*

___

###  parse

▸ **parse**(`json`: any, `errors?`: Array‹[IValidationError](../interfaces/ivalidationerror.md)›): *void*

*Defined in [host-config.ts:492](https://github.com/microsoft/AdaptiveCards/blob/a61c5fd56/source/nodejs/adaptivecards/src/host-config.ts#L492)*

**Parameters:**

Name | Type |
------ | ------ |
`json` | any |
`errors?` | Array‹[IValidationError](../interfaces/ivalidationerror.md)› |

**Returns:** *void*
