//
//  CustomTextBlockRenderer
//  CustomTextBlockRenderer.mm
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "CustomTextBlockRenderer.h"
#import <AdaptiveCards/ACFramework.h>
#import <AdaptiveCards/SharedAdaptiveCard.h>
#import <AdaptiveCards/TextBlock.h>
#import <AdaptiveCards/ACRTextBlockRenderer.h>
#import <AdaptiveCards/ACOBaseCardElementPrivate.h>



@implementation CustomTextBlockRenderer

+ (CustomTextBlockRenderer *)getInstance
{
    static CustomTextBlockRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

- (UIView *)render:(UIView<ACRIContentHoldingView> *)viewGroup
            rootView:(ACRView *)rootView
            inputs:(NSArray *)inputs
   baseCardElement:(ACOBaseCardElement *)acoElem
        hostConfig:(ACOHostConfig *)acoConfig
{
    ACRTextBlockRenderer *defaultRenderer = [ACRTextBlockRenderer getInstance];
    
    std::shared_ptr<BaseCardElement> elem = [acoElem element];
    std::shared_ptr<TextBlock> textBlockElem = std::static_pointer_cast<TextBlock>(elem);
    
    textBlockElem->SetText("shared object shared complete");

    UIView *input = [defaultRenderer render:viewGroup
                                   rootView:rootView
                                     inputs:inputs
                            baseCardElement:acoElem
                                 hostConfig:acoConfig];
    
    return input;
}
@end
