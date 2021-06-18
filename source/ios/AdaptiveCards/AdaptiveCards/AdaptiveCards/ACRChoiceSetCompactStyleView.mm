//
//  ACRChoiceSetCompactStyleTextFiled
//  ACRChoiceSetCompactStyleTextFiled.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRChoiceSetCompactStyleView.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOBundle.h"
#import "ACRActionDelegate.h"
#import "ACRBaseCardElementRenderer.h"
#import "ACRInputLabelView.h"
#import "UtiliOS.h"

using namespace AdaptiveCards;

@implementation ACRChoiceSetCompactStyleView {
    NSString *_defaultString;
    NSString *_inputLabel;
    NSArray<NSString *> *_titles;
    NSArray<NSString *> *_filteredList;
    UITableView *_listView;
    UIView *_view;
    UIButton *_button;
    BOOL _isValid;
    BOOL _filteringEnabled;
    BOOL _isListViewVisible;
    NSMutableDictionary<NSString *, NSString *> *_titlesMap;
    std::shared_ptr<ChoiceSetInput> _choiceSetInput;
    __weak UIViewController *_viewController;
    CGFloat _keyboardHeight;
}

- (instancetype)initWithInputChoiceSet:(ACOBaseCardElement *)acoElem
                              rootView:(ACRView *)rootView
                            hostConfig:(ACOHostConfig *)acoConfig
{
    self = [super init];
    if (self) {
        std::shared_ptr<BaseCardElement> elem = [acoElem element];
        std::shared_ptr<ChoiceSetInput> choiceSet = std::dynamic_pointer_cast<ChoiceSetInput>(elem);
        self.id = [NSString stringWithCString:choiceSet->GetId().c_str()
                                     encoding:NSUTF8StringEncoding];
        self.isRequired = choiceSet->GetIsRequired();
        self.allowsEditingTextAttributes = NO;
        _filteringEnabled = choiceSet->GetChoiceSetStyle() == ChoiceSetStyle::Filtered;
        if (!_filteringEnabled) {
            self.accessibilityTraits |= (UIAccessibilityTraitButton | UIAccessibilityTraitStaticText);
        }

        self.delegate = self;
        _rootView = rootView;
        _choiceSetInput = choiceSet;
        _defaultString = [NSString stringWithCString:choiceSet->GetPlaceholder().c_str() encoding:NSUTF8StringEncoding];
        self.placeholder = _defaultString;

        _listView = [[UITableView alloc] init];
        _listView.dataSource = self;
        _listView.delegate = self;
        self.filteredListView = _listView;

        _view = [[UIView alloc] init];
        [_view addSubview:_listView];

        _button = [UIButton buttonWithType:UIButtonTypeCustom];
        self.showFilteredListControl = _button;
        [_button addTarget:self action:@selector(toggleListView:) forControlEvents:UIControlEventTouchUpInside];
        self.rightView = _button;
        self.rightViewMode = _filteringEnabled ? UITextFieldViewModeUnlessEditing : UITextFieldViewModeAlways;

        ACRBaseCardElementRenderer *renderer = [[ACRRegistration getInstance] getRenderer:[NSNumber numberWithInt:(int)choiceSet->GetElementType()]];
        if (renderer && [renderer respondsToSelector:@selector(configure:rootView:baseCardElement:hostConfig:)]) {
            // configure input UI
            [renderer configure:self rootView:rootView baseCardElement:acoElem hostConfig:acoConfig];
        }

        _viewController = traverseResponderChainForUIViewController(_rootView);

        _isValid = YES;
        _titlesMap = [[NSMutableDictionary alloc] init];
        NSMutableArray *mutableArrayStrings = [[NSMutableArray alloc] init];
        NSInteger index = 0;
        auto inputLabel = _choiceSetInput->GetLabel();
        if (!inputLabel.empty()) {
            _inputLabel = [NSString stringWithCString:inputLabel.c_str() encoding:NSUTF8StringEncoding];
        }

        NSString *defaultValue = [NSString stringWithCString:_choiceSetInput->GetValue().c_str()
                                                    encoding:NSUTF8StringEncoding];
        BOOL shouldFilterList = NO;
        for (auto choice : _choiceSetInput->GetChoices()) {
            NSString *title = [NSString stringWithCString:choice->GetTitle().c_str() encoding:NSUTF8StringEncoding];
            NSString *value = [NSString stringWithCString:choice->GetValue().c_str() encoding:NSUTF8StringEncoding];
            _titlesMap[title] = value;
            if ([value isEqualToString:defaultValue]) {
                self.text = title;
                shouldFilterList = YES;
            }
            [mutableArrayStrings addObject:title];
            ++index;
        }

        if ([mutableArrayStrings count]) {
            _titles = [NSArray arrayWithArray:mutableArrayStrings];
            if (shouldFilterList) {
                [self filterList:self.text];
            } else {
                _filteredList = _titles;
            }
        }

        self.hasValidationProperties = self.isRequired;
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(handleKeyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(handleKeyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    }

    return self;
}

/// configures position of showFilteredListControl
- (CGRect)rightViewRectForBounds:(CGRect)bounds
{
    CGRect newBounds = [super rightViewRectForBounds:bounds];
    newBounds.origin.x = newBounds.origin.x - self.layoutMargins.right;
    return newBounds;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    if (!_filteringEnabled) {
        // don't show keyboard if filtering is not enabled
        [self endEditing:YES];
        // if showFilteredListControl is not in the selected state,
        // show the filtered list
        if (!_isListViewVisible) {
            [self showListView];
            // announce layout change, and move the VO focus to the filtered list
            UIAccessibilityPostNotification(UIAccessibilityLayoutChangedNotification, _listView);
        } else {
            [self hideListView];
            // announce layout change, and move the VO focus to the filtered list
            UIAccessibilityPostNotification(UIAccessibilityLayoutChangedNotification, self);
        }

        if (!_button.isSelected) {
            _button.selected = YES;
        } else {
            _button.selected = NO;
        }
    }
}

/// mainly used in checking the user input
- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string
{
    if (!_filteringEnabled) {
        // we don't want to editing the title of choices
        return NO;
    }

    // find the newly edited string
    NSString *newString = [textField.text stringByReplacingCharactersInRange:range
                                                                  withString:string];
    // implemented fluentUI north star behavior of removing the
    // filtered list when input field is empty
    if ([newString length]) {
        [self filterList:newString];
        if (!_isListViewVisible) {
            [self showListView];
        } else {
            [_listView reloadData];
        }
        // button state has to be checked
        // button state is not binary values that toggles
        if (!_button.isSelected) {
            _button.selected = YES;
        }
    } else {
        [self resetFilteredList];
        if (_isListViewVisible) {
            [self hideListView];
        }
        if (_button.isSelected) {
            _button.selected = NO;
        }
    }

    return YES;
}

- (void)resetFilteredList
{
    _filteredList = _titles;
    [_listView reloadData];
}

/// handles `return` key
- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if (_button.isSelected) {
        _button.selected = NO;
    }
    // ask UIKit to dimiss the keyboard
    [self resignFirstResponder];
    return YES;
}

- (void)filterList:(NSString *)text
{
    NSString *filter = @"SELF CONTAINS[c] %@";
    NSPredicate *predicate = [NSPredicate predicateWithFormat:filter, text.lowercaseString];
    _filteredList = [_titles filteredArrayUsingPredicate:predicate];
}

- (void)toggleListView:(UIButton *)button
{
    if (!button.isSelected) {
        [self showListView];
    } else {
        [self hideListView];
    }
    button.selected = !button.selected;
}

- (void)showListView
{
    _isListViewVisible = YES;
    if (_filteringEnabled) {
        // overlay keyboard
        [self becomeFirstResponder];
    }
    [self.window addSubview:_view];
    [self setNeedsLayout];
    [self layoutIfNeeded];
    [_listView reloadData];
    if (!_filteringEnabled) {
        // _litView is first responder if keyboard is not shown
        [_listView becomeFirstResponder];
    }
}

- (BOOL)resignFirstResponder
{
    if (_isListViewVisible) {
        [self hideListView];
    }
    if (_button.isSelected) {
        _button.selected = NO;
    }
    return [super resignFirstResponder];
}

- (void)hideListView
{
    [_view removeFromSuperview];
    _isListViewVisible = NO;
}

- (void)layoutSubviews
{
    [super layoutSubviews];
    [self layoutFilterredView];
}

// layout the filtered view
- (void)layoutFilterredView
{
    CGPoint position = [self.superview convertPoint:self.frame.origin toView:nil];
    CGSize windowSize;
    CGFloat statusBarHeight = 0.0f;
    if (self.window) {
        windowSize = self.window.bounds.size;
        if (@available(iOS 11.0, *)) {
            statusBarHeight = self.window.safeAreaInsets.top;
        } else {
            statusBarHeight = self.window.layoutMargins.top;
        }
    } else {
        windowSize = UIScreen.mainScreen.bounds.size;
    }
    CGRect frame = _viewController.view.frame;
    if (frame.size.width == 0 || frame.size.height == 0) {
        frame = CGRectMake(0, 0, windowSize.width, windowSize.height);
    }

    CGFloat x = 0;
    if (_viewController.view.superview) {
        x = [_viewController.view.superview convertPoint:frame.origin toView:nil].x;
    }

    CGFloat y = position.y + self.frame.size.height;
    CGFloat height = windowSize.height - y - _keyboardHeight;

    if (height > position.y - statusBarHeight) {
        _view.frame = CGRectMake(x, y, frame.size.width, height);
        _listView.frame = CGRectMake(_view.bounds.origin.x, _view.bounds.origin.y, frame.size.width, height);
    } else {
        _view.frame = CGRectMake(x, statusBarHeight, frame.size.width, position.y - statusBarHeight);
        _listView.frame = CGRectMake(_view.bounds.origin.x, _view.bounds.origin.y, frame.size.width, _view.frame.size.height);
    }
}

- (void)handleKeyboardWillShow:(NSNotification *)notification
{
    NSValue *frameValue = [notification.userInfo objectForKey:UIKeyboardFrameEndUserInfoKey];
    if (frameValue) {
        CGRect keyboardFrame = [frameValue CGRectValue];
        NSNumber *durationNumber = [notification.userInfo objectForKey:UIKeyboardAnimationDurationUserInfoKey];
        if (durationNumber) {
            CGFloat keyboardAnimationDuration = [durationNumber doubleValue];
            _keyboardHeight = keyboardFrame.size.height;
            [UIView animateWithDuration:keyboardAnimationDuration
                             animations:^void {
                                 [self layoutFilterredView];
                             }];
        }
    }
}

- (void)handleKeyboardWillHide:(NSNotification *)notification
{
    _keyboardHeight = 0;
    NSNumber *durationNumber = [notification.userInfo objectForKey:UIKeyboardAnimationDurationUserInfoKey];
    if (durationNumber) {
        CGFloat keyboardAnimationDuration = [durationNumber doubleValue];
        [UIView animateWithDuration:keyboardAnimationDuration
                         animations:^void {
                             [self layoutFilterredView];
                         }];
    }
}

- (void)setFocus:(BOOL)shouldBecomeFirstResponder view:(UIView *)view
{
    self.accessibilityLabel = view.accessibilityLabel;
    if (shouldBecomeFirstResponder) {
        if (!_isListViewVisible) {
            [self showListView];
        }
        [_listView becomeFirstResponder];
        UIAccessibilityPostNotification(UIAccessibilityLayoutChangedNotification, _listView);
    } else {
        [view resignFirstResponder];
    }
}

- (BOOL)validate:(NSError **)error
{
    // no need to validate
    _isValid = YES;
    if (self.isRequired) {
        _isValid = !(!self.text || !self.text.length ||
                     [self.text isEqualToString:_defaultString] ||
                     ![_titlesMap objectForKey:self.text]);
    } else if (self.text && self.text.length) {
        _isValid = [_titlesMap objectForKey:self.text] != nil;
    }
    return _isValid;
}

- (void)getInput:(NSMutableDictionary *)dictionary
{
    dictionary[self.id] = (self.text && self.text.length) ? [_titlesMap objectForKey:self.text] : @"";
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (_filteredList) {
        return [_filteredList count];
    } else {
        return 0;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"filterred-cell"];
    if (!cell) {
        cell = [[UITableViewCell alloc] init];
    }
    cell.textLabel.text = _filteredList[indexPath.row];
    cell.textLabel.numberOfLines = _choiceSetInput->GetWrap() ? 0 : 1;
    cell.accessibilityLabel = [NSString stringWithFormat:@"%@, %@", _inputLabel, cell.textLabel.text];
    cell.accessibilityTraits = UIAccessibilityTraitButton;
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    self.text = _filteredList[indexPath.row];
    if (_filteringEnabled) {
        [self filterList:self.text];
    }
    if (_isListViewVisible) {
        [self hideListView];
    }
    if (_button.isSelected) {
        _button.selected = NO;
    }
    [self resignFirstResponder];
}

@synthesize hasValidationProperties;

@synthesize id;

@synthesize isRequired;

@synthesize hasVisibilityChanged;

@end
