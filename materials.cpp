#include "exceptions.h"
#include "materials.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <iomanip>

// Constructorul default
Material::Material() : quantity(0), critical(0), unit_price(0), category(Category::others) {
}

// Constructorul cu parametri
Material::Material(std::string id, std::string name, std::string measure_unit,
                   const double quantity, const double critical, const double unit_price, const Category category)
    : id(std::move(id)), name(std::move(name)), measure_unit(std::move(measure_unit)),
      quantity(quantity), critical(critical), unit_price(unit_price), category(category) {
    Utils::validate_material_id(this->id);
    Utils::validate_material_name(this->name);
    Utils::validate_material_measure_unit(this->measure_unit);
    Utils::validate_material_quantity(this->quantity);
    Utils::validate_material_critical(this->critical);
    Utils::validate_material_unit_price(this->unit_price);
}

// Copy constructorul
Material::Material(const Material &other) = default;

// Destructor
Material::~Material() = default;

// Setters
void Material::set_material_critical(const double set_critical) {
    Utils::validate_material_critical(set_critical);
    critical = set_critical;
}

void Material::set_material_unit_price(const double set_unit_price) {
    Utils::validate_material_unit_price(set_unit_price);
    unit_price = set_unit_price;
}

void Material::set_material_quantity(const double set_quantity) {
    Utils::validate_material_quantity(set_quantity);
    quantity = set_quantity;
}

// Getters
const std::string &Material::get_material_id() const { return id; }
const std::string &Material::get_material_name() const { return name; }
const std::string &Material::get_material_measure_unit() const { return measure_unit; }
double Material::get_material_critical() const { return critical; }
double Material::get_material_unit_price() const { return unit_price; }
double Material::get_material_quantity() const { return quantity; }
Material::Category Material::get_material_category() const { return category; }

// Supraincarcare operator de atribuire (copy and swap)
Material &Material::operator=(Material other) {
    std::swap(id, other.id);
    std::swap(name, other.name);
    std::swap(measure_unit, other.measure_unit);
    std::swap(quantity, other.quantity);
    std::swap(critical, other.critical);
    std::swap(unit_price, other.unit_price);
    std::swap(category, other.category);

    return *this;
}

// Supraincarcarea operatorilor de I/O
std::ostream &operator<<(std::ostream &os, const Material &material) {
    const std::string category = Material::material_category_to_string(material.category);

    os << material.id << "  " << material.name << "\n";
    os << "|  Category   " << category << "\n";
    os << "|  Quantity   " << std::fixed << std::setprecision(2) << material.quantity << " " << material.measure_unit << "\n";
    os << "|  Critical   " << std::fixed << std::setprecision(2) << material.critical << " " << material.measure_unit << "\n";
    os << "|  Price      " << std::fixed << std::setprecision(2) << material.unit_price << " RON\n";
    os << "|_\n\n";

    return os;
}

// Convertor category la string
std::string Material::material_category_to_string(const Category category) {
    switch (category) {
        case Category::wood:
            return "wood";
        case Category::metal:
            return "metal";
        case Category::finishes:
            return "finishes";
        case Category::insulation:
            return "insulation";
        default:
            return "others";
    }
}