# aptic-stack-parse
Imports image stacks and prepares them for APTIC processing

Based on the [APTIC algorithm](http://ieeexplore.ieee.org/document/6556662/)

## Getting started

### Prerequisites
 * Visual Studio 2017 (15.5.6) 
    * .NET 4.7.03056
    * Visual C++ 2017 v141 toolset
    * Windows 10 SDK (10.0.16299.0)
    * Visual C++ tools for CMake
 * Boost 1.68.0 libraries
 * Python3
    * random
    * PIL
    * numpy
    * argparse
    * unittest

### Testing
#### Test datasets
 Test datasets can be created using the utility in tools/image_generator:
 ```
 python image_generator.py <height>, <width>, <frames>, <flashes>, <flash_radius>
 ```

 For example,
 ```
 python image_generator.py 20, 30, 40, 2, 3
 ```
 Would create a stack of images 20 pixels high, 30 pixels wide, 40 frames long, with two flashes of radius 3 pixels.

 This image generator is currently very basic and will become more sophisticated over time.

 #### Unit testing
 Each module is built with unit tests.

## Authors

* [**Joseph Radford**](https://https://github.com/josephradford)
