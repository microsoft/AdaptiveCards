[Adaptive Cards Templating Javascript SDK](../README.md) › [Template](template.md)

# Class: Template

Represents a template that can be bound to data.

## Hierarchy

* **Template**

## Index

### Constructors

* [constructor](template.md#constructor)

### Methods

* [expand](template.md#expand)
* [parseInterpolatedString](template.md#static-parseinterpolatedstring)
* [tryEvaluateExpression](template.md#static-tryevaluateexpression)

## Constructors

###  constructor

\+ **new Template**(`payload`: any): *[Template](template.md)*

*Defined in [template-engine.ts:394](https://github.com/microsoft/AdaptiveCards/blob/bf1bfa514/source/nodejs/adaptivecards-templating/src/template-engine.ts#L394)*

Initializes a new Template instance based on the provided payload.
Once created, the instance can be bound to different data objects
in a loop.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`payload` | any | The template payload.  |

**Returns:** *[Template](template.md)*

## Methods

###  expand

▸ **expand**(`context`: [IEvaluationContext](../interfaces/ievaluationcontext.md)): *any*

*Defined in [template-engine.ts:474](https://github.com/microsoft/AdaptiveCards/blob/bf1bfa514/source/nodejs/adaptivecards-templating/src/template-engine.ts#L474)*

Expands the template using the provided context. Template expansion involves
evaluating the expressions used in the original template payload, as well as
repeating (expanding) parts of that payload that are bound to arrays.

Example:

```typescript
let context = {
    $root: {
        firstName: "John",
        lastName: "Doe",
        children: [
            { fullName: "Jane Doe", age: 9 },
            { fullName: "Alex Doe", age: 12 }
        ]
    }
}

let templatePayload = {
    type: "AdaptiveCard",
    version: "1.2",
    body: [
        {
            type: "TextBlock",
            text: "${firstName} ${lastName}"
        },
        {
            type: "TextBlock",
            $data: "${children}",
            text: "${fullName} (${age})"
        }
    ]
}

let template = new Template(templatePayload);

let expandedTemplate = template.expand(context);
```

With the above code, the value of `expandedTemplate` will be

```json
{
    type: "AdaptiveCard",
    version: "1.2",
    body: [
        {
            type: "TextBlock",
            text: "John Doe"
        },
        {
            type: "TextBlock",
            text: "Jane Doe (9)"
        },
        {
            type: "TextBlock",
            text: "Alex Doe (12)"
        }
    ]
}
```

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`context` | [IEvaluationContext](../interfaces/ievaluationcontext.md) | The context to bind the template to. |

**Returns:** *any*

A value representing the expanded template. The type of that value
  is dependent on the type of the original template payload passed to the constructor.

___

### `Static` parseInterpolatedString

▸ **parseInterpolatedString**(`interpolatedString`: string): *Expression | string*

*Defined in [template-engine.ts:212](https://github.com/microsoft/AdaptiveCards/blob/bf1bfa514/source/nodejs/adaptivecards-templating/src/template-engine.ts#L212)*

Parses an interpolated string into an Expression object ready to evaluate.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`interpolatedString` | string | The interpolated string to parse. Example: "Hello ${name}" |

**Returns:** *Expression | string*

An Expression object if the provided interpolated string contained at least one expression (e.g. "${expression}"); the original string otherwise.

___

### `Static` tryEvaluateExpression

▸ **tryEvaluateExpression**(`expression`: Expression, `context`: [IEvaluationContext](../interfaces/ievaluationcontext.md), `allowSubstitutions`: boolean): *object*

*Defined in [template-engine.ts:263](https://github.com/microsoft/AdaptiveCards/blob/bf1bfa514/source/nodejs/adaptivecards-templating/src/template-engine.ts#L263)*

Tries to evaluate the provided expression using the provided context.

**Parameters:**

Name | Type | Description |
------ | ------ | ------ |
`expression` | Expression | The expression to evaluate. |
`context` | [IEvaluationContext](../interfaces/ievaluationcontext.md) | The context (data) used to evaluate the expression. |
`allowSubstitutions` | boolean | Indicates if the expression evaluator should substitute undefined value with a default   string or the value returned by the GlobalSettings.getUndefinedFieldValueSubstitutionString callback. |

**Returns:** *object*

An object representing the result of the evaluation. If the evaluation succeeded, the value property
  contains the actual evaluation result, and the error property is undefined. If the evaluation fails, the error
  property contains a message detailing the error that occurred.

* **error**: *string*

* **value**: *any*
