# UITableView
## Problem Description
Using UITableView as a hosting view for AdaptiveCard requires additional considerations. One of the challenges is incorrect height for the row. UITableView correctly self sizes most of the times, but it breaks down in a few known cases, for example, if the images are loaded asynchronously, or if visibility changes for sub views in visible rows, the cells does not adjust the height dynamically. In such cases, there are few well known practices in dealing with such occasions. This document covers one such practice.     
## Overview
This document will focus on [reloadRows(at:with:)](https://developer.apple.com/documentation/uikit/uitableview/1614935-reloadrows) method. The method is used in reloading the rows specified with an NSArray of NSIndexPath. When the height changes, reloadRows makes request for layout refresh to the hosting UITableView. The rest of the documents covers the example used in iOS AdaptiveCard sample app such uses.
## AdaptiveCard API
* render a card
* update data source
* this should be enough if no Image, ShowCard, or ToggleVisibility are used in AdaptiveCards.
* Otherwise, UITableView needs to refresh the hosting view after the height changes of an AdaptiveCard.
