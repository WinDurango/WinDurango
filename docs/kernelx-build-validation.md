# KernelX contribution: complete-build validation

Date: 2026-10-16.

The branch `codex/kernelx-virtual-protect` starts directly at upstream
`ae747f406395581f1faafc5da8f03d0b701d2705`. The KernelX fix was cherry-picked into
its own commit, `ed08d95`. The earlier ConnectedStorage work remains on
`codex/connected-storage-save-queries` and is not part of this contribution.

## Result

The complete x64 Release build succeeded with the setup described below. All 12
project DLLs and `WinDurango.Watchdog.exe` were produced, along with four runtime
dependency DLLs. Artifacts are in `build/bin/`. The build completed all 332 Ninja
operations with exit code zero; that operation count includes scans and links,
not just compilation units.

`dumpbin /exports` confirmed that `VirtualProtect` and `VirtualProtectEx` are
implemented at local RVAs in the built `kernelx.dll`, rather than forwarded to
Windows. This inspected the DLL without loading it or running its initialization.
The successful build compiled the modified production `kernelx.cpp`.

This result uses an older pinned ImGui source and existing ATL headers. An
unadjusted build with the current moving ImGui branch failed, as recorded below.

## Focused verification

The standalone production-function target was configured and built afresh on
the isolated branch with Visual Studio 2026 Community 18.9.2, MSVC 19.51.36256.0,
Windows SDK 10.0.26100.0, Ninja, and Release configuration. All 16 cases passed
with `/W4 /WX /permissive-`; CTest passed 1/1. The earlier MSVC 19.44 run passed
the same cases, while the saved pre-fix source passed 6 and failed 10.

The unmodified upstream base also has a
[successful full CI build](https://github.com/WinDurango/WinDurango/actions/runs/37055545752).
That result is for the base commit, not this patch. Upstream CI uses the
`windows-2025-vs2026` runner and requests Windows SDK 28000. Patch CI and game
compatibility have not been tested.

## Local build setup

The complete-build attempt uses the existing Visual Studio 2026 developer shell
and Windows SDK 10.0.26100.0. The project's existing metadata-generation logic
has a fallback for this SDK's UniversalApiContract 19.0.0.0. CMake is version
4.0.0 with Ninja and Release configuration.

A local vcpkg checkout under `build/dependencies/vcpkg` was bootstrapped without
global integration. Its revision is `3cd21e48a75f67acfef289da52893ce79144aaa1`,
with vcpkg-tool release 2026-09-26. The project's pinned package baseline remains
`a903750172f93c76c9beb5efc61e6296df02849a`; no port versions were changed.

The selected packages include C++/WinRT 2.0.250303.1, Detours 4.0.1, DirectXTex
2025-10-27, FFmpeg 8.0.1 with avcodec, Kinect SDK 2.0, and zlib 1.3.1. vcpkg's
normal tool bootstrap also acquired its build tools locally. It builds both
Release and Debug dependency libraries even though WinDurango is configured for
Release.

The successful build used ImGui docking revision
`64944b4520b30772de8dbf0b37d0311746477a32` (1.93.0 WIP), selected from the docking
branch's first-parent history before the upstream CI build. This is a local
`FETCHCONTENT_SOURCE_DIR_IMGUI` override, not a change to the repository's GUI
backend or CMake files. The exact ImGui revision used by that old CI run is not
claimed to have been identified. spdlog's inspected `v1.x` revision was
`154b518531955375cfd64169c3e2993b2c65b5d8` (1.17.0); nlohmann/json is 3.12.0.

The 2026 installation lacked ATL. The existing VS 2022 Professional ATL headers
and x64 libraries from toolset 14.44.35207 were added to the build process's
`INCLUDE` and `LIB` environment variables. The compiler and linker remained VS
2026 / 19.51. No global environment, Visual Studio components, or SDK installation
was changed.

## Failures and remedies

1. The first configure failed while vcpkg's child Git process tried to lazily
   fetch historical port files from a partial clone: it could not resolve
   `github.com`. Direct Git access from the developer environment worked.
2. Prefetching the first missing blobs directly worked, but the next missing
   blobs encountered the same child-process failure.
3. Fetching the pinned baseline directly with
   `git fetch --refetch --no-filter --depth 1 origin <baseline>` hydrated the
   required port files. Configuration then advanced to compiling and installing
   dependencies. This did not change the project's baseline or source.

4. After all 15 pinned packages installed successfully, the first source build
   failed in `WinDurango.Common/thirdparty/imgui_impl_uwp.cpp`: the latest ImGui
   docking revision `d88f238d1d363ef387382b2e29ad12cf96f826ac` (1.93.1 WIP) removed
   the legacy `ImGuiIO::GetClipboardTextFn` and `SetClipboardTextFn` members.
   Neither the backend nor the dependency declaration is modified by this patch.
5. The first historical ImGui selection, `ed73ef4e84c9488256c5710de6ff1ebc2c9a8496`,
   came from merged mainline history and lacked `ImGuiConfigFlags_DockingEnable`.
   That failed attempt was corrected by selecting the docking branch's
   first-parent history, resulting in the successful revision listed above.
6. Compilation then failed on missing `atlbase.h`. Adding the existing ATL
   include/library directories to the local process resolved it.
7. The initial nested build directory reached a Kinect linker failure,
   `LNK1104: cannot open file 'kinect20.lib'`. Its dependency installation directory
   did not match the paths hard-coded in the Kinect CMake configuration. Using
   the standard top-level `build` directory placed vcpkg libraries at the expected
   `build/vcpkg_installed/x64-windows/lib` path. All 15 packages restored from the
   local binary cache; they did not need rebuilding. This was an incompatible
   local directory choice, not a KernelX regression.
8. The standard-layout configure and complete Release build succeeded with the
   pinned ImGui checkout and existing ATL environment. No additional production
   source changes were required.

The early CMake messages about unset compilers and Ninja followed the failed
toolchain install; they do not establish a separate compiler/build-tool problem.
A warning about long object paths appeared only in the nested configuration and
did not recur in the standard build layout.

## Reproduction

In an x64 Visual Studio developer shell with ATL available, set `VCPKG_ROOT` to
the local bootstrapped vcpkg checkout, and prepare a clean ImGui docking checkout
at the revision above. From the WinDurango repository root:

```powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release `
  "-DCMAKE_TOOLCHAIN_FILE=$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" `
  "-DFETCHCONTENT_SOURCE_DIR_IMGUI=<absolute path to the pinned ImGui checkout>"
cmake --build build --config Release --parallel 8
```

The KernelX tests have their own [standalone commands](../tests/kernelx_virtual_protect/README.md).

## Warnings and remaining validation

The successful complete build emitted 252 compiler warning occurrences, including
macro mismatches/redefinitions, ignored typedefs, narrowing, exceptions in
`noexcept` stubs, and paths without a return value. Repeated header diagnostics
count more than once; this is not a count of distinct bugs. These warnings were
not disabled or repaired for this contribution. The focused protection tests
still build with warnings treated as errors.

Remote CI for the patch and game compatibility remain untested. The current
moving ImGui dependency will need a separate upstream compatibility change or
pin for an unadjusted full build. The KernelX patch deliberately contains no GUI
or general build-system repair. No game launch, profile sign-in, save modification,
or game DLL deployment occurred during this validation.

Full timestamped command logs and the local helper script are retained under
`build/full-validation/`, which Git ignores. This public record summarizes them
without publishing local profile paths or machine-specific scripts. The local
`results.json` records the artifact sizes and SHA-256 hashes, compiler/SDK and
dependency revisions, warning counts, and export-verification results.
