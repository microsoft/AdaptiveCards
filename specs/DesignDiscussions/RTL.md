# Right-to-left layout support

## Pending Concerns

Text alignment, word ordering, and base direction of text. Should each one be based on the rtl property, or the Unicode first strong directional character algorithm? If we go with the 

> # Outcome
> ## `rtl` property on `Container`, `AdaptiveCard`
> 
> `AdaptiveCard`, `Container`, and `Column` types support the optional `rtl` property which can be unset (default), `true`, or `false`.
> 
> Every element has a layout direction of left-to-right or right-to-left, determined as described below.
> 
> By default, a root AdaptiveCard must inherit its layout direction from the environment its rendered in. For example, a card rendered on a device with language set to Arabic must render in a right-to-left layout by default.
>
> By default, all elements must inherit their layout direction from their parent.
>
> If the `rtl` property is explicitly set on an element that supports it, then the element must ignore any parent layout direction and adopt a left-to-right (if set to `false`) or right-to-left (if set to `true`) layout direction for itself and its descendents. If the `rtl` property is unset, layout direction must be inherited from parent.
> 
> An element's layout direction must be applied to its primary view and should be applied to any of its associated views, such as popup dialogs, pickers, tooltips, etc.
> 
> Any element with a `horizontalAligment` property must adapt the described alignment to the start (if set to `left`) or end (if set to `right`) of the element's layout direction.
> 
> `ColumnSet` must adapt column order to follow its layout direction.
>
> `ImageSet` must adapt image order to follow its layout direction.
>
> `Image` must NOT adapt or mirror its bitmap in any way.
>
> `Textblock` should allow the underlying platform to determine character/word ordering, typically following the Unicode bidi algorithm based on text contents. The base direction supplied to the algorithm should match the textblock's layout direction. The alignment of text should not change based on text content, but should follow layout direction (see `horizontalAlignment` rule above).
>
> `ActionSet` must adapt button order to follow its layout direction.
>
> An `AdaptiveCard` with `actions` must adapt button order to follow its layout direction.
> 
> An `Input.Text` with an `inlineAction` must adapt its input to the start and its inline action to the end of its layout direction.
> 
> A `Fact` must adapt its title to the start and its value to the end of its layout direction.
>
> An `Input.*` with a `label` must adapt its label to the start and its suffix to the end of its layout direction.
> 
> An `Action.*` with an `iconUrl` (and `IconPlacement` is configured to `LeftOfTitle`) must adapt its icon to the start and its title to the end of its layout direction.
> 
> If `ActionAlignment` is configured to `Left` or `Right`, the buttons must be aligned to start or end of layout direction, respectively.
>
> An `Action.*` must inherit the layout direction of the `ActionSet` or `AdaptiveCard` it belongs to.
>
> `Media` should NOT adapt any play/seek controls and bars, if present. Any progress bars should progress from left to right, rewind controls should point left, and forward controls should point right.
>
> An inline `AdaptiveCard` must, by default, inherit the layout direction of its `Action.ShowCard`.
>
> Unless otherwise specified above, the renderer should defer to the underlying platform's implementation of layout direction for all other views.

## Considered Options


### 