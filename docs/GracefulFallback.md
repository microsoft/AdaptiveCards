# Graceful Fallback / Progressive Enhancement

Adaptive Cards are consumed and rendered by a large variety of consumers. Even within the internal renderers, like Windows, Xbox, and HoloLens, the features supported by each renderer varies.

Developers should be able to send the same Adaptive payload to all devices, and have it render correctly while still taking advantage of new features on newer devices. To support this, Adaptive Cards and its consumers need to ensure that they support graceful fallback.

Graceful fallback simply means that if a feature isn't supported by an adaptive renderer, an acceptable fallback is displayed instead. For example, some renderers might support assigning a text color, while other renderers don't support custom text colors – but they will gracefully fallback by still displaying the text, albiet with the default text color.

# Fallback via `hint-*` properties

The hint system is one way we allow devices to light up new features without breaking existing renderers.

Action for Renderers: No action required. Simply ignore any hints that you don't understand. Later on, if you choose to start supporting these hints, simply start supporting them! For example, in V1 of your device, you might not support text wrapping. But in V2, you add support for text wrapping, and therefore you can start detecting the `hint-wrap` property. When Cards are displayed on your V1 device, they will "gracefully fall back" by at least displaying the text, and in V2 they will work even better by respecting the wrap property!

```
{ 
    "text": "Hello San Francisco", 
    "hint-wrap": true
}
```

# Fallback of enum values
In addition to adding new hints, we sometimes need to add new property values too. Therefore, we need a way for property values to fall back.

For example, what happens when we add a new text hint-style value, like `superHeader`? If a renderer doesn't support the new style value, how should it fall back?

Without fallback of enum values, the text would be displayed using the default text style, which might be drastically different than what the developer wanted.

With fallback of enum values, the developer creating the Card can specify what fallbacks they would like used. With our `superHeader` example, the next closest text style is `header`. This means that the developer can send the same Card to all devices, and it will look great even if the device doesn't support some of the new values.

Therefore, all enum properties take a list of enums. The list allows developers to provide the fallback values. The first item in the list is the preferred value, and the subsequent items are the fallback values.

```
{ 
    "text": "Hello San Francisco", 
    "hint-style": "superHeader | header"
}
```

# Versioning 

Sometimes graceful fallback isn't enough. For example, what if a device doesn't support background placement of images, and therefore you need to completely re-design your Card to incorporate the image?

In these cases, apps can query the `AdaptiveCardVersion` to discover what elements, properties, and values are supported, and then craft their Card based on the results.

Action for Renderers: In order for developers to know which set of functionality that you renderer is capable of, you should declare the `AdaptiveCardVersion` that you support. 
