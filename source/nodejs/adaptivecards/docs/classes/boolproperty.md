[Adaptive Cards Javascript SDK](../README.md) › [BoolProperty](boolproperty.md)

# Class: BoolProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **BoolProperty**

## Index

### Constructors

* [constructor](boolproperty.md#constructor)

### Properties

* [defaultValue](boolproperty.md#optional-readonly-defaultvalue)
* [isSerializationEnabled](boolproperty.md#isserializationenabled)
* [name](boolproperty.md#readonly-name)
* [onGetInitialValue](boolproperty.md#optional-readonly-ongetinitialvalue)
* [sequentialNumber](boolproperty.md#readonly-sequentialnumber)
* [targetVersion](boolproperty.md#readonly-targetversion)

### Methods

* [getInternalName](boolproperty.md#getinternalname)
* [parse](boolproperty.md#parse)
* [toJSON](boolproperty.md#tojson)

## Constructors

###  constructor

\+ **new BoolProperty**(`targetVersion`: [Version](version.md), `name`: string, `defaultValue?`: any, `onGetInitialValue?`: undefined | function): *[BoolProperty](boolproperty.md)*

*Inherited from [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`defaultValue?` | any |
`onGetInitialValue?` | undefined &#124; function |

**Returns:** *[BoolProperty](boolproperty.md)*

## Properties

### `Optional` `Readonly` defaultValue

• **defaultValue**? : *any*

*Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-readonly-defaultvalue)*

___

###  isSerializationEnabled

• **isSerializationEnabled**: *boolean* = true

*Inherited from [PropertyDefinition](propertydefinition.md).[isSerializationEnabled](propertydefinition.md#isserializationenabled)*

___

### `Readonly` name

• **name**: *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#readonly-name)*

___

### `Optional` `Readonly` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Inherited from [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-readonly-ongetinitialvalue)*

___

### `Readonly` sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#readonly-sequentialnumber)*

___

### `Readonly` targetVersion

• **targetVersion**: *[Version](version.md)*

*Inherited from [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#readonly-targetversion)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *boolean | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *boolean | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: object, `value`: boolean | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | object |
`value` | boolean &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
