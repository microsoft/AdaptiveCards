# Handling speech
To support speech adaptive cards has the *speak* property which contains information on how to create speech to play for the user.


The speech tag can be annotated using  [SSML markup](https://msdn.microsoft.com/en-us/library/office/hh361578(v=office.14).aspx). 
SSML gives you the ability control the speed, tone, inflection of the speech.  It even allows you to stream audio or a render a TTS audio stream
from your own service, giving you a great deal of customization.

There are 2 patterns for speak property usage by a host application:
* **on delivery** - When a card is delivered a client may opt to read the Speak property for the card to describe the card as a whole.
* **on demand** - In order to support a richer accessibility model the schema supports a speak tag per element.  
This allows for clients to read each element to recipients with accessibility requirements.

