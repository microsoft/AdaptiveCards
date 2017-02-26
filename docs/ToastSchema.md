# Table of Contents

TODO

# Windows Toast notifications

## ToastContent
ToastContent is the top level object that describes a notification's content, including visuals, actions, and audio.

| Property | Type | Required | Description |
|---|---|---|---|
| **action**| [Action](#action) | false | Declares what action to take when the toast is clicked by the user. |
| **scenario** | [ToastScenario](#toastscenario) | false | Declares the scenario your toast is used for, like an alarm or reminder. |
| **displayTimestamp** | datetime | false | Override the default timestamp with a custom timestamp representing when your notification content was actually delivered, rather than the time the notification was received by the Windows platform. |
| **header** | [ToastHeader](#toastheader) | false | Add a custom header to your notification to group multiple notifications together within Action Center. |
| **visual** | [ToastVisual](#toastvisual) | true | Describes the visual portion of the toast notification |
| **audio** | [ToastAudio](#toastaudio) | false | Describes the audio portion of the toast notification |


## ToastVisual
The visual portion of toasts contains the text, images, inputs, and actions.

| Property | Type | Required | Description |
|---|---|---|---|
| **bindings** | [ToastBindings](#toastbindings) | true | A set of bindings that represent the various visual layouts of the toast notification. |
| **baseUri** | uri | false | A default base URI that is combined with relative URIs in image source attributes. |
| **addImageQuery** | boolean | false | Set to "true" to allow Windows to append a query string to the image URI supplied in the toast notification. Use this attribute if your server hosts images and can handle query strings, either by retrieving an image variant based on the query strings or by ignoring the query string and returning the image as specified without the query string. This query string specifies scale, contrast setting, and language; for instance, a value of "www.website.com/images/hello.png" given in the notification becomes "www.website.com/images/hello.png?ms-scale=100&ms-contrast=standard&ms-lang=en-us" |
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
| **audio** | [ToastAudio](#toastaudio) | false | Specify custom audio options. |
| **baseUri** | uri | false | A default base URI that is combined with relative URIs in image source attributes. |
| **addImageQuery** | boolean | false | Set to "true" to allow Windows to append a query string to the image URI supplied in the toast notification. Use this attribute if your server hosts images and can handle query strings, either by retrieving an image variant based on the query strings or by ignoring the query string and returning the image as specified without the query string. This query string specifies scale, contrast setting, and language; for instance, a value of "www.website.com/images/hello.png" given in the notification becomes "www.website.com/images/hello.png?ms-scale=100&ms-contrast=standard&ms-lang=en-us" |
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
| **addImageQuery** | boolean | false | Set to "true" to allow Windows to append a query string to the image URI supplied in the toast notification. Use this attribute if your server hosts images and can handle query strings, either by retrieving an image variant based on the query strings or by ignoring the query string and returning the image as specified without the query string. This query string specifies scale, contrast setting, and language; for instance, a value of "www.website.com/images/hello.png" given in the notification becomes "www.website.com/images/hello.png?ms-scale=100&ms-contrast=standard&ms-lang=en-us" |


## ToastGenericHeroImage
A featured "hero" image that is displayed on the toast and within Action Center.

| Property | Type | Required |Description |
|---|---|---|---|
| **url** | string | true | The URL to the image. ms-appx, ms-appdata, and http are supported. |
| **altText** | string | false | Alternate text describing the image, used for accessibility purposes. |
| **addImageQuery** | boolean | false | Set to "true" to allow Windows to append a query string to the image URI supplied in the toast notification. Use this attribute if your server hosts images and can handle query strings, either by retrieving an image variant based on the query strings or by ignoring the query string and returning the image as specified without the query string. This query string specifies scale, contrast setting, and language; for instance, a value of "www.website.com/images/hello.png" given in the notification becomes "www.website.com/images/hello.png?ms-scale=100&ms-contrast=standard&ms-lang=en-us" |


## ToastGenericAttributionText
Attribution text displayed at the bottom of the toast notification.

| Property | Type | Required | Description |
|---|---|---|---|
| **text** | string | true | The text to display. |
| **lang** | string | false | The target locale of the visual payload when using localized resources, specified as BCP-47 language tags such as "en-US" or "fr-FR". If not provided, the system locale will be used instead. |


## ToastAudio
Specify audio to be played when the Toast notification is received.

| Property | Type | Required | Description |
|---|---|---|---|
| **src** | uri | false | The media file to play in place of the default sound. Only ms-appx and ms-appdata are supported. |
| **loop** | boolean | false | Set to true if the sound should repeat as long as the Toast is shown; false to play only once (default). |
| **silent** | boolean | false | True to mute the sound; false to allow the toast notification sound to play (default). |
