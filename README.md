libnumerica
===========

*v0.1.0-alpha*



Build status (on Travis CI) [![Build Status](https://travis-ci.org/krvajalmiguelangel/libnumerica.svg?branch=master)](https://travis-ci.org/krvajalmiguelangel/libnumerica)

## What is this

Libnumerica is a numeric library written in C++. It includes implementations for the most common methods used in numerical computing. 
We put our effort on code clarity  and expressive in the implementation of the algorithms.

## Aim of this project

The aim of this project is not to compete with existing libraries that are specialized and very optimized. Instead we try to provide a coherent
interface and implementation that is easy to read and understand for a person that is learning numerical methods for the first time.
All the code is implemented using C++11 and should work with any compatible compiler.

The complete range of subject areas covered by the library includes,
* [Quadrature](https://github.com/krvajalmiguelangel/libnumerica/blob/master/docs/quadrature.md)
* Root Finding
* [Linear Algebra](https://github.com/krvajalmiguelangel/libnumerica/blob/master/docs/linearalgebra.md)
* [Interpolation](https://github.com/krvajalmiguelangel/libnumerica/blob/master/docs/interpolation.md)
* [ODEs](https://github.com/krvajalmiguelangel/libnumerica/blob/master/docs/odes.md)
* Least Square Fitting
* FFT

## How to use it
In order to use it you must link your project with the libnumerica static library and make  the headers accesibles in your include path so they can be visibles by your source code.
A sample project using CMake is included that shows a typical configuration to use the library.
## Authors
* Daniel Miravet [dmiravet@gmail.com](mailto:dmiravet@gmail.com)
* Yuriel Nuñez [yurielnf@gmail.com](mailto:yurielnf@gmail.com)

## More
Join our online chat at [![Gitter](https://badges.gitter.im/gitterHQ/gitter.svg)](https://gitter.im/libnumerica/Lobby)

Issues and bugs can be raised on the [Issue tracker on GitHub](https://github.com/krvajalmiguelangel/libnumerica/issues)
