<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
<div align="center">

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![Latest Release][release-shield]][release-url]

</div>



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/alwyn974/Saturnity">
    <img src="assets/logo.ico" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Saturnity</h3>

  <p align="center">
    Saturnity is a C++ library to handle network communication between a client and a server. <br />
    <br />
    <a href="https://alwyn974.github.io/Saturntiy"><strong>Explore the source code docs »</strong></a>
    <br />
    <a href="https://alwyn974-rtype.gitbook.io/saturnity"><strong>Explore the project docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/alwyn974/Saturnity/issues">Report Bug</a>
    ·
    <a href="https://github.com/alwyn974/Saturnity/issues">Request Feature</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#documentation">Documentation</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#authors">Authors</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]](https://github.com/alwyn974/Saturnity)

Saturnity is a C++ library to handle network communication between a client and a server. <br />
Saturnity provide some abstraction to the user to handle the network communication. <br />
You have a TCP and UDP server and client implementation. <br />
You can easily create a server and a client and communicate with them using packets. <br />

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

* [![CPP][CPP]][CPP-url]
* [![CMake][CMake]][CMake-url]
* [![CLion][CLion]][CLion-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

- CMake
- C++20

### Installation

You can install Saturnity using the release package. <br />
You can also install Saturnity with CMake:

- You will need to create a `FindSaturnity.cmake` file in your project, create it in a `cmake` directory, and add the following lines:

```cmake
cmake_minimum_required(VERSION 3.17)

Include(FetchContent)
if (NOT ${LIBRARY_NAME}_FIND_QUIETLY)
    set(FETCHCONTENT_QUIET OFF)
endif ()

if (NOT Saturnity_FOUND)
    FetchContent_Declare(
            Saturnity
            GIT_REPOSITORY https://github.com/alwyn974/Saturnity.git
            GIT_TAG v1.0.1.7
            GIT_SHALLOW 1 # Only fetch the head commit
    )
    FetchContent_MakeAvailable(Saturnity)
    FetchContent_GetProperties(Saturnity)
    message(STATUS "Saturnity is available now")
endif ()
```
- You will need to add the following lines in your CMakeLists.txt file:

```cmake
# Make project-provided Find modules available
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Saturnity REQUIRED)
target_link_libraries(${PROJECT_NAME} Saturnity::Saturnity)
```

Or you can use it as submodule:
- Clone the repo
   ```sh
   git submodule add https://github.com/alwyn974/Saturnity library/Saturnity
   ```
- Add the following lines in your CMakeLists.txt file:
  ```cmake
    add_subdirectory(library/Saturnity)
  ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- Documentation -->
## Documentation

The documentation of this project can be found at:
- Source code documentation: [https://alwyn974.github.io/Saturntiy][github.io-url]
- Project documentation: [https://alwyn974-rtype.gitbook.io/saturnity][gitbook-url]

<!-- USAGE -->
## Usage

See the examples in the [source code documentation][github.io-url] or the [project documentation][gitbook-url].

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

Read the [contributing guide][contributing-url] to learn how to contribute to the project.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- LICENSE -->
## License

Distributed under the MIT License. See [LICENSE.txt][license-url] for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Authors

<table>
    <tbody>
        <tr>
            <td align="center"><a href="https://github.com/alwyn974/"><img src="https://avatars.githubusercontent.com/u/47529956?v=4?s=100" width="100px;" alt="alwyn974"/><br /><sub><b>alwyn974</b></sub></a><br /></td>
            <td align="center"><a href="https://github.com/ChatDo/"><img src="https://avatars.githubusercontent.com/u/72121087?v=4?s=100" width="100px;" alt="ChatDo"/><br /><sub><b>ChatDo</b></sub></a><br /></td>
        </tr>
    </tbody>
</table>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/alwyn974/Saturnity.svg?style=for-the-badge
[contributors-url]: https://github.com/alwyn974/Saturnity/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/alwyn974/Saturnity.svg?style=for-the-badge
[forks-url]: https://github.com/alwyn974/Saturnity/network/members
[stars-shield]: https://img.shields.io/github/stars/alwyn974/Saturnity.svg?style=for-the-badge
[stars-url]: https://github.com/alwyn974/Saturnity/stargazers
[issues-shield]: https://img.shields.io/github/issues/alwyn974/Saturnity.svg?style=for-the-badge
[issues-url]: https://github.com/alwyn974/Saturnity/issues
[license-shield]: https://img.shields.io/github/license/alwyn974/Saturnity.svg?style=for-the-badge
[license-url]: https://github.com/alwyn974/Saturnity/blob/master/LICENSE.txt
[product-screenshot]: assets/nsis-header.png
[contributing-url]: CONTRIBUTING.md
[gitbook-url]: https://alwyn974-rtype.gitbook.io/saturnity/
[github.io-url]: https://alwyn974.github.io/Saturnity/
[release-shield]: https://img.shields.io/github/v/release/alwyn974/Saturnity?color=lime&label=LATEST%20RELEASE&style=for-the-badge
[release-url]: https://github.com/alwyn974/Saturnity/releases/latest

[CPP]: https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white
[CPP-url]: https://en.cppreference.com/w/cpp/20
[CMake]: https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white
[CMake-url]: https://cmake.org
[CLion]: https://img.shields.io/badge/CLion-black?style=for-the-badge&logo=clion&logoColor=white
[CLion-url]: https://www.jetbrains.com/clion/
