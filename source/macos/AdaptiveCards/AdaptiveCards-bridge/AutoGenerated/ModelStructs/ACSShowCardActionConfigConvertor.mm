// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "HostConfig.h"
#import "Enums.h"

#import "ACSShowCardActionConfigConvertor.h"
#import "ACSActionModeConvertor.h"
#import "ACSContainerStyleConvertor.h"
#import "ACSActionMode.h"
#import "ACSContainerStyle.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSShowCardActionConfigConvertor 

+(ACSShowCardActionConfig *) convertCpp:(const AdaptiveCards::ShowCardActionConfig& )showCardActionConfigCpp
{ 
     @autoreleasepool { 
 
        ACSShowCardActionConfig*  showCardActionConfigCocoa = [[ ACSShowCardActionConfig  alloc] initWithActionMode: [ACSActionModeConvertor convertCpp:showCardActionConfigCpp.actionMode] 
        style: [ACSContainerStyleConvertor convertCpp:showCardActionConfigCpp.style]
        inlineTopMargin: [NSNumber numberWithUnsignedInt:showCardActionConfigCpp.inlineTopMargin]];
        return  showCardActionConfigCocoa;
   }
}

+(AdaptiveCards::ShowCardActionConfig) convertObj:(ACSShowCardActionConfig *)showCardActionConfigObjc {
  AdaptiveCards::ShowCardActionConfig showCardActionConfigCpp;
  showCardActionConfigCpp.actionMode = [ACSActionModeConvertor convertObj:showCardActionConfigObjc.actionMode];
  showCardActionConfigCpp.style = [ACSContainerStyleConvertor convertObj:showCardActionConfigObjc.style];
  showCardActionConfigCpp.inlineTopMargin = [showCardActionConfigObjc.inlineTopMargin unsignedIntValue];
  return  showCardActionConfigCpp;
}

@end 
