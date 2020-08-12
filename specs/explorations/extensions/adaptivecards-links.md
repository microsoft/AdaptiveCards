
### adaptivecards-links

```json
{
    "id": "adaptivecards-links",
    "version": "0.1",
    "platforms": {
        "adaptivecards-js": {
            "version": "^2.0.0",
            "package": "https://npmjs.com/package/adaptivecards-links"
        },
        "adaptivecards-dotnet": {
            "version": "^1.0.0",
            "package": "https://nuget.org/packages/Adaptivecards.Links"
        }
    },
    "plugins": { // this may be redundant with package dependnecies
        "adaptivecards-templating": "^1.0.0"
    },
    "contributes": {
        "elements": {
            "TextBlock": {
                "properties": {
                    "previewLinks": {
                        "type": "boolean"
                    }
                }
            }
        }

    },
    "hostConfig": {
        "properties": {
            "registries": {
                "type": "array",
                "description": "The list of registries to lookup templates",
                "items": {
                    "type": "uri"
                }
            }
        }
    }
}
```

**Example**

```json
{
    "type": "TextBlock",
    "text": "Issue [#4223](https://github.com/microsoft/AdaptiveCards/issues/4223)",
    "-links": {
        "$plugin": "https://adaptivecards.io/plugins/links",
        "previewLinks": true
    }
}
```
