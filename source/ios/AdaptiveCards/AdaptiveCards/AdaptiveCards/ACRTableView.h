//
//  ACRTableView.h
//  SPMTest
//
//  Created by Inyoung Woo on 5/14/21.
//

#import <UIKit/UIKit.h>
#import "ACRView.h"

NS_ASSUME_NONNULL_BEGIN


@class ACOBaseCardElement;
@class ACOHostConfig;

typedef struct  ACRWidth ACRWidth;

@interface ACRTableView : UIView

- (instancetype)init:(ACOBaseCardElement *)acoElement
           viewGroup:(UIView<ACRIContentHoldingView> *)viewGroup
            rootView:(ACRView *)rootView
              inputs:(NSMutableArray *)inputs
          hostConfig:(ACOHostConfig *)acoConfig;

@end

NS_ASSUME_NONNULL_END
