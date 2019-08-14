//
//  ACRIMeida
//  ACRIMeida.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVKit/AVKit.h>
#import "ACOAdaptiveCard.h"
#import "ACOMediaEvent.h"

@protocol ACRMediaDelegate<NSObject>

- (void)didFetchMediaViewController:(AVPlayerViewController *)controller card:(ACOAdaptiveCard *)card;

@optional
- (void)didFetchMediaEvent:(ACOMediaEvent *)mediaElement card:(ACOAdaptiveCard *)card;

@end
