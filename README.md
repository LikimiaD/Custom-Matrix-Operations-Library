# Custom Matrix Operations Library

The Custom Matrix Operations Library (`custom_matrix`) is a static library developed in C11, aimed at providing a comprehensive set of operations for matrix manipulation. This library supports basic arithmetic operations, matrix transformations, and advanced computations such as determinant calculation and finding the inverse of a matrix. Developed with adherence to Google's C++ Style Guide and POSIX.1-2017 standards, this library ensures modern coding practices and compatibility.

## Installation

To use the Custom Matrix Operations Library, follow these steps:

1. Clone the repository to your local machine.
2. Ensure you have GCC compiler and the Check library installed on your system for unit testing.
3. Navigate to the root directory of the project.
    Run the `make` command to compile the library and the unit tests.

The project structure includes:

* `src` directory containing the library source code (`matrix_core.c`, `matrix_arithmetic.c`, `matrix_support.c`) and header file (`custom_matrix.h`).
* `tests` directory with unit tests (`matrix_test.c`).
* `Makefile` for building the library and tests, and generating coverage reports.
* `Dockerfile` for containerization.

## Usage

To utilize the library in your project, include the `custom_matrix.h` header file and link against the `custom_matrix.a` static library.

```c
#include "custom_matrix.h"

int main() {
    matrix_t A, B, result;
    // Initialize matrices A and B...
    custom_sum_matrix(&A, &B, &result);
    // Use result...
    custom_remove_matrix(&A);
    custom_remove_matrix(&B);
    custom_remove_matrix(&result);
    return 0;
}
```

### Functions

The library offers the following matrix operations:

* `custom_create_matrix`: Initialize a matrix with specified dimensions.
* `custom_remove_matrix`: Free the memory allocated for a matrix.
* `custom_eq_matrix`: Check if two matrices are equal.
* Arithmetic operations: Addition (`custom_sum_matrix`), subtraction (`custom_sub_matrix`), multiplication by a matrix (`custom_mult_matrix`), and by a scalar (`custom_mult_number`).
* Transformation operations: Transpose (`custom_transpose`) and inverse (`custom_inverse_matrix`).
* Advanced computations: Determinant (`custom_determinant`), calculation of complements (`custom_calc_complements`).

Refer to the [custom_matrix.h](custom_matrix.h) for detailed function signatures and descriptions.

### Makefile

The Makefile included in the project simplifies the build process and management of the library:

* `make all`: Compiles the library and runs unit tests.
* `make custom_matrix.a`: Compiles the static library.
* `make test`: Compiles and runs the unit tests.
* `make clean`: Cleans up compiled binaries and coverage reports.
* `make gcov_report`: Generates a coverage report in HTML format using gcov.

### Dockerfile

The `Dockerfile` allows for containerization of the library, making it easy to build and test in an isolated environment:
* Build the Docker image:

```bash
docker build -t custom_matrix .
```
* Run the container:

```bash
docker run --rm custom_matrix
```

This setup ensures that the library can be compiled and tested on any system with Docker, without the need to install specific dependencies.

## Contributing

Contributions are welcome to enhance `Custom Matrix Operations Library`. Feel free to fork the project, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for more details.