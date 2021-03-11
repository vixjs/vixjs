/*
 * gui_app.h
 *
 *  Created on: Mar 1, 2021
 *      Author: lion
 */

#ifndef GUI_APP_H
#define GUI_APP_H

#include "object.h"
#include "options.h"
#include "include/cef_app.h"
#include "res_handler.h"

namespace fibjs {
class GuiApp : public CefApp,
               public CefBrowserProcessHandler,
               public CefPrintHandler {
public:
    GuiApp(int argc, char* argv[])
#ifdef WIN32
        : m_args(NULL)
#else
        : m_args(argc, argv)
#endif
        , m_bHeadless(g_cefheadless)
    {
        if (g_cefprocess) {
            for (int32_t i = 0; i < argc; i++) {
                if (!qstrcmp(argv[i], "--cef_path=", 11))
                    m_cef_path = argv[i] + 11;
            }
        }
    }

public:
    // CefApp
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
        OVERRIDE
    {
        return this;
    }

    virtual CefRefPtr<CefPrintHandler> GetPrintHandler()
        OVERRIDE
    {
        return this;
    }

public:
    // CefBrowserProcessHandler
    virtual void OnContextInitialized() OVERRIDE
    {
        for (auto const& it : m_schemes)
            it.second->RegisterScheme(it.first);

        m_gui_ready.set();
    }

    virtual void OnRegisterCustomSchemes(CefRawPtr<CefSchemeRegistrar> registrar) OVERRIDE
    {
        for (auto const& it : m_schemes)
            if (it.first != "http" && it.first != "https")
                registrar->AddCustomScheme(it.first.c_str(),
                    CEF_SCHEME_OPTION_FETCH_ENABLED | CEF_SCHEME_OPTION_CORS_ENABLED);
    }

    virtual void OnBeforeCommandLineProcessing(const CefString& process_type,
        CefRefPtr<CefCommandLine> command_line) OVERRIDE
    {
        if (m_opt && !g_cefheadless) {
            Variant v;
            if (m_opt->get("headless", v) == 0 && v.boolVal()) {
                command_line->AppendSwitch("headless");
                g_cefheadless = true;
            }
        }

#ifdef Darwin
        command_line->AppendSwitch("use-mock-keychain");
#endif
    }

    virtual void OnBeforeChildProcessLaunch(CefRefPtr<CefCommandLine> command_line)
        OVERRIDE
    {
        command_line->AppendSwitchWithValue("cef_path", m_cef_path.c_str());
    }

public:
    // CefPrintHandler
    virtual void OnPrintStart(CefRefPtr<CefBrowser> browser) OVERRIDE
    {
    }

    virtual void OnPrintSettings(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefPrintSettings> settings, bool get_defaults)
        OVERRIDE
    {
    }

    virtual bool OnPrintDialog(CefRefPtr<CefBrowser> browser,
        bool has_selection, CefRefPtr<CefPrintDialogCallback> callback)
        OVERRIDE
    {
        return false;
    }

    virtual bool OnPrintJob(CefRefPtr<CefBrowser> browser, const CefString& document_name,
        const CefString& pdf_file_path, CefRefPtr<CefPrintJobCallback> callback)
        OVERRIDE
    {
        return false;
    }

    virtual void OnPrintReset(CefRefPtr<CefBrowser> browser) OVERRIDE
    {
    }

    virtual CefSize GetPdfPaperSize(int device_units_per_inch)
        OVERRIDE
    {
        return CefSize((int32_t)(8.27 * device_units_per_inch),
            (int32_t)(11.75 * device_units_per_inch));
    }

public:
    void load_cef();
    void runGuiThread(int argc, char* argv[]);
    void gui_flush();
    result_t open(exlib::string url, v8::Local<v8::Object> opt, obj_ptr<WebView_base>& retVal);
    result_t config(v8::Local<v8::Object> opt);

public:
    obj_ptr<NObject> m_opt;
    exlib::string m_cef_path;

    CefMainArgs m_args;
    CefSettings m_settings;

    bool m_has_cef = false;

    bool m_bDebug = true;
    bool m_bPopup = true;
    bool m_bMenu = true;
    bool m_bHeadless = true;

    exlib::Event m_gui;
    exlib::Event m_gui_ready;
    exlib::Event m_gui_done;

public:
    std::map<exlib::string, CefRefPtr<GuiSchemeHandlerFactory>> m_schemes;
    std::vector<obj_ptr<ValueHolder>> m_hdrs;

private:
    IMPLEMENT_REFCOUNTING(GuiApp);
};
}

#endif