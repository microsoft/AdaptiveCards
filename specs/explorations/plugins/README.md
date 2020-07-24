# Adaptive Card Plugins

Learning from the web by embracing experimentation and extensibility in a controlled way.

---

Exploration status: **Draft**. 

No current plan to ship, but actively seeking feedback.

---

## Preface

Building a standard is hard, and as adoption grows, things necessarily slow down. Keeping a handle on fragmentation while still allowing groups to innovate and experiment is critical to prevent stagnation and discourage those groups from "forking" and rolling their own version to meet their needs. 

In the web world, they have come a long way to address  fragmentation and bugs across different browser vendors (Internet Explorer vs Edge vs FireFox vs Chrome vs Safari). It wasn't that long ago that websites had a range of incompatibilities between browers, some serious, some mere annoyances. In one of the webs darker hours, they even went as far as to "sniff" the User Agent string for competing browsers just to make certain websites work. Suffice to say it was a frustrating time for users and developers alike.

Eventually the W3C gained momentum and got the browser vendors to agree that reliable standards are in everyone's best interest. **They also knew that standards and innovation are diametrically opposed**, so the working group prescribed a set of rules that would allow browsers to innovate and experiment, and give web developers APIs to modify their sites according to which features worked in a given browser. This is often referred to as ["progressive enhancement" or "graceful degredation"](https://www.sitepoint.com/progressive-enhancement-graceful-degradation-choice/).

Specifically, this included things like [CSS vendor prefixes](https://developer.mozilla.org/en-US/docs/Glossary/Vendor_Prefix). The web community also innovated simple tools known as [polyfills](https://developer.mozilla.org/en-US/docs/Glossary/Polyfill#:~:text=A%20polyfill%20is%20a%20piece,do%20not%20natively%20support%20it.) that make it easier for web developers to take advantage of the latest enhancements with a reasonable fallback to down-level browsers.

Finally, the community maintains the [Browser Compatibility Data repository (BCD)](https://developer.mozilla.org/en-US/docs/MDN/Contribute/Structures/Compatibility_tables) which is the central repository for CSS, JavaScript, and HTML features, their current status, and their current support. 

Excerpt of the CSS property [`border-width`](https://github.com/mdn/browser-compat-data/blob/master/css/properties/border-width.json) showing its current status and browser compatibility. 

```json
{
  "css": {
    "properties": {
      "border-width": {
        "__compat": {
          "mdn_url": "https://developer.mozilla.org/docs/Web/CSS/border-width",
          "support": {
            "chrome": {
              "version_added": "1"
            },
            "chrome_android": {
              "version_added": "18"
            },
            "edge": {
              "version_added": "12"
            },
            "firefox": {
              "version_added": "1"
            }
          },
          "status": {
            "experimental": false,
            "standard_track": true,
            "deprecated": false
          }
        }
      }
    }
  }
}
```

And a slightly more complex schema exists to describe JavaScript "builtin" APIs, such as [Array](https://github.com/mdn/browser-compat-data/blob/master/javascript/builtins/Array.json)

Another metaphor from the web: Edge provides [`-ms-high-contast`](https://developer.mozilla.org/en-US/docs/Web/CSS/@media/-ms-high-contrast), which is not currently part of the standard or on a standards track. The MDN makes it very clear on their websites the state of any extension and which extension works in which browsers:

> **Non-standard**
> 
> This feature is non-standard and is not on a standards track. Do not use it on production sites facing the Web: it will not work for every user. There may also be large incompatibilities between implementations and the behavior may change in the future.

### Learning from the web

From the onset of Adaptive Cards we knew we wanted to provide a core set of elements in the schema, and offer [extensibility APIs](https://docs.microsoft.com/en-us/adaptive-cards/sdk/rendering-cards/javascript/extensibility) for Hosts to register new elements, or custom render existing ones. We even followed the W3C's lead by providing guidance on naming these custom elements and properties. 

Some of the more well-known extensions that followed this guidance were [created by Cortana](https://stciuxdocs.asgfalcon.io/documents/Content/Segments/CortanaUX/Adaptive.html) (*internal Microsoft link*).

**In short, standards are important, but standards move slowly as a rule. And a standard that doesn't meet changing business needs is a standard not long for this world. Let's embrace "controlled" innovation and experiments in a holistic way.**

What follows is a starting point to grok this problem.

## Principles and Objectives

1. Our overarching goal should be to embrace and control fragmentation in the ecosystem without compounding or accelerating it.
2. Create clarity around schema extensions, whether they are on a standards-track or not, and provide plenty of guidance on how to properly utilize plugins.
3. Facilitate non-stanadard experimentation and vendor-specific innovation
4. Formalize and codify a means for the community to develop, spec, and recommend a plugin for standards consideration. E.g., a company can create a Charting plugin that works on the platforms they need. With plugins they have a consistent and normalized way of describing the schema, and a self-contained implementation/reference renderers that can be easily reviewed and ported to other platforms.  
   
## Benefits

1. **Improved discoverability and awareness throughout the Adaptive Cards ecosytsem**. Since plugins are just a feature of Adaptive Cards, our existing website, docs and SDKs can be enhanced to promote plugins.
2. **Centralized documentation and tooling for officially extending the schema.**. adaptivecards.io will be updated to list plugins, show compatibilty charts, and the Designer will automatically reflect which plugins are supported in which hosts.
3. **Follows well-known extensibility patterns**. [ASP.NET has "Middleware"](https://docs.microsoft.com/en-us/aspnet/core/fundamentals/middleware/?view=aspnetcore-3.1). VS Code has ["Extensions"](https://code.visualstudio.com/api/references/extension-manifest)
4. **Gives a name to what we've already been doing.** Instead of saying "use our extensbility APIs and read these docs" we can say "write a plugin and here are the lifecycle events to use". Also gives us a way to describe the existing packages for [adaptivecards-fabric](https://www.npmjs.com/package/adaptivecards-fabric) and [AdaptiveCards.Rendering.Wpf.Xceed](https://www.nuget.org/packages/AdaptiveCards.Rendering.Wpf.Xceed/).
5. **Fasciliates rapid protoyping and experimentation.** A standard and comprehensive lifecycle API makes it possible to extend the renderers in powerful ways without having to fork them.
6. **We can ship "experiments" and satisfy needs on specific platforms, and port them as needed.** For example, some internal teams have been asking for more UI flexibility and only depend on the web stack, so we've kicked around the idea of a JS-renderer fork that could skirt the normal card-author-host constraints and give full UI power to card authors. A plugin model gives us flexibility to do this without forking or implicit fragmenting functionality by not documenting certain things (like explicit padding in Outlook AM).
7. **Clarity around what-works-where**. Is Universal Actions supported everywhere? Or only where the plugin is enabled.
8. **Makes it easy to build and ship samples.** Because plugins are self-contained and follow strict rules that each renderer must support, it becomes a lot easier to build and package sample code.


## How they work?

1. Official vnext renderers introduce consistent support for a new plugin model.
2. Plugins are backed by a **a plugin manifest** which describes its name, supported platforms, etc (details below)
3. This plugin model includes a standard set of lifecycle events that always occur in the same order (*what follows is just an example*):
   1. Parse element
   2. Parse property
   3. Resource resolving / modifying outbound HTTP calls
   4. Render element
   5. Process text (markdown, hyperlinks)
   6. Hooking into actions
   7. Reading/modifying host config
   8. More TBD
4. Plugin authors hook into these events and ultimately modify the pipeline to achieve their goal. 
5. Plugins can read/modify the `Element` and `Action` registries
6. Plugins should declare if they are parse-time or render-time, since that will determine what official SDK dependency they have. (E.g., a .NET plugin could depend on `AdaptiveCards` if parse-only, or `AdaptiveCards.Rendering.Wpf` if it needs rendering APIs.) 
7. Because of the above, some plugins can work server-side and client-side, if they don't have a dependency on the rendering stack. (E.g., `adaptivecards-templating`)
8. Hosts describe what plugins they support
9. Plugin manifests and Host Configs are used to generate new pages on adaptivecards.io that list available plugins and which plugins work in which hosts.
10. Plugins should be in a set of wel-defined states, such as "standard" or "experiment" or "osbolete" (which could indicate a workaround)


## Website and documentation of plugins

1. List of plugins
2. Plugin details page
   1. Compat chart showing which platforms the plugin works on
   2. Shows which Hosts the plugin wokks with
   3. Status: experimental, standard, obsolete, etc
3. List of Hosts
   1. Which version they support
   2. Which plugins they support
4. Lists of SDKs
   1. Current version
   2. Package link
   3. Docs link
   4. Which hosts use which SDK
   5. Which plugins work for the SDK
5. Designer
   1. Selecting a host updates the canvas with supported plugins.
      1. Toolbox shows custom elements
      2. Element Properties show custom properties
   2. Warnings for experimental or non-standard plugins 

![](compat-chart.png)


### Plugin manifests

Imagine this file sitting at the root of a plugin's GitHub repo. The code for the plugins will exist on each supported platform, and be packaged and deployed using the existing platform tools. 

This manifest describes 
- which platforms are supported
- links to those packages
- how the schema is extended
- how Hosts configure it

```json
{
    "id": "adaptivecards-autocomplete",
    "version": "0.1",
    "elementPrefix": "",
    "propertyPrefix": "autocomplete",
    "supports": {
        "javascript": "https://npmjs.com/package/adaptivecards-autocomplete"
    },
    "plugins": { 
        "adaptivecards-templating": "^1.0.0"
    },
    "contributes": {
        "elements": {
            "Input.ChoiceSet": {
                "properties": {
                    "autocomplete": {
                        "type": "object",
                        "properties": {
                            "data": {
                                "type": "uri"
                            }
                        }
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

**Card Usage**

Using a plugin in a card payload is clearly denoted by a special prefix character. We can also provide a means of linking to the plugin documentation in the payload, making it self-contained and self-describing as it potentially moves between Hosts.

```json
{
    "type": "Input.ChoiceSet",
    "label": "Select user",
    "-autocomplete": {
        "plugin": "https://adaptivecards.io/plugins/autocomplete",
        "data": "https://api.example.com/users",
        "fallback": {
            ...
        }
    }
}
```

### Host Config

Hosts will declare what plugins they support in Host Config and how they should be configured.

**Teams Host Config**

```json
{
    "plugins": {
        "adaptivecards-universalactions": {

        },
        "adaptivecards-autocomplete": {

        },
        "adaptivecards-templating": {

        },
        "adaptivecards-links": {
            "version": "^0.1",
            "registries": [
                "https://registry.adaptivecards.io"
            ]
        }
    }
}
```

**Host loading the plugin manually**

The plugin will get passed the Host Config object and configure itself as expected. 

This reduces, but may not always eliminate, the per-platform specific code that a host needs to write per plugin.

```csharp
{
    var renderer = new AdaptiveCardRenderer();
    renderer.HostConfig = ...;
    renderer.Plugins.Add(new AdaptiveLinksPlugin());
    var card = renderer.Render(PAYLOAD);

    // TODO: How does a host manually activate the link unfurling?
    var card = renderer.Render({
        "link": "https://github.com/microsoft/AdaptiveCards"
    })
}
```

### Tests and verification

We can and should enforce that plugins are authored and packaged with test payloads. We can then build out a means of validating them in CI, especially on different platforms.

## Plugin ideas

The website would be updated to list plugins, and which platforms they work on. 

Our Hosts/Partners page would also list which plugins work for a given Host.

Eventually plugins can be rolled into official Adaptive Cards releases? 

| Plugin                           | JavaScript | .NET | Android | iOS | UWP |
| -------------------------------- | ---------- | ---- | ------- | --- | --- |
| `adaptivecards-templating`       | ✅          | ✅    | ✅       | ✅   | ✅   |
| `adaptivecards-universalactions` | ✅          | ✅    | ✅       | ✅   | ✅   |
| `adaptivecards-links`            | ✅          | ✅    | ✅       | ✅   | ✅   |
| `adaptivecards-fluentui`         | ✅          | ❌    | ❌       | ❌   | ❌   |
| `adaptivecards-fluid`            | ✅          | ❌    | ❌       | ❌   | ❌   |
| `adaptivecards-padding`          | ✅          | ❌    | ❌       | ❌   | ❌   |
| `adaptivecards-xceed`            | ❌          | ✅    | ❌       | ❌   | ❌   |


Other possibilities:

* `adaptivecards-from-jsonschema`: Card-From-JSON-Schema support
* `adaptivecards-auth-msa`: Resource resolvers with authentication. E.g., automatically append auth headers for `Image` endpoints on Graph, SharePoint, etc
* `adaptivecards-autocomplete`: Could extend choice set to fetch remote data 
* `adaptivecards-graphing`: Graph plugins can be natively supported on speicifc client but service-lvel fallback could work on other platforms
* Should the standard set of elements, actions, inputs, also be repackaged into a set of plugins, like a "metapackage"
* `adaptivecards-youtube` - built in fallback to an image with a selectAction
* `adaptivecards-semanticelements` - explore a POC from a while back where elements can be `Data.X` which will lookup the template for that data type from the template service and automatically expand it
* `adaptivecards-colorpicker` - with fallback to `Input.ChoiceSet`
* `adaptivecards-fluenticons` including icon properties for ChoiceSet choices, Actions, etc
   

## Requirements

> Project board tracking this work is here:  https://github.com/microsoft/AdaptiveCards/projects/25

1. Designer support. If a Host supports a plugin the Designer should reflect that (where possible)
2. Adaptive Cards website will auto-generate a page that lists the plugins and which platforms are supported for each
3. Card-authors can explicitly require plugins using the `requires` and `fallback` mechanism
4. Some plugins need the ability to completely override the pipeline in some cases. E.g., `adaptivecards-links`
5. The "pipeline" order must be documented and enforced to run consistently on every platform
  
## Further thoughts

1. On-demand acquisition of plugins. Lots to figure out here, potentially boostrapping on Fluid Loaders, etc. Card Authors can declare which plugins they need and they get dynamically loaded
2. Versioning could get really complicated.
