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
#import "ACOTypeaheadDynamicChoicesService.h"

typedef enum {
    error = 0,
    networkError,
    success
} ACODynamicTypeaheadResponseType;

@interface ACRChoiceSetTypeaheadSearchView : UIViewController <UISearchBarDelegate, UITableViewDelegate,UITableViewDataSource,ACOTypeaheadDynamicChoicesProtocol>

@property NSString *id;
@property (weak) UIView *filteredListView;
@property UISearchBar *searchBar;
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
