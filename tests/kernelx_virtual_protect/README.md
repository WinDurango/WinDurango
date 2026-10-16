# KernelX memory-protection regression tests

These Windows x64 tests reproduce an off-by-one error in `EraVirtualProtectEx`
and exercise its error handling. They need a recent Windows SDK and MSVC with
Desktop C++ support. No game, Xbox SDK, vcpkg packages, or package registration
is required. The placeholder-mapping APIs used by the fixture require Windows
10 version 1803 or newer.

```powershell
cmake -S tests/kernelx_virtual_protect -B build/kernelx-virtual-protect-tests -A x64
cmake --build build/kernelx-virtual-protect-tests --config Release
ctest --test-dir build/kernelx-virtual-protect-tests -C Release --output-on-failure
```

CMake extracts the current production `EraVirtualProtectEx` and
`EraVirtualProtect` functions from `kernelx.cpp`, and their mappable-allocation
registry from `kernelx.h`. It compiles those sections directly into the test
executable. There is no copied protection implementation or mocked Windows API.
Missing extraction markers fail configuration, and editing either production
file triggers reconfiguration.

The fixture reserves real Windows placeholders, splits them into adjacent views,
and replaces selected placeholders with anonymous file mappings. It registers
those views in the production allocation registry. Large-mapping fixtures use
the same 4-MiB address alignment as `EraVirtualAllocEx`; they do not require
privileged Windows large-page allocations. Every case releases its mappings and
handles. No game files or saved data are accessed.

The 16 cases cover exact 4-KiB and 2-MiB boundaries, unaligned and cross-view
requests, zero and overflowing sizes, allocation bounds, first/later Windows
failures, previous protection, optional output, ordinary allocations, and handles
opened with only `PROCESS_VM_OPERATION`.

To demonstrate the regression against an earlier source file, configure another
build directory with `-DKERNELX_SOURCE_FILE:FILEPATH=<absolute path to kernelx.cpp>`.
The source must retain the expected function signatures; the allocation registry
is taken from the current production header. The recorded comparison passed 6/16
checks before the fix and 16/16 afterward.

These are focused production-function tests, not a complete KernelX DLL build or
an in-game compatibility result. The fixture creates the registry entries itself;
it does not test `EraVirtualAllocEx` or the game's loader. See the
[investigation and limitations](../../docs/kernelx-virtual-protect.md).
