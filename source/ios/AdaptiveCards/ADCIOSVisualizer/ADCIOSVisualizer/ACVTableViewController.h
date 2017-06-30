//
//  ACVTableViewController.h
//  ACVTableViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <UIKit/UIKit.h>
@class ACVTableViewController;

@protocol ACVTableViewControllerDelegate
- (void) fromACVTable: (ACVTableViewController *) avcTabVc
     userSelectedJson: (NSString*) jsonStr;
@end

@interface ACVTableViewController: UITableViewController

@property (nonatomic, weak) id <ACVTableViewControllerDelegate> delegate;

@end

