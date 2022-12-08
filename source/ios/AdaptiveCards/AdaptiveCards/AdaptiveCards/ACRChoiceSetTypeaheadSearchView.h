//
//  ACRChoiceSetTypeaheadSearchView.h
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 07/11/22.
//  Copyright © 2022 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACODebouncer.h"
#import "BaseCardElement.h"
#import "ACRView.h"
#import "HostConfig.h"
#import "ACRChoiceSetCompactStyleView.h"

typedef enum {
    error = 0,
    networkError,
    success
} ACODynamicTypeaheadResponseType;

@interface ACRChoiceSetTypeaheadSearchView : UIViewController <UITextFieldDelegate,ACODebouncerDelegate,UITableViewDelegate,UITableViewDataSource>

@property NSString *id;
@property NSMutableDictionary *results;
@property (weak) UIView *filteredListView;

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)acoConfig
                              delegate:(ACRChoiceSetCompactStyleView *)delegate;
@end
