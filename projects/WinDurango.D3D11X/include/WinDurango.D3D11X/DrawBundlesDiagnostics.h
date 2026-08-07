#pragma once

#include <Windows.h>
#include <cstdio>

inline bool WinDurangoDrawBundleLogEnabled()
{
    static int enabled = -1;
    if (enabled < 0)
    {
        char buffer[4]{};
        enabled = GetEnvironmentVariableA("WIN_DURANGO_DRAW_BUNDLE_LOG", buffer, sizeof(buffer)) > 0 ? 1 : 0;
    }
    return enabled == 1;
}

inline void WinDurangoLogDrawBundle(char const *message)
{
    if (!WinDurangoDrawBundleLogEnabled())
        return;

    printf("[WinDurango DrawBundles] %s\n", message);
    fflush(stdout);
}
