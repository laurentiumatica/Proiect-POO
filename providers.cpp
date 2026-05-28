#include "providers.h"
#include "materials.h"
#include <iostream>
#include <regex>
#include <algorithm>
#include <iomanip>

#include "utils.h"

// Constructorul default
Provider::Provider() = default;

// Constructorul cu parametri
Provider::Provider(std::string id, std::string name, std::string phone, std::string email, std::string address, std::vector<Material> materials)
    : id(std::move(id)),name(std::move(name)), phone(std::move(phone)), email(std::move(email)), address(std::move(address)), materials(std::move(materials)) {
    Utils::validate_provider_id(this->id);
    Utils::validate_provider_name(this->name);
    Utils::validate_provider_phone(this->phone);
    Utils::validate_provider_email(this->email);
    Utils::validate_provider_address(this->address);
    Utils::validate_provider_materials(this->materials);
}

// Copy constructor
Provider::Provider(const Provider &other) = default;

// Destructorul
Provider::~Provider() = default;

// Getters
const std::string &Provider::get_provider_id() const { return id; }
const std::string &Provider::get_provider_name() const { return name; }
const std::string &Provider::get_provider_phone() const { return phone; }
const std::string &Provider::get_provider_email() const { return email; }
const std::string &Provider::get_provider_address() const { return address; }
const std::vector<Material>& Provider::get_provider_materials() const { return materials; }
int Provider::get_provider_materials_count() const { return static_cast<int>(materials.size()); }

// Supraincarcarea operatorului de atribuire
Provider &Provider::operator=(Provider other) {
    std::swap(id,other.id);
    std::swap(name,other.name);
    std::swap(phone,other.phone);
    std::swap(email,other.email);
    std::swap(address,other.address);
    std::swap(materials,other.materials);

    return *this;
}

// Supraincarcarea operatorilor de I/O
std::ostream &operator<<(std::ostream &os, const Provider &provider) {
    os << provider.id << " " << provider.name << "\n";
    os << "|  Phone      : " << provider.phone << "\n";
    os << "|  Email      : " << provider.email << "\n";
    os << "|  Address    : " << provider.address << "\n";
    os << "|  Materials  : \n";
    for (const auto &material : provider.materials)
        os << "|    - " << material.get_material_id() << " " << material.get_material_name()
        << " (Category: " << Material::material_category_to_string(material.get_material_category())
        << ", Unit: " << material.get_material_measure_unit() << ", Unit price: " << std::fixed << std::setprecision(2) << material.get_material_unit_price() << ")\n";
    os << "|_\n\n";

    return os;
}

// Functii helper
void Provider::print_available_materials(const std::vector<Material> &materials) {
    for (const auto &material : materials)
        std::cout << material.get_material_id() << " " << material.get_material_name() << " (Category: "
        << Material::material_category_to_string(material.get_material_category()) << ", Unit: "
        << material.get_material_measure_unit() << ", Unit price: " << material.get_material_unit_price() << ")\n";
}