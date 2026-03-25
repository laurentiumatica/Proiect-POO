#include "providers.h"
#include <cstring>
#include <iostream>

// Constructorul default
Provider::Provider() {
    this->id = nullptr;
    this->name = nullptr;
    this->phone = nullptr;
    this->email = nullptr;
    this->address = nullptr;
    this->materials_id = nullptr;
    this->materials_count = 0;
    this->discount = 0;
}

// Constructorul cu parametri
Provider::Provider(const char *id, const char *name, const char *phone,
                   const char *email, const char *address,
                   const char **materials_id, const int &materials_count,
                   const double &discount) {
    this->id = new char[strlen(id) + 1];
    strcpy(this->id, id);

    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->phone = new char[strlen(phone) + 1];
    strcpy(this->phone, phone);

    this->email = new char[strlen(email) + 1];
    strcpy(this->email, email);

    this->address = new char[strlen(address) + 1];
    strcpy(this->address, address);

    this->materials_count = materials_count;
    this->discount = discount;

    this->materials_id = new char *[materials_count]; // Alocăm array-ul principal
    for (int i = 0; i < materials_count; i++) {
        this->materials_id[i] = new char[strlen(materials_id[i]) + 1]; // Alocăm fiecare linie în parte
        strcpy(this->materials_id[i], materials_id[i]);
    }
}

// Copy constructor
Provider::Provider(const Provider &other) {
    if (other.id != nullptr) {
        this->id =
                new char[strlen(other.id) + 1];
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

    if (other.address != nullptr) {
        this->address = new char[strlen(other.address) + 1];
        strcpy(this->address, other.address);
    }
    else {
        this->address = nullptr;
    }

    // Logica de deep copy pentru array-ul intern
    if (other.materials_id != nullptr) {
        this->materials_id = new char *[other.materials_count];
        for (int i = 0; i < other.materials_count; i++) {
            if (other.materials_id[i] != nullptr) {
                this->materials_id[i] = new char[strlen(other.materials_id[i]) + 1];
                strcpy(this->materials_id[i], other.materials_id[i]);
            } else {
                this->materials_id[i] = nullptr;
            }
        }
    } else {
        this->materials_id = nullptr;
    }

    this->materials_count = other.materials_count;
    this->discount = other.discount;
}

// Destructorul
Provider::~Provider() {
    delete[] this->id;
    delete[] this->name;
    delete[] this->phone;
    delete[] this->email;
    delete[] this->address;

    // Pentru array-ul bidimensional, întâi dăm delete fiecărui element
    for (int i = 0; i < this->materials_count; i++)
        delete[] this->materials_id[i];

    delete[] this->materials_id; // Apoi eliberăm structura principală
}

// Getters
char *Provider::get_provider_id() const { return this->id; }
char *Provider::get_provider_name() const { return this->name; }
char *Provider::get_provider_phone() const { return this->phone; }
char *Provider::get_provider_email() const { return this->email; }
char *Provider::get_provider_address() const { return this->address; }
char **Provider::get_provider_materials_id() const { return this->materials_id; }
int Provider::get_provider_materials_count() const { return this->materials_count; }
double Provider::get_provider_discount() const { return this->discount; }

// Setters
void Provider::set_provider_id(const char *new_id) {
    delete[] this->id;
    this->id = new char[strlen(new_id) + 1];
    strcpy(this->id, new_id);
}

void Provider::set_provider_name(const char *new_name) {
    delete[] this->name;
    this->name = new char[strlen(new_name) + 1];
    strcpy(this->name, new_name);
}

void Provider::set_provider_phone(const char *new_phone) {
    delete[] this->phone;
    this->phone = new char[strlen(new_phone) + 1];
    strcpy(this->phone, new_phone);
}

void Provider::set_provider_email(const char *new_email) {
    delete[] this->email;
    this->email = new char[strlen(new_email) + 1];
    strcpy(this->email, new_email);
}

void Provider::set_provider_address(const char *new_address) {
    delete[] this->address;
    this->address = new char[strlen(new_address) + 1];
    strcpy(this->address, new_address);
}

void Provider::set_provider_materials(const char **new_materials, const int &new_materials_count) {
    for (int i = 0; i < this->materials_count; i++)
        delete[] this->materials_id[i];
    delete[] this->materials_id;

    this->materials_count = new_materials_count;
    this->materials_id = new char *[new_materials_count];

    for (int i = 0; i < new_materials_count; i++) {
        this->materials_id[i] = new char[strlen(new_materials[i]) + 1];
        strcpy(this->materials_id[i], new_materials[i]);
    }
}

void Provider::set_provider_discount(const double &new_discount) {
    this->discount = new_discount;
}

// Supraîncărcarea operatorului de atribuire =
Provider &Provider::operator=(const Provider &other) {
    if (this == &other)
        return *this;

    delete[] this->id;
    delete[] this->name;
    delete[] this->phone;
    delete[] this->email;
    delete[] this->address;
    for (int i = 0; i < this->materials_count; i++)
        delete[] this->materials_id[i];
    delete[] this->materials_id;

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

    if (other.address != nullptr) {
        this->address = new char[strlen(other.address) + 1];
        strcpy(this->address, other.address);
    }
    else {
        this->address = nullptr;
    }

    this->materials_count = other.materials_count;
    this->discount = other.discount;

    if (other.materials_id != nullptr) {
        this->materials_id = new char *[other.materials_count];
        for (int i = 0; i < other.materials_count; i++) {
            if (other.materials_id[i] != nullptr) {
                this->materials_id[i] = new char[strlen(other.materials_id[i]) + 1];
                strcpy(this->materials_id[i], other.materials_id[i]);
            }
            else {
                this->materials_id[i] = nullptr;
            }
        }
    }
    else {
        this->materials_id = nullptr;
    }

    return *this;
}

// Supraîncărcarea operatorilor relaționali
bool Provider::operator==(const Provider &other) const {
    if (strcmp(this->id, other.id) != 0 || strcmp(this->name, other.name) != 0 ||
        strcmp(this->phone, other.phone) != 0 ||
        strcmp(this->email, other.email) != 0 ||
        strcmp(this->address, other.address) != 0 ||
        this->materials_count != other.materials_count ||
        this->discount != other.discount)
        return false;

    for (int i = 0; i < this->materials_count; i++)
        if (strcmp(this->materials_id[i], other.materials_id[i]) != 0)
            return false;

    return true;
}

// Refolosim codul deja scris pentru operatorul de inegalitate
bool Provider::operator!=(const Provider &other) const {
    return !(*this == other);
}

// Interschimbare
void Provider::swap(Provider &provider1, Provider &provider2) noexcept {
    Provider temp = provider1;
    provider1 = provider2;
    provider2 = temp;
}

// Supraîncărcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Provider &provider) {
    char provider_id[256];
    char provider_name[256];
    char provider_phone[256];
    char provider_email[256];
    char provider_address[256];
    int provider_materials_count;

    std::cout << "Enter provider ID: ";
    is >> provider_id;
    delete[] provider.id;
    provider.id = new char[strlen(provider_id) + 1];
    strcpy(provider.id, provider_id);

    std::cout << "Enter provider name: ";
    is >> provider_name;
    delete[] provider.name;
    provider.name = new char[strlen(provider_name) + 1];
    strcpy(provider.name, provider_name);

    std::cout << "Enter provider phone: ";
    is >> provider_phone;
    delete[] provider.phone;
    provider.phone = new char[strlen(provider_phone) + 1];
    strcpy(provider.phone, provider_phone);

    std::cout << "Enter provider email: ";
    is >> provider_email;
    delete[] provider.email;
    provider.email = new char[strlen(provider_email) + 1];
    strcpy(provider.email, provider_email);

    std::cout << "Enter provider address: ";
    is >> provider_address;
    delete[] provider.address;
    provider.address = new char[strlen(provider_address) + 1];
    strcpy(provider.address, provider_address);

    std::cout << "Enter discount: ";
    is >> provider.discount;

    std::cout << "Enter number of materials: ";
    is >> provider_materials_count;

    // Curățăm vechiul array de materiale
    for (int i = 0; i < provider.materials_count; i++)
        delete[] provider.materials_id[i];
    delete[] provider.materials_id;

    provider.materials_count = provider_materials_count;
    provider.materials_id = new char *[provider_materials_count];

    for (int i = 0; i < provider_materials_count; i++) {
        char material_id[256];
        std::cout << "Enter material " << i + 1 << " ID: ";
        is >> material_id;
        provider.materials_id[i] = new char[strlen(material_id) + 1];
        strcpy(provider.materials_id[i], material_id);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Provider &provider) {
    os << "[ " << provider.id << " ] " << provider.name << "\n";
    os << "  Phone      : " << provider.phone << "\n";
    os << "  Email      : " << provider.email << "\n";
    os << "  Address    : " << provider.address << "\n";
    os << "  Discount   : " << provider.discount << "%\n";
    os << "  Materials  : ";

    for (int i = 0; i < provider.materials_count; i++) {
        os << provider.materials_id[i];
        if (i < provider.materials_count - 1)
            os << ", ";
    }
    os << "\n\n";
    return os;
}