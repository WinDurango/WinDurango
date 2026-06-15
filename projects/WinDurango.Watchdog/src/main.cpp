#include "Watchdog.h"

int main() {
    WinDurango::Watchdog wdproc;
    std::jthread l_jt = wdproc.ObserveProcess(8724);
    l_jt.join();
}