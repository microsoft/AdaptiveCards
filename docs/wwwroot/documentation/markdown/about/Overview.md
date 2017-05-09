# Overview 
Adaptive cards are an open common JSON card exchange format which provides an easy way for developers to exchange 
UI content.

## How it works

A developer creates interactive content by creating a simple JSON object and sending it to the target application.
The schema is made up of simple building blocks that can be combined in an endless number of combinations. 

An adaptive card aware application uses an open source library for their platform/ui framework to renders the card
natively into their application. 

## Content developers
If you are a developer of content adaptive cards are great because:
* **One card** - You get one format, minimizing the cost of creating a card and maximizing the number of places it can be used.
* **Richer Expression** - Your content can more closely align with want you want to say because you have a richer pallete to paint in.
* **Broad Reach** - Your content will work across a broader set of applications without you having to learn new schemas.
* **Input controls** - Your card can include input controls for gathering information from the user that is viewing the card.
* **Better tooling** - Because there is a shared card ecosystem better tooling can be created that is shared by everyone.

## App developers
If you are an app developer which displays content you will love adaptive cards because:
* **Consistent user experience** - You get a consistent experience because you own the style of the rendered card
* **Native performance** - You get native performance as it targets your ui framework directly
* **Safe** - Content is delivered in safe payload, you don't have to open up your ui framework to raw html
* **Easy to implement** - You get off the shelf libraries to easily integrate 
* **Free documentation** - You save time because you don't have invent schema, document schema, creating tooling around it, etc.
* **Shared tooling** - You save time because you don't have tooling for your schema

# Goals 
The goals for adaptive cards are:

* **Portable** - to any device and ui framework
* **Open** - Libraries and schema are open source and shared.
* **Automatically Styled** to the Host application UX and brand guidelines
* **Low cost** - Easy to define, easy to consume
* **Expressive** - Targeted at the long tail of content that developers want to produce.
* **Purely declarative** - no code is needed or allowed

## Core Design Principles 
The design of adaptive cards has been driven by some core principles that have been useful for keeping the 
design on track.

### Semantic instead of pixel-perfect
As much as possible we have strived for semantic values and concepts as opposed to pure pixel pefect layout. 
Examples of semantic expression show up in colors, sizes, and in elements like FactSet and ImageSet. These all
allow the prod allow the host application to control decisions about the actual look and feel.

### Card creator owns the content, card displayer owns the look and feel
The creator owns what they want to say, but the application which is displaying it owns the look and feel of
 of the card in the context of their application.

### Keep it simple, but expressive
We want adaptive cards to be expressive and general purpose, but we don't want to build a ui framework.  The whole point
is to create an intermediate layer which is expressive enough in the same way markdown is expressive enough.

By focusing on keeping it simple and expressive, markdown created an easy and consistent expression of document content.  In the
same way we believe that adaptive cards can create a simple, expressive way for card content.

### When in doubt, keep it out
It is easier to add later then it is to live with a mistake.  This means that if we find ourselves arguing about whether
we should add something or not, we opted to leave it out.  It is always easier to add a property then to live with a legacy property we wished we didn't want to support anymore.


