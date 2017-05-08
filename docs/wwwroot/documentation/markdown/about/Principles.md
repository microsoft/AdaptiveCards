# Core Principles 
The design of adaptive cards has been driven by some core principles that have been useful for keeping the 
design on track.

## Semantic instead of pixel-perfect structure
As much as possible we have strived for semantic values and concepts as opposed to pure pixel pefect layout. 
Examples of this is colors being semantic, and elements like FactSet and ImageSet allowing the host application
to make decisions about the actually expression.

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
we should add something or the structure about it, we opted to leave it out.  From a backwards compatibility standpoint 
it is always easier to add a property that is ignored then to have a legacy property we wished we didn't want to support anymore.

