//
//  Util
//  Util.mm
//
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "BackgroundImage.h"
#import "Enums.h"
#import "ACRViewPrivate.h"
#import "ACRUIImageView.h"
#import "Util.h"
#import "ACRContentStackView.h"
#import "ACOHostConfigPrivate.h"
#import "ACOBaseCardElementPrivate.h"
#import "ACRBaseCardElementRenderer.h"
#import "ACRRegistration.h"
#import "ACOBaseActionElementPrivate.h"
#import "ACRIBaseActionElementRenderer.h"

using namespace AdaptiveCards;

void configVisibility(UIView *view, std::shared_ptr<BaseCardElement> const &visibilityInfo)
{
    view.hidden = !(visibilityInfo->GetIsVisible());
    NSString *hashkey = [NSString stringWithCString:visibilityInfo->GetId().c_str() encoding:NSUTF8StringEncoding];
    view.tag = hashkey.hash;
}

void renderBackgroundImage(const std::shared_ptr<AdaptiveCards::BackgroundImage> backgroundImage, UIView *containerView, ACRView *rootView)
{
    if (backgroundImage == nullptr || backgroundImage->GetUrl().empty()) {
        return;
    }

    std::string imageUrl = backgroundImage->GetUrl();
    NSString *key = [NSString stringWithCString:imageUrl.c_str() encoding:[NSString defaultCStringEncoding]];
    if ([key length]) {
        UIImageView *imgView = nil;
        UIImage *img = [rootView getImageMap][key];
        if (img) {
            switch (backgroundImage->GetMode()) {
                case BackgroundImageMode::Repeat:
                case BackgroundImageMode::RepeatHorizontally:
                case BackgroundImageMode::RepeatVertically:
                    imgView = [[ACRUIImageView alloc] init];
                    imgView.backgroundColor = [UIColor colorWithPatternImage:img];
                    break;
                case BackgroundImageMode::Stretch:
                default:
                    imgView = [[ACRUIImageView alloc] initWithImage:img];
                    break;
            }
        } else {
            NSNumber *number = [NSNumber numberWithUnsignedLongLong:(unsigned long long)backgroundImage.get()];
            NSString *imageViewKey = [number stringValue];
            imgView = [rootView getImageView:imageViewKey];
            if (!imgView){
                imgView = [rootView getImageView:@"backgroundImage"];
            }
        }

        if (imgView) {
            imgView.translatesAutoresizingMaskIntoConstraints = NO;
            [containerView addSubview:imgView];
            [containerView sendSubviewToBack:imgView];

            if (img) {
                // apply now if image is ready, otherwise wait until it is loaded (ACRView::observeValueForKeyPath)
                applyBackgroundImageConstraints(backgroundImage.get(), imgView, img);
            }
        }
    }
}

void renderBackgroundImage(const BackgroundImage *backgroundImageProperties, UIImageView *imageView, UIImage *image)
{
    if (backgroundImageProperties->GetMode() == BackgroundImageMode::Repeat
        || backgroundImageProperties->GetMode() == BackgroundImageMode::RepeatHorizontally
        || backgroundImageProperties->GetMode() == BackgroundImageMode::RepeatVertically) {
        imageView.backgroundColor = [UIColor colorWithPatternImage:image];
        imageView.image = nil;
    }
    applyBackgroundImageConstraints(backgroundImageProperties, imageView, image);
}

void applyBackgroundImageConstraints(const BackgroundImage *backgroundImageProperties, UIImageView *imageView, UIImage *image)
{
    if (backgroundImageProperties == nullptr || imageView == nullptr || image == nullptr) {
        return;
    }

    UIView *superView = [imageView superview];
    if (superView == nullptr) {
        return;
    }

    switch (backgroundImageProperties->GetMode()) {
        case BackgroundImageMode::Repeat:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;

            imageView.contentMode = UIViewContentModeScaleAspectFill;
            break;
        }
        case BackgroundImageMode::RepeatHorizontally:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:image.size.height].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;

            switch (backgroundImageProperties->GetVerticalAlignment())
            {
                case VerticalAlignment::Bottom:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
                    break;
                case VerticalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
                    break;
                case VerticalAlignment::Top:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
                    break;
            }
            break;
        }
        case BackgroundImageMode::RepeatVertically:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:image.size.width].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            switch (backgroundImageProperties->GetHorizontalAlignment())
            {
                case HorizontalAlignment::Right:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeRight multiplier:1.0 constant:0].active = YES;
                    break;
                case HorizontalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
                    break;
                case HorizontalAlignment::Left:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0].active = YES;
                    break;
            }
            break;
        }
        case BackgroundImageMode::Stretch:
        default:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:superView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;

            imageView.contentMode = UIViewContentModeScaleAspectFill;
            break;
	}
    }
}

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem, ACRContentStackView *container, ACOHostConfig *acoConfig)
{
    std::shared_ptr<CollectionTypeElement> collection = std::dynamic_pointer_cast<CollectionTypeElement>(elem);
    if (collection) {
        // check current collection type element has padding, if so added to the padding map
        [rootView updatePaddingMap:collection view:container];
        // bleed specification requires the object that's asked to be bled to have padding
        if (collection->GetPadding()) {
            std::shared_ptr<HostConfig> config = [acoConfig getHostConfig];
            // bleed specification requires that there should be at leat one parental object with padding
            if (collection->GetCanBleed()) {
                InternalId internalId = collection->GetParentalId();
                ACRContentStackView *view = (ACRContentStackView *)[rootView getBleedTarget:internalId];
                // c++ to object-c enum conversion
                view = view? view: rootView;
                if (view) {
                    ACRBleedDirection direction = ACRRestricted;
                    switch (collection->GetBleedDirection()) {
                        case ContainerBleedDirection::BleedToLeading:
                            direction = ACRToLeadingEdge;
                            break;
                        case ContainerBleedDirection::BleedToTrailing:
                            direction = ACRToTrailingEdge;
                            break;
                        case ContainerBleedDirection::BleedToBothEdges:
                            direction = ACRToBothEdges;
                            break;
                        default:
                            direction = ACRRestricted;
                            break;
                    }
                    // 1. create a background view (bv).
                    // 2. bv is added to bleed target view (tv), which is also a parent view.
                    // bv is then pinned to the tv according to the bleed direction
                    // bv gets current container view's (cv) container style
                    // and cv's container style is reset to transparent, such that
                    // bv's container style will be diplayed.
                    // container view's stack view (csv) holds content views, and bv dislpays container style
                    // we transpose them, and get the final result
                    UIView *backgroundView = [[UIView alloc] init];
                    container.backgroundView = backgroundView;
                    backgroundView.translatesAutoresizingMaskIntoConstraints = NO;

                    UIView *marginalView = view.backgroundView? view.backgroundView : view;
                    [marginalView addSubview:backgroundView];
                    [marginalView sendSubviewToBack:backgroundView];
                    backgroundView.backgroundColor = container.backgroundColor;
                    container.backgroundColor = UIColor.clearColor;
                    [backgroundView.topAnchor constraintEqualToAnchor:container.topAnchor].active = YES;
                    [backgroundView.bottomAnchor constraintEqualToAnchor:container.bottomAnchor].active = YES;

                    // reset current width constraints and update them with new one according to bleed specification
                    [container bleed:config->GetSpacing().paddingSpacing priority:1000 target:backgroundView
                           direction:direction];

                    if([container layer].borderWidth) {
                        [backgroundView layer].borderWidth = [container layer].borderWidth;
                        [container layer].borderWidth = 0;
                    }

                    if([container layer].borderColor) {
                        [backgroundView layer].borderColor = [container layer].borderColor;
                        [container layer].borderColor = 0;
                    }

                    if (direction == ACRToLeadingEdge || direction == ACRToBothEdges) {
                        [backgroundView.leadingAnchor constraintEqualToAnchor:marginalView.leadingAnchor].active = YES;

                        if (direction == ACRToLeadingEdge) {
                            [backgroundView.trailingAnchor constraintEqualToAnchor:container.trailingAnchor].active = YES;
                        }
                    }

                    if (direction == ACRToTrailingEdge || direction == ACRToBothEdges) {
                        [backgroundView.trailingAnchor constraintEqualToAnchor:marginalView.trailingAnchor].active = YES;
                        if (direction == ACRToTrailingEdge) {
                            [backgroundView.leadingAnchor constraintEqualToAnchor:container.leadingAnchor].active = YES;
                        }
                    }

                    // recenters content view
                    if (direction != ACRRestricted) {
                        [container.stackView.centerXAnchor constraintEqualToAnchor:backgroundView.centerXAnchor].active = YES;
                    }
                }
            }
        }
    }
}

ObserverActionBlock generateBackgroundImageObserverAction(std::shared_ptr<BackgroundImage> backgroundImageProperties, ACRView *observer, std::shared_ptr<BaseCardElement> const &context)
{
    return ^(NSObject<ACOIResourceResolver>* imageResourceResolver, NSString* key, std::shared_ptr<BaseCardElement> const &elem, NSURL* url, ACRView* rootView) {
        UIImageView *view = [imageResourceResolver resolveImageViewResource:url];
        if(view) {
            [view addObserver:observer forKeyPath:@"image"
                      options:NSKeyValueObservingOptionNew
                      context:backgroundImageProperties.get()];

            // store the image view and column for easy retrieval in ACRView::observeValueForKeyPath
            [rootView setImageView:key view:view];
            [rootView setImageContext:key context:context];
        }
    };
}

void handleFallbackException(ACOFallbackException *exception,
                             UIView<ACRIContentHoldingView> *view,
                             ACRView *rootView,
                             NSMutableArray *inputs,
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
                [renderer render:view rootView:rootView inputs:inputs baseCardElement:acoElem hostConfig:config];
                bHandled = true;
            } @catch (ACOFallbackException *e){
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

void removeLastViewFromCollectionView(const CardElementType elemType, UIView<ACRIContentHoldingView> *view)
{
    if (elemType == CardElementType::Container ||
        elemType == CardElementType::Column ||
        elemType == CardElementType::ColumnSet) {
        [view removeLastViewFromArrangedSubview];
    }
}

void handleActionFallbackException(ACOFallbackException *exception,
                                   UIView<ACRIContentHoldingView> *view,
                                   ACRView *rootView,
                                   NSMutableArray *inputs,
                                   ACOBaseActionElement *acoElem,
                                   ACOHostConfig *config,
                                   UIView<ACRIContentHoldingView> *actionSet)
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

        ACOBaseActionElement *acoElem = [[ACOBaseActionElement alloc] initWithBaseActionElement:elem];

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
