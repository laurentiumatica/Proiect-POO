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
    this->materials_capacity = 0;
    this->providers_count = 0;
    this->providers_capacity = 0;
    this->orders_count = 0;
    this->orders_capacity = 0;
}

// Copy constructor
Inventory::Inventory(const Inventory &other) {
    this->materials_count = other.materials_count;
    this->providers_count = other.providers_count;
    this->orders_count = other.orders_count;
    this->materials_capacity = other.materials_capacity;
    this->providers_capacity = other.providers_capacity;
    this->orders_capacity = other.orders_capacity;

    if (other.id != nullptr) {
        this->id = new char[strlen(other.id) + 1];
        strcpy(this->id, other.id);
    }
    else {
        this->id = nullptr;
    }

    if (other.name != nullptr) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }
    else {
        this->name = nullptr;
    }

    if (other.address != nullptr) {
        this->address = new char[strlen(other.address) + 1];
        strcpy(this->address, other.address);
    }
    else {
        this->address = nullptr;
    }

    if (other.phone != nullptr) {
        this->phone = new char[strlen(other.phone) + 1];
        strcpy(this->phone, other.phone);
    }
    else {
        this->phone = nullptr;
    }

    if (other.email != nullptr) {
        this->email = new char[strlen(other.email) + 1];
        strcpy(this->email, other.email);
    }
    else {
        this->email = nullptr;
    }

    this->materials = new Material[other.materials_capacity];
    for (int i = 0; i < other.materials_count; i++)
        this->materials[i] = other.materials[i];

    this->providers = new Provider[other.providers_capacity];
    for (int i = 0; i < other.providers_count; i++)
        this->providers[i] = other.providers[i];

    this->orders = new Order[other.orders_capacity];
    for (int i = 0; i < other.orders_count; i++)
        this->orders[i] = other.orders[i];
}

// Constructorul cu parametri
Inventory::Inventory(const char *id, const char *name, const char *address,
                     const char *phone, const char *email,
                     const Material *materials, const Provider *providers,
                     const Order *orders, const int &materials_count,
                     const int &providers_count, const int &orders_count,
                     const int &materials_capacity,
                     const int &providers_capacity,
                     const int &orders_capacity) {
    this->id = new char[strlen(id) + 1];
    strcpy(this->id, id);

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->address = new char[strlen(address) + 1];
    strcpy(this->address, address);

    this->phone = new char[strlen(phone) + 1];
    strcpy(this->phone, phone);

    this->email = new char[strlen(email) + 1];
    strcpy(this->email, email);

    this->materials_count = materials_count;
    this->providers_count = providers_count;
    this->orders_count = orders_count;
    this->materials_capacity = materials_capacity;
    this->providers_capacity = providers_capacity;
    this->orders_capacity = orders_capacity;

    this->materials = new Material[materials_capacity];
    for (int i = 0; i < materials_count; i++)
        this->materials[i] = materials[i];

    this->providers = new Provider[providers_capacity];
    for (int i = 0; i < providers_count; i++)
        this->providers[i] = providers[i];

    this->orders = new Order[orders_capacity];
    for (int i = 0; i < orders_count; i++)
        this->orders[i] = orders[i];
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
int Inventory::get_inventory_materials_capacity() const { return this->materials_capacity; }
int Inventory::get_inventory_providers_capacity() const { return this->providers_capacity; }
int Inventory::get_inventory_orders_capacity() const { return this->orders_capacity; }

void Inventory::set_inventory_id(const char *new_id) {
    delete[] this->id;
    this->id = new char[strlen(new_id) + 1];
    strcpy(this->id, new_id);
}

void Inventory::set_inventory_name(const char *new_name) {
    delete[] this->name;
    this->name = new char[strlen(new_name) + 1];
    strcpy(this->name, new_name);
}

void Inventory::set_inventory_address(const char *new_address) {
    delete[] this->address;
    this->address = new char[strlen(new_address) + 1];
    strcpy(this->address, new_address);
}

void Inventory::set_inventory_phone(const char *new_phone) {
    delete[] this->phone;
    this->phone = new char[strlen(new_phone) + 1];
    strcpy(this->phone, new_phone);
}

void Inventory::set_inventory_email(const char *new_email) {
    delete[] this->email;
    this->email = new char[strlen(new_email) + 1];
    strcpy(this->email, new_email);
}

void Inventory::set_inventory_materials(const Material *new_materials, const int &new_materials_count) {
    if (new_materials_count > this->materials_capacity) {
        std::cout << "[Inventory] set_inventory_materials: new_materials_count (" << new_materials_count << ") exceeds capacity (" << this->materials_capacity << "). Operation aborted.\n";
        return;
    }

    const int old_count = this->materials_count;
    for (int i = 0; i < new_materials_count; i++)
        this->materials[i] = new_materials[i];
    for (int i = new_materials_count; i < old_count; i++)
        this->materials[i] = Material();
    this->materials_count = new_materials_count;
}

void Inventory::set_inventory_providers(const Provider *new_providers, const int &new_providers_count) {
    if (new_providers_count > this->providers_capacity) {
        std::cout << "[Inventory] set_inventory_providers: new_providers_count (" << new_providers_count << ") exceeds capacity (" << this->providers_capacity << "). Operation aborted.\n";
        return;
    }

    const int old_count = this->providers_count;
    for (int i = 0; i < new_providers_count; i++)
        this->providers[i] = new_providers[i];
    for (int i = new_providers_count; i < old_count; i++)
        this->providers[i] = Provider();
    this->providers_count = new_providers_count;
}

void Inventory::set_inventory_orders(const Order *new_orders, const int &new_orders_count) {
    if (new_orders_count > this->orders_capacity) {
        std::cout << "[Inventory] set_inventory_orders: new_orders_count (" << new_orders_count << ") exceeds capacity (" << this->orders_capacity << "). Operation aborted.\n";
        return;
    }

    const int old_count = this->orders_count;
    for (int i = 0; i < new_orders_count; i++)
        this->orders[i] = new_orders[i];
    for (int i = new_orders_count; i < old_count; i++)
        this->orders[i] = Order();
    this->orders_count = new_orders_count;
}

void Inventory::set_inventory_materials_capacity(const int &new_materials_capacity) {
    if (new_materials_capacity < this->materials_count) {
        std::cout << "[Inventory] set_inventory_materials_capacity: new capacity (" << new_materials_capacity << ") is below current count (" << this->materials_count << "). Operation aborted.\n";

        return;
    }
    this->materials_capacity = new_materials_capacity;
}

void Inventory::set_inventory_providers_capacity(const int &new_providers_capacity) {
    if (new_providers_capacity < this->providers_count) {
        std::cout << "[Inventory] set_inventory_providers_capacity: new capacity (" << new_providers_capacity << ") is below current count (" << this->providers_count << "). Operation aborted.\n";

        return;
    }
    this->providers_capacity = new_providers_capacity;
}

void Inventory::set_inventory_orders_capacity(const int &new_orders_capacity) {
    if (new_orders_capacity < this->orders_count) {
        std::cout << "[Inventory] set_inventory_orders_capacity: new capacity (" << new_orders_capacity << ") is below current count (" << this->orders_count << "). Operation aborted.\n";

        return;
    }
    this->orders_capacity = new_orders_capacity;
}

// Metode care modifică starea obiectului
bool Inventory::add_material(const Material &material) {
    if (this->materials_count >= this->materials_capacity)
        return false;

    this->materials[this->materials_count++] = material;
    return true;
}

bool Inventory::add_provider(const Provider &provider) {
    if (this->providers_count >= this->providers_capacity)
        return false;
    this->providers[this->providers_count++] = provider;
    return true;
}

bool Inventory::add_order(const Order &order) {
    if (this->orders_count >= this->orders_capacity)
        return false;
    this->orders[this->orders_count++] = order;
    return true;
}

Material *Inventory::find_material_by_id(const char *find_id) const {
    for (int i = 0; i < this->materials_count; i++)
        if (strcmp(this->materials[i].get_material_id(), find_id) == 0)
            return &this->materials[i];

    return nullptr;
}

Provider *Inventory::find_provider_by_id(const char *find_id) const {
    for (int i = 0; i < this->providers_count; i++)
        if (strcmp(this->providers[i].get_provider_id(), find_id) == 0)
            return &this->providers[i];

    return nullptr;
}

Order *Inventory::find_order_by_id(const char *find_id) const {
    for (int i = 0; i < this->orders_count; i++)
        if (strcmp(this->orders[i].get_order_id(), find_id) == 0)
            return &this->orders[i];

    return nullptr;
}

Material *Inventory::find_material_by_id(Material *materials, const int &materials_count, const char *find_id) {
    for (int i = 0; i < materials_count; i++)
        if (strcmp(materials[i].get_material_id(), find_id) == 0)
            return &materials[i];

    return nullptr;
}

Provider *Inventory::find_provider_by_id(Provider *providers, const int &providers_count, const char *find_id) {
    for (int i = 0; i < providers_count; i++)
        if (strcmp(providers[i].get_provider_id(), find_id) == 0)
            return &providers[i];

    return nullptr;
}

Order *Inventory::find_order_by_id(Order *orders, const int &orders_count, const char *find_id) {
    for (int i = 0; i < orders_count; i++)
        if (strcmp(orders[i].get_order_id(), find_id) == 0)
            return &orders[i];
    return nullptr;
}

// Logica de sortare pentru atributele instanței curente
void Inventory::sort_materials_by_name_ascending() {
    for (int i = 0; i < this->materials_count - 1; i++)
        for (int j = i + 1; j < this->materials_count; j++)
            if (strcmp(this->materials[i].get_material_name(), this->materials[j].get_material_name()) > 0)
                Material::swap(this->materials[i], this->materials[j]);
}

void Inventory::sort_materials_by_name_descending() {
    for (int i = 0; i < this->materials_count - 1; i++)
        for (int j = i + 1; j < this->materials_count; j++)
            if (strcmp(this->materials[i].get_material_name(), this->materials[j].get_material_name()) < 0)
                Material::swap(this->materials[i], this->materials[j]);
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

// Variante statice ale sortărilor
void Inventory::sort_materials_by_name_ascending(Material *materials, const int &materials_count) {
    for (int i = 0; i < materials_count - 1; i++)
        for (int j = i + 1; j < materials_count; j++)
            if (strcmp(materials[i].get_material_name(), materials[j].get_material_name()) > 0)
                Material::swap(materials[i], materials[j]);
}

void Inventory::sort_materials_by_name_descending(Material *materials, const int &materials_count) {
    for (int i = 0; i < materials_count - 1; i++)
        for (int j = i + 1; j < materials_count; j++)
            if (strcmp(materials[i].get_material_name(), materials[j].get_material_name()) < 0)
                Material::swap(materials[i], materials[j]);
}

void Inventory::sort_materials_by_quantity_ascending(
    Material *materials, const int &materials_count) {
    for (int i = 0; i < materials_count - 1; i++)
        for (int j = i + 1; j < materials_count; j++)
            if (materials[i].get_material_quantity() > materials[j].get_material_quantity())
                Material::swap(materials[i], materials[j]);
}

void Inventory::sort_materials_by_quantity_descending(
    Material *materials, const int &materials_count) {
    for (int i = 0; i < materials_count - 1; i++)
        for (int j = i + 1; j < materials_count; j++)
            if (materials[i].get_material_quantity() < materials[j].get_material_quantity())
                Material::swap(materials[i], materials[j]);
}

void Inventory::sort_orders_by_total_price_ascending(Order *orders, const int &orders_count) {
    for (int i = 0; i < orders_count - 1; i++)
        for (int j = i + 1; j < orders_count; j++)
            if (orders[i].get_order_total_price() > orders[j].get_order_total_price())
                Order::swap(orders[i], orders[j]);
}

void Inventory::sort_orders_by_total_price_descending(Order *orders, const int &orders_count) {
    for (int i = 0; i < orders_count - 1; i++)
        for (int j = i + 1; j < orders_count; j++)
            if (orders[i].get_order_total_price() < orders[j].get_order_total_price())
                Order::swap(orders[i], orders[j]);
}

// Extragerea comenzilor in functie de ID-ul furnizorului
Order *Inventory::get_orders_by_provider_id(const char *provider_id, int &result_count) const {
    result_count = 0;
    for (int i = 0; i < this->orders_count; i++)
        if (strcmp(this->orders[i].get_order_provider_id(), provider_id) == 0)
            result_count++;

    if (result_count == 0)
        return nullptr;

    auto *result = new Order[result_count];
    int index = 0;

    for (int i = 0; i < this->orders_count; i++)
        if (strcmp(this->orders[i].get_order_provider_id(), provider_id) == 0)
            result[index++] = this->orders[i];

    return result;
}

// Extragerea materialelor care au un stoc critic
Material *Inventory::get_critical_materials(int &result_count) const {
    result_count = 0;
    for (int i = 0; i < this->materials_count; i++)
        if (this->materials[i].get_material_quantity() <= this->materials[i].get_material_critical())
            result_count++;

    if (result_count == 0)
        return nullptr;

    auto *result = new Material[result_count];
    int index = 0;
    for (int i = 0; i < this->materials_count; i++)
        if (this->materials[i].get_material_quantity() <= this->materials[i].get_material_critical())
            result[index++] = this->materials[i];

    return result;
}

// Extragerea elementelor care fac parte dintr-o categorie anume
Material *Inventory::get_materials_by_category(const Material::Category &category, int &result_count) const {
    result_count = 0;
    for (int i = 0; i < this->materials_count; i++)
        if (this->materials[i].get_material_category() == category)
            result_count++;

    if (result_count == 0)
        return nullptr;

    auto *result = new Material[result_count];
    int index = 0;
    for (int i = 0; i < this->materials_count; i++)
        if (this->materials[i].get_material_category() == category)
            result[index++] = this->materials[i];

    return result;
}

// Logica de Business a inventarului
// Modificarea stării obiectelor interconectate
bool Inventory::consume_material(const char *material_id, const double &quantity) {
    Material *material = this->find_material_by_id(material_id);

    if (material == nullptr)
        return false;

    if (quantity <= 0 || material->get_material_quantity() < quantity)
        return false;

    const double new_quantity = material->get_material_quantity() - quantity;
    material->set_material_quantity(new_quantity);

    return true;
}

// Recepționarea unei comenzi
bool Inventory::receive_order(Order *order) {
    // Verificăm state-ul comenzii
    // Nu o putem procesa de 2 ori sau dacă a fost anulată
    if (order->get_order_status() != Order::Status::pending)
        return false;

    // Extragem "payload-ul din obiectul order
    char **materials_id = order->get_order_materials_id();
    const double *quantities = order->get_order_quantities();
    const int order_materials_count = order->get_order_materials_count();

    // Verificăm preventiv capacitatea memoriei
    // Dacă aducem materiale noi trebuie să ne asigurăm că tabloul de materiale din inventar nu va da pe afară
    int new_count = 0;
    for (int i = 0; i < order_materials_count; i++) {
        if (this->find_material_by_id(materials_id[i]) == nullptr) {
            new_count++;
        }
    }

    if (this->materials_count + new_count > this->materials_capacity) {
        return false; // Nu avem loc în memorie pentru a adăuga obiecte noi
    }

    // Adăugăm elementele noi care lipsesc din inventarul curent, inițializându-le cu 0 cantitatile
    for (int i = 0; i < order_materials_count; i++) {
        if (this->find_material_by_id(materials_id[i]) == nullptr) {
            Material new_material(materials_id[i], "", "", 0.0, 0.0, 0.0, Material::Category::others);
            static_cast<void>(this->add_material(new_material));
        }
    }

    // Actualizăm quantity pentru toate elementele implicate din comandă
    for (int i = 0; i < order_materials_count; i++) {
        // Luăm instanța din inventar
        Material *material = this->find_material_by_id(materials_id[i]);
        if (material != nullptr) {
            // Calculăm valoarea nouă adunând ce avem cu ce a venit
            double new_quantity = material->get_material_quantity() + quantities[i];
            // Transmitem modificarea prin setterul delegat
            material->set_material_quantity(new_quantity);
        }
    }

    // Finalizăm procesul modificând state-ul obiectului Order primit la delivered
    constexpr auto new_status = Order::Status::delivered;
    order->set_order_status(new_status);

    return true;
}

// Calcularea întregii valori a inventarului
double Inventory::calculate_inventory_value() const {
    double total = 0;
    for (int i = 0; i < this->materials_count; i++)
        total += this->materials[i].get_material_quantity() * this->materials[i].get_material_unit_price();

    return total;
}

// Supraîncărcarea operatorului de atribuire
Inventory &Inventory::operator=(const Inventory &other) {
    if (this == &other)
        return *this;

    delete[] this->id;
    delete[] this->name;
    delete[] this->address;
    delete[] this->phone;
    delete[] this->email;
    delete[] this->materials;
    delete[] this->providers;
    delete[] this->orders;

    if (other.id != nullptr) {
        this->id = new char[strlen(other.id) + 1];
        strcpy(this->id, other.id);
    }
    else {
        this->id = nullptr;
    }

    if (other.name != nullptr) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }
    else {
        this->name = nullptr;
    }

    if (other.address != nullptr) {
        this->address = new char[strlen(other.address) + 1];
        strcpy(this->address, other.address);
    }
    else {
        this->address = nullptr;
    }

    if (other.phone != nullptr) {
        this->phone = new char[strlen(other.phone) + 1];
        strcpy(this->phone, other.phone);
    }
    else {
        this->phone = nullptr;
    }

    if (other.email != nullptr) {
        this->email = new char[strlen(other.email) + 1];
        strcpy(this->email, other.email);
    }
    else {
        this->email = nullptr;
    }

    this->materials_count = other.materials_count;
    this->materials_capacity = other.materials_capacity;
    this->providers_count = other.providers_count;
    this->providers_capacity = other.providers_capacity;
    this->orders_count = other.orders_count;
    this->orders_capacity = other.orders_capacity;

    this->materials = new Material[other.materials_capacity];
    for (int i = 0; i < other.materials_count; i++)
        this->materials[i] = other.materials[i];

    this->providers = new Provider[other.providers_capacity];
    for (int i = 0; i < other.providers_count; i++)
        this->providers[i] = other.providers[i];

    this->orders = new Order[other.orders_capacity];
    for (int i = 0; i < other.orders_count; i++)
        this->orders[i] = other.orders[i];

    return *this;
}

// Supraîncărcarea operatorilor relaționali
bool Inventory::operator==(const Inventory &other) const {
    if (strcmp(this->id, other.id) != 0 ||
        strcmp(this->name, other.name) != 0 ||
        strcmp(this->address, other.address) != 0 ||
        strcmp(this->phone, other.phone) != 0 ||
        strcmp(this->email, other.email) != 0)
        return false;

    if (this->materials_count != other.materials_count ||
        this->providers_count != other.providers_count ||
        this->orders_count != other.orders_count)
        return false;

    for (int i = 0; i < this->materials_count; i++)
        if (this->materials[i] != other.materials[i])
            return false;

    for (int i = 0; i < this->providers_count; i++)
        if (this->providers[i] != other.providers[i])
            return false;

    for (int i = 0; i < this->orders_count; i++)
        if (this->orders[i] != other.orders[i])
            return false;

    return true;
}

bool Inventory::operator!=(const Inventory &other) const {
    return !(*this == other);
}

// Supraîncărcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Inventory &inventory) {
    char id[256];
    char name[256];
    char address[256];
    char phone[256];
    char email[256];
    int materials_capacity;
    int providers_capacity;
    int orders_capacity;

    std::cout << "Enter inventory ID: ";
    is >> id;
    delete[] inventory.id;
    inventory.id = new char[strlen(id) + 1];
    strcpy(inventory.id, id);

    std::cout << "Enter inventory name: ";
    is >> name;
    delete[] inventory.name;
    inventory.name = new char[strlen(name) + 1];
    strcpy(inventory.name, name);

    std::cout << "Enter address: ";
    is >> address;
    delete[] inventory.address;
    inventory.address = new char[strlen(address) + 1];
    strcpy(inventory.address, address);

    std::cout << "Enter phone: ";
    is >> phone;
    delete[] inventory.phone;
    inventory.phone = new char[strlen(phone) + 1];
    strcpy(inventory.phone, phone);

    std::cout << "Enter email: ";
    is >> email;
    delete[] inventory.email;
    inventory.email = new char[strlen(email) + 1];
    strcpy(inventory.email, email);

    // Setarea capacităților memoriei viitoare
    std::cout << "Enter materials capacity: ";
    is >> materials_capacity;

    std::cout << "Enter providers capacity: ";
    is >> providers_capacity;

    std::cout << "Enter orders capacity: ";
    is >> orders_capacity;

    delete[] inventory.materials;
    delete[] inventory.providers;
    delete[] inventory.orders;

    inventory.materials_capacity = materials_capacity;
    inventory.providers_capacity = providers_capacity;
    inventory.orders_capacity = orders_capacity;
    inventory.materials_count = 0;
    inventory.providers_count = 0;
    inventory.orders_count = 0;

    inventory.materials = new Material[materials_capacity];
    inventory.providers = new Provider[providers_capacity];
    inventory.orders = new Order[orders_capacity];

    std::cout << "Enter number of materials: ";
    int materials_count;
    is >> materials_count;
    for (int i = 0; i < materials_count; i++) {
        std::cout << "\n-- Material " << i + 1 << " --\n";
        Material material;
        is >> material;
        if (!inventory.add_material(material))
            std::cout << "Warning: materials capacity full, material not added.\n";
    }

    std::cout << "\nEnter number of providers: ";
    int providers_count;
    is >> providers_count;
    for (int i = 0; i < providers_count; i++) {
        std::cout << "\n-- Provider " << i + 1 << " --\n";
        Provider provider;
        is >> provider;
        if (!inventory.add_provider(provider))
            std::cout << "Warning: providers capacity full, provider not added.\n";
    }

    std::cout << "\nEnter number of orders: ";
    int orders_count;
    is >> orders_count;
    for (int i = 0; i < orders_count; i++) {
        std::cout << "\n-- Order " << i + 1 << " --\n";
        Order order;
        is >> order;
        if (!inventory.add_order(order))
            std::cout << "Warning: orders capacity full, order not added.\n";
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Inventory &inventory) {
    os << "[ " << inventory.id << " ] " << inventory.name << "\n";
    os << "  Address    : " << inventory.address << "\n";
    os << "  Phone      : " << inventory.phone << "\n";
    os << "  Email      : " << inventory.email << "\n";
    os << "  Materials  : " << inventory.materials_count << " / " << inventory.materials_capacity << "\n";
    os << "  Providers  : " << inventory.providers_count << " / " << inventory.providers_capacity << "\n";
    os << "  Orders     : " << inventory.orders_count << " / " << inventory.orders_capacity << "\n\n";

    return os;
}