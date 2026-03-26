#include "orders.h"
#include <cstring>
#include <iostream>

// Constructorul default
Order::Order() {
    this->id = nullptr;
    this->provider_id = nullptr;
    this->materials_id = nullptr;
    this->quantities = nullptr;
    this->date = nullptr;
    this->materials_count = 0;
    this->total_price = 0;
    this->status = Status::pending;
}

// Constructorul cu parametri
Order::Order(const char *id, const char *provider_id, const char **materials_id,
             const int &materials_count, const double *quantities,
             const double &total_price, const char *date, const Status &status) : Order() {
    set_order_id(id);
    set_order_provider_id(provider_id);
    set_order_materials(materials_id, quantities, materials_count);
    set_order_total_price(total_price);
    set_order_date(date);
    set_order_status(status);
}

// Copy constructor
Order::Order(const Order &other) : Order() {
    set_order_id(other.id);
    set_order_provider_id(other.provider_id);
    set_order_date(other.date);
    set_order_total_price(other.total_price);
    set_order_materials(const_cast<const char **>(other.materials_id), other.quantities, other.materials_count);
    set_order_status(other.status);
}

// Destructorul
Order::~Order() {
    delete[] this->id;
    delete[] this->provider_id;
    delete[] this->date;

    if (this->materials_id != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            delete[] this->materials_id[i];

    delete[] this->materials_id;
    delete[] this->quantities;
}

// Getters
char *Order::get_order_id() const { return this->id; }
char *Order::get_order_provider_id() const { return this->provider_id; }
char **Order::get_order_materials_id() const { return this->materials_id; }
double *Order::get_order_quantities() const { return this->quantities; }
double Order::get_order_total_price() const { return this->total_price; }
char *Order::get_order_date() const { return this->date; }
Order::Status Order::get_order_status() const { return this->status; }
int Order::get_order_materials_count() const { return this->materials_count; }

// Setters
void Order::set_order_status(const Status &new_order_status) {
    this->status = new_order_status;
}

void Order::set_order_total_price(const double &new_order_total_price) {
    this->total_price = new_order_total_price >= 0 ? new_order_total_price : 0;
}

void Order::set_order_id(const char *new_order_id) {
    delete[] this->id;
    this->id = (new_order_id != nullptr) ? strcpy(new char[strlen(new_order_id) + 1], new_order_id) : nullptr;
}

void Order::set_order_provider_id(const char *new_order_provider_id) {
    delete[] this->provider_id;
    this->provider_id = (new_order_provider_id != nullptr) ? strcpy(new char[strlen(new_order_provider_id) + 1], new_order_provider_id) : nullptr;
}

void Order::set_order_date(const char *new_order_date) {
    delete[] this->date;
    this->date = (new_order_date != nullptr) ? strcpy(new char[strlen(new_order_date) + 1], new_order_date) : nullptr;
}

void Order::set_order_materials(const char **new_order_materials, const double *new_order_quantities, const int &new_order_materials_count) {
    // Stergem memoria alocata anterior
    if (materials_id != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            delete[] this->materials_id[i];
    delete[] this->materials_id;
    delete[] this->quantities;

    // Verificam posibilitatea de copiere a noilor valori si efectuam daca se poate
    this->materials_count = (new_order_materials_count >= 0) ? new_order_materials_count : 0;
    if (this->materials_count > 0 && new_order_materials != nullptr && new_order_quantities != nullptr) {
        this->materials_id = new char *[this->materials_count];
        this->quantities = new double[this->materials_count];
        for (int i = 0; i < this->materials_count; i++) {
            this->materials_id[i] = (new_order_materials[i] != nullptr)
                                        ? (strcpy(new char[strlen(new_order_materials[i]) + 1], new_order_materials[i]))
                                        : nullptr;
            this->quantities[i] = new_order_quantities[i] >= 0 ? new_order_quantities[i] : 0;
        }
    } else {
        // Altfel declaram inexistenta materialelor
        this->materials_id = nullptr;
        this->quantities = nullptr;
        this->materials_count = 0;
    }
}

void Order::update_order_id(Order &order, const void *new_data) {
    order.set_order_id(static_cast<const char *>(new_data));
}

void Order::update_order_provider_id(Order &order, const void *new_data) {
    order.set_order_provider_id(static_cast<const char *>(new_data));
}

void Order::update_order_date(Order &order, const void *new_data) {
    order.set_order_date(static_cast<const char *>(new_data));
}

void Order::update_order_total_price(Order &order, const void *new_data) {
    order.set_order_total_price(*static_cast<const double *>(new_data));
}

void Order::update_order_status(Order &order, const void *new_data) {
    order.set_order_status(*static_cast<const Status *>(new_data));
}

struct OrderUpdate {
    const char **new_materials_id;
    const double *new_quantities;
    int new_materials_count;
};


void Order::update_order_materials(Order &order, const void *new_data) {
    const auto *u = static_cast<const OrderUpdate *>(new_data);
    order.set_order_materials(u->new_materials_id, u->new_quantities , u->new_materials_count);
}

// Functie generala de update
void Order::update_order(Order &order, void (*func)(Order &, const void *), const void *new_value) {
    if (func == nullptr)
        return;
    func(order, new_value);
}

// Supraincarcarea operatorului de atribuire
// Nu mai este nevoie sa initializam pointerii la nullptr pentru ca avem garantia constructorilor ca putem sterge zonele de memorie alocate
Order &Order::operator=(const Order &other) {
    if (this == &other)
        return *this;

    set_order_id(other.id);
    set_order_provider_id(other.provider_id);
    set_order_date(other.date);
    set_order_total_price(other.total_price);
    set_order_status(other.status);
    set_order_materials(const_cast<const char **>(other.materials_id), other.quantities, other.materials_count);

    return *this;
}

// Supraincarcare operatori relationali
// Aplicam si aici verificari ale validitatii datelor pentru a putea folosi strcmp
bool Order::operator==(const Order &other) const {
    if ((this->id == nullptr) != (other.id == nullptr)) return false;
    if (this->id != nullptr && other.id != nullptr && strcmp(this->id, other.id) != 0) return false;

    if ((this->provider_id == nullptr) != (other.provider_id == nullptr)) return false;
    if (this->provider_id != nullptr && other.provider_id != nullptr && strcmp(this->provider_id, other.provider_id) != 0) return false;

    if ((this->date == nullptr) != (other.date == nullptr)) return false;
    if (this->date != nullptr && other.date != nullptr && strcmp(this->date, other.date) != 0) return false;

    if (this->materials_count != other.materials_count ||
        this->total_price != other.total_price ||
        this->status != other.status)
        return false;

    if ((this->materials_id == nullptr) != (other.materials_id == nullptr)) return false;
    if ((this->quantities == nullptr) != (other.quantities == nullptr)) return false;

    if (this->materials_id != nullptr && this->quantities != nullptr &&
        other.materials_id != nullptr && other.quantities != nullptr)
        for (int i = 0; i < this->materials_count; i++) {
            if ((this->materials_id[i] == nullptr) != (other.materials_id[i] == nullptr)) return false;
            if (this->materials_id[i] != nullptr && other.materials_id[i] != nullptr && strcmp(this->materials_id[i], other.materials_id[i]) != 0) return false;
            if (this->quantities[i] != other.quantities[i]) return false;
        }

    return true;
}

bool Order::operator!=(const Order &other) const {
    return !(*this == other);
}

// Interschimbare
void Order::swap(Order &order1, Order &order2) noexcept {
    std::swap(order1.id, order2.id);
    std::swap(order1.provider_id, order2.provider_id);
    std::swap(order1.materials_id, order2.materials_id);
    std::swap(order1.materials_count, order2.materials_count);
    std::swap(order1.quantities, order2.quantities);
    std::swap(order1.total_price, order2.total_price);
    std::swap(order1.date, order2.date);
    std::swap(order1.status, order2.status);
}

// Supraincarcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Order &order) {
    char order_id[256];
    char provider_id[256];
    char order_date[256];
    int order_materials_count;
    int order_status;
    double order_total_price;

    std::cout << "Enter order ID: ";
    is >> order_id;
    order.set_order_id(order_id);

    std::cout << "Enter provider ID: ";
    is >> provider_id;
    order.set_order_provider_id(provider_id);

    std::cout << "Enter date (DD-MM-YYYY): ";
    is >> order_date;
    order.set_order_date(order_date);

    std::cout << "Enter total price: ";
    is >> order_total_price;
    order.set_order_total_price(order_total_price);

    std::cout << "Enter status (0: pending, 1: delivered, 2: cancelled, 3: unknown): ";
    is >> order_status;
    order_status = (order_status >= 0 && order_status <= 3) ? order_status : 3;
    order.set_order_status(static_cast<Order::Status>(order_status));

    std::cout << "Enter number of materials: ";
    is >> order_materials_count;

    if (order_materials_count > 0) {
        auto **order_materials_id = new char *[order_materials_count];
        auto *order_quantities = new double[order_materials_count];

        for (int i = 0; i < order_materials_count; i++) {
            char order_material_id[256];

            std::cout << "Enter material " << i + 1 << " ID: ";
            is >> order_material_id;

            order_materials_id[i] = new char[strlen(order_material_id) + 1];
            strcpy(order_materials_id[i], order_material_id);

            std::cout << "Enter material " << i + 1 << " quantity: ";
            is >> order_quantities[i];
        }

        order.set_order_materials(const_cast<const char **>(order_materials_id), order_quantities, order_materials_count);

        for (int i = 0; i < order_materials_count; i++)
            delete[] order_materials_id[i];
        delete[] order_materials_id;
        delete[] order_quantities;
    } else {
        order.set_order_materials(nullptr, nullptr, 0);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Order &order) {
    os << "[ " << (order.id ? order.id : "N/A") << " ] " << (order.date ? order.date : "N/A") << "\n";
    os << "  Provider    : " << (order.provider_id ? order.provider_id : "N/A") << "\n";
    os << "  Status      : " << Order::order_status_to_string(order.status) << "\n";
    os << "  Total price : " << order.total_price << " RON\n";
    os << "  Materials   : ";

    // Verificam existenta materialelor pentru a le putea afisa
    if (order.materials_id != nullptr && order.quantities != nullptr && order.materials_count > 0)
        for (int i = 0; i < order.materials_count; i++) {
            os << (order.materials_id[i] ? order.materials_id[i] : "N/A") << " x " << order.quantities[i];
            if (i < order.materials_count - 1)
                os << ", ";
        }
    else
        os << "None";
    os << "\n\n";
    return os;
}

// Convertor status la string
const char *Order::order_status_to_string(const Status &status) {
    switch (status) {
        case Status::pending:
            return "pending";
        case Status::delivered:
            return "delivered";
        case Status::cancelled:
            return "cancelled";
        default:
            return "unknown";
    }
}