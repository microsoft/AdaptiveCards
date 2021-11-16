[Adaptive Cards Javascript SDK](../README.md) / serialization

# Module: serialization

## Table of contents

### Classes

- [BaseSerializationContext](../classes/serialization.baseserializationcontext.md)
- [BoolProperty](../classes/serialization.boolproperty.md)
- [CustomProperty](../classes/serialization.customproperty.md)
- [EnumProperty](../classes/serialization.enumproperty.md)
- [NumProperty](../classes/serialization.numproperty.md)
- [PixelSizeProperty](../classes/serialization.pixelsizeproperty.md)
- [PropertyDefinition](../classes/serialization.propertydefinition.md)
- [SerializableObject](../classes/serialization.serializableobject.md)
- [SerializableObjectCollectionProperty](../classes/serialization.serializableobjectcollectionproperty.md)
- [SerializableObjectProperty](../classes/serialization.serializableobjectproperty.md)
- [SerializableObjectSchema](../classes/serialization.serializableobjectschema.md)
- [StringProperty](../classes/serialization.stringproperty.md)
- [ValueSetProperty](../classes/serialization.valuesetproperty.md)
- [Version](../classes/serialization.version.md)
- [Versions](../classes/serialization.versions.md)

### Interfaces

- [IValidationEvent](../interfaces/serialization.ivalidationevent.md)
- [IVersionedValue](../interfaces/serialization.iversionedvalue.md)

### Type aliases

- [PropertyBag](serialization.md#propertybag)
- [SerializableObjectType](serialization.md#serializableobjecttype)
- [TargetVersion](serialization.md#targetversion)

### Functions

- [isVersionLessOrEqual](serialization.md#isversionlessorequal)
- [property](serialization.md#property)

## Type aliases

### PropertyBag

Ƭ **PropertyBag**: *object*

#### Type declaration:

Defined in: [serialization.ts:771](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L771)

___

### SerializableObjectType

Ƭ **SerializableObjectType**: *object*

#### Type declaration:

Defined in: [serialization.ts:605](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L605)

___

### TargetVersion

Ƭ **TargetVersion**: [*Version*](../classes/serialization.version.md) \| ***

Defined in: [serialization.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L103)

## Functions

### isVersionLessOrEqual

▸ **isVersionLessOrEqual**(`version`: [*TargetVersion*](serialization.md#targetversion), `targetVersion`: [*TargetVersion*](serialization.md#targetversion)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`version` | [*TargetVersion*](serialization.md#targetversion) |
`targetVersion` | [*TargetVersion*](serialization.md#targetversion) |

**Returns:** *boolean*

Defined in: [serialization.ts:113](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L113)

___

### property

▸ **property**(`property`: [*PropertyDefinition*](../classes/serialization.propertydefinition.md)): (`target`: *any*, `propertyKey`: *string*) => *void*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](../classes/serialization.propertydefinition.md) |

**Returns:** *function*

Defined in: [serialization.ts:758](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L758)
