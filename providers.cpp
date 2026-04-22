#include "providers.h"
#include "materials.h"
#include <iostream>
#include <regex>
#include <algorithm>
#include <iomanip>

// Constructorul default
Provider::Provider() = default;

// Constructorul cu parametri
Provider::Provider(const std::string_view new_provider_id, const std::string_view new_provider_name,
                   const std::string_view new_provider_phone, const std::string_view new_provider_email,
                   const std::string_view new_provider_address, const std::span<const ProviderMaterial> new_provider_materials)
    : id(new_provider_id), name(new_provider_name),
      phone(new_provider_phone), email(new_provider_email),
      address(new_provider_address), materials(new_provider_materials.begin(), new_provider_materials.end()) {
    validate_provider_id(new_provider_id);
    validate_provider_name(new_provider_name);
    validate_provider_phone(new_provider_phone);
    validate_provider_email(new_provider_email);
    validate_provider_address(new_provider_address);
    validate_provider_materials(new_provider_materials);
}

// Copy constructor
Provider::Provider(const Provider &other)
    : Provider(other.id, other.name, other.phone, other.email, other.address, other.materials) {};

// Destructorul
Provider::~Provider() = default;

// Getters
const std::string &Provider::get_provider_id() const { return id; }
const std::string &Provider::get_provider_name() const { return name; }
const std::string &Provider::get_provider_phone() const { return phone; }
const std::string &Provider::get_provider_email() const { return email; }
const std::string &Provider::get_provider_address() const { return address; }
const std::vector<Provider::ProviderMaterial>& Provider::get_provider_materials() const { return materials; }
int Provider::get_provider_materials_count() const { return static_cast<int>(materials.size()); }

// Setters
void Provider::set_provider_id(const std::string_view new_provider_id) {
    validate_provider_id(new_provider_id);
    id = new_provider_id;
}
void Provider::set_provider_name(const std::string_view new_provider_name) {
    validate_provider_name(new_provider_name);
    name = new_provider_name;
}
void Provider::set_provider_phone(const std::string_view new_provider_phone) {
    validate_provider_phone(new_provider_phone);
    phone = new_provider_phone;
}
void Provider::set_provider_email(const std::string_view new_provider_email) {
    validate_provider_email(new_provider_email);
    email = new_provider_email;
}
void Provider::set_provider_address(const std::string_view new_provider_address) {
    validate_provider_address(new_provider_address);
    address = new_provider_address;
}
void Provider::set_provider_materials(const std::span<const ProviderMaterial> new_provider_materials) {
    validate_provider_materials(new_provider_materials);
    materials = std::vector(new_provider_materials.begin(), new_provider_materials.end());
}

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

// Supraincarcarea operatorilor relationali
bool Provider::operator==(const Provider &other) const {
    constexpr double epsilon = 1e-9;

    return id == other.id &&
           name == other.name &&
           phone == other.phone &&
           email == other.email &&
           address == other.address &&
           std::ranges::equal(materials, other.materials, [](const ProviderMaterial &m1, const ProviderMaterial &m2) {
               return m1.material_id == m2.material_id &&
                      m1.material_name == m2.material_name &&
                      m1.material_category == m2.material_category &&
                      m1.material_measure_unit == m2.material_measure_unit &&
                      std::abs(m1.material_unit_price - m2.material_unit_price) < epsilon;
           });
}
bool Provider::operator!=(const Provider &other) const { return !(*this == other); }

// Interschimbare
void Provider::swap(Provider &provider1, Provider &provider2) noexcept {
    std::swap(provider1.id, provider2.id);
    std::swap(provider1.name, provider2.name);
    std::swap(provider1.phone, provider2.phone);
    std::swap(provider1.email, provider2.email);
    std::swap(provider1.address, provider2.address);
    std::swap(provider1.materials, provider2.materials);
}

// Supraincarcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Provider &provider) {
    std::vector<Provider::ProviderMaterial> buffer;
    int cnt;
    
    is.ignore();

    Provider::read_string("Enter provider ID (expected format: PRV-#####)", [&provider](const std::string &s) { provider.set_provider_id(s); });
    Provider::read_string("Enter provider name", [&provider](const std::string &s) { provider.set_provider_name(s); });
    Provider::read_string("Enter provider phone (expected format: 10 digits)", [&provider](const std::string &s) { provider.set_provider_phone(s); });
    Provider::read_string("Enter provider email", [&provider](const std::string &s) { provider.set_provider_email(s); });
    Provider::read_string("Enter provider address", [&provider](const std::string &s) { provider.set_provider_address(s); });
    Provider::read_string("Enter number of materials", [&cnt](const std::string &s) { cnt = std::stoi(s); Provider::validate_provider_materials_number(cnt); });
    
    for (int i=0;i<cnt;i++) {
        Provider::ProviderMaterial material;
        Provider::read_material(material, buffer);
        buffer.push_back(material);
    }

    provider.set_provider_materials(buffer);

    return is;
}

std::ostream &operator<<(std::ostream &os, const Provider &provider) {
    os << provider.id << " " << provider.name << "\n";
    os << "|  Phone      : " << provider.phone << "\n";
    os << "|  Email      : " << provider.email << "\n";
    os << "|  Address    : " << provider.address << "\n";
    os << "|  Materials  : \n";
    for (const auto &[material_id, material_name, material_measure_unit, material_category, unit_price] : provider.materials)
        os << "|    - " << material_id << " " << material_name << " (Category: " << Material::material_category_to_string(material_category) << ", Unit: " << material_measure_unit << ", Unit price: " << std::fixed << std::setprecision(2) << unit_price << ")\n";
    os << "|_\n\n";

    return os;
}

// Functii helper
void Provider::validate_provider_id(const std::string_view new_provider_id) {
    if (new_provider_id.empty()) {
        throw std::invalid_argument("Provider ID must not be empty");
    }
    static const std::regex id_regex("^PRV-[0-9]{5}$");
    if (!std::regex_match(new_provider_id.begin(), new_provider_id.end(), id_regex)) {
        throw std::invalid_argument("Invalid provider ID format (expected format: PRV-XXXXX)");
    }
}

void Provider::validate_provider_name(const std::string_view new_provider_name) {
    if (new_provider_name.empty()) {
        throw std::invalid_argument("Provider name must not be empty");
    }
    if (std::ranges::all_of(new_provider_name, [](const unsigned char c) { return std::isspace(c); })) {
        throw std::invalid_argument("Provider name must contain at least one non-space character");
    }
    if (!std::ranges::all_of(new_provider_name, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); })) {
        throw std::invalid_argument("Provider name must contain only letters, numbers and spaces");
    }
}

void Provider::validate_provider_phone(const std::string_view new_provider_phone) {
    if (new_provider_phone.empty()) {
        throw std::invalid_argument("Provider phone number must not be empty");
    }
    static const std::regex phone_regex("^[0-9]{10}$");
    if (!std::regex_match(new_provider_phone.begin(), new_provider_phone.end(), phone_regex)) {
        throw std::invalid_argument("Invalid provider phone number format (expected format: 10 digits)");
    }
}

void Provider::validate_provider_email(const std::string_view new_provider_email) {
    if (new_provider_email.empty()) {
        throw std::invalid_argument("Provider email must not be empty");
    }
    static const std::regex email_regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!std::regex_match(new_provider_email.begin(), new_provider_email.end(), email_regex)) {
        throw std::invalid_argument("Invalid provider email format");
    }
}

void Provider::validate_provider_address(const std::string_view new_provider_address) {
    if (new_provider_address.empty()) {
        throw std::invalid_argument("Provider address must not be empty");
    }
    if (std::ranges::all_of(new_provider_address, [](const unsigned char c) { return std::isspace(c); })) {
        throw std::invalid_argument("Provider address must contain at least one non-space character");
    }
    if (!std::ranges::all_of(new_provider_address, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); })) {
        throw std::invalid_argument("Provider address must contain only letters, numbers and spaces");
    }
}

void Provider::provider_material_already_exists(const std::string_view material_id, const std::span<const ProviderMaterial> materials) {
    if (std::ranges::any_of(materials, [material_id](const ProviderMaterial &m) { return m.material_id == material_id; })) {
        throw std::invalid_argument("Provider material with the same ID already exists");
    }
}

void Provider::read_string(const std::string_view prompt, auto setter) {
    while (true) {
        try {
            std::cout << prompt << ": ";
            std::string temp;
            std::getline(std::cin, temp);
            setter(temp);
            break;
        } catch (const std::invalid_argument &e) {
            std::cout << "Error: " << e.what() << ". Try again.\n";
        } catch (const std::out_of_range &) {
            std::cout << "Error: value out of range. Try again.\n";
        }
    }
}

void Provider::set_provider_material_id(ProviderMaterial &material, const std::string_view new_provider_material_id, const std::span<const ProviderMaterial> materials) {
    Material::validate_material_id(new_provider_material_id);
    provider_material_already_exists(new_provider_material_id, materials);
    material.material_id = new_provider_material_id;
}

void Provider::set_provider_material_name(ProviderMaterial &material, const std::string_view new_provider_material_name) {
    Material::validate_material_name(new_provider_material_name);
    material.material_name = new_provider_material_name;
}

void Provider::set_provider_material_unit_price(ProviderMaterial &material, const double new_provider_material_unit_price) {
    Material::validate_material_unit_price(new_provider_material_unit_price);
    material.material_unit_price = new_provider_material_unit_price;
}

void Provider::set_provider_material_measure_unit(ProviderMaterial &material, const std::string_view new_provider_material_measure_unit) {
    Material::validate_material_measure_unit(new_provider_material_measure_unit);
    material.material_measure_unit = new_provider_material_measure_unit;
}

void Provider::read_material(ProviderMaterial &material, const std::span<const ProviderMaterial> materials) {
    read_string("Enter material ID (expected format: MAT-#####)", [&material, materials](const std::string &s) { set_provider_material_id(material, s, materials); });
    read_string("Enter material name", [&material](const std::string &s) { set_provider_material_name(material, s); });
    read_string("Enter material measure unit", [&material](const std::string &s) { set_provider_material_measure_unit(material, s); });
    read_string("Enter material category (0 - wood, 1 - metal, 2 - insulation, 3 - finishes, 4 - others)",
    [&material](const std::string &s) {
        const int cat = std::stoi(s);
        if (cat < 0 || cat > 4)
            throw std::invalid_argument("Category must be between 0 and 4");
        material.material_category = static_cast<Material::Category>(cat);
    });
    read_string("Enter material unit price", [&material](const std::string &s) { set_provider_material_unit_price(material, std::stod(s)); });
}

void Provider::validate_provider_materials_number(const int new_provider_materials_number) {
    if (new_provider_materials_number < 1) {
        throw std::invalid_argument("Provider materials number must be at least 1");
    }
    // Am ales 15 ca limita superioara strict in scop demonstrativ
    if (new_provider_materials_number > 15) {
        throw std::invalid_argument("Provider materials number must be at most 15");
    }
}


void Provider::validate_provider_materials(const std::span<const ProviderMaterial> new_provider_materials) {
    validate_provider_materials_number(static_cast<int>(new_provider_materials.size()));
    for (const auto &[material_id, material_name, material_measure_unit, material_category, material_unit_price] : new_provider_materials) {
        Material::validate_material_id(material_id);
        Material::validate_material_name(material_name);
        Material::validate_material_measure_unit(material_measure_unit);
        Material::validate_material_unit_price(material_unit_price);
    }
    for (int i=0;i<static_cast<int>(new_provider_materials.size())-1;i++)
        for (int j=i+1;j<static_cast<int>(new_provider_materials.size());j++)
            if (new_provider_materials[i].material_id == new_provider_materials[j].material_id)
                throw std::invalid_argument("Provider materials must not contain duplicate ID's");
}

void Provider::print_available_materials(const std::span<const ProviderMaterial> available_materials) {
    for (const auto &[material_id, material_name, material_measure_unit, material_category, material_unit_price] : available_materials)
        std::cout << material_id << " " << material_name << " (Category: " << Material::material_category_to_string(material_category) << ", Unit: " << material_measure_unit << ", Unit price: " << material_unit_price << ")\n";
}