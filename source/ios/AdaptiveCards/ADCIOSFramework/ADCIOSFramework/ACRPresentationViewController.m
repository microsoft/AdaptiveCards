//
//  ACRPresentationViewController.m
//  ADCIOS
//
//  Created by jwoo on 5/31/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ACRPresentationViewController.h"
#import "ACRViewController.h"

@implementation ACRPresentationViewController

- (id) init:(NSString*) str{
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
        
        [self.view addSubview: acVc.view];
    
        [NSLayoutConstraint activateConstraints:@[[acVc.view.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor], [acVc.view.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor]]];
    }
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end
