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
#import "AdaptiveCards/ACROverflowTarget.h"
#import "AdaptiveFileBrowserSource.h"
#import "CustomActionNewType.h"
#import "CustomActionOpenURLRenderer.h"
#import "CustomActionSetRenderer.h"
#import "CustomInputNumberRenderer.h"
#import "CustomProgressBarRenderer.h"
#import "CustomTextBlockRenderer.h"
#import <SafariServices/SafariServices.h>

// the width of the AdaptiveCards does not need to be set.
// if the width for Adaptive Cards is zero, the width is determined by the contraint(s) set externally on the card.
CGFloat kAdaptiveCardsWidth = 0;
CGFloat kFileBrowserWidth = 0;

@interface ViewController () {
    BOOL _enableCustomRenderer;
    id<ACRIBaseActionSetRenderer> _defaultRenderer;
    ACRChatWindow *_dataSource;
    dispatch_queue_t _global_queue;
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
    [self.view endEditing:YES];
    [self dismissViewControllerAnimated:YES completion:nil];
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
    [self.view endEditing:YES];
    _enableCustomRenderer = !_enableCustomRenderer;
    ACRRegistration *registration = [ACRRegistration getInstance];

    if (_enableCustomRenderer) {
        // enum will be part of API in next iterations when custom renderer extended to non-action
        // type - tracked by issue #809
        [registration setActionRenderer:[CustomActionOpenURLRenderer getInstance]
                      actionElementType:ACROpenUrl
                    useResourceResolver:YES];
        [registration setBaseCardElementRenderer:[CustomTextBlockRenderer getInstance]
                                 cardElementType:ACRTextBlock
                             useResourceResolver:YES];
        [registration setBaseCardElementRenderer:[CustomInputNumberRenderer getInstance]
                                 cardElementType:ACRNumberInput
                             useResourceResolver:YES];
        [registration setBaseCardElementRenderer:[CustomActionSetRenderer getInstance] cardElementType:ACRActionSet useResourceResolver:YES];

        [[ACRTargetBuilderRegistration getInstance] setTargetBuilder:[ACRCustomSubmitTargetBuilder getInstance] actionElementType:ACRSubmit capability:ACRAction];
        [[ACRTargetBuilderRegistration getInstance] setTargetBuilder:[ACRCustomSubmitTargetBuilder getInstance] actionElementType:ACRSubmit capability:ACRQuickReply];
        _enableCustomRendererButton.backgroundColor = UIColor.redColor;
        _defaultRenderer = [registration getActionSetRenderer];
        [registration setActionSetRenderer:self];
    } else {
        [registration setActionRenderer:nil actionElementType:ACROpenUrl];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRTextBlock];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRNumberInput];
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
    [self.view endEditing:YES];
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
    _global_queue = dispatch_get_main_queue();

    kFileBrowserWidth = [[UIScreen mainScreen] bounds].size.width - 32.0f;
    kAdaptiveCardsWidth = kFileBrowserWidth;
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
        [[AdaptiveFileBrowserSource alloc] initWithFrame:CGRectMake(20, 40, kFileBrowserWidth, 55)
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
    UIStackView *buttonLayout0 = buttons[0], *buttonLayout1 = buttons[1], *retrievedInputsLayout;

    self.chatWindow = [[UITableView alloc] init];
    self.chatWindow.translatesAutoresizingMaskIntoConstraints = NO;
    self.chatWindow.separatorStyle = UITableViewCellSeparatorStyleSingleLineEtched;
    
    // set a identifier to ease development of UI tests
    self.chatWindow.accessibilityIdentifier = @"ChatWindow";

    // the width of the AdaptiveCards does not need to be set.
    // if the width for Adaptive Cards is zero, the width is determined by the contraint(s) set externally on the card.
    _dataSource = [[ACRChatWindow alloc] init:kAdaptiveCardsWidth];
    _dataSource.adaptiveCardsDelegates = self;
    self.chatWindow.dataSource = _dataSource;

    [self.view addSubview:self.chatWindow];

    UITableView *chatWindow = self.chatWindow;
    NSDictionary *viewMap;
    NSArray<NSString *> *formats;
    
    // if the app is being tested we render an extra layout that contains the
    // retrieved input values json
    if ([self appIsBeingTested])
    {
        retrievedInputsLayout = buttons[2];
        viewMap =
        NSDictionaryOfVariableBindings(_compositeFileBrowserView, buttonLayout0, buttonLayout1, retrievedInputsLayout, chatWindow);
        formats = [NSArray arrayWithObjects:@"V:|-40-[_compositeFileBrowserView]-[buttonLayout0]-[buttonLayout1]-[retrievedInputsLayout]-[chatWindow]-40@100-|",
                         @"H:|-[chatWindow]-|", nil];
    }
    else
    {
        viewMap =
        NSDictionaryOfVariableBindings(_compositeFileBrowserView, buttonLayout0, buttonLayout1, chatWindow);
        formats = [NSArray arrayWithObjects:@"V:|-40-[_compositeFileBrowserView]-[buttonLayout0]-[buttonLayout1]-[chatWindow]-40@100-|",
                         @"H:|-[chatWindow]-|", nil];
    }

    [ViewController applyConstraints:formats variables:viewMap];

    ACOFeatureRegistration *featureReg = [ACOFeatureRegistration getInstance];
    [featureReg addFeature:@"acTest" featureVersion:@"1.0"];
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
    } else if (action.type == ACRSubmit || action.type == ACRExecute) {
        NSMutableArray<NSString *> *fetchedInputList = [NSMutableArray array];
        NSData *userInputsAsJson = [card inputs];
        if (userInputsAsJson) {
            [fetchedInputList addObject:[[NSString alloc] initWithData:userInputsAsJson
                                                              encoding:NSUTF8StringEncoding]];
        }

        NSString *data = [action data];
        if (data && data.length) {
            [fetchedInputList addObject:[NSString stringWithFormat:@"\"data\" : %@", data]];
        }

        if (action.type == ACRExecute) {
            if (action.verb && action.verb.length) {
                [fetchedInputList addObject:[NSString stringWithFormat:@"\"verb\" : %@", action.verb]];
            }
        } else {
            [self reloadRowsAtChatWindowsWithIndexPaths:self.chatWindow.indexPathsForSelectedRows];
        }
        NSString *str = [NSString stringWithFormat:@"{\n%@\n}", [fetchedInputList componentsJoinedByString:@",\n"]];
        
        // if the app is being tested we set the result in the uilabel, otherwise
        // we show the label in a popup
        if ([self appIsBeingTested])
        {
            NSString *str2 = [NSString stringWithFormat:@"{\n\"inputs\":%@\n}", [fetchedInputList componentsJoinedByString:@",\n"]];
            [self.retrievedInputsTextView setText:str2];
        }
        else
        {
            [self presentViewController:[self createAlertController:@"user response fetched" message:str] animated:YES completion:nil];
        }
        
    } else if (action.type == ACRUnknownAction) {
        if ([action isKindOfClass:[CustomActionNewType class]]) {
            CustomActionNewType *newType = (CustomActionNewType *)action;
            newType.alertController = [self createAlertController:@"successfully rendered new button type" message:newType.alertMessage];
            [self presentViewController:newType.alertController animated:YES completion:nil];
        }
    } else if (action.type == ACRToggleVisibility) {
        [self reloadRowsAtChatWindowsWithIndexPaths:self.chatWindow.indexPathsForSelectedRows];
    } else if (action.type == ACRShowCard) {
        [self reloadRowsAtChatWindowsWithIndexPaths:self.chatWindow.indexPathsForSelectedRows];
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
    [self reloadRowsAtChatWindowsWithIndexPaths:self.chatWindow.indexPathsForSelectedRows];
}

- (void)didChangeViewLayout:(CGRect)oldFrame newFrame:(CGRect)newFrame properties:(NSDictionary *)properties
{
    NSString *actiontype = (NSString *)properties[ACRAggregateTargetActionType];
    if ([actiontype isEqualToString:ACRAggregateTargetSubmitAction]) {
        UIView *focusedView = properties[ACRAggregateTargetFirstResponder];
        if (focusedView && [focusedView isKindOfClass:[UIView class]]) {
            [self.chatWindow setContentOffset:focusedView.frame.origin animated:YES];
            [self reloadRowsAtChatWindowsWithIndexPathsAfterValidation:self.chatWindow.indexPathsForVisibleRows];
        }
    } else {
        [self reloadRowsAtChatWindowsWithIndexPaths:self.chatWindow.indexPathsForVisibleRows];
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

- (BOOL)shouldAllowMoreThanMaxActionsInOverflowMenu
{
    return YES;
}

- (BOOL)onRenderOverflowAction:(UIButton *)button
                     forTarget:(ACROverflowTarget *)target
          isAtRootLevelActions:(BOOL)isAtRootLevelActions
{
    if (isAtRootLevelActions) {
        UIButton *extOverflowBtn = [UIButton buttonWithType:UIButtonTypeSystem];
        CGRect buttonFrame = extOverflowBtn.frame;
        buttonFrame.size = CGSizeMake(250, 40);
        extOverflowBtn.frame = buttonFrame;
        extOverflowBtn.layer.cornerRadius = 10;
        extOverflowBtn.titleLabel.lineBreakMode = NSLineBreakByWordWrapping;
        [extOverflowBtn setTitle:@"Root Overflow Actions (...)" forState:UIControlStateNormal];
        [extOverflowBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
        [extOverflowBtn setBackgroundColor:[UIColor orangeColor]];
        [extOverflowBtn addTarget:target
                           action:@selector(doSelectAction)
                 forControlEvents:UIControlEventTouchUpInside];
        extOverflowBtn.contentEdgeInsets = UIEdgeInsetsMake(5, 8, 5, 8);
        [_dataSource insertView:extOverflowBtn];
        return YES; // skip SDK defult render
    }
    return NO; // continue SDK defult render
}

- (BOOL)onDisplayOverflowActionMenu:(NSArray<ACROverflowMenuItem *> *)menuItems
                    alertController:(UIAlertController *)alert
{
    // [Option 1] the easiest way is to just present the alert view. It's prepared and presentable ready.
    //    [self presentViewController: alert];

    // [Option 2] client can prepare its own presentation by direclty employing menuItems
    UIAlertController *myAlert = [UIAlertController alertControllerWithTitle:nil
                                                                     message:nil
                                                              preferredStyle:UIAlertControllerStyleAlert];

    for (ACROverflowMenuItem *item in menuItems) {
        UIAlertAction *action = [UIAlertAction actionWithTitle:item.title
                                                         style:UIAlertActionStyleDestructive
                                                       handler:^(UIAlertAction *_Nonnull action) {
                                                           [item.target doSelectAction];
                                                       }];

        [item loadIconImageWithSize:CGSizeMake(40, 40)
                       onIconLoaded:^(UIImage *image) {
                           if (image) {
                               [action setValue:[image imageWithRenderingMode:UIImageRenderingModeAlwaysOriginal]
                                         forKey:@"image"];
                           }
                       }];

        [myAlert addAction:action];
    }
    [myAlert addAction:[UIAlertAction actionWithTitle:@"Cancel"
                                                style:UIAlertActionStyleCancel
                                              handler:nil]];
    [self presentViewController:myAlert animated:YES completion:nil];
    return YES; // skip SDK defult display
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
    self.chatWindow.contentInset = contentInsets;
}

// Called when the UIKeyboardWillHideNotification is sent
- (void)keyboardWillBeHidden:(NSNotification *)aNotification
{
    UIEdgeInsets contentInsets = UIEdgeInsetsZero;
    self.chatWindow.contentInset = contentInsets;
}

- (NSArray<UIStackView *> *)buildButtonsLayout:(NSLayoutAnchor *)centerXAnchor
{
    NSArray<UIStackView *> *layout = @[ [self configureButtons:centerXAnchor distribution:UIStackViewDistributionFillEqually],
                                        [self configureButtons:centerXAnchor
                                                  distribution:UIStackViewDistributionFill],
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

    if ([self appIsBeingTested])
    {
        // Set a background red color to signalize the app is in test mode
        self.view.backgroundColor = [UIColor colorWithRed:1.0 green:0.80 blue:0.80 alpha:1];
        
        // Initialize the input results label
        self.retrievedInputsTextView = [self buildLabel:@"" withIdentifier:@"SubmitActionRetrievedResults"];
        
        // Add the label to the container
        [layout[2] addArrangedSubview:self.retrievedInputsTextView];
    }
    
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

- (UILabel *)buildLabel:(NSString*)text withIdentifier:(NSString*)identifier
{
    UILabel *label = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
    [label setText:text];
    [label setTextColor:[UIColor blackColor]];
    [label setBaselineAdjustment:UIBaselineAdjustmentAlignBaselines];
    [label setLineBreakMode:NSLineBreakByCharWrapping];
    [label setNumberOfLines:4];
    
    [label setAccessibilityIdentifier:identifier];
    return label;
}

- (UIStackView *)configureButtons:(NSLayoutAnchor *)centerXAnchor distribution:(UIStackViewDistribution)distribution
{
    UIStackView *buttonLayout = [[UIStackView alloc] init];
    buttonLayout.axis = UILayoutConstraintAxisHorizontal;
    buttonLayout.translatesAutoresizingMaskIntoConstraints = NO;
    [self.view addSubview:buttonLayout];

    [buttonLayout.widthAnchor constraintEqualToConstant:kFileBrowserWidth].active = YES;
    [buttonLayout.centerXAnchor constraintEqualToAnchor:centerXAnchor].active = YES;

    buttonLayout.alignment = UIStackViewAlignmentCenter;
    buttonLayout.distribution = distribution;
    buttonLayout.spacing = 10;
    return buttonLayout;
}

- (void)update:(NSString *)jsonStr
{
    [self.view endEditing:YES];
    NSInteger prevCount = [_dataSource tableView:self.chatWindow numberOfRowsInSection:0];
    // resources such as images may not be ready when AdaptiveCard is added to its super view
    // AdaptiveCard can notify when its resources are all loaded via - (void)didLoadElements delegate
    // but the notification can come at any time
    // adding the two tasks, rendering the card & handling the notification, to a task queue ensures
    // the syncronization.
    dispatch_async(_global_queue, ^{
        self.editableStr = jsonStr;
        // the data source will parse & render the card, and update its store for AdaptiveCards
        [self->_dataSource insertCard:jsonStr];
        // tell the table view UI to add N rows.
        // The delta change might be > 1 since [_dataSource insertView] might have been called to
        // insert additional non-card views (such as overflow button)

        NSInteger lastRowIndex = [self.chatWindow numberOfRowsInSection:0];
        NSInteger postCount = [self->_dataSource tableView:self.chatWindow numberOfRowsInSection:0];
        NSInteger rowsToAdd = postCount - prevCount;
        NSMutableArray<NSIndexPath *> *indexPaths = [NSMutableArray arrayWithCapacity:rowsToAdd];
        for (int i = 0; i < rowsToAdd; ++i) {
            NSIndexPath *pathToLastRow = [NSIndexPath indexPathForRow:(lastRowIndex + i) inSection:0];
            [indexPaths addObject:pathToLastRow];
        }
        [self.chatWindow insertRowsAtIndexPaths:indexPaths
                               withRowAnimation:UITableViewRowAnimationNone];
    });
}

// ViewController's AdaptiveCard delegate that handles the resource loading completion event.
- (void)didLoadElements
{
    // GCD ensures that this event happens after the AdaptiveCard is rendered and added to the table view.
    // updating the data source & its table view is complete when it's the turn for the enqueued task by the delegate.
    dispatch_async(_global_queue,
                   ^{
                       NSInteger lastRowIndex = [self->_dataSource tableView:self.chatWindow numberOfRowsInSection:0] - 1;
                       NSIndexPath *pathToLastRow = [NSIndexPath indexPathForRow:lastRowIndex inSection:0];
                       // reload the row; it is possible that the row height, for example, is calculated without images loaded
                       [self.chatWindow reloadRowsAtIndexPaths:@[ pathToLastRow ] withRowAnimation:UITableViewRowAnimationNone];
                       // scroll the new card to the top
                       [self.chatWindow scrollToRowAtIndexPath:pathToLastRow atScrollPosition:UITableViewScrollPositionTop animated:YES];
                   });
}


- (void)reloadRowsAtChatWindows:(NSIndexPath *)indexPath
{
    [self reloadRowsAtChatWindowsWithIndexPaths:@[ indexPath ]];
}

- (void)reloadRowsAtChatWindowsWithIndexPathsAfterValidation:(NSArray<NSIndexPath *> *)indexPaths
{
    dispatch_async(_global_queue,
                   ^{
                       [self.chatWindow beginUpdates];
                       [self.chatWindow endUpdates];
    });
}

- (void)reloadRowsAtChatWindowsWithIndexPaths:(NSArray<NSIndexPath *> *)indexPaths
{
    dispatch_async(_global_queue,
                   ^{
                       [self.chatWindow beginUpdates];
                       [self.chatWindow endUpdates];

                       // This lines are required for updating the element tree after a
                       // show card action has taken place, otherwise no previously hidden
                       // element can be retrieved
                       if ([self appIsBeingTested])
                       {
                           NSIndexPath* index = [NSIndexPath indexPathForRow:0 inSection:0];
                           NSArray* indexPath = [NSArray arrayWithObjects:index, nil];
                           [self.chatWindow reloadRowsAtIndexPaths:indexPath withRowAnimation:UITableViewRowAnimationNone];
                       }
        
    });
}

- (BOOL)appIsBeingTested
{
    // Uncomment this line for test recording
    // return YES;
    NSArray *arguments = [[NSProcessInfo processInfo] arguments];
    return [arguments containsObject:@"ui-testing"];
}

@end
