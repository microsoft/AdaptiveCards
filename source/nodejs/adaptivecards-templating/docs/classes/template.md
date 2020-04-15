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

## Constructors

###  constructor

\+ **new Template**(`payload`: any): *[Template](template.md)*

*Defined in [template-engine.ts:354](https://github.com/microsoft/AdaptiveCards/blob/3a9538575/source/nodejs/adaptivecards-templating/src/template-engine.ts#L354)*

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

*Defined in [template-engine.ts:432](https://github.com/microsoft/AdaptiveCards/blob/3a9538575/source/nodejs/adaptivecards-templating/src/template-engine.ts#L432)*

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
`context` | [IEvaluationContext](../interfaces/ievaluationcontext.md) | The context to bind the template to.  |

**Returns:** *any*
