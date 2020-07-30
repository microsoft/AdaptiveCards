# Prepare Project

  - [ ] Create a new release branch for the outbound release of the format `release/<sprint>` eg release/20.07
  - [ ] Ensure all needed changes are in the relevant `release/<sprint>` branch. `git log --cherry-pick --no-merges release/20.07...main` can be helpful. Be sure to cherry-pick changes in the same order they were _merged_ to the main branch (but do not cherry-pick merge commits themselves)
  - [ ] Update custom.props to point to the updated *binary* version for the .NET Renderers; Follow semantic versioning, preferring to revise minor versions for non-breaking changes and upgrading major versions for major breaking changes. Eg "2.0" for our 20.07 release
  - [ ] [Work-in-progress]Update the `CHANGELOG.md` in the main branch with key/relevant changes. (Tip: See (changeloggenerator)[https://github.com/github-changelog-generator/github-changelog-generator])
  - [ ] Use `git cherry-pick` to add the new `CHANGELOG` entry to the `release/<milestone>` branch
  - [ ] Visit the project's releases page (e.g. `open https://github.com/microsoft/AdaptiveCards/releases`)
    - [ ] Create a new release object for the git tag using the format `<milestone>` eg `20.07`
    - [ ] Ensure the title is of the format `AdaptiveCards <sprint>`
    - [ ] Add a brief description for the release, followed by a changelog of issues organized by Artifact head (Eg Website, Designer, Templating, Renderer) and then further broken up by platforms where applicable
    - [ ] Ensure all issues and pull requests (where issues are not available) tagged "AdaptiveCardsv<sprint>" are included in the changelog in long-form syntax with the full HTTP URL (and not github short-form via #<issueNum> or #<PRNum>)
    - [ ] Call out any Breaking Changes or notable bug fixes based on the "Breaking Changes" etc label filters on the bugs
    - [ ] Include a Testing Results section here with a pointer to our Bug Bash matrix page
        
# Create, & publish new Packages
  - [ ] Kick off the respective release pipelines for .NET/UWP/iOS/Android renderer packages; Before publishing these please ensure that we smoke test our basic scenarios samples
  - [ ] Publish new packages for the JS renderer and website (if needed); Deploy website changes to a test endpoint ahead of the final publish to adaptivecards.io
 
# Publish the release
