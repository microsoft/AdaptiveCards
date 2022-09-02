# Type Ahead Seach in Input.ChoiceSet

## Summary

When there are thousands of choices in a menu (like assigning a task to someone, when there's thousands of people in your org), you need to have a searchable select menu that dynamically loads data as the user searches (since including 1,000 or more choices statically in the card/data isn't a good option).

This document covers feature changes to add Type ahead search support to Input.ChoiceSet in adaptive cards. Discussions and considerations that lead to this spec.

## Requirements

P0: The input can dynamically fetch the list of choices from a remote backend as the user types

P0: Hosts can specify 1 or more pre-determined datasets that get the first-chance to fulfill the request. (E.g., Microsoft Teams could query the Active Directory list of users by hooking into the graph.microsoft.com/users dataset). If the host hasn't registered a matching dataset, the request will be sent to the backend.

P0: A static list of choices can be provided, and any dynamic ones will get appended to the end

P1: The input will support "isMultiSelect": true and "style": "filtered"

P1: Search dynamically renders a list (which has custom UI for each element) with the search result

## Schema Changes

Input.ChoiceSet
| Property | Type | Required | Description
| :---------- | :------- | :---------- | :------- |
| choices.data | Data.Query | No | Enables dynamic typeahead as the user types, by fetching a remote set of choices from a backend.

Data.Query Definition
| Property | Type | Required | Description
| :---------- | :------- | :---------- | :------- |
| type | Data.Query | Yes | Specifies that this is a Data.Query object.
| dataset| String | Yes | The type of data that should be fetched dynamically
| value | String | No | Populated for the invoke request to the bot with the input the user provided to the ChoiceSet
| count | number | No | Populated for the invoke request to the bot to specify how many elements should be returned (can be ignored by the bot, if they want to send a diff amount)  
| skip | number | No | Populated for the invoke request to the bot to indicate that we want to paginate and skip ahead in the list

## Type Ahead Rendering and Changes

1. Add choice.data schema to Input.ChoiceSet
2. ChoiceSetInputRenderer - Support type ahead search control rendering. Support multi select mode as well.
3. Communicate change in SearchText in TypeAheadSearch control to host and get updated choices for the same.
   a. Register TypeAheadSearchWatcher on CardRendererRegistration on the lines of InputWatcher.
   b. ChoiceSetInputRenderer uses ITypeAheadSearchHandler which can be defined by the host and can be set on the ChoiceSetInputRender.
   c. ICardActionHandler is used for processing onActionClicks, similary SDK can expose another interface for communication between SDK and host for TypeAheadControl which the host to implement.
4. Loading experience while the dynamic choices are being fetched from the host through a bot/backend.
5. Debouncing logic - Implement a default debouncing logic in the SDK. Allowing host to override this debouncing logic.

### Current Input.ChoiceSet rendering

![img](assets/InputLabels/Input.ChoiceSet_rendering_1.png)

Diagram - https://www.plantuml.com/plantuml/uml/POynRiCm34LtdeAZV8LcI52dtRhKQnT5Pc2YicY859BSldG3D4cZwOEVxqdQgSLgRSxm6m3uY87resNZWJ8bstPe4nKC5z8E45ygbP4gzXEbxrSvasw0iXA68ckl9xOqOUWduKG3sM2NJDkryfFYkeblvoMwPSJh-6RzAfznPC53CvEYcmUgbtc9oR33VzI-ohANKt4y-D91_5tT8_lEsQW-ttWhxYL_mpkRSqvSlmUU-0Xgii3ESvlp3m00

### Proposed Input.ChoiceSet rendering

![img](assets/InputLabels/Input.ChoiceSet_rendering_2.png)

Diagram - https://www.plantuml.com/plantuml/uml/PP2nSlCW3CTtda8ZVeNFG_BLRhSkTSSi2bOEhXZvGBx4Rry8lJZdQE04V_r_4ZecmIZBvDKzKSfTG5jCdMLdQ23fKV3GW5WAe5TAZGA0Vn0fZ1JXUvtfloKS1y9ex2dNz6l0oPccLUGJWGvyjnIkIv-B5pUG9oDxQC7-KJjBvkUDRsrvVgQKI5Sdne9-J3Z8wkbGvH86Ym7URpDcsWYRidKuXIyS7SDv4U6Gshsvusb68z20Ul7saUUUho53TAuxSvwqUI5yE2yKQ_iTOTEUKBjDwa5Gd7bmix5-NDMBkwXw9k5P7NE-JFuN

### Communication with Host to fetch Dynamic choices

### Debounce Logic

We can have a default debounce time of 250 ms or 500 ms. After the user has made text change, we add a delay of 250ms before making a call to the host to fetch the dynamic choices.

1. Additional debounce to search only after user has types 2-3 characters?

Link - https://medium.com/android-news/implementing-search-on-type-in-android-with-coroutines-ab117c8f13a4

## Fallback impact / Backward compatibility

Static typeahead
For static typeahead, fall back to the default compact style if static typeahead is not supported.

Dynamic typeahead
Since we still support defining static values as choices, we can just provide those options and safely ignore the dynamic information. This will make the choicesets a little less functional, but won’t break the host.

## Important Notes

## Open Questions

1. SDK will leave the search request processing to the host? Is there a need for the host to register any pre-determined databases?
2. Current `Filtered` choice set style support single select for static choices. When `choices.data` is absent in the payload. Do we support multi select from filtered static choices?
3. Does developer assign ChoiceSetStyle as `Filtered` when using TypeAheadSearch? If not, how do we manage fallback to show static choices using existing `Filtered` ChoiceSetStyle control?
