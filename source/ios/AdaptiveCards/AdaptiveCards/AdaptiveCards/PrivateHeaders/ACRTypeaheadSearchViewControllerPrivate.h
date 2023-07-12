//
//  ACRTypeaheadSearchViewControllerPrivate.h
//  AdaptiveCards
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#ifdef SWIFT_PACKAGE
/// Swift Package Imports
#import "ACOTypeaheadDebouncer.h"
#import "ACOTypeaheadSearchHandler.h"
#import "ACRChoiceSetCompactStyleView.h"
#import "ACRChoiceSetFilteredStyleView.h"
#import "ACRTypeaheadSearchParameters.h"
#import "ACRView.h"
#import "BaseCardElement.h"
#import "HostConfig.h"
#else
/// Cocoapods Imports
#import <AdaptiveCards/ACOTypeaheadDebouncer.h>
#import <AdaptiveCards/ACOTypeaheadSearchHandler.h>
#import <AdaptiveCards/ACRChoiceSetCompactStyleView.h>
#import <AdaptiveCards/ACRChoiceSetFilteredStyleView.h>
#import <AdaptiveCards/ACRTypeaheadSearchParameters.h>
#import <AdaptiveCards/ACRView.h>
#import <AdaptiveCards/BaseCardElement.h>
#import <AdaptiveCards/HostConfig.h>
#endif
#import "ACOTypeaheadDynamicChoicesService.h"
#import <UIKit/UIKit.h>

@interface ACRTypeaheadSearchViewController : UIViewController <UISearchBarDelegate, UITableViewDelegate, UITableViewDataSource, ACRTypeaheadSearchProtocol>

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
                    filteredDataSource:(ACOFilteredDataSource *)filteredDataSource
                filteredStyleValidator:(ACOChoiceSetFilteredStyleValidator *)validator
                    typeaheadViewTitle:(NSString *)typeaheadViewTitle
                     choiceSetDelegate:(id<ACRChoiceSetFilteredDelegate>)choiceSetDelegate
                     searchStateParams:(ACRTypeaheadStateAllParameters *)searchStateParams;
@end
