//
//  ACRChoiceSetViewDataSourceCompactStyle
//  ACRChoiceSetViewDataSourceCompactStyle.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRIBaseInputHandler.h"
#import "ACRView.h"
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "HostConfig.h"
#import <UIKit/UIKit.h>

@interface ACRChoiceSetViewDataSourceCompactStyle : NSObject <UITableViewDataSource, UITableViewDelegate, UIPickerViewDataSource, UIPickerViewDelegate, ACRIBaseInputHandler>
@property NSString *id;
@property BOOL isMultiChoicesAllowed;
@property NSMutableDictionary *results;
@property (weak) ACRView *rootView;

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const &)choiceSet
                              rootView:(ACRView *)rootView;
@end
