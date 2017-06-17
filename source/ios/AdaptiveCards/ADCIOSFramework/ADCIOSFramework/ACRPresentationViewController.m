//
//  ACRPresentationViewController.m
//  ACRPresentationViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRPresentationViewController.h"
#import "ACRViewController.h"

@implementation ACRPresentationViewController

- (instancetype) init:(NSString*) str{
    self = [super init];
    
    if(self){
        _jsonStr = nil;
        _jsonStr = str;
    }
    
    return self;
}

- (void) viewDidLoad {

    [super viewDidLoad];
    
    if(self.jsonStr){
        ACRViewController* acVc = [[ACRViewController alloc] init: self.jsonStr];

        [self addChildViewController:acVc];
        
        [self.view addSubview: acVc.view];

        [acVc didMoveToParentViewController:self];
    
        [NSLayoutConstraint activateConstraints:@[[acVc.view.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor], [acVc.view.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor]]];
    }
}

@end
