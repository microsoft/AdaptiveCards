[Adaptive Cards Javascript SDK](../README.md) › [EnumProperty](enumproperty.md)

# Class: EnumProperty <**TEnum**>

## Type parameters

▪ **TEnum**: *object*

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **EnumProperty**

## Index

### Constructors

* [constructor](enumproperty.md#constructor)

### Properties

* [defaultValue](enumproperty.md#optional-defaultvalue)
* [enumType](enumproperty.md#enumtype)
* [name](enumproperty.md#name)
* [onGetInitialValue](enumproperty.md#optional-ongetinitialvalue)
* [targetVersion](enumproperty.md#targetversion)

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

*Defined in [serialization.ts:523](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L523)*

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

### `Optional` defaultValue

• **defaultValue**? : *undefined | number*

*Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

*Defined in [serialization.ts:529](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L529)*

___

###  enumType

• **enumType**: *TEnum*

*Defined in [serialization.ts:528](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L528)*

___

###  name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

*Defined in [serialization.ts:527](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L527)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

*Defined in [serialization.ts:531](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L531)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

*Defined in [serialization.ts:526](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L526)*

## Accessors

###  values

• **get values**(): *[IVersionedValue](../interfaces/iversionedvalue.md)‹number›[]*

*Defined in [serialization.ts:548](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L548)*

**Returns:** *[IVersionedValue](../interfaces/iversionedvalue.md)‹number›[]*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

*Defined in [serialization.ts:244](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L244)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *number | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

*Defined in [serialization.ts:454](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L454)*

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

*Defined in [serialization.ts:491](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L491)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | number &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
