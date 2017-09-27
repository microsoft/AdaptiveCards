//using System.Collections.Generic;

//namespace AdaptiveCards
//{
//    public interface ITypedElement
//    {
//        string Type { get; set; }
//    }

//    public interface IActionBase : ITypedElement
//    {
//        /// <summary>
//        ///     Title of the action
//        /// </summary>
//        string Title { get; set; }

//        /// <summary>
//        ///     Speak phrase for this action
//        /// </summary>
//        string Speak { get; set; }
//    }


//    public interface IActionHttp : IActionBase
//    {
//        /// <summary>
//        ///     HttpMethod to use
//        /// </summary>
//        string Method { get; set; }

//        /// <summary>
//        ///     url to use (can have binding information)
//        ///     NOTE: You can bind to properties from input fields by using {{InputID}} in the string where
//        ///     InputID is an id property on an TextInput or ChoiceInput element
//        /// </summary>
//        string Url { get; set; }

//        /// <summary>
//        ///     Object which represents headers Example: { "content-type":"application/json" }
//        /// </summary>
//        object Headers { get; set; }

//        /// <summary>
//        ///     Body for payload to http command
//        ///     NOTE: You can bind to properties from input fields by using {{InputID}} in the string
//        /// </summary>
//        string Body { get; set; }
//    }

//    public interface IActionOpenUrl : IActionBase
//    {
//        /// <summary>
//        ///     Url to open using default operating system browser
//        /// </summary>
//        string Url { get; set; }
//    }

//    public interface IActionShowCard : IActionBase
//    {
//        /// <summary>
//        ///     Container card to show when the action is invoked
//        /// </summary>
//        IContainer Card { get; set; }
//    }

//    public interface IActionSubmit : IActionBase
//    {
//        /// <summary>
//        ///     initial data that input fields will be combined with. This is essentially 'hidden' properties, Example:
//        ///     {"id":"123123123"}
//        /// </summary>
//        object Data { get; set; }
//    }

//    public interface IAdaptiveCard : ITypedElement
//    {
//        /// <summary>
//        ///     Elements for this card
//        /// </summary>
//        List<CardElement> Body { get; set; }

//        /// <summary>
//        ///     Actions for this container
//        /// </summary>
//        List<ActionBase> Actions { get; set; }

//        /// <summary>
//        ///     Speak annotation for the card
//        /// </summary>
//        string Speak { get; set; }

//        /// <summary>
//        ///     Background image for card
//        /// </summary>
//        string BackgroundImage { get; set; }

//        /// <summary>
//        ///     version of schema that this card was authored
//        /// </summary>
//        string Version { get; set; }

//        /// <summary>
//        ///     if a client doesn't support the minVersion the card should be rejected.  If it does, then the elements that are not
//        ///     supported are safe to ignore
//        /// </summary>
//        string MinVersion { get; set; }

//        /// <summary>
//        ///     if a client is not able to show the card, show fallbackText to the user. This can be in markdown format.
//        /// </summary>
//        string FallbackText { get; set; }
//    }


//    public interface IContainerSet : ICardElement
//    {
//        /// <summary>
//        ///     Columns that are part of this group
//        /// </summary>
//        List<IContainer> Containers{ get; set; }
//    }

//    public interface IContainer : ICardElement
//    {
//        /// <summary>
//        ///     Elements of the container
//        /// </summary>
//        List<ICardElement> Items { get; set; }

//        /// <summary>
//        ///     Action for this container (this allows a default action at the container level)
//        /// </summary>
//        IActionBase SelectAction { get; set; }

//        /// <summary>
//        ///     Size for the column (either ColumnSize string or number which is relative size of the column)
//        /// </summary>
//        string Size { get; set; }
//    }

//    public interface IFactSet : ICardElement
//    {
//        /// <summary>
//        ///     The facts to be displayed.
//        /// </summary>
//        List<Fact> Facts { get; set; }
//    }

//    public interface IImageSet : ICardElement
//    {
//        /// <summary>
//        ///     Collection of images to display together
//        /// </summary>
//        List<Image> Images { get; set; }

//        /// <summary>
//        ///     Specifies the horizontal size of each image in the set
//        /// </summary>
//        ImageSize ImageSize { get; set; }
//    }

//    public interface ICardElement : ITypedElement
//    {
//        /// <summary>
//        ///     SSML fragment for spoken interaction
//        /// </summary>
//        string Speak { get; set; }

//        /// <summary>
//        ///     How should this element be emphasized relative to previous element
//        /// </summary>
//        SeparationStyle Separation { get; set; }
//    }

//    public interface IImage : ICardElement
//    {
//        /// <summary>
//        ///     Size for the Image
//        /// </summary>
//        ImageSize Size { get; set; }

//        /// <summary>
//        ///     The style in which the image is displayed.
//        /// </summary>
//        ImageStyle Style { get; set; }

//        /// <summary>
//        ///     A url pointing to an image to display
//        /// </summary>
//        string Url { get; set; }

//        /// <summary>
//        ///     Horizontal alignment for element
//        /// </summary>
//        HorizontalAlignment HorizontalAlignment { get; set; }

//        /// <summary>
//        ///     Action for this image (this allows a default action to happen when a click on an image happens)
//        /// </summary>
//        ActionBase SelectAction { get; set; }

//        /// <summary>
//        ///     Alternate text to display for this image
//        /// </summary>
//        string AltText { get; set; }
//    }

//    public interface IInput : ICardElement
//    {
//        /// <summary>
//        ///     Id for the value (will be used to identify collected input when SUBMIT is clicked)
//        /// </summary>
//        string Id { get; set; }

//        /// <summary>
//        ///     The input must have a value for it to be part of a Submit or Http action
//        /// </summary>
//        bool IsRequired { get; set; }
//    }


//    public interface IInputChoiceSet : IInput
//    {
//        /// <summary>
//        ///     The initial value for the field
//        /// </summary>
//        string Value { get; set; }

//        /// <summary>
//        ///     Style for choice
//        /// </summary>
//        ChoiceInputStyle Style { get; set; }

//        /// <summary>
//        ///     allow multiple choices to be selected (default false)
//        /// </summary>
//        bool IsMultiSelect { get; set; }

//        /// <summary>
//        ///     the choice options
//        /// </summary>
//        List<Choice> Choices { get; set; }
//    }

//    public interface IInputDate : IInput
//    {
//        /// <summary>
//        ///     Placeholder text for the input desired
//        /// </summary>
//        string Placeholder { get; set; }

//        /// <summary>
//        ///     The initial value for the field
//        /// </summary>
//        string Value { get; set; }

//        /// <summary>
//        ///     hint of minimum value(may be ignored by some clients)
//        /// </summary>
//        string Min { get; set; }

//        /// <summary>
//        ///     hint of maximum value(may be ignored by some clients)
//        /// </summary>
//        string Max { get; set; }
//    }

//    public interface IInputNumber : IInput
//    {
//        /// <summary>
//        ///     Placeholder text for the input desired
//        /// </summary>
//        string Placeholder { get; set; }

//        /// <summary>
//        ///     The initial value for the field
//        /// </summary>
//        string Value { get; set; }

//        /// <summary>
//        ///     hint of minimum value(may be ignored by some clients)
//        /// </summary>
//        string Min { get; set; }

//        /// <summary>
//        ///     hint of maximum value(may be ignored by some clients)
//        /// </summary>
//        string Max { get; set; }
//    }

//    public interface IInputText : IInput
//    {
//        /// <summary>
//        ///     Placeholder text for the input desired
//        /// </summary>
//        string Placeholder { get; set; }

//        /// <summary>
//        ///     The initial value for the field
//        /// </summary>
//        string Value { get; set; }

//        /// <summary>
//        ///     Hint of style of input, if client doesn't support the style it will become simple text input
//        /// </summary>
//        TextInputStyle Style { get; set; }

//        /// <summary>
//        ///     true to collect multiple lines of text(default is false)
//        /// </summary>
//        bool IsMultiline { get; set; }

//        /// <summary>
//        ///     hint of maximum length characters to collect(may be ignored by some clients)
//        /// </summary>
//        int MaxLength { get; set; }
//    }

//    public interface IInputTime : IInput
//    {
//        /// <summary>
//        ///     Placeholder text for the input desired
//        /// </summary>
//        string Placeholder { get; set; }

//        /// <summary>
//        ///     The initial value for the field
//        /// </summary>
//        string Value { get; set; }

//        /// <summary>
//        ///     hint of minimum value(may be ignored by some clients)
//        /// </summary>
//        string Min { get; set; }

//        /// <summary>
//        ///     hint of maximum value(may be ignored by some clients)
//        /// </summary>
//        string Max { get; set; }
//    }

//    public interface IInputToggle : IInput
//    {
//        /// <summary>
//        ///     Title text for toggle
//        /// </summary>
//        string Title { get; set; }

//        /// <summary>
//        ///     Value to use for on (Default: true)
//        /// </summary>
//        string ValueOn { get; set; }

//        /// <summary>
//        ///     Value to use for off (Default: false)
//        /// </summary>
//        string ValueOff { get; set; }

//        /// <summary>
//        ///     The initial value for the field
//        /// </summary>
//        string Value { get; set; }
//    }

//    public interface ITextBlock : ICardElement
//    {
//        /// <summary>
//        ///     The size of the text
//        /// </summary>
//        TextSize Size { get; set; }

//        /// <summary>
//        ///     The weight of the text
//        /// </summary>
//        TextWeight Weight { get; set; }

//        /// <summary>
//        ///     The color of the text
//        /// </summary>
//        TextColor Color { get; set; }

//        /// <summary>
//        ///     Should it be subtle?
//        /// </summary>
//        bool IsSubtle { get; set; }

//        /// <summary>
//        ///     The text to display
//        /// </summary>
//        string Text { get; set; }

//        /// <summary>
//        ///     Horizontal alignment for element
//        /// </summary>
//        HorizontalAlignment HorizontalAlignment { get; set; }

//        /// <summary>
//        ///     Is it allowed for the text to wrap
//        /// </summary>
//        bool Wrap { get; set; }

//        /// <summary>
//        ///     When Wrap is true, you can specify the maximum number of lines to allow the textBlock to use.
//        /// </summary>
//        int MaxLines { get; set; }
//    }
//}