<p align="center">
  <a href="https://github.com/WinDurango-project/WinDurango/">
    <img alt="WinDurango logo" src="https://raw.githubusercontent.com/WinDurango-project/WinDurango/main/assets/logo/1024.png" height="120px">
  </a>
</p>

<h1 align="center">WinDurango</h1>

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![project_license][license-shield]][license-url]

WinDurango is an experimental compatibility layer and emulator for **Xbox One** games on Windows. It aims to recreate the console environment so titles can run natively on PC hardware. Development is still in its early stages.

[![Product Name Screen Shot][product-screenshot]](https://github.com/WinDurango/WinDurango)

> [!NOTE]
> This project is still being worked on, and we **really** need help as we only have a few developers.   
> If you know C++ and think you can help out, hop into the Discord and let us know. :)

Come chat with us on our [Discord](https://discord.gg/mHN2BgH7MR).
For developer chat join `#developer` but stay on topic. Lurking is not only fine, but encouraged!

Discussing illegal activities, such as piracy, (illegal) hacking, doxxing/cyberbullying, and all other forms of copyright infringement will get you banned.

## Status
[![GitHub Latest Release](https://img.shields.io/badge/Latest-Release-green?color=2c9510&)](https://github.com/WinDurango/WinDurango/releases)
[![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/WinDurango/WinDurango/build-WD.yml?label=Nightly&color=2c9510&)](https://github.com/WinDurango/WinDurango/actions)

### Playable Games

 - Sonic Mania - Playable
 - Minecraft: Xbox One Edition (version 1.2.0.0) - Playable
 - Minecraft: Xbox One Edition (versions 1.61.X.X) - Boots
 - LIMBO - Playable
 - Forza Horizon 2 and it's variants - Boots
 - Forza Motorsport 5 - Boots
 - Peggle 2 - Boots

 <!-- ROADMAP -->
### Roadmap

- [ ] Get Minecraft: Xbox One Edition (versions 1.61.X.X) to a playable state
- [ ] Get Forza Horizon 2 and it's variants to a playable state
- [ ] Get Forza Motorsport 5 to a playable state
- [ ] Get Peggle 2 to a playable state

## Installation
1. To install WinDurango, you need to build it beforehand, or download it from Github Actions. See [docs/BUILDING.md](docs/BUILDING.md) for setup instructions.
2. Get WinDurango DLL's from `build/bin/Release` or from the downloaded archive.
3. Copy the DLL's into the Mount directory of your desired game.
4. Enable Developer Mode.
5. Install the game (open powershell in Mount folder, that contains `AppxManifest.xml`)
   ```sh
   Add-AppXPackage -Register .\AppxManifest.xml
   ```
6. Move `EmbeddedXvd` to your game directory.
7. Pick these DLLs from EmbeddedXvd and drop them in the same folder as the executable:
   `xg_x.dll`, `xg.dll` (if present), `AcpHal.dll`, `xaudio2_9.dll`,
   `D3DCompiler46.dll` (if present), `sc_dll.dll` (if present).
   if the game complains about a missing DLL that isn't present in this list nor implemented, please reach us out.

## Minimum Requirements

WinDurango does not have a fixed and correct minimum requirements list, as some games are more demanding than others (e.g. Minecraft uses way less system resources than Forza). However, we can speculate system requirements that **should** supply the needs of most games:

- A CPU with at least 4 cores (e.g. Intel Core i5 4690K)
- A GPU with at least 2GB of Video Memory (e.g. NVIDIA GeForce GTX 960)
- 8GB of RAM (DDR3 or newer)
- Windows 10 or newer

## Disclaimer

The goal of this project is to experiment, research, and educate on the topic
of emulation of modern devices and operating systems. **It is not for enabling
illegal activity**. All information is obtained via reverse engineering of
legally purchased devices and games and information made public on the internet
(you'd be surprised what's indexed on Google...). We are not any way affiliated
with Microsoft.

## Contributors Wanted!

Have some spare time and know C++? Help build the world's first Xbox One compatibility layer!
Check the [open issues](https://github.com/WinDurango/WinDurango/issues) and the
[good first issue](https://github.com/WinDurango/WinDurango/labels/good%20first%20issue) label,
then come chat with us on [Discord](https://discord.gg/mHN2BgH7MR) before starting work.

## License

WinDurango is licensed under the [GNU General Public License, version 3](LICENSE.txt).

## Credits
Thanks to 
- @othneildrew for `Best Readme Template`


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/WinDurango/WinDurango.svg
[contributors-url]: https://github.com/WinDurango/WinDurango/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/WinDurango/WinDurango.svg
[forks-url]: https://github.com/WinDurango/WinDurango/network/members
[stars-shield]: https://img.shields.io/github/stars/WinDurango/WinDurango.svg
[stars-url]: https://github.com/WinDurango/WinDurango/stargazers
[issues-shield]: https://img.shields.io/github/issues/WinDurango/WinDurango.svg
[issues-url]: https://github.com/WinDurango/WinDurango/issues
[license-shield]: https://img.shields.io/github/license/WinDurango/WinDurango.svg
[license-url]: https://github.com/WinDurango/WinDurango/blob/main/LICENSE.md
[product-screenshot]: https://github.com/WinDurango/WinDurango/blob/main/assets/demo.png
