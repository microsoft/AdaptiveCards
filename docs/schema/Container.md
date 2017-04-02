
A  Container is a CardElement which contains a list of CardElements that are logically grouped.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"Container"** |
| **items** |  [CardElement](#CardElement)[] | true | The items that are to be displayed in this container. |
| **actions** | [Action](#action)[] | false | Actions associated with this container |
| **selectAction** | [Action](#action) | false | Action to perform for a tap on this container, (this allows entire container to act as an action) |
