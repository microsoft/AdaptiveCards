# Speech and Advanced Customization
We live in an era of speech interaction via services like Cortana and Alexa.  Adaptive cards are designed from day one
to support speech, enabling cool new hands-full scenarios.

The speak tag enables the adaptive card to be delivered to an environment where a visual display  might not be primary experience (such as to a car dashboard while driving). 

## Speak Property
To support speech we have a *speak* property which contains text to say to the user. The  text can be annotated using 
[SSML markup](https://msdn.microsoft.com/en-us/library/office/hh361578(v=office.14).aspx). SSML gives you the ability
control the speed, tone, inflection of the speech.  It even allows you to stream audio or a render a TTS audio stream
from your own service, giving you a great deal of customization.

There are 2 patterns for speak property usage by a host application:
* **on delivery** - When a card is delivered a client may opt to read the Speak property for the card to describe the card as a whole.
* **on demand** - In order to support a richer accessibility model the schema supports a speak tag per element.  
This allows for clients to read each element to recipients with accessibility requirements.

### Examples

```
    "speak":"hello world!"

    "speak":"<s>This is sentence 1.</s><s>This is sentence two</s>"

    "speak":"<speak><audio src='https://www.soundjay.com/misc/bell-ringing-04.mp3'/><s>Time to wake up!</s></speak>"

```

## Speech content
The content you design for speech is usually different from the content that you design in a visual display. When you design
a card you are designing a visual experience which is presenting the information to a user in a way that delights them.  
With speech you should think about how to verbally describe the content to them in a way that delights them.  
