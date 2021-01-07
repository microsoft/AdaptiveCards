[Adaptive Cards Javascript SDK](../README.md) › [InputValidationOptions](inputvalidationoptions.md)

# Class: InputValidationOptions

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **InputValidationOptions**

## Index

### Constructors

* [constructor](inputvalidationoptions.md#constructor)

### Properties

* [errorMessage](inputvalidationoptions.md#optional-errormessage)
* [maxVersion](inputvalidationoptions.md#maxversion)
* [necessity](inputvalidationoptions.md#necessity)
* [errorMessageProperty](inputvalidationoptions.md#static-errormessageproperty)
* [necessityProperty](inputvalidationoptions.md#static-necessityproperty)
* [onRegisterCustomProperties](inputvalidationoptions.md#static-optional-onregistercustomproperties)

### Methods

* [getCustomProperty](inputvalidationoptions.md#getcustomproperty)
* [getSchema](inputvalidationoptions.md#getschema)
* [getSchemaKey](inputvalidationoptions.md#protected-getschemakey)
* [getValue](inputvalidationoptions.md#protected-getvalue)
* [hasAllDefaultValues](inputvalidationoptions.md#hasalldefaultvalues)
* [hasDefaultValue](inputvalidationoptions.md#hasdefaultvalue)
* [internalParse](inputvalidationoptions.md#protected-internalparse)
* [internalToJSON](inputvalidationoptions.md#protected-internaltojson)
* [parse](inputvalidationoptions.md#parse)
* [populateSchema](inputvalidationoptions.md#protected-populateschema)
* [resetDefaultValues](inputvalidationoptions.md#resetdefaultvalues)
* [setCustomProperty](inputvalidationoptions.md#setcustomproperty)
* [setValue](inputvalidationoptions.md#protected-setvalue)
* [shouldSerialize](inputvalidationoptions.md#protected-shouldserialize)
* [toJSON](inputvalidationoptions.md#tojson)

## Constructors

###  constructor

\+ **new InputValidationOptions**(): *[InputValidationOptions](inputvalidationoptions.md)*

*Inherited from [SerializableObject](serializableobject.md).[constructor](serializableobject.md#constructor)*

**Returns:** *[InputValidationOptions](inputvalidationoptions.md)*

## Properties

### `Optional` errorMessage

• **errorMessage**? : *undefined | string*

___

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.latest

*Inherited from [SerializableObject](serializableobject.md).[maxVersion](serializableobject.md#maxversion)*

___

###  necessity

• **necessity**: *[InputValidationNecessity](../enums/inputvalidationnecessity.md)* = Enums.InputValidationNecessity.Optional

___

### `Static` errorMessageProperty

▪ **errorMessageProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.vNext, "errorMessagwe")

___

### `Static` necessityProperty

▪ **necessityProperty**: *[EnumProperty](enumproperty.md)‹[InputValidationNecessity](../enums/inputvalidationnecessity.md)›* = new EnumProperty(Versions.vNext, "necessity", Enums.InputValidationNecessity, Enums.InputValidationNecessity.Optional)

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [SerializableObject](serializableobject.md).[onRegisterCustomProperties](serializableobject.md#static-optional-onregistercustomproperties)*

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [SerializableObject](serializableobject.md).[getCustomProperty](serializableobject.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

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

▸ **internalParse**(`source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [SerializableObject](serializableobject.md).[internalParse](serializableobject.md#protected-internalparse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
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
