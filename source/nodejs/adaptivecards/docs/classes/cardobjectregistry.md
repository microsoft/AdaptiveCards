[Adaptive Cards Javascript SDK](../README.md) › [CardObjectRegistry](cardobjectregistry.md)

# Class: CardObjectRegistry <**T**>

## Type parameters

▪ **T**: *[SerializableObject](serializableobject.md)*

## Hierarchy

* **CardObjectRegistry**

## Index

### Methods

* [clear](cardobjectregistry.md#clear)
* [createInstance](cardobjectregistry.md#createinstance)
* [findByName](cardobjectregistry.md#findbyname)
* [getItemAt](cardobjectregistry.md#getitemat)
* [getItemCount](cardobjectregistry.md#getitemcount)
* [register](cardobjectregistry.md#register)
* [unregister](cardobjectregistry.md#unregister)

## Methods

###  clear

▸ **clear**(): *void*

*Defined in [registry.ts:18](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/registry.ts#L18)*

**Returns:** *void*

___

###  createInstance

▸ **createInstance**(`typeName`: string, `targetVersion`: [Version](version.md)): *T | undefined*

*Defined in [registry.ts:43](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/registry.ts#L43)*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |
`targetVersion` | [Version](version.md) |

**Returns:** *T | undefined*

___

###  findByName

▸ **findByName**(`typeName`: string): *[ITypeRegistration](../interfaces/ityperegistration.md)‹T› | undefined*

*Defined in [registry.ts:14](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/registry.ts#L14)*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *[ITypeRegistration](../interfaces/ityperegistration.md)‹T› | undefined*

___

###  getItemAt

▸ **getItemAt**(`index`: number): *[ITypeRegistration](../interfaces/ityperegistration.md)‹T›*

*Defined in [registry.ts:53](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/registry.ts#L53)*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[ITypeRegistration](../interfaces/ityperegistration.md)‹T›*

___

###  getItemCount

▸ **getItemCount**(): *number*

*Defined in [registry.ts:49](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/registry.ts#L49)*

**Returns:** *number*

___

###  register

▸ **register**(`typeName`: string, `objectType`: object, `schemaVersion`: [Version](version.md)): *void*

*Defined in [registry.ts:22](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/registry.ts#L22)*

**Parameters:**

▪ **typeName**: *string*

▪ **objectType**: *object*

Name | Type |
------ | ------ |
`constructor` |  |

▪`Default value`  **schemaVersion**: *[Version](version.md)*= Versions.v1_0

**Returns:** *void*

___

###  unregister

▸ **unregister**(`typeName`: string): *void*

*Defined in [registry.ts:39](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/registry.ts#L39)*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *void*
