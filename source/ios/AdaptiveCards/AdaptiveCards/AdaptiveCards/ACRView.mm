//
//  ACRView.m
//  ACRView
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRViewPrivate.h"
#import "ACRContentHoldingUIView.h"
#import "ACOHostConfigPrivate.h"
#import "ACRIBaseCardElementRenderer.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOAdaptiveCardPrivate.h"
#import "SharedAdaptiveCard.h"
#import "ACRRendererPrivate.h"
#import "ACRRegistration.h"
#import <AVFoundation/AVFoundation.h>
#import "Container.h"
#import "ColumnSet.h"
#import "Column.h"
#import "Fact.h"
#import "Enums.h"
#import "Media.h"
#import "TextInput.h"
#import "ACRImageRenderer.h"
#import "TextBlock.h"
#import "ACRTextBlockRenderer.h"
#import "MarkDownParser.h"
#import "ImageSet.h"
#import "ACRUILabel.h"
#import "ACRUIImageView.h"
#import "FactSet.h"
#import "AdaptiveBase64Util.h"
#import "ACRButton.h"
#import "BackgroundImage.h"

using namespace AdaptiveCards;
typedef UIImage* (^ImageLoadBlock)(NSURL *url);

@implementation ACRView
{
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
}

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if(self){
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
    }
    return self;
}

- (instancetype)init:(ACOAdaptiveCard *)card
          hostconfig:(ACOHostConfig *)config
     widthConstraint:(float)width
            delegate:(id<ACRActionDelegate>)acrActionDelegate
{
    self = [self initWithFrame:CGRectMake(0, 0, width, 0)];
    if(self){
        self.accessibilityLabel = @"ACR Root View";
        _adaptiveCard = card;
        if(config){
            _hostConfig = config;
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
    NSMutableArray *inputs = [[NSMutableArray alloc] init];

    if(self.frame.size.width){
        [NSLayoutConstraint constraintWithItem:self attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:self.frame.size.width].active = YES;
    }

    UIView *newView = [ACRRenderer renderWithAdaptiveCards:[_adaptiveCard card] inputs:inputs context:self containingView:self hostconfig:_hostConfig];

    ContainerStyle style = ([_hostConfig getHostConfig]->GetAdaptiveCard().allowCustomStyle)? [_adaptiveCard card]->GetStyle(): ContainerStyle::Default;

    newView.backgroundColor = [_hostConfig getBackgroundColorForContainerStyle:
        [ACOHostConfig getPlatformContainerStyle:style]];

    [ACRView renderBackgroundImageView:[_adaptiveCard card]->GetBackgroundImage().get() containerView:newView rootView:self];
    
    [self callDidLoadElementsIfNeeded];
    return newView;
}

+ (void)renderBackgroundImageView:(const AdaptiveCards::BackgroundImage *)backgroundImageProperties containerView:(UIView *)containerView rootView:(ACRView *)rootView
{
    std::string imageUrl = "";
    if((backgroundImageProperties != nullptr) && !(backgroundImageProperties->GetUrl().empty())) {
        imageUrl = backgroundImageProperties->GetUrl();
    }
    
    NSString *key = [NSString stringWithCString:imageUrl.c_str() encoding:[NSString defaultCStringEncoding]];
    if ([key length]) {
        UIImageView *imgView = nil;
        UIImage *img = nil;
        img = [rootView getImageMap][key];
        if (img) {
            if (backgroundImageProperties->GetMode() == BackgroundImageMode::Stretch) {
                imgView = [[ACRUIImageView alloc] initWithImage:img];
            } else {
                imgView = [[ACRUIImageView alloc] init];
                imgView.backgroundColor = [UIColor colorWithPatternImage:img];
            }
        } else {
            NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)backgroundImageProperties];
            NSString * imageViewKey = [number stringValue];
            imgView = [rootView getImageView:imageViewKey];
        }
        
        if (imgView) {
            imgView.translatesAutoresizingMaskIntoConstraints = NO;
            [containerView addSubview:imgView];
            [containerView sendSubviewToBack:imgView];
            
            [ACRView applyBackgroundImageConstraints:backgroundImageProperties imageView:imgView];
            
            [imgView setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
            [imgView setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
            [imgView setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
            [imgView setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
        }
    }
}

+ (void) applyBackgroundImageConstraints:(const AdaptiveCards::BackgroundImage *)backgroundImageProperties imageView:(UIImageView *)imageView
{
    UIView *parentView = [imageView superview];
    UIImage *image = [imageView image];
    switch (backgroundImageProperties->GetMode()) {
        case AdaptiveCards::BackgroundImageMode::Repeat:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
            
            imageView.contentMode = UIViewContentModeScaleAspectFill;
            break;
        }
        case AdaptiveCards::BackgroundImageMode::RepeatHorizontally:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:image.size.height].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
            
            switch (backgroundImageProperties->GetVerticalAlignment())
            {
                case AdaptiveCards::VerticalAlignment::Bottom:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
                    break;
                case AdaptiveCards::VerticalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
                    break;
                case AdaptiveCards::VerticalAlignment::Top:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
                    break;
            }
            break;
        }
        case AdaptiveCards::BackgroundImageMode::RepeatVertically:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:image.size.width].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            switch (backgroundImageProperties->GetHorizontalAlignment())
            {
                case AdaptiveCards::HorizontalAlignment::Right:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeRight multiplier:1.0 constant:0].active = YES;
                    break;
                case AdaptiveCards::HorizontalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
                    break;
                case AdaptiveCards::HorizontalAlignment::Left:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0].active = YES;
                    break;
            }
            break;
        }
        case AdaptiveCards::BackgroundImageMode::Stretch:
        default:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
            
            imageView.contentMode = UIViewContentModeScaleAspectFill;
            break;
        }
    }
}

- (void)waitForAsyncTasksToFinish
{
    dispatch_group_wait(_async_tasks_group, DISPATCH_TIME_FOREVER);
    [self callDidLoadElementsIfNeeded];
}

- (void)callDidLoadElementsIfNeeded
{
    // Call back app with didLoadElements
    if ([[self acrActionDelegate] respondsToSelector:@selector(didLoadElements)] && !_numberOfSubscribers)
    {
        [[self acrActionDelegate] didLoadElements];
    }
}

// Walk through adaptive cards elements recursively and if images/images set/TextBlocks are found process them concurrently
- (void)addTasksToConcurrentQueue:(std::vector<std::shared_ptr<BaseCardElement>> const &)body
{
    ACRRegistration *rendererRegistration = [ACRRegistration getInstance];

    for(auto &elem : body)
    {
        if([rendererRegistration isElementRendererOverridden:(ACRCardElementType) elem->GetElementType()] == YES){
            continue;
        }
        switch (elem->GetElementType())
        {
            case CardElementType::TextBlock:
            {
                std::shared_ptr<TextBlock> textBlockElement = std::static_pointer_cast<TextBlock>(elem);
                TextConfig textConfig =
                {
                    .weight = textBlockElement->GetTextWeight(),
                    .size = textBlockElement->GetTextSize(),
                    .style = textBlockElement->GetFontStyle(),
                    .color = textBlockElement->GetTextColor(),
                    .isSubtle = textBlockElement->GetIsSubtle(),
                    .wrap = textBlockElement->GetWrap()
                };

                /// tag a base card element with unique key
                NSString *key = [NSString stringWithCString:textBlockElement->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
                std::string text = textBlockElement->GetText();
                [self processTextConcurrently:textBlockElement
                              elementType:CardElementType::TextBlock
                                   textConfig:textConfig
                                    elementId:key
                                         text:text
                                         lang:textBlockElement->GetLanguage()];
                break;
            }
            case CardElementType::FactSet:
            {
                [self tagBaseCardElement:elem];
                std::shared_ptr<FactSet> factSet = std::dynamic_pointer_cast<FactSet>(elem);
                NSString *key = [NSString stringWithCString:elem->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
                key = [key stringByAppendingString:@"*"];
                int rowFactId = 0;
                for(auto fact : factSet->GetFacts()) {
                    std::string title = fact->GetTitle();
                    [self processTextConcurrently:factSet
                                      elementType:CardElementType::FactSet
                                       textConfig:[_hostConfig getHostConfig]->GetFactSet().title
                                        elementId:[key stringByAppendingString:[[NSNumber numberWithInt:rowFactId++] stringValue]]
                                             text:title
                                             lang:fact->GetLanguage()];

                    std::string value = fact->GetValue();
                    [self processTextConcurrently:factSet
                                      elementType:CardElementType::FactSet
                                       textConfig:[_hostConfig getHostConfig]->GetFactSet().value
                                        elementId:[key stringByAppendingString:[[NSNumber numberWithInt:rowFactId++] stringValue]]
                                             text:value
                                             lang:fact->GetLanguage()];
                }
                break;
            }
            case CardElementType::Image:
            {

                ObserverActionBlock observerAction =
                ^(NSObject<ACOIResourceResolver>* imageResourceResolver, NSString* key, std::shared_ptr<BaseCardElement> const &elem, NSURL* url, ACRView *rootView) {
                        UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                        if(view) {
                            [view addObserver:self forKeyPath:@"image"
                                      options:NSKeyValueObservingOptionNew
                                      context:elem.get()];
                            [rootView setImageView:key view:view];
                            rootView->_imageContextMap[key] = [[ACOBaseCardElement alloc] initWithBaseCardElement:elem];
                        }
                };
                [self loadImageAccordingToResourceResolverIF:elem key:nil observerAction:observerAction];

                break;
            }
            case CardElementType::ImageSet:
            {
                std::shared_ptr<ImageSet>imgSetElem = std::static_pointer_cast<ImageSet>(elem);
                for(auto img :imgSetElem->GetImages()) { // loops through images in image set
                    std::shared_ptr<BaseCardElement> baseImgElem = std::static_pointer_cast<BaseCardElement>(img);
                    img->SetImageSize(imgSetElem->GetImageSize());

                    ObserverActionBlock observerAction =
                    ^(NSObject<ACOIResourceResolver>* imageResourceResolver, NSString* key, std::shared_ptr<BaseCardElement> const &elem, NSURL* url, ACRView *rootView) {
                        UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                        if(view) {
                            [view addObserver:self forKeyPath:@"image"
                                      options:NSKeyValueObservingOptionNew
                                      context:elem.get()];
                            [rootView setImageView:key view:view];
                            rootView->_imageContextMap[key] = [[ACOBaseCardElement alloc] initWithBaseCardElement:elem];
                        }
                    };

                    [self loadImageAccordingToResourceResolverIF:baseImgElem key:nil observerAction:observerAction];

                }
                break;
            }
            case CardElementType::Media:
            {
                std::shared_ptr<Media> mediaElem = std::static_pointer_cast<Media>(elem);
                std::string poster =  mediaElem->GetPoster();
                if(poster.empty()) {
                    poster = [_hostConfig getHostConfig]->GetMedia().defaultPoster;
                }

                if(!poster.empty()) {
                    ObserverActionBlock observerAction =
                    ^(NSObject<ACOIResourceResolver>* imageResourceResolver, NSString* key, std::shared_ptr<BaseCardElement> const &imgElem, NSURL* url, ACRView* rootView) {
                        UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                        ACRContentHoldingUIView *contentholdingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];
                        if(view) {
                            [contentholdingview addSubview:view];
                            contentholdingview.isMediaType = YES;
                            [view addObserver:self forKeyPath:@"image"
                                      options:NSKeyValueObservingOptionNew
                                      context:elem.get()];
                            [rootView setImageView:key view:contentholdingview];
                            rootView->_imageContextMap[key] = [[ACOBaseCardElement alloc] initWithBaseCardElement:elem];
                        }
                    };
                    [self loadImageAccordingToResourceResolverIF:elem key:nil observerAction:observerAction];
                }

                break;
            }
            case CardElementType::TextInput:
            {
                std::shared_ptr<TextInput> textInput = std::static_pointer_cast<TextInput>(elem);
                std::shared_ptr<BaseActionElement> action = textInput->GetInlineAction();
                if(action != nullptr && !action->GetIconUrl().empty()) {
                    ObserverActionBlockForBaseAction observerAction =
                    ^(NSObject<ACOIResourceResolver>* imageResourceResolver, NSString* key, std::shared_ptr<BaseActionElement> const &elem, NSURL* url, ACRView *rootView) {
                        UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                        if(view) {
                            [view addObserver:self forKeyPath:@"image"
                                      options:NSKeyValueObservingOptionNew
                                      context:elem.get()];
                            [rootView setImageView:key view:view];
                        }
                    };
                    [self loadImageAccordingToResourceResolverIFForBaseAction:action key:nil observerAction:observerAction];
                }
                break;
            }
            // continue on search
            case CardElementType::Container:
            {
                std::shared_ptr<Container> container = std::static_pointer_cast<Container>(elem);
                
                auto backgroundImageProperties = container->GetBackgroundImage();
                if((backgroundImageProperties != nullptr) && !(backgroundImageProperties->GetUrl().empty())) {
                    ObserverActionBlock observerAction =
                    ^(NSObject<ACOIResourceResolver>* imageResourceResolver, NSString* key, std::shared_ptr<BaseCardElement> const &elem, NSURL* url, ACRView* rootView) {
                        UIImageView *view = [imageResourceResolver resolveBackgroundImageViewResource:url hasStretch:(backgroundImageProperties->GetMode() == BackgroundImageMode::Stretch)];
                        [rootView setImageView:key view:view];
                        if(view) {
                            [view addObserver:rootView forKeyPath:@"image"
                                      options:NSKeyValueObservingOptionNew
                                      context:backgroundImageProperties.get()];
                        }
                    };
                    [self
                     loadBackgroundImageAccordingToResourceResolverIF:container->GetBackgroundImage()
                     key:nil observerAction:observerAction];
                }
                
                std::vector<std::shared_ptr<BaseCardElement>> &new_body = container->GetItems();
                [self addTasksToConcurrentQueue: new_body];
                break;
            }
            // continue on search
            case CardElementType::ColumnSet:
            {
                std::shared_ptr<ColumnSet> columSet = std::static_pointer_cast<ColumnSet>(elem);
                std::vector<std::shared_ptr<Column>> &columns = columSet->GetColumns();
                // ColumnSet is vector of Column, instead of vector of BaseCardElement
                for(auto &column : columns) { // update serial number that is used for generating unique key for image_map
                    // Handle background image (if necessary)
                    auto backgroundImageProperties = column->GetBackgroundImage();
                    if((backgroundImageProperties != nullptr) && !(backgroundImageProperties->GetUrl().empty())) {
                        ObserverActionBlock observerAction =
                        ^(NSObject<ACOIResourceResolver>* imageResourceResolver, NSString* key, std::shared_ptr<BaseCardElement> const &elem, NSURL* url, ACRView* rootView) {
                            UIImageView *view = [imageResourceResolver resolveBackgroundImageViewResource:url hasStretch:(backgroundImageProperties->GetMode() == BackgroundImageMode::Stretch)];
                            [rootView setImageView:key view:view];
                            if(view) {
                                [view addObserver:rootView forKeyPath:@"image"
                                          options:NSKeyValueObservingOptionNew
                                          context:backgroundImageProperties.get()];
                            }
                        };
                        [self
                         loadBackgroundImageAccordingToResourceResolverIF:column->GetBackgroundImage()
                         key:nil observerAction:observerAction];
                    }
                    
                    [self addTasksToConcurrentQueue: column->GetItems()];
                }
                break;
            }
            default:
            {
                /// no work is needed
                break;
            }
        }
    }
}

// Walk through the actions found and process them concurrently
- (void)loadImagesForActionsAndCheckIfAllActionsHaveIconImages:(std::vector<std::shared_ptr<BaseActionElement>> const &)actions hostconfig:(ACOHostConfig *)hostConfig;
{
    for(auto &action : actions){
        if(!action->GetIconUrl().empty()) {
            ObserverActionBlockForBaseAction observerAction =
            ^(NSObject<ACOIResourceResolver>* imageResourceResolver, NSString* key, std::shared_ptr<BaseActionElement> const &elem, NSURL* url, ACRView *rootView) {
                UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
                if(view) {
                    [view addObserver:self forKeyPath:@"image"
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

- (void)processTextConcurrently:(std::shared_ptr<BaseCardElement> const &)textElement
                    elementType:(CardElementType)elementType
                     textConfig:(TextConfig const &)textConfig
                      elementId:(NSString *)elementId
                           text:(std::string  const &)text
                           lang:(std::string const &)lang
{
    std::shared_ptr<BaseCardElement> textElementForBlock = textElement;
    struct TextConfig textConfigForBlock = textConfig;
    std::string textForBlock = text;
    CardElementType elementTypeForBlock = elementType;
    /// dispatch to concurrent queue
    dispatch_group_async(_async_tasks_group, _global_queue,
        ^{
            std::shared_ptr<MarkDownParser> markDownParser = std::make_shared<MarkDownParser>([ACOHostConfig getLocalizedDate:textForBlock language:lang]);

            // MarkDownParser transforms text with MarkDown to a html string
            NSString* parsedString = [NSString stringWithCString:markDownParser->TransformToHtml().c_str() encoding:NSUTF8StringEncoding];
            NSDictionary *data = nil;

            // use Apple's html rendering only if the string has markdowns
            if(markDownParser->HasHtmlTags() || markDownParser->IsEscaped()) {
                NSString *fontFamilyName = nil;

                if(![self->_hostConfig getFontFamily:textConfigForBlock.style]){
                    if(textConfigForBlock.style == FontStyle::Monospace){
                        fontFamilyName = @"'Courier New'";
                    } else{
                        fontFamilyName = @"'-apple-system',  'San Francisco'";
                    }
                } else {
                    fontFamilyName = [self->_hostConfig getFontFamily:textConfigForBlock.style];
                }
                // Font and text size are applied as CSS style by appending it to the html string
                parsedString = [parsedString stringByAppendingString:[NSString stringWithFormat:@"<style>body{font-family: %@; font-size:%dpx; font-weight: %d;}</style>",
                                                                      fontFamilyName,
                                                                      [self->_hostConfig getTextBlockTextSize:textConfigForBlock.style
                                                                                                     textSize:textConfigForBlock.size],
                                                                      [self->_hostConfig getTextBlockFontWeight:textConfigForBlock.style
                                                                                                     textWeight:textConfigForBlock.weight]]];

                NSData *htmlData = [parsedString dataUsingEncoding:NSUTF16StringEncoding];
                NSDictionary *options = @{NSDocumentTypeDocumentAttribute: NSHTMLTextDocumentType};
                data = @{@"html" : htmlData, @"options" : options};
            } else {
                int fontweight = [self->_hostConfig getTextBlockFontWeight:textConfigForBlock.style
                                                                textWeight:textConfigForBlock.weight];
                // sanity check, 400 is the normal font;
                if(fontweight <= 0 || fontweight > 900){
                    fontweight = 400;
                }
                UIFont *font = nil;
                fontweight -= 100;
                fontweight /= 100;

                if(![self->_hostConfig getFontFamily:textConfigForBlock.style]){
                    const NSArray<NSNumber *> *fontweights = @[@(UIFontWeightUltraLight), @(UIFontWeightThin), @(UIFontWeightLight), @(UIFontWeightRegular), @(UIFontWeightMedium),
                       @(UIFontWeightSemibold), @(UIFontWeightBold), @(UIFontWeightHeavy), @(UIFontWeightBlack)];
                    const CGFloat size = [self->_hostConfig getTextBlockTextSize:textConfigForBlock.style textSize:textConfigForBlock.size];
                    if(textConfigForBlock.style == FontStyle::Monospace){
                        const NSArray<NSString *> *fontweights = @[ @"UltraLight", @"Thin", @"Light", @"Regular",
                                                                    @"Medium", @"Semibold", @"Bold", @"Heavy", @"Black" ];
                        UIFontDescriptor *descriptor = [UIFontDescriptor fontDescriptorWithFontAttributes:@{UIFontDescriptorFamilyAttribute: @"Courier New",
                                                                                                            UIFontDescriptorFaceAttribute:fontweights[fontweight]}];
                        font = [UIFont fontWithDescriptor:descriptor size:[self->_hostConfig getTextBlockTextSize:textConfigForBlock.style textSize:textConfigForBlock.size]];
                    }
                    else{
                        font = [UIFont systemFontOfSize:size weight:[fontweights[fontweight] floatValue]];
                    }
                } else {
                    // font weight as string since font weight as double doesn't work
                    // normailze fontweight for indexing
                    const NSArray<NSString *> *fontweights = @[ @"UltraLight", @"Thin", @"Light", @"Regular",
                                                                @"Medium", @"Semibold", @"Bold", @"Heavy", @"Black" ];
                    UIFontDescriptor *descriptor = [UIFontDescriptor fontDescriptorWithFontAttributes:@{UIFontDescriptorFamilyAttribute: [self->_hostConfig getFontFamily:textConfigForBlock.style],
                                                                                                          UIFontDescriptorFaceAttribute:fontweights[fontweight]}];
                    font = [UIFont fontWithDescriptor:descriptor size:[self->_hostConfig getTextBlockTextSize:textConfigForBlock.style textSize:textConfigForBlock.size]];
                }

                NSDictionary *attributeDictionary = @{NSFontAttributeName:font};
                data = @{@"nonhtml" : parsedString, @"descriptor" : attributeDictionary};
            }

            NSString *key = nil;
            if(CardElementType::TextBlock == elementTypeForBlock){
                std::shared_ptr<TextBlock> textBlockElement = std::dynamic_pointer_cast<TextBlock>(textElementForBlock);
                NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)textBlockElement.get()];
                key = [number stringValue];
            } else {
                std::shared_ptr<FactSet> factSetElement = std::dynamic_pointer_cast<FactSet>(textElementForBlock);
                key = elementId;
            }
            dispatch_sync(self->_serial_text_queue, ^{self->_textMap[key] = data; });
         });
}

- (void)loadImage:(std::string const &)urlStr
{
    if(urlStr.empty()){
        return;
    }

    NSString *nSUrlStr = [NSString stringWithCString:urlStr.c_str()
                                            encoding:[NSString defaultCStringEncoding]];
    NSURL *url = [NSURL URLWithString:nSUrlStr];
    // if url is relative, try again with adding base url from host config
    if([url.relativePath isEqualToString:nSUrlStr]) {
        url = [NSURL URLWithString:nSUrlStr relativeToURL:_hostConfig.baseURL];
    }

    NSObject<ACOIResourceResolver> *imageResourceResolver = [_hostConfig getResourceResolverForScheme:[url scheme]];
    ImageLoadBlock imageloadblock = nil;
    if(!imageResourceResolver || ![imageResourceResolver respondsToSelector:@selector(resolveImageResource:)]) {
        imageloadblock = ^(NSURL *url){
            // download image
            UIImage *img = nil;
            if([url.scheme isEqualToString: @"data"]) {
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
            if(imageloadblock) {
                img = imageloadblock(url);
            } else if(imageResourceResolver){
                img = [imageResourceResolver resolveImageResource:url];
            }

            dispatch_sync(self->_serial_queue, ^{self->_imageViewMap[nSUrlStr] = img;});
         }
    );
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
        if(context) {
            UIImage *image = [change objectForKey:NSKeyValueChangeNewKey];
            NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)(context)];
            NSString *key = [number stringValue];
            ACRRegistration *reg = [ACRRegistration getInstance];
            ACOBaseCardElement *baseCardElement = _imageContextMap[key];
            if(baseCardElement) {
                ACRBaseCardElementRenderer<ACRIKVONotificationHandler> *renderer = (ACRBaseCardElementRenderer<ACRIKVONotificationHandler> *)[reg getRenderer:[NSNumber numberWithInt:baseCardElement.type]];
                if(renderer && [[renderer class] conformsToProtocol:@protocol(ACRIKVONotificationHandler)]) {
                    [renderer configUpdateForUIImageView:baseCardElement config:_hostConfig image:image imageView:(UIImageView *)object];
                }
            } else {
                id view = _imageViewContextMap[key];
                if([view isKindOfClass:[ACRButton class]]) {
                    ACRButton *button = (ACRButton *)view;
                    [button setImageView:image withConfig:_hostConfig];
                }
            }
        }

        _numberOfSubscribers--;
        [object removeObserver:self forKeyPath:path];
        [_setOfRemovedObservers addObject:object];
        [self callDidLoadElementsIfNeeded];
    }
}

- (void)loadBackgroundImageAccordingToResourceResolverIF:(std::shared_ptr<BackgroundImage> const &)backgroundImage key:(NSString *)key observerAction:(ObserverActionBlock)observerAction
{
    NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)backgroundImage.get()];
    NSString *nSUrlStr = [NSString stringWithCString:backgroundImage->GetUrl().c_str() encoding:[NSString defaultCStringEncoding]];
    
    _numberOfSubscribers++;
    
    if(!key) {
        key = [number stringValue];
    }
    
    NSURL *url = [NSURL URLWithString:nSUrlStr];
    NSObject<ACOIResourceResolver> *imageResourceResolver = [_hostConfig getResourceResolverForScheme:[url scheme]];
    if(imageResourceResolver && ACOImageViewIF == [_hostConfig getResolverIFType:[url scheme]]) {
        if(observerAction) {
            observerAction(imageResourceResolver, key, nil, url, self);
        }
    } else {
        [self loadImage:[nSUrlStr cStringUsingEncoding:NSUTF8StringEncoding]];
    }
}

- (void)loadImageAccordingToResourceResolverIFFromString:(std::string const &)url
    key:(NSString *)key observerAction:(ObserverActionBlock)observerAction
{
    std::shared_ptr<Image> imgElem = std::make_shared<Image>();
    imgElem->SetUrl(url);
    imgElem->SetImageSize(ImageSize::None);
    [self loadImageAccordingToResourceResolverIF:imgElem key:key observerAction:observerAction];
}

- (void)loadImageAccordingToResourceResolverIF:(std::shared_ptr<BaseCardElement> const &)elem
    key:(NSString *)key observerAction:(ObserverActionBlock)observerAction
{
    NSNumber *number = nil;
    NSString *nSUrlStr = nil;

    _numberOfSubscribers++;

    if(elem->GetElementType() == CardElementType::Media) {
        std::shared_ptr<Media> mediaElem = std::static_pointer_cast<Media>(elem);
        number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)mediaElem.get()];
        nSUrlStr = [NSString stringWithCString:mediaElem->GetPoster().c_str() encoding:[NSString defaultCStringEncoding]];
    } else {
        std::shared_ptr<Image> imgElem = std::static_pointer_cast<Image>(elem);
        number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)imgElem.get()];
        nSUrlStr = [NSString stringWithCString:imgElem->GetUrl().c_str() encoding:[NSString defaultCStringEncoding]];
    }
    if(!key) {
        key = [number stringValue];
    }

    NSURL *url = [NSURL URLWithString:nSUrlStr];
    NSObject<ACOIResourceResolver> *imageResourceResolver = [_hostConfig getResourceResolverForScheme:[url scheme]];
    if(imageResourceResolver && ACOImageViewIF == [_hostConfig getResolverIFType:[url scheme]])
    {
        if(observerAction) {
            observerAction(imageResourceResolver, key, elem, url, self);
        }
    } else {
        [self loadImage:[nSUrlStr cStringUsingEncoding:NSUTF8StringEncoding]];
    }
}

- (void)loadImageAccordingToResourceResolverIFForBaseAction:(std::shared_ptr<BaseActionElement> const &)elem
    key:(NSString *)key observerAction:(ObserverActionBlockForBaseAction)observerAction
{
    NSNumber *number = nil;
    NSString *nSUrlStr = nil;

    _numberOfSubscribers++;

    number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)elem.get()];
    nSUrlStr = [NSString stringWithCString:elem->GetIconUrl().c_str() encoding:[NSString defaultCStringEncoding]];
    if(!key) {
        key = [number stringValue];
    }

    NSURL *url = [NSURL URLWithString:nSUrlStr];
    NSObject<ACOIResourceResolver> *imageResourceResolver = [_hostConfig getResourceResolverForScheme:[url scheme]];
    if(ACOImageViewIF == [_hostConfig getResolverIFType:[url scheme]])
    {
        if(observerAction) {
            observerAction(imageResourceResolver, key, elem, url, self);
        }
    } else {
        [self loadImage:[nSUrlStr cStringUsingEncoding:NSUTF8StringEncoding]];
    }
}

- (void)dealloc
{
    for (id key in _imageViewContextMap)
    {
        id object = _imageViewContextMap[key];

        if ([object isKindOfClass:[ACRContentHoldingUIView class]]) {
            object = ((UIView *)object).subviews[0];
        } else if ([object isKindOfClass:[ACRButton class]]) {
            object = ((ACRButton *)object).iconView;
        }

        if (![_setOfRemovedObservers containsObject:object] && [object isKindOfClass:[UIImageView class]])
        {
            [object removeObserver:self forKeyPath:@"image"];
        }
    }
}

@end
