//
//  ViewController.h
//  ACVVisualizer
//
//  Created by jwoo on 6/2/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACVTableViewController.h"
#import <AdaptiveCards/AdaptiveCards.h>
#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <ACVTableViewControllerDelegate, ACRActionDelegate, ACRMediaDelegate, ACRIBaseActionSetRenderer>

@property (strong, nonatomic) ACVTableViewController *ACVTabVC;
@property (strong, nonatomic) UITextView *editView;
@property (strong, nonatomic) UIStackView *buttonLayout;
@property (strong, nonatomic) UIStackView *compositeFileBrowserView;
@property (strong, nonatomic) UISwitch *enableCustomRendererSwitch;
@property (strong, nonatomic) UIButton *deleteAllRowsButton;
@property (strong, nonatomic) NSString *hostconfig;
@property (strong, nonatomic) ACOHostConfig *config;
@property (strong, nonatomic) UILabel *userResponseLabel;

@property ACRView *curView;
@property UIScrollView *scrView;
@property UITableView *chatWindow;

@property UILabel *retrievedInputsTextView;

@end
