//
//  ADCIOSPresentationViewController.m
//  ADCIOS
//
//  Created by jwoo on 5/31/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ADCIOSPresentationViewController.h"
#import "ADCIOSViewController.h"

@implementation ADCIOSPresentationViewController

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
        ADCIOSViewController* adcVc = [[ADCIOSViewController alloc] init: self.jsonStr];
        
        [self.view addSubview: adcVc.view];
    
        [NSLayoutConstraint activateConstraints:@[[adcVc.view.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor], [adcVc.view.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor]]];
    }
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end
