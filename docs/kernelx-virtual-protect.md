# KernelX protection-range investigation

## Comparison

On 2026-10-16, [SlimEra](https://github.com/XWine1/SlimEra) was cloned as a separate
reference checkout under `reserch/SlimEra`. The inspected SlimEra revision was
`397807a9563f62b56cf7aaea9809b6fa635ba651`. WinDurango's pre-fix local revision was
`c1a5d1eff6e7e6c53f6702f33480c688a846fec7`.

The comparison found 33 function definitions in SlimEra's `kernelx.cpp` and 56 in
WinDurango's. All 33 SlimEra definitions have counterparts in WinDurango; 29 bodies
match after ignoring comments and formatting. The four differing bodies are
`EraVirtualAllocEx`, `GetSystemOSVersion`, `TitleMemoryStatus`, and
`XMemAllocDefault`. This counts function definitions, not all forwarded DLL
exports, and is not a measure of API completeness or correctness.

WinDurango's header already identifies SlimEra as a source for much of this code.
In particular, the pre-fix `EraVirtualProtectEx` bodies have the same tokens. This
makes SlimEra useful for identifying shared behavior, but it is not an independent
oracle for whether that behavior is correct. The reference clone is unchanged;
the fix described here is an original change to WinDurango.

## Reproduced failure

For tracked mappable allocations, `EraVirtualProtectEx` previously calculated:

```cpp
LastPage = (Address + Size) & ~(PageSize - 1);
```

The loop then included `LastPage`. If the requested bytes end exactly at a page
boundary, this changes the following page as well. A real Windows-mapping test
confirmed that a request to make one 4-KiB page read-only also made its writable
neighbor read-only. The same issue affected the existing 2-MiB protection units
used for 4-MiB mappings, and could cross into an adjacent mapped view.

The loop also combined Windows results with bitwise OR. A successful call could
therefore conceal an earlier or later failed call, and the loop kept changing
pages after failure. Zero sizes, overflowing byte ranges, and requests extending
past the tracked allocation were not rejected before modification.

[Windows documents protection in terms of the pages containing the requested
bytes, a failure return of zero, and the first page's previous protection.](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualprotectex)
The tests use real Windows API results to check these properties; no retail Xbox
runtime was used as a reference.

## Fix

- Reject zero and overflowing sizes before doing address arithmetic.
- Reject a range that extends beyond its tracked mappable allocation.
- Calculate the final page from the last requested byte, `Address + Size - 1`.
- Stop on the first Windows protection failure and preserve its last-error code.
- Publish the first page's previous protection after all requested units succeed.
- Keep the existing optional output, 4-KiB/2-MiB stepping, and ordinary-allocation
  forwarding behavior.

No extra process-query permission is required. A regression case opens a process
handle with only `PROCESS_VM_OPERATION` and successfully changes protection.

## Validation and limits

The [standalone test target](../tests/kernelx_virtual_protect/README.md) compiles
the exact production protection functions and allocation registry. Its fixture
uses real `VirtualAlloc2`, `MapViewOfFile3`, `VirtualProtectEx`, and `VirtualQuery`
calls with adjacent mapped views and deliberately uncommitted placeholders.

| Source | Passed | Failed |
| --- | ---: | ---: |
| Pre-fix WinDurango | 6 | 10 |
| Patched WinDurango | 16 | 0 |

Local validation used MSVC 19.44, Windows SDK 10.0.26100.0, and an x64 Release
build with `/W4 /WX /permissive-`. GitHub Actions runs the standalone target too;
the remote workflow has not yet been run for this patch.

The tests populate the production registry directly rather than exercising all
allocation/remapping code. A complete WinDurango DLL build, retail Xbox behavior,
and game compatibility remain unverified. This change does not establish that
another title is playable.

The existing TODO about validating every page before changing protection remains:
if a later unit fails, earlier successfully changed units are not rolled back.
Concurrent changes to mappings and tracking allocations belonging to another
process also remain outside this patch. The fix bounds the requested range and
reports failures correctly; it does not promise atomic protection changes across
multiple views. Similar range calculations in `EraVirtualFreeEx` and
`EraVirtualQueryEx` deserve separate reproductions before changes are proposed.
