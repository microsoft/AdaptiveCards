[Adaptive Cards Javascript SDK](../README.md) / [host-capabilities](../modules/host_capabilities.md) / HostCapabilities

# Class: HostCapabilities

[host-capabilities](../modules/host_capabilities.md).HostCapabilities

## Hierarchy

- [_SerializableObject_](serialization.serializableobject.md)

  ↳ **HostCapabilities**

## Table of contents

### Constructors

- [constructor](host_capabilities.hostcapabilities.md#constructor)

### Properties

- [maxVersion](host_capabilities.hostcapabilities.md#maxversion)
- [defaultMaxVersion](host_capabilities.hostcapabilities.md#defaultmaxversion)
- [onRegisterCustomProperties](host_capabilities.hostcapabilities.md#onregistercustomproperties)

### Methods

- [addCapability](host_capabilities.hostcapabilities.md#addcapability)
- [areAllMet](host_capabilities.hostcapabilities.md#areallmet)
- [clear](host_capabilities.hostcapabilities.md#clear)
- [getCustomProperty](host_capabilities.hostcapabilities.md#getcustomproperty)
- [getDefaultSerializationContext](host_capabilities.hostcapabilities.md#getdefaultserializationcontext)
- [getSchema](host_capabilities.hostcapabilities.md#getschema)
- [getSchemaKey](host_capabilities.hostcapabilities.md#getschemakey)
- [getValue](host_capabilities.hostcapabilities.md#getvalue)
- [hasAllDefaultValues](host_capabilities.hostcapabilities.md#hasalldefaultvalues)
- [hasCapability](host_capabilities.hostcapabilities.md#hascapability)
- [hasDefaultValue](host_capabilities.hostcapabilities.md#hasdefaultvalue)
- [internalParse](host_capabilities.hostcapabilities.md#internalparse)
- [internalToJSON](host_capabilities.hostcapabilities.md#internaltojson)
- [parse](host_capabilities.hostcapabilities.md#parse)
- [populateSchema](host_capabilities.hostcapabilities.md#populateschema)
- [removeCapability](host_capabilities.hostcapabilities.md#removecapability)
- [resetDefaultValues](host_capabilities.hostcapabilities.md#resetdefaultvalues)
- [setCustomProperty](host_capabilities.hostcapabilities.md#setcustomproperty)
- [setValue](host_capabilities.hostcapabilities.md#setvalue)
- [shouldSerialize](host_capabilities.hostcapabilities.md#shouldserialize)
- [toJSON](host_capabilities.hostcapabilities.md#tojson)

## Constructors

### constructor

\+ **new HostCapabilities**(): [_HostCapabilities_](host_capabilities.hostcapabilities.md)

**Returns:** [_HostCapabilities_](host_capabilities.hostcapabilities.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### maxVersion

• **maxVersion**: [_Version_](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[maxVersion](serialization.serializableobject.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

---

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [_Version_](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[defaultMaxVersion](serialization.serializableobject.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

---

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: _undefined_ \| (`sender`: [_SerializableObject_](serialization.serializableobject.md), `schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)) => _void_

Inherited from: [SerializableObject](serialization.serializableobject.md).[onRegisterCustomProperties](serialization.serializableobject.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

## Methods

### addCapability

▸ **addCapability**(`name`: _string_, `version`: [_TargetVersion_](../modules/serialization.md#targetversion)): _void_

#### Parameters:

| Name      | Type                                                         |
| :-------- | :----------------------------------------------------------- |
| `name`    | _string_                                                     |
| `version` | [_TargetVersion_](../modules/serialization.md#targetversion) |

**Returns:** _void_

Defined in: [host-capabilities.ts:43](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L43)

---

### areAllMet

▸ **areAllMet**(`hostCapabilities`: [_HostCapabilities_](host_capabilities.hostcapabilities.md)): _boolean_

#### Parameters:

| Name               | Type                                                        |
| :----------------- | :---------------------------------------------------------- |
| `hostCapabilities` | [_HostCapabilities_](host_capabilities.hostcapabilities.md) |

**Returns:** _boolean_

Defined in: [host-capabilities.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L67)

---

### clear

▸ **clear**(): _void_

**Returns:** _void_

Defined in: [host-capabilities.ts:51](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L51)

---

### getCustomProperty

▸ **getCustomProperty**(`name`: _string_): _any_

#### Parameters:

| Name   | Type     |
| :----- | :------- |
| `name` | _string_ |

**Returns:** _any_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

---

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [_BaseSerializationContext_](serialization.baseserializationcontext.md)

**Returns:** [_BaseSerializationContext_](serialization.baseserializationcontext.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:784](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L784)

---

### getSchema

▸ **getSchema**(): [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

**Returns:** [_SerializableObjectSchema_](serialization.serializableobjectschema.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

---

### getSchemaKey

▸ `Protected`**getSchemaKey**(): _string_

**Returns:** _string_

Overrides: [SerializableObject](serialization.serializableobject.md)

Defined in: [host-capabilities.ts:8](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L8)

---

### getValue

▸ `Protected`**getValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _any_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _any_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

---

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): _boolean_

**Returns:** _boolean_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

---

### hasCapability

▸ **hasCapability**(`name`: _string_, `version`: [_TargetVersion_](../modules/serialization.md#targetversion)): _boolean_

#### Parameters:

| Name      | Type                                                         |
| :-------- | :----------------------------------------------------------- |
| `name`    | _string_                                                     |
| `version` | [_TargetVersion_](../modules/serialization.md#targetversion) |

**Returns:** _boolean_

Defined in: [host-capabilities.ts:55](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L55)

---

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md)): _boolean_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |

**Returns:** _boolean_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

---

### internalParse

▸ `Protected`**internalParse**(`source`: _any_, `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `source`  | _any_                                                                   |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Overrides: [SerializableObject](serialization.serializableobject.md)

Defined in: [host-capabilities.ts:12](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L12)

---

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [_PropertyBag_](../modules/serialization.md#propertybag), `context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `target`  | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Overrides: [SerializableObject](serialization.serializableobject.md)

Defined in: [host-capabilities.ts:35](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L35)

---

### parse

▸ **parse**(`source`: [_PropertyBag_](../modules/serialization.md#propertybag), `context?`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _void_

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `source`   | [_PropertyBag_](../modules/serialization.md#propertybag)                |
| `context?` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:912](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L912)

---

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [_SerializableObjectSchema_](serialization.serializableobjectschema.md)): _void_

#### Parameters:

| Name     | Type                                                                    |
| :------- | :---------------------------------------------------------------------- |
| `schema` | [_SerializableObjectSchema_](serialization.serializableobjectschema.md) |

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:788](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L788)

---

### removeCapability

▸ **removeCapability**(`name`: _string_): _void_

#### Parameters:

| Name   | Type     |
| :----- | :------- |
| `name` | _string_ |

**Returns:** _void_

Defined in: [host-capabilities.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L47)

---

### resetDefaultValues

▸ **resetDefaultValues**(): _void_

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

---

### setCustomProperty

▸ **setCustomProperty**(`name`: _string_, `value`: _any_): _void_

#### Parameters:

| Name    | Type     |
| :------ | :------- |
| `name`  | _string_ |
| `value` | _any_    |

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

---

### setValue

▸ `Protected`**setValue**(`property`: [_PropertyDefinition_](serialization.propertydefinition.md), `value`: _any_): _void_

#### Parameters:

| Name       | Type                                                        |
| :--------- | :---------------------------------------------------------- |
| `property` | [_PropertyDefinition_](serialization.propertydefinition.md) |
| `value`    | _any_                                                       |

**Returns:** _void_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

---

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _boolean_

#### Parameters:

| Name      | Type                                                                    |
| :-------- | :---------------------------------------------------------------------- |
| `context` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _boolean_

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:894](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L894)

---

### toJSON

▸ **toJSON**(`context?`: [_BaseSerializationContext_](serialization.baseserializationcontext.md)): _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

#### Parameters:

| Name       | Type                                                                    |
| :--------- | :---------------------------------------------------------------------- |
| `context?` | [_BaseSerializationContext_](serialization.baseserializationcontext.md) |

**Returns:** _undefined_ \| [_PropertyBag_](../modules/serialization.md#propertybag)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)
