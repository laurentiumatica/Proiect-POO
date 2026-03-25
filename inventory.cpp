#include "inventory.h"
#include <cstring>
#include <iostream>

// Constructorul default
Inventory::Inventory() {
    this->id = nullptr;
    this->name = nullptr;
    this->address = nullptr;
    this->phone = nullptr;
    this->email = nullptr;
    this->materials = nullptr;
    this->providers = nullptr;
    this->orders = nullptr;
    this->materials_count = 0;
    this->providers_count = 0;
    this->orders_count = 0;
}

// Copy constructor
Inventory::Inventory(const Inventory &other) : Inventory() {
    set_inventory_id(other.get_inventory_id());
    set_inventory_name(other.get_inventory_name());
    set_inventory_address(other.get_inventory_address());
    set_inventory_phone(other.get_inventory_phone());
    set_inventory_email(other.get_inventory_email());
    set_inventory_materials(other.get_inventory_materials(), other.get_inventory_materials_count());
    set_inventory_providers(other.get_inventory_providers(), other.get_inventory_providers_count());
    set_inventory_orders(other.get_inventory_orders(), other.get_inventory_orders_count());
}

// Constructorul cu parametri
Inventory::Inventory(const char *id, const char *name, const char *address, const char *phone, const char *email,
                     const Material *materials, const Provider *providers, const Order *orders,
                     const int &materials_count, const int &providers_count, const int &orders_count) : Inventory() {
    set_inventory_id(id);
    set_inventory_name(name);
    set_inventory_address(address);
    set_inventory_phone(phone);
    set_inventory_email(email);
    set_inventory_materials(materials, materials_count);
    set_inventory_providers(providers, providers_count);
    set_inventory_orders(orders, orders_count);
}

// Destructor
Inventory::~Inventory() {
    delete[] this->id;
    delete[] this->name;
    delete[] this->address;
    delete[] this->phone;
    delete[] this->email;
    delete[] this->materials;
    delete[] this->providers;
    delete[] this->orders;
}

// Getters
char *Inventory::get_inventory_id() const { return this->id; }
char *Inventory::get_inventory_name() const { return this->name; }
char *Inventory::get_inventory_address() const { return this->address; }
char *Inventory::get_inventory_phone() const { return this->phone; }
char *Inventory::get_inventory_email() const { return this->email; }
Material *Inventory::get_inventory_materials() const { return this->materials; }
Provider *Inventory::get_inventory_providers() const { return this->providers; }
Order *Inventory::get_inventory_orders() const { return this->orders; }
int Inventory::get_inventory_materials_count() const { return this->materials_count; }
int Inventory::get_inventory_providers_count() const { return this->providers_count; }
int Inventory::get_inventory_orders_count() const { return this->orders_count; }

void Inventory::set_inventory_id(const char *new_inventory_id) {
    delete[] this->id;
    this->id = (new_inventory_id != nullptr) ? strcpy(new char[strlen(new_inventory_id)+1],new_inventory_id) : nullptr;
}

void Inventory::set_inventory_name(const char *new_inventory_name) {
    delete[] this->name;
    this->name = (new_inventory_name != nullptr) ? strcpy(new char[strlen(new_inventory_name)+1],new_inventory_name) : nullptr;
}

void Inventory::set_inventory_address(const char *new_inventory_address) {
    delete[] this->address;
    this->address = (new_inventory_address != nullptr) ? strcpy(new char[strlen(new_inventory_address)+1],new_inventory_address) : nullptr;
}

void Inventory::set_inventory_phone(const char *new_inventory_phone) {
    delete[] this->phone;
    this->phone = (new_inventory_phone != nullptr) ? strcpy(new char[strlen(new_inventory_phone)+1],new_inventory_phone) : nullptr;
}

void Inventory::set_inventory_email(const char *new_inventory_email) {
    delete[] this->email;
    this->email = (new_inventory_email != nullptr) ? strcpy(new char[strlen(new_inventory_email)+1],new_inventory_email) : nullptr;
}

void Inventory::set_inventory_materials(const Material *new_inventory_materials, const int &new_inventory_materials_count) {
    // Nu este nevoie de o stergere mai complexa a memoriei alocate datorita destructorilor obiectului
    delete[] this->materials;

    // Verificam posibilitatea de copiere a noilor valori si efectuam daca se poate
    this->materials_count = (new_inventory_materials_count > 0) ? new_inventory_materials_count : 0;
    if (this->materials_count > 0 && new_inventory_materials != nullptr) {
        this->materials = new Material[this->materials_count];
        for (int i = 0; i < this->materials_count; i++)
            this->materials[i] = new_inventory_materials[i];
    }
    else {
        this->materials = nullptr;
        this->materials_count = 0;
    }
}

void Inventory::set_inventory_providers(const Provider *new_inventory_providers, const int &new_inventory_providers_count) {
    // Nu este nevoie de o stergere mai complexa a memoriei alocate datorita destructorilor obiectului
    delete[] this->providers;

    // Verificam posibilitatea de copiere a noilor valori si efectuam daca se poate
    this->providers_count = (new_inventory_providers_count > 0) ? new_inventory_providers_count : 0;
    if (this->providers_count > 0 && new_inventory_providers != nullptr) {
        this->providers = new Provider [this->providers_count];
        for (int i = 0; i < this->providers_count; i++)
            this->providers[i] = new_inventory_providers[i];
    }
    else {
        this->providers = nullptr;
        this->providers_count = 0;
    }
}

void Inventory::set_inventory_orders(const Order *new_inventory_orders, const int &new_inventory_orders_count) {
    // Nu este nevoie de o stergere mai complexa a memoriei alocate datorita destructorilor obiectului
    delete[] this->orders;

    // Verificam posibilitatea de copiere a noilor valori si efectuam daca se poate
    this->orders_count = (new_inventory_orders_count > 0) ? new_inventory_orders_count : 0;
    if (this->orders_count > 0 && new_inventory_orders != nullptr) {
        this->orders = new Order [this->orders_count];
        for (int i = 0; i < this->orders_count; i++)
            this->orders[i] = new_inventory_orders[i];
    }
    else {
        this->orders = nullptr;
        this->orders_count = 0;
    }
}

// Metode care modifica starea obiectului
void Inventory::add_material(const Material &material) {
    // Alocam memorie pentru a putea adauga noul material si copiem materialele vechi
    const auto new_materials = new Material[this->materials_count + 1];
    for (int i = 0; i < this->materials_count; i++)
        new_materials[i] = this->materials[i];
    new_materials[this->materials_count++] = material;

    // Eliberam memoria folosita anterior
    delete[] this->materials;
    this->materials = new_materials;
}

void Inventory::add_provider(const Provider &provider) {
    // Alocam memorie pentru a putea adauga noul furnizor si copiem furnizorii vechi
    const auto new_providers = new Provider[this->providers_count + 1];
    for (int i = 0; i < this->providers_count; i++)
        new_providers[i] = this->providers[i];
    new_providers[this->providers_count++] = provider;

    // Eliberam memoria folosita anterior
    delete[] this->providers;
    this->providers = new_providers;
}

void Inventory::add_order(const Order &order) {
    // Alocam memorie pentru a putea adauga noua comanda si copiem comenzile vechi
    const auto new_orders = new Order[this->orders_count + 1];
    for (int i = 0; i < this->orders_count; i++)
        new_orders[i] = this->orders[i];
    new_orders[this->orders_count++] = order;

    // Eliberam memoria folosita anterior
    delete[] this->orders;
    this->orders = new_orders;
}

Material *Inventory::find_material_by_id(const char *find_id) const {
    if (find_id != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            if (this->materials[i].get_material_id() != nullptr && strcmp(this->materials[i].get_material_id(), find_id) == 0)
                return &this->materials[i];
    return nullptr;
}

Provider *Inventory::find_provider_by_id(const char *find_id) const {
    if (find_id != nullptr)
        for (int i = 0; i < this->providers_count; i++)
            if (this->providers[i].get_provider_id() != nullptr && strcmp(this->providers[i].get_provider_id(), find_id) == 0)
                return &this->providers[i];
    return nullptr;
}

Order *Inventory::find_order_by_id(const char *find_id) const {
    if (find_id != nullptr)
        for (int i = 0; i < this->orders_count; i++)
            if (this->orders[i].get_order_id() != nullptr && strcmp(this->orders[i].get_order_id(), find_id) == 0)
                return &this->orders[i];
    return nullptr;
}

// Logica de sortare pentru atributele instantei curente
void Inventory::sort_materials_by_name_ascending() {
    for (int i = 0; i < this->materials_count - 1; i++)
        for (int j = i + 1; j < this->materials_count; j++) {
            const char *material_name_i = this->materials[i].get_material_name();
            const char *material_name_j = this->materials[j].get_material_name();
            if (material_name_i != nullptr && material_name_j != nullptr) {
                if (strcmp(material_name_i, material_name_j) > 0)
                    Material::swap(this->materials[i], this->materials[j]);
            }
            else if (material_name_i == nullptr && material_name_j != nullptr)
                Material::swap(this->materials[i], this->materials[j]);
        }
}

void Inventory::sort_materials_by_name_descending() {
    for (int i = 0; i < this->materials_count - 1; i++)
        for (int j = i + 1; j < this->materials_count; j++) {
            const char *material_name_i = this->materials[i].get_material_name();
            const char *material_name_j = this->materials[j].get_material_name();
            if (material_name_i != nullptr && material_name_j != nullptr) {
                if (strcmp(material_name_i, material_name_j) < 0)
                    Material::swap(this->materials[i], this->materials[j]);
            }
            else if (material_name_i == nullptr && material_name_j != nullptr)
                Material::swap(this->materials[i], this->materials[j]);
        }
}

void Inventory::sort_materials_by_quantity_ascending() {
    for (int i = 0; i < this->materials_count - 1; i++)
        for (int j = i + 1; j < this->materials_count; j++)
            if (this->materials[i].get_material_quantity() > this->materials[j].get_material_quantity())
                Material::swap(this->materials[i], this->materials[j]);
}

void Inventory::sort_materials_by_quantity_descending() {
    for (int i = 0; i < this->materials_count - 1; i++)
        for (int j = i + 1; j < this->materials_count; j++)
            if (this->materials[i].get_material_quantity() < this->materials[j].get_material_quantity())
                Material::swap(this->materials[i], this->materials[j]);
}

void Inventory::sort_orders_by_total_price_ascending() {
    for (int i = 0; i < this->orders_count - 1; i++)
        for (int j = i + 1; j < this->orders_count; j++)
            if (this->orders[i].get_order_total_price() > this->orders[j].get_order_total_price())
                Order::swap(this->orders[i], this->orders[j]);
}

void Inventory::sort_orders_by_total_price_descending() {
    for (int i = 0; i < this->orders_count - 1; i++)
        for (int j = i + 1; j < this->orders_count; j++)
            if (this->orders[i].get_order_total_price() < this->orders[j].get_order_total_price())
                Order::swap(this->orders[i], this->orders[j]);
}

// Extragerea comenzilor in functie de ID-ul furnizorului
Order *Inventory::get_orders_by_provider_id(const char *provider_id, int &result_count) const {
    if (provider_id == nullptr) {
        result_count = 0;
        return nullptr;
    }

    const auto *to_search_orders= this->get_inventory_orders();
    result_count = 0;
    for (int i = 0; i < this->orders_count; i++)
        if (to_search_orders[i].get_order_provider_id() != nullptr && strcmp(to_search_orders[i].get_order_provider_id(), provider_id) == 0)
            result_count++;

    if (result_count == 0)
        return nullptr;

    auto *result = new Order[result_count];
    int index = 0;
    for (int i = 0; i < this->orders_count; i++)
        if (to_search_orders[i].get_order_provider_id() != nullptr && strcmp(to_search_orders[i].get_order_provider_id(), provider_id) == 0)
            result[index++] = to_search_orders[i];

    return result;
}

// Extragerea materialelor care au un stoc critic
Material *Inventory::get_critical_materials(int &result_count) const {
    result_count = 0;
    auto const *to_search_materials = this->get_inventory_materials();
    for (int i = 0; i < this->get_inventory_materials_count(); i++)
        if (to_search_materials[i].get_material_critical() >= to_search_materials[i].get_material_quantity())
            result_count++;

    if (result_count == 0)
        return nullptr;

    auto *result = new Material[result_count];
    int index = 0;
    for (int i = 0; i < this->get_inventory_materials_count(); i++)
        if (to_search_materials[i].get_material_critical() >= to_search_materials[i].get_material_quantity())
            result[index++] = to_search_materials[i];

    return result;
}

// Extragerea elementelor care fac parte dintr-o categorie anume
Material *Inventory::get_materials_by_category(const Material::Category &category, int &result_count) const {
    result_count = 0;
    auto const *to_search_materials = this->get_inventory_materials();

    for (int i = 0; i < this->materials_count; i++)
        if (to_search_materials[i].get_material_category() == category)
            result_count++;

    if (result_count == 0)
        return nullptr;

    auto *result = new Material[result_count];
    int index = 0;
    for (int i = 0; i < this->materials_count; i++)
        if (to_search_materials[i].get_material_category() == category)
            result[index++] = to_search_materials[i];

    return result;
}

// Logica de Business a inventarului
// Modificarea starii obiectelor interconectate
void Inventory::consume_material(const char *material_id, const double &quantity) {
    Material *material = this->find_material_by_id(material_id);

    if (material == nullptr)
        return;

    const double new_quantity = material->get_material_quantity() - quantity;

    if (new_quantity < 0)
        return;

    material->set_material_quantity(new_quantity);
}

// Receptionarea unei comenzi
void Inventory::receive_order(Order *order) {
    // Verificam existenta comenzii
    if (order == nullptr)
        return;

    // Verificam state-ul comenzii
    // Nu o putem procesa de 2 ori sau daca a fost anulata
    if (order->get_order_status() != Order::Status::pending)
        return;

    // Extragem informatia din obiectul order
    char **materials_id = order->get_order_materials_id();
    const double *quantities = order->get_order_quantities();
    const int order_materials_count = order->get_order_materials_count();

    if (materials_id == nullptr || quantities == nullptr || order_materials_count == 0)
        return;

    // Adaugam elementele noi care lipsesc din inventarul curent
    for (int i = 0; i < order_materials_count; i++) {
        if (this->find_material_by_id(materials_id[i]) == nullptr) {
            Material new_material(materials_id[i], "", "", 0.0, 0.0, 0.0, Material::Category::others);
            add_material(new_material);
        }
    }

    // Actualizam quantity pentru toate elementele implicate din comanda
    for (int i = 0; i < order_materials_count; i++) {
        Material *material = this->find_material_by_id(materials_id[i]);
        if (material != nullptr) {
            double new_quantity = material->get_material_quantity() + quantities[i];
            material->set_material_quantity(new_quantity);
        }
    }

    // Finalizam procesul modificand state-ul obiectului Order primit la delivered
    constexpr auto new_status = Order::Status::delivered;
    order->set_order_status(new_status);
}

// Calcularea intregii valori a inventarului
double Inventory::calculate_inventory_value() const {
    double total = 0;
    for (int i = 0; i < this->materials_count; i++)
        total += this->materials[i].get_material_quantity() * this->materials[i].get_material_unit_price();

    return total;
}

// Supraincarcarea operatorului de atribuire
// Nu mai este nevoie sa initializam pointerii la nullptr pentru ca avem garantia constructorilor ca putem sterge zonele de memorie alocate
Inventory &Inventory::operator=(const Inventory &other) {
    if (this == &other)
        return *this;

    set_inventory_id(other.get_inventory_id());
    set_inventory_name(other.get_inventory_name());
    set_inventory_address(other.get_inventory_address());
    set_inventory_phone(other.get_inventory_phone());
    set_inventory_email(other.get_inventory_email());
    set_inventory_materials(other.get_inventory_materials(), other.get_inventory_materials_count());
    set_inventory_providers(other.get_inventory_providers(), other.get_inventory_providers_count());
    set_inventory_orders(other.get_inventory_orders(), other.get_inventory_orders_count());

    return *this;
}

// Supraincarcarea operatorilor relationali
// Aplicam si aici verificari ale validitatii datelor pentru a putea folosi strcmp
bool Inventory::operator==(const Inventory &other) const {
    if ((this->id == nullptr) != (other.id == nullptr)) return false;
    if (this->id != nullptr && other.id != nullptr && strcmp(this->id, other.id) != 0) return false;

    if ((this->name == nullptr) != (other.name == nullptr)) return false;
    if (this->name != nullptr && other.name != nullptr && strcmp(this->name, other.name) != 0) return false;

    if ((this->address == nullptr) != (other.address == nullptr)) return false;
    if (this->address != nullptr && other.address != nullptr && strcmp(this->address, other.address) != 0) return false;

    if ((this->phone == nullptr) != (other.phone == nullptr)) return false;
    if (this->phone != nullptr && other.phone != nullptr && strcmp(this->phone, other.phone) != 0) return false;

    if ((this->email == nullptr) != (other.email == nullptr)) return false;
    if (this->email != nullptr && other.email != nullptr && strcmp(this->email, other.email) != 0) return false;

    if (this->materials_count != other.materials_count) return false;
    if (this->providers_count != other.providers_count) return false;
    if (this->orders_count != other.orders_count) return false;

    if ((this->materials == nullptr) != (other.materials == nullptr)) return false;
    if (this->materials != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            if (this->materials[i] != other.materials[i]) return false;

    if ((this->providers == nullptr) != (other.providers == nullptr)) return false;
    if (this->providers != nullptr)
        for (int i = 0; i < this->providers_count; i++)
            if (this->providers[i] != other.providers[i]) return false;

    if ((this->orders == nullptr) != (other.orders == nullptr)) return false;
    if (this->orders != nullptr)
        for (int i = 0; i < this->orders_count; i++)
            if (this->orders[i] != other.orders[i]) return false;

    return true;
}

bool Inventory::operator!=(const Inventory &other) const {
    return !(*this == other);
}

// Supraincarcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Inventory &inventory) {
    char inventory_id[256];
    char inventory_name[256];
    char inventory_address[256];
    char inventory_phone[256];
    char inventory_email[256];
    int inventory_materials_count;
    int inventory_providers_count;
    int inventory_orders_count;

    std::cout << "Enter inventory ID: ";
    is >> inventory_id;
    inventory.set_inventory_id(inventory_id);

    std::cout << "Enter inventory name: ";
    is >> inventory_name;
    inventory.set_inventory_name(inventory_name);

    std::cout << "Enter address: ";
    is >> inventory_address;
    inventory.set_inventory_address(inventory_address);

    std::cout << "Enter phone: ";
    is >> inventory_phone;
    inventory.set_inventory_phone(inventory_phone);

    std::cout << "Enter email: ";
    is >> inventory_email;
    inventory.set_inventory_email(inventory_email);

    // Setarea capacitatilor memoriei viitoare
    std::cout << "Enter number of materials: ";
    is >> inventory_materials_count;

    std::cout << "Enter number of providers: ";
    is >> inventory_providers_count;

    std::cout << "Enter number of orders: ";
    is >> inventory_orders_count;

    for (int i = 0; i < inventory_materials_count; i++) {
        std::cout << "\n-- Material " << i + 1 << " --\n";
        Material material;
        is >> material;
        inventory.add_material(material);
    }

    for (int i = 0; i < inventory_providers_count; i++) {
        std::cout << "\n-- Provider " << i + 1 << " --\n";
        Provider provider;
        is >> provider;
        inventory.add_provider(provider);
    }

    for (int i = 0; i < inventory_orders_count; i++) {
        std::cout << "\n-- Order " << i + 1 << " --\n";
        Order order;
        is >> order;
        inventory.add_order(order);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Inventory &inventory) {
    os << "[ " << (inventory.id ? inventory.id : "N/A") << " ] " << (inventory.name ? inventory.name : "N/A") << "\n";
    os << "  Address    : " << (inventory.address ? inventory.address : "N/A") << "\n";
    os << "  Phone      : " << (inventory.phone ? inventory.phone : "N/A") << "\n";
    os << "  Email      : " << (inventory.email ? inventory.email : "N/A") << "\n";
    os << "  Materials  : " << inventory.materials_count << "\n";
    os << "  Providers  : " << inventory.providers_count << "\n";
    os << "  Orders     : " << inventory.orders_count << "\n\n";

    return os;
}
