//
//  ViewController.m
//  ADCIOSVisualizer
//
//  Created by jwoo on 6/2/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ViewController.h"
#import <ADCIOSFramework/ADCIOSFramework.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    ADCIOSPresentationViewController* adcVc = [[ADCIOSPresentationViewController alloc] init];
    [self.view addSubview: adcVc.view];
    
    [NSLayoutConstraint activateConstraints:@[[adcVc.view.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor], [adcVc.view.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor]]];
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
