# Floating Point Number Representation C Application

The following application would accept a floating point number be able to print on the screen the bits of the fields composing a 32-bit floating point number following the IEEE 754 standard.

Example:
Enter the floating point number: 15.23
Sign Exponent Mantissa
   0 10000010 11100111010111000010100

Two binaries are generated fpn_main and fpn_test. 

Test is for testing the functions and ensure the program is working as expected while the main is the main application.

Getting Started:

1) Clone the Repo.

2) Build and Run the application:

    a) To run the program run the following commands from root:
    ``` 
        make main
        build/fpn_main
    ```

    b) To run the test binary run the following commands from root:
    ```
        make test
        build/fpn_test
    ```

    c) To build both fpn_main and fpn_test run the following command from root:
    ```
        make all
    ```
