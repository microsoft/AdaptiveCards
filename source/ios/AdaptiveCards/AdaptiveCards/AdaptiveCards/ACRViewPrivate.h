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

- (void)loadImage:(NSString *)url key:(NSString *)key;
// Walk through adaptive cards elements and if images are found, download and process images concurrently and on different thread
// from main thread, so images process won't block UI thread.
- (void)addTasksToConcurrentQueue:(std::vector<std::shared_ptr<BaseCardElement>> const &) body;
// async method
- (void)loadImagesForActionsAndCheckIfAllActionsHaveIconImages:(std::vector<std::shared_ptr<BaseActionElement>> const &)actions hostconfig:(ACOHostConfig *)hostConfig;

+ (NSString *)generateKeyForElement:(std::shared_ptr<BaseCardElement> const &)elem;

+ (NSString *)generateKeyForActionElement:(std::shared_ptr<BaseActionElement> const &)elem;

@end
