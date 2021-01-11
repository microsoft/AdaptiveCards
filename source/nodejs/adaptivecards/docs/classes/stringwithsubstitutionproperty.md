[Adaptive Cards Javascript SDK](../README.md) › [StringWithSubstitutionProperty](stringwithsubstitutionproperty.md)

# Class: StringWithSubstitutionProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **StringWithSubstitutionProperty**

## Index

### Constructors

* [constructor](stringwithsubstitutionproperty.md#constructor)

### Properties

* [defaultValue](stringwithsubstitutionproperty.md#optional-readonly-defaultvalue)
* [isSerializationEnabled](stringwithsubstitutionproperty.md#isserializationenabled)
* [name](stringwithsubstitutionproperty.md#readonly-name)
* [onGetInitialValue](stringwithsubstitutionproperty.md#optional-readonly-ongetinitialvalue)
* [sequentialNumber](stringwithsubstitutionproperty.md#readonly-sequentialnumber)
* [targetVersion](stringwithsubstitutionproperty.md#readonly-targetversion)

### Methods

* [getInternalName](stringwithsubstitutionproperty.md#getinternalname)
* [parse](stringwithsubstitutionproperty.md#parse)
* [toJSON](stringwithsubstitutionproperty.md#tojson)

## Constructors

###  constructor

\+ **new StringWithSubstitutionProperty**(`targetVersion`: [Version](version.md), `name`: string): *[StringWithSubstitutionProperty](stringwithsubstitutionproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |

**Returns:** *[StringWithSubstitutionProperty](stringwithsubstitutionproperty.md)*

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

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#readonly-name)*

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

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#readonly-targetversion)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *[StringWithSubstitutions](stringwithsubstitutions.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[StringWithSubstitutions](stringwithsubstitutions.md)*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: [StringWithSubstitutions](stringwithsubstitutions.md), `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | [StringWithSubstitutions](stringwithsubstitutions.md) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
