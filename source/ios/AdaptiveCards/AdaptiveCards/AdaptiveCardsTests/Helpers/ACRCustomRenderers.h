//
//  ACRCustomColumnRenderer.h
//  AdaptiveCardsTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRColumnRenderer.h"
#import "ACRContainerRenderer.h"

@protocol ACRIUnitTest

@property void (^fetchActualRenderedView) (UIView *view, NSDictionary *props);

@end

@interface ACRCustomColumnRenderer : ACRColumnRenderer<ACRIUnitTest>

+ (ACRCustomColumnRenderer *)getInstance;

@end

@interface ACRCustomContainerRenderer : ACRContainerRenderer<ACRIUnitTest>

+ (ACRCustomContainerRenderer *)getInstance;;

@end
