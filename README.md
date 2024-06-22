# C++ Book Search Application with Test Data Generator and Linting

This project is a C++ application designed to search for new books using given data. It includes a script to create test data, a C++ source file for the main application, and a Makefile to compile the project. Additionally, it uses `cpplint.py` for linting the C++ code to ensure it follows Google's C++ style guide.

## Project Files

1. **create_testData**
   - Script to generate test data for the book search application.

2. **Makefile**
   - Makefile for compiling the C++ source code.

3. **book_search.cpp**
   - Main C++ source file implementing the book search functionality.

4. **cpplint.py**
   - Python script for linting C++ code according to Google's style guide.

## How to Use

### Prerequisites

- C++ compiler (e.g., g++)
- Python 3.x
- Required Python libraries: none

### Steps

1. **Clone the Repository**

   ```sh
   git clone https://github.com/yourusername/Book-Search-Application.git
   cd Book-Search-Application
   ```

2. **Generate Test Data**

   ```sh
   ./create_testData
   ```

3. **Compile the Code**

   ```sh
   make
   ```

4. **Run the Application**

   ```sh
   ./SearchNewBooks
   ```

5. **Lint the C++ Code**

   ```sh
   python cpplint.py book_search.cpp
   ```

## Directory Structure

```
src/
├── create_testData
├── Makefile
├── book_search.cpp
└── cpplint.py
```

## Example

### Running the Application

After generating the test data and compiling the code, you can run the application as follows:

```sh
./SearchNewBooks
```

### Linting the Code

To lint the C++ source code:

```sh
python cpplint.py book_search.cpp
```

This will check for style issues and ensure that the code follows Google's C++ style guide.