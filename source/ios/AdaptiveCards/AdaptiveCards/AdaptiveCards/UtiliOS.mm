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
#import "ACRContentStackView.h"
#import "ACRIBaseActionElementRenderer.h"
#import "ACRRegistration.h"
#import "ACRTargetBuilderDirector.h"
#import "ACRUIImageView.h"
#import "ACRViewPrivate.h"
#import "BackgroundImage.h"
#import "BaseActionElement.h"
#import "Enums.h"

using namespace AdaptiveCards;

void configVisibility(UIView *view, std::shared_ptr<BaseCardElement> const &visibilityInfo) {
    view.hidden = !(visibilityInfo->GetIsVisible());
    NSString *hashkey = [NSString stringWithCString:visibilityInfo->GetId().c_str()
                                           encoding:NSUTF8StringEncoding];
    view.tag = hashkey.hash;
}

void configSeparatorVisibility(ACRSeparator *view,
                               std::shared_ptr<BaseCardElement> const &visibilityInfo) {
    view.hidden = !(visibilityInfo->GetIsVisible());
    NSMutableString *hashkey = [NSMutableString stringWithCString:visibilityInfo->GetId().c_str()
                                                         encoding:NSUTF8StringEncoding];
    [hashkey appendString:@"-separator"];
    view.tag = hashkey.hash;
}

void renderBackgroundImage(const std::shared_ptr<AdaptiveCards::BackgroundImage> backgroundImage,
                           UIView *containerView, ACRView *rootView) {
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
            [containerView addSubview:imgView];
            [containerView sendSubviewToBack:imgView];

            if (img) {
                // apply now if image is ready, otherwise wait until it is loaded
                // (ACRView::observeValueForKeyPath)
                applyBackgroundImageConstraints(backgroundImage.get(), imgView, img);
            }
        }
    }
}

void renderBackgroundImage(const BackgroundImage *backgroundImageProperties, UIImageView *imageView,
                           UIImage *image) {
    if (backgroundImageProperties->GetFillMode() == ImageFillMode::Repeat ||
        backgroundImageProperties->GetFillMode() == ImageFillMode::RepeatHorizontally ||
        backgroundImageProperties->GetFillMode() == ImageFillMode::RepeatVertically) {
        imageView.backgroundColor = [UIColor colorWithPatternImage:image];
        imageView.image = nil;
    }
    applyBackgroundImageConstraints(backgroundImageProperties, imageView, image);
}

void applyBackgroundImageConstraints(const BackgroundImage *backgroundImageProperties,
                                     UIImageView *imageView, UIImage *image) {
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

            switch (backgroundImageProperties->GetVerticalAlignment()) {
                case VerticalAlignment::Bottom:
                    [NSLayoutConstraint constraintWithItem:imageView
                                                 attribute:NSLayoutAttributeBottom
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:superView
                                                 attribute:NSLayoutAttributeBottom
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;
                    break;
                case VerticalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView
                                                 attribute:NSLayoutAttributeCenterY
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:superView
                                                 attribute:NSLayoutAttributeCenterY
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;
                    break;
                case VerticalAlignment::Top:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView
                                                 attribute:NSLayoutAttributeTop
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:superView
                                                 attribute:NSLayoutAttributeTop
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;
                    break;
            }
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
            switch (backgroundImageProperties->GetHorizontalAlignment()) {
                case HorizontalAlignment::Right:
                    [NSLayoutConstraint constraintWithItem:imageView
                                                 attribute:NSLayoutAttributeRight
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:superView
                                                 attribute:NSLayoutAttributeRight
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;
                    break;
                case HorizontalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView
                                                 attribute:NSLayoutAttributeCenterX
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:superView
                                                 attribute:NSLayoutAttributeCenterX
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;
                    break;
                case HorizontalAlignment::Left:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView
                                                 attribute:NSLayoutAttributeLeft
                                                 relatedBy:NSLayoutRelationEqual
                                                    toItem:superView
                                                 attribute:NSLayoutAttributeLeft
                                                multiplier:1.0
                                                  constant:0]
                        .active = YES;
                    break;
            }
            break;
        }
        case ImageFillMode::Cover:
        default: {
            imageView.contentMode = UIViewContentModeScaleAspectFill;

            if (superView.frame.size.width > imageView.frame.size.width) {
                [imageView.widthAnchor constraintEqualToAnchor:superView.widthAnchor].active = YES;
            } else if (superView.frame.size.height > imageView.frame.size.height) {
                [imageView.heightAnchor constraintEqualToAnchor:superView.heightAnchor].active =
                    YES;
            } else {  // if background image is bigger than the superview; let it retain its
                      // dimensions
                imageView.translatesAutoresizingMaskIntoConstraints = YES;
            }

            [imageView.centerYAnchor constraintEqualToAnchor:superView.centerYAnchor].active = YES;

            switch (backgroundImageProperties->GetHorizontalAlignment()) {
                case HorizontalAlignment::Right:
                    [imageView.trailingAnchor constraintEqualToAnchor:superView.trailingAnchor]
                        .active = YES;
                    break;
                case HorizontalAlignment::Left:
                    [imageView.leadingAnchor constraintEqualToAnchor:superView.leadingAnchor]
                        .active = YES;
                    break;
                case HorizontalAlignment::Center:
                    [imageView.centerXAnchor constraintEqualToAnchor:superView.centerXAnchor]
                        .active = YES;
                    break;
            }

            superView.clipsToBounds = YES;
            break;
        }
    }
}

void configBleed(ACRView *rootView, std::shared_ptr<BaseCardElement> const &elem,
                 ACRContentStackView *container, ACOHostConfig *acoConfig) {
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
                InternalId internalId = collection->GetParentalId();
                ACRContentStackView *view =
                    (ACRContentStackView *)[rootView getBleedTarget:internalId];
                // c++ to object-c enum conversion
                ContainerBleedDirection adaptiveBleedDirection = collection->GetBleedDirection();
                ACRBleedDirection direction = (ACRBleedDirection)adaptiveBleedDirection;
                view = view ? view : rootView;

                if (view) {
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

                    UIView *marginalView = view.backgroundView ? view.backgroundView : view;
                    [marginalView addSubview:backgroundView];
                    [marginalView sendSubviewToBack:backgroundView];
                    backgroundView.backgroundColor = container.backgroundColor;
                    container.backgroundColor = UIColor.clearColor;

                    [container bleed:config->GetSpacing().paddingSpacing
                            priority:1000
                              target:backgroundView
                           direction:direction
                          parentView:marginalView];

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
}

ObserverActionBlock generateBackgroundImageObserverAction(
    std::shared_ptr<BackgroundImage> backgroundImageProperties, ACRView *observer,
    std::shared_ptr<BaseCardElement> const &context) {
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
                             ACOHostConfig *config) {
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
                                      UIView<ACRIContentHoldingView> *view) {
    if (elemType == CardElementType::Container || elemType == CardElementType::Column ||
        elemType == CardElementType::ColumnSet) {
        [view removeLastViewFromArrangedSubview];
    }
}

void handleActionFallbackException(ACOFallbackException *exception,
                                   UIView<ACRIContentHoldingView> *view, ACRView *rootView,
                                   NSMutableArray *inputs, ACOBaseActionElement *acoElem,
                                   ACOHostConfig *config,
                                   UIView<ACRIContentHoldingView> *actionSet) {
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

UIFontDescriptor *getItalicFontDescriptor(UIFontDescriptor *descriptor, bool isItalic) {
    if (isItalic && descriptor) {
        return [descriptor fontDescriptorWithSymbolicTraits:UIFontDescriptorTraitItalic];
    }

    return descriptor;
}

ACRRenderingStatus buildTargetForButton(ACRTargetBuilderDirector *director,
                                        std::shared_ptr<BaseActionElement> const &action,
                                        UIButton *button, NSObject **target) {
    *target = [director build:action forButton:button];
    return *target ? ACRRenderingStatus::ACROk : ACRRenderingStatus::ACRFailed;
}

ACRRenderingStatus buildTarget(ACRTargetBuilderDirector *director,
                               std::shared_ptr<BaseActionElement> const &action,
                               NSObject **target) {
    *target = [director build:action];
    return *target ? ACRRenderingStatus::ACROk : ACRRenderingStatus::ACRFailed;
}
