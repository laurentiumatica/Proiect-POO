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

// Pentru urmatorii constructori folosim setters pentru atribuirea valorilor deoarece implementeaza deja verificarea datelor
// De asemenea initializam pointerii la nullptr pentru a preveni stergerea memoriei de la adrese invalide

// Constructorul cu parametri
Provider::Provider(const char *id, const char *name, const char *phone,
                   const char *email, const char *address,
                   const char **materials_id, const int &materials_count,
                   const double &discount) : Provider() {
    set_provider_id(id);
    set_provider_name(name);
    set_provider_phone(phone);
    set_provider_email(email);
    set_provider_address(address);
    set_provider_materials(materials_id, materials_count);
    set_provider_discount(discount);
}

// Copy constructor
Provider::Provider(const Provider &other) : Provider() {
    set_provider_id(other.id);
    set_provider_name(other.name);
    set_provider_phone(other.phone);
    set_provider_email(other.email);
    set_provider_address(other.address);
    set_provider_materials(const_cast<const char **>(other.materials_id), other.materials_count);
    set_provider_discount(other.discount);
}

// Destructorul
Provider::~Provider() {
    delete[] this->id;
    delete[] this->name;
    delete[] this->phone;
    delete[] this->email;
    delete[] this->address;

    for (int i = 0; i < this->materials_count; i++)
        delete[] this->materials_id[i];
    delete[] this->materials_id;
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
void Provider::set_provider_discount(const double &new_provider_discount) {
    this->discount = (new_provider_discount >= 0 && new_provider_discount <= 100) ? new_provider_discount : 0;
}

void Provider::set_provider_id(const char *new_provider_id) {
    delete[] this->id;
    this->id = (new_provider_id != nullptr)
                   ? (strcpy(new char[strlen(new_provider_id) + 1], new_provider_id))
                   : nullptr;
}

void Provider::set_provider_name(const char *new_provider_name) {
    delete[] this->name;
    this->name = (new_provider_name != nullptr)
                     ? (strcpy(new char[strlen(new_provider_name) + 1], new_provider_name))
                     : nullptr;
}

void Provider::set_provider_phone(const char *new_provider_phone) {
    delete[] this->phone;
    this->phone = (new_provider_phone != nullptr)
                      ? (strcpy(new char[strlen(new_provider_phone) + 1], new_provider_phone))
                      : nullptr;
}

void Provider::set_provider_email(const char *new_provider_email) {
    delete[] this->email;
    this->email = (new_provider_email != nullptr)
                      ? (strcpy(new char[strlen(new_provider_email) + 1], new_provider_email))
                      : nullptr;
}

void Provider::set_provider_address(const char *new_provider_address) {
    delete[] this->address;
    this->address = (new_provider_address != nullptr)
                        ? (strcpy(new char[strlen(new_provider_address) + 1], new_provider_address))
                        : nullptr;
}

void Provider::set_provider_materials(const char **new_provider_materials, const int &new_provider_materials_count) {
    // Stergem memoria alocata anterior
    if (materials_id != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            delete[] this->materials_id[i];
    delete[] this->materials_id;

    // Verificam posibilitatea de copiere a noilor valori si efectuam daca se poate
    this->materials_count = (new_provider_materials_count >= 0) ? new_provider_materials_count : 0;
    if (this->materials_count > 0 && new_provider_materials != nullptr) {
        this->materials_id = new char *[this->materials_count];
        for (int i = 0; i < this->materials_count; i++)
            this->materials_id[i] = (new_provider_materials[i] != nullptr)
                                        ? (strcpy(new char[strlen(new_provider_materials[i]) + 1], new_provider_materials[i]))
                                        : nullptr;
    } else {
        // Altfel declaram inexistenta materialelor
        this->materials_id = nullptr;
        this->materials_count = 0;
    }
}

// Supraincarcarea operatorului de atribuire
// Nu mai este nevoie sa initializam pointerii la nullptr pentru ca avem garantia constructorilor ca putem sterge zonele de memorie alocate
Provider &Provider::operator=(const Provider &other) {
    if (this == &other)
        return *this;

    set_provider_id(other.id);
    set_provider_name(other.name);
    set_provider_phone(other.phone);
    set_provider_email(other.email);
    set_provider_address(other.address);
    set_provider_materials(const_cast<const char **>(other.materials_id), other.materials_count);
    set_provider_discount(other.discount);

    return *this;
}

// Supraincarcarea operatorilor relationali
// Aplicam si aici verificari ale validitatii datelor pentru a putea folosi strcmp
bool Provider::operator==(const Provider &other) const {
    if ((this->id == nullptr) != (other.id == nullptr)) return false;
    if (this->id != nullptr && other.id != nullptr && strcmp(this->id, other.id) != 0) return false;

    if ((this->name == nullptr) != (other.name == nullptr)) return false;
    if (this->name != nullptr && other.name != nullptr && strcmp(this->name, other.name) != 0) return false;

    if ((this->phone == nullptr) != (other.phone == nullptr)) return false;
    if (this->phone != nullptr && other.phone != nullptr && strcmp(this->phone, other.phone) != 0) return false;

    if ((this->email == nullptr) != (other.email == nullptr)) return false;
    if (this->email != nullptr && other.email != nullptr && strcmp(this->email, other.email) != 0) return false;

    if ((this->address == nullptr) != (other.address == nullptr)) return false;
    if (this->address != nullptr && other.address != nullptr && strcmp(this->address, other.address) != 0) return false;

    if (this->materials_count != other.materials_count) return false;
    if (this->discount != other.discount) return false;
    if ((this->materials_id == nullptr) != (other.materials_id == nullptr)) return false;
    if (this->materials_id != nullptr)
        for (int i = 0; i < this->materials_count; i++) {
            if ((this->materials_id[i] == nullptr) != (other.materials_id[i] == nullptr)) return false;
            if (this->materials_id[i] != nullptr && other.materials_id[i] != nullptr && strcmp(this->materials_id[i], other.materials_id[i]) != 0) return false;
        }

    return true;
}

// Refolosim codul deja scris pentru operatorul de inegalitate
bool Provider::operator!=(const Provider &other) const {
    return !(*this == other);
}

// Interschimbare
void Provider::swap(Provider &provider1, Provider &provider2) noexcept {
    std::swap(provider1.id, provider2.id);
    std::swap(provider1.name, provider2.name);
    std::swap(provider1.phone, provider2.phone);
    std::swap(provider1.email, provider2.email);
    std::swap(provider1.address, provider2.address);
    std::swap(provider1.materials_id, provider2.materials_id);
    std::swap(provider1.materials_count, provider2.materials_count);
    std::swap(provider1.discount, provider2.discount);
}

// Supraincarcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Provider &provider) {
    char provider_id[256];
    char provider_name[256];
    char provider_phone[256];
    char provider_email[256];
    char provider_address[256];
    double provider_discount;
    int provider_materials_count;

    std::cout << "Enter provider ID: ";
    is >> provider_id;
    provider.set_provider_id(provider_id);

    std::cout << "Enter provider name: ";
    is >> provider_name;
    provider.set_provider_name(provider_name);

    std::cout << "Enter provider phone: ";
    is >> provider_phone;
    provider.set_provider_phone(provider_phone);

    std::cout << "Enter provider email: ";
    is >> provider_email;
    provider.set_provider_email(provider_email);

    std::cout << "Enter provider address: ";
    is >> provider_address;
    provider.set_provider_address(provider_address);

    std::cout << "Enter discount: ";
    is >> provider_discount;
    provider.set_provider_discount(provider_discount);

    std::cout << "Enter number of materials: ";
    is >> provider_materials_count;

    if (provider_materials_count > 0) {
        auto **provider_materials_id = new char *[provider_materials_count];

        for (int i = 0; i < provider_materials_count; i++) {
            char provider_material_id[256];
            std::cout << "Enter material " << i + 1 << " ID: ";
            is >> provider_material_id;
            provider_materials_id[i] = new char[strlen(provider_material_id) + 1];
            strcpy(provider_materials_id[i], provider_material_id);
        }

        provider.set_provider_materials(const_cast<const char **>(provider_materials_id), provider_materials_count);

        for (int i = 0; i < provider_materials_count; i++)
            delete[] provider_materials_id[i];
        delete[] provider_materials_id;
    } else {
        provider.set_provider_materials(nullptr, 0);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Provider &provider) {
    os << "[ " << (provider.id ? provider.id : "N/A") << " ] " << (provider.name ? provider.name : "N/A") << "\n";
    os << "  Phone      : " << (provider.phone ? provider.phone : "N/A") << "\n";
    os << "  Email      : " << (provider.email ? provider.email : "N/A") << "\n";
    os << "  Address    : " << (provider.address ? provider.address : "N/A") << "\n";
    os << "  Discount   : " << provider.discount << "%\n";
    os << "  Materials  : ";

    // Verificam existenta materialelor pentru a le putea afisa
    if (provider.materials_id != nullptr && provider.materials_count > 0)
        for (int i = 0; i < provider.materials_count; i++) {
            os << (provider.materials_id[i] ? provider.materials_id[i] : "N/A");
            if (i < provider.materials_count - 1)
                os << ", ";
        }
    else
        os << "None";
    os << "\n\n";

    return os;
}
