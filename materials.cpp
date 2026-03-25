#include "materials.h"
#include <cstring>
#include <iostream>

// Constructorul default
Material::Material() {
    this->id = nullptr;
    this->name = nullptr;
    this->measure_unit = nullptr;
    this->quantity = 0;
    this->critical = 0;
    this->unit_price = 0;
    this->category = Category::others;
}

// Pentru urmatorii constructori folosim setters pentru atribuirea valorilor deoarece implementeaza deja verificarea datelor
// De asemenea initializam pointerii la nullptr pentru a preveni stergerea memoriei de la adrese invalide

// Constructorul cu parametri
Material::Material(const char *id, const char *name, const char *measure_unit,
                   const double &quantity, const double &critical,
                   const double &unit_price, const Category &category) : Material() {
    set_material_id(id);
    set_material_name(name);
    set_material_measure_unit(measure_unit);
    set_material_quantity(quantity);
    set_material_critical(critical);
    set_material_unit_price(unit_price);
    set_material_category(category);
}

// Copy constructorul
Material::Material(const Material &other) : Material() {
    set_material_id(other.id);
    set_material_name(other.name);
    set_material_measure_unit(other.measure_unit);
    set_material_quantity(other.quantity);
    set_material_critical(other.critical);
    set_material_unit_price(other.unit_price);
    set_material_category(other.category);
}

// Destructor
Material::~Material() {
    delete[] this->id;
    delete[] this->name;
    delete[] this->measure_unit;
}

// Getters
char *Material::get_material_id() const { return this->id; }
char *Material::get_material_name() const { return this->name; }
char *Material::get_material_measure_unit() const { return this->measure_unit; }
double Material::get_material_critical() const { return this->critical; }
double Material::get_material_unit_price() const { return this->unit_price; }
double Material::get_material_quantity() const { return this->quantity; }
Material::Category Material::get_material_category() const { return this->category; }

// Setters
void Material::set_material_id(const char *new_material_id) {
    delete[] this->id;
    this->id = (new_material_id != nullptr)
                   ? (strcpy(new char[strlen(new_material_id) + 1], new_material_id))
                   : nullptr;
}

void Material::set_material_name(const char *new_material_name) {
    delete[] this->name;
    this->name = (new_material_name != nullptr)
                     ? (strcpy(new char[strlen(new_material_name) + 1], new_material_name))
                     : nullptr;
}

void Material::set_material_measure_unit(const char *new_material_measure_unit) {
    delete[] this->measure_unit;
    this->measure_unit = (new_material_measure_unit != nullptr)
                             ? (strcpy(new char[strlen(new_material_measure_unit) + 1], new_material_measure_unit))
                             : nullptr;
}

void Material::set_material_critical(const double &new_material_critical) {
    this->critical = (new_material_critical >= 0) ? new_material_critical : 0;
}

void Material::set_material_unit_price(const double &new_material_unit_price) {
    this->unit_price = (new_material_unit_price >= 0) ? new_material_unit_price : 0;
}

void Material::set_material_quantity(const double &new_material_quantity) {
    this->quantity = (new_material_quantity >= 0) ? new_material_quantity : 0;
}

void Material::set_material_category(const Category &new_material_category) {
    this->category = new_material_category;
}

// Supraincarcare operator de atribuire
// Nu mai este nevoie sa initializam pointerii la nullptr pentru ca avem garantia constructorilor ca putem sterge zonele de memorie alocate
Material &Material::operator=(const Material &other) {
    if (this == &other)
        return *this;

    set_material_id(other.id);
    set_material_name(other.name);
    set_material_measure_unit(other.measure_unit);
    set_material_quantity(other.quantity);
    set_material_critical(other.critical);
    set_material_unit_price(other.unit_price);
    set_material_category(other.category);

    return *this;
}

// Supraincarcarea operatorilor relationali
// Aplicam si aici verificari ale validitatii datelor pentru a putea folosi strcmp
bool Material::operator==(const Material &other) const {
    if ((this->id == nullptr) != (other.id == nullptr)) return false;
    if (this->id != nullptr && other.id != nullptr && strcmp(this->id, other.id) != 0) return false;

    if ((this->name == nullptr) != (other.name == nullptr)) return false;
    if (this->name != nullptr && other.name != nullptr && strcmp(this->name, other.name) != 0) return false;

    if ((this->measure_unit == nullptr) != (other.measure_unit == nullptr)) return false;
    if (this->measure_unit != nullptr && other.measure_unit != nullptr && strcmp(this->measure_unit, other.measure_unit)
        != 0) return false;

    return this->quantity == other.quantity &&
           this->critical == other.critical &&
           this->unit_price == other.unit_price &&
           this->category == other.category;
}

bool Material::operator!=(const Material &other) const {
    return !(*this == other);
}

//Interschimbare
void Material::swap(Material &material1, Material &material2) noexcept {
    std::swap(material1.id, material2.id);
    std::swap(material1.name, material2.name);
    std::swap(material1.measure_unit, material2.measure_unit);
    std::swap(material1.quantity, material2.quantity);
    std::swap(material1.critical, material2.critical);
    std::swap(material1.unit_price, material2.unit_price);
    std::swap(material1.category, material2.category);
}

std::ostream &operator<<(std::ostream &os, const Material &material) {
    os << "[ " << (material.id ? material.id : "N/A") << " ] " << (material.name ? material.name : "N/A") << "\n";
    os << "  Category    : " << Material::material_category_to_string(material.category) << "\n";
    os << "  Quantity    : " << material.quantity << " " << (material.measure_unit ? material.measure_unit : "N/A") << "\n";
    os << "  Critical    : " << material.critical << " " << (material.measure_unit ? material.measure_unit : "N/A") << "\n";
    os << "  Price/unit  : " << material.unit_price << " RON\n\n";

    return os;
}

// Supraincarcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Material &material) {
    char material_id[256];
    char material_name[256];
    char material_measure_unit[256];
    int material_category;
    double temp;

    std::cout << "Enter material ID: ";
    is >> material_id;
    material.set_material_id(material_id);

    std::cout << "Enter material name: ";
    is >> material_name;
    material.set_material_name(material_name);

    std::cout << "Enter measure unit: ";
    is >> material_measure_unit;
    material.set_material_measure_unit(material_measure_unit);

    std::cout << "Enter quantity: ";
    is >> temp;
    material.set_material_quantity(temp);

    std::cout << "Enter critical level: ";
    is >> temp;
    material.set_material_critical(temp);

    std::cout << "Enter unit price: ";
    is >> temp;
    material.set_material_unit_price(temp);

    std::cout << "Enter category (0: wood, 1: metal, 2: finishes, 3: insulation, 4: others): ";
    is >> material_category;
    material_category = (material_category >= 0 && material_category <= 4) ? material_category : 4;
    material.set_material_category(static_cast<Material::Category>(material_category));

    return is;
}

// Convertor category la string
const char *Material::material_category_to_string(const Category &category) {
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
