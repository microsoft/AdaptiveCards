//
//  ViewController.m
//  ViewController
//
//  Copyright © 2020 Microsoft. All rights reserved.
//

#import "ViewController.h"
#import "ACRChatWindow.h"
#import "ACRCustomSubmitTargetBuilder.h"
#import "ADCResolver.h"
#import "AdaptiveCards/ACRAggregateTarget.h"
#import "AdaptiveCards/ACRButton.h"
#import "AdaptiveFileBrowserSource.h"
#import "CustomActionNewType.h"
#import "CustomActionOpenURLRenderer.h"
#import "CustomActionSetRenderer.h"
#import "CustomInputNumberRenderer.h"
#import "CustomProgressBarRenderer.h"
#import "CustomTextBlockRenderer.h"
#import <SafariServices/SafariServices.h>

CGFloat kAdaptiveCardsWidth = 360;

@interface ViewController () {
    BOOL _enableCustomRenderer;
    id<ACRIBaseActionSetRenderer> _defaultRenderer;
    ACRChatWindow *_dataSource;
}

@end

@implementation ViewController
+ (void)applyConstraints:(NSArray<NSString *> *)formats variables:(NSDictionary *)variables
{
    NSArray<NSLayoutConstraint *> *constraints = nil;

    for (NSString *format in formats) {
        constraints = [NSLayoutConstraint constraintsWithVisualFormat:format
                                                              options:0
                                                              metrics:nil
                                                                views:variables];
        [NSLayoutConstraint activateConstraints:constraints];
    }
}

- (IBAction)editText:(id)sender
{
    if (!self.editableStr) {
        return;
    }

    UIStackView *filebrowserView = self.compositeFileBrowserView;
    if (!self.editView) {
        CGRect desiredDimension = filebrowserView.frame;
        self.editView = [[UITextView alloc] initWithFrame:desiredDimension textContainer:nil];

        [self.view addSubview:self.editView];
        self.editView.directionalLockEnabled = NO;
        self.editView.showsHorizontalScrollIndicator = YES;
        self.editView.keyboardType = UIKeyboardTypeAlphabet;

        CGRect frame = CGRectMake(0, 0, self.editView.frame.size.width, 30);
        UIToolbar *toolBar = [[UIToolbar alloc] initWithFrame:frame];
        UIBarButtonItem *flexSpace =
            [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemFlexibleSpace
                                                          target:nil
                                                          action:nil];
        UIBarButtonItem *doneButton =
            [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone
                                                          target:self
                                                          action:@selector(dismissKeyboard)];
        [toolBar setItems:@[ doneButton, flexSpace ] animated:NO];
        [toolBar sizeToFit];
        self.editView.inputAccessoryView = toolBar;
    }
    self.editView.hidden = NO;
    self.editView.delegate = self;

    NSMutableAttributedString *content =
        [[NSMutableAttributedString alloc] initWithString:self.editableStr];
    NSMutableParagraphStyle *para = [[NSMutableParagraphStyle alloc] init];
    para.lineBreakMode = NSLineBreakByCharWrapping;
    para.alignment = NSTextAlignmentLeft;
    [content addAttributes:@{NSParagraphStyleAttributeName : para} range:NSMakeRange(0, 1)];
    self.editView.attributedText = content;
    UIFontDescriptor *dec = self.editView.font.fontDescriptor;
    self.editView.font = [UIFont fontWithDescriptor:dec size:15];
    self.editView.layer.borderWidth = 0.8;
    filebrowserView.hidden = YES;
}

- (BOOL)textViewShouldEndEditing:(UITextView *)textView
{
    [textView resignFirstResponder];
    return YES;
}

- (void)dismissKeyboard
{
    [self.editView resignFirstResponder];
}

- (void)textViewDidBeginEditing:(UITextView *)textView
{
    [textView becomeFirstResponder];
}

- (void)textViewDidEndEditing:(UITextView *)textView
{
    [textView resignFirstResponder];
}

- (IBAction)toggleCustomRenderer:(id)sender
{
    _enableCustomRenderer = !_enableCustomRenderer;
    ACRRegistration *registration = [ACRRegistration getInstance];

    if (_enableCustomRenderer) {
        // enum will be part of API in next iterations when custom renderer extended to non-action
        // type - tracked by issue #809
        [registration setActionRenderer:[CustomActionOpenURLRenderer getInstance]
                        cardElementType:@3];
        [registration setBaseCardElementRenderer:[CustomTextBlockRenderer getInstance]
                                 cardElementType:ACRTextBlock];
        [registration setBaseCardElementRenderer:[CustomInputNumberRenderer getInstance]
                                 cardElementType:ACRNumberInput];
        [registration setBaseCardElementRenderer:[CustomActionSetRenderer getInstance] cardElementType:ACRActionSet];

        [[ACRTargetBuilderRegistration getInstance] setTargetBuilder:[ACRCustomSubmitTargetBuilder getInstance] actionElementType:ACRSubmit capability:ACRAction];
        [[ACRTargetBuilderRegistration getInstance] setTargetBuilder:[ACRCustomSubmitTargetBuilder getInstance] actionElementType:ACRSubmit capability:ACRQuickReply];
        _enableCustomRendererButton.backgroundColor = UIColor.redColor;
        _defaultRenderer = [registration getActionSetRenderer];
        [registration setActionSetRenderer:self];
    } else {
        [registration setActionRenderer:nil cardElementType:@3];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRTextBlock];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRNumberInput];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRImage];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRActionSet];
        [registration setActionSetRenderer:nil];
        _enableCustomRendererButton.backgroundColor = [UIColor colorWithRed:0 / 255
                                                                      green:122.0 / 255
                                                                       blue:1
                                                                      alpha:1];
    }
    [self update:self.editableStr];
}

- (IBAction)applyText:(id)sender
{
    if (_editView.text != NULL && ![_editView.text isEqualToString:@""]) {
        [self update:self.editView.text];
    }
    self.editView.hidden = YES;
    self.compositeFileBrowserView.hidden = NO;
}

- (IBAction)deleteAllRows:(id)sender
{
    [(ACRChatWindow *)self.chatWindow.dataSource deleteAllRows:self.chatWindow];
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    kAdaptiveCardsWidth = [[UIScreen mainScreen] bounds].size.width - 32.0f;
    [self registerForKeyboardNotifications];

    _enableCustomRenderer = NO;
    self.curView = nil;

    ACRRegistration *registration = [ACRRegistration getInstance];
    NSString *type = @"ProgressBar";
    CACProgressBar *progressBarParser = [[CACProgressBar alloc] init];
    [registration setCustomElementParser:progressBarParser key:type];

    CustomProgressBarRenderer *progressBarRenderer = [[CustomProgressBarRenderer alloc] init];
    [registration setCustomElementRenderer:progressBarRenderer key:type];

    CustomActionNewType *customParser = [[CustomActionNewType alloc] init];
    NSString *type1 = @"NewStyle";
    [registration setCustomActionElementParser:customParser key:type1];

    CustomActionNewTypeRenderer *customActionRenderer = [CustomActionNewTypeRenderer getInstance];
    [registration setCustomActionRenderer:customActionRenderer key:type1];

    self.ACVTabVC = [[ACVTableViewController alloc] init];
    [self addChildViewController:self.ACVTabVC];
    self.ACVTabVC.delegate = self;
    self.ACVTabVC.tableView.rowHeight = 25;
    self.ACVTabVC.tableView.sectionFooterHeight = 5;
    self.ACVTabVC.tableView.sectionHeaderHeight = 5;
    self.ACVTabVC.tableView.scrollEnabled = YES;
    self.ACVTabVC.tableView.showsVerticalScrollIndicator = YES;
    self.ACVTabVC.tableView.userInteractionEnabled = YES;
    self.ACVTabVC.tableView.bounces = YES;
    self.ACVTabVC.tableView.separatorStyle = UITableViewCellSeparatorStyleNone;

    UITableView *ACVTabView = self.ACVTabVC.tableView;
    _compositeFileBrowserView = [[UIStackView alloc] init];
    _compositeFileBrowserView.backgroundColor = UIColor.lightGrayColor;
    _compositeFileBrowserView.translatesAutoresizingMaskIntoConstraints = NO;
    _compositeFileBrowserView.alignment = UIStackViewAlignmentCenter;
    _compositeFileBrowserView.axis = UILayoutConstraintAxisVertical;
    [self.view addSubview:_compositeFileBrowserView];
    [_compositeFileBrowserView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor
                                                            constant:10]
        .active = YES;
    [_compositeFileBrowserView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor
                                                             constant:-10]
        .active = YES;

    UIView *fileBrowserView =
        [[AdaptiveFileBrowserSource alloc] initWithFrame:CGRectMake(20, 40, kAdaptiveCardsWidth, 55)
                                        WithDataDelegate:self.ACVTabVC];
    fileBrowserView.translatesAutoresizingMaskIntoConstraints = NO;
    [_compositeFileBrowserView addArrangedSubview:fileBrowserView];

    [_compositeFileBrowserView addArrangedSubview:ACVTabView];
    ACVTabView.translatesAutoresizingMaskIntoConstraints = NO;
    ACVTabView.showsVerticalScrollIndicator = YES;

    [ACVTabView.widthAnchor constraintEqualToAnchor:fileBrowserView.widthAnchor].active = YES;
    self.ACVTabVC.tableHeight = [ACVTabView.heightAnchor constraintEqualToConstant:200.0];
    self.ACVTabVC.tableHeight.active = YES;
    ACVTabView.hidden = YES;

    NSArray<UIStackView *> *buttons = [self buildButtonsLayout:fileBrowserView.centerXAnchor];
    UIStackView *buttonLayout0 = buttons[0], *buttonLayout1 = buttons[1];

    self.chatWindow = [[UITableView alloc] init];
    self.chatWindow.translatesAutoresizingMaskIntoConstraints = NO;
    self.chatWindow.separatorStyle = UITableViewCellSeparatorStyleSingleLineEtched;
    _dataSource = [[ACRChatWindow alloc] init:kAdaptiveCardsWidth];
    _dataSource.adaptiveCardsDelegates = self;
    self.chatWindow.dataSource = _dataSource;

    [self.view addSubview:self.chatWindow];

    UITableView *chatWindow = self.chatWindow;
    NSDictionary *viewMap =
        NSDictionaryOfVariableBindings(_compositeFileBrowserView, buttonLayout0, buttonLayout1, chatWindow);

    NSArray<NSString *> *formats = [NSArray
        arrayWithObjects:@"V:|-40-[_compositeFileBrowserView]-[buttonLayout0]-[buttonLayout1]-[chatWindow]-40@100-|",
                         @"H:|-[chatWindow]-|", nil];

    [ViewController applyConstraints:formats variables:viewMap];

    ACOFeatureRegistration *featureReg = [ACOFeatureRegistration getInstance];
    [featureReg addFeature:@"acTest" featureVersion:@"1.0"];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)update:(NSString *)jsonStr
{
    self.editableStr = jsonStr;

    if (@available(iOS 11.0, *)) {
        [self.chatWindow
            performBatchUpdates:^(void) {
                [_dataSource insertCard:jsonStr];
                NSInteger lastRowIndex = [self.chatWindow numberOfRowsInSection:0];
                NSIndexPath *pathToLastRow = [NSIndexPath indexPathForRow:lastRowIndex inSection:0];
                [self.chatWindow insertRowsAtIndexPaths:@[ pathToLastRow ] withRowAnimation:UITableViewRowAnimationNone];
                //[self.chatWindow reloadRowsAtIndexPaths:self.chatWindow.indexPathsForSelectedRows withRowAnimation:UITableViewRowAnimationNone];
            }
                     completion:nil];
    }
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    float verticalContentInset = self.scrView.frame.size.height - self.curView.frame.size.height;
    verticalContentInset = (verticalContentInset <= 0) ? 20 : verticalContentInset;
    UIEdgeInsets contentInsets = UIEdgeInsetsMake(0.0, 0.0, verticalContentInset, 0.0);
    self.scrView.contentInset = contentInsets;
}

- (void)fromACVTable:(ACVTableViewController *)avcTabVc userSelectedJson:(NSString *)jsonStr
{
    [self update:jsonStr];
}

- (void)source:(ACVTableViewController *)avcTabVc userconfig:(NSString *)payload
{
    self.hostconfig = payload;
}

- (void)didFetchUserResponses:(ACOAdaptiveCard *)card action:(ACOBaseActionElement *)action
{
    if (action.type == ACROpenUrl) {
        NSURL *url = [NSURL URLWithString:[action url]];
        SFSafariViewController *svc = [[SFSafariViewController alloc] initWithURL:url];
        [self presentViewController:svc animated:YES completion:nil];
    } else if (action.type == ACRSubmit) {
        NSData *userInputsAsJson = [card inputs];
        NSString *actionDataField = [action data];

        NSData *actionData = [actionDataField dataUsingEncoding:NSUTF8StringEncoding];
        NSMutableData *combinedData = [actionData mutableCopy];
        [combinedData appendData:userInputsAsJson];
        NSString *str = [[NSString alloc] initWithData:combinedData
                                              encoding:NSUTF8StringEncoding];
        [self presentViewController:[self createAlertController:@"user response fetched" message:str] animated:YES completion:nil];

    } else if (action.type == ACRUnknownAction) {
        if ([action isKindOfClass:[CustomActionNewType class]]) {
            CustomActionNewType *newType = (CustomActionNewType *)action;
            newType.alertController = [self createAlertController:@"successfully rendered new button type" message:newType.alertMessage];
            [self presentViewController:newType.alertController animated:YES completion:nil];
        }
    } else if (action.type == ACRToggleVisibility) {
        [self reloadRowsAtChatWindows];
    } else if (action.type == ACRShowCard) {
        [self reloadRowsAtChatWindows];
    }
}

- (UIAlertController *)createAlertController:(NSString *)title message:(NSString *)message
{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
    [alertController addAction:[UIAlertAction actionWithTitle:@"Dismiss" style:UIAlertActionStyleDefault handler:nil]];
    return alertController;
}

- (void)didChangeViewLayout:(CGRect)oldFrame newFrame:(CGRect)newFrame
{
    //[self.chatWindow reloadData];
}

- (void)didChangeViewLayout:(CGRect)oldFrame newFrame:(CGRect)newFrame properties:(NSDictionary *)properties
{
    NSString *actiontype = (NSString *)properties[ACRAggregateTargetActionType];
    if ([actiontype isEqualToString:ACRAggregateTargetSubmitAction]) {
        UIView *focusedView = properties[ACRAggregateTargetFirstResponder];
        if (focusedView && [focusedView isKindOfClass:[UIView class]]) {
            [self.chatWindow setContentOffset:focusedView.frame.origin animated:YES];
            [self reloadRowsAtChatWindows];
        }
    } else {
        [self reloadRowsAtChatWindows];
    }
}

- (void)didChangeVisibility:(UIButton *)button isVisible:(BOOL)isVisible
{
    if (isVisible) {
        button.backgroundColor = [UIColor redColor];
    } else {
        if ([button isKindOfClass:[ACRButton class]]) {
            ACRButton *acrButton = (ACRButton *)button;
            if (acrButton.sentiment &&
                [@"default" caseInsensitiveCompare:acrButton.sentiment] != NSOrderedSame) {
                [acrButton applySentimentStyling];
            } else {
                button.backgroundColor = [UIColor colorWithRed:0.11 green:0.68 blue:0.97 alpha:1.0];
            }
        } else {
            button.backgroundColor = [UIColor colorWithRed:0.11 green:0.68 blue:0.97 alpha:1.0];
        }
    }
}

- (void)didFetchMediaViewController:(AVPlayerViewController *)controller
                               card:(ACOAdaptiveCard *)card
{
    [self addChildViewController:controller];
    [controller didMoveToParentViewController:self];
}

- (UIView *)renderButtons:(ACRView *)rootView
                   inputs:(NSMutableArray *)inputs
                superview:(UIView<ACRIContentHoldingView> *)superview
                     card:(ACOAdaptiveCard *)card
               hostConfig:(ACOHostConfig *)config
{
    UIView *actionSetView = [_defaultRenderer renderButtons:rootView
                                                     inputs:inputs
                                                  superview:superview
                                                       card:card
                                                 hostConfig:config];
    ((UIScrollView *)actionSetView).showsHorizontalScrollIndicator = NO;
    return actionSetView;
}
- (void)registerForKeyboardNotifications
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWasShown:)
                                                 name:UIKeyboardWillShowNotification
                                               object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWillBeHidden:)
                                                 name:UIKeyboardWillHideNotification
                                               object:nil];
}

// Called when the UIKeyboardDidShowNotification is sent.
- (void)keyboardWasShown:(NSNotification *)aNotification
{
    NSDictionary *info = [aNotification userInfo];
    CGRect kbFrame = [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue];
    CGSize kbSize = kbFrame.size;

    UIEdgeInsets contentInsets = UIEdgeInsetsMake(0.0, 0.0, kbSize.height, 0.0);
    CGRect scrollViewFrame = _scrView.frame;
    if (scrollViewFrame.origin.y + scrollViewFrame.size.height > kbFrame.origin.y) {
        self.scrView.contentInset = contentInsets;
        self.scrView.scrollIndicatorInsets = contentInsets;
    }
}

// Called when the UIKeyboardWillHideNotification is sent
- (void)keyboardWillBeHidden:(NSNotification *)aNotification
{
    UIEdgeInsets contentInsets = UIEdgeInsetsZero;
    self.scrView.contentInset = contentInsets;
    self.scrView.scrollIndicatorInsets = contentInsets;
}

- (void)didLoadElements
{
    [self reloadRowsAtChatWindows];
}

- (NSArray<UIStackView *> *)buildButtonsLayout:(NSLayoutAnchor *)centerXAnchor
{
    NSArray<UIStackView *> *layout = @[ [self configureButtons:centerXAnchor distribution:UIStackViewDistributionFillEqually],
                                        [self configureButtons:centerXAnchor
                                                  distribution:UIStackViewDistributionFill] ];

    // try button
    self.tryButton = [self buildButton:@"Edit" selector:@selector(editText:)];
    [layout[0] addArrangedSubview:self.tryButton];

    // apply button
    self.applyButton = [self buildButton:@"Apply" selector:@selector(applyText:)];
    [layout[0] addArrangedSubview:self.applyButton];

    // delete button
    self.deleteAllRowsButton = [self buildButton:@"Delete All Cards" selector:@selector(deleteAllRows:)];
    [layout[1] addArrangedSubview:self.deleteAllRowsButton];

    // custon renderer button
    self.enableCustomRendererButton = [self buildButton:@"Enable Custom Renderer" selector:@selector(toggleCustomRenderer:)];
    [layout[1] addArrangedSubview:self.enableCustomRendererButton];

    return layout;
}

- (UIButton *)buildButton:(NSString *)title selector:(SEL)selector
{
    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];

    [button setTitle:title forState:UIControlStateNormal];
    [button setTitleColor:[UIColor colorWithRed:0 / 255 green:122.0 / 255 blue:1 alpha:1]
                 forState:UIControlStateSelected];
    button.titleLabel.lineBreakMode = NSLineBreakByWordWrapping;

    [button setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    [button addTarget:self
                  action:selector
        forControlEvents:UIControlEventTouchUpInside];
    button.backgroundColor = [UIColor colorWithRed:0 / 255
                                             green:122.0 / 255
                                              blue:1
                                             alpha:1];
    button.contentEdgeInsets = UIEdgeInsetsMake(5, 8, 5, 8);
    button.layer.cornerRadius = 10;
    return button;
}

- (UIStackView *)configureButtons:(NSLayoutAnchor *)centerXAnchor distribution:(UIStackViewDistribution)distribution
{
    UIStackView *buttonLayout = [[UIStackView alloc] init];
    buttonLayout.axis = UILayoutConstraintAxisHorizontal;
    buttonLayout.translatesAutoresizingMaskIntoConstraints = NO;
    [self.view addSubview:buttonLayout];

    [buttonLayout.widthAnchor constraintEqualToConstant:kAdaptiveCardsWidth].active = YES;
    [buttonLayout.centerXAnchor constraintEqualToAnchor:centerXAnchor].active = YES;

    buttonLayout.alignment = UIStackViewAlignmentCenter;
    buttonLayout.distribution = distribution;
    buttonLayout.spacing = 10;
    return buttonLayout;
}

- (void)reloadRowsAtChatWindows
{
    void (^scroll)(BOOL) = ^(BOOL isFinished) {
        if (isFinished) {
            NSInteger lastRowIndex1 = [self.chatWindow numberOfRowsInSection:0] - 1;
            NSIndexPath *pathToLastRow1 = [NSIndexPath indexPathForRow:lastRowIndex1 inSection:0];
            [self.chatWindow scrollToRowAtIndexPath:pathToLastRow1 atScrollPosition:UITableViewScrollPositionTop animated:YES];
        }
    };

//    if (@available(iOS 11.0, *)) {
//        if ([self.chatWindow numberOfRowsInSection:0] > 1) {
//
//            [self.chatWindow
//                performBatchUpdates:^(void) {
//                    [self.chatWindow reloadRowsAtIndexPaths:self.chatWindow.indexPathsForSelectedRows withRowAnimation:UITableViewRowAnimationNone];
//                }
//                         completion:scroll];
//            return;
//        }
//    }

    [self.chatWindow reloadData];
    scroll(YES);
}
@end
