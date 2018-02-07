//
//  ACRViewController.m
//  ACRViewController
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import "ACRViewController.h"
#import "ACOHostConfigPrivate.h"
#import "ACOAdaptiveCardPrivate.h"
#import "SharedAdaptiveCard.h"
#import "ACRRendererPrivate.h"
#import <AVFoundation/AVFoundation.h>
#import "Container.h"
#import "ColumnSet.h"
#import "Column.h"
#import "Image.h"
#import "ACRImageRenderer.h"

using namespace AdaptiveCards;

@implementation ACRViewController
{
    std::shared_ptr<AdaptiveCard> _adaptiveCard;
    std::shared_ptr<HostConfig> _hostConfig;
    CGRect _guideFrame;
    NSMutableDictionary *_imageViewMap;
}

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if(self){
        _guideFrame = CGRectMake(0, 0, 0, 0);
        _hostConfig = std::make_shared<HostConfig>();
        _imageViewMap = [[NSMutableDictionary alloc] init];
    }
    return self;
}

// Initializes ACRViewController instance with HostConfig and AdaptiveCard
- (instancetype)init:(ACOAdaptiveCard *)card
          hostconfig:(ACOHostConfig *)config
               frame:(CGRect)frame
{
    self = [self initWithNibName:nil bundle:nil];
    if(self)
    {
        _adaptiveCard = [card getCard];
        if(config)
        {
            _hostConfig = [config getHostConfig];
        }
        _guideFrame = frame;
        _imageViewMap = [[NSMutableDictionary alloc] init];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    [self render];
}

- (void)render
{
    UIView *view = self.view;
    view.frame = _guideFrame;
    NSMutableArray *inputs = [[NSMutableArray alloc] init];

    std::string backgroundImage = _adaptiveCard->GetBackgroundImage();
    NSString* imgUrl = nil;
    if(!backgroundImage.empty())
        imgUrl = [[NSString alloc] initWithCString:backgroundImage.c_str() encoding:NSUTF8StringEncoding];
    if (imgUrl)
    {
        NSURL *url = [NSURL URLWithString:imgUrl];
        UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
        UIImageView *imgView = [[UIImageView alloc] initWithImage:img];
        [view addSubview:imgView];
        [view sendSubviewToBack:imgView];
        [NSLayoutConstraint activateConstraints:
         @[[imgView.trailingAnchor constraintEqualToAnchor:view.trailingAnchor],
           [imgView.topAnchor constraintEqualToAnchor:view.topAnchor],
           [imgView.trailingAnchor constraintEqualToAnchor:view.trailingAnchor],
           ]];
    }
    ContainerStyle style = (_hostConfig->adaptiveCard.allowCustomStyle)? _adaptiveCard->GetStyle() : _hostConfig->actions.showCard.style;
    if(style != ContainerStyle::None)
    {
        unsigned long num = 0;
        if(style == ContainerStyle::Emphasis)
        {
            num = std::stoul(_hostConfig->containerStyles.emphasisPalette.backgroundColor.substr(1), nullptr, 16);
        }
        else
        {
            num = std::stoul(_hostConfig->containerStyles.defaultPalette.backgroundColor.substr(1), nullptr, 16);
        }
        view.backgroundColor =
        [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                        green:((num & 0x0000FF00) >>  8) / 255.0
                         blue:((num & 0x000000FF)) / 255.0
                        alpha:((num & 0xFF000000) >> 24) / 255.0];
    }
    std::vector<std::shared_ptr<BaseCardElement>> body = _adaptiveCard->GetBody();
    if(!body.empty())
    {
        // loop through elements and find images or text blocks
        // images splits over two task, loading and scaling
        // text has only one taks initializing attributed text
        // get concurrent gcd queue
        // dispatch sync for image downloading
        // dispatch async for image scaling
        // --> cache the result
        // disptach async attributed text
        // --> cache  the result
        // wait till all task is done
        // execute the rest of the code
        // transforms (i.e. renders) an adaptiveCard to a new UIView instance
        [self addImageBlockToConcurrentQueue:body];
    }
    
    UIView *newView = [ACRRenderer renderWithAdaptiveCards:_adaptiveCard
                                                             inputs:inputs
                                                     viewController:self
                                                         guideFrame:_guideFrame
                                                         hostconfig:_hostConfig];
    // new rendered adaptiveCard view is added as a sub view
    [view addSubview:newView];
    // affix the left margin of the rendered adaptiveCard to current view
    NSLayoutConstraint *constraint =
    [NSLayoutConstraint constraintWithItem:view
                                 attribute:NSLayoutAttributeLeading
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeLeading
                                multiplier:1.0
                                  constant:0];
    [view addConstraint:constraint];
    // affix the right margin of the rendered adaptiveCard to current view
    constraint =
    [NSLayoutConstraint constraintWithItem:view
                                 attribute:NSLayoutAttributeTrailing
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeTrailing
                                multiplier:1.0
                                  constant:0];
    [view addConstraint:constraint];

    constraint =
    [NSLayoutConstraint constraintWithItem:view
                                 attribute:NSLayoutAttributeTop
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeTop
                                multiplier:1.0
                                  constant:0];
    [view addConstraint:constraint];

    constraint =
    [NSLayoutConstraint constraintWithItem:view
                                 attribute:NSLayoutAttributeBottom
                                 relatedBy:NSLayoutRelationGreaterThanOrEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeBottom
                                multiplier:1.0
                                  constant:0];
    [view addConstraint:constraint];

    [NSLayoutConstraint activateConstraints:
     @[[newView.leadingAnchor constraintEqualToAnchor:view.leadingAnchor],
       [newView.topAnchor constraintEqualToAnchor:view.topAnchor]]];
}

- (void) addImageBlockToConcurrentQueue:(std::vector<std::shared_ptr<BaseCardElement>> const &) body
{
    for(auto &elem : body)
    {
        switch (elem->GetElementType())
        {
            case CardElementType::Image:
            {
                //dispatch_queue_t syncQueue = dispatch_queue_create("io.AdaptiveCards.syncQueue", NULL);
                /// dispatch to concurrent queue
                dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^
                {
                    std::shared_ptr<Image> imgElem = std::dynamic_pointer_cast<Image>(elem);
                    NSString *urlStr = [NSString stringWithCString:imgElem->GetUrl().c_str()
                                                          encoding:[NSString defaultCStringEncoding]];
                    NSLog(@"entered");
                    NSURL *url = [NSURL URLWithString:urlStr];

                    UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];

                    CGSize cgsize = [ACRImageRenderer getImageSize:imgElem withHostConfig:_hostConfig];

                    UIGraphicsBeginImageContext(cgsize);
                    [img drawInRect:(CGRectMake(0, 0, cgsize.width, cgsize.height))];
                    img = UIGraphicsGetImageFromCurrentImageContext();
                    UIGraphicsEndImageContext();
                    dispatch_sync(dispatch_get_main_queue(), ^
                                  {
                                      NSLog(@"recording");
                                      NSNumber *key = [NSNumber numberWithUnsignedLong: (unsigned long)elem.get()];
                                      UIImageView *view = _imageViewMap[key];
                                      if (!view)
                                      {
                                          NSLog(@"view is not ready");
                                      }
                                      else{
                                      view.image = img;
                                      }
                                  });

                });
                break;
            }
            case CardElementType::Container:
            {
                std::shared_ptr<Container> container = std::static_pointer_cast<Container>(elem);
                std::vector<std::shared_ptr<BaseCardElement>> &new_body = container->GetItems();
                [self addImageBlockToConcurrentQueue: new_body];
                break;
            }
            case CardElementType::Column:
            {
                std::shared_ptr<Column> colum = std::static_pointer_cast<Column>(elem);
                std::vector<std::shared_ptr<BaseCardElement>> &new_body = colum->GetItems();
                [self addImageBlockToConcurrentQueue: new_body];
                break;
            }
            case CardElementType::ColumnSet:
            {
                std::shared_ptr<ColumnSet> columSet = std::static_pointer_cast<ColumnSet>(elem);
                std::vector<std::shared_ptr<Column>> &columns = columSet->GetColumns();
                for(auto &colum : columns)
                {
                    [self addImageBlockToConcurrentQueue: colum->GetItems()];
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

- (NSMutableDictionary *) getImageMap
{
    return _imageViewMap;
}

@end
