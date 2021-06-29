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
/// top margin of filtered list view
@property CGFloat spacingTop;
/// bottom margin of filtered list view
@property CGFloat spacingBottom;

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)acoConfig;
@end

@interface ACOFilteredDataSource : NSObject

@property (readonly) NSUInteger count;
@property (readonly) BOOL isEnabled;

- (instancetype)init:(BOOL)filteringEnabled;

- (void)addToSource:(NSString *)item;

- (NSString *)getItemAt:(NSInteger)index;

- (void)filter:(NSString *)filter;

- (void)resetFilter;

@end

@interface ACOFilteredListStateManager : NSObject

@property (readonly) BOOL isShowFilteredListControlSelected;
@property (readonly) BOOL isFilteredListVisible;
@property (readonly) BOOL shouldUpdateFilteredList;

- (void)expanded;
- (void)collapsed;
- (void)toggleState;

@end

@interface ACOChoiceSetCompactStyleValidator : NSObject

@property BOOL isRequired;
@property NSString *placeHolder;
@property (readonly, copy) NSString *userInitialChoice;

- (instancetype)init:(ACOBaseCardElement *)acoElem  dataSource:(ACOFilteredDataSource *)dataSource;

- (BOOL)isValid:(NSString *)input;

- (NSString *)getValue:(NSString *)input;

@end

@interface ACOFilteredListLayout : NSObject

@property CGFloat y;
@property CGFloat height;
@property CGFloat topMargin;
@property CGFloat bottomMargin;
@property CGRect keyboardFrame;

- (instancetype)initWithTopMargin:(CGFloat)top bottomMargin:(CGFloat)bottom;

- (BOOL)shouldDrawBelow:(CGFloat)windowHeight inputHeight:(CGFloat)inputHeight yPos:(CGFloat)yPos;

- (void)refreshDimension:(CGFloat)windowHeight inputYPos:(CGFloat)inputYPos inputHeight:(CGFloat)inputHeight yPos:(CGFloat)yPos rootViewFrame:(CGRect)rootViewFrame;

@end
