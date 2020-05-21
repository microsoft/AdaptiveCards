[Adaptive Cards Javascript SDK](../README.md) › [PropertyDefinition](propertydefinition.md)

# Class: PropertyDefinition

## Hierarchy

* **PropertyDefinition**

  ↳ [StringProperty](stringproperty.md)

  ↳ [BoolProperty](boolproperty.md)

  ↳ [NumProperty](numproperty.md)

  ↳ [PixelSizeProperty](pixelsizeproperty.md)

  ↳ [ValueSetProperty](valuesetproperty.md)

  ↳ [EnumProperty](enumproperty.md)

  ↳ [SerializableObjectProperty](serializableobjectproperty.md)

  ↳ [SerializableObjectCollectionProperty](serializableobjectcollectionproperty.md)

  ↳ [CustomProperty](customproperty.md)

  ↳ [ActionProperty](actionproperty.md)

## Index

### Constructors

* [constructor](propertydefinition.md#constructor)

### Properties

* [defaultValue](propertydefinition.md#optional-defaultvalue)
* [name](propertydefinition.md#name)
* [onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)
* [sequentialNumber](propertydefinition.md#sequentialnumber)
* [targetVersion](propertydefinition.md#targetversion)

### Methods

* [getInternalName](propertydefinition.md#getinternalname)
* [parse](propertydefinition.md#parse)
* [toJSON](propertydefinition.md#tojson)

## Constructors

###  constructor

\+ **new PropertyDefinition**(`targetVersion`: [Version](version.md), `name`: string, `defaultValue?`: any, `onGetInitialValue?`: undefined | function): *[PropertyDefinition](propertydefinition.md)*

*Defined in [serialization.ts:258](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L258)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`defaultValue?` | any |
`onGetInitialValue?` | undefined &#124; function |

**Returns:** *[PropertyDefinition](propertydefinition.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *any*

*Defined in [serialization.ts:263](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L263)*

___

###  name

• **name**: *string*

*Defined in [serialization.ts:262](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L262)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Defined in [serialization.ts:264](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L264)*

___

###  sequentialNumber

• **sequentialNumber**: *number*

*Defined in [serialization.ts:258](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L258)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Defined in [serialization.ts:261](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L261)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Defined in [serialization.ts:246](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L246)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *any*

*Defined in [serialization.ts:250](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L250)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *any*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: any, `context`: [BaseSerializationContext](baseserializationcontext.md)): *void*

*Defined in [serialization.ts:254](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L254)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | any |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
