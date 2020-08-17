[Adaptive Cards Javascript SDK](../README.md) › [CustomProperty](customproperty.md)

# Class: CustomProperty ‹**T**›

## Type parameters

▪ **T**

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **CustomProperty**

  ↳ [TimeProperty](timeproperty.md)

## Index

### Constructors

* [constructor](customproperty.md#constructor)

### Properties

* [defaultValue](customproperty.md#optional-defaultvalue)
* [isSerializationEnabled](customproperty.md#isserializationenabled)
* [name](customproperty.md#name)
* [onGetInitialValue](customproperty.md#optional-ongetinitialvalue)
* [onParse](customproperty.md#onparse)
* [onToJSON](customproperty.md#ontojson)
* [sequentialNumber](customproperty.md#sequentialnumber)
* [targetVersion](customproperty.md#targetversion)

### Methods

* [getInternalName](customproperty.md#getinternalname)
* [parse](customproperty.md#parse)
* [toJSON](customproperty.md#tojson)

## Constructors

###  constructor

\+ **new CustomProperty**(`targetVersion`: [Version](version.md), `name`: string, `onParse`: function, `onToJSON`: function, `defaultValue?`: T, `onGetInitialValue?`: undefined | function): *[CustomProperty](customproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

▪ **targetVersion**: *[Version](version.md)*

▪ **name**: *string*

▪ **onParse**: *function*

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *T*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

▪ **onToJSON**: *function*

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `target`: [PropertyBag](../README.md#propertybag), `value`: T, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | T |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

▪`Optional`  **defaultValue**: *T*

▪`Optional`  **onGetInitialValue**: *undefined | function*

**Returns:** *[CustomProperty](customproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *T*

*Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

###  name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

___

###  onParse

• **onParse**: *function*

#### Type declaration:

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *T*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

___

###  onToJSON

• **onToJSON**: *function*

#### Type declaration:

▸ (`sender`: [SerializableObject](serializableobject.md), `property`: [PropertyDefinition](propertydefinition.md), `target`: [PropertyBag](../README.md#propertybag), `value`: T, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`property` | [PropertyDefinition](propertydefinition.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | T |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

___

###  sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#sequentialnumber)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *T*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *T*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: T, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | T |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
