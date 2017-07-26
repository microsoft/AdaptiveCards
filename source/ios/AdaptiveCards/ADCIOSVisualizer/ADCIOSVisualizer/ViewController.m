//
//  ViewController.m
//  ViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ViewController.h"
#import <ADCIOSFramework/ACFramework.h>

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
    self.ACVTabVC.tableView.frame = CGRectMake(20,50, 250, 150);
    self.ACVTabVC.tableView.sectionFooterHeight = 5;
    self.ACVTabVC.tableView.sectionHeaderHeight = 5;
    self.ACVTabVC.tableView.scrollEnabled = YES;
    self.ACVTabVC.tableView.showsVerticalScrollIndicator = YES;
    self.ACVTabVC.tableView.userInteractionEnabled = YES;
    self.ACVTabVC.tableView.bounces = YES;
    self.ACVTabVC.tableView.layer.borderWidth = 1.25;
    [self.view addSubview:self.ACVTabVC.tableView];
    
    self.editView = [[UITextView alloc] initWithFrame:CGRectMake(20, 50, 250, 150) textContainer: nil];
    self.editView.directionalLockEnabled = NO;
    [self.view addSubview:self.editView];
    self.editView.hidden = true;

    // try button
    self.tryButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [self.tryButton setTitle:@"Try Yourself" forState:UIControlStateNormal];
    [self.tryButton setTitleColor:UIColor.blueColor forState:UIControlStateSelected];
    CGSize contentSize = [self.tryButton.titleLabel intrinsicContentSize];
    self.tryButton.frame = CGRectMake(20, 210, contentSize.width + 8, contentSize.height + 8);
    self.tryButton.backgroundColor = UIColor.lightGrayColor;
    [self.tryButton addTarget:self action:@selector(editText:)
             forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:self.tryButton];

    // apply button
    self.applyButton = [UIButton buttonWithType:UIButtonTypeSystem];
    [self.applyButton setTitle:@"Apply" forState:UIControlStateNormal];
    [self.applyButton setTitleColor:UIColor.blueColor forState:UIControlStateSelected];
    
    self.applyButton.backgroundColor = UIColor.lightGrayColor;
    CGSize contentSize1 = [self.applyButton.titleLabel intrinsicContentSize];
    self.applyButton.frame = CGRectMake(20 + contentSize.width + 20, 210, contentSize1.width + 8, contentSize1.height + 8);
    [self.applyButton addTarget:self action:@selector(applyText:)
               forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:self.applyButton];
    [NSLayoutConstraint activateConstraints:
     @[[self.tryButton.trailingAnchor constraintEqualToAnchor:self.applyButton.leadingAnchor]]];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

- (void)update:(NSString *) jsonStr
{
    self.editableStr = jsonStr;
    ACRViewController *adcVc = [[ACRViewController alloc] init:jsonStr
                                                     withFrame:CGRectMake(20, 250, 300, 850)];
    if(self.curView)
        [self.curView removeFromSuperview];
    self.curView = adcVc.view;
    self.curView.frame = CGRectMake(20, 250, 300, 850);
    [self addChildViewController:adcVc];
    [self.view addSubview:adcVc.view];
    [adcVc didMoveToParentViewController:self];
}

- (void)fromACVTable:(ACVTableViewController *)avcTabVc userSelectedJson:(NSString *)jsonStr
{
    [self update:jsonStr];
}
@end
