# DCC-Central
This is the Model Trains Central for control trains with the DCC protocol. This is developed for the Raspberry-Pi.



# Compile

To compile normally without any tests, you have to run this command, from source directory:

```bash
cmake -B build -S .
```

## Run tests

- Run unit tests:

To run tests, you vane to complie the project, you have to be in the sourde folder and run:

```bash
cmake -B build -S . -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
```

The you have to compile the project

```bash
cmake --build build -j 10
```

After that you can run the unit tests, inside the build folder:

```bash
ctests
```

- Run Coverage reports:

To compile with coverage reports, you have to run this command:

```bash
cmake -B build -S . -DCODE_COVERAGE=ON -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Debug
```

The you have to compile the specific unit test to generate the coverage report like:

```bash
cmake --build build -j 10 -t Coverage-TestLibDccProtocol
```

This generate an output with the coverage information.
