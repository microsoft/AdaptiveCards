//
//  ACRChoiceSetViewDataSource
//  ACRChoiceSetViewDataSource.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRIBaseInputHandler.h"
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "HostConfig.h"
#import <UIKit/UIKit.h>

extern NSString *checkedCheckboxReuseID;
extern NSString *uncheckedCheckboxReuseID;
extern NSString *checkedRadioButtonReuseID;
extern NSString *uncheckedRadioButtonReuseID;

@interface ACRChoiceSetCell : UITableViewCell
@end

@interface ACRChoiceSetViewDataSource : NSObject <UITableViewDataSource, UITableViewDelegate, ACRIBaseInputHandler>
@property NSString *id;
@property BOOL isMultiChoicesAllowed;

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const &)choiceSet;

- (void)getDefaultInput:(NSMutableDictionary *)dictionary;

- (NSString *)getTitlesOfChoices;

@end
