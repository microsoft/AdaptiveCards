//
//  ACRTypeaheadSearchViewController.mm
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 26/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACRTypeaheadSearchViewController.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOBundle.h"
#import "ACOHostConfigPrivate.h"
#import "ACOTypeaheadDynamicChoicesService.h"
#import "ACRActionDelegate.h"
#import "ACRBaseCardElementRenderer.h"
#import "ACRChoiceSetCompactStyleView.h"
#import "ACRChoiceSetFilteredStyleView.h"
#import "ACRInputLabelView.h"
#import "ACRView.h"
#import "ChoiceInput.h"
#import "ChoiceSetInput.h"
#import "ChoicesData.h"
#import "HostConfig.h"
#import "UtiliOS.h"
#import <UIKit/UIKit.h>

typedef enum {
    none = 0,
    staticDataSource,
    dynamicDataSource,
} TSChoicesDataSource;

typedef enum {
    error = 0,
    networkError,
    success
} ACODynamicTypeaheadResponseType;

static CGFloat const ACOSearchImageViewHeight = 48.0f;
static CGFloat const ACOSearchImageViewWidth = 48.0f;
static CGFloat const ACOSearchBarPadding = 8.0f;
static CGFloat const ACOListViewBottomPadding = 32.0f;
static CGFloat const ACOStackViewSpacing = 14.0f;

@implementation ACRTypeaheadSearchViewController {
    ACOFilteredDataSource *_filteredDataSource;
    ACOChoiceSetFilteredStyleValidator *_validator;
    ACOBaseCardElement *_inputElem;
    __weak ACRView *_rootView;
    NSInteger _wrapLines;
    TSChoicesDataSource _dataSourceType;
    TSTypeaehadSearchViewState _searchViewState;
    id<ACRChoiceSetFilteredDelegate> _choiceSetDelegate;
    ACRTypeaheadStateAllParameters *_searchStateParams;
    UIStackView *_container;
    UISearchBar *_searchBar;
    UIView *_searchBarSeparator;
    UIActivityIndicatorView *_loader;
    UILabel *_searchStateTitleLabel;
    UIImageView *_searchStateImageView;
    UITableView *_listView;
    ACOTypeaheadDynamicChoicesService *_dynamicChoicesService;
    NSString *_typeaheadViewTitle;
}

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)hostConfig
                    filteredDataSource:(ACOFilteredDataSource *)filteredDataSource
                filteredStyleValidator:(ACOChoiceSetFilteredStyleValidator *)validator
                    typeaheadViewTitle:(NSString *)typeaheadViewTitle
                     choiceSetDelegate:(id<ACRChoiceSetFilteredDelegate>)choiceSetDelegate
                     searchStateParams:(ACRTypeaheadStateAllParameters *)searchStateParams
{
    self = [super init];
    if (self) {
        std::shared_ptr<BaseCardElement> elem = [acoElem element];
        std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
        _rootView = rootView;
        _inputElem = acoElem;
        _typeaheadViewTitle = typeaheadViewTitle;
        _choiceSetDelegate = choiceSetDelegate;
        _searchStateParams = searchStateParams;
        _filteredDataSource = filteredDataSource;
        _validator = validator;
        _wrapLines = choiceSet->GetWrap() ? 0 : 1;
        _dynamicChoicesService = [[ACOTypeaheadDynamicChoicesService alloc] initWithRootView:_rootView inputElem:_inputElem typeaheadSearchDelegate:self];
        std::shared_ptr<ChoicesData> choicesData = choiceSet->GetChoicesData();
        _dataSourceType = none;
        if (choicesData->GetChoicesDataType().compare((AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::DataQuery))) == 0) {
            _dataSourceType = dynamicDataSource;
        } else if (choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Filtered) {
            _dataSourceType = staticDataSource;
        }
    }

    return self;
}

- (void)viewDidLoad
{
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
    _container.spacing = ACOStackViewSpacing;
    self.stackViewContainer = _container;
    _container.backgroundColor = UIColor.whiteColor;
    [mainview addSubview:_container];
    _searchBar = [UISearchBar new];
    [_searchBar sizeToFit];
    _searchBar.delegate = self;
    [_searchBar becomeFirstResponder];
    _searchBar.text = [_choiceSetDelegate getSelectedText];
    _searchBar.placeholder = _validator.placeHolder ?: @"Enter a search term";
    _searchBar.accessibilityIdentifier = [NSString stringWithFormat:@"%@, %@", @"searchBar", [_choiceSetDelegate getChoiceSetId]];
    self.searchBar = _searchBar;

    _searchBarSeparator = [[UIView alloc] init];
    self.searchBarSeparator = _searchBarSeparator;
    _listView = [[UITableView alloc] init];
    _listView.dataSource = self;
    _listView.delegate = self;
    _listView.accessibilityIdentifier = [NSString stringWithFormat:@"%@, %@", @"listView", [_choiceSetDelegate getChoiceSetId]];
    _listView.keyboardDismissMode = UIScrollViewKeyboardDismissModeOnDrag;
    self.filteredListView = _listView;
    [_container addArrangedSubview:_searchBar];
    [_container addArrangedSubview:_searchBarSeparator];
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
    _searchStateImageView.frame = CGRectMake((self.view.frame.size.width - ACOSearchImageViewWidth) / 2, (self.view.frame.size.height - ACOSearchImageViewHeight) / 2, ACOSearchImageViewWidth, ACOSearchImageViewHeight);
    self.searchStateImageView = _searchStateImageView;
    [self.view addSubview:_loader];
    [self.view addSubview:_searchStateImageView];
    [self.view addSubview:_searchStateTitleLabel];

    [NSLayoutConstraint activateConstraints:@[
        [[_container trailingAnchor] constraintEqualToAnchor:[self.view trailingAnchor]],
        [[_container leadingAnchor] constraintEqualToAnchor:[self.view leadingAnchor]],
        [[_container widthAnchor] constraintEqualToAnchor:[self.view widthAnchor]],
        [[_container topAnchor] constraintEqualToAnchor:[self.view topAnchor]],
        [[_searchBar leadingAnchor] constraintEqualToAnchor:[self.view leadingAnchor]
                                                   constant:ACOSearchBarPadding],
        [[_searchBar trailingAnchor] constraintEqualToAnchor:[self.view trailingAnchor]
                                                    constant:-ACOSearchBarPadding],
        [[_searchBarSeparator leadingAnchor] constraintEqualToAnchor:[self.view leadingAnchor]
                                                            constant:0],
        [[_searchBarSeparator trailingAnchor] constraintEqualToAnchor:[self.view trailingAnchor]],
        [[_listView leadingAnchor] constraintEqualToAnchor:[self.view leadingAnchor]],
        [[_searchStateTitleLabel topAnchor] constraintEqualToAnchor:[_loader bottomAnchor]
                                                           constant:0],
        [[_searchStateTitleLabel centerXAnchor] constraintEqualToAnchor:[self.view centerXAnchor]],
        [[_searchStateTitleLabel topAnchor] constraintEqualToAnchor:[_searchStateImageView bottomAnchor]],
        [[_loader centerXAnchor] constraintEqualToAnchor:[self.view centerXAnchor]],
        [[_loader centerYAnchor] constraintEqualToAnchor:[self.view centerYAnchor]],
        [[_searchStateImageView centerXAnchor] constraintEqualToAnchor:[self.view centerXAnchor]],
        [[_searchStateImageView centerYAnchor] constraintEqualToAnchor:[self.view centerYAnchor]],
        [[_listView bottomAnchor] constraintEqualToAnchor:[self.view bottomAnchor]
                                                 constant:-ACOListViewBottomPadding]
    ]];

    [_listView reloadData];
    if (_searchBar.text) {
        [self fetchChoicesWithQueryString:_searchBar.text];
    } else {
        [self resetFilteredList];
    }

    [self setupNavigationItemView];
    ACRBaseCardElementRenderer *renderer = [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)choiceSet->GetElementType()]];
    if (renderer && [renderer respondsToSelector:@selector(configureVC:rootView:baseCardElement:hostConfig:)]) {
        [renderer configureVC:self rootView:_rootView baseCardElement:_inputElem hostConfig:nil];
    }
}

- (void)setupNavigationItemView
{
    BOOL shouldConfigure = YES;
    if ([_rootView.acrActionDelegate respondsToSelector:@selector(shouldConfigureNavigationItemViewWithVC:)]) {
        shouldConfigure = [_rootView.acrActionDelegate shouldConfigureNavigationItemViewWithVC:self];
    }

    if (!shouldConfigure) {
        return;
    }

    [self.navigationItem setTitle:_typeaheadViewTitle];
    UIImage *image = [UIImage systemImageNamed:@"chevron.backward"];
    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithImage:image
                                                                   style:UIBarButtonItemStylePlain
                                                                  target:self
                                                                  action:@selector(navigateBack)];
    self.navigationItem.leftBarButtonItem = backButton;

    if (_searchBar.text != nil && _searchBar.text.length) {
        UIImage *rightImage = [UIImage systemImageNamed:@"checkmark"];
        UIBarButtonItem *rightBarButton = [[UIBarButtonItem alloc] initWithImage:rightImage
                                                                           style:UIBarButtonItemStylePlain
                                                                          target:self
                                                                          action:@selector(checkmarkButtonClicked)];
        self.navigationItem.rightBarButtonItem = rightBarButton;
    }
}

- (void)navigateBack
{
    [self dismiss];
}

- (void)checkmarkButtonClicked
{
    [self dismiss];
    [_choiceSetDelegate updateSelectedChoiceInTextField:_searchBar.text];
}

- (void)dismiss
{
    [self dismissViewControllerAnimated:NO completion:nil];
}

#pragma mark - UISearchBarDelegate  Methods

- (void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText
{
    if ([searchBar.text length] == 0) {
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


- (void)fetchChoicesWithQueryString:(NSString *)queryString
{
    switch (_dataSourceType) {
        case staticDataSource:
            [_filteredDataSource updateFilteredListForStaticTypeahead:queryString];
            break;
        case dynamicDataSource:
            _searchStateTitleLabel.text = @"Loading options";
            _searchStateTitleLabel.hidden = NO;
            _searchStateImageView.hidden = YES;
            _filteredListView.hidden = YES;
            if (![_loader isAnimating]) {
                [_loader startAnimating];
            }
            [_dynamicChoicesService fetchChoicesFromDynamicSourceWithSearchQuery:queryString];
            break;
        default:
            break;
    }
}

- (void)resetFilteredList
{
    _searchBar.text = @"";
    if (@available(iOS 16.0, *)) {
        self.navigationItem.rightBarButtonItem.hidden = YES;
    }
    [_choiceSetDelegate updateSelectedChoiceInTextField:@""];
    [_filteredDataSource resetFilter];
    [self configureSearchStateUI:_filteredDataSource.count ? displayingResults : zeroState];
}

#pragma mark - ACOTypeaheadDynamicChoicesService Methods

- (void)updateTypeaheadUIWithSearchText:(NSString *)searchText dynamicChoices:(NSDictionary *)choices withError:(NSError *)error
{
    __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_get_main_queue(), ^{
        __strong typeof(self) strongSelf = weakSelf;
        if (!error) {
            [strongSelf->_loader stopAnimating];
            [strongSelf->_filteredDataSource updateFilteredListForStaticAndDynamicTypeahead:searchText dynamicChoices:choices];
            [strongSelf->_validator updateDynamicTitleMap:choices];
            if (strongSelf->_filteredDataSource.count) {
                [strongSelf configureSearchStateUI:displayingResults];
            } else if (![searchText length]) {
                [strongSelf configureSearchStateUI:zeroState];
            } else {
                [strongSelf configureSearchStateUI:displayingInvalidSearchError];
            }
        } else {
            [strongSelf configureSearchStateUI:displayingGenericError];
        }

        if (@available(iOS 16.0, *)) {
            strongSelf.navigationItem.rightBarButtonItem.hidden = YES;
            if ([strongSelf->_filteredDataSource findMatch:searchText]) {
                strongSelf.navigationItem.rightBarButtonItem.hidden = NO;
            }
        }
    });
}

- (void)configureSearchStateUI:(TSTypeaehadSearchViewState)searchViewState
{
    _searchStateImageView.hidden = NO;
    _searchStateTitleLabel.hidden = NO;
    _filteredListView.hidden = YES;
    switch (searchViewState) {
        case zeroState:
            _searchStateTitleLabel.text = _searchStateParams.zeroStateParams.title;
            break;
        case displayingResults:
            _searchStateTitleLabel.hidden = YES;
            _searchStateImageView.hidden = YES;
            _filteredListView.hidden = NO;
            break;
        case displayingGenericError:
            _searchStateTitleLabel.text = _searchStateParams.errorStateParams.title;
            break;
        case displayingInvalidSearchError:
            _searchStateTitleLabel.text = _searchStateParams.noResultStateParams.title;
            break;
        default:
            break;
    }
    [_listView reloadData];
    if ([_rootView.acrActionDelegate respondsToSelector:@selector(didUpdateTypeaheadSearchViewController:searchStateImageView:searchViewState:)]) {
        [_rootView.acrActionDelegate didUpdateTypeaheadSearchViewController:self searchStateImageView:_searchStateImageView searchViewState:searchViewState];
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
    NSString *resultText = [_filteredDataSource getItemAt:indexPath.row];
    NSRange highlightedRanges = [_filteredDataSource getHighlightRangeForSearchText:_searchBar.text resultText:resultText];
    NSMutableAttributedString *attrString = [[NSMutableAttributedString alloc] initWithString:resultText];
    [attrString beginEditing];
    [attrString addAttributes:@{
        NSFontAttributeName : [UIFont boldSystemFontOfSize:cell.textLabel.font.pointSize]
    }
                        range:highlightedRanges];
    [attrString endEditing];
    cell.textLabel.attributedText = attrString;
    cell.textLabel.numberOfLines = _wrapLines;
    cell.accessibilityLabel = [NSString stringWithFormat:@"%@, %@", _typeaheadViewTitle, cell.textLabel.text];
    cell.accessibilityValue = [NSString stringWithFormat:@"%ld of %ld", indexPath.row + 1, [self tableView:tableView numberOfRowsInSection:0]];
    cell.accessibilityIdentifier = [NSString stringWithFormat:@"%@, %@", [_choiceSetDelegate getChoiceSetId], cell.textLabel.text];
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
