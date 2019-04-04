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

using namespace AdaptiveCards;

void configVisibility(UIView *view, std::shared_ptr<BaseCardElement> const &visibilityInfo)
{
    view.hidden = !(visibilityInfo->GetIsVisible());
    NSString *hashkey = [NSString stringWithCString:visibilityInfo->GetId().c_str() encoding:NSUTF8StringEncoding];
    view.tag = hashkey.hash;
}

void renderBackgroundImageView(const AdaptiveCards::BackgroundImage *backgroundImageProperties, UIView *containerView, ACRView *rootView)
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
            NSString *imageViewKey = [number stringValue];
            imgView = [rootView getImageView:imageViewKey];
        }
        
        if (imgView) {
            imgView.translatesAutoresizingMaskIntoConstraints = NO;
            [containerView addSubview:imgView];
            [containerView sendSubviewToBack:imgView];
            
            applyBackgroundImageConstraints(backgroundImageProperties, imgView);
            
            [imgView setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
            [imgView setContentHuggingPriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
            [imgView setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisHorizontal];
            [imgView setContentCompressionResistancePriority:UILayoutPriorityDefaultLow forAxis:UILayoutConstraintAxisVertical];
        }
    }
}

void applyBackgroundImageConstraints(const BackgroundImage *backgroundImageProperties, UIImageView *imageView)
{
    UIView *parentView = [imageView superview];
    UIImage *image = [imageView image];
    switch (backgroundImageProperties->GetMode()) {
        case BackgroundImageMode::Repeat:
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
        case BackgroundImageMode::RepeatHorizontally:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeHeight relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:image.size.height].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeading relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeLeading multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTrailing relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTrailing multiplier:1.0 constant:0].active = YES;
            
            switch (backgroundImageProperties->GetVerticalAlignment())
            {
                case VerticalAlignment::Bottom:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
                    break;
                case VerticalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterY multiplier:1.0 constant:0].active = YES;
                    break;
                case VerticalAlignment::Top:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
                    break;
            }
            break;
        }
        case BackgroundImageMode::RepeatVertically:
        {
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeWidth relatedBy:NSLayoutRelationEqual toItem:nil attribute:NSLayoutAttributeNotAnAttribute multiplier:1.0 constant:image.size.width].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeTop multiplier:1.0 constant:0].active = YES;
            [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeBottom multiplier:1.0 constant:0].active = YES;
            switch (backgroundImageProperties->GetHorizontalAlignment())
            {
                case HorizontalAlignment::Right:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeRight multiplier:1.0 constant:0].active = YES;
                    break;
                case HorizontalAlignment::Center:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeCenterX multiplier:1.0 constant:0].active = YES;
                    break;
                case HorizontalAlignment::Left:
                default:
                    [NSLayoutConstraint constraintWithItem:imageView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:parentView attribute:NSLayoutAttributeLeft multiplier:1.0 constant:0].active = YES;
                    break;
            }
            break;
        }
        case BackgroundImageMode::Stretch:
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
