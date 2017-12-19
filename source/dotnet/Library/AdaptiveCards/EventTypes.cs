using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    /// <summary>
    /// Events that can be subscribed to in the code behind
    /// </summary>
    public class EventTypes
    {
        /// <summary>
        /// Sent when card is activated
        ///{  "type":"OnActivate""card": {}}
        /// </summary>
        public const string OnCardActivate = "onCardActivate";

        /// <summary>
        /// Sent when card is deactivated
        /// { "type":"OnDeactivate"}
        /// </summary>
        public const string OnCardDeactivate = "onCardDeactivate";

        /// <summary>
        /// Sent when element gets focus
        ///  {"type":"onFocus""id":"elementId"}
        /// </summary>
        public const string OnFocus = "onFocus";


        /// <summary>
        /// Sent when element loses focus
        ///{   "type":"onBlur",   "id":"elementId" }
        /// </summary>
        public const string OnBlur = "onBlur";


        /// <summary>
        /// Sent when element is clicked
        /// { "type":"onClick"  "id":"elementId"}
        /// </summary>
        public const string OnClick = "onClick";

        /// <summary>
        /// Sent when element is double clicked
        /// { "type":"onDoubleClick"  "id":"elementId"}
        /// </summary>
        public const string OnDoubleClick = "onDoubleClick";

        /// <summary>
        /// Sent when keystroke happens
        /// {"type":"onKey""id":"elementId","key":"keyValue"}
        /// </summary>
        public const string OnKey = "onKey";

        /// <summary>
        /// Sent when text has changed
        /// { "type":"onTextChanged","id":"elementId""text:"newTextValue" }
        /// </summary>
        public const string OnTextChanged = "onTextChanged";

        /// <summary>
        /// Sent when selection for element has changed
        ///  {   "type":"OnSelectionChanged",    "id":"elementId",    "selection": [array of selected indices]    }
        /// </summary>
        public const string OnSelectionChanged = "onSelectionChanged";

        /// <summary>
        /// Sent when mouse cursor enters element
        /// {    "type":"onMouseEnter",    "id":"ElementId"}
        /// </summary>
        public const string OnMouseEnter = "onMouseEnter";

        /// <summary>
        /// Sent when mouse cursor leaves element
        /// {   "type":"onMouseLeave",    "id":"elementId"}
        /// </summary>
        public const string OnMouseLeave = "onMouseLeave";
    }

    public class AdaptiveCommands
    {

        /// <summary>
        /// Inserts new element into visual tree
        ///        {   "type":"insertElement",   "id":"targetElementId",    "position":"before|after",     "element":{ … } }
        /// </summary>
        public const string InsertElement = "insertElement";

        /// <summary>
        /// Replace element with new element
        /// {   "type":"replaceElement",    "id","targetElementId",    "element": {…}}
        /// </summary>
        public const string ReplaceElement = "replaceElement";


        /// <summary>
        /// Remove element from tree
        /// {   "type":"removeElement",    "Id":"targetElementId"}
        /// </summary>
        public const string RemoveElement = "removeElement";


        /// <summary>
        /// Update properties on element
        /// {   "type":"setProperties",   "id":"elementId",    "properties":[       "property":"name", value":"newValue"     ]}
        /// </summary>
        public const string SetProperties = "setProperties";


        /// <summary>
        /// Deactivate the card
        /// {   "type":"deactivateCard"}
        /// </summary>
        public const string Deactivate = "deactivate";

        /// <summary>
        /// Save the card
        /// {   "type":"saveCard"}
        /// </summary>
        public const string Save = "save";
    }
}
