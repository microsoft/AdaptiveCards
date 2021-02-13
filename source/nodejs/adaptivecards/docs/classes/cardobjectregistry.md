[Adaptive Cards Javascript SDK](../README.md) › [CardObjectRegistry](cardobjectregistry.md)

# Class: CardObjectRegistry ‹**T**›

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

**Returns:** *void*

___

###  createInstance

▸ **createInstance**(`typeName`: string, `targetVersion`: [Version](version.md)): *T | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |
`targetVersion` | [Version](version.md) |

**Returns:** *T | undefined*

___

###  findByName

▸ **findByName**(`typeName`: string): *[ITypeRegistration](../interfaces/ityperegistration.md)‹T› | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *[ITypeRegistration](../interfaces/ityperegistration.md)‹T› | undefined*

___

###  getItemAt

▸ **getItemAt**(`index`: number): *[ITypeRegistration](../interfaces/ityperegistration.md)‹T›*

**Parameters:**

Name | Type |
------ | ------ |
`index` | number |

**Returns:** *[ITypeRegistration](../interfaces/ityperegistration.md)‹T›*

___

###  getItemCount

▸ **getItemCount**(): *number*

**Returns:** *number*

___

###  register

▸ **register**(`typeName`: string, `objectType`: object, `schemaVersion`: [Version](version.md)): *void*

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

**Parameters:**

Name | Type |
------ | ------ |
`typeName` | string |

**Returns:** *void*
