[Adaptive Cards Templating Javascript SDK](../README.md) › [Binding](binding.md)

# Class: Binding

## Hierarchy

* **Binding**

## Index

### Constructors

* [constructor](binding.md#constructor)

### Properties

* [allowNull](binding.md#allownull)
* [expressionString](binding.md#expressionstring)

### Methods

* [evaluate](binding.md#evaluate)

## Constructors

###  constructor

\+ **new Binding**(`expressionString`: string, `expression`: EvaluationNode, `allowNull`: boolean): *[Binding](binding.md)*

*Defined in [expression-parser.ts:874](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L874)*

**Parameters:**

Name | Type | Default |
------ | ------ | ------ |
`expressionString` | string | - |
`expression` | EvaluationNode | - |
`allowNull` | boolean | true |

**Returns:** *[Binding](binding.md)*

## Properties

###  allowNull

• **allowNull**: *boolean*

*Defined in [expression-parser.ts:875](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L875)*

___

###  expressionString

• **expressionString**: *string*

*Defined in [expression-parser.ts:875](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L875)*

## Methods

###  evaluate

▸ **evaluate**(`context`: [EvaluationContext](evaluationcontext.md)): *LiteralValue*

*Defined in [expression-parser.ts:877](https://github.com/microsoft/AdaptiveCards/blob/689f58229/source/nodejs/adaptivecards-templating/src/expression-parser.ts#L877)*

**Parameters:**

Name | Type |
------ | ------ |
`context` | [EvaluationContext](evaluationcontext.md) |

**Returns:** *LiteralValue*
