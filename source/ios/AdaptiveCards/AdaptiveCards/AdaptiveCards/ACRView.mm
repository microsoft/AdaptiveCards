//
//  ACRView.m
//  ACRView
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACOAdaptiveCardPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRButton.h"
#import "ACRContentHoldingUIView.h"
#import "ACRIBaseCardElementRenderer.h"
#import "ACRImageRenderer.h"
#import "ACRRegistration.h"
#import "ACRRendererPrivate.h"
#import "ACRTextBlockRenderer.h"
#import "ACRUIImageView.h"
#import "ACRUILabel.h"
#import "ACRViewPrivate.h"
#import "AdaptiveBase64Util.h"
#import "BackgroundImage.h"
#import "Column.h"
#import "ColumnSet.h"
#import "Container.h"
#import "Enums.h"
#import "Fact.h"
#import "FactSet.h"
#import "ImageSet.h"
#import "MarkDownParser.h"
#import "Media.h"
#import "RichTextBlock.h"
#import "RichTextElementProperties.h"
#import "SharedAdaptiveCard.h"
#import "TextBlock.h"
#import "TextInput.h"
#import "TextRun.h"
#import "UtiliOS.h"
#import <AVFoundation/AVFoundation.h>

using namespace AdaptiveCards;
typedef UIImage * (^ImageLoadBlock)(NSURL *url);

@implementation ACRView {
    ACOAdaptiveCard *_adaptiveCard;
    ACOHostConfig *_hostConfig;
    NSMutableDictionary *_imageViewMap;
    NSMutableDictionary *_textMap;
    dispatch_queue_t _serial_queue;
    dispatch_queue_t _serial_text_queue;
    dispatch_queue_t _global_queue;
    dispatch_group_t _async_tasks_group;
    int _serialNumber;
    int _numberOfSubscribers;
    NSMutableDictionary *_imageContextMap;
    NSMutableDictionary *_imageViewContextMap;
    NSMutableSet *_setOfRemovedObservers;
    NSMutableDictionary<NSString *, UIView *> *_paddingMap;
    ACRTargetBuilderDirector *_actionsTargetBuilderDirector;
    ACRTargetBuilderDirector *_selectActionsTargetBuilderDirector;
    ACRTargetBuilderDirector *_quickReplyTargetBuilderDirector;
    NSMapTable<ACRColumnView *, ACRColumnView *> *_inputHandlerLookupTable;
    NSMutableArray<ACRColumnView *> *_showcards;
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        std::shared_ptr<HostConfig> cHostConfig = std::make_shared<HostConfig>();
        _hostConfig = [[ACOHostConfig alloc] initWithConfig:cHostConfig];
        _imageViewMap = [[NSMutableDictionary alloc] init];
        _textMap = [[NSMutableDictionary alloc] init];
        _serial_queue = dispatch_queue_create("io.adaptiveCards.serial_queue", DISPATCH_QUEUE_SERIAL);
        _serial_text_queue = dispatch_queue_create("io.adaptiveCards.serial_text_queue", DISPATCH_QUEUE_SERIAL);
        _global_queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        _async_tasks_group = dispatch_group_create();
        _serialNumber = 0;
        _imageContextMap = [[NSMutableDictionary alloc] init];
        _imageViewContextMap = [[NSMutableDictionary alloc] init];
        _setOfRemovedObservers = [[NSMutableSet alloc] init];
        _paddingMap = [[NSMutableDictionary alloc] init];
        _inputHandlerLookupTable = [[NSMapTable alloc] initWithKeyOptions:NSMapTableWeakMemory valueOptions:NSMapTableWeakMemory capacity:5];
        _showcards = [[NSMutableArray alloc] init];
    }
    return self;
}

- (instancetype)init:(ACOAdaptiveCard *)card
          hostconfig:(ACOHostConfig *)config
     widthConstraint:(float)width
            delegate:(id<ACRActionDelegate>)acrActionDelegate
{
    self = [self initWithFrame:CGRectMake(0, 0, width, 0)];
    if (self) {
        self.accessibilityLabel = @"ACR Root View";
        _adaptiveCard = card;
        _warnings = [[NSMutableArray<ACOWarning *> alloc] init];
        // override default host config if user host config is provided
        if (config) {
            _hostConfig = config;
        }
        _actionsTargetBuilderDirector = [[ACRTargetBuilderDirector alloc] init:self capability:ACRAction adaptiveHostConfig:_hostConfig];
        _selectActionsTargetBuilderDirector = [[ACRTargetBuilderDirector alloc] init:self capability:ACRSelectAction adaptiveHostConfig:_hostConfig];
        _quickReplyTargetBuilderDirector = [[ACRTargetBuilderDirector alloc] init:self capability:ACRQuickReply adaptiveHostConfig:_hostConfig];
        unsigned int padding = [_hostConfig getHostConfig] -> GetSpacing().paddingSpacing;
        [self removeConstraints:self.constraints];
        if (padding) {
            [self applyPadding:padding priority:1000];
        }
        self.acrActionDelegate = acrActionDelegate;
        [self render];
    }
    return self;
}

// Initializes ACRView instance with HostConfig and AdaptiveCard
- (instancetype)init:(ACOAdaptiveCard *)card
          hostconfig:(ACOHostConfig *)config
     widthConstraint:(float)width
{
    self = [self init:card hostconfig:config widthConstraint:width delegate:nil];
    return self;
}

- (UIView *)render
{
    if (self.frame.size.width) {
        [NSLayoutConstraint constraintWithItem:self attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:self.frame.size.width].active = YES;
    }

    [self pushCurrentShowcard:self];
    [self setParent:nil child:self];

    UIView *newView = [ACRRenderer renderWithAdaptiveCards:[_adaptiveCard card] inputs:self.inputHandlers context:self containingView:self hostconfig:_hostConfig];

    [self popCurrentShowcard];

    ContainerStyle style = ([_hostConfig getHostConfig] -> GetAdaptiveCard().allowCustomStyle) ? [_adaptiveCard card] -> GetStyle() : ContainerStyle::Default;

    newView.backgroundColor = [_hostConfig getBackgroundColorForContainerStyle:
                                               [ACOHostConfig getPlatformContainerStyle:style]];

    renderBackgroundImage([_adaptiveCard card] -> GetBackgroundImage(), newView, self);

    [self callDidLoadElementsIfNeeded];

    return newView;
}

- (void)waitForAsyncTasksToFinish
{
    dispatch_group_wait(_async_tasks_group, DISPATCH_TIME_FOREVER);
    [self callDidLoadElementsIfNeeded];
}

- (void)callDidLoadElementsIfNeeded
{
    // Call back app with didLoadElements
    if ([[self acrActionDelegate] respondsToSelector:@selector(didLoadElements)] && !_numberOfSubscribers) {
        [[self acrActionDelegate] didLoadElements];
    }
}

- (void)processBaseCardElement:(std::shared_ptr<BaseCardElement> const &)elem
{
    switch (elem->GetElementType()) {
        case CardElementType::TextBlock: {
            std::shared_ptr<TextBlock> textBlockElement = std::static_pointer_cast<TextBlock>(elem);
            RichTextElementProperties textProp;
            TextBlockToRichTextElementProperties(textBlockElement, textProp);

            /// tag a base card element with unique key
            NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)textBlockElement.get()];
            NSString *key = [number stringValue];
            [self processTextConcurrently:textProp elementId:key];
            break;
        }
        case CardElementType::RichTextBlock: {
            std::shared_ptr<RichTextBlock> rTxtBlkElement = std::static_pointer_cast<RichTextBlock>(elem);
            for (const auto &inlineText : rTxtBlkElement->GetInlines()) {
                std::shared_ptr<TextRun> textRun = std::static_pointer_cast<TextRun>(inlineText);
                if (textRun) {
                    RichTextElementProperties textProp;
                    TextRunToRichTextElementProperties(textRun, textProp);
                    NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)textRun.get()];
                    NSString *key = [number stringValue];
                    [self processTextConcurrently:textProp elementId:key];
                }
            }
            break;
        }
        case CardElementType::FactSet: {
            [self tagBaseCardElement:elem];
            std::shared_ptr<FactSet> factSet = std::dynamic_pointer_cast<FactSet>(elem);
            NSString *key = [NSString stringWithCString:elem->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
            key = [key stringByAppendingString:@"*"];
            int rowFactId = 0;
            for (auto fact : factSet->GetFacts()) {

                RichTextElementProperties titleTextProp{[_hostConfig getHostConfig] -> GetFactSet().title, fact->GetTitle(), fact->GetLanguage()};
                [self processTextConcurrently:titleTextProp
                                    elementId:[key stringByAppendingString:[[NSNumber numberWithInt:rowFactId++] stringValue]]];


                RichTextElementProperties valueTextProp{[_hostConfig getHostConfig] -> GetFactSet().value, fact->GetValue(), fact->GetLanguage()};
                [self processTextConcurrently:valueTextProp
                                    elementId:[key stringByAppendingString:[[NSNumber numberWithInt:rowFactId++] stringValue]]];
            }
            break;
        }
        case CardElementType::Image: {

            ObserverActionBlock observerAction =
                ^(NSObject<ACOIResourceResolver> *imageResourceResolver, NSString *key, std::shared_ptr<BaseCardElement> const &elem, NSURL *url, ACRView *rootView) {
                    UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                    if (view) {
                        // check image already exists in the returned image view and register the image
                        [self registerImageFromUIImageView:view key:key];
                        [view addObserver:self
                               forKeyPath:@"image"
                                  options:NSKeyValueObservingOptionNew
                                  context:elem.get()];

                        // store the image view and image element for easy retrieval in ACRView::observeValueForKeyPath
                        [rootView setImageView:key view:view];
                        [rootView setImageContext:key context:elem];
                    }
                };
            [self loadImageAccordingToResourceResolverIF:elem key:nil observerAction:observerAction];

            break;
        }
        case CardElementType::ImageSet: {
            std::shared_ptr<ImageSet> imgSetElem = std::static_pointer_cast<ImageSet>(elem);
            for (auto img : imgSetElem->GetImages()) { // loops through images in image set
                std::shared_ptr<BaseCardElement> baseImgElem = std::static_pointer_cast<BaseCardElement>(img);
                img->SetImageSize(imgSetElem->GetImageSize());

                ObserverActionBlock observerAction =
                    ^(NSObject<ACOIResourceResolver> *imageResourceResolver, NSString *key, std::shared_ptr<BaseCardElement> const &elem, NSURL *url, ACRView *rootView) {
                        UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                        if (view) {
                            // check image already exists in the returned image view and register the image
                            [self registerImageFromUIImageView:view key:key];
                            [view addObserver:self
                                   forKeyPath:@"image"
                                      options:NSKeyValueObservingOptionNew
                                      context:elem.get()];

                            // store the image view and image set element for easy retrieval in ACRView::observeValueForKeyPath
                            [rootView setImageView:key view:view];
                            [rootView setImageContext:key context:elem];
                        }
                    };

                [self loadImageAccordingToResourceResolverIF:baseImgElem key:nil observerAction:observerAction];
            }
            break;
        }
        case CardElementType::Media: {
            std::shared_ptr<Media> mediaElem = std::static_pointer_cast<Media>(elem);
            std::string poster = mediaElem->GetPoster();
            if (poster.empty()) {
                poster = [_hostConfig getHostConfig] -> GetMedia().defaultPoster;
            }

            if (!poster.empty()) {
                ObserverActionBlock observerAction =
                    ^(NSObject<ACOIResourceResolver> *imageResourceResolver, NSString *key, std::shared_ptr<BaseCardElement> const &imgElem, NSURL *url, ACRView *rootView) {
                        UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                        ACRContentHoldingUIView *contentholdingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];
                        if (view) {
                            // check image already exists in the returned image view and register the image
                            [self registerImageFromUIImageView:view key:key];
                            [contentholdingview addSubview:view];
                            contentholdingview.isMediaType = YES;
                            [view addObserver:self
                                   forKeyPath:@"image"
                                      options:NSKeyValueObservingOptionNew
                                      context:elem.get()];

                            // store the image view and media element for easy retrieval in ACRView::observeValueForKeyPath
                            [rootView setImageView:key view:contentholdingview];
                            [rootView setImageContext:key context:elem];
                        }
                    };
                [self loadImageAccordingToResourceResolverIF:elem key:nil observerAction:observerAction];
            }

            if (![_hostConfig getHostConfig] -> GetMedia().playButton.empty()) {
                ObserverActionBlock observerAction =
                    ^(NSObject<ACOIResourceResolver> *imageResourceResolver, NSString *key, std::shared_ptr<BaseCardElement> const &elem, NSURL *url, ACRView *rootView) {
                        UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                        if (view) {
                            // check image already exists in the returned image view and register the image
                            [self registerImageFromUIImageView:view key:key];
                            [view addObserver:rootView
                                   forKeyPath:@"image"
                                      options:NSKeyValueObservingOptionNew
                                      context:nil];
                            // store the image view for easy retrieval in ACRView::observeValueForKeyPath
                            [rootView setImageView:key view:view];
                        }
                    };

                NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)elem.get()];
                NSString *key = [NSString stringWithFormat:@"%@_%@", [number stringValue], @"playIcon"];

                [self loadImageAccordingToResourceResolverIFFromString:[_hostConfig getHostConfig] -> GetMedia().playButton key:key observerAction:observerAction];
            }

            break;
        }
        case CardElementType::TextInput: {
            std::shared_ptr<TextInput> textInput = std::static_pointer_cast<TextInput>(elem);
            std::shared_ptr<BaseActionElement> action = textInput->GetInlineAction();
            if (action != nullptr && !action->GetIconUrl().empty()) {
                ObserverActionBlockForBaseAction observerAction =
                    ^(NSObject<ACOIResourceResolver> *imageResourceResolver, NSString *key, std::shared_ptr<BaseActionElement> const &elem, NSURL *url, ACRView *rootView) {
                        UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                        if (view) {
                            [view addObserver:self
                                   forKeyPath:@"image"
                                      options:NSKeyValueObservingOptionNew
                                      context:elem.get()];

                            // store the image view for easy retrieval in ACRView::observeValueForKeyPath
                            [rootView setImageView:key view:view];
                        }
                    };
                [self loadImageAccordingToResourceResolverIFForBaseAction:action key:nil observerAction:observerAction];
            }
            break;
        }
        // continue on search
        case CardElementType::Container: {
            std::shared_ptr<Container> container = std::static_pointer_cast<Container>(elem);

            auto backgroundImageProperties = container->GetBackgroundImage();
            if ((backgroundImageProperties != nullptr) && !(backgroundImageProperties->GetUrl().empty())) {
                ObserverActionBlock observerAction = generateBackgroundImageObserverAction(backgroundImageProperties, self, container);
                [self loadBackgroundImageAccordingToResourceResolverIF:backgroundImageProperties key:nil observerAction:observerAction];
            }

            std::vector<std::shared_ptr<BaseCardElement>> &new_body = container->GetItems();
            [self addTasksToConcurrentQueue:new_body];
            break;
        }
        // continue on search
        case CardElementType::ColumnSet: {
            std::shared_ptr<ColumnSet> columSet = std::static_pointer_cast<ColumnSet>(elem);
            std::vector<std::shared_ptr<Column>> &columns = columSet->GetColumns();
            // ColumnSet is vector of Column, instead of vector of BaseCardElement
            for (auto const &column : columns) { // update serial number that is used for generating unique key for image_map
                [self processBaseCardElement:column];
            }
            break;
        }

        case CardElementType::Column: {
            std::shared_ptr<Column> column = std::static_pointer_cast<Column>(elem);
            // Handle background image (if necessary)
            auto backgroundImageProperties = column->GetBackgroundImage();
            if ((backgroundImageProperties != nullptr) && !(backgroundImageProperties->GetUrl().empty())) {
                ObserverActionBlock observerAction = generateBackgroundImageObserverAction(backgroundImageProperties, self, column);
                [self loadBackgroundImageAccordingToResourceResolverIF:backgroundImageProperties key:nil observerAction:observerAction];
            }

            // add column fallbacks to async task queue
            [self processFallback:column];
            [self addTasksToConcurrentQueue:column->GetItems()];
        }
    }
}

// Walk through adaptive cards elements recursively and if images/images set/TextBlocks are found process them concurrently
- (void)addTasksToConcurrentQueue:(std::vector<std::shared_ptr<BaseCardElement>> const &)body
{
    ACRRegistration *rendererRegistration = [ACRRegistration getInstance];

    for (auto &elem : body) {
        if ([rendererRegistration isElementRendererOverridden:(ACRCardElementType)elem->GetElementType()] == YES) {
            continue;
        }

        [self processFallback:elem];
        [self processBaseCardElement:elem];
    }
}

// Walk through the actions found and process them concurrently
- (void)loadImagesForActionsAndCheckIfAllActionsHaveIconImages:(std::vector<std::shared_ptr<BaseActionElement>> const &)actions hostconfig:(ACOHostConfig *)hostConfig;
{
    for (auto &action : actions) {
        if (!action->GetIconUrl().empty()) {
            ObserverActionBlockForBaseAction observerAction =
                ^(NSObject<ACOIResourceResolver> *imageResourceResolver, NSString *key, std::shared_ptr<BaseActionElement> const &elem, NSURL *url, ACRView *rootView) {
                    UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                    if (view) {
                        [view addObserver:self
                               forKeyPath:@"image"
                                  options:NSKeyValueObservingOptionNew
                                  context:elem.get()];
                        [rootView setImageView:key view:view];
                    }
                };
            [self loadImageAccordingToResourceResolverIFForBaseAction:action key:nil observerAction:observerAction];
        } else {
            hostConfig.allActionsHaveIcons = NO;
        }
    }
}

- (void)processTextConcurrently:(RichTextElementProperties const &)textProperties
                      elementId:(NSString *)elementId
{
    RichTextElementProperties textProp = std::move(textProperties);
    /// dispatch to concurrent queue
    dispatch_group_async(_async_tasks_group, _global_queue,
                         ^{
                             buildIntermediateResultForText(self, self->_hostConfig, textProp, elementId);
                         });
}

- (void)enqueueIntermediateTextProcessingResult:(NSDictionary *)data
                                      elementId:(NSString *)elementId
{
    dispatch_sync(_serial_text_queue, ^{
        self->_textMap[elementId] = data;
    });
}

- (void)loadImage:(std::string const &)urlStr
{
    if (urlStr.empty()) {
        return;
    }

    NSString *nSUrlStr = [NSString stringWithCString:urlStr.c_str()
                                            encoding:[NSString defaultCStringEncoding]];
    NSURL *url = [NSURL URLWithString:nSUrlStr];
    // if url is relative, try again with adding base url from host config
    if ([url.relativePath isEqualToString:nSUrlStr]) {
        url = [NSURL URLWithString:nSUrlStr relativeToURL:_hostConfig.baseURL];
    }

    NSObject<ACOIResourceResolver> *imageResourceResolver = [_hostConfig getResourceResolverForScheme:[url scheme]];
    ImageLoadBlock imageloadblock = nil;
    if (!imageResourceResolver || ![imageResourceResolver respondsToSelector:@selector(resolveImageResource:)]) {
        imageloadblock = ^(NSURL *url) {
            // download image
            UIImage *img = nil;
            if ([url.scheme isEqualToString:@"data"]) {
                NSString *absoluteUri = url.absoluteString;
                std::string dataUri = AdaptiveCards::AdaptiveBase64Util::ExtractDataFromUri(std::string([absoluteUri UTF8String]));
                std::vector<char> decodedDataUri = AdaptiveCards::AdaptiveBase64Util::Decode(dataUri);
                NSData *decodedBase64 = [NSData dataWithBytes:decodedDataUri.data() length:decodedDataUri.size()];
                img = [UIImage imageWithData:decodedBase64];
            } else {
                img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
            }
            return img;
        };
    }

    dispatch_group_async(_async_tasks_group, _global_queue,
                         ^{
                             UIImage *img = nil;
                             if (imageloadblock) {
                                 img = imageloadblock(url);
                             } else if (imageResourceResolver) {
                                 img = [imageResourceResolver resolveImageResource:url];
                             }

                             dispatch_sync(self->_serial_queue, ^{
                                 self->_imageViewMap[nSUrlStr] = img;
                             });
                         });
}

// add postfix to existing BaseCardElement ID to be used as key
- (void)tagBaseCardElement:(std::shared_ptr<BaseCardElement> const &)elem
{
    std::string serial_number_as_string = std::to_string(_serialNumber);
    // concat a newly generated key to a existing id, the key will be removed after use
    elem->SetId(elem->GetId() + "_" + serial_number_as_string);
    ++_serialNumber;
}

- (NSMutableDictionary *)getImageMap
{
    return _imageViewMap;
}

- (UIImageView *)getImageView:(NSString *)key
{
    return _imageViewContextMap[key];
}

- (void)setImageView:(NSString *)key view:(UIView *)view
{
    _imageViewContextMap[key] = view;
}

- (void)setImageContext:(NSString *)key context:(std::shared_ptr<BaseCardElement> const &)elem
{
    _imageContextMap[key] = [[ACOBaseCardElement alloc] initWithBaseCardElement:elem];
}

- (dispatch_queue_t)getSerialQueue
{
    return _serial_queue;
}

- (NSMutableDictionary *)getTextMap
{
    return _textMap;
}

- (ACOAdaptiveCard *)card
{
    return _adaptiveCard;
}

// notification is delivered from main (serial) queue, thus run in the main thread context
- (void)observeValueForKeyPath:(NSString *)path ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    if ([path isEqualToString:@"image"]) {
        bool observerRemoved = false;
        if (context) {
            // image that was loaded
            UIImage *image = [change objectForKey:NSKeyValueChangeNewKey];

            NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)(context)];
            NSString *key = [number stringValue];

            ACOBaseCardElement *baseCardElement = _imageContextMap[key];
            if (baseCardElement) {
                ACRRegistration *reg = [ACRRegistration getInstance];
                ACRBaseCardElementRenderer<ACRIKVONotificationHandler> *renderer = (ACRBaseCardElementRenderer<ACRIKVONotificationHandler> *)[reg getRenderer:[NSNumber numberWithInt:static_cast<int>(baseCardElement.type)]];
                if (renderer && [[renderer class] conformsToProtocol:@protocol(ACRIKVONotificationHandler)]) {
                    // remove observer early in case background image must be changed to handle mode = repeat
                    [self removeObserver:self forKeyPath:path onObject:object];
                    observerRemoved = true;
                    NSMutableDictionary *imageViewMap = [self getImageMap];
                    imageViewMap[key] = image;
                    [renderer configUpdateForUIImageView:baseCardElement config:_hostConfig image:image imageView:(UIImageView *)object];
                }
            } else {
                id view = _imageViewContextMap[key];
                if ([view isKindOfClass:[ACRButton class]]) {
                    ACRButton *button = (ACRButton *)view;
                    [button setImageView:image withConfig:_hostConfig];
                } else {
                    // handle background image for adaptive card that uses resource resolver
                    UIImageView *imageView = (UIImageView *)object;
                    auto backgroundImage = [_adaptiveCard card] -> GetBackgroundImage();

                    // remove observer early in case background image must be changed to handle mode = repeat
                    [self removeObserver:self forKeyPath:path onObject:object];
                    observerRemoved = true;

                    renderBackgroundImage(backgroundImage.get(), imageView, image);
                }
            }
        }

        if (!observerRemoved) {
            [self removeObserver:self forKeyPath:path onObject:object];
        }
    } else if ([path isEqualToString:@"hidden"]) {
        [super observeValueForKeyPath:path ofObject:object change:change context:context];
    }
}

// remove observer from UIImageView
- (void)removeObserverOnImageView:(NSString *)KeyPath onObject:(NSObject *)object keyToImageView:(NSString *)key
{
    if ([object isKindOfClass:[UIImageView class]]) {
        if (_imageViewContextMap[key]) {
            [self removeObserver:self forKeyPath:KeyPath onObject:object];
        }
    }
}

- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)path onObject:(NSObject *)object
{
    // check that makes sure that there are subscribers, and the given observer is not one of the removed observers
    if (_numberOfSubscribers && ![_setOfRemovedObservers containsObject:object]) {
        _numberOfSubscribers--;
        [object removeObserver:self forKeyPath:path];
        [_setOfRemovedObservers addObject:object];
        [self callDidLoadElementsIfNeeded];
    }
}

- (void)loadBackgroundImageAccordingToResourceResolverIF:(std::shared_ptr<BackgroundImage> const &)backgroundImage key:(NSString *)key observerAction:(ObserverActionBlock)observerAction
{
    NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)(backgroundImage.get())];
    NSString *nSUrlStr = [NSString stringWithCString:backgroundImage->GetUrl().c_str() encoding:[NSString defaultCStringEncoding]];

    if (!key) {
        key = [number stringValue];
    }

    [self loadImage:nSUrlStr key:key context:nullptr observerAction:observerAction];
}

- (void)loadImageAccordingToResourceResolverIFFromString:(std::string const &)url
                                                     key:(NSString *)key
                                          observerAction:(ObserverActionBlock)observerAction
{
    std::shared_ptr<Image> imgElem = std::make_shared<Image>();
    imgElem->SetUrl(url);
    imgElem->SetImageSize(ImageSize::None);
    NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)imgElem.get()];
    if (!key) {
        key = [number stringValue];
    }
    [self loadImageAccordingToResourceResolverIF:imgElem key:key observerAction:observerAction];
}

- (void)loadImageAccordingToResourceResolverIF:(std::shared_ptr<BaseCardElement> const &)elem
                                           key:(NSString *)key
                                observerAction:(ObserverActionBlock)observerAction
{
    NSNumber *number = nil;
    NSString *nSUrlStr = nil;

    if (elem->GetElementType() == CardElementType::Media) {
        std::shared_ptr<Media> mediaElem = std::static_pointer_cast<Media>(elem);
        number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)mediaElem.get()];
        nSUrlStr = [NSString stringWithCString:mediaElem->GetPoster().c_str() encoding:[NSString defaultCStringEncoding]];
    } else {
        std::shared_ptr<Image> imgElem = std::static_pointer_cast<Image>(elem);
        number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)imgElem.get()];
        nSUrlStr = [NSString stringWithCString:imgElem->GetUrl().c_str() encoding:[NSString defaultCStringEncoding]];
    }

    if (!key) {
        key = [number stringValue];
    }

    [self loadImage:nSUrlStr key:key context:elem observerAction:observerAction];
}

- (void)loadImage:(NSString *)nSUrlStr key:(NSString *)key context:(std::shared_ptr<BaseCardElement> const &)elem observerAction:(ObserverActionBlock)observerAction
{
    _numberOfSubscribers++;

    NSURL *url = [NSURL URLWithString:nSUrlStr];
    NSObject<ACOIResourceResolver> *imageResourceResolver = [_hostConfig getResourceResolverForScheme:[url scheme]];
    if (imageResourceResolver && ACOImageViewIF == [_hostConfig getResolverIFType:[url scheme]]) {
        if (observerAction) {
            observerAction(imageResourceResolver, key, elem, url, self);
        }
    } else {
        [self loadImage:[nSUrlStr cStringUsingEncoding:NSUTF8StringEncoding]];
    }
}

- (void)loadImageAccordingToResourceResolverIFForBaseAction:(std::shared_ptr<BaseActionElement> const &)elem
                                                        key:(NSString *)key
                                             observerAction:(ObserverActionBlockForBaseAction)observerAction
{
    NSNumber *number = nil;
    NSString *nSUrlStr = nil;

    _numberOfSubscribers++;

    number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)elem.get()];
    nSUrlStr = [NSString stringWithCString:elem->GetIconUrl().c_str() encoding:[NSString defaultCStringEncoding]];
    if (!key) {
        key = [number stringValue];
    }

    NSURL *url = [NSURL URLWithString:nSUrlStr];
    NSObject<ACOIResourceResolver> *imageResourceResolver = [_hostConfig getResourceResolverForScheme:[url scheme]];
    if (ACOImageViewIF == [_hostConfig getResolverIFType:[url scheme]]) {
        if (observerAction) {
            observerAction(imageResourceResolver, key, elem, url, self);
        }
    } else {
        [self loadImage:[nSUrlStr cStringUsingEncoding:NSUTF8StringEncoding]];
    }
}

- (void)dealloc
{
    for (id key in _imageViewContextMap) {
        id object = _imageViewContextMap[key];

        if ([object isKindOfClass:[ACRContentHoldingUIView class]]) {
            object = ((UIView *)object).subviews[0];
        } else if ([object isKindOfClass:[ACRButton class]]) {
            object = ((ACRButton *)object).iconView;
        }

        if (![_setOfRemovedObservers containsObject:object] && [object isKindOfClass:[UIImageView class]]) {
            [object removeObserver:self forKeyPath:@"image"];
        }
    }
}

- (void)updatePaddingMap:(std::shared_ptr<CollectionTypeElement> const &)collection view:(UIView *)view
{
    if (view && collection && collection->GetPadding()) {
        NSNumber *key = [NSNumber numberWithUnsignedLongLong:collection->GetInternalId().Hash()];
        _paddingMap[[key stringValue]] = view;
    }
}

// This adjustment is needed because during parsing the card, host config can't be accessed
- (void)updatePaddingMapForTopElements:(std::shared_ptr<BaseCardElement> const &)element rootView:(ACRView *)view card:(std::shared_ptr<AdaptiveCard> const &)card
{
    const CardElementType type = element->GetElementType();
    if (type == CardElementType::Container || type == CardElementType::ColumnSet || type == CardElementType::Column) {
        std::shared_ptr<CollectionTypeElement> collection = std::dynamic_pointer_cast<CollectionTypeElement>(element);
        if (view && collection && collection->GetStyle() != card->GetStyle()) {
            NSNumber *key = [NSNumber numberWithUnsignedLongLong:collection->GetInternalId().Hash()];
            _paddingMap[[key stringValue]] = view;
        }
    }
}

- (UIView *)getBleedTarget:(InternalId const &)internalId
{
    NSNumber *key = [NSNumber numberWithUnsignedLongLong:internalId.Hash()];
    return _paddingMap[[key stringValue]];
}

// get fallback content and add them async task queue
- (void)processFallback:(std::shared_ptr<BaseCardElement> const &)elem
{
    std::shared_ptr<BaseElement> fallbackElem = elem->GetFallbackContent();
    while (fallbackElem) {
        std::shared_ptr<BaseCardElement> fallbackElemCard = std::static_pointer_cast<BaseCardElement>(fallbackElem);
        if (fallbackElemCard) {
            [self processBaseCardElement:fallbackElemCard];
        }

        fallbackElem = fallbackElemCard->GetFallbackContent();
    }
}

- (ACRTargetBuilderDirector *)getActionsTargetBuilderDirector
{
    return _actionsTargetBuilderDirector;
}

- (ACRTargetBuilderDirector *)getSelectActionsTargetBuilderDirector
{
    return _selectActionsTargetBuilderDirector;
}

- (ACRTargetBuilderDirector *)getQuickReplyTargetBuilderDirector
{
    return _quickReplyTargetBuilderDirector;
}

- (void)addWarnings:(ACRWarningStatusCode)statusCode mesage:(NSString *)message
{
    [((NSMutableArray *)_warnings) addObject:[[ACOWarning alloc] initWith:statusCode message:message]];
}

- (ACRColumnView *)getParent:(ACRColumnView *)child
{
    return [_inputHandlerLookupTable objectForKey:child];
}

- (void)setParent:(ACRColumnView *)parent child:(ACRColumnView *)child
{
    [_inputHandlerLookupTable setObject:parent forKey:child];
}

- (void)pushCurrentShowcard:(ACRColumnView *)showcard;
{
    if (showcard) {
        [_showcards addObject:showcard];
    }
}

- (void)popCurrentShowcard
{
    if ([_showcards count]) {
        [_showcards removeLastObject];
    }
}

- (ACRColumnView *)peekCurrentShowCard
{
    ACRColumnView *showcard = nil;
    if ([_showcards count]) {
        showcard = _showcards.lastObject;
    }
    return showcard;
}

// check if UIImageView already contains an UIImage, if so, add it the image map.
- (void)registerImageFromUIImageView:(UIImageView *)imageView key:(NSString *)key
{
    if (imageView.image) {
        self->_imageViewMap[key] = imageView.image;
    }
}

@end
