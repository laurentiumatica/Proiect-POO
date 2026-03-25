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

// Constructorul cu parametri
Material::Material(const char *id, const char *name, const char *measure_unit,
                   const double &quantity, const double &critical,
                   const double &unit_price, const Category &category) {
  this->id = new char[strlen(id) + 1]; // Alocăm blocul pe heap exact pentru capacitatea cerută (plus \0)
  strcpy(this->id, id); // Copiem valoarea efectivă

  this->name = new char[strlen(name) + 1];
  strcpy(this->name, name);

  this->measure_unit = new char[strlen(measure_unit) + 1];
  strcpy(this->measure_unit, measure_unit);

  this->quantity = quantity;
  this->critical = critical;
  this->unit_price = unit_price;
  this->category = category;
}

// Copy constructorul
Material::Material(const Material &other) {
  if (other.id != nullptr) {
    this->id = new char[strlen(other.id) + 1]; // Dacă obiectul sursă are proprietatea populată, alocăm noi copiem
    strcpy(this->id, other.id);
  }
  else {
    this->id = nullptr; // Altfel, setăm nullptr (protejăm de segfault)
  }

  if (other.name != nullptr) {
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
  }
  else {
    this->name = nullptr;
  }

  if (other.measure_unit != nullptr) {
    this->measure_unit = new char[strlen(other.measure_unit) + 1];
    strcpy(this->measure_unit, other.measure_unit);
  }
  else {
    this->measure_unit = nullptr;
  }

  this->quantity = other.quantity;
  this->critical = other.critical;
  this->unit_price = other.unit_price;
  this->category = other.category;
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
Material::Category Material::get_material_category() const {
  return this->category;
}

// Setters
void Material::set_material_id(const char *new_id) {
  delete[] this->id; // Mai întâi ștergem segmentul de memorie cu vechea valoare a instanței
  this->id = new char[strlen(new_id) + 1]; // Cerem memorie exact pe dimensiunea noii valori ce trebuie salvată
  strcpy(this->id, new_id); // Setăm noul member din heap
}

void Material::set_material_name(const char *new_name) {
  delete[] this->name;
  this->name = new char[strlen(new_name) + 1];
  strcpy(this->name, new_name);
}

void Material::set_material_measure_unit(const char *new_measure_unit) {
  delete[] this->measure_unit;
  this->measure_unit = new char[strlen(new_measure_unit) + 1];
  strcpy(this->measure_unit, new_measure_unit);
}

void Material::set_material_critical(const double &new_critical) {
  this->critical = new_critical;
}

void Material::set_material_unit_price(const double &new_unit_price) {
  this->unit_price = new_unit_price;
}

void Material::set_material_quantity(const double &new_quantity) {
  this->quantity = new_quantity;
}

void Material::set_material_category(const Category &new_category) {
  this->category = new_category;
}

// Supraîncărcare operator =
Material &Material::operator=(const Material &other) {
  if (this == &other)
    return *this;

  delete[] this->id;
  delete[] this->name;
  delete[] this->measure_unit;

  if (other.id != nullptr) {
    this->id = new char[strlen(other.id) + 1];
    strcpy(this->id, other.id);
  } else {
    this->id = nullptr;
  }

  if (other.name != nullptr) {
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
  } else {
    this->name = nullptr;
  }

  if (other.measure_unit != nullptr) {
    this->measure_unit = new char[strlen(other.measure_unit) + 1];
    strcpy(this->measure_unit, other.measure_unit);
  } else {
    this->measure_unit = nullptr;
  }

  this->quantity = other.quantity;
  this->critical = other.critical;
  this->unit_price = other.unit_price;
  this->category = other.category;

  return *this;
}
// Supraîncărcarea operatorilor relaționali
bool Material::operator==(const Material &other) const {
  return strcmp(this->id, other.id) == 0 &&
         strcmp(this->name, other.name) == 0 &&
         strcmp(this->measure_unit, other.measure_unit) == 0 &&
         this->quantity == other.quantity && this->critical == other.critical &&
         this->unit_price == other.unit_price &&
         this->category == other.category;
}

bool Material::operator!=(const Material &other) const {
  return !(*this == other); // Inversează evaluarea metodei de equality
}

//Interschimbare
void Material::swap(Material &material1, Material &material2) noexcept {
  const Material temp = material1; // Tragem instanța 1 prin copy operatorul preexistent
  material1 = material2; // Setăm instanța 1 cu data class assignment operat din material2
  material2 = temp; // Răsturnare back data original salvată a lui temp
}

std::ostream &operator<<(std::ostream &os, const Material &material) {
  os << "[ " << material.id << " ] " << material.name << "\n";
  os << "  Category    : " << Material::material_category_to_string(material.category) << "\n";
  os << "  Quantity    : " << material.quantity << " " << material.measure_unit << "\n";
  os << "  Critical    : " << material.critical << " " << material.measure_unit << "\n";
  os << "  Price/unit  : " << material.unit_price << " RON\n\n";

  return os;
}

// Supraîncărcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Material &material) {
  char id[256];
  char name[256];
  char measure_unit[256];
  int category;

  std::cout << "Enter material ID: ";
  is >> id; // Primim input care trebuie preluat ca setter pentru atribut
  delete[] material.id; // Din nou curățăm buffer-ul pe object
  material.id = new char[strlen(id) + 1]; // Reținem lungimea potrivită pentru member field al instanței
  strcpy(material.id, id);

  std::cout << "Enter material name: ";
  is >> name;
  delete[] material.name;
  material.name = new char[strlen(name) + 1];
  strcpy(material.name, name);

  std::cout << "Enter measure unit: ";
  is >> measure_unit;
  delete[] material.measure_unit;
  material.measure_unit = new char[strlen(measure_unit) + 1];
  strcpy(material.measure_unit, measure_unit);

  std::cout << "Enter quantity: ";
  is >> material.quantity;

  std::cout << "Enter critical level: ";
  is >> material.critical;

  std::cout << "Enter unit price: ";
  is >> material.unit_price;

  std::cout << "Enter category:\n"
            << "  0 - wood\n"
            << "  1 - metal\n"
            << "  2 - insulation\n"
            << "  3 - finishes\n"
            << "  4 - others\n"
            << ": ";
  is >> category;
  switch (category) {
    case 0:
      material.category = Material::Category::wood;
      break;
    case 1:
      material.category = Material::Category::metal;
      break;
    case 2:
      material.category = Material::Category::insulation;
      break;
    case 3:
      material.category = Material::Category::finishes;
      break;
    default:
      material.category = Material::Category::others;
      break;
  }

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
