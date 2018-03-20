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

@interface ViewController ()

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
    scrollview.showsVerticalScrollIndicator = YES;
    UIView *view = self.curView;
    view.translatesAutoresizingMaskIntoConstraints = NO;
    scrollview.translatesAutoresizingMaskIntoConstraints = NO;

    NSDictionary *viewMap = NSDictionaryOfVariableBindings(ACVTabView, scrollview, buttonLayout);
    NSArray<NSString *> *formats = 
        [NSArray arrayWithObjects:@"H:|-[ACVTabView]-|",   
                              @"V:|-40-[ACVTabView(==200)]-[buttonLayout]-[scrollview]-20-|",
         @"H:|-[buttonLayout]-|", @"H:|-[scrollview]-|", nil];
    [ViewController applyConstraints:formats variables:viewMap];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)update:(NSString *) jsonStr
{
    self.editableStr = jsonStr;
    ACRRenderResult *renderResult;
    ACOHostConfigParseResult *hostconfigParseResult = [ACOHostConfig fromJson:self.hostconfig];
    ACOAdaptiveCardParseResult *cardParseResult = [ACOAdaptiveCard fromJson:jsonStr];
    if(cardParseResult.isValid){
        renderResult = [ACRRenderer render:cardParseResult.card config:hostconfigParseResult.config frame:CGRectMake(0, 0, 500, 0)];
    }	
    
    if(renderResult.succeeded)
    {
        ACRRegistration *registration = [ACRRegistration getInstance];
        // enum will be part of API in next iterations when custom renderer extended to non-action type - tracked by issue #809 
        [registration setActionRenderer:[CustomActionOpenURLRenderer getInstance] cardElementType:@3];
        [registration setBaseCardElementRenderer:[CustomInputNumberRenderer getInstance] cardElementType:ACRNumberInput];

        CustomProgressBarRenderer *progressBarRenderer = [[CustomProgressBarRenderer alloc] init];
        [registration setCustomElementParser:progressBarRenderer];
        ACRView *ad = renderResult.view;
        ad.acrActionDelegate = self;
        if(self.curView)
            [self.curView removeFromSuperview];
        else
        {
            self.scrView = [[UIScrollView alloc] initWithFrame:CGRectMake(0,0,0,0)];
            self.scrView.showsHorizontalScrollIndicator = YES;
        }
        self.curView = ad;
        [self.scrView addSubview:ad];
        self.scrView.contentSize = self.curView.frame.size;
        self.scrView.translatesAutoresizingMaskIntoConstraints = NO;
        UIScrollView *scrollview = self.scrView;
        UIView *view = self.curView;
        view.translatesAutoresizingMaskIntoConstraints = NO;
        scrollview.translatesAutoresizingMaskIntoConstraints = NO;
        NSDictionary *viewMap = NSDictionaryOfVariableBindings(view, scrollview);
        NSArray<NSString *> *formats = [NSArray arrayWithObjects:@"H:|[view(<=scrollview)]|", @"V:|[view(>=scrollview)]|",nil];
        [ViewController applyConstraints:formats variables:viewMap];
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

- (void) didFetchUserResponses:(ACOAdaptiveCard *)card action:(ACOBaseActionElement *)action
{
    if(action.type == ACROpenUrl){
        NSURL *url = [NSURL URLWithString:[action url]];
        SFSafariViewController *svc = [[SFSafariViewController alloc] initWithURL:url];
        [self presentViewController:svc animated:YES completion:nil];
    }
    else if(action.type == ACRSubmit){
        NSData * userInputsAsJson = [card inputs];
        NSString *str = [[NSString alloc] initWithData:userInputsAsJson encoding:NSUTF8StringEncoding];
        NSLog(@"user response fetched: %@ with %@", str, [action data]);
    }
}

- (void)didFetchSecondaryView:(ACOAdaptiveCard *)card navigationController:(UINavigationController *)navigationController{
    [self presentViewController:navigationController animated:YES completion:nil];
}

- (void)didFetchUserResponses:(NSData *)json error:(NSError *)error
{
    if(!error && json)
    {
        NSString *str = [[NSString alloc] initWithData:json encoding:NSUTF8StringEncoding];
        NSLog(@"user response fetched: %@", str);
    }
}

- (void)didFetchUserResponses:(NSData *)json data:(NSString *) data error:(NSError *)error
{
    if(!error && json && data)
    {
        NSString *str = [[NSString alloc] initWithData:json encoding:NSUTF8StringEncoding];
        NSLog(@"user response fetched: %@ with %@", str, data);
    }
}

- (void)didFetchHttpRequest:(NSURLRequest *)request
{
    NSLog(@"Http Request fetched: %@", request);    
}

- (void)didLoadElements
{
    NSLog(@"didLoadElements");
}

- (void)registerForKeyboardNotifications
{
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWasShown:)
                                                 name:UIKeyboardDidShowNotification object:nil];

    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardWillBeHidden:)
                                                 name:UIKeyboardWillHideNotification object:nil];

}
// Called when the UIKeyboardDidShowNotification is sent.
- (void)keyboardWasShown:(NSNotification*)aNotification
{
    NSDictionary* info = [aNotification userInfo];
    CGSize kbSize = [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;

    UIEdgeInsets contentInsets = UIEdgeInsetsMake(0.0, 0.0, kbSize.height, 0.0);
    self.scrView.contentInset = contentInsets;
    self.scrView.scrollIndicatorInsets = contentInsets;
}

// Called when the UIKeyboardWillHideNotification is sent
- (void)keyboardWillBeHidden:(NSNotification*)aNotification
{
    UIEdgeInsets contentInsets = UIEdgeInsetsZero;
    self.scrView.contentInset = contentInsets;
    self.scrView.scrollIndicatorInsets = contentInsets;
}

@end
