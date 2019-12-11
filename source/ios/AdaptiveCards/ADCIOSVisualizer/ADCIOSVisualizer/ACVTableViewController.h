//
//  ACVTableViewController.h
//  ACVTableViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//
#import <UIKit/UIKit.h>
@class ACVTableViewController;

@protocol ACVTableViewControllerDelegate
- (void)fromACVTable:(ACVTableViewController *)avcTabVc
    userSelectedJson:(NSString *)jsonStr;
- (void)source:(ACVTableViewController *)avcTabVc
    userconfig:(NSString *)payload;

@end

@protocol ACVTableViewControllerFetchDataDelegate
- (void)updateTable:(NSArray<NSString *> *)data;

@end

@interface ACVTableViewController : UITableViewController <ACVTableViewControllerFetchDataDelegate>

@property (nonatomic, weak) id<ACVTableViewControllerDelegate> delegate;
@property NSString *userSelectedJSon;
@property (strong, nonatomic) NSLayoutConstraint *tableHeight;
@property BOOL IsCollapsed;

@end
