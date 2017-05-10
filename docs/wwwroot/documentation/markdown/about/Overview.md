# Adaptive Cards Overview 

Adaptive Cards are a open card exchange format enabling developers to exchange UI content in a common and consistent way.

## How they work

**Card Authors** describe their content as a simple JSON object. That content can then be rendered natively inside a **Host Application**, automatically adapting to the look and feel of the Host.

For example, Contoso Bot can author an Adaptive Card through the Bot Framework, and when delivered to Skype, it will look and feel like a Skype card. When that same payload is sent to Microsoft Teams, it will look and feel like Microsoft Teams. As more host apps start to support Adaptive Cards, that same payload will automatically light up inside these applications, yet still feel entirely native to the app.

Users win because everything feels familiar. Host apps win because they control the user experience. And Card Authors win because their content gets broader reach without any additional work.

## Goals 
The goals for adaptive cards are:

* **Portable** - To any app, device, and UI framework
* **Open** - Libraries and schema are open source and shared
* **Automatically Styled** - To the Host application UX and brand guidelines
* **Low cost** - Easy to define, easy to consume
* **Expressive** - Targeted at the long tail of content that developers want to produce.
* **Purely declarative** - No code is needed or allowed

## Content developers
If you are a developer of content Adaptive Cards are great because:

* **One card** - You get a single format, minimizing the cost of creating a card and maximizing the number of places it can be used.
* **Richer Expression** - Your content can more closely align with want you want to say because you have a richer palette to paint with.
* **Broad Reach** - Your content will work across a broader set of applications without you having to learn new schemas.
* **Input controls** - Your card can include input controls for gathering information from the user that is viewing the card.
* **Better tooling** - An open card ecosystem means better tooling that is shared by everyone.

## App developers
If you are an app developer who wants to tap into an ecosystem of third-party content you will love Adaptive Cards because:

* **Consistent user experience** - You guarantee a consistent experience for your users, because you own the style of the rendered card.
* **Native performance** - You get native performance as it targets your UI framework directly.
* **Safe** - Content is delivered in safe payloads so you don't have to open up your UI framework to raw markup and scripting.
* **Easy to implement** - You get off the shelf libraries to easily integrate on any platform you support 
* **Free documentation** - You save time because you don't have invent, implement, and document a proprietary schema.
* **Shared tooling** - You save time because you don't have to create custom tooling.

## Core Design Principles 
The design of adaptive cards has been driven by some core principles that have been useful for keeping the design on track.

### Semantic instead of pixel-perfect
We have striven as much as possible for semantic values and concepts as opposed to pure pixel-perfect layout. 
Examples of semantic expression show up in colors, sizes, and in elements like FactSet and ImageSet. These all allow the host application to make better decisions about the actual look and feel.

### Card Authors own the content, Host App owns the look and feel
The card authors own what they want to say, but the application displaying it owns the look and feel of the card in the context of their application.

### Keep it simple, but expressive
We want Adaptive Cards to be expressive and general purpose, but we don't want to build a UI framework.  The goal is to create an intermediate layer which is "expressive enough" in the same way Markdown is expressive enough for documents.

By focusing on keeping it simple and expressive, Markdown created an easy and consistent description of document content.  In the
same way, we believe that Adaptive Cards can create a simple, expressive means of describing card content.

### When in doubt, keep it out
It is easier to add later then it is to live with a mistake. Iif we found ourselves debating whether we should add something or not, we opted to leave it out.  It is always easier to add a property than to live with a legacy we wish we didn't have to support.


