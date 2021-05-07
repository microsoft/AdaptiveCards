# Adaptive Card Extras for JavaScript

This package contains a set of additional features that extend the capabilities of the base Adaptive Cards SDK for JavaScript. These additional features can be:
- Demos or samples to help developers get started when extending the Adaptive Card SDK for JavaScript
- Experiments that may or may not be incorporated into the main SDK later
- Previews of upcoming features in order to get feedback on the design before we integrate those features into the main SDK

Features exported by this package are not fully tested and are subject to change without notice, including removal of some or all features. Little to no effort will be made to ensure backward compatibility if breaking changes are introduced.

## Using the Extras package
Install the package in your app:
```
npm install adaptivecards-extras
```

In your code, import the package and register its features with the main SDK:
```typescript
import * as ACExtras from "adaptivecards-extras";

// This will register all exported features into the lobal Registry.
// Alternatively, you can specify your own registries as parameters.
ACExtras.registerAllFeatures();
```

Since `adaptivecards-extras` is an "opt-in" package, all features are registered with version 1.0 in order to always be available.

If you do not need all the features exported by the package, you can register each individual feature on your own. For example, to register `Extras.ProgressBar` in the Global Registry, just add this code:
```typescript
import * as Adaptive from "adaptivecards";
import * as ACExtras from "adaptivecards-extras";

Adaptive.GlobalRegistry.elements.register(ProgressBar.JsonTypeName, ProgressBar, Adaptive.Versions.v1_0);
```

## Designer support
If you embed the Adaptive Card designer in your application and want to enable designer support for the features exported by this package, you will need to install the `adaptivecards-extras-designer` package. For more information, please refer to that package's documentation.

## Extras.ProgressBar element
`Extras.ProgressBar` implements a basic horizontal "progress bar" element, that can also be used as a basic gauge. It supports the following properties:

| Property | Type | Required | Description |
| --- | --- | --- | --- |
| `title` | string | No | The title that appears above the progress bar. |
| `value` | number | Yes | The current "progress" value. Must be between 0 and 100. Defaults to 0. |
