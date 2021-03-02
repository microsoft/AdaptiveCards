[Adaptive Cards Javascript SDK](../README.md) / [registry](../modules/registry.md) / CardObjectRegistry

# Class: CardObjectRegistry<T\>

[registry](../modules/registry.md).CardObjectRegistry

## Type parameters

Name | Type |
:------ | :------ |
`T` | [*SerializableObject*](serialization.serializableobject.md) |

## Table of contents

### Constructors

- [constructor](registry.cardobjectregistry.md#constructor)

### Methods

- [clear](registry.cardobjectregistry.md#clear)
- [createInstance](registry.cardobjectregistry.md#createinstance)
- [findByName](registry.cardobjectregistry.md#findbyname)
- [getItemAt](registry.cardobjectregistry.md#getitemat)
- [getItemCount](registry.cardobjectregistry.md#getitemcount)
- [register](registry.cardobjectregistry.md#register)
- [unregister](registry.cardobjectregistry.md#unregister)

## Constructors

### constructor

\+ **new CardObjectRegistry**<T\>(): [*CardObjectRegistry*](registry.cardobjectregistry.md)<T\>

#### Type parameters:

Name | Type |
:------ | :------ |
`T` | [*SerializableObject*](serialization.serializableobject.md)<T\> |

**Returns:** [*CardObjectRegistry*](registry.cardobjectregistry.md)<T\>

## Methods

### clear

▸ **clear**(): *void*

**Returns:** *void*

Defined in: [registry.ts:18](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L18)

___

### createInstance

▸ **createInstance**(`typeName`: *string*, `targetVersion`: [*Version*](serialization.version.md)): *undefined* \| T

#### Parameters:

Name | Type |
:------ | :------ |
`typeName` | *string* |
`targetVersion` | [*Version*](serialization.version.md) |

**Returns:** *undefined* \| T

Defined in: [registry.ts:43](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L43)

___

### findByName

▸ **findByName**(`typeName`: *string*): *undefined* \| [*ITypeRegistration*](../interfaces/registry.ityperegistration.md)<T\>

#### Parameters:

Name | Type |
:------ | :------ |
`typeName` | *string* |

**Returns:** *undefined* \| [*ITypeRegistration*](../interfaces/registry.ityperegistration.md)<T\>

Defined in: [registry.ts:14](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L14)

___

### getItemAt

▸ **getItemAt**(`index`: *number*): [*ITypeRegistration*](../interfaces/registry.ityperegistration.md)<T\>

#### Parameters:

Name | Type |
:------ | :------ |
`index` | *number* |

**Returns:** [*ITypeRegistration*](../interfaces/registry.ityperegistration.md)<T\>

Defined in: [registry.ts:53](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L53)

___

### getItemCount

▸ **getItemCount**(): *number*

**Returns:** *number*

Defined in: [registry.ts:49](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L49)

___

### register

▸ **register**(`typeName`: *string*, `objectType`: () => T, `schemaVersion?`: [*Version*](serialization.version.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`typeName` | *string* |
`objectType` | () => T |
`schemaVersion` | [*Version*](serialization.version.md) |

**Returns:** *void*

Defined in: [registry.ts:22](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L22)

___

### unregister

▸ **unregister**(`typeName`: *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`typeName` | *string* |

**Returns:** *void*

Defined in: [registry.ts:39](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/registry.ts#L39)
