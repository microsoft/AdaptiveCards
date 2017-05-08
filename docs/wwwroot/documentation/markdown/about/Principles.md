# Core Design Principles 
The design of adaptive cards has been driven by some core principles that have been useful for keeping the 
design on track.

## Semantic instead of pixel-perfect
As much as possible we have strived for semantic values and concepts as opposed to pure pixel pefect layout. 
Examples of semantic expression show up in colors, sizes, and in elements like FactSet and ImageSet. These all
allow the prod allow the host application to control decisions about the actual look and feel.

## Card producer owns the content, card host owns the look and feel
The producer owns what they want to say, but the card host owns the look and feel of how that content is expressed
in the context of their application.

## Keep it simple, but expressive
We want adaptive cards to be expressive and general purpose, but we don't want to build a ui framework.  The whole point
is to create an intermediate layer which is expressive enough in the same way markdown is expressive enough.

By focusing on keeping it simple and expressive, markdown created an easy and consistent expression of document content.  In the
same way we believe that adaptive cards can create a simple, expressive way for card content.

## When in doubt, keep it out
It is easier to add later then it is to live with a mistake.  This means that if we find ourselves arguing about whether
we should add something or not, we opted to leave it out.  It is always easier to add a property then to live with a legacy property we wished we didn't want to support anymore.


