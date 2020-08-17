[Adaptive Cards Javascript SDK](../README.md) › [StringProperty](stringproperty.md)

# Class: StringProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **StringProperty**

## Index

### Constructors

* [constructor](stringproperty.md#constructor)

### Properties

* [defaultValue](stringproperty.md#optional-defaultvalue)
* [isSerializationEnabled](stringproperty.md#isserializationenabled)
* [name](stringproperty.md#name)
* [onGetInitialValue](stringproperty.md#optional-ongetinitialvalue)
* [regEx](stringproperty.md#optional-regex)
* [sequentialNumber](stringproperty.md#sequentialnumber)
* [targetVersion](stringproperty.md#targetversion)
* [treatEmptyAsUndefined](stringproperty.md#treatemptyasundefined)

### Methods

* [getInternalName](stringproperty.md#getinternalname)
* [parse](stringproperty.md#parse)
* [toJSON](stringproperty.md#tojson)

## Constructors

###  constructor

\+ **new StringProperty**(`targetVersion`: [Version](version.md), `name`: string, `treatEmptyAsUndefined`: boolean, `regEx?`: RegExp, `defaultValue?`: undefined | string, `onGetInitialValue?`: undefined | function): *[StringProperty](stringproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`targetVersion` | [Version](version.md) | - |
`name` | string | - |
`treatEmptyAsUndefined` | boolean | true |
`regEx?` | RegExp | - |
`defaultValue?` | undefined &#124; string | - |
`onGetInitialValue?` | undefined &#124; function | - |

**Returns:** *[StringProperty](stringproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *undefined | string*

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

### `Optional` regEx

• **regEx**? : *RegExp*

___

###  sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#sequentialnumber)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

___

###  treatEmptyAsUndefined

• **treatEmptyAsUndefined**: *boolean*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *string | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *string | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: string | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | string &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
