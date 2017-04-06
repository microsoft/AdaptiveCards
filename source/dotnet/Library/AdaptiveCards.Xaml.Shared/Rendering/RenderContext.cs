using Newtonsoft.Json.Linq;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
#if XAMARIN
using Xamarin.Forms;
using Xamarin.Forms.Xaml.Internals;
using FrameworkElement = Xamarin.Forms.View;
#elif WPF
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
using System.Windows.Media.Imaging;
using Xceed.Wpf.Toolkit;
#endif

namespace AdaptiveCards.Rendering
{
    public partial class RenderContext
    {
        public Dictionary<Type,Func<FrameworkElement,object>> GetValueFromElementDictionary { get; set; }
        internal Func<string, MemoryStream> ImageResolver = null;

        public RenderContext(Action<object, ActionEventArgs> actionCallback,
            Action<object, MissingInputEventArgs> missingDataCallback,
            Func<string, MemoryStream> imageResolver = null)
        {
            if (actionCallback != null)
                this.OnAction += (obj, args) => actionCallback(obj, args);

            if (missingDataCallback != null)
                this.OnMissingInput += (obj, args) => missingDataCallback(obj, args);

            this.ImageResolver = imageResolver;
            Init();
        }

        partial void Init();

        public CardStyling Styling { get; set; } = new CardStyling();

        /// <summary>
        /// Input Controls in scope for actions array
        /// </summary>
        public List<FrameworkElement> InputControls = new List<FrameworkElement>();

        /// <summary>
        /// Event fires when action is invoked
        /// </summary>
        public delegate void ActionEventHandler(object sender, ActionEventArgs e);

        public event ActionEventHandler OnAction;

        /// <summary>
        /// Event fires when missing input for submit/http actions
        /// </summary>
        public delegate void MissingInputEventHandler(object sender, MissingInputEventArgs e);

        public event MissingInputEventHandler OnMissingInput;

        public void Action(FrameworkElement ui, ActionEventArgs args)
        {
            this.OnAction?.Invoke(ui, args);
        }

        public void MissingInput(ActionBase sender, MissingInputEventArgs args)
        {
            this.OnMissingInput?.Invoke(sender, args);
        }

        public virtual dynamic MergeInputData(dynamic data)
        {
            foreach (var inputControl in this.InputControls)
            {
                if (inputControl.GetContext() is InputChoiceSet)
                {
                    InputChoiceSet choiceInput = (InputChoiceSet)inputControl.GetContext();
                    var value = GetValueFromInputControl(inputControl);
                    if (value != null)
                    {
                        data[choiceInput.Id] = JToken.FromObject(value);
                    }
                }
                else
                {
                    Input input = inputControl.GetContext() as Input;
                    var value = GetValueFromInputControl(inputControl);
                    bool hasValue = false;
                    if (value != null)
                    {
                        if (value is string && !String.IsNullOrEmpty((string)value))
                            hasValue = true;
                    }

                    if (hasValue)
                    {
                        data[input.Id] = JToken.FromObject(value);
                    }
                    else if (input.IsRequired)
                    {
                        throw new MissingInputException($"You are missing a required value.", input, inputControl);
                    }
                }

            }
            return data;
        }

        /// <summary>
        /// Override this to look at inputControl and return value for it
        /// </summary>
        /// <param name="inputControl"></param>
        /// <returns></returns>
        public virtual object GetValueFromInputControl(FrameworkElement inputControl)
        {
            return inputControl?.GetValue();
        }

        public void ResetInput()
        {
            foreach (var control in this.InputControls)
            {
                ResetInputControl(control);
            }
        }

        /// <summary>
        /// Override to reset a control back to default state
        /// </summary>
        /// <param name="control"></param>
        public virtual void ResetInputControl(FrameworkElement control)
        {
            control.ResetValue();
        }

    }


    public class ActionEventArgs : EventArgs
    {
        public ActionEventArgs()
        {
        }

        /// <summary>
        /// The action that fired
        /// </summary>
        public ActionBase Action { get; set; }

        /// <summary>
        /// Data for Input controls (if appropriate)
        /// </summary>
        public object Data { get; set; }
    }

    public class MissingInputEventArgs : EventArgs
    {
        public MissingInputEventArgs(Input input, FrameworkElement frameworkElement)
        {
            this.FrameworkElement = frameworkElement;
            this.Input = input;
        }

        public FrameworkElement FrameworkElement { get; private set; }

        public Input Input { get; private set; }
    }


    public class MissingInputException : Exception
    {
        public MissingInputException(string message, Input input, FrameworkElement frameworkElement)
            : base(message)
        {
            this.FrameworkElement = frameworkElement;
            this.Input = input;
        }

        public FrameworkElement FrameworkElement { get; set; }

        public Input Input { get; set; }
    }
}
