//
//  JLEStickerManager.h
//  JaaleeStickerSDK
//
//  Created by jaalee on 14-4-22.
//  Copyright (c) 2014年 jaalee. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JLEStickerDevice.h"


@class JLEStickerManager;

/**
 
 The JLEStickerManagerDelegateJLEStickerManagerDelegate protocol defines the delegate methods to respond for related events.
 */

@protocol JLEStickerManagerDelegate <NSObject>

@optional

/**
 * Delegate method invoked to handle discovered
 * JLEStickerDevice objects using CoreBluetooth framework
 * in particular region.
 *
 * @param manager jaalee sticker manager
 * @param sticker discovered sticker
 *
 * @return void
 */

- (void)stickerManager:(JLEStickerManager *)manager didDiscoverSticker:(JLEStickerDevice *)sticker RSSI:(NSNumber *)RSSI;

@end


@interface JLEStickerManager : NSObject

@property (nonatomic, weak) id <JLEStickerManagerDelegate> delegate;


/// @name CoreBluetooth based utility methods


/**
 * Start sticker discovery process based on CoreBluetooth
 * framework. 
 *
 *
 * @return void
 */
-(void)startJaaleeStickersDiscovery;


/**
 * Stops CoreBluetooth based sticker discovery process.
 *
 * @return void
 */
-(void)stopJaaleeStickersDiscovery;


@end
