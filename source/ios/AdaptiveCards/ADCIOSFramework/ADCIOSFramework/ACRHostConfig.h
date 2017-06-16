//
//  ADCIOSAdaptiveHostConfig.h
//  ADCIOSFramework
//
//  Created by jwoo on 6/7/17.
//  Copyright © 2017 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "TextBlock.h"
#import "Image.h"
#import "HostConfig.h"

using namespace AdaptiveCards;

@interface ACRHostConfig:NSObject

- (CGSize) getImageSize:(std::shared_ptr<Image>) img;

- (UIColor* ) getTextBlockColor:(std::shared_ptr<AdaptiveCards::TextBlock>) txtBlock;

- (int) getTextBlockTexSize:(std::shared_ptr<TextBlock>)txtBlock;

- (NSTextAlignment) getTextBlockAlignment:(std::shared_ptr<TextBlock>) txtBlock;

- (NSNumber* ) getTextBlockTextWeight:(std::shared_ptr<TextBlock>) txtBlock;

@property std::shared_ptr<HostConfig> m_hostConfig;

@end    
