//
//  JLEContralStickerDemo.m
//  Example
//
//  Created by jaalee on 14-4-23.
//  Copyright (c) 2014年 jaalee. All rights reserved.
//
//  http://www.jaalee.com/
//

#import "JLEContralStickerDemo.h"
#import "WaitProgressShow.h"

@interface JLEContralStickerDemo ()<JLEStickerDeviceDelegate>

@end

@implementation JLEContralStickerDemo

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    _mReadRSSITimer = nil;
    
    [self.mDistanceMode setSelectedSegmentIndex:0];
    
    if (self.mSelectStickerDevice) {
        self.mSelectStickerDevice.delegate = self;
        [self.mSelectStickerDevice connectToSticker];
        [WaitProgressShow showWithStatus:@"Trying to connect the sticker..."];
    }
    
    _mReadRSSITimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(readRSSI:) userInfo:Nil repeats:TRUE];//Read Rssi Value
    
}

- (void)viewDidDisappear:(BOOL)animated
{
    if (self.mSelectStickerDevice.isConnected)
    {
        [self.mSelectStickerDevice disconnectSticker];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark - JLEBeaconDeviceDelegate Callbacks

- (void)stickerConnectionDidSucceeded:(JLEStickerDevice *)sticker
{
    [WaitProgressShow showSuccessWithStatus:@"Connected successfully"];
    
    [self ReadParaFromBeacon];
}

- (void)stickerConnectionDidFail:(JLEStickerDevice *)sticker withError:(NSError *)error
{
    [WaitProgressShow showErrorWithStatus:@"Connect the sticker Failed"];
    [self.navigationController popToRootViewControllerAnimated:true];
}

- (void)stickerDidDisconnect:(JLEStickerDevice *)sticker withError:(NSError *)error
{
    [WaitProgressShow showErrorWithStatus:@"Disconnect from the sticker"];
    [self.navigationController popToRootViewControllerAnimated:true];
}


-(void)stickerDidUpdateRssi:(JLEStickerDevice *)sticker Error:(NSError *)error
{
    self.mRssiValue.text = [NSString stringWithFormat:@"%ld", (long)sticker.rssi];
}


#pragma mark - Read Beacon Parameter Method
- (void) ReadBattery
{
    if (self.mSelectStickerDevice.isConnected) {
        [self.mSelectStickerDevice readStickerBatteryWithCompletion:^(unsigned short value, NSError* error){
            self.mBattreyLevel.text = [NSString stringWithFormat:@"%d%%", value];
        }];
    }
}


- (void) ReadDeviceName
{
    if (self.mSelectStickerDevice.isConnected) {
        [self.mSelectStickerDevice readStickerDeviceNameWithCompletion:^(NSString *value, NSError* error){
            self.mStickerName.text = value;
        }];
    }
}

- (void) ReadDeviceState
{
    if (self.mSelectStickerDevice.isConnected) {
        [self.mSelectStickerDevice readStickerStateWithCompletion:^(Jaalee_Sticker_State value, NSError* error){
            if (value == STICKER_STATE_ENABLE) {
                [self.mStickerState setOn:true animated:true];
            }
            else
            {
                [self.mStickerState setOn:false animated:true];
            }
        }];
    }
}

#pragma mark - Write Beacon Parameter Method
- (void) ChangeTxPowerValue:(JLEStickerTxPower)power
{
    if (self.mSelectStickerDevice.isConnected) {
        
        [self.mSelectStickerDevice writeStickerTxPower:power withCompletion:^(BOOL value, NSError* error){
            
            if (value) {
                NSLog(@"Sticker Tx Power Config Success..");
                [WaitProgressShow showSuccessWithStatus:@"Sticker Tx Power Config Success.."];
            }
            
        }];
    }
}

- (void) ChangeDeviceName:(NSString*)name
{
    if (self.mSelectStickerDevice.isConnected) {
        [self.mSelectStickerDevice writeStickerDeviceName:name withCompletion:^(BOOL value, NSError* error){
            
            if (value) {
                NSLog(@"Sticker Device Name Config Success..");
                [WaitProgressShow showSuccessWithStatus:@"Sticker Device Name Config Success.."];
            }
            
        }];
    }
}

#pragma mark - Local Method

-(void) readRSSI:(NSTimer *)timer
{
    if (self.mSelectStickerDevice.isConnected) {
        [self.mSelectStickerDevice readStickerRSSIValue];
    }
}


-(void) ReadParaFromBeacon
{
    [UIView animateWithDuration:0.0 delay:1.0 options:UIViewAnimationOptionAllowUserInteraction animations:^{
    } completion:^(BOOL finished) {
        
        [self ReadBattery];
    }];
    
    [UIView animateWithDuration:0.0 delay:1.5 options:UIViewAnimationOptionAllowUserInteraction animations:^{
    } completion:^(BOOL finished) {
        
        [self ReadDeviceName];
    }];
    
    [UIView animateWithDuration:0.0 delay:2.0 options:UIViewAnimationOptionAllowUserInteraction animations:^{
    } completion:^(BOOL finished) {
        
        [self ReadDeviceState];
    }];
    
}



- (IBAction)OnSelectSegment:(id)sender {
    
    UISegmentedControl *temp = (UISegmentedControl *)sender;
    NSInteger Index = temp.selectedSegmentIndex;
    
    switch (Index) {
            
        case 0://-4 dBm
            [self ChangeTxPowerValue:JLEStickerTxPowerLevel3];
            break;
        case 1://0 dBm
            [self ChangeTxPowerValue:JLEStickerTxPowerLevel2];
            break;
        case 2://+4 dBm
            [self ChangeTxPowerValue:JLEStickerTxPowerLevel1];
            break;
        default:
            break;
    }

}
- (IBAction)OnTouchUpdateName:(id)sender {
    
    [self ChangeDeviceName:self.mStickerName.text];
}

- (IBAction)OnTouchCallSticker:(id)sender {
    
    if (self.mSelectStickerDevice.isConnected) {
        [self.mSelectStickerDevice callJaaleeSticker];
    }
}

- (IBAction)OnTouchBeaconState:(id)sender {
    
    UISwitch *temp = sender;
    [WaitProgressShow showWithStatus:@"Trying to set the sticker state"];
    if (temp.isOn) {
        if (self.mSelectStickerDevice.isConnected) {
            [self.mSelectStickerDevice writeStickerState:STICKER_STATE_ENABLE withCompletion:^(BOOL value, NSError* error){
                
                if (value) {
                    [WaitProgressShow showSuccessWithStatus:@"Sticker state set successfully"];
                }
                else
                {
                    [WaitProgressShow showSuccessWithStatus:@"Sticker state set failed"];
                }

            }];
        }
    }
    else
    {
        if (self.mSelectStickerDevice.isConnected) {
            [self.mSelectStickerDevice writeStickerState:STICKER_STATE_DISABLE withCompletion:^(BOOL value, NSError* error){
                
                if (value) {
                    [WaitProgressShow showSuccessWithStatus:@"Sticker state set successfully"];
                }
                else
                {
                    [WaitProgressShow showSuccessWithStatus:@"Sticker state set failed"];
                }
                
            }];
        }
    }
    
}
@end
