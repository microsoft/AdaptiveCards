# Prepare Project

  - [ ] Create a new release branch for the outbound release of the format `release/<sprint>` eg release/20.07
  - [ ] Ensure all needed changes are in the relevant `release/<sprint>` branch. `git log --cherry-pick --no-merges release/20.07...main` can be helpful. Be sure to cherry-pick changes in the same order they were _merged_ to the main branch (but do not cherry-pick merge commits themselves)
  - [ ] Update custom.props to point to the updated *binary* version for the .NET Renderers; 
  - [ ] Follow semantic versioning, preferring to revise minor versions for non-breaking changes (eg 2.1.0) and upgrading major versions for major breaking changes. Eg "2.0.0" for renderer binaries. NOTE: Each shipping artifact has its own versioning sequence (eg Templating SDK binaries should have their owning versioning scheme and not try to match the sequence of the renderer SDK binaries); Similarly, different platform implementations, esp ones that don't share a common code stack, may be expected to diverge even in their major versioning sequences from the other platform binaries, but our goal should be to keep these variances and releases in check and coordinate releases more broadly if and where possible. NOTE: AdaptiveCards Schema version number is yet another versioning metadata that has no bearing on the versioning of the released binaries/artifacts themselves (so for eg a 1.3 AdaptiveCards (schema) version may be implemented in Renderer versions 2.0.0 binaries/SDK)
  - [ ] [WIP]Update the `CHANGELOG.md` in the main branch with key/relevant changes. (Tip: See [changeloggenerator](https://github.com/github-changelog-generator/github-changelog-generator))
  - [ ] [WIP] Use `git cherry-pick` to add the new `CHANGELOG` entry to the `release/<milestone>` branch
  - [ ] Visit the project's releases page (e.g. `open https://github.com/microsoft/AdaptiveCards/releases`)
    - [ ] Create a new release object for the git tag using the format `<milestone>` eg `2020.07`
    - [ ] Ensure the title is of the format `AdaptiveCards <milestone>` eg `AdaptiveCards 2020.07`; Note: please adhere to these naming rules strictly to allow for post-processing of the generated release note (once published) by our bots for issue annotations with the release announce.
    - [ ] Ensure the release is based off of the release/`milestone` branch 
    - [ ] Add a brief description for the release, followed by a changelog of issues organized by Artifact head (Eg Website, Designer, Templating, Renderer) and then further broken up by platforms where applicable
    - [ ] For each feature breakdown, do include the links to the respective store download locations for the latest shipping versions (*See [this](https://github.com/microsoft/AdaptiveCards/releases/tag/2020.07) for an example*)
    - [ ] Ensure all issues and pull requests (where issues are not available) tagged "AdaptiveCardsv<sprint>" are included in the changelog in long-form syntax with the full HTTP URL (and not github short-hand notation via #<issueNum> or #<PRNum>, except to call out Known Issues below)
    - [ ] Include a `Known Issues` subsection with links to the issues in github short-hand notation (*not* full HTTP URL)- This is a fabricbot "ignore list" quirk we are leveraging to avoid annotating issues that are linked in the release notes but not actually fixed.
    - [ ] Call out any `Breaking Changes` or `Notable Bug Fixes` based on the "Breaking Changes" etc label filters on the bugs
    - [ ] Include a Smoke Testing Results section here with a pointer to our samples locations used for testing
    - [ ] Repeat this process for servicing release/1.2 series. We'll need to create a separate release draft for the servicing release to release/1.2 at this point in time
# Create, & publish new Packages
  - [ ] Kick off the respective release pipelines for .NET/UWP/iOS/Android renderer packages; Before publishing these please ensure that we smoke test our basic scenarios samples
  - [ ] Publish new packages for the JS renderer and website (*if needed*); Deploy website changes to a test endpoint ahead of the final publish to adaptivecards.io
# Publish the release
