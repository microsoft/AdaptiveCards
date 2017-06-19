//
//  ViewController.m
//  ADCIOSVisualizer
//
//  Created by jwoo on 6/2/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ViewController.h"
#import <ADCIOSFramework/ACFramework.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    _idx = 3;
    _inputs = @[@"{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\n\
                \"type\": \"AdaptiveCard\",\n\
                \"version\": \"0.5\",\n\
                \"body\": [\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"Meow!\"\n\
                }\n\
                ]\n\
                }",
                @"{\n\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\n\
                \"type\": \"AdaptiveCard\",\n\
                \"version\": \"0.5\",\n\
                \"body\": [\n\
                {\
                \"type\": \"TextBlock\",\n\
                \"text\": \"size:default\"\n\
                },\
                {\
                \"type\": \"TextBlock\",\n\
                \"text\": \"size:small\",\n\
                \"size\": \"small\"\n\
                },\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"size:normal\",\n\
                \"size\": \"normal\"\n\
                },\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"size:medium\",\n\
                \"size\": \"medium\"\n\
                },\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"size:large\",\n\
                \"size\": \"large\"\n\
                },\n\
                {\
                \"type\": \"TextBlock\",\n\
                \"text\": \"size:extraLarge\",\n\
                \"size\": \"extraLarge\"\n\
                }\n\
                ]\n\
                }",
                @"{\n\
                \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\n\
                \"type\": \"AdaptiveCard\",\n\
                \"version\": \"0.5\",\n\
                \"body\": [\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"color:default\",\n\
                \"color\": \"default\"\n\
                },\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"color:accent\",\n\
                \"color\": \"accent\"\n\
                },\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"color:good\",\n\
                \"color\": \"good\"\n\
                },\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"color:warning\",\n\
                \"color\": \"warning\"\n\
                },\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"color:attention\",\n\
                \"color\": \"attention\"\n\
                },\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"color:light\",\n\
                \"color\": \"light\"\n\
                },\n\
                {\n\
                \"type\": \"TextBlock\",\n\
                \"text\": \"color:dark\",\n\
                \"color\": \"dark\"\n\
                }\n\
                ]\n\
                }",
                @"{\
                \"$schema\":\"http://adaptivecards.io/schemas/adaptive-card.json\",\n\
                \"type\": \"AdaptiveCard\",\n\
                \"version\": \"0.5\",\n\
                \"body\": [\n\
                {\n\
                \"type\": \"Image\",\n\
                \"url\": \"https://connectorsdemo.azurewebsites.net/images/MSC12_Oscar_002.jpg\",\n\
                \"size\": \"large\",\n\
                \"style\": \"person\",\n\
                \"horizontalAlignment\": \"left\"\
                }\n\
                ]\n\
                }",

                ];

    self.JSLab = [[UILabel alloc] init];
    self.JSLab.numberOfLines = 50;
    [self.JSLab setFont:[UIFont systemFontOfSize:8]];
    self.JSLab.lineBreakMode = NSLineBreakByTruncatingTail;
    self.JSLab.text = self.inputs[self.idx];
   
    ACRViewController* adcVc = [[ACRViewController alloc] init: self.inputs[self.idx]];
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(changeView:) forControlEvents:UIControlEventTouchUpInside];
    [button setTitle:@"Show View" forState:UIControlStateNormal];
    button.backgroundColor = [UIColor grayColor];
    button.frame = CGRectMake(40.0, 200.0, 80.0, 20.0);
    [self.StkView addArrangedSubview:button];
    [self.StkView addArrangedSubview:self.JSLab];
    [self.StkView addArrangedSubview:adcVc.view];
    self.curView = adcVc.view;
}

- (void) changeView: (id) sender {
    
    self.idx = self.idx + 1;
    self.idx = self.idx % 4;
    self.JSLab.text = self.inputs[self.idx];
    [self.StkView removeArrangedSubview:self.curView];
    [self.curView removeFromSuperview];

    ACRViewController* adcVc = [[ACRViewController alloc] init: self.inputs[self.idx]];
    self.curView = adcVc.view;
    [self.StkView addArrangedSubview: self.curView];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


@end
