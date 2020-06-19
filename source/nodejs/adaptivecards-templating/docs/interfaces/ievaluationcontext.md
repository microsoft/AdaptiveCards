[Adaptive Cards Templating Javascript SDK](../README.md) › [IEvaluationContext](ievaluationcontext.md)

# Interface: IEvaluationContext

Holds the context used to expand a template.

## Hierarchy

* **IEvaluationContext**

## Index

### Properties

* [$root](ievaluationcontext.md#root)

## Properties

###  $root

• **$root**: *any*

*Defined in [template-engine.ts:118](https://github.com/microsoft/AdaptiveCards/blob/bf1bfa514/source/nodejs/adaptivecards-templating/src/template-engine.ts#L118)*

The root data object the template will bind to. Expressions that refer to $root in the template payload
map to this field. Initially, $data also maps to $root.
