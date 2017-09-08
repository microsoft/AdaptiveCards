//
//  ACRInputNumberRenderer
//  ACRInputNumberRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRInputNumberRenderer.h"
#import "ACRContentHoldingUIView.h"
#import "ACRNumericTextField.h"
#import "NumberInput.h"

@implementation ACRInputNumberRenderer

+ (ACRInputNumberRenderer *)getInstance
{
    static ACRInputNumberRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::NumberInput;
}

- (UIView *)render:(UIView *)viewGroup
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<NumberInput> numInputBlck = std::dynamic_pointer_cast<NumberInput>(elem);
    ACRNumericTextField *numInput = [[ACRNumericTextField alloc] init];
    NSString *placeHolderStr = [NSString stringWithFormat: @"%d", numInputBlck->GetValue()];
    numInput.placeholder = placeHolderStr;
    numInput.allowsEditingTextAttributes = YES;
    numInput.borderStyle = UITextBorderStyleLine;
    numInput.keyboardType = UIKeyboardTypeNumberPad;
    numInput.min = numInputBlck->GetMin();
    numInput.max = numInputBlck->GetMax();
    
    CGSize intrinsicSz = [numInput intrinsicContentSize];
    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:CGRectMake(0, 0, intrinsicSz.width, intrinsicSz.height)];
    
    [wrappingview addSubview: numInput];
    
    [wrappingview setAlignmentForSubview: HorizontalAlignment::Left];
                                  
    if(viewGroup)
    {
        [(UIStackView *)viewGroup addArrangedSubview: wrappingview];
    }
    
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
    
    numInput.translatesAutoresizingMaskIntoConstraints = NO;
    
    [inputs addObject:numInput];
    
    return wrappingview;
}

@end
