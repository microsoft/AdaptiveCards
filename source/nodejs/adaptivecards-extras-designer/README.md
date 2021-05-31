# Adaptive Card Extras for JavaScript

This package enables designer support for features exported by the `adaptivecards-extras` package. For more information about Adaptive Card Extras, please refer to the `adaptivecards-extras` package documentation.

Features exported by this package are not fully tested and are subject to change without notice, including removal of some or all features. Little to no effort will be made to ensure backwards compatibility if breaking changes are introduced.

## Using the Extras Designer package
Install the package in your app:
```
npm install adaptivecards-extras-designer
```

In your code, import the package and register it with the designer SDK:
```typescript
import * as ACExtrasDesigner from "adaptivecards-extras-designer";

// This will register all exported features into the lobal Registry.
// Alternatively, you can specify your own registries as parameters.
ACExtrasDesigner.initializeDesignerSupport();
```

If you only need a subset of the features exported by the package, you can register each individual feature on your own. For example, to register designer support for the `Extras.ProgressBar`, just add this code:
```typescript
import * as ACDesigner from "adaptivecards-designer";
import * as ACExtras from "adaptivecards-extras";
import * as ACExtrasDesigner from "adaptivecards-extras-designer";

ACDesigner.CardDesignerSurface.cardElementPeerRegistry.registerPeer(ACExtras.ProgressBar, ACExtrasDesigner.ProgressBarPeer, "Extras");
```