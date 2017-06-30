 //
//  ACRColumnStackView
//  ACRColumnStackView.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRColumnStackView.h"

@implementation ACRColumnStackView
#if 1
- (CGSize) intrinsicContentSize
{
    CGSize test;
    if(self.relativeColumnWidth)
        return test = CGSizeMake(self.relativeColumnWidth*3, 150);
    else
    test = super.intrinsicContentSize;
    test.width = test.width * self.relativeColumnWidth;
    return test;
}
#endif

@end
