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
* [targetVersion](propertydefinition.md#targetversion)

### Methods

* [getInternalName](propertydefinition.md#getinternalname)
* [parse](propertydefinition.md#parse)
* [toJSON](propertydefinition.md#tojson)

## Constructors

###  constructor

\+ **new PropertyDefinition**(`targetVersion`: [Version](version.md), `name`: string, `defaultValue?`: any, `onGetInitialValue?`: undefined | function): *[PropertyDefinition](propertydefinition.md)*

*Defined in [serialization.ts:254](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L254)*

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

*Defined in [serialization.ts:259](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L259)*

___

###  name

• **name**: *string*

*Defined in [serialization.ts:258](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L258)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Defined in [serialization.ts:260](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L260)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Defined in [serialization.ts:257](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L257)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Defined in [serialization.ts:244](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L244)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *any*

*Defined in [serialization.ts:248](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L248)*

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

*Defined in [serialization.ts:252](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L252)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | any |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
