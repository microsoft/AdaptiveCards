[Adaptive Cards Javascript SDK](../README.md) › [HttpHeader](httpheader.md)

# Class: HttpHeader

## Hierarchy

* [SerializableObject](serializableobject.md)

  ↳ **HttpHeader**

## Index

### Constructors

* [constructor](httpheader.md#constructor)

### Properties

* [maxVersion](httpheader.md#maxversion)
* [name](httpheader.md#name)
* [nameProperty](httpheader.md#static-readonly-nameproperty)
* [onRegisterCustomProperties](httpheader.md#static-optional-onregistercustomproperties)
* [valueProperty](httpheader.md#static-readonly-valueproperty)

### Accessors

* [value](httpheader.md#value)

### Methods

* [getCustomProperty](httpheader.md#getcustomproperty)
* [getDefaultSerializationContext](httpheader.md#protected-getdefaultserializationcontext)
* [getReferencedInputs](httpheader.md#getreferencedinputs)
* [getSchema](httpheader.md#getschema)
* [getSchemaKey](httpheader.md#protected-getschemakey)
* [getValue](httpheader.md#protected-getvalue)
* [hasAllDefaultValues](httpheader.md#hasalldefaultvalues)
* [hasDefaultValue](httpheader.md#hasdefaultvalue)
* [internalParse](httpheader.md#protected-internalparse)
* [internalToJSON](httpheader.md#protected-internaltojson)
* [parse](httpheader.md#parse)
* [populateSchema](httpheader.md#protected-populateschema)
* [prepareForExecution](httpheader.md#prepareforexecution)
* [resetDefaultValues](httpheader.md#resetdefaultvalues)
* [setCustomProperty](httpheader.md#setcustomproperty)
* [setValue](httpheader.md#protected-setvalue)
* [shouldSerialize](httpheader.md#protected-shouldserialize)
* [toJSON](httpheader.md#tojson)

## Constructors

###  constructor

\+ **new HttpHeader**(`name`: string, `value`: string): *[HttpHeader](httpheader.md)*

*Overrides [HostCapabilities](hostcapabilities.md).[constructor](hostcapabilities.md#constructor)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`name` | string | "" |
`value` | string | "" |

**Returns:** *[HttpHeader](httpheader.md)*

## Properties

###  maxVersion

• **maxVersion**: *[Version](version.md)* = Versions.v1_3

*Inherited from [HostCapabilities](hostcapabilities.md).[maxVersion](hostcapabilities.md#maxversion)*

___

###  name

• **name**: *string*

___

### `Static` `Readonly` nameProperty

▪ **nameProperty**: *[StringProperty](stringproperty.md)‹›* = new StringProperty(Versions.v1_0, "name")

___

### `Static` `Optional` onRegisterCustomProperties

▪ **onRegisterCustomProperties**? : *undefined | function*

*Inherited from [HostCapabilities](hostcapabilities.md).[onRegisterCustomProperties](hostcapabilities.md#static-optional-onregistercustomproperties)*

___

### `Static` `Readonly` valueProperty

▪ **valueProperty**: *[StringWithSubstitutionProperty](stringwithsubstitutionproperty.md)‹›* = new StringWithSubstitutionProperty(Versions.v1_0, "value")

## Accessors

###  value

• **get value**(): *string | undefined*

**Returns:** *string | undefined*

• **set value**(`newValue`: string | undefined): *void*

**Parameters:**

Name | Type |
------ | ------ |
`newValue` | string &#124; undefined |

**Returns:** *void*

## Methods

###  getCustomProperty

▸ **getCustomProperty**(`name`: string): *any*

*Inherited from [HostCapabilities](hostcapabilities.md).[getCustomProperty](hostcapabilities.md#getcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *any*

___

### `Protected` getDefaultSerializationContext

▸ **getDefaultSerializationContext**(): *[BaseSerializationContext](baseserializationcontext.md)*

*Inherited from [HostCapabilities](hostcapabilities.md).[getDefaultSerializationContext](hostcapabilities.md#protected-getdefaultserializationcontext)*

**Returns:** *[BaseSerializationContext](baseserializationcontext.md)*

___

###  getReferencedInputs

▸ **getReferencedInputs**(`inputs`: [Input](input.md)[], `referencedInputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [Input](input.md)[] |
`referencedInputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› |

**Returns:** *void*

___

###  getSchema

▸ **getSchema**(): *[SerializableObjectSchema](serializableobjectschema.md)*

*Inherited from [HostCapabilities](hostcapabilities.md).[getSchema](hostcapabilities.md#getschema)*

**Returns:** *[SerializableObjectSchema](serializableobjectschema.md)*

___

### `Protected` getSchemaKey

▸ **getSchemaKey**(): *string*

*Overrides [SerializableObject](serializableobject.md).[getSchemaKey](serializableobject.md#protected-abstract-getschemakey)*

**Returns:** *string*

___

### `Protected` getValue

▸ **getValue**(`property`: [PropertyDefinition](propertydefinition.md)): *any*

*Inherited from [HostCapabilities](hostcapabilities.md).[getValue](hostcapabilities.md#protected-getvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |

**Returns:** *any*

___

###  hasAllDefaultValues

▸ **hasAllDefaultValues**(): *boolean*

*Inherited from [HostCapabilities](hostcapabilities.md).[hasAllDefaultValues](hostcapabilities.md#hasalldefaultvalues)*

**Returns:** *boolean*

___

###  hasDefaultValue

▸ **hasDefaultValue**(`property`: [PropertyDefinition](propertydefinition.md)): *boolean*

*Inherited from [HostCapabilities](hostcapabilities.md).[hasDefaultValue](hostcapabilities.md#hasdefaultvalue)*

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

*Inherited from [SerializableObject](serializableobject.md).[internalToJSON](serializableobject.md#protected-internaltojson)*

**Parameters:**

Name | Type |
------ | ------ |
`target` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

###  parse

▸ **parse**(`source`: [PropertyBag](../README.md#propertybag), `context?`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[parse](hostcapabilities.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`source` | [PropertyBag](../README.md#propertybag) |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*

___

### `Protected` populateSchema

▸ **populateSchema**(`schema`: [SerializableObjectSchema](serializableobjectschema.md)): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[populateSchema](hostcapabilities.md#protected-populateschema)*

**Parameters:**

Name | Type |
------ | ------ |
`schema` | [SerializableObjectSchema](serializableobjectschema.md) |

**Returns:** *void*

___

###  prepareForExecution

▸ **prepareForExecution**(`inputs`: [Dictionary](../README.md#dictionary)‹[Input](input.md)›): *void*

**Parameters:**

Name | Type |
------ | ------ |
`inputs` | [Dictionary](../README.md#dictionary)‹[Input](input.md)› |

**Returns:** *void*

___

###  resetDefaultValues

▸ **resetDefaultValues**(): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[resetDefaultValues](hostcapabilities.md#resetdefaultvalues)*

**Returns:** *void*

___

###  setCustomProperty

▸ **setCustomProperty**(`name`: string, `value`: any): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[setCustomProperty](hostcapabilities.md#setcustomproperty)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`value` | any |

**Returns:** *void*

___

### `Protected` setValue

▸ **setValue**(`property`: [PropertyDefinition](propertydefinition.md), `value`: any): *void*

*Inherited from [HostCapabilities](hostcapabilities.md).[setValue](hostcapabilities.md#protected-setvalue)*

**Parameters:**

Name | Type |
------ | ------ |
`property` | [PropertyDefinition](propertydefinition.md) |
`value` | any |

**Returns:** *void*

___

### `Protected` shouldSerialize

▸ **shouldSerialize**(`context`: [BaseSerializationContext](baseserializationcontext.md)): *boolean*

*Inherited from [HostCapabilities](hostcapabilities.md).[shouldSerialize](hostcapabilities.md#protected-shouldserialize)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *boolean*

___

###  toJSON

▸ **toJSON**(`context?`: [BaseSerializationContext](baseserializationcontext.md)): *[PropertyBag](../README.md#propertybag) | undefined*

*Inherited from [HostCapabilities](hostcapabilities.md).[toJSON](hostcapabilities.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`context?` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[PropertyBag](../README.md#propertybag) | undefined*
