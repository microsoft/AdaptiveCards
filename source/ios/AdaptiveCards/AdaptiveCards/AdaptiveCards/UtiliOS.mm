//
//  UtiliOS
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "UtiliOS.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACOHostConfigPrivate.h"
#import "ACRBaseCardElementRenderer.h"
#import "ACRColumnSetView.h"
#import "ACRContentStackView.h"
#import "ACRIBaseActionElementRenderer.h"
#import "ACRRegistration.h"
#import "ACRTargetBuilderDirector.h"
#import "ACRUIImageView.h"
#import "ACRViewPrivate.h"
#import "BackgroundImage.h"
#import "BaseActionElement.h"
#import "Enums.h"
#import "MarkDownParser.h"
#import "RichTextElementProperties.h"
#import "TextRun.h"

using namespace AdaptiveCards;

void configVisibility(UIView *view, std::shared_ptr<BaseCardElement> const &visibilityInfo)
{
    if (!visibilityInfo->GetIsVisible()) {
        view.hidden = YES;
    } else {
        view.hidden = NO;
    }

    NSString *hashkey = [NSString stringWithCString:visibilityInfo->GetId().c_str()
                                           encoding:NSUTF8StringEncoding];
    view.tag = hashkey.hash;
}

void configSeparatorVisibility(ACRSeparator *view,
                               std::shared_ptr<BaseCardElement> const &visibilityInfo)
{
    if (!visibilityInfo->GetIsVisible()) {
        view.hidden = YES;
    }
    NSMutableString *hashkey = [NSMutableString stringWithCString:visibilityInfo->GetId().c_str()
                                                         encoding:NSUTF8StringEncoding];
    [hashkey appendString:@"-separator"];
    view.tag = hashkey.hash;
}

void renderBackgroundImage(const std::shared_ptr<AdaptiveCards::BackgroundImage> backgroundImage,
                           UIView *containerView, ACRView *rootView)
{
    if (backgroundImage == nullptr || backgroundImage->GetUrl().empty()) {
        return;
    }

    std::string imageUrl = backgroundImage->GetUrl();
    NSString *key = [NSString stringWithCString:imageUrl.c_str()
                                       encoding:[NSString defaultCStringEncoding]];
    if ([key length]) {
        UIImageView *imgView = nil;
        UIImage *img = [rootView getImageMap][key];
        if (img) {
            switch (backgroundImage->GetFillMode()) {
                case ImageFillMode::Repeat:
                case ImageFillMode::RepeatHorizontally:
                case ImageFillMode::RepeatVertically:
                    imgView = [[ACRUIImageView alloc] init];
                    imgView.backgroundColor = [UIColor colorWithPatternImage:img];
                    break;
                case ImageFillMode::Cover:
                default:
                    imgView = [[ACRUIImageView alloc] initWithImage:img];
                    break;
            }
        } else {
            NSNumber *number =
                [NSNumber numberWithUnsignedLongLong:(unsigned long long)backgroundImage.get()];
            NSString *imageViewKey = [number stringValue];
            imgView = [rootView getImageView:imageViewKey];
            if (!imgView) {
                imgView = [rootView getImageView:@"backgroundImage"];
            }
        }

        if (imgView) {
            imgView.translatesAutoresizingMaskIntoConstraints = NO;
            [containerView insertSubview:imgView atIndex:0];

            if (img) {
                // apply now if image is ready, otherwise wait until it is loaded
                applyBackgroundImageConstraints(backgroundImage.get(), imgView, img);
            }
        }
    }
}

void renderBackgroundImage(const BackgroundImage *backgroundImageProperties, UIImageView *imageView,
                           UIImage *image)
{
    if (backgroundImageProperties->GetFillMode() == ImageFillMode::Repeat ||
        backgroundImageProperties->GetFillMode() == ImageFillMode::RepeatHorizontally ||
        backgroundImageProperties->GetFillMode() == ImageFillMode::RepeatVertically) {
        imageView.backgroundColor = [UIColor colorWithPatternImage:image];
        imageView.image = nil;
    }
    applyBackgroundImageConstraints(backgroundImageProperties, imageView, image);
}

void applyBackgroundImageConstraints(const BackgroundImage *backgroundImageProperties,
                                     UIImageView *imageView, UIImage *image)
{
    if (backgroundImageProperties == nullptr || imageView == nullptr || image == nullptr) {
        return;
    }

    UIView *superView = [imageView superview];
    if (superView == nullptr) {
        return;
    }

    switch (backgroundImageProperties->GetFillMode()) {
        case ImageFillMode::Repeat: {
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeTop
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:superView
                                         attribute:NSLayoutAttributeTop
                                        multiplier:1.0
                                          constant:0]
                .active = YES;
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeBottom
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:superView
                                         attribute:NSLayoutAttributeBottom
                                        multiplier:1.0
                                          constant:0]
                .active = YES;
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeLeading
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:superView
                                         attribute:NSLayoutAttributeLeading
                                        multiplier:1.0
                                          constant:0]
                .active = YES;
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeTrailing
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:superView
                                         attribute:NSLayoutAttributeTrailing
                                        multiplier:1.0
                                          constant:0]
                .active = YES;

            imageView.contentMode = UIViewContentModeScaleAspectFill;
            break;
        }
        case ImageFillMode::RepeatHorizontally: {
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeHeight
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:nil
                                         attribute:NSLayoutAttributeNotAnAttribute
                                        multiplier:1.0
                                          constant:image.size.height]
                .active = YES;
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeLeading
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:superView
                                         attribute:NSLayoutAttributeLeading
                                        multiplier:1.0
                                          constant:0]
                .active = YES;
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeTrailing
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:superView
                                         attribute:NSLayoutAttributeTrailing
                                        multiplier:1.0
                                          constant:0]
                .active = YES;

            configVerticalAlignmentConstraintsForBackgroundImageView(backgroundImageProperties, superView, imageView);
            break;
        }
        case ImageFillMode::RepeatVertically: {
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeWidth
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:nil
                                         attribute:NSLayoutAttributeNotAnAttribute
                                        multiplier:1.0
                                          constant:image.size.width]
                .active = YES;
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeTop
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:superView
                                         attribute:NSLayoutAttributeTop
                                        multiplier:1.0
                                          constant:0]
                .active = YES;
            [NSLayoutConstraint constraintWithItem:imageView
                                         attribute:NSLayoutAttributeBottom
                                         relatedBy:NSLayoutRelationEqual
                                            toItem:superView
                                         attribute:NSLayoutAttributeBottom
                                        multiplier:1.0
                                          constant:0]
                .active = YES;
            configHorizontalAlignmentConstraintsForBackgroundImageView(backgroundImageProperties, superView, imageView);
            break;
        }
        case ImageFillMode::Cover:
        default: {
            imageView.contentMode = UIViewContentModeScaleAspectFill;
            // Fill Mode Description
            // ScaleAspectFill increases one dimension of image proportionally if
            // corresponding dimension increases but it does not increase view surroinding the image
            // find which dimension is in deficit and act accordingly
            // when both dimensions are in deficit find the most deficient dimension
            // and increase
            // center the modified image view to the target view.

            CGSize targetViewSize = superView.frame.size;
            CGSize sourceSize = image.size;
            BOOL isDeficientInWidth = NO;
            BOOL isDeficientInHeight = NO;

            if (sourceSize.width < targetViewSize.width) {
                isDeficientInWidth = YES;
            }

            if (sourceSize.height < targetViewSize.height) {
                isDeficientInHeight = YES;
            }

            if (isDeficientInWidth and isDeficientInHeight) {
                CGFloat widthDeficiencyRaito = sourceSize.width ? targetViewSize.width / sourceSize.width : 1;
                CGFloat heightDifficiencyRaito = sourceSize.height ? targetViewSize.height / sourceSize.height : 1;
                // m * a >= x
                // m * b >= y
                // we want factor m that produces width and height when multiplied to a and b that are equal or greater than x and y where a, b is the background image size, and x, y are size of super view we are trying to fill
                // then m is max of (a/x, b/y)
                // we applies m to image view's corresponding axis.
                // then we applies a/b or b/a aspect raito to y or x to increase the other axis and keep the aspect ratio.
                if (widthDeficiencyRaito >= heightDifficiencyRaito) {
                    configWidthAndHeightAnchors(superView, imageView, false);
                } else {
                    configWidthAndHeightAnchors(superView, imageView, true);
                }
            } else if (isDeficientInWidth) {
                configWidthAndHeightAnchors(superView, imageView, false);
            } else if (isDeficientInHeight) {
                configWidthAndHeightAnchors(superView, imageView, true);
            }

            configVerticalAlignmentConstraintsForBackgroundImageView(backgroundImageProperties, superView, imageView);

            configHorizontalAlignmentConstraintsForBackgroundImageView(backgroundImageProperties, superView, imageView);

            superView.clipsToBounds = YES;

            break;
        }
    }
}

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem,
                 ACRContentStackView *container, ACOHostConfig *acoConfig)
{
    configBleed(rootView, elem, container, acoConfig, nil);
}

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem,
                 ACRContentStackView *container, ACOHostConfig *acoConfig, UIView<ACRIContentHoldingView> *superview)
{
    std::shared_ptr<CollectionTypeElement> collection =
        std::dynamic_pointer_cast<CollectionTypeElement>(elem);
    if (collection) {
        // check current collection type element has padding, if so added to the padding map
        [rootView updatePaddingMap:collection view:container];
        // bleed specification requires the object that's asked to be bled to have padding
        if (collection->GetPadding()) {
            std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
            // bleed specification requires that there should be at leat one parental object with
            // padding
            if (collection->GetCanBleed()) {
                InternalId parentInternalId = collection->GetParentalId();
                ACRContentStackView *parentView =
                    (ACRContentStackView *)[rootView getBleedTarget:parentInternalId];
                // c++ to object-c enum conversion
                ContainerBleedDirection adaptiveBleedDirection = collection->GetBleedDirection();
                ACRBleedDirection direction = (ACRBleedDirection)adaptiveBleedDirection;
                if (![parentView isKindOfClass:[ACRColumnSetView class]] || parentView != superview) {
                    parentView = nil;
                }

                // 1. create a background view (bv).
                // 2. bv is added to bleed target view (tv), which is also a parent view.
                // bv is then pinned to the tv according to the bleed direction
                // bv gets current container view's (cv) container style
                // and cv's container style is reset to transparent, such that
                // bv's container style will be diplayed.
                // container view's stack view (csv) holds content views, and bv dislpays
                // container style we transpose them, and get the final result

                UIView *backgroundView = [[UIView alloc] init];
                container.backgroundView = backgroundView;
                backgroundView.translatesAutoresizingMaskIntoConstraints = NO;

                [container addSubview:backgroundView];
                [container sendSubviewToBack:backgroundView];
                backgroundView.backgroundColor = container.backgroundColor;
                container.backgroundColor = UIColor.clearColor;

                [container bleed:config->GetSpacing().paddingSpacing
                        priority:1000
                          target:backgroundView
                       direction:direction
                      parentView:parentView];

                if ([container layer].borderWidth) {
                    [backgroundView layer].borderWidth = [container layer].borderWidth;
                    [container layer].borderWidth = 0;
                }

                if ([container layer].borderColor) {
                    [backgroundView layer].borderColor = [container layer].borderColor;
                    [container layer].borderColor = 0;
                }
            }
        }
    }
}

ObserverActionBlock generateBackgroundImageObserverAction(
    std::shared_ptr<BackgroundImage> backgroundImageProperties, ACRView *observer,
    std::shared_ptr<BaseCardElement> const &context)
{
    return ^(NSObject<ACOIResourceResolver> *imageResourceResolver, NSString *key,
             std::shared_ptr<BaseCardElement> const &elem, NSURL *url, ACRView *rootView) {
        UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
        if (view) {
            [view addObserver:observer
                   forKeyPath:@"image"
                      options:NSKeyValueObservingOptionNew
                      context:backgroundImageProperties.get()];

            // store the image view and column for easy retrieval in ACRView::observeValueForKeyPath
            [rootView setImageView:key view:view];
            [rootView setImageContext:key context:context];
        }
    };
}

void handleFallbackException(ACOFallbackException *exception, UIView<ACRIContentHoldingView> *view,
                             ACRView *rootView, NSMutableArray *inputs,
                             std::shared_ptr<BaseCardElement> const &givenElem,
                             ACOHostConfig *config)
{
    std::shared_ptr<BaseElement> fallbackBaseElement = nullptr;
    std::shared_ptr<BaseCardElement> elem = givenElem;
    bool bCanFallbackToAncestor = elem->CanFallbackToAncestor();
    FallbackType fallbackType = elem->GetFallbackType();
    bool bHandled = false;
    ACRRegistration *reg = [ACRRegistration getInstance];

    do {
        fallbackType = elem->GetFallbackType();
        if (fallbackType != FallbackType::Content) {
            break;
        }

        fallbackBaseElement = elem->GetFallbackContent();
        elem = std::static_pointer_cast<BaseCardElement>(fallbackBaseElement);
        if (!elem) {
            break;
        }

        ACOBaseCardElement *acoElem = [[ACOBaseCardElement alloc] init];
        [acoElem setElem:elem];

        ACRBaseCardElementRenderer *renderer =
            [reg getRenderer:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if (renderer) {
            @try {
                const CardElementType elemType = givenElem->GetElementType();
                removeLastViewFromCollectionView(elemType, view);
                [renderer render:view
                           rootView:rootView
                             inputs:inputs
                    baseCardElement:acoElem
                         hostConfig:config];
                bHandled = true;
            } @catch (ACOFallbackException *e) {
                NSLog(@"Fallback Failed, trying different fallback");
                NSLog(@"%@", e);
            }
        }

    } while (!bHandled);

    if (!bHandled) {
        if (bCanFallbackToAncestor && fallbackType != FallbackType::Drop) {
            @throw exception;
        } else {
            const CardElementType elemType = givenElem->GetElementType();
            removeLastViewFromCollectionView(elemType, view);
        }
    }
}

void removeLastViewFromCollectionView(const CardElementType elemType,
                                      UIView<ACRIContentHoldingView> *view)
{
    if (elemType == CardElementType::Container || elemType == CardElementType::Column ||
        elemType == CardElementType::ColumnSet) {
        [view removeLastViewFromArrangedSubview];
    }
}

void handleActionFallbackException(ACOFallbackException *exception,
                                   UIView<ACRIContentHoldingView> *view, ACRView *rootView,
                                   NSMutableArray *inputs, ACOBaseActionElement *acoElem,
                                   ACOHostConfig *config,
                                   UIStackView *actionSet)
{
    std::shared_ptr<BaseElement> fallbackBaseElement = nullptr;
    std::shared_ptr<BaseActionElement> elem = acoElem.element;
    bool bCanFallbackToAncestor = elem->CanFallbackToAncestor();
    FallbackType fallbackType = elem->GetFallbackType();
    bool bHandled = false;
    ACRRegistration *reg = [ACRRegistration getInstance];

    do {
        fallbackType = elem->GetFallbackType();
        if (fallbackType != FallbackType::Content) {
            break;
        }

        fallbackBaseElement = elem->GetFallbackContent();
        elem = std::static_pointer_cast<BaseActionElement>(fallbackBaseElement);
        if (!elem) {
            break;
        }

        ACOBaseActionElement *acoElem =
            [[ACOBaseActionElement alloc] initWithBaseActionElement:elem];

        ACRBaseActionElementRenderer *renderer =
            [reg getActionRenderer:[NSNumber numberWithInt:(int)elem->GetElementType()]];

        if (renderer) {
            @try {
                UIButton *button = [renderer renderButton:rootView
                                                   inputs:inputs
                                                superview:view
                                        baseActionElement:acoElem
                                               hostConfig:config];
                [actionSet addArrangedSubview:button];
                bHandled = true;
            } @catch (ACOFallbackException *e) {
                NSLog(@"Fallabck Failed, trying different fallback");
                NSLog(@"%@", e);
            }
        }

    } while (!bHandled);

    if (!bHandled) {
        if (bCanFallbackToAncestor && fallbackType != FallbackType::Drop) {
            @throw exception;
        }
    }
}

UIFontDescriptor *getItalicFontDescriptor(UIFontDescriptor *descriptor, bool isItalic)
{
    if (isItalic && descriptor) {
        return [descriptor fontDescriptorWithSymbolicTraits:UIFontDescriptorTraitItalic];
    }

    return descriptor;
}

ACRRenderingStatus buildTargetForButton(ACRTargetBuilderDirector *director,
                                        std::shared_ptr<BaseActionElement> const &action,
                                        UIButton *button, NSObject **target)
{
    *target = [director build:action forButton:button];
    return *target ? ACRRenderingStatus::ACROk : ACRRenderingStatus::ACRFailed;
}

ACRRenderingStatus buildTarget(ACRTargetBuilderDirector *director,
                               std::shared_ptr<BaseActionElement> const &action,
                               NSObject **target)
{
    *target = [director build:action];
    return *target ? ACRRenderingStatus::ACROk : ACRRenderingStatus::ACRFailed;
}

UIFont *getFont(ACOHostConfig *hostConfig, const AdaptiveCards::RichTextElementProperties &textProperties)
{
    int fontweight = [hostConfig getTextBlockFontWeight:textProperties.GetFontType()
                                             textWeight:textProperties.GetTextWeight()];
    // sanity check, 400 is the normal font;
    if (fontweight <= 0 || fontweight > 900) {
        fontweight = 400;
    }
    UIFont *font = nil;
    fontweight -= 100;
    fontweight /= 100;

    if (![hostConfig getFontFamily:textProperties.GetFontType()]) {
        const NSArray<NSNumber *> *fontweights = @[ @(UIFontWeightUltraLight), @(UIFontWeightThin), @(UIFontWeightLight), @(UIFontWeightRegular), @(UIFontWeightMedium),
                                                    @(UIFontWeightSemibold), @(UIFontWeightBold), @(UIFontWeightHeavy), @(UIFontWeightBlack) ];
        const CGFloat size = [hostConfig getTextBlockTextSize:textProperties.GetFontType() textSize:textProperties.GetTextSize()];
        if (textProperties.GetFontType() == FontType::Monospace) {
            const NSArray<NSString *> *fontweights = @[ @"UltraLight", @"Thin", @"Light", @"Regular",
                                                        @"Medium", @"Semibold", @"Bold", @"Heavy", @"Black" ];
            UIFontDescriptor *descriptor = [UIFontDescriptor fontDescriptorWithFontAttributes:@{UIFontDescriptorFamilyAttribute : @"Courier New",
                                                                                                UIFontDescriptorFaceAttribute : fontweights[fontweight]}];
            descriptor = getItalicFontDescriptor(descriptor, textProperties.GetItalic());

            font = [UIFont fontWithDescriptor:descriptor size:[hostConfig getTextBlockTextSize:textProperties.GetFontType() textSize:textProperties.GetTextSize()]];
        } else {
            font = [UIFont systemFontOfSize:size weight:[fontweights[fontweight] floatValue]];

            if (textProperties.GetItalic()) {
                font = [UIFont fontWithDescriptor:
                                   getItalicFontDescriptor(font.fontDescriptor, textProperties.GetItalic())
                                             size:size];
            }
        }
    } else {
        // font weight as string since font weight as double doesn't work
        // normailze fontweight for indexing
        const NSArray<NSString *> *fontweights = @[ @"UltraLight", @"Thin", @"Light", @"Regular",
                                                    @"Medium", @"Semibold", @"Bold", @"Heavy", @"Black" ];
        UIFontDescriptor *descriptor = [UIFontDescriptor fontDescriptorWithFontAttributes:
                                                             @{UIFontDescriptorFamilyAttribute : [hostConfig getFontFamily:textProperties.GetFontType()],
                                                               UIFontDescriptorFaceAttribute : fontweights[fontweight]}];

        descriptor = getItalicFontDescriptor(descriptor, textProperties.GetItalic());

        font = [UIFont fontWithDescriptor:descriptor size:[hostConfig getTextBlockTextSize:textProperties.GetFontType() textSize:textProperties.GetTextSize()]];
    }
    return font;
}

void buildIntermediateResultForText(ACRView *rootView, ACOHostConfig *hostConfig, RichTextElementProperties const &textProperties, NSString *elementId)
{
    std::shared_ptr<MarkDownParser> markDownParser = std::make_shared<MarkDownParser>([ACOHostConfig getLocalizedDate:textProperties.GetText() language:textProperties.GetLanguage()]);

    // MarkDownParser transforms text with MarkDown to a html string
    NSString *parsedString = [NSString stringWithCString:markDownParser->TransformToHtml().c_str() encoding:NSUTF8StringEncoding];
    NSDictionary *data = nil;

    // use Apple's html rendering only if the string has markdowns
    if (markDownParser->HasHtmlTags() || markDownParser->IsEscaped()) {
        NSString *fontFamilyName = nil;

        if (![hostConfig getFontFamily:textProperties.GetFontType()]) {
            if (textProperties.GetFontType() == FontType::Monospace) {
                fontFamilyName = @"'Courier New'";
            } else {
                fontFamilyName = @"'-apple-system',  'San Francisco'";
            }
        } else {
            fontFamilyName = [hostConfig getFontFamily:textProperties.GetFontType()];
        }

        NSString *font_style = textProperties.GetItalic() ? @"italic" : @"normal";
        // Font and text size are applied as CSS style by appending it to the html string
        parsedString = [parsedString stringByAppendingString:[NSString stringWithFormat:@"<style>body{font-family: %@; font-size:%dpx; font-weight: %d; font-style: %@;}</style>",
                                                                                        fontFamilyName,
                                                                                        [hostConfig getTextBlockTextSize:textProperties.GetFontType()
                                                                                                                textSize:textProperties.GetTextSize()],
                                                                                        [hostConfig getTextBlockFontWeight:textProperties.GetFontType()
                                                                                                                textWeight:textProperties.GetTextWeight()],
                                                                                        font_style]];

        NSData *htmlData = [parsedString dataUsingEncoding:NSUTF16StringEncoding];
        NSDictionary *options = @{NSDocumentTypeDocumentAttribute : NSHTMLTextDocumentType};
        data = @{@"html" : htmlData, @"options" : options};
    } else {
        UIFont *font = getFont(hostConfig, textProperties);

        NSDictionary *attributeDictionary = @{NSFontAttributeName : font};
        data = @{@"nonhtml" : parsedString, @"descriptor" : attributeDictionary};
    }

    if (elementId) {
        [rootView enqueueIntermediateTextProcessingResult:data
                                                elementId:elementId];
    }
}

void TextBlockToRichTextElementProperties(const std::shared_ptr<TextBlock> &textBlock, RichTextElementProperties &textProp)
{
    textProp.SetText(textBlock->GetText());
    textProp.SetTextSize(textBlock->GetTextSize());
    textProp.SetTextWeight(textBlock->GetTextWeight());
    textProp.SetFontType(textBlock->GetFontType());
    textProp.SetTextColor(textBlock->GetTextColor());
    textProp.SetIsSubtle(textBlock->GetIsSubtle());
    textProp.SetLanguage(textBlock->GetLanguage());
}

void TextRunToRichTextElementProperties(const std::shared_ptr<TextRun> &textRun, RichTextElementProperties &textProp)
{
    textProp.SetText(textRun->GetText());
    textProp.SetTextSize(textRun->GetTextSize());
    textProp.SetTextWeight(textRun->GetTextWeight());
    textProp.SetFontType(textRun->GetFontType());
    textProp.SetTextColor(textRun->GetTextColor());
    textProp.SetIsSubtle(textRun->GetIsSubtle());
    textProp.SetLanguage(textRun->GetLanguage());
    textProp.SetItalic(textRun->GetItalic());
    textProp.SetStrikethrough(textRun->GetStrikethrough());
}

ACOBaseActionElement *deserializeUnknownActionToCustomAction(const std::shared_ptr<UnknownAction> unknownAction)
{
    ACRRegistration *reg = [ACRRegistration getInstance];
    ACOBaseActionElement *customAction = nil;
    if (reg) {
        NSString *type = [NSString stringWithCString:unknownAction->GetElementTypeString().c_str() encoding:NSUTF8StringEncoding];
        NSObject<ACOIBaseActionElementParser> *parser = [reg getCustomActionElementParser:type];
        if (!parser) {
            @throw [ACOFallbackException fallbackException];
        }
        Json::Value blob = unknownAction->GetAdditionalProperties();
        Json::StreamWriterBuilder streamWriterBuilder;
        auto writer = streamWriterBuilder.newStreamWriter();
        std::stringstream sstream;
        writer->write(blob, &sstream);
        delete writer;
        NSString *jsonString =
            [[NSString alloc] initWithCString:sstream.str().c_str()
                                     encoding:NSUTF8StringEncoding];
        if (jsonString.length > 0) {
            NSData *jsonPayload = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
            ACOParseContext *context = [reg getParseContext];
            customAction = [parser deserialize:jsonPayload parseContext:context];
        }
    }
    return customAction;
}

UIColor *getForegroundUIColorFromAdaptiveAttribute(std::shared_ptr<HostConfig> const &config, ACRContainerStyle style, ForegroundColor textColor, bool isSubtle)
{
    const std::string str = config->GetForegroundColor([ACOHostConfig getSharedContainerStyle:style], textColor, isSubtle);
    return [ACOHostConfig convertHexColorCodeToUIColor:str];
}

unsigned int getSpacing(Spacing spacing, std::shared_ptr<HostConfig> const &config)
{
    switch (spacing) {
        case Spacing::ExtraLarge:
            return config->GetSpacing().extraLargeSpacing;
        case Spacing::Large:
            return config->GetSpacing().largeSpacing;
        case Spacing::Medium:
            return config->GetSpacing().mediumSpacing;
        case Spacing::Small:
            return config->GetSpacing().smallSpacing;
        case Spacing::Default:
            return config->GetSpacing().defaultSpacing;
        default:
            break;
    }

    return 0;
}

void configVerticalAlignmentConstraintsForBackgroundImageView(const BackgroundImage *backgroundImageProperties, UIView *superView, UIImageView *imageView)
{
    if (!backgroundImageProperties || !superView || !imageView) {
        return;
    }

    switch (backgroundImageProperties->GetVerticalAlignment()) {
        case VerticalAlignment::Bottom:
            [imageView.bottomAnchor constraintEqualToAnchor:superView.bottomAnchor].active = YES;
            break;
        case VerticalAlignment::Center:
            [imageView.centerYAnchor constraintEqualToAnchor:superView.centerYAnchor].active = YES;
            break;
        case VerticalAlignment::Top:
        default:
            [imageView.topAnchor constraintEqualToAnchor:superView.topAnchor].active = YES;
            break;
    }
}

void configHorizontalAlignmentConstraintsForBackgroundImageView(const BackgroundImage *backgroundImageProperties, UIView *superView, UIImageView *imageView)
{
    if (!backgroundImageProperties || !superView || !imageView) {
        return;
    }

    switch (backgroundImageProperties->GetHorizontalAlignment()) {
        case HorizontalAlignment::Right:
            [imageView.trailingAnchor constraintEqualToAnchor:superView.trailingAnchor].active = YES;
            break;
        case HorizontalAlignment::Center:
            [imageView.centerXAnchor constraintEqualToAnchor:superView.centerXAnchor].active = YES;
            break;
        case HorizontalAlignment::Left:
        default:
            [imageView.leadingAnchor constraintEqualToAnchor:superView.leadingAnchor].active = YES;
            break;
    }
}

void configWidthAndHeightAnchors(UIView *superView, UIImageView *imageView, bool isComplimentaryAxisHorizontal)
{
    if (!imageView || !imageView.image || !superView) {
        return;
    }
    CGSize targetViewSize = superView.frame.size;
    CGSize sourceSize = imageView.image.size;
    if (isComplimentaryAxisHorizontal) {
        CGFloat complementaryWidth = sourceSize.height ? sourceSize.width * targetViewSize.height / sourceSize.height : 1;
        [imageView.widthAnchor constraintEqualToConstant:complementaryWidth].active = YES;
        [imageView.heightAnchor constraintEqualToAnchor:superView.heightAnchor].active = YES;
    } else {
        CGFloat complementaryHeight = sourceSize.width ? sourceSize.height * targetViewSize.width / sourceSize.width : 1;
        [imageView.widthAnchor constraintEqualToAnchor:superView.widthAnchor].active = YES;
        [imageView.heightAnchor constraintEqualToConstant:complementaryHeight].active = YES;
    }
}

NSMutableAttributedString *initAttributedText(ACOHostConfig *acoConfig, const std::string &text, const AdaptiveCards::RichTextElementProperties &textElementProperties, ACRContainerStyle style)
{
    UIFont *font = getFont(acoConfig, textElementProperties);
    auto foregroundColor = [acoConfig getTextBlockColor:style textColor:textElementProperties.GetTextColor() subtleOption:NO];

    return [[NSMutableAttributedString alloc] initWithString:[NSString stringWithCString:text.c_str() encoding:NSUTF8StringEncoding] attributes:@{NSFontAttributeName : font, NSForegroundColorAttributeName : foregroundColor}];
}
