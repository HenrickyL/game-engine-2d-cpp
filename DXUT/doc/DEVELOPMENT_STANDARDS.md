# Development Standards

This document outlines the coding standards and best practices for this project. Following these guidelines ensures code consistency and readability across the project.

## Table of Contents

- [Development Standards](#development-standards)
  - [Table of Contents](#table-of-contents)
  - [Naming Conventions](#naming-conventions)
    - [Classes and Structs](#classes-and-structs)
    - [Methods and Functions](#methods-and-functions)
    - [Getters and Setters](#getters-and-setters)
    - [Variables and Attributes](#variables-and-attributes)
    - [Constants](#constants)
  - [Formatting](#formatting)
    - [Indentation](#indentation)

## Naming Conventions

### Classes and Structs

- Class and struct names should use PascalCase.
    ```cpp
    class MyClass;
    struct MyStruct;
    ```

### Methods and Functions

- Function names should use camelCase.
    ```cpp
    void myFunction();
    ```
- Method names should use PascalCase (except getters).
    ```cpp
    void MyMethod();
    ```

### Getters and Setters

- Getter methods should use lowercase.
    ```cpp
    float width() const;
    ```

- Setter methods should use Set with PascalCase.
    ```cpp
    void SetWidth(float width);
    ```

### Variables and Attributes

- Variable names should use camelCase.
    ```cpp
    int myVariable;
    ```

- Attributes names should use "_"+camelCase.
    ```cpp
    int _myAttribute;
    ```

### Constants

- Constants should use uppercase letters with underscores.
    ```cpp
    const int MAX_SIZE = 100;
    ```

## Formatting

### Indentation

- Use 4 spaces for indentation or use tabs.