# Parsing
## Memory

### Types

### Catergory by Placement of Data in json
##### inline
Data is provided as part of adaptive cards
```json
{
    "type": "AdaptiveCard",
    "$data": {
        "employee": {
            "name": "Matt"
        }
    },
    "body": [
        {
            "type": "TextBlock",
            "text": "Hi {employee.name}! Here's a bit about your org..."
        }
    ]
}
```

##### reference
Data is provided as separate json, and is provided to the parser as a parsing context.

```json
var dataContext = new ACData.EvaluationContext();
dataContext.$root = {
    "employee": {
        "name": "Matt"
    }
};

```json
{
    "type": "AdaptivCard",
    "body": [
        {
            "type": "TextBlock",
            "text": "Hi {employee.name}! Here's a bit about your org..."
        }
    ]
}
```

### Catergory by Accessor Type 
##### property 
Data is accessed via '.' 
```json
{
    "type": "AdaptiveCard",
    "body": [
        {
            "type": "TextBlock",
            "text": "Hi {employee.name}! Here's a bit about your org..."
        }
    ]
}
```

##### array 
Data is accessed via '[]' with index 

```json
{
    "type": "AdaptivCard",
    "body": [
        {
            "type": "TextBlock",
            "text": "3 of your peers are: {employee.peers[0].name}, {employee.peers[1].name}, {employee.peers[2].name}"
        }
    ]
}
```

#### scope

```json
{
    "{<property>}": "Implicitly binds to `$data.<property>`",
    "$data": "The current data object",
    "$root": "The root data object. Useful when iterating to escape to parent object",
    "$index": "The current index when iterating",
    "$host": "Access properties of the host *(not working yet)*"
}
```

### Parsing Strategy For each catergories 