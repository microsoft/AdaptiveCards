[Adaptive Cards Javascript SDK](../README.md) › [HostCapabilities](hostcapabilities.md)

# Class: HostCapabilities

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **HostCapabilities**

## Index

### Constructors

* [constructor](hostcapabilities.md#constructor)

### Properties

* [maxVersion](hostcapabilities.md#maxversion)
* [onRegisterCustomProperties](hostcapabilities.md#static-optional-onregistercustomproperties)

### Methods

* [addCapability](hostcapabilities.md#addcapability)
* [areAllMet](hostcapabilities.md#areallmet)
* [clear](hostcapabilities.md#clear)
* [getCustomProperty](hostcapabilities.md#getcustomproperty)
* [getDefaultSerializationContext](hostcapabilities.md#protected-getdefaultserializationcontext)
* [getSchema](hostcapabilities.md#getschema)
* [getSchemaKey](hostcapabilities.md#protected-getschemakey)
* [getValue](hostcapabilities.md#protected-getvalue)
* [hasAllDefaultValues](hostcapabilities.md#hasalldefaultvalues)
* [hasCapability](hostcapabilities.md#hascapability)
* [hasDefaultValue](hostcapabilities.md#hasdefaultvalue)
* [internalParse](hostcapabilities.md#protected-internalparse)
* [internalToJSON](hostcapabilities.md#protected-internaltojson)
* [parse](hostcapabilities.md#parse)
* [populateSchema](hostcapabilities.md#protected-populateschema)
* [removeCapability](hostcapabilities.md#removecapability)
* [resetDefaultValues](hostcapabilities.md#resetdefaultvalues)
* [setCustomProperty](hostcapabilities.md#setcustomproperty)
* [setValue](hostcapabilities.md#protected-setvalue)
* [shouldSerialize](hostcapabilities.md#protected-shouldserialize)
* [toJSON](hostcapabilities.md#tojson)

## Constructors

###  constructor

\+ **new HostCapabilities**(): *[HostCapabilities](hostcapabilities.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

**Returns:** *[HostCapabilities](hostcapabilities.md)*

## Properties

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

## Methods

###  addCapability

▸ **addCapability**(`name`: string, `version`: [TargetVersion](../README.md#targetversion)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`version` | [TargetVersion](../README.md#targetversion) |

**Returns:** *void*

___

###  areAllMet

▸ **areAllMet**(`hostCapabilities`: [HostCapabilities](hostcapabilities.md)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`hostCapabilities` | [HostCapabilities](hostcapabilities.md) |

**Returns:** *boolean*

___

###  clear

▸ **clear**(): *void*

**Returns:** *void*

___

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

### `Protected` getDefaultSerializationContext

▸ **getDefaultSerializationContext**(): *[BaseSerializationContext](baseserializationcontext.md)*

*Inherited from [SerializableObject](serializableobject.md).[getDefaultSerializationContext](serializableobject.md#protected-getdefaultserializationcontext)*

**Returns:** *[BaseSerializationContext](baseserializationcontext.md)*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Inherited from [SerializableObject](serializableobject.md).[getSchema](serializableobject.md#getschema)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` getSchemaKey

▸ **getSchemaKey**(): *string*

*Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Inherited from [SerializableObject](serializableobject.md).[getValue](serializableobject.md#protected-getvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasAllDefaultValues](serializableobject.md#hasalldefaultvalues)*

**Returns:** *boolean*

___

###  hasCapability

▸ **hasCapability**(`name`: string, `version`: [TargetVersion](../README.md#targetversion)): *boolean*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`version` | [TargetVersion](../README.md#targetversion) |

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[hasDefaultValue](serializableobject.md#hasdefaultvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *boolean*

___

### `Protected` internalParse

▸ **internalParse**(`source`: any, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | any |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` internalToJSON

▸ **internalToJSON**(`target`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`source`: [PropertyBag](../README.md#propertybag), `context?`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[parse](serializableobject.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[populateSchema](serializableobject.md#protected-populateschema)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  removeCapability

▸ **removeCapability**(`name`: string): *void*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *void*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [SerializableObject](serializableobject.md).[resetDefaultValues](serializableobject.md#resetdefaultvalues)*

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setCustomProperty](serializableobject.md#setcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

*Inherited from [SerializableObject](serializableobject.md).[setValue](serializableobject.md#protected-setvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`value` | any |

**Returns:** *void*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): *boolean*

*Inherited from [SerializableObject](serializableobject.md).[shouldSerialize](serializableobject.md#protected-shouldserialize)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [SerializableObject](serializableobject.md).[toJSON](serializableobject.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*
