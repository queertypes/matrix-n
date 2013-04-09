****
Matrix N
****

Matrix N is a generic C++ linear algebra library freely available under the 3-clause BSD license_.

*Note*: Matrix N was created as an experiment during my academic years. If you think this package has something to offer you that quality, production-tested packages like `Eigen`_ or `uBLAS`_ do not provide, feel free to take the torch!

.. _Eigen: http://eigen.tuxfamily.org/index.php?title=Main_Page
.. _uBLAS: http://www.boost.org/doc/libs/1_53_0/libs/numeric/ublas/doc/index.htm
.. _license: http://opensource.org/licenses/BSD-3-Clause

====
Building
====

.. code-block:: bash

    # To configure:
    $> waf configure

    # To build:
    $> waf

    # To remove all build results:
    $> waf clean

    # To remove all build and configuration files:
    $> waf distclean

For a successful build, a compiler supporting recent c++11 features 
should be used. In particular, the following features are important:

- rvalue references
- std::move support
- <chrono>

====
Overview
====

Project structure:

- numerical
    * matrix interface
    * matrix generation
    * detail
        - matrix implementation interfaces
- implementation
    * implementation of generator and matrix interfaces
    * detail
        - implementation of compute classes
- src
    * drivers and applications

Planned implementations:

- serial
- serial-simd
- parallel
- parallel-simd
- gpu
    * CUDA
    * OpenCL
- hybrid

Targets:

- x86 (primary)
- ARM (secondary)

Objects with multiple implementations:

- matrix
- determinant
- inversion

====
Contributing
====

Note this package is no longer maintained. If you have any questions, feel free to direct them to Alejandro Cabrera <cpp.cabrera@gmail.com>.
