//
//  ACOTypeaheadDebouncer.h
//  AdaptiveCards
//
//  Copyright © 2023 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ACOTypeaheadDebouncerDelegate <NSObject>
- (void)debouncerDidSendOutput:(id)output;
@end


/**
 @brief A helper class which implements the debounce operation.
 @discussion TSDebouncer is a helper which implements the debounce operation on
             a stream of data. e.g. When user is typing in a UITextField, each
             edit operation is pushed into the debouncer, but the debouncer will
             only perform the callback when a certain minimum time has been elapsed
             since last keystroke by the user.
 */
@interface ACOTypeaheadDebouncer<GenericType> : NSObject

@property (strong, nonatomic) id<ACOTypeaheadDebouncerDelegate> delegate;

/**
 @brief Initializes a debouncer object with given delay.
 @param delay The delay in seconds for which debouncing has to be done.
 */
- (instancetype)initWithDelay:(NSTimeInterval)delay;

/**
 @brief Posts the inputs from the input stream into the debouncer.
 */
- (void)postInput:(GenericType)input;

@end
