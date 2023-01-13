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
#import "ACRTypeaheadSearchParameters.h"

typedef enum {
    error = 0,
    networkError,
    success
} ACODynamicTypeaheadResponseType;

@interface ACRChoiceSetTypeaheadSearchView : UIViewController <UITableViewDelegate,UITableViewDataSource>

@property NSString *id;
@property (weak) UIView *filteredListView;
@property UITextField *searchBar;
@property UIView *searchBarSeparator;
@property UIActivityIndicatorView *loader;
@property UILabel *searchStateTitleLabel;
@property UILabel *searchStateSubtitleLabel;
@property UIImageView *searchStateImageView;

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)acoConfig
                              delegate:(ACRChoiceSetCompactStyleView *)delegate
                  searchStateParams:(ACRTypeaheadStateAllParameters *)searchStateParams;
@end
