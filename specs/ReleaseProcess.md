AdaptiveCard Release Pipeline Process

Release

Schema Discussion

Spec Drawn

Branches for each new features of the schema are cut.

A Feature leader manages the branch that is used by platform owners or devs who implement the features for a particular platform.

The feature leader manager ensures that implementation is correctly merged into feature branch, and later merge the feature branch into main.


Completed, feature branches are merged to main. 

Bugs based on priority are continuously fixed and merged into main. 

Once all feature branches are merged and important fixes are in, a release branch is cut from main. This is when schema version of renderer is updated. 

Bug bashing commences
Takes about 2 days. Each dev take on two platforms to debug. It’s not set rule, but each dev tests features they implemented on platforms different from they implemented.

Automated tests are run daily and via CI pipelines. They consisted of functional test that check and test non-ui codes and algorithms. UI tests focused on user interactions.

Before ship, manual visual tests are performed. All the scenario cards are tested against the release branch.

Any bugs found are reported to GitHub issues.
Shipment blocker bugs are either fixed or delays the shipment date. 

When builds pass all tests, release pipelines for each platform are triggered; triggering Unit Testing / UI Unit Testing. When all passed, builds are published to the platforms’ artifact repositories. 

Release note along with Git tag is 
Written in GitHub.

Git Release is released along with release note.
