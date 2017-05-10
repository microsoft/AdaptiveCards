# Getting Started 
An Adaptive Card is nothing more than a JSON-serialized card object model.

## Basic layout 
To understand the object model which is represented by the json it is useful to understand the basic architecture of a card.  A card is made up of containers of elements, actions.  These are stacked vertically unless there is an ColumnSet element which allows you to define a collection of containers that live side by side.

A simple example card which has a single line of text followed by an image
```javascript
{
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "Image",
            "url": "http://adaptivecards-staging.azurewebsites.net/api/cat"
        },
        {
            "type": "TextBlock",
            "text": "Here is a ninja cat"
        }
    ]
}
```

## Type Property
Every element has a `type` property which identifies what kind of object it is. Looking at the above card you can see we
have 2 elements, one which is an `Image`, one which is a `TextBlock`.

## Basic Elements
The most fundamantal elements are:
* **TextBlock** - let's add a block of text, with properties to control what the text looks like
* **Image** - let's you add an image, with properties to control what the image looks like

## Container Elements
A card is made up of one or more containers.  Each container has a collection of elements which are layed out vertically as blocks of the same width as the continer. 

* **Container** - Defines a a collection of elements 
* **ColumnSet/Column** - Defines a collection of columns, each column is a container
* **FactSet** - Container of Facts
* **ImageSet** - Container of Images so that UI can show appropriate photo gallery experience for a collection of images.

## Input Elements
Input elements allow you to ask for native ui to building simple forms:
* **Input.Text** - get text content from the user
* **Input.Date** - get a Date from the user
* **Input.Time** - get a Time from the user
* **Input.Number** - get a Number from the user
* **Input.ChoiceSet** - Give the user a set of choices and have them pick
* **Input.ToggleChoice** - Give the user a single choice and have them pick

## Actions
Actions allow the card author to add buttons to their card.  They don't define the logic of the actions, but instead use
4 predefined action types to control their behavior.

* **Action.OpenUrl** - Let's you have a button open an external url for viewing
* **Action.ShowCard** - Let's you request for a sub-card to be shown to the user.  
* **Action.Http** - Let's you request that all of the input data is gathered up and sent via an HTTP call 
* **Action.Submit** - Let's you have ask for all of the input elements to be gathered up into an object which is then sent to you by the host application in a way they define.

> **Example Action.Submit**: With Skype an Action.Submit will send a Bot Framework bot activity back to the bot with the **Value** property containing an object with all of the input data on it.

## Learn More
* Visit the [Card Schema reference documentation](/documentation#create-cardschema) to see details of each element.
* Visit the [Schema Explorer](/Explorer) to see interactive examples of each element and it's properties
* Visit the [Samples](/samples) to see interactive cards

 
