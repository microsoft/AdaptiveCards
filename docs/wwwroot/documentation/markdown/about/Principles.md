# Core Design Principles 
The design of adaptive cards has been driven by core principles that have kept the 
design on track.

## Semantic instead of pixel-perfect
As much as possible we have striven for semantic values and concepts as opposed to pure pixel-perfect layout. Examples of semantic expression show up in colors, sizes, and in elements like FactSet and ImageSet. These all allow the host application to control decisions about the actual look and feel.

## Card producer owns the content; card host owns the look and feel
The producer owns what they want to say, but the card host owns the look and feel of how that content is expressed in the context of the application.

## Keep it simple but expressive
Adaptive cards should be expressive and general purpose, but we don't want to build a UI framework.  The whole point is to create an intermediate layer which is "expressive enough" in the same way Markdown is "expressive enough". By focusing on keeping it simple, Markdown creates an easy and consistent expression of document content.  In the same way, we believe that adaptive cards can create a simple, expressive option for card content.

## When in doubt, keep it out
It is easier to add later then it is to live with a mistake. If we found ourselves arguing about whether we should add something or not, we opted to leave it out.  It is always easier to add a property then to live with a legacy property we wished we didn't have to support anymore.


