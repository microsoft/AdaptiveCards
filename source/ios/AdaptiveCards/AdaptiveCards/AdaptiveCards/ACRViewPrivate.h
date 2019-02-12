//
//  ACRViewPrivate
//  ACRViewPrivate.h
//
//  Copyright © 2018 Microsoft. All rights reserved.
//
//

#import "ACRView.h"
#import "Image.h"
#import "BackgroundImage.h"
#import "SharedAdaptiveCard.h"
#include "ActionParserRegistration.h"

using namespace AdaptiveCards;

@interface ACRView()

typedef void (^ObserverActionBlock)(NSObject<ACOIResourceResolver> *resolver,
                                    NSString *key, std::shared_ptr<BaseCardElement> const &elem, NSURL *url, ACRView *rootView);

typedef void (^ObserverActionBlockForBaseAction)(NSObject<ACOIResourceResolver> *resolver,
                                    NSString *key, std::shared_ptr<BaseActionElement> const &elem, NSURL *url, ACRView *rootView);

// Walk through adaptive cards elements and if images are found, download and process images concurrently and on different thread
// from main thread, so images process won't block UI thread.
- (void)addTasksToConcurrentQueue:(std::vector<std::shared_ptr<BaseCardElement>> const &) body;
// async method
- (void)loadImagesForActionsAndCheckIfAllActionsHaveIconImages:(std::vector<std::shared_ptr<BaseActionElement>> const &)actions hostconfig:(ACOHostConfig *)hostConfig;

- (void)loadImage:(std::string const &)urlStr;

- (void)loadBackgroundImageAccordingToResourceResolverIF:(std::shared_ptr<BackgroundImage> const &)backgroundImage key:(NSString *)key observerAction:(ObserverActionBlock)observerAction;

- (void)loadImageAccordingToResourceResolverIFFromString:(std::string const &)url
    key:(NSString *)key observerAction:(ObserverActionBlock)observerAction;

- (void)loadImageAccordingToResourceResolverIF:(std::shared_ptr<BaseCardElement> const &)elem
    key:(NSString *)key observerAction:(ObserverActionBlock)observerAction;

- (std::shared_ptr<AdaptiveSharedNamespace::ActionElementParser> const &)getActionParser:(NSString*)elementType;

+ (void)renderBackgroundImageView:(const AdaptiveCards::BackgroundImage *)backgroundImageProperties containerView:(UIView *)containerView rootView:(UIView *)rootView;

+ (void)applyBackgroundImageConstraints:(const AdaptiveCards::BackgroundImage *)backgroundImageProperties imageView:(UIView *)imageView;
@end
