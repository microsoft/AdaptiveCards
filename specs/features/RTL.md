# Right-to-left layout support

## 1 - Determining layout direction

1.1 - `AdaptiveCard`, `Container`, and `Column` types must support an optional, boolean `rtl` property which may be unset (default), `true`, or `false`.

1.2 - Every element has a layout direction of left-to-right or right-to-left, determined as described below.

1.3 - If the `rtl` property is unset on a root `AdaptiveCard`, it must adopt the layout direction provided to it by the underlying platform, typically inherited from a parent view's layout direction.

1.4 - If the `rtl` property is unset or unsupported on an element, it must inherit its layout direction from its parent.

1.5 - If the `rtl` property is unset on an inline `AdaptiveCard`, it must inherit its layout direction from its `Action.ShowCard`.

1.6 - If the `rtl` property is explicitly set on an element that supports it, then the element must ignore any parent layout direction and adopt a left-to-right (if set to `false`) or right-to-left (if set to `true`) layout direction for itself and its descendents.

## 2 - Applying layout direction

2.1 - An element's layout direction must be applied to its primary view and should be applied to any of its associated views, such as popup dialogs, pickers, tooltips, etc.

2.2 - Any element with a `horizontalAligment` property must adapt the described alignment to the start (if set to `left`) or end (if set to `right`) of the element's layout direction.

2.3 - `ColumnSet` must adapt column order to follow its layout direction.

2.4 - `ImageSet` must adapt image order to follow its layout direction.

2.5 - `Image` must NOT adapt or mirror its bitmap in any way.

2.6 - `Textblock` should allow the underlying platform to determine character/word ordering, typically following the Unicode bidi algorithm based on text content. The [base direction supplied to the Unicode algorithm](https://www.w3.org/International/articles/inline-bidi-markup/uba-basics#context) should match the textblock's inherited layout direction. The alignment of text should NOT change based on text content, but should follow layout direction (see `horizontalAlignment` rule above).

2.7 - `ActionSet` must adapt button order to follow its layout direction.

2.8 - An `AdaptiveCard` with `actions` must adapt button order to follow its layout direction.

2.9 - An `Input.Text` with an `inlineAction` must adapt its input to the start and its inline action to the end of its layout direction.

2.10 - A `Fact` must adapt its title to the start and its value to the end of its layout direction.

2.11 - An `Input.*` with a `label` must adapt its label to the start and its suffix to the end of its layout direction.

2.12 - An `Action.*` with an `iconUrl` (and `IconPlacement` is configured to `LeftOfTitle`) must adapt its icon to the start and its title to the end of its layout direction.

2.13 - If `ActionAlignment` is configured to `Left` or `Right`, the buttons must be aligned to start or end of layout direction, respectively.

2.14 - `Media` should NOT adapt any play/seek controls and bars, if present. Any progress bars should progress from left to right, rewind controls should point left, and forward controls should point right.

2.15 - Unless otherwise specified above, the renderer should defer to the underlying platform's implementation of layout direction for all other views.
