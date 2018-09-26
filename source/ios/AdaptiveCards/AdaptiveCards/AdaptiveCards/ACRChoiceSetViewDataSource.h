//
//  ACRChoiceSetViewDataSource
//  ACRChoiceSetViewDataSource.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "ACRIBaseInputHandler.h"
#import "HostConfig.h"
#import "ACOHostConfig.h"
#import "ACOHostConfigPrivate.h"

extern NSString *choiceSetCellReuseID;

@interface ACRChoiceSetCell : UITableViewCell
@end

@interface ACRChoiceSetViewDataSource:NSObject<UITableViewDataSource, UITableViewDelegate, ACRIBaseInputHandler>
@property NSString *id;
@property ACOHostConfig *hostConfig;
@property BOOL isMultiChoicesAllowed;

- (instancetype)initWithInputChoiceSet:(std::shared_ptr<AdaptiveCards::ChoiceSetInput> const&)choiceSet
                         andHostConfig:(ACOHostConfig *)hostConfig;

- (void)getDefaultInput:(NSMutableDictionary *)dictionary;

- (NSString *)getTitlesOfChoices;

@end
