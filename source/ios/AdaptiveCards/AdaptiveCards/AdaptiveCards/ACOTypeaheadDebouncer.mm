//
//  ACOTypeaheadDebouncer.mm
//  AdaptiveCards
//
//  Created by Jyoti Kukreja on 25/01/23.
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import "ACOTypeaheadDebouncer.h"

@interface ACOTypeaheadDebouncer ()
@property (nonatomic) NSTimeInterval delay;
@end

@implementation ACOTypeaheadDebouncer

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
