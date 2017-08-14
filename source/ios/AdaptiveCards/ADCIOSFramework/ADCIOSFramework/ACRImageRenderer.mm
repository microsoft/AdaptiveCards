//
//  ACRImageRenderer
//  ACRImageRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRImageRenderer.h"
#import "Image.h"
#import "SharedAdaptiveCard.h"
#import "ACRContentHoldingUIView.h"

@implementation ACRImageRenderer

+ (ACRImageRenderer *)getInstance
{
    static ACRImageRenderer *singletonInstance = [[self alloc] init];
    return singletonInstance;
}

+ (CardElementType)elemType
{
    return CardElementType::Image;
}

- (CGSize)getImageSize:(std::shared_ptr<Image> const &)imgElem 
        withHostConfig:(std::shared_ptr<HostConfig> const &)hostConfig
{
    float sz = hostConfig->imageSizes.smallSize;
    switch (imgElem->GetImageSize()){
        case ImageSize::Large:{
            sz = hostConfig->imageSizes.largeSize;
            break;
        }
        case ImageSize::Medium:{
            sz = hostConfig->imageSizes.mediumSize;
            break;
        }

        case ImageSize::Small:{
            sz = hostConfig->imageSizes.smallSize;
            break;
        }

        default:{
            NSLog(@"unimplemented");
        }
    }
    CGSize cgSize = CGSizeMake(sz, sz);
    return cgSize;
}
// code clean-up in progress 
- (NSArray *)setImageAlignment:(HorizontalAlignment)alignment
                 withSuperview:(UIView *)superview
                        toView:(UIView *)view
{
    NSMutableArray *constraints = [[NSMutableArray alloc] init]; 
    [constraints addObject:
        [NSLayoutConstraint constraintWithItem:superview
                                     attribute:NSLayoutAttributeCenterY
                                     relatedBy:NSLayoutRelationEqual
                                        toItem:view
                                     attribute:NSLayoutAttributeCenterY
                                    multiplier:1
                                      constant:0]];

    switch (alignment)
    {
        case HorizontalAlignment::Center:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeCenterX
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeCenterX
                                            multiplier:1
                                              constant:0]];
                return constraints;
        }
        case HorizontalAlignment::Left:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeLeading
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeLeading
                                            multiplier:1
                                              constant:0]];
            return constraints;
        }
        case HorizontalAlignment::Right:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeTrailing
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeTrailing
                                            multiplier:1
                                              constant:0]];
            return constraints;
        }
        default:
        {
            [constraints addObject:
                [NSLayoutConstraint constraintWithItem:superview
                                             attribute:NSLayoutAttributeLeading
                                             relatedBy:NSLayoutRelationEqual
                                                toItem:view
                                             attribute:NSLayoutAttributeLeading
                                            multiplier:1
                                              constant:0]];
            return constraints;
        }
    }
    return constraints;
}
- (UIView *)render:(UIView *)viewGroup
            inputs:(NSMutableArray *)inputs
      withCardElem:(std::shared_ptr<BaseCardElement> const &)elem
     andHostConfig:(std::shared_ptr<HostConfig> const &)config
{
    std::shared_ptr<Image> imgElem = std::dynamic_pointer_cast<Image>(elem);
    NSString *urlStr = [NSString stringWithCString:imgElem->GetUrl().c_str()
                                          encoding:[NSString defaultCStringEncoding]];
    NSURL *url = [NSURL URLWithString:urlStr];

    UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
    
    CGSize cgsize = [self getImageSize:imgElem withHostConfig:config];

    UIGraphicsBeginImageContext(cgsize);
    UIImageView *view = [[UIImageView alloc]
                         initWithFrame:CGRectMake(0, 0, cgsize.width, cgsize.height)];
    [img drawInRect:(CGRectMake(0, 0, cgsize.width, cgsize.height))];
    img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    view.image = img;
    
    //jwoo:experimenting with diff attributes --> UIViewContentModeCenter;//UIViewContentModeScaleAspectFit;
    view.contentMode = UIViewContentModeScaleAspectFit;
    view.clipsToBounds = NO;
    if(imgElem->GetImageStyle() == ImageStyle::Person) {
        CALayer *imgLayer = view.layer;
        [imgLayer setCornerRadius:cgsize.width/2];
        [imgLayer setMasksToBounds:YES];
    }
    
    ACRContentHoldingUIView *wrappingview = [[ACRContentHoldingUIView alloc] initWithFrame:view.frame];
    [wrappingview addSubview:view];
    

    if(viewGroup)[(UIStackView *)viewGroup addArrangedSubview:wrappingview];

    [wrappingview addConstraints:[self setImageAlignment:imgElem->GetHorizontalAlignment()
                                           withSuperview:wrappingview
                                                  toView:view]];

    view.translatesAutoresizingMaskIntoConstraints = NO;
    wrappingview.translatesAutoresizingMaskIntoConstraints = NO;
    return wrappingview;
}

@end
