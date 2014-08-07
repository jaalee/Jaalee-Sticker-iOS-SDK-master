//
//  JLEStickerDefinitions.h
//  JaaleeStickerSDK
//
//  Created by jaalee on 14-4-22.
//  Copyright (c) 2014年 jaalee. All rights reserved.
//
//  http://www.jaalee.com/
//

#import <Foundation/Foundation.h>


typedef enum : char
{
    JLEStickerPowerLevel1 = -23,
    JLEStickerPowerLevel2 = -6,
    JLEStickerPowerLevel3 = 0
} JLEStickerPower;


typedef NS_ENUM(NSInteger, JaaLeeConnectParameter) {
	JLEConnectParameter_100 = 0,//100ms
    JLEConnectParameter_500,//500ms
    JLEConnectParameter_1000,//1s
    JLEConnectParameter_1800,//1800ms
    JLEConnectParameter_2000,//2s
};


typedef void(^JLECompletionBlock) (NSError* error);
typedef void(^JLEUnsignedShortCompletionBlock) (unsigned short value, NSError* error);
typedef void(^JLEPowerCompletionBlock) (JLEStickerPower value, NSError* error);
typedef void(^JLEBoolCompletionBlock) (BOOL value, NSError* error);
typedef void(^JLEStringCompletionBlock) (NSString* value, NSError* error);




////////////////////////////////////////////////////////////////////
// Interface definition

@interface JLEStickerDefinitions : NSObject

@end
