[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / ActionProperty

# Class: ActionProperty

[card-elements](../modules/card_elements.md).ActionProperty

## Hierarchy

* [*PropertyDefinition*](serialization.propertydefinition.md)

  ↳ **ActionProperty**

## Table of contents

### Constructors

- [constructor](card_elements.actionproperty.md#constructor)

### Properties

- [defaultValue](card_elements.actionproperty.md#defaultvalue)
- [forbiddenActionTypes](card_elements.actionproperty.md#forbiddenactiontypes)
- [isSerializationEnabled](card_elements.actionproperty.md#isserializationenabled)
- [name](card_elements.actionproperty.md#name)
- [onGetInitialValue](card_elements.actionproperty.md#ongetinitialvalue)
- [sequentialNumber](card_elements.actionproperty.md#sequentialnumber)
- [targetVersion](card_elements.actionproperty.md#targetversion)

### Methods

- [getInternalName](card_elements.actionproperty.md#getinternalname)
- [parse](card_elements.actionproperty.md#parse)
- [toJSON](card_elements.actionproperty.md#tojson)

## Constructors

### constructor

\+ **new ActionProperty**(`targetVersion`: [*Version*](serialization.version.md), `name`: *string*, `forbiddenActionTypes?`: *string*[]): [*ActionProperty*](card_elements.actionproperty.md)

#### Parameters:

Name | Type |
:------ | :------ |
`targetVersion` | [*Version*](serialization.version.md) |
`name` | *string* |
`forbiddenActionTypes` | *string*[] |

**Returns:** [*ActionProperty*](card_elements.actionproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [card-elements.ts:627](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L627)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: *any*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[defaultValue](serialization.propertydefinition.md#defaultvalue)

___

### forbiddenActionTypes

• `Readonly` **forbiddenActionTypes**: *string*[]

___

### isSerializationEnabled

• **isSerializationEnabled**: *boolean*= true

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[isSerializationEnabled](serialization.propertydefinition.md#isserializationenabled)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

___

### name

• `Readonly` **name**: *string*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[name](serialization.propertydefinition.md#name)

___

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md)) => *any*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[onGetInitialValue](serialization.propertydefinition.md#ongetinitialvalue)

___

### sequentialNumber

• `Readonly` **sequentialNumber**: *number*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[sequentialNumber](serialization.propertydefinition.md#sequentialnumber)

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

___

### targetVersion

• `Readonly` **targetVersion**: [*Version*](serialization.version.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[targetVersion](serialization.propertydefinition.md#targetversion)

## Methods

### getInternalName

▸ **getInternalName**(): *string*

**Returns:** *string*

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

___

### parse

▸ **parse**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*SerializationContext*](card_elements.serializationcontext.md)): *undefined* \| [*Action*](card_elements.action.md)

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *undefined* \| [*Action*](card_elements.action.md)

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [card-elements.ts:615](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L615)

___

### toJSON

▸ **toJSON**(`sender`: [*SerializableObject*](serialization.serializableobject.md), `target`: [*PropertyBag*](../modules/serialization.md#propertybag), `value`: *undefined* \| [*Action*](card_elements.action.md), `context`: [*SerializationContext*](card_elements.serializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`sender` | [*SerializableObject*](serialization.serializableobject.md) |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`value` | *undefined* \| [*Action*](card_elements.action.md) |
`context` | [*SerializationContext*](card_elements.serializationcontext.md) |

**Returns:** *void*

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [card-elements.ts:625](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L625)
