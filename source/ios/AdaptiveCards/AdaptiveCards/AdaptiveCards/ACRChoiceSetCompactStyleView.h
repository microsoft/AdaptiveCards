//
//  ACRChoiceSetCompactStyleTextFiled
//  ACRChoiceSetCompactStyleTextFiled.h
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRIBaseInputHandler.h"
#import "ACRView.h"
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "HostConfig.h"
#import <UIKit/UIKit.h>

@interface ACRChoiceSetCompactStyleView : UITextField <UITextFieldDelegate, UITableViewDelegate, UITableViewDataSource, ACRIBaseInputHandler>
@property NSString *id;
@property BOOL isMultiChoicesAllowed;
@property NSMutableDictionary *results;
@property (weak) ACRView *rootView;
@property (weak) UIView *filteredListView;
@property (weak) UIView *showFilteredListControl;

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)acoConfig;
@end
