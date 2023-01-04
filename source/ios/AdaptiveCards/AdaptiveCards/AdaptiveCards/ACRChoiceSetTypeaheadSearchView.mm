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
#import "HostConfig.h"
#import "UtiliOS.h"
#import "ACODebouncer.h"

@interface ACRChoiceSetTypeaheadSearchView() <UITextFieldDelegate,ACODebouncerDelegate,UITableViewDelegate,UITableViewDataSource>
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
    ACODebouncer *_debouncer;
    NSInteger _wrapLines;
    TSChoicesDataSource _dataSourceType;
    TSTypeaehadSearchViewState _searchViewState;
    ACOChoiceSetCompactStyleValidator *_validator;
    UIStackView *_container;
    ACRChoiceSetCompactStyleView *_delegate;
    UITextField *_customSearchBar;
    UIActivityIndicatorView *_loader;
    UILabel *_searchStateTitleLabel;
    UIImageView *_searchStateImageView;
    UILabel *_searchStateSubtitleLabel;
}

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)acoConfig
                              delegate:(ACRChoiceSetCompactStyleView *)delegate
{
    self = [super init];
    if (self) {
        std::shared_ptr<BaseCardElement> elem = [acoElem element];
        std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
        _rootView = rootView;
        _inputElem = acoElem;
        _delegate = delegate;
        // configure helper objects
        
        _filteredDataSource = [[ACOFilteredDataSource alloc] init];
        _validator = [[ACOChoiceSetCompactStyleValidator alloc] init:acoElem dataSource:_filteredDataSource];
        
        // configure debouncer
        _global_queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        _debouncer = [[ACODebouncer alloc] initWithDelay:0.2];
        _debouncer.delegate = self;

        // configure UI
        _listView = [[UITableView alloc] init];
        _listView.dataSource = self;
        _listView.delegate = self;
        _listView.accessibilityIdentifier = [NSString stringWithUTF8String:choiceSet->GetId().c_str()];
        [_listView setSeparatorStyle:UITableViewCellSeparatorStyleNone];
        _listView.rowHeight = UITableViewAutomaticDimension;
        [_listView registerClass:UITableViewCell.self forCellReuseIdentifier:@"SauceCell"];
        self.filteredListView = _listView;

        ACRBaseCardElementRenderer *renderer = [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)choiceSet->GetElementType()]];
        if (renderer && [renderer respondsToSelector:@selector(configure:rootView:baseCardElement:hostConfig:)]) {
            // configure input UI
            [renderer configure:_container rootView:rootView baseCardElement:acoElem hostConfig:acoConfig];
        }
        
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
    self.view.backgroundColor = UIColor.whiteColor;
    [self setupNavigationItemView];
    UIView *mainview = [[UIView alloc] initWithFrame:CGRectZero];
    [self.view addSubview:mainview];
    [mainview setFrame:self.view.bounds];
    [mainview setAutoresizingMask:UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight];
    
    _container = [[UIStackView alloc] initWithFrame:CGRectZero];
    _container.axis = UILayoutConstraintAxisVertical;
    _container.layoutMargins = UIEdgeInsetsMake(12, 0, 16, 16);
    _container.layoutMarginsRelativeArrangement = YES;
    _container.spacing = 14;
    _container.backgroundColor = UIColor.whiteColor;
    mainview.backgroundColor = UIColor.whiteColor;
    [mainview addSubview:_container];
    _container.translatesAutoresizingMaskIntoConstraints = NO;
    
    UIView *searchBarSeparator = [[UIView alloc] init];
    searchBarSeparator.layer.backgroundColor = [[UIColor colorWithRed:0.784 green:0.784 blue:0.784 alpha:1] CGColor];
    [searchBarSeparator.heightAnchor constraintEqualToConstant:0.5].active = YES;
    
    _customSearchBar = [self buildCustomSearchBarWithPlaceholder:@"Enter a search term"];;
    [_customSearchBar.heightAnchor constraintEqualToConstant:36].active = YES;
    _customSearchBar.textColor = [UIColor colorWithRed:0.431 green:0.431 blue:0.431 alpha:1];
    _customSearchBar.backgroundColor = [UIColor colorWithRed:0.945 green:0.945 blue:0.945 alpha:1];
    
    UIImageView *searchIconView = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"magnifyingglass"]];
    searchIconView.frame = CGRectMake(5, 5, 26, 26);
    searchIconView.contentMode = UIViewContentModeCenter;
    UIView *searchLeftView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 32, 32)];
    [searchLeftView addSubview:searchIconView];
    
    UIImageView *clearIconView = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"xmark.circle"]];
    clearIconView.frame = CGRectMake(0, 5, 26, 26);
    clearIconView.contentMode = UIViewContentModeCenter;
    UITapGestureRecognizer *singleTap = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(clearButtonTapped)];
    singleTap.numberOfTapsRequired = 1;
    [clearIconView setUserInteractionEnabled:YES];
    [clearIconView addGestureRecognizer:singleTap];
    
    UIView *rightView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 32, 32)];
    [rightView addSubview:clearIconView];
    
    _customSearchBar.rightViewMode = UITextFieldViewModeAlways;
    _customSearchBar.rightView = rightView;
    _customSearchBar.leftViewMode = UITextFieldViewModeAlways;
    _customSearchBar.leftView = searchLeftView;
    
    [_container addArrangedSubview:_customSearchBar];
    
    [_container addArrangedSubview:searchBarSeparator];
    [_container addArrangedSubview:_listView];
    
    _loader = [[UIActivityIndicatorView alloc] initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleMedium];
    _loader.hidesWhenStopped = YES;
    _loader.hidden = YES;
    _loader.translatesAutoresizingMaskIntoConstraints = NO;
    [_loader.heightAnchor constraintEqualToConstant:32].active = YES;
    [_loader.widthAnchor constraintEqualToConstant:32].active = YES;
    
    _searchStateTitleLabel = [[UILabel alloc] init];
    _searchStateTitleLabel.backgroundColor = [UIColor whiteColor];
    _searchStateTitleLabel.textColor = [UIColor colorWithRed:0.443 green:0.443 blue:0.443 alpha:1];
    _searchStateTitleLabel.alpha = 0.9;
    _searchStateTitleLabel.textAlignment = NSTextAlignmentCenter;
    _searchStateTitleLabel.text = @"Search options";
    _searchStateTitleLabel.font = [UIFont fontWithName:@"SegoeUI-Regular" size:16];
    [_searchStateTitleLabel.heightAnchor constraintEqualToConstant:20].active = YES;
    _searchStateTitleLabel.translatesAutoresizingMaskIntoConstraints = NO;
    _searchStateTitleLabel.hidden = NO;
    
    _searchStateImageView = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"magnifyingglass"]];
    _searchStateImageView.frame = CGRectMake(self.view.frame.size.width / 2 - 24, self.view.frame.size.height / 2 - 24, 48, 48);
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
        [[searchBarSeparator leadingAnchor] constraintEqualToAnchor:[self.view leadingAnchor] constant:0],
        [[searchBarSeparator trailingAnchor] constraintEqualToAnchor:[self.view trailingAnchor] constant:0],
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
    [_customSearchBar becomeFirstResponder];
}

-(UITextField *)buildCustomSearchBarWithPlaceholder:(NSString *)placeholder {
    
    UITextField *searchTextField = [[UITextField alloc] initWithFrame:CGRectZero];
    searchTextField.delegate = self;
    searchTextField.accessibilityTraits = UIAccessibilityTraitSearchField;
    searchTextField.enablesReturnKeyAutomatically = YES;
    searchTextField.returnKeyType = UIReturnKeySearch;
    [searchTextField addTarget:self action:@selector(textFieldDidChange:) forControlEvents:UIControlEventEditingChanged];
    searchTextField.translatesAutoresizingMaskIntoConstraints = NO;
    searchTextField.layer.cornerRadius = 10;
    searchTextField.text = [_delegate getSelectedText];
    if (placeholder!= nil)
    {
        searchTextField.placeholder = placeholder;
    }
    searchTextField.borderStyle = UITextBorderStyleRoundedRect;
    searchTextField.backgroundColor = UIColor.systemGroupedBackgroundColor;
    return searchTextField;
}

-(void)textFieldDidChange:(UITextField*)textField
{
    NSLog(@"new search text %@", textField.text);
}

-(void)clearButtonTapped
{
    _customSearchBar.text = @"";
    [_customSearchBar resignFirstResponder];
    [_filteredDataSource resetFilter];
    [self updateListViewLayout];
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string {
    NSString *newSearchText = [textField.text stringByReplacingCharactersInRange:range
                                                                  withString:string];
    switch (_dataSourceType) {
        case staticDataSource:
            if ([newSearchText length]) {
                [_filteredDataSource updatefilteredListForStaticTypeahead:newSearchText];
            } else {
                [_filteredDataSource resetFilter];
            }
            [self updateListViewLayout];
            break;
        case dynamicDataSource:
            _searchStateTitleLabel.text = @"Loading options";
            _searchStateTitleLabel.hidden = NO;
            _searchStateImageView.hidden = YES;
            if (![_loader isAnimating])
            {
                [_loader startAnimating];
            }
            [_debouncer postInput:newSearchText];
            break;
        default:
            break;
    }
    return YES;
}

- (void)dealloc
{
    _debouncer.delegate = nil;
}

- (void)setupNavigationItemView {
    [self.navigationItem setTitle:@"typeahead search"];
    UIBarButtonItem *backButton = [[UIBarButtonItem alloc] initWithTitle:@"Back"
                                     style:UIBarButtonItemStylePlain
                                    target:self
                                    action:@selector(backButtonClicked)];
    self.navigationItem.leftBarButtonItem = backButton;
}

- (IBAction)backButtonClicked {
    [self dismiss];
}

-(void)dismiss {
    [self dismissViewControllerAnimated:NO completion:nil];
}

#pragma mark - TSDebouncerDelegate Methods specifically for dynamic typeahead
- (void)debouncerDidSendOutput:(id)output
{
    if ([output isKindOfClass:NSString.class])
    {
        dispatch_async(_global_queue, ^{
            __weak typeof(self) weakSelf = self;
            if ([self->_rootView.acrActionDelegate
                 respondsToSelector:@selector(onChoiceSetQueryChange:acoElem:completion:)]) {
                [self->_rootView.acrActionDelegate onChoiceSetQueryChange:output acoElem:self->_inputElem completion:^(NSArray<NSString *> * _choices, NSError *error) {
                    __strong typeof(self) strongSelf = weakSelf;
                    if (!error) {
                        dispatch_async(dispatch_get_main_queue(), ^{
                            [strongSelf->_loader stopAnimating];
                            if (![output length]) {
                                strongSelf->_searchStateTitleLabel.hidden = NO;
                                strongSelf->_searchStateTitleLabel.text = @"Search option";
                                strongSelf->_searchStateImageView.hidden = NO;
                                [strongSelf->_filteredDataSource resetFilter];
                            }
                            else if ([_choices count]) {
                                strongSelf->_searchStateTitleLabel.hidden = YES;
                                strongSelf->_searchStateImageView.hidden = YES;
                                [strongSelf->_filteredDataSource updatefilteredListForDynamicTypeahead:_choices];
                            } else {
                                strongSelf->_searchStateTitleLabel.hidden = NO;
                                strongSelf->_searchStateTitleLabel.text = @"No results found";
                                strongSelf->_searchStateImageView.image = [UIImage systemImageNamed:@"xmark.circle"];
                                strongSelf->_searchStateImageView.hidden = NO;
                                [strongSelf->_filteredDataSource resetFilter];
                            }
                            [strongSelf updateListViewLayout];
                        });
                    }
                    else
                    {
                        strongSelf->_searchStateTitleLabel.text = @"Something went wrong";
                    }
                }];
            }
        });
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

