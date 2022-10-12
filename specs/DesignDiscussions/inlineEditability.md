# Inline Editability for Adaptive Cards

# Overview

Adaptive cards are used by apps to share information as well as to collect input from users to complete user scenarios.
As of now, if we are showing some information in a card and we also want to collect user’s input, we will have bunch of Input fields hidden behind a ShowCard button or we will launch some form using button click on the card to collect user's input.
In both cases we might have duplicate readable fields and input fields.

We want to provide better experience to the user where he can read the fields and can also seamlessly update the values at the same place. 

UI of showing data and taking user input will become simplistic. 

 
## Current experience:

As shown in the below picture, An adaptive card displays data for Customer name, Est. Revenue and Est. Clode Date. If an user wants to update those information, he will have to click on 'Edit' button which will open some form and there he can update values for 'Est. Revenue' etc. and Click on Save to send data back to the bot service.

![img](../assets/InlineEditability/InlineEditabilitySecnario1.png)



## Proposed experience:
Adaptive cards use `Input` fields to collect user data. This is how current user experience of `Input` fields looks like:

 ![img](../assets/InlineEditability/InlineEditabilitySecnario7.png)


We will allow bot developer to enhance the user experience of all `Input` fields in Adaptive card (such as `Input.Text`, `Input.Number`, `Input.Date`, `Input.Time`, `Input.Toggle` and `Input.Choiceset`) in way that, these input fields can appear just as readable fields when user is not taking any action and when user clicks or focusses on them, it allows user to update those fields and then user can use use action buttons like Action.Submit/Action.Execute to send data back to the bot.

This is the flow for user to interact with inline editable fields:-
1. This is an adaptive showing information like "Contact", "Email", "Est. Closing date" etc. with inline Editable style where input fields are displayed as readable fields in the default state.

![img](../assets/InlineEditability/IE1.PNG)

2. When user hovers on the card, 
	* we will show outer outline on that card. (**PM/UX Ques 1**: Should we always show card outer outline whether or not it has any inline editable fields?)
	* we will show a lighter color outline to all the input fields which are inline editable.
	
	This will guide user to the input fields which he can go an update right on the card.
	
![img](../assets/InlineEditability/IE2.PNG)

3. When user takes hovers over the input field, we will show a darker outline in that input field to guide user that the field is activated and he can go and edit the field.

![img](../assets/InlineEditability/IE15.PNG)

4. when user goes and clicks on any inline editable field, we will show darker outline to input fields indicating that the field is getting edited by the user.

![img](../assets/InlineEditability/IE3.PNG)

5. when user has updated the value, Action.Submit or Action.Execute button such as "Save" which has  `disabledUnlessAssociatedInputsChange` property (https://github.com/microsoft/AdaptiveCards/issues/7103) will get enabled automatically. It will guide user to hit the button to commit the changes made on the card.

![img](../assets/InlineEditability/IE4.PNG)


6. When user clicks hits on the Action.Submit or Action.Execute button, latest input values will be sent to the bot from host and bot can then update the card with latest information which we will show in default state.

![img](../assets/InlineEditability/IE5.PNG)

(**PM/UX Ques 2**: Here we are showing green success banner on top of card, but right now, teams shows banner on card footer and host can only show info banner (grey footer) and erorr banner (red footer), because the host does not know whether the button click is success or not.

![img](../assets/InlineEditability/IE16.png)

So, should we update mocks accordingly which grey banner on bottom?)
## New Capabilites in the card:
In order to achive inline editable experience as mentioned above, we will add these capabilities in the card for developers:

* Introduce a new styling property in AC input fields schema which will allow developers to define if label and value would be vertically or horizontally aligned. Default would be existing vertical. 
	Note: When card width is small due to browser resize etc, horizontal view can shift to vertical view of input fields.

	(**PM/UX Ques 3**: This feature will be independent of whether input fields are inline editable or not, right? We will allow horizontal view for default input fields as well. Can we get mocks for horizontal view of default input fields?)

vertical view:

![img](../assets/InlineEditability/IE6.PNG)

horizontal view:

![img](../assets/InlineEditability/IE7.PNG)


* Introduce a new styling property in AC input fields schema for developer to choose between existing input fields vs inline editable input fields.

* Provide a host configurable styling property to define width percentage of label and value properties for input elements. 
In horizontal view, by default, label:value width is to be 3:7 of the container of input element. however, host can configure it for themselves.

![img](../assets/InlineEditability/IE9.PNG)

In vertical view, the width is always 100% of the container of input element.

![img](../assets/InlineEditability/IE8.PNG)

*  If label is missing in the input field then value takes 100% width.

* Order of `label` and `value` will always be label first and value second. In RTL, it should follow right to left convention as expected.

![img](../assets/InlineEditability/IE10.PNG)

* Host can configure these style properties of `label` and `value` field: `font`, `font color` and `font weight`. 
	Default (for both label and value): `14px; Seogue Regular`.
	Colour may be changed from the set of accessible colours in Accessible Messages Design System_WIP

![img](../assets/InlineEditability/IE17.PNG)


* If `value` is `empty` in the input field. We will show label and placeholder text in lighter color like this in the default state,

![img](../assets/InlineEditability/IE12.PNG)
which user can go and update the value,

![img](../assets/InlineEditability/IE13.PNG)

* If `label` is `empty`, we will just show `value` field in readable format in the default state which user can go and update the value.

![img](../assets/InlineEditability/IE14.PNG)

* Inline Action in Input.text: We will not support inline Editable styles for input text containing inline action. It will be shown as default input style only. Reason being, such sceanrios are reply with a comment or adding a message where user collaboration is not needed.
	(**PM/UX Ques 4**: We will support Horizontal view of inline action? Means label, value and inline action will be horzontally aligned for default input fields)

![img](../assets/InlineEditability/InlineEditabilitySecnario8.png)

* Save Button: Our recommendation is to have a `Save` button (Action.Submit or Action.Execute) with `disabledUnlessAssociatedInputsChange` on the card with inline editable fields. Save button will send the modified user input values to the bot and bot will respond with a card with updated input values.

* Cancel Button: Our recommendation is to have a `Cancel` button (Action.Submit or Action.Execute) on the card with inline editable fields. If user has made some changes in the input fields but want to revert back to original state, they can click on "Cancel" button. "Cancel" button will send the card with last saved input values.

* Dirty state of the card: When user has some unsaved changes on the card but he moved away from the card but card is still in the viewport. In this case, we will preseve the changes made by the user and we will some indication to user that fields are unsaved or dirty. When card goes out of the viewport, then we wont preserve the unsaved values. (**PM/UX Ques 5** How to show dirty state of the input fields, for eg: outline or some icon on the field)

* Mobile is `out of scope` for inline editable design since there is no focus state on mobile and alignment will be always `vertical` as of today.

