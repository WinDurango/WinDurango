<a id="readme-top"></a>

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![project_license][license-shield]][license-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/WinDurango/WinDurango">
    <img src="https://github.com/WinDurango/WinDurango/blob/main/assets/logo/128.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">WinDurango</h3>
  <p align="center">
    WinDurango is an Xbox One Translation Layer which allows you to play various ERA based Games on Windows via UWP.
    <br />
    <a href="https://github.com/WinDurango/WinDurango/issues">Report Bug</a>
    &middot;
    <a href="https://github.com/WinDurango/WinDurango/issues">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#playable-games">Playable Games</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#building">Building</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#disclaimer">Disclaimer</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://github.com/WinDurango/WinDurango)

WinDurango is an Xbox One Translation Layer which allows you to play various ERA based Games on Windows via UWP. Currently, WinDurango has implemented most of the essential Xbox WinRT interfaces, KernelX and D3D11.X. Kinect support is completely experimental and hasn't been tested, expect issues.



### Playable Games

 - Sonic Mania - Playable
 - Minecraft: Xbox One Edition (version 1.2.0.0) - Playable
 - Minecraft: Xbox One Edition (versions 1.61.X.X) - Boots
 - LIMBO - Playable
 - Forza Horizon 2 and it's variants - Boots
 - Forza Motorsport 5 - Boots
 - Peggle 2 - Boots



<!-- GETTING STARTED -->
## Getting Started

Before Building WinDurango make sure you install the prerequisites.

### Prerequisites

Make sure you have Visual Studio 2026 with the C++ Extension, vcpkg and cmake.

### Building

1. Open up the `VS 2026 Powershell Prompt`
2. Clone the repo
   ```sh
   git clone https://github.com/WinDurango/WinDurango
   ```
3. Install VCPKG packages
   ```sh
   vcpkg install
   ```
4. Prep CMake
   ```sh
    mkdir build && cd build
    cmake ..
   ```
5. Build WinDurango
   ```sh
   cmake --build .
   ```

### Installation

1. Get WinDurango Dll's from `build/bin/Debug`
2. Copy the Dll's into the Mount Dir in your Game
3. Enable Developer Mode
3. Install the Game (open powershell in the folder that contains `AppxManifest.xml`)
   ```sh
   Add-AppXPackage -Register .\AppxManifest.xml
   ```
4. Add `EmbeddedXvd` to the folder that has the game executable
   (usually in `Mount`)
5. Pick these DLLs from EmbeddedXvd and drop them in the same folder as the executable:
   `xg_x.dll`, `xg.dll` (if present), `AcpHal.dll`, `xaudio2_9.dll`,
   `D3DCompiler46.dll` (if present), `sc_dll.dll` (if present).
   if the game complains about a missing DLL that isn't present in this list nor implemented, please reach us out.


### Minimum Requirements

WinDurango does not have a fixed and correct minimum requirements list, as some games are more demands than others (e.g. Minecraft uses way less system resources than Forza). However, we can speculate system requirements that **should** supply the needs of most games:

- A CPU with at least 4 Cores (e.g. Intel Core I5 4690K)
- A GPU with at least 2gb of Video Memory (e.g. NVIDIA GeForce GTX 960)
- 12gb of RAM (DDR3 or newer)
- Windows 10 or newer

<!-- ROADMAP -->
## Roadmap

- [ ] Get Minecraft: Xbox One Edition (versions 1.61.X.X) to a playable state
- [ ] Get Forza Horizon 2 and it's variants to a playable state
- [ ] Get Forza Motorsport 5 to a playable state
- [ ] Get Peggle 2 to a playable state


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request


<!-- LICENSE -->
## License

Distributed under the project_license. See `LICENSE.txt` for more information.



<!-- CONTACT -->
## Contact

Join our [Discord](https://discord.gg/mHN2BgH7MR)



<!-- DISCLAIMER -->
## Disclaimer

The goal of this project is to experiment, research, and educate on the topic of emulation of modern devices and operating systems. It is not for enabling illegal activity. All information is obtained via reverse engineering of legally purchased devices and games and information made public on the internet (you'd be surprised what's indexed on Google...). We are not any way affiliated with Microsoft.

## Credits
Thanks to 
- @othneildrew for `Best Readme Template`


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/WinDurango/WinDurango.svg?style=for-the-badge
[contributors-url]: https://github.com/WinDurango/WinDurango/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/WinDurango/WinDurango.svg?style=for-the-badge
[forks-url]: https://github.com/WinDurango/WinDurango/network/members
[stars-shield]: https://img.shields.io/github/stars/WinDurango/WinDurango.svg?style=for-the-badge
[stars-url]: https://github.com/WinDurango/WinDurango/stargazers
[issues-shield]: https://img.shields.io/github/issues/WinDurango/WinDurango.svg?style=for-the-badge
[issues-url]: https://github.com/WinDurango/WinDurango/issues
[license-shield]: https://img.shields.io/github/license/WinDurango/WinDurango.svg?style=for-the-badge
[license-url]: https://github.com/WinDurango/WinDurango/blob/master/LICENSE.txt
[product-screenshot]: https://github.com/WinDurango/WinDurango/blob/main/assets/demo.png
