//
//  ACRMockViews.h
//  AdaptiveCardsTests
//
//  Copyright © 2021 Microsoft. All rights reserved.
//

#import "ACRContentStackView.h"
#import "ACREnums.h"
#import "ACRViewPrivate.h"
#import "MockContext.h"

@class ACOVisibilityManager;

@interface MockACRView : ACRView

@property (nonatomic) MockContext *mockContext;

@end

@interface ACRMockContentStackView : ACRContentStackView

- (ACOVisibilityManager *)getVisibilityManager;

- (ACOFillerSpaceManager *)getFillerSpaceManager;
@end
