//
//  ACRViewPrivate
//  ACRViewPrivate.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
//

#import "ACRView.h"
#import "SharedAdaptiveCard.h"

@interface ACRView()

// Walk through adaptive cards elements and if images are found, download and process images concurrently and on different thread
// from main thread, so images process won't block UI thread.
- (void) addTasksToConcurrentQueue:(std::vector<std::shared_ptr<BaseCardElement>> const &) body;
@end
