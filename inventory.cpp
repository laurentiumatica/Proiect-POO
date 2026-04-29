#include "exceptions.h"
#include "inventory.h"
#include "transactions.h"
#include <regex>
#include <algorithm>
#include <iostream>

#include "utils.h"

// Constructorul default
Inventory::Inventory() = default;

// Constructorul cu parametri
Inventory::Inventory(std::string id, std::string name, std::string address, std::string phone, std::string email,
                     std::vector<Material> materials, std::vector<Provider> providers,
                     std::vector<std::unique_ptr<Transaction> > transactions)
    : id(std::move(id)), name(std::move(name)), address(std::move(address)), phone(std::move(phone)),
      email(std::move(email)),
      materials(std::move(materials)), providers(std::move(providers)), transactions(std::move(transactions)) {
    validate_inventory_id(this->id);
    validate_inventory_name(this->name);
    validate_inventory_address(this->address);
    validate_inventory_phone(this->phone);
    validate_inventory_email(this->email);
}

// Copy constructor
Inventory::Inventory(const Inventory &other) {
    id = other.id;
    name = other.name;
    address = other.address;
    phone = other.phone;
    email = other.email;
    materials = other.materials;
    providers = other.providers;
    for (auto const &other_transaction: other.transactions)
        transactions.push_back(other_transaction->clone());
}

// Destructor
Inventory::~Inventory() = default;

// Getters
const std::vector<Material> &Inventory::get_inventory_materials() const { return materials; }
const std::vector<Provider> &Inventory::get_inventory_providers() const { return providers; }
const std::vector<std::unique_ptr<Transaction> > &Inventory::get_inventory_transactions() const { return transactions; }
int Inventory::get_inventory_materials_count() const { return static_cast<int>(materials.size()); }
int Inventory::get_inventory_providers_count() const { return static_cast<int>(providers.size()); }
int Inventory::get_inventory_transactions_count() const { return static_cast<int>(transactions.size()); }

double Inventory::get_inventory_total_refunds() const {
    double total = 0;
    for (auto const &transaction: transactions) {
        auto result = dynamic_cast<const ReturnTransaction *>(transaction.get());
        if (result != nullptr)
            total += result->get_return_transaction_price();
    }
    return total;
}

double Inventory::get_inventory_total_cost() const {
    double total = 0;
    for (auto const &material: materials)
        total+=material.get_material_quantity()*material.get_material_unit_price();
    return total;
}

std::vector<PurchaseOrder> Inventory::get_purchase_orders_by_provider_id(const std::string &provider_id) const {
    std::vector<PurchaseOrder> purchase_orders;
    for (auto const &transaction: transactions) {
        auto result = dynamic_cast<const PurchaseOrder *>(transaction.get());
        if (result != nullptr && result->get_purchase_order_provider_id() == provider_id)
            purchase_orders.push_back(*result);
    }
    return purchase_orders;
}

std::vector<Material> Inventory::get_critical_materials() const {
    std::vector<Material> critical_materials;
    for (auto const &material: materials) {
        if (material.get_material_critical() >= material.get_material_quantity())
            critical_materials.push_back(material);
    }
    return critical_materials;
}

std::vector<Material> Inventory::get_materials_by_category(const Material::Category category) const {
    std::vector<Material> same_category_materials;
    for (auto const &material: materials) {
        if (material.get_material_category() == category)
            same_category_materials.push_back(material);
    }
    return same_category_materials;
}

// Setters
void Inventory::set_inventory_name(std::string set_name) {
    validate_inventory_name(set_name);
    name = std::move(set_name);
}

void Inventory::set_inventory_address(std::string set_address) {
    validate_inventory_address(set_address);
    address = std::move(set_address);
}

void Inventory::set_inventory_phone(std::string set_phone) {
    validate_inventory_phone(set_phone);
    phone = std::move(set_phone);
}

void Inventory::set_inventory_email(std::string set_email) {
    validate_inventory_email(set_email);
    email = std::move(set_email);
}

void Inventory::set_inventory_materials(std::vector<Material> set_materials) {
    validate_inventory_materials(set_materials);
    materials = std::move(set_materials);
}

// Metode care modifica starea obiectului
void Inventory::register_provider(const std::vector<Provider> &available_providers) {
    print_available_unregistered_providers(available_providers);
    read_string("Enter provider ID to register", [this, &available_providers](const std::string &s) {
        auto it = std::ranges::find_if(available_providers,
                                       [&s](const Provider &p) { return p.get_provider_id() == s; });
        if (it == available_providers.end())
            throw ResourceNotFoundException("No provider with this ID found in the available providers list");
        if (find_provider_by_id(s) != nullptr)
            throw ValidationException("Provider with this ID is already registered");

        providers.push_back(*it);
    });
}

void Inventory::place_order() {
    std::string order_id, order_date, order_provider_id;
    int order_material_count;
    read_string("Enter purchase order ID", [&order_id, this](const std::string &s) {
        validate_transaction_id(s);
        validate_transaction_uniqueness(s, transactions);
        order_id = s;
    });
    read_string("Enter purchase order date", [&order_date](const std::string &s) {
        validate_transaction_date(s);
        order_date = s;
    });
    print_selected_providers(providers);
    read_string("Enter purchase order provider ID", [&order_provider_id, this](const std::string &s) {
        validate_provider_id(s);
        if (find_provider_by_id(s) == nullptr)
            throw ResourceNotFoundException("Provider not found in registered providers");
        order_provider_id = s;
    });
    read_string("Enter number of materials to order", [&order_material_count](const std::string &s) {
        const int count = std::stoi(s);
        validate_transaction_materials_number(count);
        order_material_count = count;
    });
    std::vector<Material> available_materials = find_provider_by_id(order_provider_id)->get_provider_materials();
    std::vector<Material> order_materials;
    if (order_material_count > static_cast<int>(available_materials.size()))
        throw ValidationException("Cannot order more unique materials than the provider supplies");
    for (int i = 0; i < order_material_count; i++) {
        Material order_material;
        read_string("Enter material ID to purchase",
                    [&available_materials, &order_material, &order_materials](const std::string &s) {
                        validate_material_id(s);
                        validate_materials_uniqueness(s, order_materials);
                        auto it = std::ranges::find_if(available_materials, [&s](const Material &m) {
                            return m.get_material_id() == s;
                        });
                        if (it == available_materials.end())
                            throw ResourceNotFoundException(
                                "Material not found in provider's materials list");
                        order_material = *it;
                    });
        read_string("Enter material quantity to order", [&order_material](const std::string &s) {
            order_material.set_material_quantity(std::stod(s));
        });
        order_materials.push_back(order_material);
    }
    transactions.push_back(std::make_unique<PurchaseOrder>(order_id, order_date, order_materials, order_provider_id,
                                                           PurchaseOrder::Status::pending));
}

void Inventory::record_consumption() {
    std::string consumption_id, consumption_date, consumption_project_name, consumption_department;
    int consumption_material_count;

    read_string("Enter consumption record order ID", [&consumption_id, this](const std::string &s) {
        validate_transaction_id(s);
        validate_transaction_uniqueness(s, transactions);
        consumption_id = s;
    });
    read_string("Enter consumption record order date", [&consumption_date](const std::string &s) {
        validate_transaction_date(s);
        consumption_date = s;
    });
    read_string("Enter consumption record project name", [&consumption_project_name](const std::string &s) {
        validate_consumption_record_project_name(s);
        consumption_project_name = s;
    });
    read_string("Enter consumption record department", [&consumption_department](const std::string &s) {
        validate_consumption_record_department(s);
        consumption_department = s;
    });
    print_selected_materials(materials);
    read_string("Enter number of materials to consume", [&consumption_material_count](const std::string &s) {
        const int count = std::stoi(s);
        validate_transaction_materials_number(count);
        consumption_material_count = count;
    });
    std::vector<Material> consumption_materials;
    if (consumption_material_count > static_cast<int>(materials.size()))
        throw ValidationException("Cannot consume more unique materials than the inventory has");
    for (int i = 0; i < consumption_material_count; i++) {
        Material consumption_material;
        read_string("Enter material ID to consume", [this, &consumption_material, &consumption_materials](const std::string &s) {
            validate_material_id(s);
            validate_materials_uniqueness(s, consumption_materials);
            auto it = std::ranges::find_if(materials, [&s](const Material &m) { return m.get_material_id() == s; });
            if (it == materials.end())
                throw ResourceNotFoundException("Material not found in inventory");
            consumption_material = *it;
        });
        read_string("Enter material quantity to consume", [&consumption_material, this](const std::string &s) {
            const double consumption_quantity = std::stod(s);
            const Material *current = find_material_by_id(consumption_material.get_material_id());
            if (current && consumption_quantity > current->get_material_quantity())
                throw InsufficientStockException(
                    "Requested " + s + " but only " + std::to_string(current->get_material_quantity()) + " available");
            consumption_material.set_material_quantity(consumption_quantity);
        });
        consumption_materials.push_back(consumption_material);
    }
    transactions.push_back(std::make_unique<ConsumptionRecord>(consumption_id, consumption_date, consumption_materials,
                                                               consumption_project_name, consumption_department));
}

void Inventory::register_return() {
    std::string return_id, return_date, return_original_id, return_reason;
    int return_material_count;

    read_string("Enter return transaction ID", [&return_id, this](const std::string &s) {
        validate_transaction_id(s);
        validate_transaction_uniqueness(s, transactions);
        return_id = s;
    });
    read_string("Enter return transaction date", [&return_date](const std::string &s) {
        validate_transaction_date(s);
        return_date = s;
    });
    read_string("Enter original order ID", [&return_original_id, this](const std::string &s) {
        validate_transaction_id(s);
        if (find_transaction_by_id(s) == nullptr)
            throw ResourceNotFoundException("Original transaction with ID " + s + " not found in inventory");
        return_original_id = s;
    });
    read_string("Enter return reason", [&return_reason](const std::string &s) {
        validate_refund_transaction_reason(s);
        return_reason = s;
    });
    print_selected_materials(materials);
    read_string("Enter number of materials to return", [&return_material_count](const std::string &s) {
        const int count = std::stoi(s);
        validate_transaction_materials_number(count);
        return_material_count = count;
    });
    if (return_material_count > static_cast<int>(materials.size()))
        throw ValidationException("Cannot return more unique materials than the inventory has");
    std::vector<Material> return_materials;
    for (int i = 0; i < return_material_count; i++) {
        Material return_material;
        read_string("Enter material ID to return", [this, &return_material, &return_materials](const std::string &s) {
            validate_material_id(s);
            validate_materials_uniqueness(s, return_materials);
            auto it = std::ranges::find_if(materials, [&s](const Material &m) { return m.get_material_id() == s; });
            if (it == materials.end())
                throw ResourceNotFoundException("Material not found in inventory");
            return_material = *it;
        });
        read_string("Enter material quantity to return", [&return_material, this](const std::string &s) {
            const double return_quantity = std::stod(s);
            const Material *current = find_material_by_id(return_material.get_material_id());
            if (current && return_quantity > current->get_material_quantity())
                throw InsufficientStockException(
                    "Requested " + s + " but only " + std::to_string(current->get_material_quantity()) + " available");
            return_material.set_material_quantity(return_quantity);
        });
        return_materials.push_back(return_material);
    }
    transactions.push_back(
        std::make_unique<ReturnTransaction>(return_id, return_date, return_materials, return_original_id,
                                            return_reason));
}

void Inventory::record_adjustment() {
    std::string adjustment_id, adjustment_date, adjustment_reason;
    int adjustment_material_count;

    read_string("Enter adjustment transaction ID", [&adjustment_id, this](const std::string &s) {
        validate_transaction_id(s);
        validate_transaction_uniqueness(s, transactions);
        adjustment_id = s;
    });
    read_string("Enter adjustment transaction date", [&adjustment_date](const std::string &s) {
        validate_transaction_date(s);
        adjustment_date = s;
    });
    read_string("Enter adjustment reason", [&adjustment_reason](const std::string &s) {
        validate_adjustment_transaction_reason(s);
        adjustment_reason = s;
    });
    print_selected_materials(materials);
    read_string("Enter number of materials to adjust", [&adjustment_material_count](const std::string &s) {
        const int count = std::stoi(s);
        validate_transaction_materials_number(count);
        adjustment_material_count = count;
    });
    if (adjustment_material_count > static_cast<int>(materials.size()))
        throw ValidationException("Cannot adjust more unique materials than the inventory has");
    std::vector<Material> adjustment_materials;
    for (int i = 0; i < adjustment_material_count; i++) {
        Material adjustment_material;
        read_string("Enter material ID to adjust", [this, &adjustment_material, &adjustment_materials](const std::string &s) {
            validate_material_id(s);
            validate_materials_uniqueness(s, adjustment_materials);
            auto it=std::ranges::find_if(materials,[&s](const Material &m){return m.get_material_id() == s;});
            if (it==materials.end())
                throw ResourceNotFoundException("Material not found in inventory");
            adjustment_material=*it;
        });
        read_string("Enter corrected quantity", [&adjustment_material](const std::string &s) {
            adjustment_material.set_material_quantity(std::stod(s));
        });
        adjustment_materials.push_back(adjustment_material);
    }
    transactions.push_back(std::make_unique<AdjustmentTransaction>(adjustment_id, adjustment_date, adjustment_materials, adjustment_reason));
}

void Inventory::process_transaction() {
    print_selected_transactions(transactions);

    std::string transaction_id;
    read_string("Enter transaction ID to process", [&transaction_id](const std::string &s) {
        validate_transaction_id(s);
        transaction_id = s;
    });
    auto it = std::ranges::find_if(transactions, [&transaction_id](const std::unique_ptr<Transaction> &t) {
        return t->get_transaction_id() == transaction_id;
    });
    if (it == transactions.end())
        throw ResourceNotFoundException("Transaction with ID " + transaction_id + " not found in inventory");

    // Verificare universala, nicio tranzactie nu poate fi procesata de doua ori
    if ((*it)->is_processed())
        throw ValidationException("Transaction has already been processed");

    auto *purchase_order = dynamic_cast<PurchaseOrder *>(it->get());
    if (purchase_order) {
        if (purchase_order->get_purchase_order_status() == PurchaseOrder::Status::cancelled)
            throw ValidationException("Purchase order has been cancelled");
    }

    (*it)->apply(*this);
}

void Inventory::cancel_order() {
    print_selected_purchase_orders(transactions);

    std::string transaction_id;
    read_string("Enter transaction ID to cancel", [&transaction_id](const std::string &s) {
        validate_transaction_id(s);
        transaction_id = s;
    });
    auto it = std::ranges::find_if(transactions, [&transaction_id](const std::unique_ptr<Transaction> &t) {
        return t->get_transaction_id() == transaction_id;
    });
    if (it == transactions.end())
        throw ResourceNotFoundException("Transaction with ID " + transaction_id + " not found in inventory");

    auto *purchase_order = dynamic_cast<PurchaseOrder *>(it->get());
    if (!purchase_order)
        throw ValidationException("Only purchase orders can be cancelled");
    if (purchase_order->get_purchase_order_status() == PurchaseOrder::Status::delivered)
        throw ValidationException("Cannot cancel a delivered order");
    if (purchase_order->get_purchase_order_status() == PurchaseOrder::Status::cancelled)
        throw ValidationException("Order is already cancelled");

    purchase_order->set_purchase_order_status(PurchaseOrder::Status::cancelled);
}

Material *Inventory::find_material_by_id(const std::string &find_id) {
    auto it = std::ranges::find_if(materials, [&find_id](const Material &m) { return m.get_material_id() == find_id; });
    return it != materials.end() ? &(*it) : nullptr;
}

const Provider *Inventory::find_provider_by_id(const std::string &find_id) const {
    auto it = std::ranges::find_if(providers, [&find_id](const Provider &p) { return p.get_provider_id() == find_id; });
    return it != providers.end() ? &(*it) : nullptr;
}

const Transaction *Inventory::find_transaction_by_id(const std::string &find_id) const {
    auto it = std::ranges::find_if(transactions, [&find_id](const std::unique_ptr<Transaction> &t) {
        return t->get_transaction_id() == find_id;
    });
    return it != transactions.end() ? it->get() : nullptr;
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
    std::swap(this->transactions, other.transactions);

    return *this;
}

// Supraincarcarea operatorului de output
std::ostream &operator<<(std::ostream &os, const Inventory &inventory) {
    os << inventory.id << "  " << inventory.name << "\n";
    os << "|  Address    : " << inventory.address << "\n";
    os << "|  Phone      : " << inventory.phone << "\n";
    os << "|  Email      : " << inventory.email << "\n";
    os << "|  Materials  : " << inventory.get_inventory_materials_count() << "\n";
    os << "|  Providers  : " << inventory.get_inventory_providers_count() << "\n";
    os << "|  Orders     : " << inventory.get_inventory_transactions_count() << "\n";
    os << "|_\n\n";

    return os;
}

// Functii helper

void Inventory::print_available_unregistered_providers(const std::vector<Provider> &available_providers) const {
    std::cout << "Available unregistered providers:\n\n";
    for (const auto &provider : available_providers)
        if (find_provider_by_id(provider.get_provider_id()) == nullptr)
            std::cout << provider << "\n";
    std::cout << "\n";
}

void Inventory::print_selected_providers(const std::vector<Provider> &selected_providers) {
    std::cout << "Registered providers:\n\n";
    for (const auto &provider: selected_providers)
        std::cout << provider << "\n";
    std::cout << "\n";
}

void Inventory::print_selected_materials(const std::vector<Material> &selected_materials) {
    std::cout << "Registered materials:\n\n";
    for (const auto &material: selected_materials)
        std::cout << material << "\n";
    std::cout << "\n";
}

void Inventory::print_selected_purchase_orders(const std::vector<std::unique_ptr<Transaction>> &selected_transactions) {
    std::cout << "Registered orders:\n\n";
    for (const auto &transaction: selected_transactions) {
        const auto purchase_order = dynamic_cast<const PurchaseOrder *>(transaction.get());
        if (purchase_order != nullptr)
            std::cout << *purchase_order;
    }
    std::cout << "\n";
}

void Inventory::print_selected_transactions(const std::vector<std::unique_ptr<Transaction>> &selected_transactions) {
    std::cout << "Registered transactions:\n\n";
    for (const auto &transaction: selected_transactions)
        std::cout << *transaction << "\n";
    std::cout << "\n";
}