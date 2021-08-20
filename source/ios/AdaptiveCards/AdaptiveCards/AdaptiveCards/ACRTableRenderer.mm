//
//  ACRTableRenderer
//  ACRTableRenderer.mm
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRTableRenderer.h"
#import "ACRTableView.h"

@implementation ACRTableRenderer

+ (ACRTableRenderer *)getInstance
{
    static ACRTableRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (ACRCardElementType)elemType
{
    return ACRTable;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
           rootView:(ACRView *)rootView
             inputs:(NSMutableArray *)inputs
    baseCardElement:(ACOBaseCardElement *)acoElem
         hostConfig:(ACOHostConfig *)acoConfig;
{
    [rootView.context pushBaseCardElementContext:acoElem];
    ACRTableView *tableView = [[ACRTableView alloc] init:acoElem
                                               viewGroup:viewGroup
                                                rootView:rootView
                                                  inputs:inputs
                                              hostConfig:acoConfig];
    [rootView.context popBaseCardElementContext:acoElem];

    return tableView;
}

@end
