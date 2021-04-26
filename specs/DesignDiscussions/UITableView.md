# UITableView
## Problem Description
Using UITableView as a hosting view for AdaptiveCard requires additional considerations. One of the challenges is the height changes that happens in the row. UITableView correctly self sizes most of the times, but it breaks down in a few known cases, for example, if the images are loaded asynchronously causing height changes after the row is drawn, or if the visibility changes in its subviews, the row does not adjust the height dynamically. In such cases, there are a few well known practices in dealing with such occasions. This document covers practical guidelines of using them. This document will focus on [beginUpdates()](https://developer.apple.com/documentation/uikit/uitableview/1614908-beginupdates) and [reloadRows(at:with:)](https://developer.apple.com/documentation/uikit/uitableview/1614935-reloadrows) methods. It will show how to use the APIs in conjunction with AdaptiveCards' API. The rest of the documents uses the [iOS AdaptiveCard sample app](https://github.com/microsoft/AdaptiveCards/tree/main/source/ios/AdaptiveCards/ADCIOSVisualizer/ADCIOSVisualizer) as an example.
## Apple API
1. [beginUpdates()](https://developer.apple.com/documentation/uikit/uitableview/1614908-beginupdates)
     - As documented in the [Apple Documentation](https://developer.apple.com/documentation/uikit/uitableview/1614908-beginupdates), this method can be used to animate the changes in the row heights wihtout reloading the cell followed by endUpdates().
	 - Not reloading the cell is one of the frequent reasons the devs give in popluar sites such as StackOverflow.
     - It's easier to use this method than using reloadRowsAtIndexPaths method
     - Some of the usage [examples](https://www.raywenderlich.com/8549-self-sizing-table-view-cells)
2. [reloadRowsAtIndexPaths:withRowAnimation](https://developer.apple.com/documentation/uikit/uitableview/1614935-reloadrowsatindexpaths)
    - Reloads a row by asking a table view's data source for a new cell for that row.
    - It can be tricky as timing requirement and having to know which rows to reload mandates more careful approaches than using `beginUpdates()`
3. [Great Central Dispatch(GCD)](https://developer.apple.com/documentation/DISPATCH).  

## AdaptiveCard API
The following API is used in conjunction with Apple API.
1. `@protocol ACRActionDelegate <NSObject>`
	* `- (void)didLoadElements` is a delegate that get called when AdaptiveCards' resources are loaded.
	* `- (void)didChangeVisibility:(UIButton *)button isVisible:(BOOL)isVisible` is a delegate when the visibility of the card is changed.
	* `- (void)didChangeViewLayout:(CGRect)oldFrame newFrame:(CGRect)newFrame properties:(NSDictionary *)properties` is a delegate when card's layout has changed.

## Overview
1. Render AdaptiveCard 
2. Update data source
3. Wait for the `didLoadElements` to get called.
4. Refresh the row to update the height of the row.

To refresh the row, [beginUpdates()](https://developer.apple.com/documentation/uikit/uitableview/1614908-beginupdates) or [reloadRowsAtIndexPaths:withRowAnimation](https://developer.apple.com/documentation/uikit/uitableview/1614935-reloadrowsatindexpaths) can be used. If `beginUpdates` is used, the call can be added to `didLoadElements`
```
- (void)didLoadElements
{
	beginUpdates();
	endUpdates();
}
```
We want the delegate to be called only once after the card is rendered. Due to asynchronous tasks such as image loading, we have to do due diligence of ensuring the order of execution. In this example, we use GCD to ensure the right order. We create a block that renders an AdaptiveCard and queues it to the main queue. When the delegate is called, we wraps the layout refresh code in a block and queues it. This ensures that the layout refreshing happens after the rendering event. 
#### [GitHub sample example](https://github.com/microsoft/AdaptiveCards/blob/d43eb4e2fe84794eec706cea194b0cf213eaacc8/source/ios/AdaptiveCards/ADCIOSVisualizer/ADCIOSVisualizer/ViewController.m#L587) 

```
- (void)didLoadElements
{
	dispatch_async(_main_queue,
                   ^{
						beginUpdates();
						endUpdates();
				   });
}
```
