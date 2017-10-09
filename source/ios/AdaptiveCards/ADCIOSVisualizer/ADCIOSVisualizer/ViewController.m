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

    /* disabled for current commits -jwoo
    //self.editView = [[UITextView alloc] initWithFrame:CGRectMake(0, 0, 0, 0) textContainer: nil];
    self.editView.directionalLockEnabled = NO;
    self.editView.hidden = true;
     */

    UIStackView *buttonLayout = [[UIStackView alloc] init];
    // try button
    buttonLayout.axis = UILayoutConstraintAxisHorizontal;
    self.tryButton = [UIButton buttonWithType:UIButtonTypeSystem];
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

    
    [self.applyButton addTarget:self action:@selector(applyText:)
               forControlEvents:UIControlEventTouchUpInside];
    [buttonLayout addArrangedSubview:self.applyButton];
    [self.view addSubview:buttonLayout];
    buttonLayout.translatesAutoresizingMaskIntoConstraints = NO;
    buttonLayout.alignment = UIStackViewAlignmentLeading;
    buttonLayout.distribution = UIStackViewDistributionFillEqually;
    [self update:self.ACVTabVC.userSelectedJSon];
    
    [self.view addSubview:self.scrView];
    [self.scrView addSubview:self.curView];
    UIScrollView *scrollview = self.scrView;
    UIView *view = self.curView;
    view.translatesAutoresizingMaskIntoConstraints = NO;
    scrollview.translatesAutoresizingMaskIntoConstraints = NO;

    NSDictionary *viewMap = NSDictionaryOfVariableBindings(ACVTabView, view, scrollview, buttonLayout);
    NSArray<NSString *> *formats = 
        [NSArray arrayWithObjects:@"H:|-[ACVTabView]-|", 
                              @"V:|-40-[ACVTabView(>=150,<=200)]-[buttonLayout]-[scrollview(>=100)]-|",
         @"H:|-[buttonLayout]-|", @"H:|-[scrollview]-|", @"H:|-10-[view(<=scrollview)]-10-|", @"V:|-[view(>=scrollview)]",nil];
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
                                     frame:CGRectMake(0, 0, 200, 0)];
    }	
    
    if(renderResult.succeeded)
    {
        ACRViewController *adcVc = renderResult.viewcontroller;
        adcVc.acrActionDelegate = self;
        if(self.curView)
            [self.curView removeFromSuperview];
        else
        {
            self.scrView = [[UIScrollView alloc] initWithFrame:CGRectMake(0,0,0,0)];
            self.scrView.showsHorizontalScrollIndicator = YES;
        }
        self.curView = adcVc.view;
        self.scrView.translatesAutoresizingMaskIntoConstraints = NO;
        
        //self.curView.frame = CGRectMake(0, 0, 0, 0);
        [self addChildViewController:adcVc];
        [self.scrView addSubview:adcVc.view];
        [adcVc didMoveToParentViewController:self];
        self.scrView.contentSize = self.curView.frame.size;
        
        UIScrollView *scrollview = self.scrView;
        UIView *view = self.curView;
        view.translatesAutoresizingMaskIntoConstraints = NO;
        scrollview.translatesAutoresizingMaskIntoConstraints = NO;
        
        NSDictionary *viewMap = NSDictionaryOfVariableBindings(view, scrollview);
        NSArray<NSString *> *formats =
        [NSArray arrayWithObjects:@"H:|-10-[view(<=scrollview)]-10-|", @"V:|-[view(>=scrollview)]-|",nil];
        NSArray<NSLayoutConstraint *> *constraints = nil;
        
        
        for(NSString *format in formats)
        {
            constraints = [NSLayoutConstraint constraintsWithVisualFormat:format
                                                                  options:0
                                                                  metrics:nil
                                                                    views:viewMap]; 
            [NSLayoutConstraint activateConstraints:constraints];
        }
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
