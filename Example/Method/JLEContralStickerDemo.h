//
//  JLEContralStickerDemo.h
//  Example
//
//  Created by jaalee on 14-4-23.
//  Copyright (c) 2014年 jaalee. All rights reserved.
//
//  http://www.jaalee.com/
//


#import "JLEStickerDevice.h"
#import "JLEStickerManager.h"

@interface JLEContralStickerDemo : UIViewController

@property (weak, nonatomic) IBOutlet UILabel *mRssiValue;

@property (weak, nonatomic) IBOutlet UILabel *mBattreyLevel;

@property (weak, nonatomic) IBOutlet UISegmentedControl *mDistanceMode;

@property (weak, nonatomic) IBOutlet UITextField *mStickerName;

@property (weak, nonatomic) IBOutlet NSTimer *mReadRSSITimer;

@property (weak, nonatomic) IBOutlet UISwitch *mStickerState;
- (IBAction)OnSelectSegment:(id)sender;

@property (nonatomic, strong) JLEStickerDevice          *mSelectStickerDevice;

- (IBAction)OnTouchUpdateName:(id)sender;

- (IBAction)OnTouchCallSticker:(id)sender;

- (IBAction)OnTouchBeaconState:(id)sender;


@end
