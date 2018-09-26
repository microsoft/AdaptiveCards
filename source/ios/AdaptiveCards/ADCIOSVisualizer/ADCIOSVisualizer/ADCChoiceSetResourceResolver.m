//
//  ADCChoiceSetResourceResolver.m
//  ADCIOSVisualizer
//
//  Created by Ankit Maurya on 9/21/18.
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ADCChoiceSetResourceResolver.h"

@implementation ADCChoiceSetResourceResolver

- (UIImage*) getRadioButtonForSelectedState{
    return [UIImage imageNamed:@"checked.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
}

- (UIImage*) getRadioButtonForUnselectedState{
    return [UIImage imageNamed:@"unchecked.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
}

- (UIImage*) getCheckBoxButtonSelectedState{
    return [UIImage imageNamed:@"checked-checkbox-24.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
}

- (UIImage*) getCheckBoxButtonUnselectedState{
    return [UIImage imageNamed:@"unchecked-checkbox-24.png" inBundle:[NSBundle bundleWithIdentifier:@"MSFT.AdaptiveCards"] compatibleWithTraitCollection:nil];
}

@end

