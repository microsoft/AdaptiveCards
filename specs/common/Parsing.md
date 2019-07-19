# Parsing an object

The following specifies the behavior that should be used when parsing objects. Note that this behavior applies to all objects (like fact values or background image objects), not just elements/actions. Inner objects should be parsed first following these rules before applying these rules to the parent object.

## Required properties

If a required property is not specified or invalid, the object MUST be **dropped**, a **warning** SHOULD be triggered, and **fallback MUST NOT be invoked**.

Reasons for not specified/invalid...

* **Property not specified**: They didn't specify the `text` property.
* **Property value was null**: They specified `"text": null`.
* **Property value was invalid**: See invalid property values.
* **Property type was string and empty string provided**: For example, `"text": ""`.
* **Property type was array and empty array provided**: For example, `"inlines": []`.

**Provided JSON**

```json
{
    "type": "TextBlock",
    "text": "First TextBlock"
},
{
    "type": "TextBlock" // Missing required text property
},
{
    "type": "TextBlock",
    "text": "Third TextBlock"
}
```

**Should render (and serialize) like...**

```json
{
    "type": "TextBlock",
    "text": "First TextBlock"
},
{
    "type": "TextBlock",
    "text": "Third TextBlock"
}
```

Note the behavior for nested objects... Nested objects are parsed FIRST, so an invalid nested object gets dropped

**Provided JSON**

```json
{
    "type": "FactSet",
    "facts": [
        {
            "value": "Intro to Adaptive" // Missing required title property
        },
        {
            "title": "Requested by",
            "value": "Andrew"
        }
    ]
}
```

**Should render (and serialize) like...**

```json
{
    "type": "FactSet",
    "facts": [
        {
            "title": "Requested by",
            "value": "Andrew"
        }
    ]
}
```

And for nested object single values... Same policy, the nested object is parsed FIRST, so an invalid nested object gets dropped

**Provided JSON**

```json
{
    "type": "Container",
    "backgroundImage": {
        "fillMode": "RepeatHorizontally" // Missing required url property
    }
}
```

**Should render (and serialize) like...**

```json
{
    "type": "Container"
}
```

## Invalid property values

If a property value on an object is invalid, the property will be **ignored** (use default value) and a **warning will be triggered**.

Reasons for being invalid...

* **Incorrect type**: Expected a boolean, but received a number.
* **Unknown enum**: Unknown enum value.
* **Incorrect format**: Expected string in the format of "npx" but was "50 pixels".

**Provided JSON**

```json
{
    "type": "Image",
    "url": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg",
    "width": "25 px", // Invalid, should be "25px" (no space)
    "separator": "true", // Invalid, should be boolean, not string
    "spacing": "huge" // Invalid, there is no huge spacing enum value
}
```

**Should render (and serialize) like...**

```json
{
    "type": "Image",
    "url": "https://pbs.twimg.com/profile_images/3647943215/d7f12830b3c17a5a9e4afcc370e3a37e_400x400.jpeg"
}
```

An example of invalid properties on inner non-element objects...

**Provided JSON**

```json
{
    "type": "Container",
    "backgroundImage": {
        "url": "https://picsum.photos/30/30?image=101",
        "fillMode": 3 // Invalid, should be enum, not number
    },
    "minHeight": "20px"
}
```

**Should render (and serialize) like...**

```json
{
    "type": "Container",
    "backgroundImage": {
        "url": "https://picsum.photos/30/30?image=101"
    },
    "minHeight": "20px"
}
```
