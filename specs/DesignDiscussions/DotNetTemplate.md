# Overview
## Templating
Templating addresses one of the pain points for the AdaptiveCards users. We have very good user experience going from AdaptiveCards json to 
a rendered AdaptiveCards UI component. Creationg of AdaptiveCards json is also great, but it's not to easy to modify AdaptiveCards json. 
Consider this example of  
# Parsing

## Parsing Strategy

* templating parser builds a parsed tree for templated string
* The parse tree's node is defined as in grammar file
* current grammar is based on standard json grammar with the addtion to scopes that context switches to
* template parser
* when token '{' is encoutnered, the mode context switched to templating parsing, upto that moment, it's closely following json parsing
* key, value pairs, arrays, and etc.
* Simple direct substitutions of text is not sufficient we need a some way to capture the text in the value block.
* At this point, we could deserialize the json into objects, and return the objects to the parent node. However, this way we have difficulties  
* implementing the defferred parsing of templated string. for example, if one wants to parse in muti-pass, leaving the templated string, as templated
string would be a good option. If the string is deserialized into objects, it's not obvious which proceses to use in our current disposal.
* in essence, we are converting templated json into a tree, and as we are binding the data, we are flattening the tree into a json.
* for performance reason, we can have a option to leave the paresed tree only replacing the node with fully bounded terminal node.
* at second pass, we only parses the nodes that have not been bound, and all fully bound or non templated node would have been turned to terminal node
* the operation will be merging the nodes to a terminal node.

* repeating objects

## Translation Strategy

* visit each child node and append its text bottom up
* as data is found add to memory list 
* --> problem is performance and efficiency
* --> before moving down to childre, check for data node?
* --> this is sensible strategy considering how much complidation it would incurrs without it
* --> perhaps I should implement listener, all memory is parsed and known
* check asked data is array type
* check if the data is in parent
* if 'YES', don't bind it yet, defer it to the parent node which host the data
* if 'NO', first bind all non-array types, and bind array-type data to the appended string of the current node for available elems in the array-type data.
* return the appended string 
* corner case, what happens when the data type is not avaialbe, and the data type is array?
* the problem is that we repeat the element that is the owner of the data 
* what is the most straitforward way of user expectation?
* this is not really hard problem if we allow them to pare it again,
* it's less than optimal compared to the case where we know that there will be deffered expansion, then we probably felt that building the parse tree twice seems to be wasteful.
* it's also possible that the unbound data is user mistake.
* returning the json as it is is the right behavioer, i.e
* that's their choice
* we appends the text as we move bottom up, when the templated text is encountered,
we add it list in the result 
## Memory

global look up table for data objects
key is path to data 
value json object
type bool arary type? YES or NO

## Result Type
string = ((expanded string)? (non-expanded string)?)*; 
templated-strings =  list of paths to data + properties
first elem in the list is path to data
each subsequent element is property

## Post Translation
append all string, once result is returned from the root node
## Data Source

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
Data is provided as a separate json, and is provided to a parser as a parsing context.

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
Data objects can be placed anywhere in AdaptiveCards elements such as Container, TextBlock, and etc in json.
Templating string is bound to the nearest data when AdaptiveCard is viewed as a tree

```json
{
    "type": "AdaptiveCard",
    "$data": {
        "key": "1.2"
    },
    "body": [
        {
            "type": "Container",
            "$data": {
                "key": "2"
            },
            "items": [
                {
                    "type": "TextBlock",
                    "$data": {
                        "key": "3"
                    },
                    "text": "key should be 3, actual:{key}",
                    "size": "Medium",
                    "wrap": true
                },
                {
                    "type": "TextBlock",
                    "text": "key should be 2, actual:{key}",
                    "size": "Medium",
                    "wrap": true
                }
            ],
            "style": "good",
            "bleed": true
        }
    ],
    "$schema": "http://adaptivecards.io/schemas/adaptive-card.json",
    "version": "{key}"
}
```

## Parsing value of $data key entry
As the visitor visits the nodes in a Parse tree.
Data object is parsed to JSON object.
The object is kept in a Trie.
The prefix used for matching is Adaptive Element's Type string.
This works for both DFS and BFS since it's tree siblings share a parent
When templated string is encountered, the trie is used to find the entry that matches the most prefix

should we try to find the best match even when there is no matches in the nearest data object?
how de we handle in repeating context
texts in array, but some properties of the text block's data object is arrary, which array of data to follow?
need example


```json
{
    "{<property>}": "Implicitly binds to `$data.<property>`",
    "$data": "The current data object",
    "$root": "The root data object. Useful when iterating to escape to parent object",
    "$index": "The current index when iterating",
    "$host": "Access properties of the host *(not working yet)*"
}
```
#### Binding
## binds to all templated string when condition is satified
list of allowed attributes to be bound


### Parsing Strategy For each catergories 
