[Adaptive Cards Javascript SDK](../README.md) › [ActionProperty](actionproperty.md)

# Class: ActionProperty

## Hierarchy

* [PropertyDefinition](propertydefinition.md)

  ↳ **ActionProperty**

## Index

### Constructors

* [constructor](actionproperty.md#constructor)

### Properties

* [defaultValue](actionproperty.md#optional-defaultvalue)
* [forbiddenActionTypes](actionproperty.md#forbiddenactiontypes)
* [name](actionproperty.md#name)
* [onGetInitialValue](actionproperty.md#optional-ongetinitialvalue)
* [sequentialNumber](actionproperty.md#sequentialnumber)
* [targetVersion](actionproperty.md#targetversion)

### Methods

* [getInternalName](actionproperty.md#getinternalname)
* [parse](actionproperty.md#parse)
* [toJSON](actionproperty.md#tojson)

## Constructors

###  constructor

\+ **new ActionProperty**(`targetVersion`: [Version](version.md), `name`: string, `forbiddenActionTypes`: string[]): *[ActionProperty](actionproperty.md)*

*Overrides [PropertyDefinition](propertydefinition.md).[constructor](propertydefinition.md#constructor)*

*Defined in [card-elements.ts:611](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L611)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`targetVersion` | [Version](version.md) | - |
`name` | string | - |
`forbiddenActionTypes` | string[] | [] |

**Returns:** *[ActionProperty](actionproperty.md)*

## Properties

### `Optional` defaultValue

• **defaultValue**? : *any*

*Inherited from [PropertyDefinition](propertydefinition.md).[defaultValue](propertydefinition.md#optional-defaultvalue)*

*Defined in [serialization.ts:263](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L263)*

___

###  forbiddenActionTypes

• **forbiddenActionTypes**: *string[]*

*Defined in [card-elements.ts:616](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L616)*

___

###  name

• **name**: *string*

*Overrides [PropertyDefinition](propertydefinition.md).[name](propertydefinition.md#name)*

*Defined in [card-elements.ts:615](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L615)*

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

*Defined in [card-elements.ts:614](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L614)*

## Methods

###  getInternalName

▸ **getInternalName**(): *string*

*Inherited from [PropertyDefinition](propertydefinition.md).[getInternalName](propertydefinition.md#getinternalname)*

*Defined in [serialization.ts:246](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/serialization.ts#L246)*

**Returns:** *string*

___

###  parse

▸ **parse**(`sender`: [SerializableObject](serializableobject.md), `source`: [PropertyBag](../README.md#propertybag), `context`: [SerializationContext](serializationcontext.md)): *[Action](action.md) | undefined*

*Overrides [PropertyDefinition](propertydefinition.md).[parse](propertydefinition.md#parse)*

*Defined in [card-elements.ts:599](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L599)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`source` | [PropertyBag](../README.md#propertybag) |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *[Action](action.md) | undefined*

___

###  toJSON

▸ **toJSON**(`sender`: [SerializableObject](serializableobject.md), `target`: [PropertyBag](../README.md#propertybag), `value`: [Action](action.md) | undefined, `context`: [SerializationContext](serializationcontext.md)): *void*

*Overrides [PropertyDefinition](propertydefinition.md).[toJSON](propertydefinition.md#tojson)*

*Defined in [card-elements.ts:609](https://github.com/microsoft/AdaptiveCards/blob/899191664/source/nodejs/adaptivecards/src/card-elements.ts#L609)*

**Parameters:**

Name | Type |
------ | ------ |
`sender` | [SerializableObject](serializableobject.md) |
`target` | [PropertyBag](../README.md#propertybag) |
`value` | [Action](action.md) &#124; undefined |
`context` | [SerializationContext](serializationcontext.md) |

**Returns:** *void*
