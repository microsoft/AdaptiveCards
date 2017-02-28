# Table of Contents

[ToastContent](#toastcontent)
* [ToastVisual](#toastvisual)
  * [ToastBindings](#toastbindings)
    * [ToastBindingGeneric](#toastbindinggeneric)
      * [ToastGenericTextBlock](#toastgenerictextblock)
      * [ToastGenericAppLogo](#toastgenericapplogo)
      * [ToastGenericAttributionText](#toastgenericattributiontext)
      * [CardElement](Schema.md#cardelement)[]
* [ToastAction](#toastaction)
* [ToastAudio](#toastaudio)
* [ToastHeader](#toastheader)

# Windows Toast notifications

## ToastContent
ToastContent is the top level object that describes a notification's content, including visuals, actions, and audio.

| Property | Type | Required | Description |
|---|---|---|---|
| **action**| [ToastAction](#toastaction) | false | Declares what action to take when the toast is clicked by the user. |
| **visual** | [ToastVisual](#toastvisual) | true | Describes the visual portion of the toast notification |
| **audio** | [ToastAudio](#toastaudio) | false | Describes the audio portion of the toast notification |
| **scenario** | [ToastScenario](#toastscenario) | false | Declares the scenario your toast is used for, like an alarm or reminder. |
| **displayTimestamp** | datetime | false | Override the default timestamp with a custom timestamp representing when your notification content was actually delivered, rather than the time the notification was received by the Windows platform. |
| **header** | [ToastHeader](#toastheader) | false | Add a custom header to your notification to group multiple notifications together within Action Center. |


## ToastVisual
The visual portion of toasts contains the text, images, inputs, and actions.

| Property | Type | Required | Description |
|---|---|---|---|
| **bindings** | [ToastBindings](#toastbindings) | true | A set of bindings that represent the various visual layouts of the toast notification. |
| **baseUrl** | url | false | A default base URL that is combined with relative URLs in image source attributes. |
| **addImageQuery** | boolean | false | Set to "true" to allow Windows to append a query string to the image URL supplied in the toast notification. Use this attribute if your server hosts images and can handle query strings, either by retrieving an image variant based on the query strings or by ignoring the query string and returning the image as specified without the query string. This query string specifies scale, contrast setting, and language; for instance, a value of "www.website.com/images/hello.png" given in the notification becomes "www.website.com/images/hello.png?ms-scale=100&ms-contrast=standard&ms-lang=en-us" |
| **lang**| string | false | The target locale of the visual payload when using localized resources, specified as BCP-47 language tags such as "en-US" or "fr-FR". This locale is overridden by any locale specified in binding or text. If not provided, the system locale will be used instead. |


## ToastBindings
A set of bindings that represent the various visual layouts of the toast notification.

| Property | Type | Required | Description |
|---|---|---|---|
| **generic** | [ToastBindingGeneric](#toastbindinggeneric) | true | The generic toast binding, which is used across various UI surfaces. |


## ToastBindingGeneric
The generic toast binding, which is used across various UI surfaces.

| Property | Type | Required | Description |
|---|---|---|---|
| **title** | [ToastGenericTextBlock](#toastgenerictextblock) | true | The title string to be displayed on the toast notification. Note that only the text, lang, and maxLines properties are supported. |
| **descriptionLine1** | [ToastGenericTextBlock](#toastgenerictextblock) | false | The first line of description text to be displayed on the toast notification. Note that only the text, lang, and maxLines properties are supported. |
| **descriptionLine2** | [ToastGenericTextBlock](#toastgenerictextblock) | false | The second line of description text to be displayed on the toast notification. Note that only the text, lang, and maxLines properties are supported. |
| **appLogoOverride** | [ToastGenericAppLogo](#toastgenericapplogo) | false | An optional logo to override the app logo. |
| **heroImage** | [ToastGenericHeroImage](#toastgenericheroimage) | false | An optional featured "hero" image that is displayed on the toast and within Action Center. |
| **attribution** | [ToastGenericAttributionText](#toastgenericattributiontext) | false | Optional attribution text which will be displayed at the bottom of the toast notification. |
| **body** | [CardElement](Schema.md#cardelement)[] | false | An optional array of adaptive CardElement objects to be displayed after the title and description. |
| **actions** | [CardElement](Schema.md#cardelement)[] | false | An optional array of adaptive CardElement objects displayed in the action bar of the toast notification, where you can take inputs, provide buttons, and more. |
| **baseUrl** | url | false | A default base URL that is combined with relative URLs in image source attributes. |
| **addImageQuery** | boolean | false | Set to "true" to allow Windows to append a query string to the image URL supplied in the toast notification. Use this attribute if your server hosts images and can handle query strings, either by retrieving an image variant based on the query strings or by ignoring the query string and returning the image as specified without the query string. This query string specifies scale, contrast setting, and language; for instance, a value of "www.website.com/images/hello.png" given in the notification becomes "www.website.com/images/hello.png?ms-scale=100&ms-contrast=standard&ms-lang=en-us" |
| **lang**| string | false | The target locale of the visual payload when using localized resources, specified as BCP-47 language tags such as "en-US" or "fr-FR". This locale is overridden by any locale specified in binding or text. If not provided, the system locale will be used instead. |


## ToastGenericTextBlock
A title or description line of text that is displayed in both the collapsed and expanded portion of the toast notification.

| Property | Type | Required | Description |
|---|---|---|---|
| **text** | string | true | The text to display. |
| **lang** | string | false | The target locale of the visual payload when using localized resources, specified as BCP-47 language tags such as "en-US" or "fr-FR". If not provided, the system locale will be used instead. |
| **wrap** | boolean | false | Indicates whether the text should be allowed to wrap. If not provided, the default behavior is determined by Action Center. |
| **maxLines** | number | false | You can specify the maximum number of lines allowed. If not provided, the default value is determined by Action Center. |


## ToastGenericAppLogo
A logo to be displayed instead of the app logo.

| Property | Type | Required |Description |
|---|---|---|---|
| **url** | string | true | The URL to the image. ms-appx, ms-appdata, and http are supported. |
| **style** | [ToastAppLogoImageStyle](#toastapplogoimagestyle) | false | The style in which the image is displayed. |
| **altText** | string | false | Alternate text describing the image, used for accessibility purposes. |
| **addImageQuery** | boolean | false | Set to "true" to allow Windows to append a query string to the image URL supplied in the toast notification. Use this attribute if your server hosts images and can handle query strings, either by retrieving an image variant based on the query strings or by ignoring the query string and returning the image as specified without the query string. This query string specifies scale, contrast setting, and language; for instance, a value of "www.website.com/images/hello.png" given in the notification becomes "www.website.com/images/hello.png?ms-scale=100&ms-contrast=standard&ms-lang=en-us" |


## ToastGenericHeroImage
A featured "hero" image that is displayed on the toast and within Action Center.

| Property | Type | Required |Description |
|---|---|---|---|
| **url** | string | true | The URL to the image. ms-appx, ms-appdata, and http are supported. |
| **altText** | string | false | Alternate text describing the image, used for accessibility purposes. |
| **addImageQuery** | boolean | false | Set to "true" to allow Windows to append a query string to the image URL supplied in the toast notification. Use this attribute if your server hosts images and can handle query strings, either by retrieving an image variant based on the query strings or by ignoring the query string and returning the image as specified without the query string. This query string specifies scale, contrast setting, and language; for instance, a value of "www.website.com/images/hello.png" given in the notification becomes "www.website.com/images/hello.png?ms-scale=100&ms-contrast=standard&ms-lang=en-us" |


## ToastGenericAttributionText
Attribution text displayed at the bottom of the toast notification.

| Property | Type | Required | Description |
|---|---|---|---|
| **text** | string | true | The text to display. |
| **lang** | string | false | The target locale of the visual payload when using localized resources, specified as BCP-47 language tags such as "en-US" or "fr-FR". If not provided, the system locale will be used instead. |


## ToastAction
*Extends [Action](Schema.md#action)*

Base class for all toast actions

> NOTE: You cannot add a ToastAction directly, you can only add derived action types

| Property | Type | Required | Description |
|---|---|---|---|
| **imageUrl**| url | false | An optional image (ms-appx or ms-appdata) that is displayed on the button in addition to the button text. |


## ToastOpenUrlAction
*Extends [ToastAction](#toastaction)*

When ToastOpenUrlAction is invoked it will protocol activate the given url. Can be a https url, or an app link like settings:storage.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"ToastOpenUrlAction"** |
| **url** | string | true | The protocol url to launch.  |
| **targetApplicationPfn** | string | false | You can optionally specify the target PFN of the app you want to protocol launch, so that regardless of whether multiple apps are registered to handle the same protocol url, your desired app will always be launched. |


## ToastForegroundAction
*Extends [ToastAction](#toastaction)*

Gathers up input fields, merges with optional data field and performs a foreground launch of the app.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"ToastForegroundAction"** |
| **data** | object | false | Initial data that input fields will be combined with.  This is essentially 'hidden' properties |


## ToastBackgroundAction
*Extends [ToastAction](#toastaction)*

Gathers up input fields, merges with optional data field and performs a background task launch of the app.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"ToastBackgroundAction"** |
| **data** | object | false | Initial data that input fields will be combined with.  This is essentially 'hidden' properties |
| **afterActivationBehavior** | [ToastAfterActivationBehavior](#toastafteractivationbehavior) | false | New in RS3. Specifies the behavior that the toast should use when the user invokes this action. |


## ToastSnoozeAction
*Extends [ToastAction](#toastaction)*

This action automatically handles snoozing the toast notification.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"ToastSnoozeAction"** |
| **snoozeTimeInputId** | string | false | Optionally specify the ID of an existing input in order to allow the user to pick a custom snooze time. The value of the input must represent the snooze interval in minutes. For example, if the user selects an item that has a value of "120", then the notification will be snoozed for 2 hours. When the user clicks this button, If you don't specify this ID, the system will snooze by the default system snooze time. |


## ToastDismissAction
*Extends [ToastAction](#toastaction)*

This action simply dismisses the toast notification without any further action being performed.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"ToastDismissAction"** |


## ToastShowCardAction
*Extends [ToastAction](#toastaction)*

ShowCard defines an inline AdaptiveCard which is shown to the user when it is clicked.

| Property | Type | Required | Description |
|---|---|---|---|
| **type**| string | true | **"ToastShowCardAction"** |
| **card** | [AdaptiveCard](#adaptivecard) | true | Inline card defining the card to be shown when this action is invoked. The card will be displayed below the associated action. |


## ToastAfterActivationBehavior
New in RS3. Specifies the behavior that the toast should use when the user takes action on the toast.

| Value | Meaning |
|---|---|
| **Default** | Default behavior. The toast will be dismissed when the user takes action on the toast. |
| **PendingUpdate** | After the user clicks a button on your toast, the notification will remain present, in a "pending update" visual state. You should immediately update your toast from a background task so that the user does not see this "pending update" visual state for too long. |


## ToastAudio
Specify audio to be played when the Toast notification is received.

| Property | Type | Required | Description |
|---|---|---|---|
| **src** | url | false | The media file to play in place of the default sound. Only ms-appx and ms-appdata are supported. |
| **loop** | boolean | false | Set to true if the sound should repeat as long as the Toast is shown; false to play only once (default). |
| **silent** | boolean | false | True to mute the sound; false to allow the toast notification sound to play (default). |


## ToastScenario
Specifies what scenario the toast represents.

| Value | Meaning |
|---|---|
| **Default** | The normal toast behavior. |
| **Reminder** | A reminder notification. This will be displayed pre-expanded and stay on the user's screen till dismissed. |
| **Alarm** | An alarm notification. This will be displayed pre-expanded and stay on the user's screen till dismissed. Audio will loop by default and will use alarm audio. |
| **IncomingCall** | An incoming call notification. This will be displayed pre-expanded in a special call format and stay on the user's screen till dismissed. Audio will loop by default and will use ringtone audio. |


## ToastHeader
A custom header that groups multiple notifications together within Action Center.

| Property | Type | Required | Description |
|---|---|---|---|
| **id** | string | true | A developer-created identifier that uniquely identifies this header. If two notifications have the same header id, they will be displayed underneath the same header in Action Center. |
| **title** | string | true | A title for the header. |
| **action**| [Action](Schema.md#action) | false | Declares what action to take when the toast is clicked by the user. |
