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
    validate_material_id(this->id);
    validate_material_name(this->name);
    validate_material_measure_unit(this->measure_unit);
    validate_material_quantity(this->quantity);
    validate_material_critical(this->critical);
    validate_material_unit_price(this->unit_price);
}

// Copy constructorul
Material::Material(const Material &other)
    : Material(other.id, other.name, other.measure_unit,
               other.quantity, other.critical, other.unit_price, other.category) {
}

// Destructor
Material::~Material() = default;

// Setters
void Material::set_material_critical(const double set_critical) {
    validate_material_critical(set_critical);
    critical = set_critical;
}

void Material::set_material_unit_price(const double set_unit_price) {
    validate_material_unit_price(set_unit_price);
    unit_price = set_unit_price;
}

void Material::set_material_quantity(const double set_quantity) {
    validate_material_quantity(set_quantity);
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
    os << "│  Category   " << category << "\n";
    os << "│  Quantity   " << std::fixed << std::setprecision(2) << material.quantity << " " << material.measure_unit << "\n";
    os << "│  Critical   " << std::fixed << std::setprecision(2) << material.critical << " " << material.measure_unit << "\n";
    os << "│  Price      " << std::fixed << std::setprecision(2) << material.unit_price << " RON\n";
    os << "|_\n\n";

    return os;
}

std::istream &operator>>(std::istream &is, Material &material) {
    is.ignore();

    std::string id, measure_unit, name, critical, unit_price, quantity;
    Material::Category category;

    read_string("Enter material ID", [&id](const std::string &s) { validate_material_id(s); id = s; });
    read_string("Enter measure unit", [&measure_unit](const std::string &s) { validate_material_measure_unit(s); measure_unit=s; });
    read_string("Enter material name", [&name](const std::string &s) { validate_material_name(s); name = s; });
    read_string("Enter material critical level", [&critical](const std::string &s) {
        validate_material_critical(std::stod(s));
        critical = s;
    });
    read_string("Enter material unit price", [&unit_price](const std::string &s) {
        validate_material_unit_price(std::stod(s));
        unit_price = s;
    });
    read_string("Enter material quantity", [&quantity](const std::string &s) {
        validate_material_quantity(std::stod(s));
        quantity = s;
    });
    read_string("Enter material category (0 - wood, 1 - metal, 2 - insulation, 3 - finishes, 4 - others)", [&category](const std::string &s) {
        const int cat = std::stoi(s);
        if (cat < 0 || cat > 4)
            throw ValidationException("Category must be between 0 and 4");
        category=static_cast<Material::Category>(cat);
    });

    material = Material(id, name, measure_unit, std::stod(quantity), std::stod(critical), std::stod(unit_price), category);

    return is;
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