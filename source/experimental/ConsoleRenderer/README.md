# Windows Console Renderer for Adaptive Cards

As part of a recent Hackathon, the Adaptive Cards team at Microsoft wrote a proof-of-concept console renderer. This project was intended to explore the possibility of using Adaptive Cards to enable shared experiences from within a CLI environment. Its implementation is not ship-ready and is incomplete.

It's probably easier to list what *does* work rather than what doesn't:
* Border drawn around card
* Basic `TextBlock` rendering (no colors)
* Basic `Column` rendering
* Basic `FactSet` rendering
* Render `Image` as inline URL

Here's some sample output taken from `ActivityUpdate.json`:

```
┌───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
│ Publish Adaptive Card schema                                                                                          │
│ <https://pbs.twimg.com/profile_images/3647943215/d7f128 Matt Hidinger                                                 │
│ 30b3c17a5a9e4afcc370e3a37e_400x400.jpeg>                Created {{DATE(2017-02-14T06:08:39Z, SHORT)}}                 │
│ Now that we have defined the main rules and features of the format, we need to produce a schema and publish it to Gi  │
│ tHub. The schema will be the starting point of our reference documentation.                                           │
│ Board:                                                    Adaptive Card                                               │
│ List:                                                     Backlog                                                     │
│ Assigned to:                                              Matt Hidinger                                               │
│ Due date:                                                 Not set                                                     │
└───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
