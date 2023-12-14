#include "wintoastlib.h"
#include <string>
#include <windows.h>

using namespace WinToastLib;

class CustomHandler : public IWinToastHandler {
public:
    void toastActivated() const {
        std::wcout << L"The user clicked in this toast" << std::endl;
        // Handle 'Yes' button click
        // Add your custom logic here
        exit(0);
    }

    void toastActivated(int actionIndex) const {
        std::wcout << L"The user clicked on action #" << actionIndex << std::endl;
        // Handle 'No' button click
        // Add your custom logic here
        exit(16 + actionIndex);
    }

    void toastDismissed(WinToastDismissalReason state) const {
        switch (state) {
            case UserCanceled:
                std::wcout << L"The user dismissed this toast" << std::endl;
                // Handle dismissal (e.g., equivalent to clicking 'No')
                // Add your custom logic here
                exit(1);
                break;
            case TimedOut:
                std::wcout << L"The toast has timed out" << std::endl;
                exit(2);
                break;
            case ApplicationHidden:
                std::wcout << L"The application hid the toast using ToastNotifier.hide()" << std::endl;
                exit(3);
                break;
            default:
                std::wcout << L"Toast not activated" << std::endl;
                exit(4);
                break;
        }
    }

    void toastFailed() const {
        std::wcout << L"Error showing current toast" << std::endl;
        exit(5);
    }
};


enum Results {
    ToastClicked,             // user clicked on the toast
    ToastDismissed,           // user dismissed the toast
    ToastTimeOut,             // toast timed out
    ToastHided,               // application hid the toast
    ToastNotActivated,        // toast was not activated
    ToastFailed,              // toast failed
    SystemNotSupported,       // system does not support toasts
    UnhandledOption,          // unhandled option
    MultipleTextNotSupported, // multiple texts were provided
    InitializationFailure,    // toast notification manager initialization failure
    ToastNotLaunched          // toast could not be launched
};


void print_help() {

    std::wcout << "try WinToast \"-h\"" << std::endl;
}

int wmain(int argc, LPWSTR* argv) {
    if (!argc == 1) {
        print_help();
        return 0;
    }

    if (!WinToast::isCompatible()) {
        std::wcerr << L"Error, your system in not supported!" << std::endl;
        return Results::SystemNotSupported;
    }

    std::wstring appName        = L"NotifyOnlyApp";
    std::wstring appUserModelID = L"NotifyOnlyApp";
    std::wstring text           = L"Do you allow the file modification !";
    std::wstring imagePath      = L"";
    std::wstring attribute      = L"default";
    std::vector<std::wstring> actions;
    INT64 expiration = 0;

    bool onlyCreateShortcut                   = false;
    WinToastTemplate::AudioOption audioOption = WinToastTemplate::AudioOption::Default;

   

    WinToast::instance()->setAppName(appName);
    WinToast::instance()->setAppUserModelId(appUserModelID);

    if (onlyCreateShortcut) {
        if (!imagePath.empty() || !text.empty() || actions.size() > 0 || expiration) {
            std::wcerr << L"--only-create-shortcut does not accept images/text/actions/expiration" << std::endl;
            return 9;
        }
        enum WinToast::ShortcutResult result = WinToast::instance()->createShortcut();
        return result ? 16 + result : 0;
    }

    if (text.empty()) {
        text = L"empty text !";
    }

    if (!WinToast::instance()->initialize()) {
        std::wcerr << L"Error, your system in not compatible!" << std::endl;
        return Results::InitializationFailure;
    }

    // Update the WinToastTemplate to use two buttons
    WinToastTemplate templ(WinToastTemplate::ImageAndText04);  // Using ImageAndText04 template for two buttons
    templ.setTextField(text, WinToastTemplate::FirstLine);
    templ.setAudioOption(audioOption);
    templ.setAttributionText(attribute);
    templ.setImagePath(imagePath);

    // Adding 'Yes' and 'No' buttons
    templ.addAction(L"Yes");
    templ.addAction(L"No");

    if (WinToast::instance()->showToast(templ, new CustomHandler()) < 0) {
        std::wcerr << L"Could not launch your toast notification!";
        return Results::ToastFailed;
    }

    // Give the handler a chance for 15 seconds (or the expiration plus 1 second)
    Sleep(expiration ? (DWORD)expiration + 1000 : 15000);

    exit(2);
}