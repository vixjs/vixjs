/*
 * WebView.h
 *
 *  Created on: Sep 23, 2016
 *      Author: lion
 */
#ifdef _WIN32

#include "ifs/WebView.h"
#include <comdef.h>
#include <Exdisp.h>
#include <mshtmhst.h>

#ifndef WEBVIEW_WIN32_H_
#define WEBVIEW_WIN32_H_

namespace fibjs {

class WebView : public WebView_base,
                public IDispatch,
                public IOleClientSite,
                public IOleInPlaceSite,
                public IDocHostUIHandler,
                public IOleCommandTarget,
                public IServiceProvider,
                public IInternetSecurityManager {
    FIBER_FREE();

public:
    WebView(exlib::string url, NObject* opt);
    ~WebView();

    HRESULT open();

    void GetDPI(int* dpix, int* dpiy);
    RECT PixelToHiMetric(const RECT& _rc);

    virtual void SetRect(const RECT& _rc);

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
        WPARAM wParam, LPARAM lParam);

    HRESULT TranslateAccelerator(MSG* msg);

    EVENT_SUPPORT();

public:
    // WebView_base
    virtual result_t loadUrl(exlib::string url, AsyncEvent* ac);
    virtual result_t getUrl(exlib::string& retVal, AsyncEvent* ac);
    virtual result_t setHtml(exlib::string html, AsyncEvent* ac);
    virtual result_t reload(AsyncEvent* ac);
    virtual result_t goBack(AsyncEvent* ac);
    virtual result_t goForward(AsyncEvent* ac);
    virtual result_t print(int32_t mode, AsyncEvent* ac);
    virtual result_t printToPDF(exlib::string file, AsyncEvent* ac);
    virtual result_t executeJavaScript(exlib::string code, AsyncEvent* ac);
    virtual result_t executeDevToolsMethod(exlib::string method, v8::Local<v8::Object> params, Variant& retVal, AsyncEvent* ac);
    virtual result_t close(AsyncEvent* ac);
    virtual result_t postMessage(exlib::string msg, AsyncEvent* ac);
    virtual result_t get_dev(v8::Local<v8::Value>& retVal);

private:
    static void exec_js(IWebBrowser2* frame, const wchar_t* code);

public:
    EVENT_FUNC(open);
    EVENT_FUNC(load);
    EVENT_FUNC(move);
    EVENT_FUNC(resize);
    EVENT_FUNC(closed);
    EVENT_FUNC(message);

private:
    void Navigate(exlib::string szUrl);

public:
    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, void** ppvObject);
    STDMETHODIMP_(ULONG)
    AddRef(void);
    STDMETHODIMP_(ULONG)
    Release(void);

public:
    // IDispatch
    STDMETHODIMP GetIDsOfNames(REFIID riid, OLECHAR** rgszNames, unsigned int cNames, LCID lcid, DISPID* rgdispid);
    STDMETHODIMP GetTypeInfo(unsigned int itinfo, LCID lcid, ITypeInfo** pptinfo);
    STDMETHODIMP GetTypeInfoCount(unsigned int* pctinfo);
    STDMETHODIMP Invoke(DISPID dispid, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult, EXCEPINFO* pexecinfo, unsigned int* puArgErr);

public:
    // IOleWindow
    STDMETHODIMP GetWindow(HWND* phwnd);
    STDMETHODIMP ContextSensitiveHelp(BOOL fEnterMode);

public:
    // IOleInPlaceSite
    STDMETHODIMP CanInPlaceActivate(void);
    STDMETHODIMP OnInPlaceActivate(void);
    STDMETHODIMP OnUIActivate(void);
    STDMETHODIMP GetWindowContext(IOleInPlaceFrame** ppFrame,
        IOleInPlaceUIWindow** ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect,
        LPOLEINPLACEFRAMEINFO lpFrameInfo);
    STDMETHODIMP Scroll(SIZE scrollExtant);
    STDMETHODIMP OnUIDeactivate(BOOL fUndoable);
    virtual HWND GetControlWindow();
    STDMETHODIMP OnInPlaceDeactivate(void);
    STDMETHODIMP DiscardUndoState(void);
    STDMETHODIMP DeactivateAndUndo(void);
    STDMETHODIMP OnPosRectChange(LPCRECT lprcPosRect);

public:
    // IOleClientSite
    STDMETHODIMP SaveObject(void);
    STDMETHODIMP GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker,
        IMoniker** ppmk);
    STDMETHODIMP GetContainer(IOleContainer** ppContainer);
    STDMETHODIMP ShowObject(void);
    STDMETHODIMP OnShowWindow(BOOL fShow);
    STDMETHODIMP RequestNewObjectLayout(void);

public:
    // IDocHostUIHandler
    STDMETHODIMP ShowContextMenu(DWORD dwID, POINT* ppt, IUnknown* pcmdtReserved,
        IDispatch* pdispReserved);
    STDMETHODIMP GetHostInfo(DOCHOSTUIINFO* pInfo);
    STDMETHODIMP ShowUI(DWORD dwID, IOleInPlaceActiveObject* pActiveObject,
        IOleCommandTarget* pCommandTarget, IOleInPlaceFrame* pFrame,
        IOleInPlaceUIWindow* pDoc);
    STDMETHODIMP HideUI(void);
    STDMETHODIMP UpdateUI(void);
    STDMETHODIMP EnableModeless(BOOL fEnable);
    STDMETHODIMP OnDocWindowActivate(BOOL fActivate);
    STDMETHODIMP OnFrameWindowActivate(BOOL fActivate);
    STDMETHODIMP ResizeBorder(LPCRECT prcBorder, IOleInPlaceUIWindow* pUIWindow,
        BOOL fRameWindow);
    STDMETHODIMP TranslateAccelerator(LPMSG lpMsg, const GUID* pguidCmdGroup,
        DWORD nCmdID);
    STDMETHODIMP GetOptionKeyPath(LPOLESTR* pchKey, DWORD dw);
    STDMETHODIMP GetDropTarget(IDropTarget* pDropTarget, IDropTarget** ppDropTarget);
    STDMETHODIMP GetExternal(IDispatch** ppDispatch);
    STDMETHODIMP TranslateUrl(DWORD dwTranslate, OLECHAR* pchURLIn, OLECHAR** ppchURLOut);
    STDMETHODIMP FilterDataObject(IDataObject* pDO, IDataObject** ppDORet);

public:
    // IOleCommandTarget
    STDMETHODIMP Exec(const GUID* pguidCmdGroup, DWORD nCmdID, DWORD nCmdexecopt,
        VARIANT* pvaIn, VARIANT* pvaOut);
    STDMETHODIMP QueryStatus(const GUID* pguidCmdGroup, ULONG cCmds, OLECMD prgCmds[],
        OLECMDTEXT* pCmdText);

public:
    // IServiceProvider
    STDMETHODIMP QueryService(REFGUID siid, REFIID riid,
        void** ppvObject);

public:
    // IInternetSecurityManager
    STDMETHODIMP SetSecuritySite(IInternetSecurityMgrSite* pSite);
    STDMETHODIMP GetSecuritySite(IInternetSecurityMgrSite** ppSite);
    STDMETHODIMP MapUrlToZone(LPCWSTR pwszUrl, DWORD* pdwZone,
        DWORD dwFlags);
    STDMETHODIMP GetSecurityId(LPCWSTR pwszUrl, BYTE* pbSecurityId,
        DWORD* pcbSecurityId, DWORD_PTR dwReserved);
    STDMETHODIMP ProcessUrlAction(LPCWSTR pwszUrl, DWORD dwAction,
        BYTE* pPolicy, DWORD cbPolicy, BYTE* pContext, DWORD cbContext,
        DWORD dwFlags, DWORD dwReserved);
    STDMETHODIMP QueryCustomPolicy(LPCWSTR pwszUrl, REFGUID guidKey,
        BYTE** ppPolicy, DWORD* pcbPolicy, BYTE* pContext, DWORD cbContext,
        DWORD dwReserved);
    STDMETHODIMP SetZoneMapping(DWORD dwZone, LPCWSTR lpszPattern,
        DWORD dwFlags);
    STDMETHODIMP GetZoneMappings(DWORD dwZone, IEnumString** ppenumString,
        DWORD dwFlags);

private:
    void clear();
    HRESULT OnBeforeNavigate2(DISPPARAMS* pDispParams);
    HRESULT OnCommandStateChange(DISPPARAMS* pDispParams);
    HRESULT OnDocumentComplete(DISPPARAMS* pDispParams);
    HRESULT OnDownloadBegin(DISPPARAMS* pDispParams);
    HRESULT OnDownloadComplete(DISPPARAMS* pDispParams);
    HRESULT OnNavigateComplete2(DISPPARAMS* pDispParams);
    HRESULT OnNewWindow2(DISPPARAMS* pDispParams);
    HRESULT OnProgressChange(DISPPARAMS* pDispParams);
    HRESULT OnPropertyChange(DISPPARAMS* pDispParams);
    HRESULT OnStatusTextChange(DISPPARAMS* pDispParams);
    HRESULT OnTitleChange(DISPPARAMS* pDispParams);
    HRESULT OnWindowClosing(DISPPARAMS* pDispParams);

    HRESULT OnPostMessage(DISPPARAMS* pDispParams);
    HRESULT OnLog(DISPPARAMS* pDispParams);
    HRESULT OnOnMessage(DISPPARAMS* pDispParams);
    HRESULT OnOnClose(DISPPARAMS* pDispParams);
    HRESULT OnClose(DISPPARAMS* pDispParams);

    result_t postMessage(exlib::string msg, _variant_t& retVal);
    result_t WebView::postClose(_variant_t& retVal);

protected:
    exlib::string m_url;
    obj_ptr<NObject> m_opt;

    IStorage* storage;
    IOleObject* oleObject;
    IOleInPlaceObject* oleInPlaceObject;
    IOleInPlaceActiveObject* oleInPlaceActiveObject;
    IOleCommandTarget* oleCommandTarget;
    IConnectionPoint* connectionPoint;
    IWebBrowser2* webBrowser2;
    IDispatch* _onmessage;
    IDispatch* _onclose;

    RECT rObject;
    DWORD eventCookie;

    HWND hWndParent;
    HWND hWndControl;

    bool m_bSilent;

    AsyncEvent* m_ac;
};

} /* namespace fibjs */
#endif /* WEBVIEW_WIN32_H_ */
#endif /* _WIN32 */