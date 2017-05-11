# Get Started 

An Adaptive Card is nothing more than a JSON-serialized card object model.

## Basic card architecture 
To understand the object model represented by the JSON, it is useful to understand the basic architecture of a card.  A card is made up of containers of elements and actions. These containers are stacked vertically unless there is an ColumnSet element which allows you to define a collection of containers that live side by side.

A simple example card which has a single line of text followed by an image:

```javascript
{
    "type": "AdaptiveCard",
    "version": "1.0",
    "body": [
        {
            "type": "Image",
            "url": "http://adaptivecards.io/api/cat"
        },
        {
            "type": "TextBlock",
            "text": "Here is a ninja cat"
        }
    ]
}
```

## Type property
Every element has a `type` property which identifies what kind of object it is. Looking at the above card you can see we
have two elements, one which is an `Image`, one which is a `TextBlock`.

## Basic elements
The most fundamental basic elements are:
* **TextBlock** - adds a block of text with properties to control what the text looks like
* **Image** - adds an image with properties to control what the image looks like

## Container elements
A card is made up of one or more containers.  Each container has a collection of elements which are laid out vertically as blocks of the same width as the container. 

* **Container** - Defines a a collection of elements 
* **ColumnSet/Column** - Defines a collection of columns, each column is a container
* **FactSet** - Container of Facts
* **ImageSet** - Container of Images so that UI can show appropriate photo gallery experience for a collection of images.

## Input elements
Input elements allow you to ask for native UI to build simple forms:
* **Input.Text** - get text content from the user
* **Input.Date** - get a Date from the user
* **Input.Time** - get a Time from the user
* **Input.Number** - get a Number from the user
* **Input.ChoiceSet** - Give the user a set of choices and have them pick
* **Input.ToggleChoice** - Give the user a single choice between two items and have them pick

## Actions
Actions add buttons to the card.  They don't define the logic of the actions, but use the predefined action types instead.

* **Action.OpenUrl** - the button opens an external URL for viewing
* **Action.ShowCard** - Requests a sub-card to be shown to the user.  
* **Action.Http** - Requests that all of the input data is gathered up and sent via an HTTP call 
* **Action.Submit** - Ask for all of the input elements to be gathered up into an object which is then sent to you through some method defined by the host application.

> **Example Action.Submit**: With Skype, an Action.Submit will send a Bot Framework bot activity back to the bot with the **Value** property containing an object with all of the input data on it.

## Learn more
* The [Card Schema reference documentation](CardSchema.md) contains details of each element.
* Examine the interactive card [samples](/samples) to see interactive cards.
* The [Schema Explorer](../../../explorer/index.html) contains interactive examples of each element and its properties.