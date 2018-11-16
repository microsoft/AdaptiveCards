//
//  ViewController.m
//  ViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <SafariServices/SafariServices.h>
#import "ViewController.h"
#import "CustomActionOpenURLRenderer.h"
#import "CustomInputNumberRenderer.h"
#import "CustomProgressBarRenderer.h"
#import "CustomTextBlockRenderer.h"
#import "CustomImageRenderer.h"
#import "ADCResolver.h"
#import "AdaptiveCards/ACRButton.h"

@interface ViewController ()
{
    BOOL _enableCustomRenderer;
    ACOResourceResolvers *_resolvers;
    id<ACRIBaseActionSetRenderer> _defaultRenderer;
}

@end

@implementation ViewController
+ (void)applyConstraints:(NSArray<NSString *> *)formats variables:(NSDictionary *)variables
{
    NSArray<NSLayoutConstraint *> *constraints = nil;

    for(NSString *format in formats)
    {
        constraints = [NSLayoutConstraint constraintsWithVisualFormat:format
                                                              options:0
                                                              metrics:nil
                                                                views:variables]; 
        [NSLayoutConstraint activateConstraints:constraints];
    }
}

- (IBAction)editText:(id)sender
{
    NSMutableAttributedString *content =
    [[NSMutableAttributedString alloc] initWithString:self.editableStr];
    
    NSMutableParagraphStyle *para = [[NSMutableParagraphStyle alloc] init];
    para.lineBreakMode = NSLineBreakByCharWrapping;
    para.alignment = NSTextAlignmentLeft;
    [content addAttributes:@{NSParagraphStyleAttributeName:para} range:NSMakeRange(0,1)];
    self.editView.attributedText = content;
    UIFontDescriptor *dec = self.editView.font.fontDescriptor;
    self.editView.font = [UIFont fontWithDescriptor:dec size:8];
    self.editView.layer.borderWidth = 1.25;

    UITextView *editView = self.editView;
    [self.view addSubview:editView];
    editView.translatesAutoresizingMaskIntoConstraints = NO;
    UIStackView *buttonLayout = self.buttonLayout;
    NSDictionary *viewMap = NSDictionaryOfVariableBindings(editView, buttonLayout);
    [self.ACVTabVC.tableView removeFromSuperview];

    NSArray<NSString *> *formats = 
        [NSArray arrayWithObjects:@"H:|-[editView]-|",   
                              @"V:|-40-[editView(==200)]-[buttonLayout]", nil];
    [ViewController applyConstraints:formats variables:viewMap];
}
- (IBAction)toggleCustomRenderer:(id)sender
{
    _enableCustomRenderer = !_enableCustomRenderer;
    ACRRegistration *registration = [ACRRegistration getInstance];
    if(_enableCustomRenderer){
        // enum will be part of API in next iterations when custom renderer extended to non-action type - tracked by issue #809
        [registration setActionRenderer:[CustomActionOpenURLRenderer getInstance] cardElementType:@3];
        [registration setBaseCardElementRenderer:[CustomTextBlockRenderer getInstance] cardElementType:ACRTextBlock];
        [registration setBaseCardElementRenderer:[CustomInputNumberRenderer getInstance] cardElementType:ACRNumberInput];
        [registration setBaseCardElementRenderer:[CustomImageRenderer getInstance] cardElementType:ACRImage];
        _enableCustomRendererButton.backgroundColor = UIColor.redColor;
        _defaultRenderer = [registration getActionSetRenderer];
        [registration setActionSetRenderer:self];
    } else
    {
        [registration setActionRenderer:nil cardElementType:@3];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRTextBlock];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRNumberInput];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRImage];
        [registration setActionSetRenderer:nil];
        _enableCustomRendererButton.backgroundColor = [UIColor colorWithRed:0/255 green:122.0/255 blue:1 alpha:1];
    }
    [self update:self.editableStr];
}

- (IBAction)applyText:(id)sender
{
    UITableView *ACVTabView = self.ACVTabVC.tableView;
    [self update:self.editView.text];
    [self.view addSubview: ACVTabView];
    [self.editView removeFromSuperview];

    UIStackView *buttonLayout = self.buttonLayout;
    NSDictionary *viewMap = NSDictionaryOfVariableBindings(ACVTabView, buttonLayout);
    NSArray<NSString *> *formats = 
        [NSArray arrayWithObjects:@"H:|-[ACVTabView]-|",   
                              @"V:|-40-[ACVTabView(==200)]-[buttonLayout]", nil];
    [ViewController applyConstraints:formats variables:viewMap];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self registerForKeyboardNotifications];
    _resolvers = [[ACOResourceResolvers alloc] init];
    ADCResolver *resolver = [[ADCResolver alloc] init];
    [_resolvers setResourceResolver:resolver scheme:@"http"];
    _enableCustomRenderer = NO;
    self.curView = nil;
    self.ACVTabVC = [[ACVTableViewController alloc] init];
    self.ACVTabVC.delegate = self;
    self.ACVTabVC.tableView.rowHeight = 25;
    self.ACVTabVC.tableView.sectionFooterHeight = 5;
    self.ACVTabVC.tableView.sectionHeaderHeight = 5;
    self.ACVTabVC.tableView.scrollEnabled = YES;
    self.ACVTabVC.tableView.showsVerticalScrollIndicator = YES;
    self.ACVTabVC.tableView.userInteractionEnabled = YES;
    self.ACVTabVC.tableView.bounces = YES;
    self.ACVTabVC.tableView.layer.borderWidth = 1.25;
    UITableView *ACVTabView = self.ACVTabVC.tableView;
    [self.view addSubview:ACVTabView];
    ACVTabView.translatesAutoresizingMaskIntoConstraints = NO;

    self.editView = [[UITextView alloc] initWithFrame:CGRectMake(0, 0, 0, 0) textContainer: nil];
    self.editView.directionalLockEnabled = NO;
    [self.view addSubview:self.editView];

    UIStackView *buttonLayout = [[UIStackView alloc] init];
    self.buttonLayout = buttonLayout;

    // try button
    buttonLayout.axis = UILayoutConstraintAxisHorizontal;
    self.tryButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [NSLayoutConstraint constraintWithItem:_tryButton attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:25].active = YES;

    [self.tryButton setTitle:@"Try Yourself" forState:UIControlStateNormal];
    [self.tryButton setTitleColor:[UIColor colorWithRed:0/255 green:122.0/255 blue:1 alpha:1] forState:UIControlStateSelected];
    [self.tryButton setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    [self.tryButton addTarget:self action:@selector(editText:)
             forControlEvents:UIControlEventTouchUpInside];
    [buttonLayout addArrangedSubview:self.tryButton];
    self.tryButton.backgroundColor = [UIColor colorWithRed:0/255 green:122.0/255 blue:1 alpha:1];
    self.tryButton.contentEdgeInsets = UIEdgeInsetsMake(5,5,5,5);

    // apply button
    self.applyButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [self.applyButton setTitle:@"Apply" forState:UIControlStateNormal];
    [self.applyButton setTitleColor:[UIColor colorWithRed:0/255 green:122.0/255 blue:1 alpha:1] forState:UIControlStateSelected];
    [self.applyButton setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];

    self.applyButton.backgroundColor = [UIColor colorWithRed:0/255 green:122.0/255 blue:1 alpha:1];
    self.applyButton.contentEdgeInsets = UIEdgeInsetsMake(5,5,5,5);
      [NSLayoutConstraint constraintWithItem:_applyButton attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:25].active = YES;

    [self.applyButton addTarget:self action:@selector(applyText:)
               forControlEvents:UIControlEventTouchUpInside];
    [buttonLayout addArrangedSubview:self.applyButton];

    // custon renderer button
    self.enableCustomRendererButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [self.enableCustomRendererButton setTitle:@"Enable Custom Renderer" forState:UIControlStateNormal];
    [self.enableCustomRendererButton setTitleColor:[UIColor colorWithRed:0/255 green:122.0/255 blue:1 alpha:1] forState:UIControlStateSelected];
    [self.enableCustomRendererButton setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];

    self.enableCustomRendererButton.backgroundColor = [UIColor colorWithRed:0/255 green:122.0/255 blue:1 alpha:1];
    self.enableCustomRendererButton.contentEdgeInsets = UIEdgeInsetsMake(5,5,5,5);
      [NSLayoutConstraint constraintWithItem:_enableCustomRendererButton attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:25].active = YES;

    [self.enableCustomRendererButton addTarget:self action:@selector(toggleCustomRenderer:)
               forControlEvents:UIControlEventTouchUpInside];
    [buttonLayout addArrangedSubview:self.enableCustomRendererButton];

    [self.view addSubview:buttonLayout];
    buttonLayout.translatesAutoresizingMaskIntoConstraints = NO;
    buttonLayout.alignment = UIStackViewAlignmentCenter;
    buttonLayout.distribution = UIStackViewDistributionFillProportionally;
    buttonLayout.spacing = 10;

    [NSLayoutConstraint constraintWithItem:buttonLayout attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:30].active = YES;

    _scrView = [[UIScrollView alloc] init];
    _scrView.showsHorizontalScrollIndicator = NO;

    [self.view addSubview:self.scrView];

    UIScrollView *scrollview = self.scrView;
    scrollview.showsVerticalScrollIndicator = YES;
    _scrView.scrollEnabled = YES;
    scrollview.translatesAutoresizingMaskIntoConstraints = NO;

    NSDictionary *viewMap = NSDictionaryOfVariableBindings(ACVTabView, buttonLayout, scrollview);
    NSArray<NSString *> *formats = 
        [NSArray arrayWithObjects:@"H:|-[ACVTabView]-|",   
                              @"V:|-40-[ACVTabView(==200)]-[buttonLayout]-[scrollview]-40@100-|",
         @"H:|-[buttonLayout]-|", @"H:|-[scrollview]-|", nil];

    [ViewController applyConstraints:formats variables:viewMap];

    [self update:self.ACVTabVC.userSelectedJSon];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)update:(NSString *) jsonStr
{
    self.editableStr = jsonStr;
    ACRRenderResult *renderResult;
    ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:self.hostconfig resourceResolvers:_resolvers];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:jsonStr];
    if(cardParseResult.isValid){
        ACRRegistration *registration = [ACRRegistration getInstance];

        CustomProgressBarRenderer *progressBarRenderer = [[CustomProgressBarRenderer alloc] init];
        [registration setCustomElementParser:progressBarRenderer];
        _config = hostconfigParseResult.config;
        renderResult = [ACRRenderer render:cardParseResult.card config:hostconfigParseResult.config widthConstraint:335];
    }
    
    if(renderResult.succeeded)
    {
        ACRView *ad = renderResult.view;
        ad.acrActionDelegate = self;
        ad.mediaDelegate = self;
        if(self.curView)
            [self.curView removeFromSuperview];

        self.curView = ad;

        [_scrView addSubview:self.curView];
        UIView *view = self.curView;
        view.translatesAutoresizingMaskIntoConstraints = NO;
            
        [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:_scrView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
        [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:_scrView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
        [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:_scrView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:3].active = YES;
        [NSLayoutConstraint constraintWithItem:view attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:_scrView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
    }
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    float verticalContentInset = self.scrView.frame.size.height - self.curView.frame.size.height;
    verticalContentInset = (verticalContentInset <= 0)? 20 : verticalContentInset;
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
    if(action.type == ACROpenUrl){
        NSURL *url = [NSURL URLWithString:[action url]];
        SFSafariViewController *svc = [[SFSafariViewController alloc] initWithURL:url];
        [self presentViewController:svc animated:YES completion:nil];
    } else if(action.type == ACRSubmit){
        NSData * userInputsAsJson = [card inputs];
        NSString *str = [[NSString alloc] initWithData:userInputsAsJson encoding:NSUTF8StringEncoding];
        if(!_userResponseLabel) {
            _userResponseLabel = [[UILabel alloc] init];
            _userResponseLabel.numberOfLines = 0;
            _userResponseLabel.backgroundColor = UIColor.groupTableViewBackgroundColor;
            _userResponseLabel.accessibilityIdentifier = @"ACRUserResponse";
            [(UIStackView *)self.curView addArrangedSubview:_userResponseLabel];
        }
        _userResponseLabel.text = str;
        NSLog(@"user response fetched: %@ with %@", str, [action data]);
    }
}

- (void)didChangeViewLayout:(CGRect)oldFrame newFrame:(CGRect)newFrame
{
    [self.scrView scrollRectToVisible:newFrame animated:YES];
}

- (void)didChangeVisibility:(UIButton *)button isVisible:(BOOL)isVisible
{
    if(isVisible)
    {
        button.backgroundColor = [UIColor redColor];
    }
    else
    {
        if([button isKindOfClass:[ACRButton class]])
        {
            ACRButton *acrButton = (ACRButton*)button;
            if(acrButton.sentiment != ACRSentimentDefault)
            {
                [acrButton applySentimentStyling];
            }
            else
            {
                button.backgroundColor = [UIColor colorWithRed:0.11 green:0.68 blue:0.97 alpha:1.0];
            }
        }
        else
        {
            button.backgroundColor = [UIColor colorWithRed:0.11 green:0.68 blue:0.97 alpha:1.0];
        }
        [self.scrView layoutIfNeeded];
    }
}

- (void)didFetchMediaViewController:(AVPlayerViewController *)controller card:(ACOAdaptiveCard *)card {
    [self addChildViewController:controller];    
    [controller didMoveToParentViewController:self];
}

- (UIView *)renderButtons:(ACRView *)rootView
                   inputs:(NSMutableArray *)inputs
                superview:(UIView<ACRIContentHoldingView> *)superview
                     card:(ACOAdaptiveCard *)card
               hostConfig:(ACOHostConfig *)config
{
    UIView *actionSetView = [_defaultRenderer renderButtons:rootView inputs:inputs superview:superview card:card hostConfig:config];
    ((UIScrollView *)actionSetView).showsHorizontalScrollIndicator = NO;
    return actionSetView;
}
- (void)registerForKeyboardNotifications
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWasShown:)
                                                 name:UIKeyboardWillShowNotification object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWillBeHidden:)
                                                 name:UIKeyboardWillHideNotification object:nil];

}
// Called when the UIKeyboardDidShowNotification is sent.
- (void)keyboardWasShown:(NSNotification*)aNotification
{
    NSDictionary* info = [aNotification userInfo];
    CGRect kbFrame = [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue];
    CGSize kbSize = kbFrame.size;

    UIEdgeInsets contentInsets = UIEdgeInsetsMake(0.0, 0.0, kbSize.height, 0.0);
    CGRect scrollViewFrame = _scrView.frame;
    if(scrollViewFrame.origin.y + scrollViewFrame.size.height > kbFrame.origin.y) {
        self.scrView.contentInset = contentInsets;
        self.scrView.scrollIndicatorInsets = contentInsets;
    }
}

// Called when the UIKeyboardWillHideNotification is sent
- (void)keyboardWillBeHidden:(NSNotification*)aNotification
{
    UIEdgeInsets contentInsets = UIEdgeInsetsZero;
    self.scrView.contentInset = contentInsets;
    self.scrView.scrollIndicatorInsets = contentInsets;
}

@end
