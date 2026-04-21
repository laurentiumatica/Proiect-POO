#pragma once
#include "materials.h"
#include <iosfwd>
#include <span>
#include <string>
#include <vector>

class Order {
public:
    enum class Status { pending, delivered, cancelled, unknown };

    struct OrderMaterial {
        std::string material_id;
        std::string material_name;
        std::string material_measure_unit;
        Material::Category material_category;
        double material_quantity;
        double material_unit_price;
    };

    // Constructorul implicit
    Order();

    // Constructorul de copiere
    Order(const Order &other);

    // Constructorul cu parametri
    Order(std::string_view new_order_id, std::string_view new_order_provider_id,
          std::string_view new_order_date, Status new_order_status,
          std::span<const OrderMaterial> new_order_materials);

    // Destructorul
    ~Order();

    // Getters
    [[nodiscard]] const std::string& get_order_id() const;
    [[nodiscard]] const std::string& get_order_provider_id() const;
    [[nodiscard]] const std::string& get_order_date() const;
    [[nodiscard]] Status get_order_status() const;
    [[nodiscard]] const std::vector<OrderMaterial>& get_order_materials() const;
    [[nodiscard]] int get_order_materials_count() const;
    [[nodiscard]] double get_order_total_price() const;

    // Supraincarcarea operatorilor de I/O
    friend std::ostream &operator<<(std::ostream &os, const Order &order);

    // Supraincarcarea operatorului de atribuire
    Order &operator=(Order other);

    // Supraincarcarea operatorilor relationali
    bool operator==(const Order &other) const;
    bool operator!=(const Order &other) const;

    // Convertor status la string
    static std::string_view order_status_to_string(Status status);

    // Interschimbare
    static void swap(Order &order1, Order &order2) noexcept;

    // Setters
    void set_order_id(std::string_view new_order_id);
    void set_order_provider_id(std::string_view new_order_provider_id);
    void set_order_date(std::string_view new_order_date);
    void set_order_status(Status new_order_status);
    void set_order_materials(std::span<const OrderMaterial> new_order_materials);

    // Functii helper
    static void validate_order_id(std::string_view new_order_id);
    static void validate_order_date(std::string_view new_order_date);
    static void validate_order_materials(std::span<const OrderMaterial> new_order_materials);
    static void validate_order_materials_number(int new_order_materials_number);
    static void order_material_already_exists(std::string_view material_id, std::span<const OrderMaterial> materials);

private:
    std::string id;
    std::string provider_id;
    std::string date;
    Status status;
    std::vector<OrderMaterial> materials;
};