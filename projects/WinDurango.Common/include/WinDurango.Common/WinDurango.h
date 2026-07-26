//
// Created by DexrnZacAttack on 1/23/26 using zPc-i2.
//
#pragma once
#pragma comment(lib, "runtimeobject.lib")
#include "Config.h"
#include "Interfaces/Storage/Directory.h"
#include "Logging.h"
#include "exports.h"
#include "GUI.h"
#include <ctime>

namespace wd::common
{
    class WD_API WinDurango
    {
      public:
        static std::shared_ptr<WinDurango> GetInstance();

        WinDurango() = default;

        void Init(std::shared_ptr<interfaces::storage::Directory> rootDir);
        bool inited();

        Config config;
        Logging log;
        std::shared_ptr<interfaces::storage::Directory> rootDir;
        GUI gui;

      private:
        bool _inited = false;
        std::shared_ptr<interfaces::storage::Directory> WinDurangoRoot;
    };
} // namespace wd::common

EXTERN_C WD_API void *g_pWindow; //Used for swap chain creation in D3D11.X.
