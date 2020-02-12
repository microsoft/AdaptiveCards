//
//  ViewController.m
//  ViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ViewController.h"
#import "ADCResolver.h"
#import "AdaptiveCards/ACRButton.h"
#import "CustomImageRenderer.h"
#import <SafariServices/SafariServices.h>

const CGFloat kAdaptiveCardsWidth = 330;

@interface ViewController () {
    BOOL _enableCustomRenderer;
    ACOResourceResolvers *_resolvers;
    id<ACRIBaseActionSetRenderer> _defaultRenderer;
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

- (IBAction)toggleCustomRenderer:(id)sender
{
    _enableCustomRenderer = !_enableCustomRenderer;
    ACRRegistration *registration = [ACRRegistration getInstance];

    if (_enableCustomRenderer) {
        // enum will be part of API in next iterations when custom renderer extended to non-action
        // type - tracked by issue #809
        [registration setBaseCardElementRenderer:[CustomImageRenderer getInstance]
                                 cardElementType:ACRImage];

        _defaultRenderer = [registration getActionSetRenderer];
        [registration setActionSetRenderer:self];
    } else {
        [registration setActionRenderer:nil cardElementType:@3];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRTextBlock];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRNumberInput];
        [registration setBaseCardElementRenderer:nil cardElementType:ACRImage];
        [registration setActionSetRenderer:nil];
    }
}

- (void)readAllFiles
{
    // Read hostconfig
    NSString *hostConfigFileName = [NSString stringWithFormat:@"%@%@", [[NSBundle mainBundle] bundlePath], @"/samples/HostConfig/sample.json"];
    NSString *hostConfigJson = [NSString stringWithContentsOfFile:hostConfigFileName
                                                          encoding:NSUTF8StringEncoding
                                                            error:NULL];
    
    ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:hostConfigJson];
    if (hostconfigParseResult.isValid) {
        _config = hostconfigParseResult.config;
    }
    
    // Read all sample cards
    NSString *bundleRoot = [NSString stringWithFormat:@"%@%@", [[NSBundle mainBundle] bundlePath], @"/samples/v1.0/Scenarios/"];
    NSFileManager *manager = [NSFileManager defaultManager];
    
    NSDirectoryEnumerator *direnum = [manager enumeratorAtPath: bundleRoot];
    NSString *filename;
    
    NSMutableArray *unsortedFileNames = [[NSMutableArray alloc] init];
    
    while ((filename = [direnum nextObject]))
    {
        if ([filename hasSuffix:@".json"])
        {
            [unsortedFileNames addObject:filename];
        }
    }
    
    NSArray *sortedFileNames = [unsortedFileNames sortedArrayUsingSelector:@selector(compare:)];
    
    _adaptiveCards = [[NSMutableArray alloc] init];
    
    for (int i = 0; i < sortedFileNames.count; ++i)
    {
        filename = [NSString stringWithFormat:@"%@%@", bundleRoot, sortedFileNames[i]];
        
        NSString *adaptiveCardJson = [NSString stringWithContentsOfFile:filename encoding:NSUTF8StringEncoding error:NULL];
        
        ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:adaptiveCardJson];
        [_adaptiveCards addObject:cardParseResult.card];
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    _resolvers = [[ACOResourceResolvers alloc] init];
    ADCResolver *resolver = [[ADCResolver alloc] init];
    [_resolvers setResourceResolver:resolver scheme:@"http"];
    [_resolvers setResourceResolver:resolver scheme:@"https"];
    _enableCustomRenderer = NO;
    
    self.curView = nil;
    _lastRenderedView = nil;

    _scrView = [[UIScrollView alloc] init];
    _scrView.showsHorizontalScrollIndicator = NO;
    [self.view addSubview:self.scrView];

    UIScrollView *scrollview = self.scrView;
    scrollview.showsVerticalScrollIndicator = YES;
    _scrView.scrollEnabled = YES;
    scrollview.translatesAutoresizingMaskIntoConstraints = NO;

    NSDictionary *viewMap = NSDictionaryOfVariableBindings(scrollview);

    NSArray<NSString *> *formats = [NSArray
        arrayWithObjects:@"V:|-70-[scrollview]-40@100-|",
                         @"H:|-[scrollview]-|", nil];

    [ViewController applyConstraints:formats variables:viewMap];
    
    [self readAllFiles];
    [self renderAllCards];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)renderAllCards
{
    int cardsToRenderCount = 30;
    for (int i = 0; i < cardsToRenderCount; ++i)
    {
        ACOAdaptiveCard *adaptiveCard = _adaptiveCards[i % _adaptiveCards.count];
        
        // put something here
        NSDate* methodStart = [NSDate date];
        ACRRenderResult *renderResult = [ACRRenderer render:adaptiveCard
                                                     config:_config
                                            widthConstraint:kAdaptiveCardsWidth
                                                   delegate:self];
        NSDate *methodFinish = [NSDate date];
        NSTimeInterval executionTime = [methodFinish timeIntervalSinceDate:methodStart];
        NSLog(@"executionTime = %f", executionTime);
        
        // put something else her
        ACRView *ad = renderResult.view;
        ad.mediaDelegate = self;

        self.curView = ad;
        [_scrView addSubview:self.curView];
        UIView *view = self.curView;
        view.translatesAutoresizingMaskIntoConstraints = NO;

        [NSLayoutConstraint constraintWithItem:view
                                 attribute:NSLayoutAttributeCenterX
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:_scrView
                                 attribute:NSLayoutAttributeCenterX
                                multiplier:1.0
                                  constant:3]
        .active = YES;
        
        if (_lastRenderedView == nil)
        {
            [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeTop
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:_scrView
                                     attribute:NSLayoutAttributeTop
                                    multiplier:1.0
                                      constant:0]
            .active = YES;
        }
        else
        {
            [NSLayoutConstraint constraintWithItem:_lastRenderedView
                                     attribute:NSLayoutAttributeBottom
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:view
                                     attribute:NSLayoutAttributeTop
                                    multiplier:1.0
                                      constant:0]
            .active = YES;
        }
            
        if (i == (cardsToRenderCount - 1))
        {
            [NSLayoutConstraint constraintWithItem:view
                                     attribute:NSLayoutAttributeBottom
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:_scrView
                                     attribute:NSLayoutAttributeBottom
                                    multiplier:1.0
                                      constant:0]
            .active = YES;
        }
        
        _lastRenderedView = view;
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

- (void)didFetchUserResponses:(ACOAdaptiveCard *)card action:(ACOBaseActionElement *)action
{
    if (action.type == ACROpenUrl) {
        NSURL *url = [NSURL URLWithString:[action url]];
        SFSafariViewController *svc = [[SFSafariViewController alloc] initWithURL:url];
        [self presentViewController:svc animated:YES completion:nil];
    } else if (action.type == ACRSubmit) {
        NSData *userInputsAsJson = [card inputs];
        NSString *str = [[NSString alloc] initWithData:userInputsAsJson
                                              encoding:NSUTF8StringEncoding];
        if (!_userResponseLabel) {
            _userResponseLabel = [[UILabel alloc] init];
            _userResponseLabel.numberOfLines = 0;
            _userResponseLabel.backgroundColor = UIColor.groupTableViewBackgroundColor;
            _userResponseLabel.accessibilityIdentifier = @"ACRUserResponse";
            [(UIStackView *)self.curView addArrangedSubview:_userResponseLabel];
        }
        _userResponseLabel.text = str;
        NSLog(@"user response fetched: %@ with %@", str, [action data]);
    } else if (action.type == ACRUnknownAction) {
    } else if (action.type == ACRToggleVisibility) {
        NSLog(@"toggle visibility");
    }
}

- (void)didChangeViewLayout:(CGRect)oldFrame newFrame:(CGRect)newFrame
{
    [self.scrView scrollRectToVisible:newFrame animated:YES];
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
        [self.scrView layoutIfNeeded];
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

- (void)didLoadElements
{
    [self.curView setNeedsLayout];
    NSLog(@"completed loading elements");
}

@end
