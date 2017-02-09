# Speech and Advanced Customization

## Speech

The way that you add speech to a card is to describe the contents of the card.  By default clients will
usually simply read all of the text properties of a card, but that doesn't always give you the best experience.

To support speech we have  *speak* property which is raw text of what to say, or fragments of 
[SSML markup](https://msdn.microsoft.com/en-us/library/office/hh361578(v=office.14).aspx) for what to say.

Examples:

    "speak":"I want to say this sentence."

    "speak":"<s>This is sentence 1.</s><s>This is sentence two</s>"

    "speak":"<speak>
        <audio src='https://www.soundjay.com/misc/bell-ringing-04.mp3'/>
        <s>Time to wake up!</s>
    </speak>"

