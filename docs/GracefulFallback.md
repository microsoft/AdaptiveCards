# Graceful Fallback / Progressive Enhancement

Adaptive Cards are consumed and rendered by a large variety of consumers. Even within the internal renderers, like Windows, Xbox, and HoloLens, the features supported by each renderer varies.

Developers should be able to send the same Adaptive payload to all devices, and have it render correctly while still taking advantage of new features on newer devices. To support this, Adaptive Cards and its consumers need to ensure that they support graceful fallback.

Graceful fallback simply means that if a feature isn't supported by an adaptive renderer, an acceptable fallback is displayed instead. For example, some renderers might support assigning a text color, while other renderers don't support custom text colors – but they will gracefully fallback by still displaying the text, albiet with the default text color.

