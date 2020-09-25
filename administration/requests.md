# Requests and requirements

## Gathering requests

Whenever anyone has new requests, a new issue should be opened to capture their request and requirements, even if someone else has asked for these features/requirements already.

A new issue should be opened for each distinct individual set of requirements. Do NOT lump a set of requirements together (like a bucket list of 5 things a team wants).

The title of the issue should be in the following format...

**Request [Asked by]: [Feature]**

For example...

**Request [Bing]: Inline text colors**

If someone else also asks for these same requirements, like Outlook, a new issue would be opened to track that ask from Outlook...

**Request [Outlook]: Inline text colors**

You might say, why not lump these together into one? Requirements from each team can be quite different. If we lumped these together into one, it becomes tough to differentiate whether a specific requirement inside the topic of "inline text colors" was actually asked for by both Bing and Outlook, or only one of them asked for it.

In the body of the issue, the requirements from the asking team need to be captured. Include screenshots if possible, as they are extremely helpful. Make the requirements as clear as possible.

If a team asks for "What Bing asked for", then copy/paste the existing requirements into a new issue for the new asking team. Unless you confirmed they want EXACTLY what the existing requirements had listed, make sure to note that "These requirements were copy/pasted from [issue]", so that we know the requirements may not be fully fleshed out. You might ask, why copy/paste the existing content, why not just link to it? Well, that original issue with the requirements might change over time. For example, if Bing's requirements change, that doesn't mean Outlook's requirements also changed. We want to preserve the original ask from the original team, to ensure we're actually meeting their requirements, not someone else's.

Remember, a lack of details is better than assuming you know what they're asking for and providing potentially incorrect details. A lack of details lets us know that we can follow up for more info.


## Request collections

In order to more easily view our requests by feature, rather than feature-and-asking-team, we create a request collection.

The title of the issue should be in the following format...

**Request: [Feature]**

For example...

**Request: Inline text colors**

The body of the issue should be...

```
# Summary
Provide a summary of the requirements from everyone asking. These need to be re-reviewed each time a new ask comes in.

# Asks

* Asking team (#issue-number)
```


## Next steps

After requests and requirements have been gathered, [proposals](proposals.md) need to be authored!