# DSP-Workstation
 A **Free & Open Source Audio Plugin using Optimized DSP Processing**
 
 * **Formats:** VST3/AU (Windows/Apple/Linux OS compatible) 64bits
 * **Type:** Audio Effects Processor
 * **Modes:** Standalone, Insert, Bypass
 * **Audio:** 4x inputs / 4x outputs channels
 * **Midi:** DAW or/and Hardware input Channels
 
 written by uriel Deveaud

<img src="https://img.shields.io/badge/DSP Workstation-VST/AU-orange.svg" alt="Name" /> <img src="https://img.shields.io/badge/C++-14-green.svg" /> <img src="https://img.shields.io/badge/Audio-Programming-blue.svg" />

---

## Overview 

| **Status:** *In progress* | First Public Release with minimum Presets | 12/2020 | **Title:** *0.5.6* |
| --- | --- | --- | --- |

See the [TODO List](TODO.md) file for details

### Features
This module is intended to recieve mono or stereo channels to process 24bits audio samples.

---

## Components

* MAIN
* PROCESSOR
* GUI

| File | Description | Type | Weight |
| --- | --- | --- | --- |
| DSPW-processor.h | Main Structure | Header | 5.0ko |
| DSPW-processor.cpp | DSP Operators | Audio Processing | 3.4ko |
| DSPW-editor.h | Main GUI | Header | 5.0ko |
| DSPW-editor.cpp | Visual Structure | User Interface | 3.4ko |

---

## Third party software

DSP Workstation is based on some external libraries :
 * JUCE : http://www.juce.com
 * Ableton Link : https://github.com/Ableton/link
 * VST3 SDK : www.steinberg.net
 * ASIO (Windows) : www.steinberg.net
 * CORE AUDIO (Apple) : https://developer.apple.com/documentation/audiounit
 * JACK (Linux) : www.linuxmao.org/Jack

See the [JUCE C++ Modules List](https://github.com/juce-framework/JUCE/tree/master/modules) for references.
---

## Author

* **Uriel Deveaud** - *Initial work* - [Kore Teknology](https://github.com/KoreTeknology)

<img src="https://img.shields.io/badge/Kore-Teknology-9cf.svg" /> <img src="https://img.shields.io/badge/Qaudraphonics-Audio-red.svg" />

Please, feel free to contact me, and/or discuss further developments or ideas for those plugins, thanks ;)
Collaboration projects are always welcome ;)

---

## License

This project is licensed under the GPL-3.0 License - see the [LICENSE](LICENSE) file for details


## Acknowledgments

* Documentation: syntax highlighting and line referencing..

```c++
if (isAwesome){
  return true
}
```
> This page is in progress, please, come back soon !
