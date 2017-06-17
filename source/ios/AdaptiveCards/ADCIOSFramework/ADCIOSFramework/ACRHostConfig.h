//
//  ADCIOSAdaptiveHostConfig.h
//  ADCIOSFramework
//
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "TextBlock.h"
#import "Image.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@interface ACRHostConfig:NSObject

- (CGSize) getImageSize:(std::shared_ptr<Image> const &) img;

- (UIColor* ) getTextBlockColor:(std::shared_ptr<AdaptiveCards::TextBlock> const &) txtBlock;

- (int) getTextBlockTextSize:(std::shared_ptr<TextBlock> const &)txtBlock;

- (NSTextAlignment) getTextBlockAlignment:(std::shared_ptr<TextBlock> const &) txtBlock;

- (NSNumber* ) getTextBlockTextWeight:(std::shared_ptr<TextBlock> const &) txtBlock;

@property std::shared_ptr<HostConfig> m_hostConfig;

@end    
