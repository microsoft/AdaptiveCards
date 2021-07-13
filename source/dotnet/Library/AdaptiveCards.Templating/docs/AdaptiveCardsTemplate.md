<a name='assembly'></a>
# AdaptiveCards.Templating

## Contents

- [AdaptiveCardTemplate](#T-AdaptiveCards-Templating-AdaptiveCardTemplate 'AdaptiveCards.Templating.AdaptiveCardTemplate')
  - [#ctor(jsonTemplate)](#M-AdaptiveCards-Templating-AdaptiveCardTemplate-#ctor-System-Object- 'AdaptiveCards.Templating.AdaptiveCardTemplate.#ctor(System.Object)')
  - [Template](#P-AdaptiveCards-Templating-AdaptiveCardTemplate-Template 'AdaptiveCards.Templating.AdaptiveCardTemplate.Template')
  - [Expand(context,nullSubstitutionOption)](#M-AdaptiveCards-Templating-AdaptiveCardTemplate-Expand-AdaptiveCards-Templating-EvaluationContext,System-Func{System-String,System-Object}- 'AdaptiveCards.Templating.AdaptiveCardTemplate.Expand(AdaptiveCards.Templating.EvaluationContext,System.Func{System.String,System.Object})')
  - [Expand(rootData,nullSubstitutionOption)](#M-AdaptiveCards-Templating-AdaptiveCardTemplate-Expand-System-Object,System-Func{System-String,System-Object}- 'AdaptiveCards.Templating.AdaptiveCardTemplate.Expand(System.Object,System.Func{System.String,System.Object})')
- [AdaptiveTemplateException](#T-AdaptiveCards-Templating-AdaptiveTemplateException 'AdaptiveCards.Templating.AdaptiveTemplateException')
  - [#ctor()](#M-AdaptiveCards-Templating-AdaptiveTemplateException-#ctor 'AdaptiveCards.Templating.AdaptiveTemplateException.#ctor')
  - [#ctor(message)](#M-AdaptiveCards-Templating-AdaptiveTemplateException-#ctor-System-String- 'AdaptiveCards.Templating.AdaptiveTemplateException.#ctor(System.String)')
  - [#ctor(message,innerException)](#M-AdaptiveCards-Templating-AdaptiveTemplateException-#ctor-System-String,System-Exception- 'AdaptiveCards.Templating.AdaptiveTemplateException.#ctor(System.String,System.Exception)')
- [EvaluationContext](#T-AdaptiveCards-Templating-EvaluationContext 'AdaptiveCards.Templating.EvaluationContext')
  - [#ctor()](#M-AdaptiveCards-Templating-EvaluationContext-#ctor 'AdaptiveCards.Templating.EvaluationContext.#ctor')
  - [#ctor(rootData)](#M-AdaptiveCards-Templating-EvaluationContext-#ctor-System-Object- 'AdaptiveCards.Templating.EvaluationContext.#ctor(System.Object)')
  - [Data](#P-AdaptiveCards-Templating-EvaluationContext-Data 'AdaptiveCards.Templating.EvaluationContext.Data')
  - [Index](#P-AdaptiveCards-Templating-EvaluationContext-Index 'AdaptiveCards.Templating.EvaluationContext.Index')
  - [NullSubstitution](#P-AdaptiveCards-Templating-EvaluationContext-NullSubstitution 'AdaptiveCards.Templating.EvaluationContext.NullSubstitution')
  - [Root](#P-AdaptiveCards-Templating-EvaluationContext-Root 'AdaptiveCards.Templating.EvaluationContext.Root')
  - [SetValue()](#M-AdaptiveCards-Templating-EvaluationContext-SetValue-System-String,System-Object- 'AdaptiveCards.Templating.EvaluationContext.SetValue(System.String,System.Object)')
  - [SmartAssign(value)](#M-AdaptiveCards-Templating-EvaluationContext-SmartAssign-Newtonsoft-Json-Linq-JToken- 'AdaptiveCards.Templating.EvaluationContext.SmartAssign(Newtonsoft.Json.Linq.JToken)')
  - [TryGetValue()](#M-AdaptiveCards-Templating-EvaluationContext-TryGetValue-System-String,System-Object@- 'AdaptiveCards.Templating.EvaluationContext.TryGetValue(System.String,System.Object@)')
  - [Version()](#M-AdaptiveCards-Templating-EvaluationContext-Version 'AdaptiveCards.Templating.EvaluationContext.Version')
- [ObjectPath](#T-AdaptiveCards-Templating-ObjectPath 'AdaptiveCards.Templating.ObjectPath')
  - [Assign(startObject,overlayObject,type)](#M-AdaptiveCards-Templating-ObjectPath-Assign-System-Object,System-Object,System-Type- 'AdaptiveCards.Templating.ObjectPath.Assign(System.Object,System.Object,System.Type)')
  - [Assign\`\`1(startObject,overlayObject)](#M-AdaptiveCards-Templating-ObjectPath-Assign``1-System-Object,System-Object- 'AdaptiveCards.Templating.ObjectPath.Assign``1(System.Object,System.Object)')
  - [Clone\`\`1(obj)](#M-AdaptiveCards-Templating-ObjectPath-Clone``1-``0- 'AdaptiveCards.Templating.ObjectPath.Clone``1(``0)')
  - [ContainsProperty(obj,name)](#M-AdaptiveCards-Templating-ObjectPath-ContainsProperty-System-Object,System-String- 'AdaptiveCards.Templating.ObjectPath.ContainsProperty(System.Object,System.String)')
  - [ForEachProperty(obj,action)](#M-AdaptiveCards-Templating-ObjectPath-ForEachProperty-System-Object,System-Action{System-String,System-Object}- 'AdaptiveCards.Templating.ObjectPath.ForEachProperty(System.Object,System.Action{System.String,System.Object})')
  - [GetNormalizedValue(value,json)](#M-AdaptiveCards-Templating-ObjectPath-GetNormalizedValue-System-Object,System-Boolean- 'AdaptiveCards.Templating.ObjectPath.GetNormalizedValue(System.Object,System.Boolean)')
  - [GetObjectProperty(obj,property)](#M-AdaptiveCards-Templating-ObjectPath-GetObjectProperty-System-Object,System-String- 'AdaptiveCards.Templating.ObjectPath.GetObjectProperty(System.Object,System.String)')
  - [GetPathValue\`\`1(obj,path)](#M-AdaptiveCards-Templating-ObjectPath-GetPathValue``1-System-Object,System-String- 'AdaptiveCards.Templating.ObjectPath.GetPathValue``1(System.Object,System.String)')
  - [GetPathValue\`\`1(obj,path,defaultValue)](#M-AdaptiveCards-Templating-ObjectPath-GetPathValue``1-System-Object,System-String,``0- 'AdaptiveCards.Templating.ObjectPath.GetPathValue``1(System.Object,System.String,``0)')
  - [GetProperties(obj)](#M-AdaptiveCards-Templating-ObjectPath-GetProperties-System-Object- 'AdaptiveCards.Templating.ObjectPath.GetProperties(System.Object)')
  - [HasValue(obj,path)](#M-AdaptiveCards-Templating-ObjectPath-HasValue-System-Object,System-String- 'AdaptiveCards.Templating.ObjectPath.HasValue(System.Object,System.String)')
  - [MapValueTo\`\`1(val)](#M-AdaptiveCards-Templating-ObjectPath-MapValueTo``1-System-Object- 'AdaptiveCards.Templating.ObjectPath.MapValueTo``1(System.Object)')
  - [Merge\`\`1(startObject,overlayObject)](#M-AdaptiveCards-Templating-ObjectPath-Merge``1-``0,``0- 'AdaptiveCards.Templating.ObjectPath.Merge``1(``0,``0)')
  - [RemovePathValue(obj,path)](#M-AdaptiveCards-Templating-ObjectPath-RemovePathValue-System-Object,System-String- 'AdaptiveCards.Templating.ObjectPath.RemovePathValue(System.Object,System.String)')
  - [SetObjectSegment(obj,segment,value,json)](#M-AdaptiveCards-Templating-ObjectPath-SetObjectSegment-System-Object,System-Object,System-Object,System-Boolean- 'AdaptiveCards.Templating.ObjectPath.SetObjectSegment(System.Object,System.Object,System.Object,System.Boolean)')
  - [SetPathValue(obj,path,value,json)](#M-AdaptiveCards-Templating-ObjectPath-SetPathValue-System-Object,System-String,System-Object,System-Boolean- 'AdaptiveCards.Templating.ObjectPath.SetPathValue(System.Object,System.String,System.Object,System.Boolean)')
  - [TryGetPathValue\`\`1(obj,path,value)](#M-AdaptiveCards-Templating-ObjectPath-TryGetPathValue``1-System-Object,System-String,``0@- 'AdaptiveCards.Templating.ObjectPath.TryGetPathValue``1(System.Object,System.String,``0@)')
  - [TryResolvePath(obj,propertyPath,segments,eval)](#M-AdaptiveCards-Templating-ObjectPath-TryResolvePath-System-Object,System-String,System-Collections-Generic-List{System-Object}@,System-Boolean- 'AdaptiveCards.Templating.ObjectPath.TryResolvePath(System.Object,System.String,System.Collections.Generic.List{System.Object}@,System.Boolean)')

<a name='T-AdaptiveCards-Templating-AdaptiveCardTemplate'></a>
## AdaptiveCardTemplate `type`

##### Namespace

AdaptiveCards.Templating

##### Summary

The main `AdaptiveCardTemplate` class
Contain all methods for performaing data binding to `AdaptiveCardTemplate`

<a name='M-AdaptiveCards-Templating-AdaptiveCardTemplate-#ctor-System-Object-'></a>
### #ctor(jsonTemplate) `constructor`

##### Summary

Creates an instance of AdaptiveCardTemplate

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| jsonTemplate | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | json string or seriazable object |

##### Example

```
 var jsonTemplate = "
 {
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "TextBlock",
            "text": "Hello ${person.firstName}"
        }
    ]
}"
 var template = new AdaptiveCardTemplate(jsonTemplate);
 
```

##### Remarks

Once created, it will contain a parsed tree based on jsonTemplate

Data is bound by calling `Expand` on the object

The intance can be rebound with different data by calling `Expand`

[Expand](#M-AdaptiveCards-Templating-AdaptiveCardTemplate-Expand-AdaptiveCards-Templating-EvaluationContext,System-Func{System-String,System-Object}- 'AdaptiveCards.Templating.AdaptiveCardTemplate.Expand(AdaptiveCards.Templating.EvaluationContext,System.Func{System.String,System.Object})')

<a name='P-AdaptiveCards-Templating-AdaptiveCardTemplate-Template'></a>
### Template `property`

##### Summary

Gets the Parsed Template.

<a name='M-AdaptiveCards-Templating-AdaptiveCardTemplate-Expand-AdaptiveCards-Templating-EvaluationContext,System-Func{System-String,System-Object}-'></a>
### Expand(context,nullSubstitutionOption) `method`

##### Summary

Bind data in `context` to the instance of AdaptiveCardTemplate

##### Returns

json as string

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| context | [AdaptiveCards.Templating.EvaluationContext](#T-AdaptiveCards-Templating-EvaluationContext 'AdaptiveCards.Templating.EvaluationContext') | provides data context |
| nullSubstitutionOption | [System.Func{System.String,System.Object}](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Func 'System.Func{System.String,System.Object}') | defines behavior when no suitable data is found for a template entry |

##### Example

```
var template = new AdaptiveCardTemplate(jsonTemplate);
var context = new AdaptiveCardsEvaluationContext(jsonData);
template.Expand(context);
```

##### Remarks

Data can be also inlined in AdaptiveCardTemplate payload

Expand can be called multiple times with different or same `context`

Returned string can be invalid AdaptiveCards, such validation will be performed by AdaptiveCards Parser

`nullSubstitutionOption` defines behavior when no suitable data is found for a template entry

Default behavior is leaving templated string unchanged

##### See Also

- [AdaptiveCards.Templating.EvaluationContext](#T-AdaptiveCards-Templating-EvaluationContext 'AdaptiveCards.Templating.EvaluationContext')

<a name='M-AdaptiveCards-Templating-AdaptiveCardTemplate-Expand-System-Object,System-Func{System-String,System-Object}-'></a>
### Expand(rootData,nullSubstitutionOption) `method`

##### Summary

Create a root data context using `rootData`, and bind it to the instance of AdaptiveCardTemplate

##### Returns

json as string

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| rootData | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | Serializable object or a string in valid json format that will be used as data context |
| nullSubstitutionOption | [System.Func{System.String,System.Object}](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Func 'System.Func{System.String,System.Object}') | Defines behavior when no suitable data is found for a template entry |

##### Example

```
var template = new AdaptiveCardTemplate(jsonTemplate);
template.Expand(rootData);
```

##### Remarks

Data can be also inlined in AdaptiveCardTemplate payload

Expand can be called multiple times with different or same `rootData`

Returned string can be invalid AdaptiveCards, such validation will be performed by AdaptiveCards Parser

`nullSubstitutionOption` defines behavior when no suitable data is found for a template entry

Default behavior is leaving templated string unchanged

##### See Also

- [AdaptiveCards.Templating.EvaluationContext](#T-AdaptiveCards-Templating-EvaluationContext 'AdaptiveCards.Templating.EvaluationContext')

<a name='T-AdaptiveCards-Templating-AdaptiveTemplateException'></a>
## AdaptiveTemplateException `type`

##### Namespace

AdaptiveCards.Templating

##### Summary

AdaptiveCardTemplate Library's Exception class

<a name='M-AdaptiveCards-Templating-AdaptiveTemplateException-#ctor'></a>
### #ctor() `constructor`

##### Summary

Default constructor

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-Templating-AdaptiveTemplateException-#ctor-System-String-'></a>
### #ctor(message) `constructor`

##### Summary

Constructor that takes single argument that is exception message

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| message | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The error message that explains the reason for the exception |

<a name='M-AdaptiveCards-Templating-AdaptiveTemplateException-#ctor-System-String,System-Exception-'></a>
### #ctor(message,innerException) `constructor`

##### Summary

Constructor that takes message and inner exception to pass

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| message | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | The error message that explains the reason for the exception |
| innerException | [System.Exception](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Exception 'System.Exception') | The exception that is the cause of the current exception |

<a name='T-AdaptiveCards-Templating-EvaluationContext'></a>
## EvaluationContext `type`

##### Namespace

AdaptiveCards.Templating

##### Summary

Provides Data Context to AdaptiveCardsTemplate Parser

<a name='M-AdaptiveCards-Templating-EvaluationContext-#ctor'></a>
### #ctor() `constructor`

##### Summary

default consturctor

##### Parameters

This constructor has no parameters.

<a name='M-AdaptiveCards-Templating-EvaluationContext-#ctor-System-Object-'></a>
### #ctor(rootData) `constructor`

##### Summary

constructor for `EvaluationContext` that takes one argument that will be used for root data context

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| rootData | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') |  |

<a name='P-AdaptiveCards-Templating-EvaluationContext-Data'></a>
### Data `property`

##### Summary

Provides Data Context

##### Example

```
 
 string jsonData = @"{
     ""person"": {
         ""firstName"": ""Hello"",
         ""lastName"": ""World""
 }";
 var context = new EvaluationContext()
 {
     Data = jsonData
 };
 
```

<a name='P-AdaptiveCards-Templating-EvaluationContext-Index'></a>
### Index `property`

##### Summary

gets or sets current iteration index.

<a name='P-AdaptiveCards-Templating-EvaluationContext-NullSubstitution'></a>
### NullSubstitution `property`

##### Summary

Null substitution

<a name='P-AdaptiveCards-Templating-EvaluationContext-Root'></a>
### Root `property`

##### Summary

Provides Root Data Context

##### Example

```
 
 string jsonData = @"{
     ""person"": {
         ""firstName"": ""Hello"",
         ""lastName"": ""World""
 }";
 var context = new EvaluationContext()
 {
     Root = jsonData
 };
 
```

<a name='M-AdaptiveCards-Templating-EvaluationContext-SetValue-System-String,System-Object-'></a>
### SetValue() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-Templating-EvaluationContext-SmartAssign-Newtonsoft-Json-Linq-JToken-'></a>
### SmartAssign(value) `method`

##### Summary

SmartAssign text values

##### Returns

jtoken.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| value | [Newtonsoft.Json.Linq.JToken](#T-Newtonsoft-Json-Linq-JToken 'Newtonsoft.Json.Linq.JToken') | jtoken to evaluate. |

##### Remarks

If a value is a string this will attempt to deserialize as JSON, other wise it will call back to text

<a name='M-AdaptiveCards-Templating-EvaluationContext-TryGetValue-System-String,System-Object@-'></a>
### TryGetValue() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='M-AdaptiveCards-Templating-EvaluationContext-Version'></a>
### Version() `method`

##### Summary

*Inherit from parent.*

##### Parameters

This method has no parameters.

<a name='T-AdaptiveCards-Templating-ObjectPath'></a>
## ObjectPath `type`

##### Namespace

AdaptiveCards.Templating

##### Summary

Helper methods for working with dynamic json objects.

<a name='M-AdaptiveCards-Templating-ObjectPath-Assign-System-Object,System-Object,System-Type-'></a>
### Assign(startObject,overlayObject,type) `method`

##### Summary

Equivalent to javascripts ObjectPath.Assign, creates a new object from startObject overlaying any non-null values from the overlay object.

##### Returns

merged object.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| startObject | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | intial object of any type. |
| overlayObject | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | overlay object of any type. |
| type | [System.Type](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Type 'System.Type') | type to output. |

<a name='M-AdaptiveCards-Templating-ObjectPath-Assign``1-System-Object,System-Object-'></a>
### Assign\`\`1(startObject,overlayObject) `method`

##### Summary

Equivalent to javascripts ObjectPath.Assign, creates a new object from startObject overlaying any non-null values from the overlay object.

##### Returns

merged object.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| startObject | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | intial object of any type. |
| overlayObject | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | overlay object of any type. |

##### Generic Types

| Name | Description |
| ---- | ----------- |
| T | The target type. |

<a name='M-AdaptiveCards-Templating-ObjectPath-Clone``1-``0-'></a>
### Clone\`\`1(obj) `method`

##### Summary

Clone an object.

##### Returns

The object as Json.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [\`\`0](#T-``0 '``0') | The object. |

##### Generic Types

| Name | Description |
| ---- | ----------- |
| T | Type to clone. |

<a name='M-AdaptiveCards-Templating-ObjectPath-ContainsProperty-System-Object,System-String-'></a>
### ContainsProperty(obj,name) `method`

##### Summary

Detects if property exists on object.

##### Returns

true if found.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | object. |
| name | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | name of the property. |

<a name='M-AdaptiveCards-Templating-ObjectPath-ForEachProperty-System-Object,System-Action{System-String,System-Object}-'></a>
### ForEachProperty(obj,action) `method`

##### Summary

Apply an action to all properties in an object.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | Object to map against. |
| action | [System.Action{System.String,System.Object}](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Action 'System.Action{System.String,System.Object}') | Action to take. |

<a name='M-AdaptiveCards-Templating-ObjectPath-GetNormalizedValue-System-Object,System-Boolean-'></a>
### GetNormalizedValue(value,json) `method`

##### Summary

Normalize value as json objects.

##### Returns

normalized value.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| value | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | value to normalize. |
| json | [System.Boolean](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Boolean 'System.Boolean') | normalize as json objects. |

<a name='M-AdaptiveCards-Templating-ObjectPath-GetObjectProperty-System-Object,System-String-'></a>
### GetObjectProperty(obj,property) `method`

##### Summary

Get a property or array element from an object.

##### Returns

the value or null if not found.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | object. |
| property | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | property or array segment to get relative to the object. |

<a name='M-AdaptiveCards-Templating-ObjectPath-GetPathValue``1-System-Object,System-String-'></a>
### GetPathValue\`\`1(obj,path) `method`

##### Summary

Get the value for a path relative to an object.

##### Returns

value or default(T).

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | object to start with. |
| path | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | path to evaluate. |

##### Generic Types

| Name | Description |
| ---- | ----------- |
| T | type to return. |

<a name='M-AdaptiveCards-Templating-ObjectPath-GetPathValue``1-System-Object,System-String,``0-'></a>
### GetPathValue\`\`1(obj,path,defaultValue) `method`

##### Summary

Get the value for a path relative to an object.

##### Returns

value or default(T).

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | object to start with. |
| path | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | path to evaluate. |
| defaultValue | [\`\`0](#T-``0 '``0') | default value to use if any part of the path is missing. |

##### Generic Types

| Name | Description |
| ---- | ----------- |
| T | type to return. |

<a name='M-AdaptiveCards-Templating-ObjectPath-GetProperties-System-Object-'></a>
### GetProperties(obj) `method`

##### Summary

Get all properties in an object.

##### Returns

enumeration of property names on the object if it is not a value type.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | Object to enumerate property names. |

<a name='M-AdaptiveCards-Templating-ObjectPath-HasValue-System-Object,System-String-'></a>
### HasValue(obj,path) `method`

##### Summary

Does an object have a subpath.

##### Returns

true if the path is there.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | object. |
| path | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | path to evaluate. |

<a name='M-AdaptiveCards-Templating-ObjectPath-MapValueTo``1-System-Object-'></a>
### MapValueTo\`\`1(val) `method`

##### Summary

Convert a generic object to a typed object.

##### Returns

converted value.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| val | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | value to convert. |

##### Generic Types

| Name | Description |
| ---- | ----------- |
| T | type to convert to. |

<a name='M-AdaptiveCards-Templating-ObjectPath-Merge``1-``0,``0-'></a>
### Merge\`\`1(startObject,overlayObject) `method`

##### Summary

Equivalent to javascripts ObjectPath.Assign, creates a new object from startObject overlaying any non-null values from the overlay object.

##### Returns

merged object.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| startObject | [\`\`0](#T-``0 '``0') | Intial object. |
| overlayObject | [\`\`0](#T-``0 '``0') | Overlay object. |

##### Generic Types

| Name | Description |
| ---- | ----------- |
| T | The object type. |

<a name='M-AdaptiveCards-Templating-ObjectPath-RemovePathValue-System-Object,System-String-'></a>
### RemovePathValue(obj,path) `method`

##### Summary

Remove path from object.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | Object to change. |
| path | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | Path to remove. |

<a name='M-AdaptiveCards-Templating-ObjectPath-SetObjectSegment-System-Object,System-Object,System-Object,System-Boolean-'></a>
### SetObjectSegment(obj,segment,value,json) `method`

##### Summary

Given an object, set a property or array element on it with a value.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | object to modify. |
| segment | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | property or array segment to put the value in. |
| value | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | value to store. |
| json | [System.Boolean](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Boolean 'System.Boolean') | if true, value will be normalized to JSON primitive objects. |

<a name='M-AdaptiveCards-Templating-ObjectPath-SetPathValue-System-Object,System-String,System-Object,System-Boolean-'></a>
### SetPathValue(obj,path,value,json) `method`

##### Summary

Given an object evaluate a path to set the value.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | object to start with. |
| path | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | path to evaluate. |
| value | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | value to store. |
| json | [System.Boolean](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Boolean 'System.Boolean') | if true, sets the value as primitive JSON objects. |

<a name='M-AdaptiveCards-Templating-ObjectPath-TryGetPathValue``1-System-Object,System-String,``0@-'></a>
### TryGetPathValue\`\`1(obj,path,value) `method`

##### Summary

Get the value for a path relative to an object.

##### Returns

true if successful.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | object to start with. |
| path | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | path to evaluate. |
| value | [\`\`0@](#T-``0@ '``0@') | value for the path. |

##### Generic Types

| Name | Description |
| ---- | ----------- |
| T | type to return. |

<a name='M-AdaptiveCards-Templating-ObjectPath-TryResolvePath-System-Object,System-String,System-Collections-Generic-List{System-Object}@,System-Boolean-'></a>
### TryResolvePath(obj,propertyPath,segments,eval) `method`

##### Summary

Given an root object and property path, resolve to a constant if eval = true or a constant path otherwise.  
conversation[user.name][user.age] => ['conversation', 'joe', 32].

##### Returns

True if it was able to resolve all nested references.

##### Parameters

| Name | Type | Description |
| ---- | ---- | ----------- |
| obj | [System.Object](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Object 'System.Object') | root object. |
| propertyPath | [System.String](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.String 'System.String') | property path to resolve. |
| segments | [System.Collections.Generic.List{System.Object}@](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Collections.Generic.List 'System.Collections.Generic.List{System.Object}@') | Path segments. |
| eval | [System.Boolean](http://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k:System.Boolean 'System.Boolean') | True to evaluate resulting segments. |
