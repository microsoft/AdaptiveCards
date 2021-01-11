[Adaptive Cards Javascript SDK](../README.md) › [EnumProperty](enumproperty.md)

# Class: EnumProperty ‹**TEnum**›

## Type parameters

▪ **TEnum**: *object*

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **EnumProperty**

## Index

### Constructors

* [constructor](enumproperty.md#constructor)

### Properties

* [defaultValue](enumproperty.md#optional-readonly-defaultvalue)
* [enumType](enumproperty.md#readonly-enumtype)
* [isSerializationEnabled](enumproperty.md#isserializationenabled)
* [name](enumproperty.md#readonly-name)
* [onGetInitialValue](enumproperty.md#optional-readonly-ongetinitialvalue)
* [sequentialNumber](enumproperty.md#readonly-sequentialnumber)
* [targetVersion](enumproperty.md#readonly-targetversion)

### Accessors

* [values](enumproperty.md#values)

### Methods

* [getInternalName](enumproperty.md#getinternalname)
* [parse](enumproperty.md#parse)
* [toJSON](enumproperty.md#tojson)

## Constructors

###  constructor

\+ **new EnumProperty**(`targetVersion`: [Version](version.md), `name`: string, `enumType`: TEnum, `defaultValue?`: undefined | number, `values?`: [IVersionedValue](../interfaces/iversionedvalue.md)‹number›[], `onGetInitialValue?`: undefined | function): *[EnumProperty](enumproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`enumType` | TEnum |
`defaultValue?` | undefined &#124; number |
`values?` | [IVersionedValue](../interfaces/iversionedvalue.md)‹number›[] |
`onGetInitialValue?` | undefined &#124; function |

**Returns:** *[EnumProperty](enumproperty.md)*

## Properties

### `Optional` `Readonly` defaultValue

• **defaultValue**? : *undefined | number*

*Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-readonly-defaultvalue)*

___

### `Readonly` enumType

• **enumType**: *TEnum*

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

### `Readonly` sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#readonly-sequentialnumber)*

___

### `Readonly` targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#readonly-targetversion)*

## Accessors

###  values

• **get values**(): *[IVersionedValue](../interfaces/iversionedvalue.md)‹number›[]*

**Returns:** *[IVersionedValue](../interfaces/iversionedvalue.md)‹number›[]*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *number | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *number | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: number | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | number &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
