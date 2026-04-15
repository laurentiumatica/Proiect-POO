#include "materials.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

// Constructorul default
Material::Material(): quantity(0), critical(0), unit_price(0), category(Category::others) { }

// Constructorul cu parametri
Material::Material(std::string new_material_id, std::string new_material_name, std::string new_material_measure_unit, const double new_material_quantity, const double new_material_critical, const double new_material_unit_price, const Category new_material_category)
    : id(std::move(new_material_id)), name(std::move(new_material_name)), measure_unit(std::move(new_material_measure_unit)), quantity(new_material_quantity), critical(new_material_critical), unit_price(new_material_unit_price), category(new_material_category) {
    if (this->id.empty()) throw std::invalid_argument("ID must be non-empty");
    if (this->name.empty()) throw std::invalid_argument("Name must be non-empty");
    if (this->measure_unit.empty()) throw std::invalid_argument("Measure unit must be non-empty");
    if (this->quantity < 0) throw std::invalid_argument("Quantity must be greater than 0");
    if (this->critical < 0) throw std::invalid_argument("Critical level must be greater than 0");
    if (this->unit_price < 0) throw std::invalid_argument("Unit price must be greater than 0");
}

// Copy constructorul
Material::Material(const Material &other) : Material(other.id, other.name, other.measure_unit, other.quantity, other.critical, other.unit_price, other.category) { }

// Destructor
Material::~Material() = default;

// Getters
const std::string &Material::get_material_id() const { return id; }
const std::string &Material::get_material_name() const { return name; }
const std::string &Material::get_material_measure_unit() const { return measure_unit; }
double Material::get_material_critical() const { return critical; }
double Material::get_material_unit_price() const { return unit_price; }
double Material::get_material_quantity() const { return quantity; }
Material::Category Material::get_material_category() const { return category; }

// Setters
void Material::set_material_id(std::string new_material_id) {
    if (new_material_id.empty())
        throw std::invalid_argument("ID must be non-empty");
    id=std::move(new_material_id);
}
void Material::set_material_name(std::string new_material_name) {
    if (new_material_name.empty())
        throw std::invalid_argument("Name must be non-empty");
    name = std::move(new_material_name);
}
void Material::set_material_measure_unit(std::string new_material_measure_unit) {
    if (new_material_measure_unit.empty())
        throw std::invalid_argument("Measure unit must be non-empty");
    measure_unit = std::move(new_material_measure_unit);
}
void Material::set_material_critical(const double new_material_critical) {
    if (new_material_critical < 0)
        throw std::invalid_argument("Critical level must be greater than 0");
    critical = new_material_critical;
}

void Material::set_material_unit_price(const double new_material_unit_price) {
    if (new_material_unit_price < 0)
        throw std::invalid_argument("Unit price must be greater than 0");
    unit_price = new_material_unit_price;
}

void Material::set_material_quantity(const double new_material_quantity) {
    if (new_material_quantity < 0)
        throw std::invalid_argument("Quantity must be greater than 0");
    quantity = new_material_quantity;
}

void Material::set_material_category(const Category new_material_category) {
    category = new_material_category;
}

// Supraincarcare operator de atribuire
// In loc sa transmitem cealalta instanta prin referinta, folosim o copie a ei pentru a evita posibilele erori la atribuiri individuale (copy and swap)
Material &Material::operator=(Material other) {
    if (this == &other)
        return *this;

    std::swap(id, other.id);
    std::swap(name, other.name);
    std::swap(measure_unit, other.measure_unit);
    std::swap(quantity, other.quantity);
    std::swap(critical, other.critical);
    std::swap(unit_price, other.unit_price);
    std::swap(category, other.category);

    return *this;
}

// Supraincarcarea operatorilor relationali
bool Material::operator==(const Material &other) const {
    constexpr double epsilon = 1e-9;

    return id == other.id &&
           name == other.name &&
           measure_unit == other.measure_unit &&
           std::abs(quantity - other.quantity) < epsilon &&
           std::abs(critical - other.critical) < epsilon &&
           std::abs(unit_price - other.unit_price) < epsilon &&
           category == other.category;
}

bool Material::operator!=(const Material &other) const {
    return !(*this == other);
}

// Interschimbare
void Material::swap(Material &material1, Material &material2) noexcept {
    std::swap(material1.id, material2.id);
    std::swap(material1.name, material2.name);
    std::swap(material1.measure_unit, material2.measure_unit);
    std::swap(material1.quantity, material2.quantity);
    std::swap(material1.critical, material2.critical);
    std::swap(material1.unit_price, material2.unit_price);
    std::swap(material1.category, material2.category);
}

// Supraincarcarea operatorilor de I/O
std::ostream &operator<<(std::ostream &os, const Material &material) {
    const std::string_view category = Material::material_category_to_string(material.category);

    os << material.id << "  " << material.name << "\n";
    os << "│  Category   " << category << "\n";
    os << "│  Quantity   " << std::fixed << std::setprecision(2) << material.quantity << " " << material.measure_unit << "\n";
    os << "│  Critical   " << std::fixed << std::setprecision(2) << material.critical << " " << material.measure_unit << "\n";
    os << "│  Price      " << std::fixed << std::setprecision(2) << material.unit_price << " RON\n\n";

    return os;
}

std::istream &operator>>(std::istream &is, Material &material) {
    std::string buffer;
    double temp;
    int cat;

    is.ignore();

    std::cout << "Enter material ID: ";
    std::getline(is,buffer);
    material.set_material_id(buffer);

    std::cout << "Enter material name: ";
    std::getline(is,buffer);
    material.set_material_name(buffer);

    std::cout << "Enter measure unit: ";
    std::getline(is,buffer);
    material.set_material_measure_unit(buffer);

    std::cout << "Enter quantity: ";
    is >> temp;
    is.ignore();
    material.set_material_quantity(temp);

    std::cout << "Enter critical level: ";
    is >> temp;
    is.ignore();
    material.set_material_critical(temp);

    std::cout << "Enter unit price: ";
    is >> temp;
    is.ignore();
    material.set_material_unit_price(temp);

    std::cout << "Enter category (0: wood, 1: metal, 2: finishes, 3: insulation, 4: others): ";
    is >> cat;
    cat = (cat >= 0 && cat <= 4) ? cat : 4;
    material.set_material_category(static_cast<Material::Category>(cat));

    return is;
}

// Convertor category la string
std::string_view Material::material_category_to_string(const Category category) {
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