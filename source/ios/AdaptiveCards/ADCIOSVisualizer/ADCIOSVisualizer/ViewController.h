//
//  ViewController.h
//  ACVVisualizer
//
//  Created by jwoo on 6/2/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ACVTableViewController.h"

@interface ViewController : UIViewController <ACVTableViewControllerDelegate>
@property (strong, nonatomic) ACVTableViewController *ACVTabVC;
@property UIView* curView;


@end

