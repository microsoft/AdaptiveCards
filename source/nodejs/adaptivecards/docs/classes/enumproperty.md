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
* [sequentialNumber](enumproperty.md#sequentialnumber)
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

*Defined in [serialization.ts:531](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L531)*

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

*Defined in [serialization.ts:537](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L537)*

___

###  enumType

• **enumType**: *TEnum*

*Defined in [serialization.ts:536](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L536)*

___

###  name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

*Defined in [serialization.ts:535](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L535)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

*Defined in [serialization.ts:539](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L539)*

___

###  sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#sequentialnumber)*

*Defined in [serialization.ts:258](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L258)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

*Defined in [serialization.ts:534](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L534)*

## Accessors

###  values

• **get values**(): *[IVersionedValue](../interfaces/iversionedvalue.md)‹number›[]*

*Defined in [serialization.ts:556](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L556)*

**Returns:** *[IVersionedValue](../interfaces/iversionedvalue.md)‹number›[]*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

*Defined in [serialization.ts:246](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L246)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *number | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

*Defined in [serialization.ts:462](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L462)*

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

*Defined in [serialization.ts:499](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L499)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | number &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
