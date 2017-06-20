//
//  ACRImageRenderer
//  ACRImageRenderer.mm
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRImageRenderer.h"
#import "Image.h"
#import "AdaptiveCard.h"

@implementation ACRImageRenderer

+ (ACRImageRenderer* ) getInstance
{
    static ACRImageRenderer *singletonInstance = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{singletonInstance = [[self alloc] init];});
    return singletonInstance;
}

+ (CardElementType) elemType
{
    return CardElementType::Image;
}

- (CGSize) getImageSize:(std::shared_ptr<Image> const &) imgBlock 
         withHostConfig:(std::shared_ptr<HostConfig> const &) hostConfig
{
    float sz = hostConfig->imageSizes.mediumSize;
    switch (imgBlock->GetImageSize()){
        case ImageSize::Large: {
            sz = hostConfig->imageSizes.largeSize;
            break;
        }
        case ImageSize::Medium: {
            sz = hostConfig->imageSizes.mediumSize;
            break;
        }

        case ImageSize::Small: {
            sz = hostConfig->imageSizes.smallSize;
            break;
        }

        default: {
            NSLog(@"unimplemented");
        }
    }
    CGSize cgSize = CGSizeMake(sz, sz);
    return cgSize;
}

- (UIView* ) render: (UIView*) viewGroup
       withCardElem: (std::shared_ptr<BaseCardElement> const &) elem
       andHostCofig: (std::shared_ptr<HostConfig> const &) config
{
    std::shared_ptr<Image> imgElem = std::dynamic_pointer_cast<Image>(elem);

    NSURL *url = [NSURL URLWithString:
                  [NSString stringWithCString: imgElem->GetUrl().c_str()
                                     encoding:[NSString defaultCStringEncoding]]];
    
    UIImage* img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
    
    CGSize cgsize = [self getImageSize: imgElem withHostConfig: config];

    UIGraphicsBeginImageContext(cgsize);
    UIImageView* view = [[UIImageView alloc]
                         initWithFrame:CGRectMake(0, 0, cgsize.width, cgsize.height)];
    [img drawInRect:(CGRectMake(0, 0, cgsize.width, cgsize.height))];
    img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    view.image = img;

    if(imgElem->GetImageStyle() == ImageStyle::Person) {
        CALayer* imgLayer = view.layer;
        [imgLayer setCornerRadius:cgsize.width/2];
        [imgLayer setMasksToBounds:YES];
    }
    return view;
}

@end
