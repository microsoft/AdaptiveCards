# Inputs

## Validation

State map works as follows...

![State map](assets/Inputs/ValidationStates.png)

* Initial state includes drawing the required cue if cue is enabled.
* Value changed should happen on each keystroke so that the error can instantly disappear once user corrects the issue
* Conversely, if input was previously valid/initial, validation only happens upon focus leaving or button being pressed