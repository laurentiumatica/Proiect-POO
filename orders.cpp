#include "orders.h"
#include <cstring>
#include <iostream>

// Constructorul default
Order::Order() {
    this->id = nullptr;
    this->provider_id = nullptr;
    this->materials_id = nullptr;
    this->materials_count = 0;
    this->quantities = nullptr;
    this->total_price = 0;
    this->date = nullptr;
    this->status = Status::pending;
}

// Constructorul cu parametri
Order::Order(const char *id, const char *provider_id, const char **materials_id,
             const int &materials_count, const double *quantities,
             const int &quantity_count, const double &total_price,
             const char *date) {
    this->id = new char[strlen(id) + 1];
    strcpy(this->id, id);

    this->provider_id = new char[strlen(provider_id) + 1];
    strcpy(this->provider_id, provider_id);

    this->date = new char[strlen(date) + 1];
    strcpy(this->date, date);

    this->materials_count = materials_count;
    this->total_price = total_price;
    this->status = Status::pending;

    this->materials_id = new char *[quantity_count];
    this->quantities = new double[quantity_count];

    for (int i = 0; i < quantity_count; i++) {
        this->materials_id[i] = new char[strlen(materials_id[i]) + 1];
        strcpy(this->materials_id[i], materials_id[i]);
        this->quantities[i] = quantities[i];
    }
}

// Copy constructor
Order::Order(const Order &other) {
    if (other.id != nullptr) {
        this->id = new char[strlen(other.id) + 1];
        strcpy(this->id, other.id);
    }
    else {
        this->id = nullptr;
    }

    if (other.provider_id != nullptr) {
        this->provider_id = new char[strlen(other.provider_id) + 1];
        strcpy(this->provider_id, other.provider_id);
    }
    else {
        this->provider_id = nullptr;
    }

    if (other.date != nullptr) {
        this->date = new char[strlen(other.date) + 1];
        strcpy(this->date, other.date);
    }
    else {
        this->date = nullptr;
    }

    if (other.materials_id != nullptr) {
        this->materials_id = new char *[other.materials_count];
        this->quantities = new double[other.materials_count];
        for (int i = 0; i < other.materials_count; i++) {
            if (other.materials_id[i] != nullptr) {
                this->materials_id[i] = new char[strlen(other.materials_id[i]) + 1];
                strcpy(this->materials_id[i], other.materials_id[i]);
            }
            else {
                this->materials_id[i] = nullptr;
            }
            this->quantities[i] = other.quantities[i];
        }
    }
    else {
        this->materials_id = nullptr;
        this->quantities = nullptr;
    }

    this->materials_count = other.materials_count;
    this->total_price = other.total_price;
    this->status = other.status;
}

// Destructorul
Order::~Order() {
    delete[] this->id;
    delete[] this->provider_id;
    delete[] this->date;

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

// Setters private
void Order::set_order_id(const char *new_id) {
    delete[] this->id;
    this->id = new char[strlen(new_id) + 1];
    strcpy(this->id, new_id);
}

void Order::set_order_provider_id(const char *new_provider_id) {
    delete[] this->provider_id;
    this->provider_id = new char[strlen(new_provider_id) + 1];
    strcpy(this->provider_id, new_provider_id);
}

void Order::set_order_materials_id(const char **new_materials_id, const double *new_quantities, const int &new_materials_count) {
    for (int i = 0; i < this->materials_count; i++)
        delete[] this->materials_id[i];
    delete[] this->materials_id;

    this->materials_count = new_materials_count;
    this->materials_id = new char *[new_materials_count];
    for (int i = 0; i < new_materials_count; i++) {
        this->materials_id[i] = new char[strlen(new_materials_id[i]) + 1];
        strcpy(this->materials_id[i], new_materials_id[i]);
    }

    delete[] this->quantities;

    this->quantities = new double[new_materials_count];
    for (int i = 0; i < new_materials_count; i++)
        this->quantities[i] = new_quantities[i];
}

void Order::set_order_total_price(const double &new_total_price) {
    this->total_price = new_total_price;
}

void Order::set_order_date(const char *new_date) {
    delete[] this->date;
    this->date = new char[strlen(new_date) + 1];
    strcpy(this->date, new_date);
}

void Order::set_status(const Status &new_status) {
    this->status = new_status;
}

void Order::set_order_materials_count(const int &new_materials_count) {
    this->materials_count = new_materials_count;
}

void Order::set_order_status(const Order::Status &new_status) {
    this->status = new_status;
}

// Overloading la operatorul de atribuire
Order &Order::operator=(const Order &other) {
    if (this == &other)
        return *this;

    delete[] this->id;
    delete[] this->provider_id;
    delete[] this->date;
    for (int i = 0; i < this->materials_count; i++)
        delete[] this->materials_id[i];
    delete[] this->materials_id;
    delete[] this->quantities;

    if (other.id != nullptr) {
        this->id = new char[strlen(other.id) + 1];
        strcpy(this->id, other.id);
    }
    else {
        this->id = nullptr;
    }

    if (other.provider_id != nullptr) {
        this->provider_id = new char[strlen(other.provider_id) + 1];
        strcpy(this->provider_id, other.provider_id);
    }
    else {
        this->provider_id = nullptr;
    }

    if (other.date != nullptr) {
        this->date = new char[strlen(other.date) + 1];
        strcpy(this->date, other.date);
    }
    else {
        this->date = nullptr;
    }

    this->materials_count = other.materials_count;
    this->total_price = other.total_price;
    this->status = other.status;

    if (other.materials_id != nullptr) {
        this->materials_id = new char *[other.materials_count];
        this->quantities = new double[other.materials_count];
        for (int i = 0; i < other.materials_count; i++) {
            if (other.materials_id[i] != nullptr) {
                this->materials_id[i] = new char[strlen(other.materials_id[i]) + 1];
                strcpy(this->materials_id[i], other.materials_id[i]);
            }
            else {
                this->materials_id[i] = nullptr;
            }
            this->quantities[i] = other.quantities[i];
        }
    } else {
        this->materials_id = nullptr;
        this->quantities = nullptr;
    }

    return *this;
}

// Supraîncărcare operatori relaționali
bool Order::operator==(const Order &other) const {
    if (strcmp(this->id, other.id) != 0 ||
        strcmp(this->provider_id, other.provider_id) != 0 ||
        strcmp(this->date, other.date) != 0 ||
        this->materials_count != other.materials_count ||
        this->total_price != other.total_price || this->status != other.status)
        return false;

    for (int i = 0; i < this->materials_count; i++)
        if (strcmp(this->materials_id[i], other.materials_id[i]) != 0 ||
            this->quantities[i] != other.quantities[i])
            return false;

    return true;
}

bool Order::operator!=(const Order &other) const {
    return !(*this == other);
}

// Interschimbare
void Order::swap(Order &order1, Order &order2) noexcept {
    const Order temp = order1;
    order1 = order2;
    order2 = temp;
}

// Supraîncărcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Order &order) {
    char id[256];
    char provider_id[256];
    char date[256];
    int materials_count;
    int status;

    std::cout << "Enter order ID: ";
    is >> id;
    delete[] order.id;
    order.id = new char[strlen(id) + 1];
    strcpy(order.id, id);

    std::cout << "Enter provider ID: ";
    is >> provider_id;
    delete[] order.provider_id;
    order.provider_id = new char[strlen(provider_id) + 1];
    strcpy(order.provider_id, provider_id);

    std::cout << "Enter date (DD-MM-YYYY): ";
    is >> date;
    delete[] order.date;
    order.date = new char[strlen(date) + 1];
    strcpy(order.date, date);

    std::cout << "Enter total price: ";
    is >> order.total_price;

    std::cout << "Enter status:\n"
            << "  0 - pending\n"
            << "  1 - delivered\n"
            << "  2 - cancelled\n"
            << ": ";
    is >> status;
    switch (status) {
        case 1:
            order.status = Order::Status::delivered;
            break;
        case 2:
            order.status = Order::Status::cancelled;
            break;
        default:
            order.status = Order::Status::pending;
            break;
    }

    std::cout << "Enter number of materials: ";
    is >> materials_count;

    for (int i = 0; i < order.materials_count; i++)
        delete[] order.materials_id[i];
    delete[] order.materials_id;
    delete[] order.quantities;

    order.materials_count = materials_count;
    order.materials_id = new char *[materials_count];
    order.quantities = new double[materials_count];

    for (int i = 0; i < materials_count; i++) {
        char material_id[256];
        std::cout << "Enter material " << i + 1 << " ID: ";
        is >> material_id;
        order.materials_id[i] = new char[strlen(material_id) + 1];
        strcpy(order.materials_id[i], material_id);

        std::cout << "Enter material " << i + 1 << " quantity: ";
        is >> order.quantities[i];
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Order &order) {
    os << "[ " << order.id << " ] " << order.date << "\n";
    os << "  Provider    : " << order.provider_id << "\n";
    os << "  Status      : " << Order::order_status_to_string(order.status) << "\n";
    os << "  Total price : " << order.total_price << " RON\n";
    os << "  Materials   :\n";

    for (int i = 0; i < order.materials_count; i++)
        os << "    - " << order.materials_id[i] << " x " << order.quantities[i] << "\n";
    os << "\n";
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
