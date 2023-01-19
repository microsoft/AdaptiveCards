//
//  ACRChoiceSetTypeaheadSearchView.h
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 07/11/22.
//  Copyright © 2022 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACOTypeaheadDebouncer.h"
#import "BaseCardElement.h"
#import "ACRView.h"
#import "HostConfig.h"
#import "ACRChoiceSetCompactStyleView.h"
#import "ACRTypeaheadSearchParameters.h"
#import "ACOTypeaheadDynamicChoicesService.h"
#import "ACRChoiceSetFilteredStyleView.h"
#import "ACOTypeaheadSearchHandler.h"

@interface ACRTypeaheadSearchViewController : UIViewController <UISearchBarDelegate, UITableViewDelegate,UITableViewDataSource,ACRTypeaheadSearchProtocol>

@property NSString *id;
@property (weak) UIView *filteredListView;
@property UISearchBar *searchBar;
@property UIView *searchBarSeparator;
@property UIActivityIndicatorView *loader;
@property UILabel *searchStateTitleLabel;
@property UILabel *searchStateSubtitleLabel;
@property UIImageView *searchStateImageView;
@property UIStackView *stackViewContainer;

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)acoConfig
                     choiceSetDelegate:(id<ACRChoiceSetFilteredDelegate>)choiceSetDelegate
                     searchStateParams:(ACRTypeaheadStateAllParameters *)searchStateParams;
@end
