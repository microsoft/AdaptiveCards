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

Ƭ **PropertyBag**: _object_

#### Type declaration:

Defined in: [serialization.ts:771](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L771)

---

### SerializableObjectType

Ƭ **SerializableObjectType**: _object_

#### Type declaration:

Defined in: [serialization.ts:605](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L605)

---

### TargetVersion

Ƭ **TargetVersion**: [_Version_](../classes/serialization.version.md) \| \*\*\*

Defined in: [serialization.ts:103](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L103)

## Functions

### isVersionLessOrEqual

▸ **isVersionLessOrEqual**(`version`: [_TargetVersion_](serialization.md#targetversion), `targetVersion`: [_TargetVersion_](serialization.md#targetversion)): _boolean_

#### Parameters:

| Name            | Type                                              |
| :-------------- | :------------------------------------------------ |
| `version`       | [_TargetVersion_](serialization.md#targetversion) |
| `targetVersion` | [_TargetVersion_](serialization.md#targetversion) |

**Returns:** _boolean_

Defined in: [serialization.ts:113](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L113)

---

### property

▸ **property**(`property`: [_PropertyDefinition_](../classes/serialization.propertydefinition.md)): (`target`: _any_, `propertyKey`: _string_) => _void_

#### Parameters:

| Name       | Type                                                                   |
| :--------- | :--------------------------------------------------------------------- |
| `property` | [_PropertyDefinition_](../classes/serialization.propertydefinition.md) |

**Returns:** _function_

Defined in: [serialization.ts:758](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L758)
