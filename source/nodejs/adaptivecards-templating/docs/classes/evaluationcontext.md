[Adaptive Cards Templating Javascript SDK](../README.md) › [EvaluationContext](evaluationcontext.md)

# Class: EvaluationContext

## Hierarchy

* **EvaluationContext**

## Index

### Properties

* [$data](evaluationcontext.md#data)
* [$index](evaluationcontext.md#index)
* [$root](evaluationcontext.md#root)

### Accessors

* [currentDataContext](evaluationcontext.md#currentdatacontext)

### Methods

* [getFunction](evaluationcontext.md#getfunction)
* [isReservedField](evaluationcontext.md#isreservedfield)
* [registerFunction](evaluationcontext.md#registerfunction)
* [restoreLastState](evaluationcontext.md#restorelaststate)
* [saveState](evaluationcontext.md#savestate)
* [unregisterFunction](evaluationcontext.md#unregisterfunction)
* [init](evaluationcontext.md#static-init)

## Properties

###  $data

• **$data**: *any*

*Defined in [expression-parser.ts:340](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L340)*

___

###  $index

• **$index**: *number*

*Defined in [expression-parser.ts:341](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L341)*

___

###  $root

• **$root**: *any*

*Defined in [expression-parser.ts:339](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L339)*

## Accessors

###  currentDataContext

• **get currentDataContext**(): *any*

*Defined in [expression-parser.ts:380](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L380)*

**Returns:** *any*

## Methods

###  getFunction

▸ **getFunction**(`name`: string): *FunctionCallback*

*Defined in [expression-parser.ts:351](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L351)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *FunctionCallback*

___

###  isReservedField

▸ **isReservedField**(`name`: string): *boolean*

*Defined in [expression-parser.ts:361](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L361)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *boolean*

___

###  registerFunction

▸ **registerFunction**(`name`: string, `callback`: FunctionCallback): *void*

*Defined in [expression-parser.ts:343](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L343)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |
`callback` | FunctionCallback |

**Returns:** *void*

___

###  restoreLastState

▸ **restoreLastState**(): *void*

*Defined in [expression-parser.ts:369](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L369)*

**Returns:** *void*

___

###  saveState

▸ **saveState**(): *void*

*Defined in [expression-parser.ts:365](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L365)*

**Returns:** *void*

___

###  unregisterFunction

▸ **unregisterFunction**(`name`: string): *void*

*Defined in [expression-parser.ts:347](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L347)*

**Parameters:**

Name | Type |
------ | ------ |
`name` | string |

**Returns:** *void*

___

### `Static` init

▸ **init**(): *void*

*Defined in [expression-parser.ts:201](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L201)*

**Returns:** *void*
