[Adaptive Cards Javascript SDK](../README.md) / [host-capabilities](../modules/host_capabilities.md) / HostCapabilities

# Class: HostCapabilities

[host-capabilities](../modules/host_capabilities.md).HostCapabilities

## Hierarchy

* [*SerializableObject*](serialization.serializableobject.md)

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

\+ **new HostCapabilities**(): [*HostCapabilities*](host_capabilities.hostcapabilities.md)

**Returns:** [*HostCapabilities*](host_capabilities.hostcapabilities.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

## Properties

### maxVersion

• **maxVersion**: [*Version*](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[maxVersion](serialization.serializableobject.md#maxversion)

Defined in: [serialization.ts:898](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L898)

___

### defaultMaxVersion

▪ `Static` **defaultMaxVersion**: [*Version*](serialization.version.md)

Inherited from: [SerializableObject](serialization.serializableobject.md).[defaultMaxVersion](serialization.serializableobject.md#defaultmaxversion)

Defined in: [serialization.ts:775](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L775)

___

### onRegisterCustomProperties

▪ `Optional` `Static` **onRegisterCustomProperties**: *undefined* \| (`sender`: [*SerializableObject*](serialization.serializableobject.md), `schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)) => *void*

Inherited from: [SerializableObject](serialization.serializableobject.md).[onRegisterCustomProperties](serialization.serializableobject.md#onregistercustomproperties)

Defined in: [serialization.ts:774](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L774)

## Methods

### addCapability

▸ **addCapability**(`name`: *string*, `version`: [*TargetVersion*](../modules/serialization.md#targetversion)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |
`version` | [*TargetVersion*](../modules/serialization.md#targetversion) |

**Returns:** *void*

Defined in: [host-capabilities.ts:43](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L43)

___

### areAllMet

▸ **areAllMet**(`hostCapabilities`: [*HostCapabilities*](host_capabilities.hostcapabilities.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`hostCapabilities` | [*HostCapabilities*](host_capabilities.hostcapabilities.md) |

**Returns:** *boolean*

Defined in: [host-capabilities.ts:67](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L67)

___

### clear

▸ **clear**(): *void*

**Returns:** *void*

Defined in: [host-capabilities.ts:51](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L51)

___

### getCustomProperty

▸ **getCustomProperty**(`name`: *string*): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |

**Returns:** *any*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:985](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L985)

___

### getDefaultSerializationContext

▸ `Protected`**getDefaultSerializationContext**(): [*BaseSerializationContext*](serialization.baseserializationcontext.md)

**Returns:** [*BaseSerializationContext*](serialization.baseserializationcontext.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:784](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L784)

___

### getSchema

▸ **getSchema**(): [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

**Returns:** [*SerializableObjectSchema*](serialization.serializableobjectschema.md)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:989](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L989)

___

### getSchemaKey

▸ `Protected`**getSchemaKey**(): *string*

**Returns:** *string*

Overrides: [SerializableObject](serialization.serializableobject.md)

Defined in: [host-capabilities.ts:8](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L8)

___

### getValue

▸ `Protected`**getValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *any*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *any*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:826](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L826)

___

### hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

**Returns:** *boolean*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:950](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L950)

___

### hasCapability

▸ **hasCapability**(`name`: *string*, `version`: [*TargetVersion*](../modules/serialization.md#targetversion)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |
`version` | [*TargetVersion*](../modules/serialization.md#targetversion) |

**Returns:** *boolean*

Defined in: [host-capabilities.ts:55](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L55)

___

### hasDefaultValue

▸ **hasDefaultValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |

**Returns:** *boolean*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:946](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L946)

___

### internalParse

▸ `Protected`**internalParse**(`source`: *any*, `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | *any* |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Overrides: [SerializableObject](serialization.serializableobject.md)

Defined in: [host-capabilities.ts:12](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L12)

___

### internalToJSON

▸ `Protected`**internalToJSON**(`target`: [*PropertyBag*](../modules/serialization.md#propertybag), `context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`target` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Overrides: [SerializableObject](serialization.serializableobject.md)

Defined in: [host-capabilities.ts:35](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L35)

___

### parse

▸ **parse**(`source`: [*PropertyBag*](../modules/serialization.md#propertybag), `context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`source` | [*PropertyBag*](../modules/serialization.md#propertybag) |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:912](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L912)

___

### populateSchema

▸ `Protected`**populateSchema**(`schema`: [*SerializableObjectSchema*](serialization.serializableobjectschema.md)): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`schema` | [*SerializableObjectSchema*](serialization.serializableobjectschema.md) |

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:788](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L788)

___

### removeCapability

▸ **removeCapability**(`name`: *string*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |

**Returns:** *void*

Defined in: [host-capabilities.ts:47](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/host-capabilities.ts#L47)

___

### resetDefaultValues

▸ **resetDefaultValues**(): *void*

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:964](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L964)

___

### setCustomProperty

▸ **setCustomProperty**(`name`: *string*, `value`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`name` | *string* |
`value` | *any* |

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:974](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L974)

___

### setValue

▸ `Protected`**setValue**(`property`: [*PropertyDefinition*](serialization.propertydefinition.md), `value`: *any*): *void*

#### Parameters:

Name | Type |
:------ | :------ |
`property` | [*PropertyDefinition*](serialization.propertydefinition.md) |
`value` | *any* |

**Returns:** *void*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:830](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L830)

___

### shouldSerialize

▸ `Protected`**shouldSerialize**(`context`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *boolean*

#### Parameters:

Name | Type |
:------ | :------ |
`context` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *boolean*

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:894](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L894)

___

### toJSON

▸ **toJSON**(`context?`: [*BaseSerializationContext*](serialization.baseserializationcontext.md)): *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

#### Parameters:

Name | Type |
:------ | :------ |
`context?` | [*BaseSerializationContext*](serialization.baseserializationcontext.md) |

**Returns:** *undefined* \| [*PropertyBag*](../modules/serialization.md#propertybag)

Inherited from: [SerializableObject](serialization.serializableobject.md)

Defined in: [serialization.ts:916](https://github.com/microsoft/AdaptiveCards/blob/0938a1f10/source/nodejs/adaptivecards/src/serialization.ts#L916)
