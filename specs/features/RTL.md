# Right-to-left layout support

1. `AdaptiveCard`, `Container`, and `Column` types must contain an optional `rtl` property which may be unset (default), `true`, or `false`.

1. Every element has a layout direction of left-to-right or right-to-left, determined as described below.

1. By default, a root AdaptiveCard must inherit its layout direction from the environment its rendered in. For example, a card rendered on a device with language set to Arabic must render in a right-to-left layout by default.

1. By default, all elements must inherit their layout direction from their parent.

1. If the `rtl` property is explicitly set on an element that supports it, then the element must ignore any parent layout direction and adopt a left-to-right (if set to `false`) or right-to-left (if set to `true`) layout direction for itself and its descendents. If the `rtl` property is unset, layout direction must be inherited from parent.

1. An element's layout direction must be applied to its primary view and should be applied to any of its associated views, such as popup dialogs, pickers, tooltips, etc.

1. Any element with a `horizontalAligment` property must adapt the described alignment to the start (if set to `left`) or end (if set to `right`) of the element's layout direction.

1. `ColumnSet` must adapt column order to follow its layout direction.

1. `ImageSet` must adapt image order to follow its layout direction.

1. `Image` must NOT adapt or mirror its bitmap in any way.

1. `Textblock` should allow the underlying platform to determine character/word ordering, typically following the Unicode bidi algorithm based on text content. The [base direction supplied to the Unicode algorithm](https://www.w3.org/International/articles/inline-bidi-markup/uba-basics#context) should match the textblock's inherited layout direction. The alignment of text should not change based on text content, but should follow layout direction (see `horizontalAlignment` rule above).

1. `ActionSet` must adapt button order to follow its layout direction.

1. An `AdaptiveCard` with `actions` must adapt button order to follow its layout direction.

1. An `Input.Text` with an `inlineAction` must adapt its input to the start and its inline action to the end of its layout direction.

1. A `Fact` must adapt its title to the start and its value to the end of its layout direction.

1. An `Input.*` with a `label` must adapt its label to the start and its suffix to the end of its layout direction.

1. An `Action.*` with an `iconUrl` (and `IconPlacement` is configured to `LeftOfTitle`) must adapt its icon to the start and its title to the end of its layout direction.

1. If `ActionAlignment` is configured to `Left` or `Right`, the buttons must be aligned to start or end of layout direction, respectively.

1. An `Action.*` must inherit the layout direction of the `ActionSet` or `AdaptiveCard` it belongs to.

1. `Media` should NOT adapt any play/seek controls and bars, if present. Any progress bars should progress from left to right, rewind controls should point left, and forward controls should point right.

1. An inline `AdaptiveCard` must, by default, inherit the layout direction of its `Action.ShowCard`.

1. Unless otherwise specified above, the renderer should defer to the underlying platform's implementation of layout direction for all other views.