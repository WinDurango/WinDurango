//
// Created by DexrnZacAttack on 1/23/26 using zPc-i2.
//
#include "WinDurango.Common/WinDurango.h"

#undef CreateFile

void *g_pWindow = nullptr;

namespace wd::common
{
    std::shared_ptr<WinDurango> WinDurango::GetInstance()
    {
        static std::shared_ptr<WinDurango> Instance =
            std::make_shared<WinDurango>(); // if we don't declare it in src, it will make multiple instances per
                                            // header import in different libs afaik

        return Instance;
    }

    bool WinDurango::inited()
    {
        return _inited;
    }

    void WinDurango::Init(std::shared_ptr<interfaces::storage::Directory> root)
    {
        if (this->_inited)
        {
            return;
        }
        try
        {
            rootDir = root;
            rootDir->open();

            std::time_t timestamp = std::time(nullptr);
            std::tm datetm = *std::localtime(&timestamp);

            char buf[512];
            std::strftime(buf, sizeof(buf), "%d.%m.%Y", &datetm);

            std::string date(buf);
            WinDurangoRoot = rootDir->CreateFolder("WinDurango");
            WinDurangoRoot->open();

            std::shared_ptr<interfaces::storage::File> LogFile =
                WinDurangoRoot->CreateFile("windurango_log_" + date + ".log");

            config = Config(WinDurangoRoot);
            log = Logging(LogFile);

            config.parse();
            log.Initialize();

            this->_inited = true;
        }
        catch (const std::exception &e)
        {
            std::cout << "[WinDurango::Common::WinDurango.exception] - Critical: " << e.what() << "\n";
        }
        catch (...)
        {
            std::cout << "[WinDurango::Common::WinDurango.(...))] - Critical: Unknown Error\n";
        }
    }
} // namespace wd::common
