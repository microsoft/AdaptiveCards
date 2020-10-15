# Input Accessibility

## Error Accessibility

How should a renderer present error messages to screen readers for inputs that have failed validation?

### On Focus

What is announced when focus moves to a validated input?

1. When an Input is in focus, announce the input's label. If the input has failed validation, **append** the error message.
    - "Email address input. Please enter a real email address."
1. When an Input is in focus, announce the input's label. If the input has failed validation, **prepend** the error message.
    - "Please enter a real email address. Email address input."
1. If an input has failed validation, announce the error message. **Else**, announce the input's label.
    - Failed validation: "Please enter a real email address."
    - No errors: "Email address input."
- Confirm (for https://github.com/microsoft/AdaptiveCards/issues/4889): Regardless of announcement, do not expand any popups or modal views on focus. User must activate the input after focus to access any such popups (e.g. dropdown options).

### On Submit

What happens when a user submits an invalid form (i.e. user activates an `Action.Submit`, and the renderers determines that one or more inputs have failed validation)?

1. Announce the quantity of errors, if present. Message configured by host config.
    - "Could not submit. Please fix the 3 errors."
1. Announce the presence of errors, if present. Message configured by host config.
    - "Could not submit. Please fix error(s)."
1. Add an `errorMessage` attribute to `Action.Submit`. Announce this message.
    - "Could not submit. Please fix error(s)."
1. Do not announce anything. This option assumes focus immediately moves away. See below.
    - ""
- Confirm (for https://github.com/microsoft/AdaptiveCards/issues/4880): No additional indication to user on repeated invalid submissions (e.g. no "flicker"). However, the submit error announcement, if any, will be repeated each time.

## Focus Accessibility

### Initial Focus

When a card is loaded, or when an `Action.ShowCard` is opened, what happens to the focus?

1. Move focus to the first Input in the card, if any.
1. Do not explicitly change focus behavior.

### On Submit

If an error is present, after making a summary error announcement (if any, see Error On Submit), what happens to the focus?

1. Focus moves to the first invalid input. This input is announced as prescribed above.
1. Focus stays, and no further announcements are made.
- Confirm (for https://github.com/microsoft/AdaptiveCards/issues/4881): All invalid inputs, regardless of above choice, should show error-styling (error colored border/background)

## Driving issues

* https://github.com/microsoft/AdaptiveCards/issues/4898
* https://github.com/microsoft/AdaptiveCards/issues/4890
* https://github.com/microsoft/AdaptiveCards/issues/4912

