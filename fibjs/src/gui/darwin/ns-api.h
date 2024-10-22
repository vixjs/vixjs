/**
 * @author Richard
 * @email ricahrdo2016@mail.com
 * @create date 2020-06-12 04:26:38
 * @modify date 2020-06-12 04:26:38

 * @desc 
 */
#if defined(__APPLE__) && !defined(VIXJS_DISABLE_GUI)

#ifndef WEBVIEW_NS_API_H
#define WEBVIEW_NS_API_H

#import <Webkit/Webkit.h>
#import <Cocoa/Cocoa.h>
#import <objc/runtime.h>
#import <objc/message.h>

#import "darwin.h"

inline exlib::string NSStringToExString(NSString* str)
{
    return exlib::string((const char*)([str UTF8String]));
}

@interface __WKScriptMessageHandler : NSObject <WKScriptMessageHandler>
- (void)userContentController:(WKUserContentController*)userContentController
      didReceiveScriptMessage:(WKScriptMessage*)message;
@end

@interface WVViewController : NSViewController
- (void)loadView;
@end

@interface FileSystemWKURLSchemeHandler : NSObject <WKURLSchemeHandler>
- (void)webView:(WKWebView*)webView
    startURLSchemeTask:(id<WKURLSchemeTask>)urlSchemeTask;
// - (void)webView:(WKWebView *)webView
//       stopURLSchemeTask:(id<WKURLSchemeTask>)urlSchemeTask;
@end

#endif // WEBVIEW_NS_API_H

#endif // __APPLE__
