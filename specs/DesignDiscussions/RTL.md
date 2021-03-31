# Right-to-left layout support

## Pending Concerns

Text alignment, word ordering, and base direction of text. Should each one be based on the rtl property, or the Unicode first strong directional character algorithm? If we go with the 

# Outcome
## `rtl` property on `Container`, `AdaptiveCard`

`AdaptiveCard`, `Container`, and `Column` types support the optional `rtl` property which can be unset (default), `true`, or `false`.

Every element has a layout direction of left-to-right or right-to-left, determined as described below.

By default, a root AdaptiveCard must inherit its layout direction from the environment its rendered in. For example, a card rendered on a device with language set to Arabic must render in a right-to-left layout by default.

By default, all elements must inherit their layout direction from their parent.

If the `rtl` property is explicitly set on an element that supports it, then the element must ignore any parent layout direction and adopt a left-to-right (if set to `false`) or right-to-left (if set to `true`) layout direction for itself and its descendents. If the `rtl` property is unset, layout direction must be inherited from parent.

An element's layout direction must be applied to its primary view and should be applied to any of its associated views, such as popup dialogs, pickers, tooltips, etc.

Any element with a `horizontalAligment` property must adapt the described alignment to the start (if set to `left`) or end (if set to `right`) of the element's layout direction.

`ColumnSet` must adapt column order to follow its layout direction.

`ImageSet` must adapt image order to follow its layout direction.

`Image` must NOT adapt or mirror its bitmap in any way.

`Textblock` should allow the underlying platform to determine character/word ordering, typically following the Unicode bidi algorithm based on text contents. The base direction supplied to the algorithm should match the textblock's layout direction. The alignment of text should not change based on text content, but should follow layout direction (see `horizontalAlignment` rule above).

`ActionSet` must adapt button order to follow its layout direction.

An `AdaptiveCard` with `actions` must adapt button order to follow its layout direction.

An `Input.Text` with an `inlineAction` must adapt its input to the start and its inline action to the end of its layout direction.

A `Fact` must adapt its title to the start and its value to the end of its layout direction.

An `Input.*` with a `label` must adapt its label to the start and its suffix to the end of its layout direction.

An `Action.*` with an `iconUrl` (and `IconPlacement` is configured to `LeftOfTitle`) must adapt its icon to the start and its title to the end of its layout direction.

If `ActionAlignment` is configured to `Left` or `Right`, the buttons must be aligned to start or end of layout direction, respectively.

An `Action.*` must inherit the layout direction of the `ActionSet` or `AdaptiveCard` it belongs to.

`Media` should NOT adapt any play/seek controls and bars, if present. Any progress bars should progress from left to right, rewind controls should point left, and forward controls should point right.

An inline `AdaptiveCard` must, by default, inherit the layout direction of its `Action.ShowCard`.

Unless otherwise specified above, the renderer should defer to the underlying platform's implementation of layout direction for all other views.

## Considered Options
must NOT adapt its inline ordering?? What about text ordering in general??? Is JSON input entered right-to-left? My brain is fried.
> !!! Bi-directional text??? Unicode bidi says that encoding should always be in logical order..? What about alignment? Okay, let's break it down. Page directionality (in our case, it is the layout direction derived from a parent) can only be LTR or RTL. Content directionality can be all LTR, all RTL, and bidi. Content directionality does not have to match page directionality. Three elements to decide: text alignment, word order, character order. W3 says Unicode bidi decides character order based on content directionality, but the page directionality determines word order and text alignment?
> Okay looks like android wants to allow Unicode's first-strong to figure out the base-text-direction (which dictates word order?, text alignment), rather than using the view's inherited layout direction. Setting gravity to end flips that alignment. Instead, we can override text alignment to follow the view's inherited layout direction. But, there is no way to set the base-text-direction to inherit from the view's inherited layout direction, we can only choose between several auto content-based algorithms and explicit LTR or RTL (which is technically a viable option, as we can compute LTR/RTL at render-time). I believe if text alignment is separately overriden, then the only thing that changes is word order (?) and some minor stuff in Unicode bidi alg e.g. the directionality of ambiguous weak characters.
https://www.w3.org/International/questions/qa-html-dir.en

### 