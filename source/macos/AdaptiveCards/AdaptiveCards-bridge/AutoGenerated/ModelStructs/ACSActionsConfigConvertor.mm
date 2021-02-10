// DO NOT EDIT - Auto generated
// Generated with objc_convertor.j2

//cpp includes 
#import "../../../../../shared/cpp/ObjectModel/HostConfig.h"
#import "../../../../../shared/cpp/ObjectModel/Enums.h"

#import "ACSActionsConfigConvertor.h"
#import "ACSActionAlignmentConvertor.h"
#import "ACSActionsOrientationConvertor.h"
#import "ACSIconPlacementConvertor.h"
#import "ACSShowCardActionConfigConvertor.h"
#import "ACSSpacingConvertor.h"
#import "ACSActionAlignment.h"
#import "ACSActionsOrientation.h"
#import "ACSIconPlacement.h"
#import "ACSSpacing.h"
#import "SwiftInterfaceHeader.h"
// #import "ConversionUtils.h"

@implementation ACSActionsConfigConvertor 

+(ACSActionsConfig *) convertCpp:(const AdaptiveCards::ActionsConfig& )actionsConfigCpp
{ 
     @autoreleasepool { 
 
        ACSActionsConfig*  actionsConfigCocoa = [[ ACSActionsConfig  alloc] initWithShowCard: [ACSShowCardActionConfigConvertor convertCpp:actionsConfigCpp.showCard] 
        actionsOrientation: [ACSActionsOrientationConvertor convertCpp:actionsConfigCpp.actionsOrientation]
        actionAlignment: [ACSActionAlignmentConvertor convertCpp:actionsConfigCpp.actionAlignment]
        buttonSpacing: [NSNumber numberWithUnsignedInt:actionsConfigCpp.buttonSpacing]
        maxActions: [NSNumber numberWithUnsignedInt:actionsConfigCpp.maxActions]
        spacing: [ACSSpacingConvertor convertCpp:actionsConfigCpp.spacing]
        iconPlacement: [ACSIconPlacementConvertor convertCpp:actionsConfigCpp.iconPlacement]
        iconSize: [NSNumber numberWithUnsignedInt:actionsConfigCpp.iconSize]];
        return  actionsConfigCocoa;
   }
}

+(AdaptiveCards::ActionsConfig) convertObj:(ACSActionsConfig *)actionsConfigObjc {
  AdaptiveCards::ActionsConfig actionsConfigCpp;
  actionsConfigCpp.showCard = [ACSShowCardActionConfigConvertor convertObj:actionsConfigObjc.showCard];
  actionsConfigCpp.actionsOrientation = [ACSActionsOrientationConvertor convertObj:actionsConfigObjc.actionsOrientation];
  actionsConfigCpp.actionAlignment = [ACSActionAlignmentConvertor convertObj:actionsConfigObjc.actionAlignment];
  actionsConfigCpp.buttonSpacing = [actionsConfigObjc.buttonSpacing unsignedIntValue];
  actionsConfigCpp.maxActions = [actionsConfigObjc.maxActions unsignedIntValue];
  actionsConfigCpp.spacing = [ACSSpacingConvertor convertObj:actionsConfigObjc.spacing];
  actionsConfigCpp.iconPlacement = [ACSIconPlacementConvertor convertObj:actionsConfigObjc.iconPlacement];
  actionsConfigCpp.iconSize = [actionsConfigObjc.iconSize unsignedIntValue];
  return  actionsConfigCpp;
}

@end 
