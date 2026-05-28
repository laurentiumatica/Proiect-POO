#include "exceptions.h"
#include "transactions.h"
#include <string>
#include <vector>
#include <iomanip>
#include "inventory.h"
#include "utils.h"

// =============
// CLASA DE BAZA
// =============

// Constructorul default
Transaction::Transaction() = default;

// Constructorul cu parametri
Transaction::Transaction(std::string id, std::string date, std::vector<Material> materials)
    : id(std::move(id)), date(std::move(date)), materials(std::move(materials)) {
    Utils::validate_transaction_id(this->id);
    Utils::validate_transaction_date(this->date);
    Utils::validate_transaction_materials(this->materials);
}

// Constructorul de copiere
Transaction::Transaction(const Transaction &other) : Transaction(other.id, other.date, other.materials) {
    processed = other.processed;
}

// Destructor virtual
Transaction::~Transaction() = default;

// Getters
const std::string &Transaction::get_transaction_id() const { return id; }

double Transaction::get_transaction_total_price() const {
    double total_price = 0;
    for (const Material &material: materials)
        total_price += material.get_material_quantity() * material.get_material_unit_price();
    return total_price;
}

bool Transaction::is_processed() const { return processed; }

// NVI
void Transaction::apply(Inventory &inventory) {
    do_apply(inventory);
    processed = true;
}

void Transaction::print(std::ostream &os) const {
    do_print(os);
}

// Supraincarcarea operatorului de output
std::ostream &operator<<(std::ostream &os, const Transaction &transaction) {
    transaction.print(os);
    return os;
}


// ==============
// CLASE DERIVATE
// ==============

// Constructorul default
PurchaseOrder::PurchaseOrder() : status(Status::unknown) {
}

// Constructorul cu parametri
PurchaseOrder::PurchaseOrder(std::string id, std::string date, std::vector<Material> materials, std::string provider_id,
                             const Status status)
    : Transaction(std::move(id), std::move(date), std::move(materials)), provider_id(std::move(provider_id)),
      status(status) {
    Utils::validate_provider_id(this->provider_id);
}

// Constructorul de copiere
PurchaseOrder::PurchaseOrder(const PurchaseOrder &other)
    : PurchaseOrder(other.id, other.date, other.materials, other.provider_id, other.status) {}

// Destructor
PurchaseOrder::~PurchaseOrder() = default;

// Setters
void PurchaseOrder::set_purchase_order_status(const Status set_status) {
    status=set_status;
}

// Getters
const std::string &PurchaseOrder::get_purchase_order_provider_id() const { return provider_id; }
PurchaseOrder::Status PurchaseOrder::get_purchase_order_status() const { return status; }

// Functii virtuale
std::unique_ptr<Transaction> PurchaseOrder::clone() const {
    return std::make_unique<PurchaseOrder>(*this);
}

// Functii helper
std::string PurchaseOrder::purchase_order_status_to_string(const Status status) {
    switch (status) {
        case Status::cancelled:
            return "cancelled";
        case Status::delivered:
            return "delivered";
        case Status::pending:
            return "pending";
        default:
            return "unknown";
    }
}

// NVI
void PurchaseOrder::do_apply(Inventory &inventory) {
    for (const auto &material: materials) {
        Material *found_material = inventory.find_material_by_id(material.get_material_id());
        if (found_material)
            found_material->set_material_quantity(
                found_material->get_material_quantity() + material.get_material_quantity());
        else {
            Material new_material = material;
            Utils::read_string("Enter new material critical level ("+ material.get_material_id()+")", [&new_material](const std::string &s) {
                new_material.set_material_critical(std::stod(s));
            });
            std::vector<Material> new_materials = inventory.get_inventory_materials();
            new_materials.push_back(new_material);
            inventory.set_inventory_materials(new_materials);
        }
    }
    status = Status::delivered;
}

void PurchaseOrder::do_print(std::ostream &os) const {
    os << id << " " << date << '\n';
    os << "| Provider: " << provider_id << '\n';
    os << "| Status: " << purchase_order_status_to_string(status) << '\n';
    for (const auto &material: materials)
        os << "|    - " << material.get_material_id() << " " << material.get_material_name()
           << " (Quantity: " << std::fixed << std::setprecision(2) << material.get_material_quantity() << " " << material.get_material_measure_unit()
           << ", Category: " << Material::material_category_to_string(material.get_material_category())
           << ", Unit price: " << std::fixed << std::setprecision(2) << material.get_material_unit_price() << " RON)\n";
    os << "|_\n\n";
}

// Constructorul default
ConsumptionRecord::ConsumptionRecord() = default;

// Constructor cu parametri
ConsumptionRecord::ConsumptionRecord(std::string id, std::string date, std::vector<Material> materials,
                                     std::string project_name, std::string department)
    : Transaction(std::move(id), std::move(date), std::move(materials)), project_name(std::move(project_name)),
      department(std::move(department)) {
    Utils::validate_consumption_record_project_name(this->project_name);
    Utils::validate_consumption_record_department(this->department);
}

// Constructor de copiere
ConsumptionRecord::ConsumptionRecord(const ConsumptionRecord &other)
    : ConsumptionRecord(other.id, other.date, other.materials, other.project_name, other.department) {
}

// Destructor
ConsumptionRecord::~ConsumptionRecord() = default;

// Functii virtuale
std::unique_ptr<Transaction> ConsumptionRecord::clone() const {
    return std::make_unique<ConsumptionRecord>(*this);
}

// NVI
void ConsumptionRecord::do_apply(Inventory &inventory) {
    std::vector<Material> dummy = inventory.get_inventory_materials();
    for (auto &material: materials) {
        auto found_material = std::ranges::find_if(dummy, [&material](const Material &m) {
            return material.get_material_id() == m.get_material_id();
        });
        if (found_material == dummy.end())
            throw ResourceNotFoundException(
                "Material " + material.get_material_id() + " not found in inventory for consumption");
        if (found_material->get_material_quantity() < material.get_material_quantity())
            throw InsufficientStockException(
                "Material " + material.get_material_id() + " has insufficient quantity for consumption");
        found_material->set_material_quantity(
            found_material->get_material_quantity() - material.get_material_quantity());
    }
    inventory.set_inventory_materials(dummy);
}

void ConsumptionRecord::do_print(std::ostream &os) const {
    os << id << " " << date << '\n';
    os << "| Project: " << project_name << '\n';
    os << "| Department: " << department << '\n';
    for (const auto &material: materials)
        os << "|    - " << material.get_material_id() << " " << material.get_material_name()
           << " (Quantity: " << std::fixed << std::setprecision(2) << material.get_material_quantity() << " " << material.get_material_measure_unit()
           << ", Category: " << Material::material_category_to_string(material.get_material_category())
           << ", Unit price: " << std::fixed << std::setprecision(2) << material.get_material_unit_price() << " RON)\n";
    os << "|_\n\n";
}

// Constructorul default
ReturnTransaction::ReturnTransaction() : return_amount(0) {
}

// Constructorul cu parametri
ReturnTransaction::ReturnTransaction(std::string id, std::string date, std::vector<Material> materials,
                                     std::string original_transaction_id, std::string reason)
    : Transaction(std::move(id), std::move(date), std::move(materials)),
      original_transaction_id(std::move(original_transaction_id)), reason(std::move(reason)), return_amount(0) {
    Utils::validate_transaction_id(this->original_transaction_id);
    Utils::validate_refund_transaction_reason(this->reason);
}

// Constructorul de copiere
ReturnTransaction::ReturnTransaction(const ReturnTransaction &other)
    : Transaction(other.id, other.date, other.materials), original_transaction_id(other.original_transaction_id),
      reason(other.reason), return_amount(other.return_amount) {
    Utils::validate_transaction_id(this->original_transaction_id);
    Utils::validate_refund_transaction_reason(this->reason);
}

// Destructor
ReturnTransaction::~ReturnTransaction() = default;

double ReturnTransaction::get_return_transaction_price() const { return return_amount; }

// Functii virtuale
std::unique_ptr<Transaction> ReturnTransaction::clone() const {
    return std::make_unique<ReturnTransaction>(*this);
}

// NVI
void ReturnTransaction::do_apply(Inventory &inventory) {
    return_amount = 0;
    std::vector<Material> dummy = inventory.get_inventory_materials();
    for (auto &material: materials) {
        auto found_material = std::ranges::find_if(dummy, [&material](const Material &m) {
            return material.get_material_id() == m.get_material_id();
        });
        if (found_material == dummy.end())
            throw ResourceNotFoundException(
                "Material " + material.get_material_id() + " not found in inventory for refund");
        if (found_material->get_material_quantity() < material.get_material_quantity())
            throw InsufficientStockException(
                "Material " + material.get_material_id() + " has insufficient quantity for refund");
        return_amount += material.get_material_quantity() * material.get_material_unit_price();
        found_material->set_material_quantity(
            found_material->get_material_quantity() - material.get_material_quantity());
    }
    inventory.set_inventory_materials(dummy);
}

void ReturnTransaction::do_print(std::ostream &os) const {
    os << id << " " << date << '\n';
    os << "| Original transaction id: " << original_transaction_id << '\n';
    os << "| Reason: " << reason << '\n';
    os << "| Return amount: " << std::fixed << std::setprecision(2) << return_amount << '\n';
    for (const auto &material: materials)
        os << "|    - " << material.get_material_id() << " " << material.get_material_name()
           << " (Quantity: " << std::fixed << std::setprecision(2) << material.get_material_quantity() << " " << material.get_material_measure_unit()
           << ", Category: " << Material::material_category_to_string(material.get_material_category())
           << ", Unit price: " << std::fixed << std::setprecision(2) << material.get_material_unit_price() << " RON)\n";
    os << "|_\n\n";
}

// Constructorul default
AdjustmentTransaction::AdjustmentTransaction() = default;

// Constructorul cu parametri
AdjustmentTransaction::AdjustmentTransaction(std::string id, std::string date, std::vector<Material> materials, std::string reason)
    : Transaction(std::move(id), std::move(date), std::move(materials)), reason(std::move(reason)) {
    Utils::validate_adjustment_transaction_reason(this->reason);
}

// Constructor de copiere
AdjustmentTransaction::AdjustmentTransaction(const AdjustmentTransaction &other)
    : Transaction(other.id, other.date, other.materials), reason(other.reason) {}

AdjustmentTransaction::~AdjustmentTransaction() = default;

// Functii virtuale
std::unique_ptr<Transaction> AdjustmentTransaction::clone() const {
    return std::make_unique<AdjustmentTransaction>(*this);
}

// NVI
void AdjustmentTransaction::do_apply(Inventory &inventory) {
    std::vector<Material> dummy = inventory.get_inventory_materials();
    for (auto &material: materials) {
        auto found_material = std::ranges::find_if(dummy, [&material](const Material &m) {
            return material.get_material_id() == m.get_material_id();
        });
        if (found_material == dummy.end())
            throw ResourceNotFoundException(
                "Material " + material.get_material_id() + " not found in inventory for adjustment");
        found_material->set_material_quantity(material.get_material_quantity());
    }
    inventory.set_inventory_materials(dummy);
}

void AdjustmentTransaction::do_print(std::ostream &os) const {
    os << id << " " << date << '\n';
    os << "| Reason: " << reason << '\n';
    for (const auto &material: materials)
        os << "|    - " << material.get_material_id() << " " << material.get_material_name()
           << " (Adjusted quantity: " << std::fixed << std::setprecision(2) << material.get_material_quantity() << " " << material.get_material_measure_unit()
           << ", Category: " << Material::material_category_to_string(material.get_material_category())
           << ", Unit price: " << std::fixed << std::setprecision(2) << material.get_material_unit_price() << " RON)\n";
    os << "|_\n\n";
}