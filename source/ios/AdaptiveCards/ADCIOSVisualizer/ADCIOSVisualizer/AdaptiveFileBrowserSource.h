//
//  CustomActionNewType.h
//  ADCIOSVisualizer
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AdaptiveCards/ACFramework.h>
#import "ACVTableViewController.h"

@interface AdaptiveFileBrowserSource:UIView<ACRActionDelegate>

- (instancetype)initWithFrame:(CGRect)frame WithDataDelegate:(id<ACVTableViewControllerFetchDataDelegate>) delegate;

@end
