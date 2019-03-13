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

void configVisibility(UIView *view, const std::shared_ptr<AdaptiveCards::BaseCardElement>visibilityInfo)
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
