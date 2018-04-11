//
//  ViewController.h
//  ACVVisualizer
//
//  Created by jwoo on 6/2/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACVTableViewController.h"
#import <AdaptiveCards/ACFramework.h>

@interface ViewController:UIViewController <ACVTableViewControllerDelegate, ACRActionDelegate>

@property (strong, nonatomic) ACVTableViewController *ACVTabVC;
@property (strong, nonatomic) UITextView *editView;
@property (strong, nonatomic) UIStackView *buttonLayout;
@property (strong, nonatomic) UIButton *tryButton;
@property (strong, nonatomic) UIButton *applyButton;
@property (strong, nonatomic) NSString *editableStr;
@property (strong, nonatomic) NSString *hostconfig;
@property UIView *curView;
@property UIScrollView *scrView;

@end

