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
    if (!view) {
        return;
    }

    if (!visibilityInfo->GetIsVisible()) {
        view.hidden = YES;
    }
    NSMutableString *hashkey = [NSMutableString stringWithCString:visibilityInfo->GetId().c_str()
                                                         encoding:NSUTF8StringEncoding];
    [hashkey appendString:@"-separator"];
    view.tag = hashkey.hash;
    view.isVisibilityObserved = YES;
}

ACRRtl getiOSRtl(std::optional<bool> const rtl)
{
    ACRRtl acrtl = ACRRtlNone;
    if (rtl.has_value()) {
        BOOL doSetRTL = rtl.value_or(false);
        if (doSetRTL) {
            acrtl = ACRRtlRTL;
        } else {
            acrtl = ACRRtlLTR;
        }
    }
    return acrtl;
}

void configRtl(UIView *view, ACORenderContext *context)
{
    if (!view || !context) {
        return;
    }

    ACRRtl rtl = context.rtl;
    if (rtl == ACRRtlNone) {
        return;
    } else if (rtl == ACRRtlRTL) {
        view.semanticContentAttribute = UISemanticContentAttributeForceRightToLeft;
    } else if (rtl == ACRRtlRTL) {
        view.semanticContentAttribute = UISemanticContentAttributeForceLeftToRight;
    }
}

void renderBackgroundImage(const std::shared_ptr<AdaptiveCards::BackgroundImage> backgroundImage,
                           ACRContentStackView *containerView, ACRView *rootView)
{
    if (rootView == nil || backgroundImage == nullptr || backgroundImage->GetUrl().empty()) {
        return;
    }

    std::string imageUrl = backgroundImage->GetUrl();
    NSString *key = [[NSNumber numberWithUnsignedLongLong:(unsigned long long)(backgroundImage.get())] stringValue];
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

            if (imgView.image) {
                // if image is ready, proceed to setting contraints
                renderBackgroundImage(rootView, backgroundImage.get(), imgView, imgView.image);
            }
        }
    }
}

void renderBackgroundImage(ACRView *rootView, const BackgroundImage *backgroundImageProperties, UIImageView *imageView,
                           UIImage *image)
{
    if (rootView == nil || backgroundImageProperties == nullptr || imageView == nullptr || image == nullptr) {
        return;
    }

    if (backgroundImageProperties->GetFillMode() == ImageFillMode::Repeat ||
        backgroundImageProperties->GetFillMode() == ImageFillMode::RepeatHorizontally ||
        backgroundImageProperties->GetFillMode() == ImageFillMode::RepeatVertically) {
        imageView.backgroundColor = [UIColor colorWithPatternImage:image];
        [rootView removeObserver:rootView forKeyPath:@"image" onObject:imageView];
        imageView.image = nil;
    }
    applyBackgroundImageConstraints(backgroundImageProperties, imageView, image);
    [rootView removeObserver:rootView forKeyPath:@"image" onObject:imageView];
}

// apply contraints for 'Cover' fill mode
// the backgroundView is set on the targetView
void renderBackgroundCoverMode(UIView *backgroundView, ACRContentStackView *targetView)
{
    if (!backgroundView || !targetView || ![backgroundView isKindOfClass:[UIImageView class]] || targetView.isBackgroundImageSet) {
        return;
    }

    UIImageView *imageView = (UIImageView *)backgroundView;
    UIImage *image = imageView.image;

    if (!image) {
        return;
    }

    targetView.isBackgroundImageSet = YES;

    imageView.contentMode = UIViewContentModeScaleAspectFill;
    // Fill Mode Description
    // ScaleAspectFill increases one dimension of image proportionally if
    // corresponding dimension increases but it does not increase view surroinding the image
    // find which dimension is in deficit and act accordingly
    // when both dimensions are in deficit find the most deficient dimension
    // and increase
    // center the modified image view to the target view.

    CGSize targetViewSize = targetView.frame.size;
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
            configWidthAndHeightAnchors(targetView, imageView, false);
        } else {
            configWidthAndHeightAnchors(targetView, imageView, true);
        }
    } else if (isDeficientInWidth) {
        configWidthAndHeightAnchors(targetView, imageView, false);
    } else if (isDeficientInHeight) {
        configWidthAndHeightAnchors(targetView, imageView, true);
    } else {
        // constraint the background image to the container's width according to the spec
        [imageView.widthAnchor constraintEqualToAnchor:targetView.widthAnchor].active = YES;
        if (imageView.image.size.width > 0) {
            [imageView.widthAnchor constraintEqualToAnchor:imageView.heightAnchor multiplier:imageView.image.size.height / imageView.image.size.width].active = YES;
        }
    }
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
            // we should not apply the constraints if the superView's frame is not ready
            // check layoutSubview of ACRContentStackView to see the alternate case
            if (superView.frame.size.width != 0 && superView.frame.size.height != 0) {
                renderBackgroundCoverMode(imageView, (ACRContentStackView *)superView);
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
                                        ACOBaseActionElement *action,
                                        UIButton *button, NSObject **target)
{
    *target = [director build:action forButton:button];
    return *target ? ACRRenderingStatus::ACROk : ACRRenderingStatus::ACRFailed;
}

ACRRenderingStatus buildTarget(ACRTargetBuilderDirector *director,
                               ACOBaseActionElement *action,
                               NSObject **target)
{
    *target = [director build:action];
    return *target ? ACRRenderingStatus::ACROk : ACRRenderingStatus::ACRFailed;
}

void setAccessibilityTrait(UIView *recipientView, ACOBaseActionElement *action)
{
    recipientView.userInteractionEnabled = [action isEnabled];
    recipientView.accessibilityTraits |= action.accessibilityTraits;
    if (![action isEnabled]) {
        recipientView.accessibilityTraits |= UIAccessibilityTraitNotEnabled;
    }
}

UIFont *getFont(ACOHostConfig *hostConfig, const AdaptiveCards::RichTextElementProperties &textProperties)
{
    FontType sharedFontType = textProperties.GetFontType().value_or(FontType::Default);
    TextWeight sharedTextWeight = textProperties.GetTextWeight().value_or(TextWeight::Default);
    TextSize sharedTextSize = textProperties.GetTextSize().value_or(TextSize::Default);

    int fontweight = [hostConfig getTextBlockFontWeight:sharedFontType
                                             textWeight:sharedTextWeight];
    // sanity check, 400 is the normal font;
    if (fontweight <= 0 || fontweight > 900) {
        fontweight = 400;
    }
    UIFont *font = nil;
    fontweight -= 100;
    fontweight /= 100;

    if (![hostConfig getFontFamily:sharedFontType]) {
        const NSArray<NSNumber *> *fontweights = @[ @(UIFontWeightUltraLight), @(UIFontWeightThin), @(UIFontWeightLight), @(UIFontWeightRegular), @(UIFontWeightMedium),
                                                    @(UIFontWeightSemibold), @(UIFontWeightBold), @(UIFontWeightHeavy), @(UIFontWeightBlack) ];
        const CGFloat size = [hostConfig getTextBlockTextSize:sharedFontType textSize:sharedTextSize];
        if (textProperties.GetFontType() == FontType::Monospace) {
            const NSArray<NSString *> *fontweights = @[ @"UltraLight", @"Thin", @"Light", @"Regular",
                                                        @"Medium", @"Semibold", @"Bold", @"Heavy", @"Black" ];
            UIFontDescriptor *descriptor = [UIFontDescriptor fontDescriptorWithFontAttributes:@{UIFontDescriptorFamilyAttribute : @"Courier New",
                                                                                                UIFontDescriptorFaceAttribute : fontweights[fontweight]}];
            descriptor = getItalicFontDescriptor(descriptor, textProperties.GetItalic());

            font = [UIFont fontWithDescriptor:descriptor size:[hostConfig getTextBlockTextSize:sharedFontType textSize:sharedTextSize]];
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
                                                             @{UIFontDescriptorFamilyAttribute : [hostConfig getFontFamily:sharedFontType],
                                                               UIFontDescriptorFaceAttribute : fontweights[fontweight]}];

        descriptor = getItalicFontDescriptor(descriptor, textProperties.GetItalic());

        font = [UIFont fontWithDescriptor:descriptor size:[hostConfig getTextBlockTextSize:sharedFontType textSize:sharedTextSize]];
    }
    return font;
}

void buildIntermediateResultForText(ACRView *rootView, ACOHostConfig *hostConfig, RichTextElementProperties const &textProperties, NSString *elementId)
{
    std::shared_ptr<MarkDownParser> markDownParser = std::make_shared<MarkDownParser>([ACOHostConfig getLocalizedDate:textProperties.GetText() language:textProperties.GetLanguage()]);

    // MarkDownParser transforms text with MarkDown to a html string
    auto markdownString = markDownParser->TransformToHtml();
    NSString *parsedString = (markDownParser->HasHtmlTags()) ? [NSString stringWithCString:markdownString.c_str() encoding:NSUTF8StringEncoding] : [NSString stringWithCString:markDownParser->GetRawText().c_str() encoding:NSUTF8StringEncoding];

    NSDictionary *data = nil;

    FontType sharedFontType = textProperties.GetFontType().value_or(FontType::Default);
    TextWeight sharedTextWeight = textProperties.GetTextWeight().value_or(TextWeight::Default);
    TextSize sharedTextSize = textProperties.GetTextSize().value_or(TextSize::Default);

    // use Apple's html rendering only if the string has markdowns
    if (markDownParser->HasHtmlTags()) {
        NSString *fontFamilyName = nil;

        if (![hostConfig getFontFamily:sharedFontType]) {
            if (sharedFontType == FontType::Monospace) {
                fontFamilyName = @"'Courier New'";
            } else {
                fontFamilyName = @"'-apple-system',  'San Francisco'";
            }
        } else {
            fontFamilyName = [hostConfig getFontFamily:sharedFontType];
        }

        NSString *font_style = textProperties.GetItalic() ? @"italic" : @"normal";
        // Font and text size are applied as CSS style by appending it to the html string
        parsedString = [parsedString stringByAppendingString:[NSString stringWithFormat:@"<style>body{font-family: %@; font-size:%dpx; font-weight: %d; font-style: %@;}</style>",
                                                                                        fontFamilyName,
                                                                                        [hostConfig getTextBlockTextSize:sharedFontType
                                                                                                                textSize:sharedTextSize],
                                                                                        [hostConfig getTextBlockFontWeight:sharedFontType
                                                                                                                textWeight:sharedTextWeight],
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

void TexStylesToRichTextElementProperties(const std::shared_ptr<TextBlock> &textBlock,
                                          const TextStyleConfig &textStyleConfig,
                                          RichTextElementProperties &textProp)
{
    textProp.SetText(textBlock->GetText());
    textProp.SetLanguage(textBlock->GetLanguage());
    textProp.SetText(textBlock->GetText());
    textProp.SetLanguage(textBlock->GetLanguage());
    textProp.SetTextSize(textBlock->GetTextSize().value_or(textStyleConfig.size));
    textProp.SetTextWeight(textBlock->GetTextWeight().value_or(textStyleConfig.weight));
    textProp.SetFontType(textBlock->GetFontType().value_or(textStyleConfig.fontType));
    textProp.SetTextColor(textBlock->GetTextColor().value_or(textStyleConfig.color));
    textProp.SetIsSubtle(textBlock->GetIsSubtle().value_or(textStyleConfig.isSubtle));
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
        case Spacing::Padding:
            return config->GetSpacing().paddingSpacing;
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
    auto foregroundColor = [acoConfig getTextBlockColor:style textColor:textElementProperties.GetTextColor().value_or(ForegroundColor::Default) subtleOption:NO];

    return [[NSMutableAttributedString alloc] initWithString:[NSString stringWithCString:text.c_str() encoding:NSUTF8StringEncoding] attributes:@{NSFontAttributeName : font, NSForegroundColorAttributeName : foregroundColor}];
}

NSString *makeKeyForImage(ACOHostConfig *acoConfig, NSString *keyType, NSDictionary<NSString *, NSString *> *pieces)
{
    ACOResolverIFType resolverType = ACODefaultIF;
    NSString *urlString = pieces[@"url"], *key = urlString;
    NSURL *url = nil;

    if (urlString) {
        url = [NSURL URLWithString:urlString];
        resolverType = [acoConfig getResolverIFType:[url scheme]];
    }

    if ([keyType isEqualToString:@"image"] || [keyType isEqualToString:@"media-poster"]) {
        if (ACOImageViewIF == resolverType) {
            key = pieces[@"number"];
        }
    } else if ([keyType isEqualToString:@"media-playicon-image"]) {
        key = (ACOImageViewIF == resolverType) ? pieces[@"playicon-url-viewIF"] : pieces[@"playicon-url"];
    } else if ([keyType isEqualToString:@"media-playicon-imageView"]) {
        key = (ACOImageViewIF == resolverType) ? pieces[@"playicon-url-imageView-viewIF"] : pieces[@"playicon-url-imageView"];
    }
    return key;
}

CGSize getAspectRatio(CGSize size)
{
    CGFloat heightToWidthRatio = 0.0f, widthToHeightRatio = 0.0f;
    if (size.width > 0) {
        heightToWidthRatio = size.height / size.width;
    }

    if (size.height > 0) {
        widthToHeightRatio = size.width / size.height;
    }
    return CGSizeMake(widthToHeightRatio, heightToWidthRatio);
}

ACRImageSize getACRImageSize(ImageSize adaptiveImageSize, BOOL hasExplicitDimensions)
{
    if (hasExplicitDimensions) {
        return ACRImageSizeExplicit;
    }

    switch (adaptiveImageSize) {
        case ImageSize::None:
            return ACRImageSizeNone;
        case ImageSize::Auto:
            return ACRImageSizeAuto;
        case ImageSize::Stretch:
            return ACRImageSizeStretch;
        case ImageSize::Small:
            return ACRImageSizeSmall;
        case ImageSize::Medium:
            return ACRImageSizeMedium;
        case ImageSize::Large:
            return ACRImageSizeLarge;
        default:
            return ACRImageSizeAuto;
    }
}

ACRHorizontalAlignment getACRHorizontalAlignment(HorizontalAlignment horizontalAlignment)
{
    switch (horizontalAlignment) {
        case HorizontalAlignment::Left:
            return ACRLeft;
        case HorizontalAlignment::Center:
            return ACRCenter;
        case HorizontalAlignment::Right:
            return ACRRight;
        default:
            return ACRLeft;
    }
}

void printSize(NSString *msg, CGSize size)
{
    NSLog(@"%@, size = %f x %f", msg, size.width, size.height);
}

NSData *JsonToNSData(const Json::Value &blob)
{
    Json::StreamWriterBuilder streamWriterBuilder;
    std::unique_ptr<Json::StreamWriter> writer(streamWriterBuilder.newStreamWriter());
    std::stringstream sstream;
    writer->write(blob, &sstream);
    NSString *jsonString =
        [[NSString alloc] initWithCString:sstream.str().c_str()
                                 encoding:NSUTF8StringEncoding];
    return (jsonString.length > 0) ? [jsonString dataUsingEncoding:NSUTF8StringEncoding] : nil;
}

void partitionActions(
    const std::vector<std::shared_ptr<BaseActionElement>> &elems,
    std::vector<std::shared_ptr<BaseActionElement>> &primary,
    std::vector<std::shared_ptr<BaseActionElement>> &secondary,
    unsigned int maxActions,
    ACRView *rootView)
{
    std::partition_copy(std::begin(elems),
                        std::end(elems),
                        std::inserter(secondary, std::end(secondary)),
                        std::inserter(primary, std::end(primary)),
                        [](std::shared_ptr<BaseActionElement> elem) {
                            return elem->GetMode() == Mode::Secondary;
                        });

    unsigned long uMaxActionsToRender = MIN(maxActions, primary.size());

    BOOL allowMoreThanMaxActionsInOverflowMenu = NO;
    if ([rootView.acrActionDelegate respondsToSelector:@selector(shouldAllowMoreThanMaxActionsInOverflowMenu)]) {
        allowMoreThanMaxActionsInOverflowMenu =
            [rootView.acrActionDelegate shouldAllowMoreThanMaxActionsInOverflowMenu];
    }

    if (uMaxActionsToRender < primary.size()) {
        auto start = std::begin(primary) + uMaxActionsToRender;
        auto end = std::end(primary);

        if (allowMoreThanMaxActionsInOverflowMenu) {
            std::copy(start, end, std::back_inserter(secondary));
        } else {
            [rootView addWarnings:ACRWarningStatusCode::ACRMaxActionsExceeded
                           mesage:@"Some actions were not rendered due to exceeding the maximum number "
                                  @"of actions allowed"];
        }

        primary.erase(start, end);
    }
}

UIImage *scaleImageToSize(UIImage *image, CGSize newSize)
{
    UIGraphicsBeginImageContextWithOptions(newSize, NO, 0.0);
    [image drawInRect:CGRectMake(0, 0, newSize.width, newSize.height)];
    UIImage *newImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return newImage;
}

NSNumber *iOSInternalIdHash(const std::size_t internalIdHash)
{
    return [NSNumber numberWithLong:internalIdHash];
}

id traverseResponderChainForUIViewController(UIView *view)
{
    id nextResponder = [view nextResponder];
    if ([nextResponder isKindOfClass:[UIViewController class]]) {
        return nextResponder;
    } else if ([nextResponder isKindOfClass:[UIView class]]) {
        return traverseResponderChainForUIViewController((UIView *)nextResponder);
    } else {
        return nil;
    }
}
