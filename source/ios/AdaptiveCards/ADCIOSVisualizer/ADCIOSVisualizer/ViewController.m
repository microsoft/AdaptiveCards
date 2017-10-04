//
//  ViewController.m
//  ViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (IBAction)editText:(id)sender
{
    self.ACVTabVC.tableView.hidden = true;
    self.editView.hidden = false;
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
}

- (IBAction)applyText:(id)sender
{
    self.ACVTabVC.tableView.hidden = false;
    self.editView.hidden = true;
    [self update:self.editView.text];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    UIStackView *mainContentView = [[UIStackView alloc] init];
    [self.view addSubview:mainContentView];
    
    NSDictionary *viewMap = NSDictionaryOfVariableBindings(mainContentView);
    NSArray<NSString *> *formats = [NSArray arrayWithObjects: @"H:|-[mainContentView]-|", @"V:|-[mainContentView]-|", nil];
    NSArray<NSLayoutConstraint *> *constraints = nil;
    
    for(NSString *format in formats)
    { 
        constraints = [NSLayoutConstraint constraintsWithVisualFormat:format
                                                              options:0
                                                              metrics:nil
                                                                views:viewMap];
        for(NSLayoutConstraint *con in constraints)
        {
            con.active = YES;
        }
    }
    
    self.curView = nil;
    self.ACVTabVC = [[ACVTableViewController alloc] init];
    self.ACVTabVC.delegate = self;
    self.ACVTabVC.tableView.rowHeight = 25;
    self.ACVTabVC.tableView.frame = CGRectMake(20,50, 250, 150);
    self.ACVTabVC.tableView.sectionFooterHeight = 5;
    self.ACVTabVC.tableView.sectionHeaderHeight = 5;
    self.ACVTabVC.tableView.scrollEnabled = YES;
    self.ACVTabVC.tableView.showsVerticalScrollIndicator = YES;
    self.ACVTabVC.tableView.userInteractionEnabled = YES;
    self.ACVTabVC.tableView.bounces = YES;
    self.ACVTabVC.tableView.layer.borderWidth = 1.25;
    [mainContentView addArrangedSubview:self.ACVTabVC.tableView];
    
    self.editView = [[UITextView alloc] initWithFrame:CGRectMake(20, 50, 250, 150) textContainer: nil];
    self.editView.directionalLockEnabled = NO;
    [mainContentView addArrangedSubview:self.editView];
    self.editView.hidden = true;

    UIStackView *buttonLayout = [[UIStackView alloc] init];
    // try button
    buttonLayout.axis = UILayoutConstraintAxisHorizontal;
    self.tryButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [self.tryButton setTitle:@"Try Yourself" forState:UIControlStateNormal];
    [self.tryButton setTitleColor:UIColor.blueColor forState:UIControlStateSelected];
    CGSize contentSize = [self.tryButton.titleLabel intrinsicContentSize];
    self.tryButton.frame = CGRectMake(20, 210, contentSize.width + 8, contentSize.height + 8);
    self.tryButton.backgroundColor = UIColor.lightGrayColor;
    [self.tryButton addTarget:self action:@selector(editText:)
             forControlEvents:UIControlEventTouchUpInside];
    [buttonLayout addArrangedSubview:self.tryButton];

    // apply button
    self.applyButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [self.applyButton setTitle:@"Apply" forState:UIControlStateNormal];
    [self.applyButton setTitleColor:UIColor.blueColor forState:UIControlStateSelected];
    
    self.applyButton.backgroundColor = UIColor.lightGrayColor;
    CGSize contentSize1 = [self.applyButton.titleLabel intrinsicContentSize];
    self.applyButton.frame = CGRectMake(20 + contentSize.width + 20, 210, contentSize1.width + 8, contentSize1.height + 8);
    [self.applyButton addTarget:self action:@selector(applyText:)
               forControlEvents:UIControlEventTouchUpInside];
    [buttonLayout addArrangedSubview:self.applyButton];
    //[NSLayoutConstraint activateConstraints:
    // @[[self.tryButton.trailingAnchor constraintEqualToAnchor:self.applyButton.leadingAnchor]]];
    [mainContentView addArrangedSubview:buttonLayout];
    self.scrView = [[UIScrollView alloc] init];
    [mainContentView addArrangedSubview:self.scrView];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)update:(NSString *) jsonStr
{
    self.editableStr = jsonStr;
    ACRRenderResult *renderResult;
    ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:self.hostconfig];
    ACOAdaptiveCardParseResult *cardParseResult       = [ACOAdaptiveCard fromJson:jsonStr];
    if(cardParseResult.IsValid)
    {
        renderResult = [ACRRenderer render:cardParseResult.card
                                    config:hostconfigParseResult.config
                                     frame:CGRectMake(20, 250, 300, 1250)];
    }	
    
    if(renderResult.succeeded)
    {
        ACRViewController *adcVc = renderResult.viewcontroller;
        adcVc.acrActionDelegate = self;
        if(self.curView)
            [self.curView removeFromSuperview];
        self.curView = adcVc.view;
        self.curView.frame = CGRectMake(20, 250, 300, 1250);
        [self addChildViewController:adcVc];
        [self.scrView addSubview:adcVc.view];
        [adcVc didMoveToParentViewController:self];
    }
}

- (void)fromACVTable:(ACVTableViewController *)avcTabVc userSelectedJson:(NSString *)jsonStr
{
    [self update:jsonStr];
}

- (void)source:(ACVTableViewController *)avcTabVc userconfig:(NSString *)payload
{
    self.hostconfig = payload;
}

- (void)didFetchUserResponses:(NSData *)json error:(NSError *)error
{
    if(!error && json)
    {
        NSString *str = [[NSString alloc] initWithData:json encoding:NSUTF8StringEncoding];
        NSLog(@"user response fetched: %@", str);
    }
}

- (void)didFetchHttpRequest:(NSURLRequest *)request
{
    NSLog(@"Http Request fetched: %@", request);    
}

@end
