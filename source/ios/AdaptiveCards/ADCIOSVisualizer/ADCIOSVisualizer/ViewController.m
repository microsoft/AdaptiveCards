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
#import "AdaptiveCards/ACRButton.h"
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
    id<ACRIBaseActionSetRenderer> _defaultRenderer;
    ACRChatWindow *_dataSource;
    dispatch_queue_t _global_queue;
    __weak AVPlayerViewController *_mediaViewController;
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

- (IBAction)toggleCustomRenderer:(UISwitch *)sender
{
    [self.view endEditing:YES];
    ACRRegistration *registration = [ACRRegistration getInstance];

    if (_enableCustomRendererSwitch.isOn) {
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
        _defaultRenderer = [registration getActionSetRenderer];
        [registration setActionSetRenderer:self];
    } else {
        [registration setActionRenderer:nil actionElementType:ACROpenUrl];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRTextBlock];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRNumberInput];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRActionSet];
        [registration setActionSetRenderer:nil];
    }
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

    // clean the retrieved inputs
    if ([self appIsBeingTested]) {
        [self.retrievedInputsTextView setText:@" "];
    }

    if (_mediaViewController && _mediaViewController.player) {
        [_mediaViewController.player pause];
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    _global_queue = dispatch_get_main_queue();

    kFileBrowserWidth = [[UIScreen mainScreen] bounds].size.width - 32.0f;
    kAdaptiveCardsWidth = kFileBrowserWidth;
    [self registerForKeyboardNotifications];

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

    NSArray<UIStackView *> *buttons = [self buildControlLayout:fileBrowserView.centerXAnchor];
    UIStackView *retrievedInputsLayout = [self buildRetrievedResultsLayout:fileBrowserView.centerXAnchor];

    UIStackView *buttonLayout0 = buttons[0], *buttonLayout1 = buttons[1];

    self.chatWindow = [[UITableView alloc] init];
    self.chatWindow.translatesAutoresizingMaskIntoConstraints = NO;
    [self.chatWindow registerClass:[ACRChatWindowCell class] forCellReuseIdentifier:@"adaptiveCell"];
    self.chatWindow.separatorStyle = UITableViewCellSeparatorStyleSingleLine;

    // set a identifier to ease development of UI tests
    self.chatWindow.accessibilityIdentifier = @"ChatWindow";

    // the width of the AdaptiveCards does not need to be set.
    // if the width for Adaptive Cards is zero, the width is determined by the contraint(s) set externally on the card.
    _dataSource = [[ACRChatWindow alloc] init:kAdaptiveCardsWidth];
    _dataSource.adaptiveCardsDelegates = self;
    _dataSource.adaptiveCardsMediaDelegates = self;
    self.chatWindow.dataSource = _dataSource;

    [self.view addSubview:self.chatWindow];

    UITableView *chatWindow = self.chatWindow;

    // if the app is being tested we render an extra layout that contains the
    // retrieved input values json
    NSString *layoutOption = [self appIsBeingTested] ? @"-[retrievedInputsLayout]-" : @"-";

    NSArray<NSString *> *visualFormats = @[ [NSString stringWithFormat:@"V:|-40-[_compositeFileBrowserView]-[buttonLayout0]-[buttonLayout1]%@[chatWindow]-40@100-|", layoutOption], @"H:|-[chatWindow]-|", @"H:|-[buttonLayout0]-|", @"H:|-[buttonLayout1]-|" ];

    NSDictionary *viewMap;
    if ([self appIsBeingTested]) {
        viewMap =
            NSDictionaryOfVariableBindings(_compositeFileBrowserView, buttonLayout0, buttonLayout1, retrievedInputsLayout, chatWindow);
    } else {
        viewMap =
            NSDictionaryOfVariableBindings(_compositeFileBrowserView, buttonLayout0, buttonLayout1, chatWindow);
    }

    [ViewController applyConstraints:visualFormats variables:viewMap];

    ACOFeatureRegistration *featureReg = [ACOFeatureRegistration getInstance];
    [featureReg addFeature:@"acTest" featureVersion:@"1.0"];

    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(handleVoiceOverEvent:) name:UIAccessibilityElementFocusedNotification object:nil];
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
        if ([self appIsBeingTested]) {
            NSString *str2 = [NSString stringWithFormat:@"{\n\t\"inputs\":%@\n}", [fetchedInputList componentsJoinedByString:@",\n"]];
            [self.retrievedInputsTextView setText:str2];
        } else {
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
    _mediaViewController = controller;
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
                     additionalData:(NSDictionary *)additionalData
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

- (NSArray<UIStackView *> *)buildControlLayout:(NSLayoutAnchor *)centerXAnchor
{
    NSArray<UIStackView *> *layout = @[ [self configureStackView:centerXAnchor distribution:UIStackViewDistributionFillEqually],
                                        [self configureStackView:centerXAnchor
                                                    distribution:UIStackViewDistributionFill] ];
    // delete button
    self.deleteAllRowsButton = [self buildButton:@"Delete All Cards" selector:@selector(deleteAllRows:)];
    [layout[0] addArrangedSubview:self.deleteAllRowsButton];

    UIView *padding1 = [[UIView alloc] init];
    [layout[1] addArrangedSubview:padding1];
    // custom control switch
    UILabel *customControlLabel = [[UILabel alloc] init];
    customControlLabel.text = @"Enable Custom Control";
    self.enableCustomRendererSwitch = [[UISwitch alloc] init];
    [self.enableCustomRendererSwitch addTarget:self action:@selector(toggleCustomRenderer:) forControlEvents:UIControlEventValueChanged];

    [layout[1] addArrangedSubview:customControlLabel];
    [layout[1] addArrangedSubview:self.enableCustomRendererSwitch];

    return layout;
}

- (UIStackView *)buildRetrievedResultsLayout:(NSLayoutAnchor *)centerXAnchor
{
    UIStackView *layout = [self configureStackView:centerXAnchor
                                      distribution:UIStackViewDistributionFill];

    if ([self appIsBeingTested]) {
        // Set a background red color to signalize the app is in test mode
        self.view.backgroundColor = [UIColor colorWithRed:1.0 green:0.80 blue:0.80 alpha:1];

        // Initialize the input results label
        self.retrievedInputsTextView = [self buildLabel:@"" withIdentifier:@"SubmitActionRetrievedResults"];

        [self.retrievedInputsTextView setText:@" "];

        // Add the label to the container
        [layout addArrangedSubview:self.retrievedInputsTextView];
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

- (UILabel *)buildLabel:(NSString *)text withIdentifier:(NSString *)identifier
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

- (UIStackView *)configureStackView:(NSLayoutAnchor *)centerXAnchor distribution:(UIStackViewDistribution)distribution
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
                       // This lines are required for updating the element tree after a
                       // show card action has taken place, otherwise no previously hidden
                       // element can be retrieved
                       if ([self appIsBeingTested]) {
                           [self.chatWindow beginUpdates];

                           NSInteger lastRowIndex = [self->_dataSource tableView:self.chatWindow numberOfRowsInSection:0] - 1;
                           NSIndexPath *pathToLastRow = [NSIndexPath indexPathForRow:lastRowIndex inSection:0];
                           // reload the row; it is possible that the row height, for example, is calculated without images loaded
                           [self.chatWindow reloadRowsAtIndexPaths:@[ pathToLastRow ] withRowAnimation:UITableViewRowAnimationNone];
                           UIAccessibilityPostNotification(UIAccessibilityLayoutChangedNotification, nil);
                           [self.chatWindow endUpdates];
                       } else {
                           // when table cell reload is complete, notify VO that layout has changed.
                           [self.chatWindow
                               performBatchUpdates:^(void) {
                                   [self.chatWindow reloadData];
                               }
                               completion:^(BOOL finished) {
                                   UIAccessibilityPostNotification(UIAccessibilityLayoutChangedNotification, nil);
                               }];
                       }
                   });
}

// Handle accessibility state change events
- (void)traitCollectionDidChange:(UITraitCollection *)previousTraitCollection
{
    [super traitCollectionDidChange:previousTraitCollection];

    if (!previousTraitCollection) {
        return;
    }

    BOOL isAccessibilityCategory = UIContentSizeCategoryIsAccessibilityCategory(self.traitCollection.preferredContentSizeCategory);

    if (isAccessibilityCategory != UIContentSizeCategoryIsAccessibilityCategory(previousTraitCollection.preferredContentSizeCategory)) {
        if (_dataSource) {
            // prep data sources for accessiblity changes, font size changes events
            [_dataSource prepareForRedraw];
            // ask for redraw of visible rows
            [self.chatWindow reloadData];
        }
    }
}

- (BOOL)appIsBeingTested
{
    // Add this line for test recording: return YES;
    NSArray *arguments = [[NSProcessInfo processInfo] arguments];
    return [arguments containsObject:@"ui-testing"];
}

- (void)handleVoiceOverEvent:(NSNotification *)notificaiton
{
    UIAccessibilityElement *a11yElement = (UIAccessibilityElement *)notificaiton.userInfo[UIAccessibilityFocusedElementKey];
    CGRect rect = UIAccessibilityConvertFrameToScreenCoordinates(self.chatWindow.frame, self.chatWindow);
    if (a11yElement.accessibilityFrame.origin.y >= rect.origin.y) {
        CGPoint point = CGPointMake(self.chatWindow.contentOffset.x, a11yElement.accessibilityFrame.origin.y - rect.origin.y);

        [self.chatWindow setContentOffset:point animated:NO];
    }
}
@end
