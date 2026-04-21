#include "orders.h"
#include <cstring>
#include <iosfwd>
#include "providers.h"
#include <string>
#include <span>
#include <regex>
#include <algorithm>
#include <iomanip>

// Constructorul default
Order::Order() : status(Status::unknown) { }

// Constructorul cu parametri
Order::Order(const std::string_view new_order_id, const std::string_view new_order_provider_id,
          const std::string_view new_order_date, const Status new_order_status,
          const std::span<const OrderMaterial> new_order_materials)
    : id(new_order_id), provider_id(new_order_provider_id), date(new_order_date), status(new_order_status), materials(new_order_materials.begin(), new_order_materials.end()) {
    validate_order_id(id);
    Provider::validate_provider_id(provider_id);
    validate_order_date(date);
    validate_order_materials(materials);
}

// Copy constructor
Order::Order(const Order &other) : Order(other.id, other.provider_id, other.date, other.status, other.materials) { }

// Destructorul
Order::~Order() = default;

// Getters
const std::string &Order::get_order_id() const { return id; }
const std::string &Order::get_order_provider_id() const { return provider_id; }
const std::string &Order::get_order_date() const { return date; }
Order::Status Order::get_order_status() const { return status; }
const std::vector<Order::OrderMaterial>& Order::get_order_materials() const { return materials; }
int Order::get_order_materials_count() const { return static_cast<int>(materials.size()); }

// Setters
void Order::set_order_id(const std::string_view new_order_id) {
    validate_order_id(new_order_id);
    id = new_order_id;
}

void Order::set_order_provider_id(const std::string_view new_order_provider_id) {
    Provider::validate_provider_id(new_order_provider_id);
    provider_id = new_order_provider_id;
}

void Order::set_order_date(const std::string_view new_order_date) {
    validate_order_date(new_order_date);
    date = new_order_date;
}

void Order::set_order_materials(const std::span<const OrderMaterial> new_order_materials) {
    validate_order_materials(new_order_materials);
    materials = std::vector(new_order_materials.begin(), new_order_materials.end());
}

void Order::set_order_status(const Status new_order_status) {
    status = new_order_status;
}

// Supraincarcarea operatorului de atribuire
Order &Order::operator=(Order other) {
    std::swap(id, other.id);
    std::swap(provider_id, other.provider_id);
    std::swap(date, other.date);
    std::swap(status, other.status);
    std::swap(materials, other.materials);

    return *this;
}

// Supraincarcare operatori relationali
bool Order::operator==(const Order &other) const {
    constexpr double epsilon = 1e-9;

    return id == other.id &&
           provider_id == other.provider_id &&
           date == other.date &&
           status == other.status &&
           std::ranges::equal(materials, other.materials, [](const OrderMaterial &m1, const OrderMaterial &m2) {
               return m1.material_id == m2.material_id &&
                      m1.material_name == m2.material_name &&
                      m1.material_category == m2.material_category &&
                      m1.material_measure_unit == m2.material_measure_unit &&
                      std::abs(m1.material_quantity - m2.material_quantity) < epsilon &&
                      std::abs(m1.material_unit_price - m2.material_unit_price) < epsilon;
           });
}

bool Order::operator!=(const Order &other) const { return !(*this == other); }

// Interschimbare
void Order::swap(Order &order1, Order &order2) noexcept {
    std::swap(order1.id, order2.id);
    std::swap(order1.provider_id, order2.provider_id);
    std::swap(order1.date, order2.date);
    std::swap(order1.status, order2.status);
    std::swap(order1.materials, order2.materials);
}

// Supraincarcarea operatorului de output
std::ostream &operator<<(std::ostream &os, const Order &order) {
    os << order.id << "  " << order.date << "\n";
    os << "|  Provider ID : " << order.provider_id << "\n";
    os << "|  Status      : " << Order::order_status_to_string(order.status) << "\n";
    os << "|  Total price : " << std::fixed << std::setprecision(2) << order.get_order_total_price() << " RON\n";
    os << "|  Materials   : \n";
    for (const auto &[material_id, material_name, material_measure_unit, material_category, material_quantity, material_unit_price] : order.materials)
        os << "|    - " << material_id << " " << material_name << " (Category: " << Material::material_category_to_string(material_category) << ", Quantity: " << material_quantity << " " << material_measure_unit << ")\n";
    os << "|_\n\n";
    return os;
}

// Convertor status la string
std::string_view Order::order_status_to_string(const Status status) {
    switch (status) {
        case Status::pending:
            return "pending";
        case Status::delivered:
            return "delivered";
        case Status::cancelled:
            return "cancelled";
        default:
            return "unknown";
    }
}

// Functie helper
void Order::validate_order_id(const std::string_view new_order_id) {
    if (new_order_id.empty()) {
        throw std::invalid_argument("Order ID must not be empty");
    }
    static const std::regex id_regex("^ORD-[0-9]{5}$");
    if (!std::regex_match(new_order_id.begin(), new_order_id.end(), id_regex)) {
        throw std::invalid_argument("Invalid order ID format");
    }
}

void Order::validate_order_date(const std::string_view new_order_date) {
    if (new_order_date.empty())
        throw std::invalid_argument("Order date must not be empty");

    static const std::regex date_regex("^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-([0-9]{4})$");
    if (!std::regex_match(new_order_date.begin(), new_order_date.end(), date_regex))
        throw std::invalid_argument("Invalid order date format (expected DD-MM-YYYY)");

    const int day   = std::stoi(std::string(new_order_date.substr(0, 2)));
    const int month = std::stoi(std::string(new_order_date.substr(3, 2)));
    const int year  = std::stoi(std::string(new_order_date.substr(6, 4)));

    if (year < 2026)
        throw std::invalid_argument("Order date must not be in the past");

    constexpr int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    const int max_days = (month == 2 && is_leap) ? 29 : days_in_month[month - 1];

    if (day > max_days)
        throw std::invalid_argument("Invalid day for the given month and year");
}

void Order::order_material_already_exists(const std::string_view material_id, const std::span<const OrderMaterial> materials) {
    if (std::ranges::any_of(materials, [material_id](const OrderMaterial &m) { return m.material_id == material_id; })) {
        throw std::invalid_argument("Order material with the same ID already exists");
    }
}

void Order::validate_order_materials_number(const int new_order_materials_number) {
    if (new_order_materials_number <= 0) {
        throw std::invalid_argument("Order must contain at least one material");
    }

    if (new_order_materials_number > 15) {
        throw std::invalid_argument("Order cannot contain more than 15 materials");
    }
}

void Order::validate_order_materials(const std::span<const OrderMaterial> new_order_materials) {
    validate_order_materials_number(static_cast<int>(new_order_materials.size()));
    for (const auto &[material_id, material_name, material_measure_unit, material_category, material_quantity, material_unit_price] : new_order_materials) {
        Material::validate_material_id(material_id);
        Material::validate_material_name(material_name);
        Material::validate_material_unit_price(material_unit_price);
        Material::validate_material_measure_unit(material_measure_unit);
        Material::validate_material_quantity(material_quantity);
    }

    for (int i = 0; i < static_cast<int>(new_order_materials.size()) - 1; i++)
        for (int j = i + 1; j < static_cast<int>(new_order_materials.size()); j++)
            if (new_order_materials[i].material_id == new_order_materials[j].material_id)
                throw std::invalid_argument("Order materials must not contain duplicate ID's");
}

double Order::get_order_total_price() const {
    double total_price = 0.0;
    for (const auto &[material_id, material_name, material_measure_unit, material_category, material_quantity, material_unit_price] : materials)
        total_price += material_quantity * material_unit_price;
    return total_price;
}
