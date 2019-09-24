//
//  CustomActionNewType.h
//  ADCIOSVisualizer
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "ACVTableViewController.h"
#import <AdaptiveCards/ACFramework.h>
#import <Foundation/Foundation.h>

@interface AdaptiveFileBrowserSource : UIView <ACRActionDelegate>

- (instancetype)initWithFrame:(CGRect)frame WithDataDelegate:(id<ACVTableViewControllerFetchDataDelegate>)delegate;

@end
