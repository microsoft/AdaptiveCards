[Adaptive Cards Javascript SDK](../README.md) › [ValueSetProperty](valuesetproperty.md)

# Class: ValueSetProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **ValueSetProperty**

## Index

### Constructors

* [constructor](valuesetproperty.md#constructor)

### Properties

* [defaultValue](valuesetproperty.md#optional-defaultvalue)
* [name](valuesetproperty.md#name)
* [onGetInitialValue](valuesetproperty.md#optional-ongetinitialvalue)
* [targetVersion](valuesetproperty.md#targetversion)
* [values](valuesetproperty.md#values)

### Methods

* [getInternalName](valuesetproperty.md#getinternalname)
* [parse](valuesetproperty.md#parse)
* [toJSON](valuesetproperty.md#tojson)

## Constructors

###  constructor

\+ **new ValueSetProperty**(`targetVersion`: [Version](version.md), `name`: string, `values`: [IVersionedValue](../interfaces/iversionedvalue.md)‹string›[], `defaultValue?`: undefined | string, `onGetInitialValue?`: undefined | function): *[ValueSetProperty](valuesetproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

*Defined in [serialization.ts:439](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L439)*

**Parameters:**

Name | Type |
------ | ------ |
`targetVersion` | [Version](version.md) |
`name` | string |
`values` | [IVersionedValue](../interfaces/iversionedvalue.md)‹string›[] |
`defaultValue?` | undefined &#124; string |
`onGetInitialValue?` | undefined &#124; function |

**Returns:** *[ValueSetProperty](valuesetproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *undefined | string*

*Overrides [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

*Defined in [serialization.ts:445](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L445)*

___

###  name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

*Defined in [serialization.ts:443](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L443)*

___

### `Optional` onGetInitialValue

• **onGetInitialValue**? : *undefined | function*

*Overrides [PropertyDefinition](propertydefinition.md).[onGetInitialValue](propertydefinition.md#optional-ongetinitialvalue)*

*Defined in [serialization.ts:446](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L446)*

___

###  targetVersion

• **targetVersion**: *[Version](version.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[targetVersion](propertydefinition.md#targetversion)*

*Defined in [serialization.ts:442](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L442)*

___

###  values

• **values**: *[IVersionedValue](../interfaces/iversionedvalue.md)‹string›[]*

*Defined in [serialization.ts:444](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L444)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

*Defined in [serialization.ts:244](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L244)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [BaseSerializationContext](baseserializationcontext.md)): *string | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

*Defined in [serialization.ts:377](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L377)*

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

*Defined in [serialization.ts:412](https://github.com/microsoft/AdaptiveCards/blob/8588bd5ad/source/nodejs/adaptivecards/src/serialization.ts#L412)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | string &#124; undefined |
`context` | [BaseSerializationContext](baseserializationcontext.md) |

**Returns:** *void*
