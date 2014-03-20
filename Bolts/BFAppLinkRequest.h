/*
 *  Copyright (c) 2014, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */

#import <Foundation/Foundation.h>

#import "BFTask.h"
#import "BFAppLink.h"

/*!
 The result of calling navigate on a BFAppLinkRequest
 */
typedef NS_ENUM(NSInteger, BFAppLinkNavigationType) {
    /*! Indicates that the navigation failed and no app was opened */
    BFAppLinkNavigationTypeFailure,
    /*! Indicates that the navigation succeeded by opening the URL in the browser */
    BFAppLinkNavigationTypeBrowser,
    /*! Indicates that the navigation succeeded by opening the URL in an app on the device */
    BFAppLinkNavigationTypeApp
};

@protocol BFAppLinkResolving;

/*!
 Represents a pending request to navigate to an App Link. Most developers will
 simply use navigateToURLInBackground: to open a URL, but developers can build
 custom requests with additional navigation and app data attached to them by
 creating BFAppLinkRequests themselves.
 */
@interface BFAppLinkRequest : NSObject

/*!
 The referer_data for the AppLinkRequest. This will generally contain application-specific
 data that should be passed along with the request, such as advertiser or affiliate IDs or
 other such metadata relevant on this device.
 */
@property (readonly, strong) NSDictionary *appData;

/*!
 The al_applink_data for the AppLinkRequest. This will generally contain data common to
 navigation attempts such as back-links, user agents, and other information that may be used
 in routing and handling an App Link request.
 */
@property (readonly, strong) NSDictionary *navigationData;

/*! The AppLink to navigate to */
@property (readonly, strong) BFAppLink *appLink;

/* Creates an AppLinkRequest with the given link, app data, and navigation data */
+ (instancetype)requestWithAppLink:(BFAppLink *)appLink
                           appData:(NSDictionary *)appData
                    navigationData:(NSDictionary *)navigationData;
/* Performs the navigation */
- (BFAppLinkNavigationType)navigate:(NSError **)error;

/*! Returns a BFAppLink for the given URL */
+ (BFTask *)resolveAppLinkInBackground:(NSURL *)destination;

/*! Returns a BFAppLink for the given URL using the given App Link resolution strategy */
+ (BFTask *)resolveAppLinkInBackground:(NSURL *)destination resolver:(id<BFAppLinkResolving>)resolver;

/*! Navigates to a BFAppLink and returns whether it opened in-app or in-browser */
+ (BFAppLinkNavigationType)navigateToAppLink:(BFAppLink *)link error:(NSError **)error;

/*! Navigates to a URL (an asynchronous action) and returns a BFNavigationType */
+ (BFTask *)navigateToURLInBackground:(NSURL *)destination;

/*!
 Navigates to a URL (an asynchronous action) using the given App Link resolution
 strategy and returns a BFNavigationType
 */
+ (BFTask *)navigateToURLInBackground:(NSURL *)destination resolver:(id<BFAppLinkResolving>)resolver;

@end
