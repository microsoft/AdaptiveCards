[Adaptive Cards Javascript SDK](../README.md) / [card-elements](../modules/card_elements.md) / ActionProperty

# Class: ActionProperty

[card-elements](../modules/card_elements.md).ActionProperty

## Hierarchy

- [_PropertyDefinition_](serialization.propertydefinition.md)

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

\+ **new ActionProperty**(`targetVersion`: [_Version_](serialization.version.md), `name`: _string_, `forbiddenActionTypes?`: _string_[]): [_ActionProperty_](card_elements.actionproperty.md)

#### Parameters:

| Name                   | Type                                  |
| :--------------------- | :------------------------------------ |
| `targetVersion`        | [_Version_](serialization.version.md) |
| `name`                 | _string_                              |
| `forbiddenActionTypes` | _string_[]                            |

**Returns:** [_ActionProperty_](card_elements.actionproperty.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [card-elements.ts:627](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L627)

## Properties

### defaultValue

• `Optional` `Readonly` **defaultValue**: _any_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[defaultValue](serialization.propertydefinition.md#defaultvalue)

---

### forbiddenActionTypes

• `Readonly` **forbiddenActionTypes**: _string_[]

---

### isSerializationEnabled

• **isSerializationEnabled**: _boolean_= true

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[isSerializationEnabled](serialization.propertydefinition.md#isserializationenabled)

Defined in: [serialization.ts:276](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L276)

---

### name

• `Readonly` **name**: _string_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[name](serialization.propertydefinition.md#name)

---

### onGetInitialValue

• `Optional` `Readonly` **onGetInitialValue**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md)) => _any_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[onGetInitialValue](serialization.propertydefinition.md#ongetinitialvalue)

---

### sequentialNumber

• `Readonly` **sequentialNumber**: _number_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[sequentialNumber](serialization.propertydefinition.md#sequentialnumber)

Defined in: [serialization.ts:274](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L274)

---

### targetVersion

• `Readonly` **targetVersion**: [_Version_](serialization.version.md)

Inherited from: [PropertyDefinition](serialization.propertydefinition.md).[targetVersion](serialization.propertydefinition.md#targetversion)

## Methods

### getInternalName

▸ **getInternalName**(): _string_

**Returns:** _string_

Inherited from: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L262)

---

### parse

▸ **parse**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_SerializationContext_](card_elements.serializationcontext.md)): _undefined_ \| [_Action_](card_elements.action.md)

#### Parameters:

| Name      | Type                                                            |
| :-------- | :-------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)     |
| `source`  | [_PropertyBag_](../modules/serialization.md#propertybag)        |
| `context` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _undefined_ \| [_Action_](card_elements.action.md)

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [card-elements.ts:615](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L615)

---

### toJSON

▸ **toJSON**(`sender`: [_SerializableObject_](serialization.serializableobject.md), `target`: [_PropertyBag_](../modules/serialization.md#propertybag), `value`: _undefined_ \| [_Action_](card_elements.action.md), `context`: [_SerializationContext_](card_elements.serializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                            |
| :-------- | :-------------------------------------------------------------- |
| `sender`  | [_SerializableObject_](serialization.serializableobject.md)     |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)        |
| `value`   | _undefined_ \| [_Action_](card_elements.action.md)              |
| `context` | [_SerializationContext_](card_elements.serializationcontext.md) |

**Returns:** _void_

Overrides: [PropertyDefinition](serialization.propertydefinition.md)

Defined in: [card-elements.ts:625](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/card-elements.ts#L625)
