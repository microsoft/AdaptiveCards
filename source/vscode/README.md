## Features
With AdaptiveCards Studio you can author cards directly in Visual Studio Code. 
The Extension automatically detects all Adaptive Cards in your working space and lets you easily
edit the card template and sample data. 

## Extension Settings

To use the Extension you must configure it first!

This extension contributes the following settings:

* `acstudio.defaultHostConfig`    : The HostConfig to be used when rendering cards
* `acstudio.cmsAccessToken`            : (ALPHA) Access Token for the CMS used
* `acstudio.cmsAccessUrl`              : (ALPHA) URL To the CMS
* `acstudio.cmsFolder`                 : (ALPHA) The Folder where to store temporary files for CMS


## Usage
Open the Adaptive Cards Panel and select a card.... thats all you have to do :)

## Snippets
The Extension comes with various snippets to make authoring cards even easier.
Just press ctrl+space anywhere in the AdaptiveCard Json

* `ac-txt`         : TextBlock with minimum properties
* `ac-txtfull`     : TextBlock with all properties
* `ac-col3`        : Columnset with 3 columns
* `ac-col2`        : Columnset with 2 columns
* `ac-fctset`      : Factset
* `ac-ctr`         : Container
* `ac-img`         : Image

## SampleData
When editing templates its a tremendous help to have sample data available. The Extension lets you
create and store sample data for your templates easily. 


## CMS Usage
The CMS interoperability is in alpha preview, to connect the extension to your self hosted CMS set
the config values above to your URL and access token. The only way to get an access token right now
is using developer tools in your browser and inspecting the calls when logged in to your CMS. 
This is an alpha proof of concept and will have a proper login mechanism soon.  