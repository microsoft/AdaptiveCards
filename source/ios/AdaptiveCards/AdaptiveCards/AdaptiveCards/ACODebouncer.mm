//
//  ACODebouncer.mm
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 31/10/22.
//  Copyright © 2022 Microsoft. All rights reserved.
//

#import "ACODebouncer.h"

@interface ACODebouncer ()
@property (nonatomic) NSTimeInterval delay;
@end

@implementation ACODebouncer

- (instancetype)initWithDelay:(NSTimeInterval)delay
{
    self = [super init];
    if (self) {
        _delay = delay;
    }
    return self;
}

- (void)postInput:(id)input
{
    __weak typeof(self) weakSelf = self;
    [NSObject cancelPreviousPerformRequestsWithTarget:weakSelf];
    [weakSelf performSelector:@selector(sendOutput:) withObject:input afterDelay:weakSelf.delay];
}

- (void)sendOutput:(id)output
{
    [self.delegate debouncerDidSendOutput:output];
}

@end
