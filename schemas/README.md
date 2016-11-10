# Adaptive Card Schemas

The current schema is pre-draft but please check back shortly.

# Schema Proposals

Schema proposals are tracked through the [Schema](../../../projects/3) project

1. Go to the `Projects` tab
1. Select `Schema`
1. Create an Issue to discuss the proposal
1. If approved, move forward to Schema Feature Contributions

# Schema Feature Contributions

Once a Schema proposal is approved (see above), submit a PR with the following items completed:

1. Add a **schema definition** in `/schemas`
1. Add a **sample payload** in `/samples`
1. Add **tests** that validate the payload in `/tests`
1. Add **renderer support** for each Renderer in `/Renderers`
1. **Verify** your payload in the Visualizer and ensure it behaves as expected
1. TODO: How should we track implementation in the various renderers?
