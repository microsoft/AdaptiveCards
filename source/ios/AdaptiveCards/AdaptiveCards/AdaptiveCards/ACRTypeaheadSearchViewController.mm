//
//  ACRChoiceSetFullScreenView.mm
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 07/11/22.
//  Copyright © 2022 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRTypeaheadSearchViewController.h"
#import "ACRChoiceSetCompactStyleView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOBundle.h"
#import "ACRActionDelegate.h"
#import "ACRBaseCardElementRenderer.h"
#import "ChoicesData.h"
#import "ACRInputLabelView.h"
#import "ACRView.h"
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "HostConfig.h"
#import "UtiliOS.h"
#import "ACOTypeaheadDynamicChoicesService.h"
#import "ACRChoiceSetFilteredStyleView.h"
#include "ACOHostConfigPrivate.h"

typedef enum {
    none = 0,
    staticDataSource,
    dynamicDataSource,
} TSChoicesDataSource;

typedef enum {
    zeroState = 0,
    searchInProgress,
    displayingGenericError,
    displayingInvalidSearchError,
    displayingResults,
} TSTypeaehadSearchViewState;

typedef enum {
    error = 0,
    networkError,
    success
} ACODynamicTypeaheadResponseType;

@implementation ACRTypeaheadSearchViewController {
    UITextField *_textField;
    ACOFilteredDataSource *_filteredDataSource;
    ACOBaseCardElement *_inputElem;
    dispatch_queue_t _global_queue;
    NSString *_inputLabel;
    UITableView *_listView;
    __weak ACRView *_rootView;
    NSInteger _wrapLines;
    TSChoicesDataSource _dataSourceType;
    TSTypeaehadSearchViewState _searchViewState;
    ACOChoiceSetCompactStyleValidator *_validator;
    UIStackView *_container;
    id<ACRChoiceSetFilteredDelegate> _choiceSetDelegate;
    ACRTypeaheadStateAllParameters *_searchStateParams;
    UISearchBar *_searchBar;
    UIView *_customSearchBarSeparator;
    UIActivityIndicatorView *_loader;
    UILabel *_searchStateTitleLabel;
    UIImageView *_searchStateImageView;
    UILabel *_searchStateSubtitleLabel;
    ACOTypeaheadDynamicChoicesService *_dynamicChoicesService;
    NSString *searchText;
}

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)hostConfig
                     choiceSetDelegate:(id<ACRChoiceSetFilteredDelegate>)choiceSetDelegate
                     searchStateParams:(ACRTypeaheadStateAllParameters *)searchStateParams
{
    self = [super init];
    if (self) {
        std::shared_ptr<BaseCardElement> elem = [acoElem element];
        std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
        _rootView = rootView;
        _inputElem = acoElem;
        _choiceSetDelegate = choiceSetDelegate;
        _searchStateParams = searchStateParams;
        _filteredDataSource = [[ACOFilteredDataSource alloc] init];
        _validator = [[ACOChoiceSetCompactStyleValidator alloc] init:acoElem dataSource:_filteredDataSource];
        _wrapLines = choiceSet->GetWrap() ? 0 : 1;
        _dynamicChoicesService = [[ACOTypeaheadDynamicChoicesService alloc] initWithRootView:_rootView inputElem:_inputElem typeaheadSearchDelegate:self];
        std::shared_ptr<ChoicesData> choicesData = choiceSet->GetChoicesData();
        _dataSourceType = none;
        if (choicesData->GetChoicesDataType().compare((AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::DataQuery))) == 0 )
        {
            _dataSourceType = dynamicDataSource;
        } else if (choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Filtered) {
            _dataSourceType =  staticDataSource;
        }
    }

    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    std::shared_ptr<BaseCardElement> elem = [_inputElem element];
    std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
    self.view.backgroundColor = UIColor.whiteColor;
    UIView *mainview = [[UIView alloc] initWithFrame:CGRectZero];
    [mainview setFrame:self.view.bounds];
    [mainview setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
    mainview.backgroundColor = UIColor.whiteColor;
    [self.view addSubview:mainview];
    
    _container = [[UIStackView alloc] initWithFrame:CGRectZero];
    _container.axis = UILayoutConstraintAxisVertical;
    _container.layoutMargins = UIEdgeInsetsMake(12, 0, 16, 16);
    _container.layoutMarginsRelativeArrangement = YES;
    _container.translatesAutoresizingMaskIntoConstraints = NO;
    _container.spacing = 14;
    self.stackViewContainer = _container;
    // [ACOHostConfig convertHexColorCodeToUIColor:"#F4F4F4"];
    _container.backgroundColor = UIColor.whiteColor;
    [mainview addSubview:_container];
    _searchBar = [UISearchBar new];
    [_searchBar sizeToFit];
    _searchBar.delegate = self;
    [_searchBar becomeFirstResponder];
    _searchBar.text = [_choiceSetDelegate getSelectedText];
    _searchBar.placeholder = _validator.placeHolder ?: @"Enter a search term";
    self.searchBar = _searchBar;
    
    _customSearchBarSeparator = [[UIView alloc] init];
    self.searchBarSeparator = _customSearchBarSeparator;
    _listView = [[UITableView alloc] init];
    _listView.dataSource = self;
    _listView.delegate = self;
    _listView.accessibilityIdentifier = [NSString stringWithUTF8String:choiceSet->GetId().c_str()];
    self.filteredListView = _listView;
    [_container addArrangedSubview:_searchBar];
    [_container addArrangedSubview:_customSearchBarSeparator];
    [_container addArrangedSubview:_listView];

    _loader = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleMedium];
    _loader.translatesAutoresizingMaskIntoConstraints = NO;
    _loader.hidesWhenStopped = YES;
    _loader.hidden = YES;
    self.loader = _loader;
    _searchStateTitleLabel = [[UILabel alloc] init];
    _searchStateTitleLabel.translatesAutoresizingMaskIntoConstraints = NO;
    self.searchStateTitleLabel = _searchStateTitleLabel;
    _searchStateImageView = [[UIImageView alloc] init];
    _searchStateImageView.frame = CGRectMake(self.view.frame.size.width / 2 - 24, self.view.frame.size.height / 2 - 24, 48, 48);
    self.searchStateImageView = _searchStateImageView;
    [self.view addSubview:_loader];
    [self.view addSubview:_searchStateImageView];
    [self.view addSubview:_searchStateTitleLabel];

    [NSLayoutConstraint activateConstraints:@[
        [[_container trailingAnchor] constraintEqualToAnchor:[self.view trailingAnchor]],
        [[_container leadingAnchor] constraintEqualToAnchor:[self.view leadingAnchor]],
        [[_container widthAnchor] constraintEqualToAnchor:[self.view widthAnchor]],
        [[_container topAnchor] constraintEqualToAnchor:[self.view topAnchor]],
        [[_searchBar leadingAnchor] constraintEqualToAnchor:[self.view leadingAnchor] constant:8],
        [[_searchBar trailingAnchor] constraintEqualToAnchor:[self.view trailingAnchor] constant:-8],
        [[_customSearchBarSeparator leadingAnchor] constraintEqualToAnchor:[self.view leadingAnchor] constant:0],
        [[_customSearchBarSeparator trailingAnchor] constraintEqualToAnchor:[self.view trailingAnchor] constant:0],
        [[_listView leadingAnchor] constraintEqualToAnchor:[self.view leadingAnchor] constant:0],
        [[_searchStateTitleLabel topAnchor] constraintEqualToAnchor:[_loader bottomAnchor] constant:0],
        [[_searchStateTitleLabel centerXAnchor] constraintEqualToAnchor:[self.view centerXAnchor]],
        [[_searchStateTitleLabel topAnchor] constraintEqualToAnchor:[_searchStateImageView bottomAnchor] constant:0],
        [[_loader centerXAnchor] constraintEqualToAnchor:[self.view centerXAnchor]],
        [[_loader centerYAnchor] constraintEqualToAnchor:[self.view centerYAnchor]],
        [[_searchStateImageView centerXAnchor] constraintEqualToAnchor:[self.view centerXAnchor]],
        [[_searchStateImageView centerYAnchor] constraintEqualToAnchor:[self.view centerYAnchor]]
    ]];
    
    [NSLayoutConstraint activateConstraints:@[
       [[_listView bottomAnchor] constraintEqualToAnchor:[self.view bottomAnchor] constant:-16]
    ]];
    [_listView reloadData];
    if (_searchBar.text) {
        [self fetchChoicesWithQueryString:_searchBar.text];
    } else {
        [self resetFilteredList];
    }
    
    [self setupNavigationItemView];
    
    ACRBaseCardElementRenderer *renderer = [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)choiceSet->GetElementType()]];
    if (renderer && [renderer respondsToSelector:@selector(configure:rootView:baseCardElement:hostConfig:)]) {
        [renderer configureUI:self rootView:_rootView baseCardElement:_inputElem hostConfig:nil];
    }
}

- (void)setupNavigationItemView {
    [self.navigationItem setTitle:@"typeahead search"];
    UIImage *image = [UIImage systemImageNamed:@"chevron.backward"];
    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithImage:image
                                                                   style:UIBarButtonItemStylePlain
                                                                  target:self
                                                                  action:@selector(navigateBack)];
    self.navigationItem.leftBarButtonItem = backButton;
    
    if(_searchBar.text !=nil && _searchBar.text.length)
    {
        UIImage *rightImage = [UIImage systemImageNamed:@"checkmark"];
        UIBarButtonItem *rightBarButton = [[UIBarButtonItem alloc] initWithImage:rightImage
                                                                           style:UIBarButtonItemStylePlain
                                                                          target:self
                                                                          action:@selector(checkmarkButtonClicked)];
        self.navigationItem.rightBarButtonItem = rightBarButton;
    }
}

- (void)navigateBack {
    [self dismiss];
}

- (void)checkmarkButtonClicked {
    [self dismiss];
    [_choiceSetDelegate updateSelectedChoiceInTextField:_searchBar.text];
}

-(void)dismiss {
    [self dismissViewControllerAnimated:NO completion:nil];
}

#pragma mark - UISearchBarDelegate  Methods

- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText
{
    if([searchBar.text length] == 0) {
        [self resetFilteredList];
    }
}

- (BOOL)searchBar:(UISearchBar *)searchBar shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text
{
    NSString *queryString = [_searchBar.text stringByReplacingCharactersInRange:range
                                                                     withString:text];
    [self fetchChoicesWithQueryString:queryString];
    [_listView reloadData];
    return YES;
}

-(void)fetchChoicesWithQueryString:(NSString *)queryString
{
    switch (_dataSourceType) {
        case staticDataSource:
            [_filteredDataSource updatefilteredListForStaticTypeahead:queryString];
            break;
        case dynamicDataSource:
            _searchStateTitleLabel.text = @"Loading options";
            _searchStateTitleLabel.hidden = NO;
            _searchStateImageView.hidden = YES;
            [_filteredDataSource clearList];
            if (![_loader isAnimating])
            {
                [_loader startAnimating];
            }
            [_dynamicChoicesService fetchChoicesFromDynamicSourceWithSearchQuery:queryString];
            break;
        default:
            break;
    }
}

-(void)resetFilteredList
{
    _searchBar.text = @"";
    if (@available(iOS 16.0, *)) {
        self.navigationItem.rightBarButtonItem.hidden = YES;
    } else {
        // Fallback on earlier versions
    }
    [_choiceSetDelegate updateSelectedChoiceInTextField:@""];
    [_filteredDataSource resetFilter];
    [self configureSearchStateUI:_filteredDataSource.count ? displayingResults : zeroState];
}

#pragma mark - ACOTypeaheadDynamicChoicesService Methods

- (void)updateSearchUIWithqueryString:(NSString*)queryString dynamicChoices:(NSDictionary *)choices withError:(NSError *)error {
    if (!error) {
        [_loader stopAnimating];
        [_filteredDataSource updatefilteredListForStaticAndDynamicTypeahead:queryString dynamicChoices:choices];
        [_validator updateDynamicTitleMap:choices];
        
        if (_filteredDataSource.count) {
            [self configureSearchStateUI:displayingResults];
        } else if(![queryString length]) {
            [self configureSearchStateUI:zeroState];
        } else {
            [self configureSearchStateUI:displayingInvalidSearchError];
        }
    }
    else {
        [self configureSearchStateUI:displayingGenericError];
    }
    self.navigationItem.rightBarButtonItem.hidden = YES;
    if ([_filteredDataSource findMatch:queryString])
    {
        self.navigationItem.rightBarButtonItem.hidden = NO;
    }
}

-(void)configureSearchStateUI:(TSTypeaehadSearchViewState)searchViewState
{
    _searchStateImageView.hidden = NO;
    _searchStateTitleLabel.hidden = NO;
    switch (searchViewState) {
        case zeroState:
            _searchStateTitleLabel.text = _searchStateParams.zeroStateParams.title;
            _searchStateImageView.image = [UIImage systemImageNamed:@"magnifyingglass"];
            break;
        case displayingResults:
            _searchStateTitleLabel.hidden = YES;
            _searchStateImageView.hidden = YES;
            break;
        case displayingGenericError:
            _searchStateImageView.image = [UIImage systemImageNamed:@"xmark.circle"];
            _searchStateTitleLabel.text = _searchStateParams.errorStateParams.title;
            break;
        case displayingInvalidSearchError:
            _searchStateTitleLabel.text = _searchStateParams.noResultStateParams.title;
            _searchStateImageView.image = [UIImage systemImageNamed:@"xmark.circle"];
            break;
        default:
            break;
    }
    [_listView reloadData];
}

#pragma mark - UITableViewDelegate Methods

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return _filteredDataSource.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"filterred-cell"];
    if (!cell) {
        cell = [[UITableViewCell alloc] init];
    }
    NSString *resultText = [_filteredDataSource getItemAt:indexPath.row];
    NSRange highlightedRanges = [_filteredDataSource getHighlightRangeForSearchText:_searchBar.text resultText:resultText];
    NSMutableAttributedString *attrString = [[NSMutableAttributedString alloc] initWithString:resultText];
    [attrString beginEditing];
    [attrString addAttributes:@{
        NSFontAttributeName: [UIFont boldSystemFontOfSize:cell.textLabel.font.pointSize]}
                              range:highlightedRanges];
    [attrString endEditing];
    cell.textLabel.attributedText = attrString;
    cell.textLabel.numberOfLines = _wrapLines;
    cell.accessibilityLabel = [NSString stringWithFormat:@"%@, %@", _inputLabel, cell.textLabel.text];
    cell.accessibilityValue = [NSString stringWithFormat:@"%ld of %ld", indexPath.row + 1, [self tableView:tableView numberOfRowsInSection:0]];
    cell.accessibilityIdentifier = [NSString stringWithFormat:@"%@, %@", self.id, cell.textLabel.text];
    cell.accessibilityTraits = UIAccessibilityTraitButton;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    _searchBar.text = [_filteredDataSource getItemAt:indexPath.row];
    [_choiceSetDelegate updateSelectedChoiceInTextField:[_filteredDataSource getItemAt:indexPath.row]];
    [self dismiss];
    [self resignFirstResponder];
}

@end

