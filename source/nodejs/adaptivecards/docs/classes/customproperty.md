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

* [defaultValue](customproperty.md#optional-readonly-defaultvalue)
* [isSerializationEnabled](customproperty.md#isserializationenabled)
* [name](customproperty.md#readonly-name)
* [onGetInitialValue](customproperty.md#optional-readonly-ongetinitialvalue)
* [onParse](customproperty.md#readonly-onparse)
* [onToJSON](customproperty.md#readonly-ontojson)
* [sequentialNumber](customproperty.md#readonly-sequentialnumber)
* [targetVersion](customproperty.md#readonly-targetversion)

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

### `Optional` `Readonly` defaultValue

• **defaultValue**? : *T*

*Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-readonly-defaultvalue)*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

### `Readonly` name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#readonly-name)*

___

### `Optional` `Readonly` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-readonly-ongetinitialvalue)*

___

### `Readonly` onParse

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

### `Readonly` onToJSON

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

### `Readonly` sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#readonly-sequentialnumber)*

___

### `Readonly` targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#readonly-targetversion)*

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
