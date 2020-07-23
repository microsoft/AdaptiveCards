# Manifests

We need a few new JSON documents in order to generate the website documentation that lists available plugins, their platform support, as well as which Hosts support which plugins.

## Plugin manifest

* Supported platforms (e.g., JavaScript and iOS)
* Dependencies (on other plugins, using SemVer to declare version constraints)
  * These dependencies match the ID of other plugins, which itself maps to the relevant platform package
* Events. This one I'm unsure of if there is value is knowing which events a plugin plans to hook into
* Describe what schema changes (if any) are included. E.g., adds a custom property or a custom element
* Describes the fallback
  

## Host Configs

Host config needs to be extended to include

- Supported schema version
- List of plugin they wish to support
  - Host Configuration for a given plugin
  - We need to consider ordering of plugins and whether that should be declared or not. E.g., if two plugins are hooking into parsing which one has to run first, such as templating.

## Platform SDKs

We also need a listing of our SDKs and which platforms are supported. When plugins describe which platforms they support, they will reference the monikers from this file.

```json
{
    "date": "2020-07-17",
    "platforms": {
        "JavaScript": {
            "adaptivecards": {
                "package": "https://npmjs.com/package/adaptivecards",
                "lifecycle": [
                    "parsing",
                    "rendering"
                ]
            },
            "adaptivecards-reactnative": {
                "package": "https://npmjs.com/package/adaptivecards-reactnative",
                "lifecycle": [
                    "parsing", 
                    "rendering"
                ]
            }
        },
        ".NET": {
            "AdaptiveCards": {
                "package": "https://nuget.org/packages/AdaptiveCards",
                "lifecycle": [
                    "parsing"
                ]
            },
            "AdaptiveCards.Rendering.Wpf": {
                "package": "https://nuget.org/packages/AdaptiveCards.Rendering.Wpf",
                "lifecycle": [
                    "rendering"
                ]
            }
        }
    }
}
```