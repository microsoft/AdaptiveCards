//
//  ACRView.m
//  ACRView
//
//  Copyright © 2018 Microsoft. All rights reserved.
//

#import "ACRView.h"
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
#import "TextBlock.h"
#import "ACRTextBlockRenderer.h"
#import "MarkDownParser.h"
#import "ImageSet.h"
#import "ACRUILabel.h"

using namespace AdaptiveCards;

@implementation ACRView
{
    ACOAdaptiveCard *_adaptiveCard;
    ACOHostConfig *_hostConfig;
    NSMutableDictionary *_imageViewMap;
    NSMutableDictionary *_textMap;
    dispatch_queue_t _serial_queue;
    dispatch_queue_t _serial_text_queue;
    int _serialNumber;
    std::list<const BaseCardElement*> _asyncRenderedElements;
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
        _serialNumber = 0;
    }
    return self;
}

// Initializes ACRView instance with HostConfig and AdaptiveCard
- (instancetype)init:(ACOAdaptiveCard *)card
          hostconfig:(ACOHostConfig *)config
               frame:(CGRect)frame
{
    self = [self initWithFrame:frame];
    if(self)
    {
        _adaptiveCard = card;
        if(config)
        {
            _hostConfig = config;
        }
        [self render];

        [self callDidLoadElementsIfNeeded];
    }
    return self;
}

- (void)render
{
    //UIView *view = self.view;
    NSMutableArray *inputs = [[NSMutableArray alloc] init];

    std::string backgroundImage = [_adaptiveCard card]->GetBackgroundImage();
    NSString* imgUrl = nil;
    if(!backgroundImage.empty())
        imgUrl = [[NSString alloc] initWithCString:backgroundImage.c_str() encoding:NSUTF8StringEncoding];
    if (imgUrl)
    {
        NSURL *url = [NSURL URLWithString:imgUrl];
        UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
        UIImageView *imgView = [[UIImageView alloc] initWithImage:img];
        [self addSubview:imgView];
        [self sendSubviewToBack:imgView];
        [NSLayoutConstraint activateConstraints:
         @[[imgView.trailingAnchor constraintEqualToAnchor:self.trailingAnchor],
           [imgView.topAnchor constraintEqualToAnchor:self.topAnchor],
           [imgView.trailingAnchor constraintEqualToAnchor:self.trailingAnchor],
           ]];
    }
    ContainerStyle style = ([_hostConfig getHostConfig]->adaptiveCard.allowCustomStyle)? [_adaptiveCard card]->GetStyle(): ContainerStyle::Default;
    if(style != ContainerStyle::None)
    {
        unsigned long num = 0;
        if(style == ContainerStyle::Emphasis)
        {
            num = std::stoul([_hostConfig getHostConfig]->containerStyles.emphasisPalette.backgroundColor.substr(1), nullptr, 16);
        }
        else
        {
            num = std::stoul([_hostConfig getHostConfig]->containerStyles.defaultPalette.backgroundColor.substr(1), nullptr, 16);
        }
        self.backgroundColor =
        [UIColor colorWithRed:((num & 0x00FF0000) >> 16) / 255.0
                        green:((num & 0x0000FF00) >>  8) / 255.0
                         blue:((num & 0x000000FF)) / 255.0
                        alpha:((num & 0xFF000000) >> 24) / 255.0];
    }
    std::vector<std::shared_ptr<BaseCardElement>> body = [_adaptiveCard card]->GetBody();


    UIView *newView = [ACRRenderer renderWithAdaptiveCards:[_adaptiveCard card]
                                                             inputs:inputs
                                                           rootView:self
                                                         guideFrame:self.frame
                                                         hostconfig:_hostConfig];
    // new rendered adaptiveCard view is added as a sub view
    [self addSubview:newView];
    // affix the left margin of the rendered adaptiveCard to current view
    NSLayoutConstraint *constraint =
    [NSLayoutConstraint constraintWithItem:self
                                 attribute:NSLayoutAttributeLeading
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeLeading
                                multiplier:1.0
                                  constant:0];
    [self addConstraint:constraint];
    // affix the right margin of the rendered adaptiveCard to current view
    constraint =
    [NSLayoutConstraint constraintWithItem:self
                                 attribute:NSLayoutAttributeTrailing
                                 relatedBy:NSLayoutRelationEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeTrailing
                                multiplier:1.0
                                  constant:0];
    [self addConstraint:constraint];

    constraint =
    [NSLayoutConstraint constraintWithItem:self
                                 attribute:NSLayoutAttributeTop
                                 relatedBy:NSLayoutRelationLessThanOrEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeTop
                                multiplier:1.0
                                  constant:0];
    [self addConstraint:constraint];

    constraint =
    [NSLayoutConstraint constraintWithItem:self
                                 attribute:NSLayoutAttributeBottom
                                 relatedBy:NSLayoutRelationGreaterThanOrEqual
                                    toItem:newView
                                 attribute:NSLayoutAttributeBottom
                                multiplier:1.0
                                  constant:0];
    [self addConstraint:constraint];

    [NSLayoutConstraint activateConstraints:
     @[[newView.leadingAnchor constraintEqualToAnchor:self.leadingAnchor],
       [newView.topAnchor constraintEqualToAnchor:self.topAnchor]]];
}

- (void)addToAsyncRenderingList:(std::shared_ptr<BaseCardElement> const &)elem
{
    _asyncRenderedElements.push_back(elem.get());
}

- (void)removeFromAsyncRenderingListAndNotifyIfNeeded:(std::shared_ptr<BaseCardElement> const &)elem
{
    _asyncRenderedElements.remove(elem.get());

    [self callDidLoadElementsIfNeeded];
}

- (void)callDidLoadElementsIfNeeded
{
    if (_asyncRenderedElements.size() == 0)
    {
        // Call back app with didLoadElements
        if ([[self acrActionDelegate] respondsToSelector:@selector(didLoadElements)])
        {
            [[self acrActionDelegate] didLoadElements];
        }
    }
}

// Walk through adaptive cards elements recursively and if images/images set/TextBlocks are found process them concurrently
- (void) addTasksToConcurrentQueue:(std::vector<std::shared_ptr<BaseCardElement>> const &) body
{
    for(auto &elem : body)
    {
        switch (elem->GetElementType())
        {
            case CardElementType::TextBlock:
            {
                [self addToAsyncRenderingList:elem];

                /// tag a base card element with unique key
                [self tagBaseCardElement:elem];
                /// dispatch to concurrent queue
                std::shared_ptr<TextBlock> txtElem = std::dynamic_pointer_cast<TextBlock>(elem);
                dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0),
                    ^{
                        std::string dateParsedString = [ACOHostConfig getLocalizedDate:txtElem];
                        // MarkDownParser transforms text with MarkDown to a html string
                        std::shared_ptr<MarkDownParser> markDownParser = std::make_shared<MarkDownParser>(dateParsedString.c_str());
                        NSString *parsedString = [NSString stringWithCString:markDownParser->TransformToHtml().c_str() encoding:NSUTF8StringEncoding];
                        // if correctly initialized, fonFamilyNames array is bigger than zero
                        NSMutableString *fontFamilyName = [[NSMutableString alloc] initWithString:@"'"];
                        for(NSUInteger index = 0; index < [_hostConfig.fontFamilyNames count] - 1; ++index){
                            [fontFamilyName appendString:_hostConfig.fontFamilyNames[index]];
                            [fontFamilyName appendString:@"', '"];
                        }
                        [fontFamilyName appendString:_hostConfig.fontFamilyNames[[_hostConfig.fontFamilyNames count] - 1]];
                        [fontFamilyName appendString:@"'"];

                        // Font and text size are applied as CSS style by appending it to the html string
                        const int fontWeight = [_hostConfig getTextBlockFontWeight:txtElem->GetTextWeight()];
                        parsedString = [parsedString stringByAppendingString:[NSString stringWithFormat:@"<style>body{font-family: %@; font-size:%dpx; font-weight: %d;}</style>",
                                                                              fontFamilyName,
                                                                              [_hostConfig getTextBlockTextSize:txtElem->GetTextSize()],
                                                                              fontWeight]];
                        // Convert html string to NSMutableAttributedString, NSAttributedString knows how to apply html tags
                        NSData *htmlData = [parsedString dataUsingEncoding:NSUTF16StringEncoding];
                        NSDictionary *options = @{NSDocumentTypeDocumentAttribute: NSHTMLTextDocumentType};

                        dispatch_async(dispatch_get_main_queue(),
                             ^{
                                  // Initializing NSMutableAttributedString for HTML rendering is very slow
                                  NSMutableAttributedString *content = [[NSMutableAttributedString alloc] initWithData:htmlData options:options documentAttributes:nil error:nil];

                                  __block ACRUILabel *lab = nil; // generate key for text map from TextBlock element's id
                                  NSString *key = [NSString stringWithCString:txtElem->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
                                  // syncronize access to text map
                                  dispatch_sync(_serial_text_queue,
                                      ^{
                                           // UILabel is not ready, cashe UILabel
                                           if(!_textMap[key]) {
                                               _textMap[key] = content;
                                           } // UILable is ready, get label
                                           else {
                                               lab = _textMap[key];
                                           }
                                      });

                                   // if a label is available, set NSAttributedString to it
                                  if(lab) {
                                      // Set paragraph style such as line break mode and alignment
                                      NSMutableParagraphStyle *paragraphStyle = [[NSMutableParagraphStyle alloc] init];
                                      paragraphStyle.lineBreakMode = txtElem->GetWrap() ? NSLineBreakByWordWrapping:NSLineBreakByTruncatingTail;
                                      paragraphStyle.alignment = [ACOHostConfig getTextBlockAlignment:txtElem->GetHorizontalAlignment()];

                                      // Obtain text color to apply to the attributed string
                                      ACRContainerStyle style = lab.style;
                                      ColorsConfig &colorConfig = (style == ACREmphasis)? [_hostConfig getHostConfig]->containerStyles.emphasisPalette.foregroundColors:
                                                                                                             [_hostConfig getHostConfig]->containerStyles.defaultPalette.foregroundColors;
                                      // Add paragraph style, text color, text weight as attributes to a NSMutableAttributedString, content.
                                      [content addAttributes:@{
                                                               NSParagraphStyleAttributeName:paragraphStyle,
                                                               NSForegroundColorAttributeName:[ACOHostConfig getTextBlockColor:txtElem->GetTextColor() colorsConfig:colorConfig subtleOption:txtElem->GetIsSubtle()],
                                                               }
                                                       range:NSMakeRange(0, content.length - 1)];
                                      lab.attributedText = content;
                                      // remove tag
                                      std::string id = txtElem->GetId();
                                      std::size_t idx = id.find_last_of('_');
                                      txtElem->SetId(id.substr(0, idx));
                                  }

                                  [self removeFromAsyncRenderingListAndNotifyIfNeeded:txtElem];
                              });
                         }
                );
                break;
            }
            case CardElementType::Image:
            {
                /// tag a base card element with unique key
                [self tagBaseCardElement:elem];
                std::shared_ptr<Image>imgElem = std::static_pointer_cast<Image>(elem);
                // dispatch to concurrent queue
                [self processImageConcurrently:imgElem];
                break;
            }
            case CardElementType::ImageSet:
            {
                std::shared_ptr<ImageSet>imgSetElem = std::static_pointer_cast<ImageSet>(elem);
                for(auto img :imgSetElem->GetImages()) { // loops through images in image set
                    std::shared_ptr<BaseCardElement> baseImgElem = std::static_pointer_cast<BaseCardElement>(img);
                    /// tag a base card element with unique key
                    [self tagBaseCardElement:baseImgElem];
                    img->SetImageSize(imgSetElem->GetImageSize());
                    [self processImageConcurrently:img];
                }
                break;
            }
            // continue on search
            case CardElementType::Container:
            {
                std::shared_ptr<Container> container = std::static_pointer_cast<Container>(elem);
                std::vector<std::shared_ptr<BaseCardElement>> &new_body = container->GetItems();
                [self addTasksToConcurrentQueue: new_body];
                break;
            }
            // continue on search
            case CardElementType::Column:
            {
                std::shared_ptr<Column> colum = std::static_pointer_cast<Column>(elem);
                std::vector<std::shared_ptr<BaseCardElement>> &new_body = colum->GetItems();
                [self addTasksToConcurrentQueue: new_body];
                break;
            }
            // continue on search
            case CardElementType::ColumnSet:
            {
                std::shared_ptr<ColumnSet> columSet = std::static_pointer_cast<ColumnSet>(elem);
                std::vector<std::shared_ptr<Column>> &columns = columSet->GetColumns();
                // ColumnSet is vector of Column, instead of vector of BaseCardElement
                for(auto &colum : columns) { // update serial number that is used for generating unique key for image_map
                    [self addTasksToConcurrentQueue: colum->GetItems()];
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

- (void) processImageConcurrently:(std::shared_ptr<Image> const &)imageElem
{
    [self addToAsyncRenderingList:imageElem];

    /// generate a string key to uniquely identify Image
    std::shared_ptr<Image> imgElem = imageElem;
    // run image downloading and processing on global queue which is concurrent and different from main queue
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0),
        ^{
             NSString *urlStr = [NSString stringWithCString:imgElem->GetUrl().c_str()
                                                   encoding:[NSString defaultCStringEncoding]];
             // generate key for imageMap from image element's id
             NSString *key = [NSString stringWithCString:imgElem->GetId().c_str() encoding:[NSString defaultCStringEncoding]];
             NSURL *url = [NSURL URLWithString:urlStr];
             // download image
             UIImage *img = [UIImage imageWithData:[NSData dataWithContentsOfURL:url]];
             CGSize cgsize = [_hostConfig getImageSize:imgElem->GetImageSize()];

             // UITask can't be run on global queue, add task to main queue
             dispatch_async(dispatch_get_main_queue(),
                 ^{
                      __block UIImageView *view = nil;
                      // syncronize access to image map
                      dispatch_sync(_serial_queue,
                          ^{
                               if(!_imageViewMap[key]) {// UIImageView is not ready, cashe UIImage
                                   _imageViewMap[key] = img;
                               } else {// UIImageView ready, get view
                                   view = _imageViewMap[key];
                               }
                          });
                      // if view is available, set image to it, and continue image processing
                      if(view) {
                          view.image = img;
                          view.contentMode = UIViewContentModeScaleAspectFit;
                          view.clipsToBounds = NO;
                          if(imgElem->GetImageStyle() == ImageStyle::Person) {
                              CALayer *imgLayer = view.layer;
                              [imgLayer setCornerRadius:cgsize.width/2];
                              [imgLayer setMasksToBounds:YES];
                          }
                          // remove tag
                          std::string id = imgElem->GetId();
                          std::size_t idx = id.find_last_of('_');
                          imgElem->SetId(id.substr(0, idx));
                      }

                      [self removeFromAsyncRenderingListAndNotifyIfNeeded:imgElem];
                  });
             }
    );
}
// add postfix to existing BaseCardElement ID to be used as key
-(void) tagBaseCardElement:(std::shared_ptr<BaseCardElement> const &) elem
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
- (dispatch_queue_t)getSerialQueue
{
    return _serial_queue;
}

- (dispatch_queue_t)getSerialTextQueue
{
    return _serial_text_queue;
}

- (NSMutableDictionary *)getTextMap
{
    return _textMap;
}

- (ACOAdaptiveCard *)card
{
    return _adaptiveCard;
}
@end
