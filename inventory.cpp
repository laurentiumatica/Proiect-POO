#include "inventory.h"
#include <regex>
#include <algorithm>
#include <iostream>

// Constructorul default
Inventory::Inventory() = default;

// Constructorul cu parametri
Inventory::Inventory(const std::string_view new_inventory_id, const std::string_view new_inventory_name, const std::string_view new_inventory_address,
                     const std::string_view new_inventory_phone, const std::string_view new_inventory_email,
                     const std::span<const Material> new_inventory_materials,
                     const std::span<const Provider> new_inventory_providers,
                     const std::span<const Order> new_inventory_orders)
    : id(new_inventory_id), name(new_inventory_name), address(new_inventory_address),
      phone(new_inventory_phone), email(new_inventory_email) {
    validate_inventory_id(id);
    validate_inventory_name(name);
    validate_inventory_address(address);
    validate_inventory_phone(phone);
    validate_inventory_email(email);
    validate_inventory_materials(materials);
    validate_inventory_providers(providers);
    validate_inventory_orders(orders);
}

// Copy constructor
Inventory::Inventory(const Inventory &other) : Inventory(other.id, other.name, other.address, other.phone, other.email, other.materials, other.providers, other.orders) {}

// Destructor
Inventory::~Inventory() = default;

// Getters
const std::string &Inventory::get_inventory_id() const { return id; }
const std::string &Inventory::get_inventory_name() const { return name; }
const std::string &Inventory::get_inventory_address() const { return address; }
const std::string &Inventory::get_inventory_phone() const { return phone; }
const std::string &Inventory::get_inventory_email() const { return email; }
const std::vector<Material> &Inventory::get_inventory_materials() const { return materials; }
const std::vector<Provider> &Inventory::get_inventory_providers() const { return providers; }
const std::vector<Order> &Inventory::get_inventory_orders() const { return orders; }
int Inventory::get_inventory_materials_count() const { return static_cast<int>(materials.size()); }
int Inventory::get_inventory_providers_count() const { return static_cast<int>(providers.size()); }
int Inventory::get_inventory_orders_count() const { return static_cast<int>(orders.size()); }

// Setters
void Inventory::set_inventory_id(const std::string_view new_inventory_id) {
    validate_inventory_id(new_inventory_id);
    id = new_inventory_id;
}

void Inventory::set_inventory_name(const std::string_view new_inventory_name) {
    validate_inventory_name(new_inventory_name);
    name = new_inventory_name;
}

void Inventory::set_inventory_address(const std::string_view new_inventory_address) {
    validate_inventory_address(new_inventory_address);
    address = new_inventory_address;
}

void Inventory::set_inventory_phone(const std::string_view new_inventory_phone) {
    validate_inventory_phone(new_inventory_phone);
    phone = new_inventory_phone;
}

void Inventory::set_inventory_email(const std::string_view new_inventory_email) {
    validate_inventory_email(new_inventory_email);
    email = new_inventory_email;
}

void Inventory::set_inventory_materials(const std::span<const Material> new_inventory_materials) {
    validate_inventory_materials(new_inventory_materials);
    materials = std::vector(new_inventory_materials.begin(), new_inventory_materials.end());
}

void Inventory::set_inventory_providers(const std::span<const Provider> new_inventory_providers) {
    validate_inventory_providers(new_inventory_providers);
    providers = std::vector(new_inventory_providers.begin(), new_inventory_providers.end());
}

void Inventory::set_inventory_orders(const std::span<const Order> new_inventory_orders) {
    validate_inventory_orders(new_inventory_orders);
    orders = std::vector(new_inventory_orders.begin(), new_inventory_orders.end());
}

// Metode care modifica starea obiectului
void Inventory::add_material(const Material &material) {
    auto it = find_material_by_id(material.get_material_id());
    if (it != nullptr) {
        const double new_quantity = it->get_material_quantity() + material.get_material_quantity();
        it->set_material_quantity(new_quantity);
    } else {
        materials.push_back(material);
    }
}

void Inventory::register_provider(const std::span<const Provider> available_providers) {
    print_available_unregistered_providers(available_providers);
    read_string("Enter provider ID to register", [this, available_providers](const std::string &input) {
        auto it = std::ranges::find_if(available_providers, [&input](const Provider &p) { return p.get_provider_id() == input; });
        if (it == available_providers.end())
            throw std::invalid_argument("No provider with this ID found in the available providers list");
        if (find_provider_by_id(it->get_provider_id()) != nullptr)
            throw std::invalid_argument("Provider with this ID is already registered");

        providers.push_back(*it);
    });
}

void Inventory::place_order() {
    print_inventory_providers();

    Provider *selected_provider = nullptr;
    read_string("Enter provider ID to place order", [this, &selected_provider](const std::string &s) {
        selected_provider = find_provider_by_id(s);
        if (selected_provider == nullptr)
            throw std::invalid_argument("No provider with this ID found in the inventory providers list");
    });

    std::cout << *selected_provider;

    Order new_order;
    new_order.set_order_provider_id(selected_provider->get_provider_id());
    new_order.set_order_status(Order::Status::pending);

    read_string("Enter order ID", [&new_order](const std::string &s) { new_order.set_order_id(s); });
    read_string("Enter order date (expected format: DD-MM-YYYY)", [&new_order](const std::string &s) { new_order.set_order_date(s); });

    int cnt;
    read_string("Enter number of materials to order", [&cnt, selected_provider](const std::string &s) {
        cnt = std::stoi(s);
        if (cnt <= 0)
            throw std::invalid_argument("Number of materials to order must not be 0");
        if (cnt > selected_provider->get_provider_materials_count())
            throw std::invalid_argument("Number of materials to order must not exceed the number of materials provided");
    });

    std::vector<Order::OrderMaterial> buffer;
    for (int i = 0; i < cnt; i++) {
        Order::OrderMaterial order_material;

        read_string("Enter material ID to order", [selected_provider, &order_material, &buffer](const std::string &s) {
            const auto &provider_materials = selected_provider->get_provider_materials();
            auto material_it = std::ranges::find_if(provider_materials, [&s](const Provider::ProviderMaterial &m) { return m.material_id == s; });
            if (material_it == provider_materials.end())
                throw std::invalid_argument("No material with this ID found in the provider materials list");

            Order::order_material_already_exists(s, buffer);

            order_material.material_id = material_it->material_id;
            order_material.material_name = material_it->material_name;
            order_material.material_category = material_it->material_category;
            order_material.material_unit_price = material_it->material_unit_price;
            order_material.material_measure_unit = material_it->material_measure_unit;
        });

        read_string("Enter material quantity to order", [&order_material](const std::string &s) {
            const double quantity = std::stod(s);
            if (quantity <= 0)
                throw std::invalid_argument("Material quantity to order must be greater than 0");
            order_material.material_quantity = quantity;
        });

        buffer.push_back(order_material);
    }

    new_order.set_order_materials(buffer);
    orders.push_back(new_order);
}

void Inventory::consume_material() {
    print_inventory_materials();

    Material *selected_material = nullptr;
    read_string("Enter material ID to send to building site", [this, &selected_material](const std::string &s) {
        selected_material=find_material_by_id(s);
        if (selected_material==nullptr)
            throw std::invalid_argument("No material with this ID found in the inventory materials list");
    });
    read_string("Enter quantity to send to building site", [selected_material](const std::string &s) {
        const double quantity = std::stod(s);
        if (quantity <= 0)
            throw std::invalid_argument("Material quantity to consume must be greater than 0");
        if (quantity > selected_material->get_material_quantity())
            throw std::invalid_argument("Material quantity to consume must not exceed the available quantity in inventory");

        const double new_quantity = selected_material->get_material_quantity() - quantity;
        selected_material->set_material_quantity(new_quantity);
    });
}

Material *Inventory::find_material_by_id(const std::string_view find_id) {
    auto it = std::ranges::find_if(materials, [find_id](const Material &m) { return m.get_material_id() == find_id; });
    return it != materials.end() ? &(*it) : nullptr;
}

Provider *Inventory::find_provider_by_id(const std::string_view find_id) {
    auto it = std::ranges::find_if(providers, [find_id](const Provider &p) {return p.get_provider_id()==find_id;});
    return it != providers.end() ? &(*it) : nullptr;
}

Order *Inventory::find_order_by_id(const std::string_view find_id) {
    auto it = std::ranges::find_if(orders, [find_id](const Order &o) { return o.get_order_id() == find_id; });
    return it != orders.end() ? &(*it) : nullptr;
}

// Logica de sortare pentru atributele instantei curente
void Inventory::sort_materials_by_name_ascending() {
    std::ranges::sort(this->materials, [](const Material &a, const Material &b) {
       return a.get_material_name() < b.get_material_name();
    });
}

void Inventory::sort_materials_by_name_descending() {
    std::ranges::sort(this->materials, [](const Material &a, const Material &b) {
       return a.get_material_name() > b.get_material_name();
    });
}

void Inventory::sort_materials_by_quantity_ascending() {
    std::ranges::sort(this->materials, [](const Material &a, const Material &b) {
       return a.get_material_quantity() < b.get_material_quantity();
    });
}

void Inventory::sort_materials_by_quantity_descending() {
    std::ranges::sort(this->materials, [](const Material &a, const Material &b) {
       return a.get_material_quantity() > b.get_material_quantity();
    });
}

void Inventory::sort_orders_by_total_price_ascending() {
    std::ranges::sort(this->orders, [](const Order &a, const Order &b) {
       return a.get_order_total_price() < b.get_order_total_price();
    });
}

void Inventory::sort_orders_by_total_price_descending() {
    std::ranges::sort(this->orders, [](const Order &a, const Order &b) {
       return a.get_order_total_price() > b.get_order_total_price();
    });
}

// Supraincarcarea operatorului de atribuire
// Nu mai este nevoie sa initializam pointerii la nullptr pentru ca avem garantia constructorilor ca putem sterge zonele de memorie alocate
Inventory &Inventory::operator=(Inventory other) {
    std::swap(this->id, other.id);
    std::swap(this->name, other.name);
    std::swap(this->address, other.address);
    std::swap(this->phone, other.phone);
    std::swap(this->email, other.email);
    std::swap(this->materials, other.materials);
    std::swap(this->providers, other.providers);
    std::swap(this->orders, other.orders);

    return *this;
}

// Supraincarcarea operatorilor relationali
// Aplicam si aici verificari ale validitatii datelor pentru a putea folosi strcmp
bool Inventory::operator==(const Inventory &other) const {
    return id == other.id &&
           name == other.name &&
           address == other.address &&
           phone == other.phone &&
           email == other.email &&
           std::ranges::equal(materials, other.materials) &&
           std::ranges::equal(providers, other.providers) &&
           std::ranges::equal(orders, other.orders);
}

bool Inventory::operator!=(const Inventory &other) const {
    return !(*this == other);
}

// Supraincarcarea operatorului de output
std::ostream &operator<<(std::ostream &os, const Inventory &inventory) {
    os << inventory.id << "  " << inventory.name << "\n";
    os << "|  Address    : " << inventory.address << "\n";
    os << "|  Phone      : " << inventory.phone << "\n";
    os << "|  Email      : " << inventory.email << "\n";
    os << "|  Materials  : " << inventory.get_inventory_materials_count() << "\n";
    os << "|  Providers  : " << inventory.get_inventory_providers_count() << "\n";
    os << "|  Orders     : " << inventory.get_inventory_orders_count() << "\n";
    os << "|_\n\n";

    return os;
}

// Functii helper
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

void Inventory::print_available_unregistered_providers(const std::span<const Provider> available_providers) {
    std::cout << "Available unregistered providers:\n\n";
    for (const auto &provider : available_providers)
        if (this->find_provider_by_id(provider.get_provider_id()) == nullptr)
            std::cout << provider << "\n";
    std::cout << "\n";
}

void Inventory::print_inventory_providers() const {
    std::cout << "Registered providers:\n\n";
    for (const auto &provider : providers)
        std::cout << provider << "\n";
    std::cout << "\n";
}

void Inventory::print_inventory_materials() const {
    std::cout << "Registered materials:\n\n";
    for (const auto &material : materials)
        std::cout << material << "\n";
    std::cout << "\n";
}

void Inventory::print_inventory_orders() const {
    std::cout << "Registered orders:\n\n";
    for (const auto &order : orders)
        std::cout << order << "\n";
    std::cout << "\n";
}

void Inventory::validate_inventory_id(const std::string_view new_inventory_id) {
    if (new_inventory_id.empty())
        throw std::invalid_argument("Inventory ID cannot be empty");
    static const std::regex id_regex("^INV-[0-9]{5}$");
    if (!std::regex_match(new_inventory_id.begin(), new_inventory_id.end(), id_regex)) {
        throw std::invalid_argument("Invalid inventory ID format (expected format: INV-#####");
    }
}

void Inventory::validate_inventory_name(const std::string_view new_inventory_name) {
    if (new_inventory_name.empty()) {
        throw std::invalid_argument("Inventory name must not be empty");
    }
    if (std::ranges::all_of(new_inventory_name, [](const unsigned char c) { return std::isspace(c); })) {
        throw std::invalid_argument("Inventory name must contain at least one non-space character");
    }
    if (!std::ranges::all_of(new_inventory_name, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); })) {
        throw std::invalid_argument("Inventory name must contain only letters, numbers and spaces");
    }
}

void Inventory::validate_inventory_address(const std::string_view new_inventory_address) {
    if (new_inventory_address.empty()) {
        throw std::invalid_argument("Provider address must not be empty");
    }
    if (std::ranges::all_of(new_inventory_address, [](const unsigned char c) { return std::isspace(c); })) {
        throw std::invalid_argument("Provider address must contain at least one non-space character");
    }
    if (!std::ranges::all_of(new_inventory_address, [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); })) {
        throw std::invalid_argument("Provider address must contain only letters, numbers and spaces");
    }
}

void Inventory::validate_inventory_phone(const std::string_view new_inventory_phone) {
    if (new_inventory_phone.empty()) {
        throw std::invalid_argument("Provider phone number must not be empty");
    }
    static const std::regex phone_regex("^[0-9]{10}$");
    if (!std::regex_match(new_inventory_phone.begin(), new_inventory_phone.end(), phone_regex)) {
        throw std::invalid_argument("Invalid provider phone number format (expected format: 10 digits)");
    }
}

void Inventory::validate_inventory_email(const std::string_view new_inventory_email) {
    if (new_inventory_email.empty()) {
        throw std::invalid_argument("Provider email must not be empty");
    }
    static const std::regex email_regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!std::regex_match(new_inventory_email.begin(), new_inventory_email.end(), email_regex)) {
        throw std::invalid_argument("Invalid provider email format");
    }
}

void Inventory::validate_inventory_materials(const std::span<const Material> new_inventory_materials) {
    if (new_inventory_materials.empty()) {
        throw std::invalid_argument("Inventory materials must not be empty");
    }
    for (const auto &material : new_inventory_materials) {
        Material::validate_material_id(material.get_material_id());
        Material::validate_material_name(material.get_material_name());
        Material::validate_material_quantity(material.get_material_quantity());
        Material::validate_material_measure_unit(material.get_material_measure_unit());
        Material::validate_material_unit_price(material.get_material_unit_price());
    }
}

void Inventory::validate_inventory_providers(const std::span<const Provider> new_inventory_providers) {
    if (new_inventory_providers.empty()) {
        throw std::invalid_argument("Inventory providers must not be empty");
    }
    for (const auto &provider : new_inventory_providers) {
        Provider::validate_provider_id(provider.get_provider_id());
        Provider::validate_provider_name(provider.get_provider_name());
        Provider::validate_provider_address(provider.get_provider_address());
        Provider::validate_provider_phone(provider.get_provider_phone());
        Provider::validate_provider_email(provider.get_provider_email());
        Provider::validate_provider_materials(provider.get_provider_materials());
    }
}

void Inventory::validate_inventory_orders(const std::span<const Order> new_inventory_orders) {
    if (new_inventory_orders.empty()) {
        throw std::invalid_argument("Inventory orders must not be empty");
    }
    for (const auto &order : new_inventory_orders) {
        Order::validate_order_id(order.get_order_id());
        Order::validate_order_date(order.get_order_date());
        Order::validate_order_materials(order.get_order_materials());
    }
}