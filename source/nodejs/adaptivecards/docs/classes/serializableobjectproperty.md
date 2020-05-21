[Adaptive Cards Javascript SDK](../README.md) › [SerializableObjectProperty](serializableobjectproperty.md)

# Class: SerializableObjectProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **SerializableObjectProperty**

## Index

### Constructors

* [constructor](serializableobjectproperty.md#constructor)

### Properties

* [defaultValue](serializableobjectproperty.md#optional-defaultvalue)
* [name](serializableobjectproperty.md#name)
* [objectType](serializableobjectproperty.md#objecttype)
* [onGetInitialValue](serializableobjectproperty.md#optional-ongetinitialvalue)
* [sequentialNumber](serializableobjectproperty.md#sequentialnumber)
* [targetVersion](serializableobjectproperty.md#targetversion)

### Methods

* [getInternalName](serializableobjectproperty.md#getinternalname)
* [parse](serializableobjectproperty.md#parse)
* [toJSON](serializableobjectproperty.md#tojson)

## Constructors

###  constructor

\+ **new SerializableObjectProperty**(`targetVersion`: [Version](version.md), `name`: string, `objectType`: [SerializableObjectType](../README.md#serializableobjecttype)): *[SerializableObjectProperty](serializableobjectproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

*Defined in [serialization.ts:585](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L585)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`objectType` | [SerializableObjectType](../README.md#serializableobjecttype) |

**Returns:** *[SerializableObjectProperty](serializableobjectproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *any*

*Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

*Defined in [serialization.ts:263](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L263)*

___

###  name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

*Defined in [serialization.ts:589](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L589)*

___

###  objectType

• **objectType**: *[SerializableObjectType](../README.md#serializableobjecttype)*

*Defined in [serialization.ts:590](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L590)*

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

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

*Defined in [serialization.ts:588](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L588)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

*Defined in [serialization.ts:246](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L246)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *[SerializableObject](serializableobject.md) | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

*Defined in [serialization.ts:564](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L564)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *[SerializableObject](serializableobject.md) | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: [SerializableObject](serializableobject.md) | undefined, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

*Defined in [serialization.ts:577](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L577)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | [SerializableObject](serializableobject.md) &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
