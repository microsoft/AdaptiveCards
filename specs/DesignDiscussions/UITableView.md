# UITableView
## Problem Description
Using UITableView as a hosting view for AdaptiveCard requires additional considerations. One of the challenges is the height changes in the row. UITableView correctly self sizes most of the times, but it breaks down in a few known cases. For example, if the images are loaded asynchronously, it will cause the height changes in the card. Unfortunately, the row does not adjust the height dynamically if the row is already drawn. The table view also fails to adjust its height when the visibility of its subviews changes. 
In such cases, there are a few well known practices in dealing with such occasions. This document covers practical guides in dealing with the height changes. This document will focus on [beginUpdates()](https://developer.apple.com/documentation/uikit/uitableview/1614908-beginupdates) and [reloadRows(at:with:)](https://developer.apple.com/documentation/uikit/uitableview/1614935-reloadrows) methods. It will show how to use the APIs in conjunction with AdaptiveCards' API. The rest of the documents uses the [iOS AdaptiveCard sample app](https://github.com/microsoft/AdaptiveCards/tree/main/source/ios/AdaptiveCards/ADCIOSVisualizer/ADCIOSVisualizer) as an example.
## Apple API
1. [beginUpdates()](https://developer.apple.com/documentation/uikit/uitableview/1614908-beginupdates)
     - As documented in the [Apple Documentation](https://developer.apple.com/documentation/uikit/uitableview/1614908-beginupdates), this method can be used to animate the changes in the row heights **without reloading the cell** followed by endUpdates().
	 - The method doesn't reload the table view. Not reloading the cell is one of the most frequently cited reasons for the advocation of the method.
     - It's easier to use this method than using reloadRowsAtIndexPaths method
     - Some of the usage [examples](https://www.raywenderlich.com/8549-self-sizing-table-view-cells)
2. [reloadRowsAtIndexPaths:withRowAnimation](https://developer.apple.com/documentation/uikit/uitableview/1614935-reloadrowsatindexpaths)
    - Reloads a row by asking a table view's data source for a new cell for that row.
    - It can be tricky as timing requirement and having to know which rows to reload mandates more careful approaches than using `beginUpdates()`
3. [Great Central Dispatch(GCD)](https://developer.apple.com/documentation/DISPATCH).  

## AdaptiveCard API
The following API is used in conjunction with Apple API.
1. `@protocol ACRActionDelegate <NSObject>`
	* `- (void)didLoadElements` is a delegate that get called when AdaptiveCards' resources are all loaded.
	* `- (void)didChangeVisibility:(UIButton *)button isVisible:(BOOL)isVisible` is a delegate when the visibility of the card is changed.
	* `- (void)didChangeViewLayout:(CGRect)oldFrame newFrame:(CGRect)newFrame properties:(NSDictionary *)properties` is a delegate when card's layout has changed.

## Refreshing the Layout Overview
We want the delegate to be called only once after the card is rendered. Due to asynchronous tasks such as image loading, we have to do due diligence of ensuring the order of execution. In this example, we use GCD to ensure the right order. We create a block that renders an AdaptiveCard and queues it to the main queue. When one of the AdaptiveCard delegates is called, we wrap the layout refresh code in a block and queue it. This ensures that the layout refreshing happens after the rendering event. 

1. Render AdaptiveCard 
2. Update data source
3. Notify UITableView
4. Do 1, 2 & 3 in the same block. 
3. As part of step 1 `didLoadElements` is called from the SDK, create a new block and add refreshing codes for the hosting table view to the block and queue it to ensure the right ordering.

### Rendering AdaptiveCard
In this simple example, a card is rendered and added to a data source. After the card completes rendering, the SDK calls `didLoadElements` delegate once its resources are loaded. When `insertRowsAtIndexPaths:withRowAnimation:` is called after `render` call is returned from SDK, the method notifies the hosting table view of the new row which in turn calls `- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath`.

[Sample Example](https://github.com/microsoft/AdaptiveCards/blob/d43eb4e2fe84794eec706cea194b0cf213eaacc8/source/ios/AdaptiveCards/ADCIOSVisualizer/ADCIOSVisualizer/ViewController.m#L558)
```
...
    dispatch_async(_global_queue, ^{
        self.editableStr = jsonStr;
        // the data source will parse & render the card, and update its store for AdaptiveCards
        [self->_dataSource insertCard:jsonStr];
		...
		...
        [self.chatWindow insertRowsAtIndexPaths:indexPaths
                               withRowAnimation:UITableViewRowAnimationNone];
...
```
#### `- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath`
Once the table view is notified of the row changes, `tableView: cellForRowAtIndexPath:` will get called for the new cell. To return the cell, the sample app as a simple example tags a new cell with the address of an AdaptiveCard cache. 
```
	...
	UIView *adaptiveCardView = adaptiveCardsViews[indexPath.row];
    NSString *identifier = [NSString stringWithFormat:@"%p", adaptiveCardView];
    ...
```                                                                    
This simple example may not meet the need of the complex real world scenarios. One should expand the managing the caches of the rendered AdaptiveCards to make it suitable to more complex situations. Furthermore, using the identifier should be refined to make the usage work nicely with `- (void)registerClass: forCellReuseIdentifier:`. 

If the cell has been never created or is already recycled, a new cell is created. 
```
...
cell = [tableView dequeueReusableCellWithIdentifier:identifier];
    if (cell) {
        return cell;
    } else {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                      reuseIdentifier:identifier];
        [cell.contentView addSubview:adaptiveCardView];
    }
...
```

The adaptive card is pinned to the cell. cell's content view's height is pinned to the adaptive card's height, so does for width, center x and center y. 
```
	...
	[adaptiveCardView.centerXAnchor constraintEqualToAnchor:cell.contentView.centerXAnchor].active = YES;
    [adaptiveCardView.centerYAnchor constraintEqualToAnchor:cell.contentView.centerYAnchor].active = YES;
    [cell.contentView.heightAnchor constraintEqualToAnchor:adaptiveCardView.heightAnchor].active = YES;
    [cell.contentView.widthAnchor constraintEqualToAnchor:adaptiveCardView.widthAnchor].active = YES;
	...
```
When the cell is returned from the call and the adaptive card appears on the table view, if the height of the card doesn't change and the dynamically set constraints are perfect, the card would be drawn correctly at this point. However, often time the height of the card changes. For example, the height changes when the image is asynchronously loaded. In this case, the layout refresh is necessary.
### Refreshing Layout
To refresh the row, [beginUpdates()](https://developer.apple.com/documentation/uikit/uitableview/1614908-beginupdates) or [reloadRowsAtIndexPaths:withRowAnimation](https://developer.apple.com/documentation/uikit/uitableview/1614935-reloadrowsatindexpaths) can be used. If `beginUpdates` is used, the call can be added to `didLoadElements` as shown in the below. 
```
- (void)didLoadElements
{
	[tableView beginUpdates];
	[tableView endUpdates];
}
```

However, this is not sufficient because the order of call for refreshing the layout can be out of order. In sample app's simple implementation, the codes for refreshing layout is wrapped in a block and queue to the main queue to order it to be executed after its corresponding rendering block.
[GitHub sample example](https://github.com/microsoft/AdaptiveCards/blob/d43eb4e2fe84794eec706cea194b0cf213eaacc8/source/ios/AdaptiveCards/ADCIOSVisualizer/ADCIOSVisualizer/ViewController.m#L587) 

```
- (void)didLoadElements
{
	dispatch_async(_main_queue,
                   ^{
                        [tableView beginUpdates];
                        [tableView endUpdates];
				   });
}
```
[reloadRowsAtIndexPaths:withRowAnimation](https://developer.apple.com/documentation/uikit/uitableview/1614935-reloadrowsatindexpaths) takes an array of index paths as a parameter. Unlike `beingUpdates` using `reloadRowsAtIndexPaths:withRowAnimation` requires bookkeeping of index path and the associated AdaptiveCard. 

[GitHub sample example](https://github.com/microsoft/AdaptiveCards/blob/d43eb4e2fe84794eec706cea194b0cf213eaacc8/source/ios/AdaptiveCards/ADCIOSVisualizer/ADCIOSVisualizer/ViewController.m#L587) 
```   
- (void)didLoadElements
{
    dispatch_async(_global_queue,
                   ^{
                       NSInteger lastRowIndex = [self->_dataSource tableView:self.chatWindow numberOfRowsInSection:0] - 1;
                       NSIndexPath *pathToLastRow = [NSIndexPath indexPathForRow:lastRowIndex inSection:0]; 
					   [self.chatWindow reloadRowsAtIndexPaths:@[ pathToLastRow ] withRowAnimation:UITableViewRowAnimationNone];
					   ...
```
In this simple example above, the index path is simply the last row of the data source since a new AdaptiveCard is always added at the end of the AdaptiveCard cache of the data source. Keeping the association between an AdaptiveCard and row index may be necessary in more complicated scenario.

