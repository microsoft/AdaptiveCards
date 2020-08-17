[Adaptive Cards Templating Javascript SDK](../README.md) › [GlobalSettings](globalsettings.md)

# Class: GlobalSettings

Holds global settings that can be used to customize the way templates are expanded.

## Hierarchy

* **GlobalSettings**

## Index

### Properties

* [getUndefinedFieldValueSubstitutionString](globalsettings.md#static-optional-getundefinedfieldvaluesubstitutionstring)

## Properties

### `Static` `Optional` getUndefinedFieldValueSubstitutionString

▪ **getUndefinedFieldValueSubstitutionString**? : *function* = undefined

*Defined in [template-engine.ts:107](https://github.com/microsoft/AdaptiveCards/blob/bf1bfa514/source/nodejs/adaptivecards-templating/src/template-engine.ts#L107)*

Callback invoked when expression evaluation needs the value of a field in the source data object
and that field is undefined or null. By default, expression evaluation will substitute an undefined
field with its binding expression (e.g. `${field}`). This callback makes it possible to customize that
behavior.

**Example**
Given this data object:

```json
{
    firstName: "David"
}
```

The expression `${firstName} ${lastName}` will evaluate to "David ${lastName}" because the `lastName`
field is undefined.

Now let's set the callback:
```typescript
GlobalSettings.getUndefinedFieldValueSubstitutionString = (path: string) => { return "<undefined value>"; }
```

With that, the above expression will evaluate to "David &lt;undefined value&gt;"

#### Type declaration:

▸ (`path`: string): *string | undefined*

**Parameters:**

Name | Type |
------ | ------ |
`path` | string |
