A Column is a container which contains a list of CardElements that are logically grouped.

| Property | Type | Required |  Description |
|---|---|---|---|
| **type**| string | true |  **"Column"** |
| **size** | string | false | "auto", "stretch", or a number representing relative width of the column in the column Set (Default:Auto)|
| **items** |  [CardElement](#CardElement)[] | true | The items that are to be displayed in this container. |
| **selectAction** | [Action](#action) | false | Action to perform for a tap on this container, (this allows entire container to act as an action) |