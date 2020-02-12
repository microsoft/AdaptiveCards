//
//  ViewController.h
//  ACVVisualizer
//
//  Created by jwoo on 6/2/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACVTableViewController.h"
#import <AdaptiveCards/ACFramework.h>
#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <ACVTableViewControllerDelegate, ACRActionDelegate, ACRMediaDelegate, ACRIBaseActionSetRenderer>

@property (strong, nonatomic) ACOHostConfig *config;
@property (strong, nonatomic) UILabel *userResponseLabel;
@property ACRView *curView;
@property UIScrollView *scrView;

@property (strong, nonatomic) NSMutableArray *adaptiveCards;

@property (strong, nonatomic) UIView *lastRenderedView;

@end
