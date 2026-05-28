#pragma once
#include <string>
#include <vector>
#include <memory>
#include <regex>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "exceptions.h"
#include "materials.h"
#include "providers.h"
#include "transactions.h"

class Utils {
    // Validari atribute materiale
    friend class Inventory;
    friend class Material;
    friend class Provider;
    friend class Transaction;
    friend class PurchaseOrder;
    friend class ConsumptionRecord;
    friend class ReturnTransaction;
    friend class AdjustmentTransaction;
    friend class Menu;

    static void validate_material_id(const std::string &id) {
        if (id.empty()) {
            throw ValidationException("Material ID must not be empty");
        }
        static const std::regex id_regex("^MAT-[0-9]{5}$");
        if (!std::regex_match(id, id_regex)) {
            throw ValidationException("Invalid material ID format (expected format: MAT-#####)");
        }
    }

    static void validate_material_name(const std::string &name) {
        if (name.empty()) {
            throw ValidationException("Material name must not be empty");
        }
        if (std::ranges::all_of(name, [](const unsigned char c) { return std::isspace(c); })) {
            throw ValidationException("Material name must contain at least one non-space character");
        }
        if (!std::ranges::all_of(name, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); })) {
            throw ValidationException("Material name must contain only letters, numbers and spaces");
        }
    }

    static void validate_material_measure_unit(const std::string &measure_unit) {
        if (measure_unit.empty()) {
            throw ValidationException("Material measure unit must not be empty");
        }
        if (std::ranges::all_of(measure_unit, [](const unsigned char c) { return std::isspace(c); })) {
            throw ValidationException("Material measure unit must contain at least one non-space character");
        }
        if (!std::ranges::all_of(measure_unit, [](const unsigned char c) { return std::isalnum(c); })) {
            throw ValidationException("Material measure unit must contain only letters and numbers");
        }
    }

    static void validate_material_quantity(const double quantity) {
        if (quantity < 0) {
            throw ValidationException("Material quantity must not be negative");
        }
    }

    static void validate_material_critical(const double critical) {
        if (critical < 0) {
            throw ValidationException("Material critical level must not be negative");
        }
    }

    static void validate_material_unit_price(const double unit_price) {
        if (unit_price <= 0) {
            throw ValidationException("Material unit price must not be negative or zero");
        }
    }

    // Validari atribute comenzi
    static void validate_transaction_id(const std::string &id) {
        if (id.empty()) {
            throw ValidationException("Transaction ID must not be empty");
        }
        static const std::regex id_regex("^TRN-[0-9]{5}$");
        if (!std::regex_match(id.begin(), id.end(), id_regex)) {
            throw ValidationException("Invalid transaction ID format (expected format: TRN-#####)");
        }
    }

    static void validate_transaction_date(const std::string &date) {
        if (date.empty())
            throw ValidationException("Transaction date must not be empty");

        static const std::regex date_regex("^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-([0-9]{4})$");
        if (!std::regex_match(date.begin(), date.end(), date_regex))
            throw ValidationException("Invalid transaction date format (expected DD-MM-YYYY)");

        const int day = std::stoi(std::string(date.substr(0, 2)));
        const int month = std::stoi(std::string(date.substr(3, 2)));
        const int year = std::stoi(std::string(date.substr(6, 4)));

        if (year < 2026)
            throw ValidationException("Transaction date must not be in the past");

        constexpr int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        const bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        const int max_days = (month == 2 && is_leap) ? 29 : days_in_month[month - 1];

        if (day > max_days)
            throw ValidationException("Invalid day for the given month and year");
    }

    static void validate_materials_uniqueness(const std::string &id, const std::vector<Material> &materials) {
        if (std::ranges::any_of(materials, [&id](const Material &m) { return m.get_material_id() == id; })) {
            throw ValidationException("Transaction material with the same ID already exists");
        }
    }

    static void validate_transaction_materials_number(const int number) {
        if (number < 1) {
            throw ValidationException("Transaction must contain at least one material");
        }

        if (number > 15) {
            throw ValidationException("Transaction cannot contain more than 15 materials");
        }
    }

    static void validate_transaction_materials(const std::vector<Material> &materials) {
        validate_transaction_materials_number(static_cast<int>(materials.size()));
        for (const auto &material: materials) {
            validate_material_id(material.get_material_id());
            validate_material_name(material.get_material_name());
            validate_material_unit_price(material.get_material_unit_price());
            validate_material_measure_unit(material.get_material_measure_unit());
            validate_material_quantity(material.get_material_quantity());
        }

        for (int i = 0; i < static_cast<int>(materials.size()) - 1; i++)
            for (int j = i + 1; j < static_cast<int>(materials.size()); j++)
                if (materials[i].get_material_id() == materials[j].get_material_id())
                    throw ValidationException("Transaction materials must not contain duplicate IDs");
    }

    static void validate_transaction_uniqueness(const std::string &id, const std::vector<std::unique_ptr<Transaction>> &transactions) {
        if (std::ranges::any_of(transactions, [&id](const std::unique_ptr<Transaction> &t) { return t->get_transaction_id() == id; }))
            throw ValidationException("Transaction with this ID already exists");
    }

    static void validate_consumption_record_project_name(const std::string &name) {
        if (name.empty())
            throw ValidationException("Project name must not be empty");
        if (std::ranges::all_of(name, [](const unsigned char c) { return std::isspace(c); }))
            throw ValidationException("Project name must contain at least one non-space character");
        if (!std::ranges::all_of(name, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); }))
            throw ValidationException("Project name must contain only letters, numbers and spaces");
    }

    static void validate_consumption_record_department(const std::string &department) {
        if (department.empty())
            throw ValidationException("Department must not be empty");
        if (std::ranges::all_of(department, [](const unsigned char c) { return std::isspace(c); }))
            throw ValidationException("Department must contain at least one non-space character");
        if (!std::ranges::all_of(department, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); }))
            throw ValidationException("Department must contain only letters, numbers and spaces");
    }

    static void validate_refund_transaction_reason(const std::string &reason) {
        if (reason.empty())
            throw ValidationException("Refund reason must not be empty");
        if (std::ranges::all_of(reason, [](const unsigned char c) { return std::isspace(c); }))
            throw ValidationException("Refund reason must contain at least one non-space character");
        if (!std::ranges::all_of(reason, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); }))
            throw ValidationException("Refund reason must contain only letters, numbers and spaces");
    }

    static void validate_adjustment_transaction_reason(const std::string &reason) {
        if (reason.empty())
            throw ValidationException("Adjustment reason must not be empty");
        if (std::ranges::all_of(reason, [](const unsigned char c) { return std::isspace(c); }))
            throw ValidationException("Adjustment reason must contain at least one non-space character");
        if (!std::ranges::all_of(reason, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); }))
            throw ValidationException("Adjustment reason must contain only letters, numbers and spaces");
    }

    // Validari atribute furnizori
    static void validate_provider_id(const std::string &id) {
        if (id.empty()) {
            throw ValidationException("Provider ID must not be empty");
        }
        static const std::regex id_regex("^PRV-[0-9]{5}$");
        if (!std::regex_match(id.begin(), id.end(), id_regex)) {
            throw ValidationException("Invalid provider ID format (expected format: PRV-#####)");
        }
    }

    static void validate_provider_name(const std::string &name) {
        if (name.empty())
            throw ValidationException("Provider name must not be empty");
        if (std::ranges::all_of(name, [](const unsigned char c) { return std::isspace(c); }))
            throw ValidationException("Provider name must contain at least one non-space character");
        if (!std::ranges::all_of(name, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); }))
            throw ValidationException("Provider name must contain only letters, numbers and spaces");
    }

    static void validate_provider_phone(const std::string &phone) {
        if (phone.empty()) {
            throw ValidationException("Provider phone number must not be empty");
        }
        static const std::regex phone_regex("^[0-9]{10}$");
        if (!std::regex_match(phone.begin(), phone.end(), phone_regex)) {
            throw ValidationException("Invalid provider phone number format (expected format: 10 digits)");
        }
    }

    static void validate_provider_email(const std::string &email) {
        if (email.empty()) {
            throw ValidationException("Provider email must not be empty");
        }
        static const std::regex email_regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
        if (!std::regex_match(email.begin(), email.end(), email_regex)) {
            throw ValidationException("Invalid provider email format");
        }
    }

    static void validate_provider_address(const std::string &address) {
        if (address.empty()) {
            throw ValidationException("Provider address must not be empty");
        }
        if (std::ranges::all_of(address, [](const unsigned char c) { return std::isspace(c); })) {
            throw ValidationException("Provider address must contain at least one non-space character");
        }
        if (!std::ranges::all_of(address, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); })) {
            throw ValidationException("Provider address must contain only letters, numbers and spaces");
        }
    }

    static void validate_provider_materials_number(const int number) {
        if (number < 1)
            throw ValidationException("Provider materials number must be at least 1");
        if (number > 15)
            throw ValidationException("Provider materials number must be at most 15");
    }

    static void validate_provider_materials(const std::vector<Material> &materials) {
        validate_provider_materials_number(static_cast<int>(materials.size()));
        for (const auto &material: materials) {
            validate_material_id(material.get_material_id());
            validate_material_name(material.get_material_name());
            validate_material_measure_unit(material.get_material_measure_unit());
            validate_material_unit_price(material.get_material_unit_price());
        }
        for (int i = 0; i < static_cast<int>(materials.size()) - 1; i++)
            for (int j = i + 1; j < static_cast<int>(materials.size()); j++)
                if (materials[i].get_material_id() == materials[j].get_material_id())
                    throw ValidationException("Provider materials must not contain duplicate IDs");
    }

    // Validari atribute inventar
    static void validate_inventory_id(const std::string &id) {
        if (id.empty()) {
            throw ValidationException("Inventory ID must not be empty");
        }
        static const std::regex id_regex("^INV-[0-9]{5}$");
        if (!std::regex_match(id.begin(), id.end(), id_regex)) {
            throw ValidationException("Invalid inventory ID format (expected format: INV-#####)");
        }
    }

    static void validate_inventory_name(const std::string &name) {
        if (name.empty())
            throw ValidationException("Inventory name must not be empty");
        if (std::ranges::all_of(name, [](const unsigned char c) { return std::isspace(c); }))
            throw ValidationException("Inventory name must contain at least one non-space character");
        if (!std::ranges::all_of(name, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); }))
            throw ValidationException("Inventory name must contain only letters, numbers and spaces");
    }

    static void validate_inventory_phone(const std::string &phone) {
        if (phone.empty()) {
            throw ValidationException("Inventory phone number must not be empty");
        }
        static const std::regex phone_regex("^[0-9]{10}$");
        if (!std::regex_match(phone.begin(), phone.end(), phone_regex)) {
            throw ValidationException("Invalid inventory phone number format (expected format: 10 digits)");
        }
    }

    static void validate_inventory_email(const std::string &email) {
        if (email.empty()) {
            throw ValidationException("Inventory email must not be empty");
        }
        static const std::regex email_regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
        if (!std::regex_match(email.begin(), email.end(), email_regex)) {
            throw ValidationException("Invalid inventory email format");
        }
    }

    static void validate_inventory_address(const std::string &address) {
        if (address.empty()) {
            throw ValidationException("Inventory address must not be empty");
        }
        if (std::ranges::all_of(address, [](const unsigned char c) { return std::isspace(c); })) {
            throw ValidationException("Inventory address must contain at least one non-space character");
        }
        if (!std::ranges::all_of(address, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); })) {
            throw ValidationException("Inventory address must contain only letters, numbers and spaces");
        }
    }

    static void validate_inventory_materials_number(const int number) {
        if (number < 0)
            throw ValidationException("Inventory materials number must be non-negative");
        if (number > 15)
            throw ValidationException("Inventory materials number must be at most 15");
    }

    static void validate_inventory_materials(const std::vector<Material> &materials) {
        validate_inventory_materials_number(static_cast<int>(materials.size()));
        for (const auto &material: materials) {
            validate_material_id(material.get_material_id());
            validate_material_name(material.get_material_name());
            validate_material_measure_unit(material.get_material_measure_unit());
            validate_material_unit_price(material.get_material_unit_price());
            validate_material_critical(material.get_material_critical());
            validate_material_quantity(material.get_material_quantity());
        }
    }

    static void validate_inventory_providers(const std::vector<Provider> &providers) {
        for (const auto &provider: providers) {
            validate_provider_id(provider.get_provider_id());
            validate_provider_name(provider.get_provider_name());
            validate_provider_address(provider.get_provider_address());
            validate_provider_email(provider.get_provider_email());
            validate_provider_phone(provider.get_provider_phone());
            validate_provider_materials_number(provider.get_provider_materials_count());
            validate_provider_materials(provider.get_provider_materials());
        }
    }

    // Functii template pentru citire
    template<typename Func>
    static void read_string(const std::string &prompt, Func function) {
        while (true) {
            try {
                std::cout << prompt << ": ";
                std::string temp;
                std::getline(std::cin, temp);
                function(temp);
                break;
            } catch (const InventoryException &e) {
                std::cout << "Error: " << e.what() << ". Try again.\n";
            } catch (const std::out_of_range &) {
                std::cout << "Error: value out of range. Try again.\n";
            }
        }
    }
};