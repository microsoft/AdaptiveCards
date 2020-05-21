[Adaptive Cards Javascript SDK](../README.md) › [NumProperty](numproperty.md)

# Class: NumProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **NumProperty**

## Index

### Constructors

* [constructor](numproperty.md#constructor)

### Properties

* [defaultValue](numproperty.md#optional-defaultvalue)
* [name](numproperty.md#name)
* [onGetInitialValue](numproperty.md#optional-ongetinitialvalue)
* [sequentialNumber](numproperty.md#sequentialnumber)
* [targetVersion](numproperty.md#targetversion)

### Methods

* [getInternalName](numproperty.md#getinternalname)
* [parse](numproperty.md#parse)
* [toJSON](numproperty.md#tojson)

## Constructors

###  constructor

\+ **new NumProperty**(`targetVersion`: [Version](version.md), `name`: string, `defaultValue?`: any, `onGetInitialValue?`: undefined | function): *[NumProperty](numproperty.md)*

*Inherited from [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

*Defined in [serialization.ts:258](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L258)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`defaultValue?` | any |
`onGetInitialValue?` | undefined &#124; function |

**Returns:** *[NumProperty](numproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *any*

*Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

*Defined in [serialization.ts:263](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L263)*

___

###  name

• **name**: *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

*Defined in [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L262)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Inherited from [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

*Defined in [serialization.ts:264](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L264)*

___

###  sequentialNumber

• **sequentialNumber**: *number*

*Inherited from [PropertyDefinition](propertydefinition.md).[sequentialNumber](propertydefinition.md#sequentialnumber)*

*Defined in [serialization.ts:258](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L258)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Inherited from [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

*Defined in [serialization.ts:261](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L261)*

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

*Defined in [serialization.ts:326](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L326)*

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

*Defined in [serialization.ts:330](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L330)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | number &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
