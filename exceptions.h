#pragma once
#include <exception>
#include <string>

class InventoryException : public std::exception {
    std::string message;
public:
    explicit InventoryException(std::string msg) : message(std::move(msg)) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class ValidationException : public InventoryException {
public:
    explicit ValidationException(const std::string &msg)
        : InventoryException("Validation error: " + msg) {}
};

class ResourceNotFoundException : public InventoryException {
public:
    explicit ResourceNotFoundException(const std::string &msg)
        : InventoryException("Not found: " + msg) {}
};

class InsufficientStockException : public InventoryException {
public:
    explicit InsufficientStockException(const std::string &msg)
        : InventoryException("Insufficient stock: " + msg) {}
};