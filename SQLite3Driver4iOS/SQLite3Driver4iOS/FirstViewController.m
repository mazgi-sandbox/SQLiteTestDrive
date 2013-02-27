//
//  FirstViewController.m
//  SQLite3Driver4iOS
//
//  Created by Matsuki Hidenori on 2/7/13.
//  Copyright (c) 2013 Matsuki Hidenori. All rights reserved.
//

#import "FirstViewController.h"
#import "SQLiteDriver.h"

@interface FirstViewController ()
- (IBAction)runButtonDidTouchUpInside:(id)sender;
@end

@implementation FirstViewController

- (IBAction)runButtonDidTouchUpInside:(id)sender {
    NSLog(@"%05d:[info]%s called.", __LINE__, __PRETTY_FUNCTION__);
}

#pragma mark - view lifecycle

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
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
@end
