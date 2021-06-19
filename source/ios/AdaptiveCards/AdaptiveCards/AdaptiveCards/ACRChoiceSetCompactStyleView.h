//
//  ACRChoiceSetCompactStyleTextFiled
//  ACRChoiceSetCompactStyleTextFiled.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRIBaseInputHandler.h"
#import "ACRView.h"
#import "ACOHostConfig.h"
#import <UIKit/UIKit.h>

@interface ACRChoiceSetCompactStyleView : UITextField <UITextFieldDelegate, UITableViewDelegate, UITableViewDataSource, ACRIBaseInputHandler>
@property NSString *id;
@property NSMutableDictionary *results;
@property (weak) UIView *filteredListView;
@property (weak) UIView *showFilteredListControl;

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)acoConfig;
@end

@interface ACOFilteredDataSource : NSObject

@property (readonly) NSUInteger count;

- (void)addToSource:(NSString *)item;

- (NSString *)getItemAt:(NSInteger)index;

- (void)filter:(NSString *)filter;

- (void)resetFilter;

@end

@interface ACOFilteredListStateManager : NSObject

@property (readonly) BOOL isShowFilteredListControlSelected;
@property (readonly) BOOL isFilteredListVisible;
@property (readonly) BOOL shouldUpdateFilteredList;

- (void)filteredListControlSelected;
- (void)filteredListControlDeselected;
- (void)showFilteredListView;
- (void)hideFilteredListView;
- (void)toggleFilteredListView;
- (void)toggleShowFilteredListControl;

@end
