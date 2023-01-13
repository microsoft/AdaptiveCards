//
//  ACRChoiceSetFullScreenView.mm
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 07/11/22.
//  Copyright © 2022 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACRChoiceSetTypeaheadSearchView.h"
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
#import "ACRSearchBar.h"
#import "HostConfig.h"
#import "UtiliOS.h"

@interface ACRChoiceSetTypeaheadSearchView() <UITableViewDelegate,UITableViewDataSource>
@end

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

@implementation ACRChoiceSetTypeaheadSearchView {
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
    ACRChoiceSetCompactStyleView *_delegate;
    ACRTypeaheadStateAllParameters *_searchStateParams;
    UITextField *_customSearchBar;
    UIView *_customSearchBarSeparator;
    UIActivityIndicatorView *_loader;
    UILabel *_searchStateTitleLabel;
    UIImageView *_searchStateImageView;
    UILabel *_searchStateSubtitleLabel;
}

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)acoConfig
                              delegate:(ACRChoiceSetCompactStyleView *)delegate
                     searchStateParams:(ACRTypeaheadStateAllParameters *)searchStateParams
{
    self = [super init];
    if (self) {
        std::shared_ptr<BaseCardElement> elem = [acoElem element];
        std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
        _rootView = rootView;
        _inputElem = acoElem;
        _delegate = delegate;
        _searchStateParams = searchStateParams;
        
        _filteredDataSource = [[ACOFilteredDataSource alloc] init];
        _validator = [[ACOChoiceSetCompactStyleValidator alloc] init:acoElem dataSource:_filteredDataSource];
        
        _rootView = rootView;
        _wrapLines = choiceSet->GetWrap() ? 0 : 1;

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
    [self setupNavigationItemView];
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
    _container.backgroundColor = UIColor.whiteColor;
    [mainview addSubview:_container];
    _customSearchBar = [self buildCustomSearchBarWithPlaceholder:@"Enter a search term"];
    self.searchBar = _customSearchBar;
    _customSearchBarSeparator = [[UIView alloc] init];
    self.searchBarSeparator = _customSearchBarSeparator;
    _listView = [[UITableView alloc] init];
    _listView.dataSource = self;
    _listView.delegate = self;
    _listView.accessibilityIdentifier = [NSString stringWithUTF8String:choiceSet->GetId().c_str()];
    self.filteredListView = _listView;
    [_container addArrangedSubview:_customSearchBar];
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
        [[_customSearchBar leadingAnchor] constraintEqualToAnchor:[self.view leadingAnchor] constant:16],
        [[_customSearchBar trailingAnchor] constraintEqualToAnchor:[self.view trailingAnchor] constant:-16],
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
    [self configureSearchStateUI:_filteredDataSource.count ? displayingResults : zeroState];
    
    ACRBaseCardElementRenderer *renderer = [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)choiceSet->GetElementType()]];
    if (renderer && [renderer respondsToSelector:@selector(configure:rootView:baseCardElement:hostConfig:)]) {
        [renderer configureUI:self rootView:_rootView baseCardElement:_inputElem hostConfig:nil];
    }
}

- (void)setupNavigationItemView {
    [self.navigationItem setTitle:@"typeahead search"];
    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Back"
                                     style:UIBarButtonItemStylePlain
                                    target:self
                                    action:@selector(backButtonClicked)];
    self.navigationItem.leftBarButtonItem = backButton;
}

- (void)backButtonClicked {
    [self dismiss];
}

-(void)dismiss {
    [self dismissViewControllerAnimated:NO completion:nil];
}

-(void)configureSearchStateUI:(TSTypeaehadSearchViewState)searchViewState
{
    switch (searchViewState) {
        case zeroState:
            _searchStateTitleLabel.hidden = NO;
            _searchStateTitleLabel.text = _searchStateParams.zeroStateParams.title;
            _searchStateImageView.image = [UIImage systemImageNamed:@"magnifyingglass"];
            _searchStateImageView.hidden = NO;
            break;
        case displayingResults:
            _searchStateTitleLabel.hidden = YES;
            _searchStateImageView.hidden = YES;
            _searchStateTitleLabel.hidden = YES;
            _searchStateImageView.hidden = YES;
            break;
        case displayingGenericError:
            _searchStateTitleLabel.hidden = NO;
            _searchStateImageView.image = [UIImage systemImageNamed:@"xmark.circle"];
            _searchStateTitleLabel.text = _searchStateParams.errorStateParams.title;
            _searchStateImageView.hidden = NO;
            break;
        case displayingInvalidSearchError:
            _searchStateTitleLabel.hidden = NO;
            _searchStateTitleLabel.text = _searchStateParams.noResultStateParams.title;
            _searchStateImageView.image = [UIImage systemImageNamed:@"xmark.circle"];
            _searchStateImageView.hidden = NO;
            break;
        default:
            break;
    }
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
    cell.textLabel.text = [_filteredDataSource getItemAt:indexPath.row];
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
    _customSearchBar.text = [_filteredDataSource getItemAt:indexPath.row];
    [_delegate updateSelectedChoiceInTextField:[_filteredDataSource getItemAt:indexPath.row]];
    [self dismiss];
    [self resignFirstResponder];
}

- (void) updateListViewLayout {
    [_listView reloadData];
}

@end

