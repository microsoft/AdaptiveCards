//
//  ACRTableView.h
//  SPMTest
//
//  Created by Inyoung Woo on 5/14/21.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class ACOBaseCardElement
@class ACOHostConfig

typedef struct  ACRWidth ACRWidth;

@interface ACRTableView : UIView

- (instancetype)init:(ACOBaseCardElement *)element config:(ACOHostConfig *)config;

@end

NS_ASSUME_NONNULL_END
