[Adaptive Cards Javascript SDK](../README.md) / [serialization](../modules/serialization.md) / PropertyDefinition

# Class: PropertyDefinition

[serialization](../modules/serialization.md).PropertyDefinition

## Hierarchy

* **PropertyDefinition**

  ↳ [*ActionProperty*](card_elements.actionproperty.md)

  ↳ [*StringProperty*](serialization.stringproperty.md)

  ↳ [*BoolProperty*](serialization.boolproperty.md)

  ↳ [*NumProperty*](serialization.numproperty.md)

  ↳ [*PixelSizeProperty*](serialization.pixelsizeproperty.md)

  ↳ [*ValueSetProperty*](serialization.valuesetproperty.md)

  ↳ [*EnumProperty*](serialization.enumproperty.md)

  ↳ [*SerializableObjectProperty*](serialization.serializableobjectproperty.md)

  ↳ [*SerializableObjectCollectionProperty*](serialization.serializableobjectcollectionproperty.md)

  ↳ [*CustomProperty*](serialization.customproperty.md)

  ↳ [*StringProperty*](adaptivecards.stringproperty.md)

  ↳ [*BoolProperty*](adaptivecards.boolproperty.md)

  ↳ [*NumProperty*](adaptivecards.numproperty.md)

  ↳ [*PixelSizeProperty*](adaptivecards.pixelsizeproperty.md)

  ↳ [*ValueSetProperty*](adaptivecards.valuesetproperty.md)

  ↳ [*EnumProperty*](adaptivecards.enumproperty.md)

  ↳ [*SerializableObjectProperty*](adaptivecards.serializableobjectproperty.md)

  ↳ [*SerializableObjectCollectionProperty*](adaptivecards.serializableobjectcollectionproperty.md)

  ↳ [*CustomProperty*](adaptivecards.customproperty.md)

  ↳ [*ActionProperty*](adaptivecards.actionproperty.md)

## Table of contents

### Constructors

- [constructor](serialization.propertydefinition.md#constructor)

### Properties

- [defaultValue](serialization.propertydefinition.md#defaultvalue)
- [isSerializationEnabled](serialization.propertydefinition.md#isserializationenabled)
- [name](serialization.propertydefinition.md#name)
- [onGetInitialValue](serialization.propertydefinition.md#ongetinitialvalue)
- [sequentialNumber](serialization.propertydefinition.md#sequentialnumber)
- [targetVersion](serialization.propertydefinition.md#targetversion)

### Methods

- [getInternalName](serialization.propertydefinition.md#getinternalname)
- [parse](serialization.propertydefinition.md#parse)
- [toJSON](serialization.propertydefinition.md#tojson)

## Constructors

### constructor

\+ **new PropertyDefinition**(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*, `defaultValue?`: *any*, `onGetInitialValue?`: (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any*): [*PropertyDefinition*](serialization.propertydefinition.md)

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |
`name` | *string* |
`defaultValue?` | *any* |
`onGetInitialValue?` | (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any* |

**Returns:** [*PropertyDefinition*](serialization.propertydefinition.md)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: *any*

___

### isSerializationEnabled

• **isSerializationEnabled**: *boolean*= true

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

___

### name

• `Readonly` **name**: *string*

___

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any*

___

### sequentialNumber

• `Readonly` **sequentialNumber**: *number*

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

___

### targetVersion

• `Readonly` **targetVersion**: [*Version*](serialization.version.md)

## Methods

### getInternalName

▸ **getInternalName**(): *string*

**Returns:** *string*

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

___

### parse

▸ **parse**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *any*

Defined in: [serialization.ts:266](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L266)

___

### toJSON

▸ **toJSON**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: *any*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`value` | *any* |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Defined in: [serialization.ts:270](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L270)
