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

- (void) viewDidLoad {

    [super viewDidLoad];
    NSString* str1 = @"{\
                          \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\
                          \"type\": \"AdaptiveCard\",\
                          \"version\": \"0.5\",\
                          \"body\": [\
                              {\
                                  \"type\": \"TextBlock\",\
                                  \"text\": \"Meow!\"\
                              }\
                          ]\
                     }";
    ADCIOSViewController* adcVc = [[ADCIOSViewController alloc] init: str1];
    [self.view addSubview: adcVc.view];
    
    [NSLayoutConstraint activateConstraints:@[[adcVc.view.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor], [adcVc.view.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor]]];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end
