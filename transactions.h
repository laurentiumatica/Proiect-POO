#pragma once
#include "materials.h"
#include <string>
#include <vector>
#include <memory>

class Inventory;

// Clasa de baza
class Transaction {
protected:
    std::string id;
    std::string date;
    std::vector<Material> materials;
    bool processed = false; // Flag pentru a preveni procesarea multipla

    Transaction();

    Transaction(std::string id, std::string date, std::vector<Material> materials);

    Transaction(const Transaction &other);

    // Operator de atribuire explicit (previne avertismentul deprecated-copy)
    Transaction &operator=(const Transaction &other) = default;

    // Functii pur virtuale
    virtual void do_apply(Inventory &inventory) = 0;
    virtual void do_print(std::ostream &os) const = 0;

public:
    virtual ~Transaction();

    // NVI
    void apply(Inventory &inventory);
    void print(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Transaction &transaction);

    // Functii virtuale
    virtual std::unique_ptr<Transaction> clone() const = 0;

    // Getters
    const std::string &get_transaction_id() const;
    const std::string &get_transaction_date() const;
    const std::vector<Material> &get_transaction_materials() const;
    double get_transaction_total_price() const;
    bool is_processed() const;
};

// Clase derivate
class PurchaseOrder : public Transaction {
public:
    enum class Status { pending, delivered, cancelled, unknown};

    // Constructor default
    PurchaseOrder();

    // Constructor cu parametri
    PurchaseOrder(std::string id, std::string date, std::vector<Material> materials, std::string provider_id, Status status);

    // Constructor de copiere
    PurchaseOrder(const PurchaseOrder &other);

    // Destructor
    ~PurchaseOrder() override;

    // Setters
    void set_purchase_order_status(Status set_status);

    // Getters
    const std::string &get_purchase_order_provider_id() const;
    Status get_purchase_order_status() const;

    // Functii virtuale
    std::unique_ptr<Transaction> clone() const override;

    // Functii helper
    static std::string purchase_order_status_to_string(Status status) ;

private:
    std::string provider_id;
    Status status;

    // NVI
    void do_apply(Inventory &inventory) override;
    void do_print(std::ostream &os) const override;
};

class ConsumptionRecord : public Transaction {
public:
    // Constructor default
    ConsumptionRecord();

    // Constructorul cu parametri
    ConsumptionRecord(std::string id, std::string date, std::vector<Material> materials, std::string project_name, std::string department);

    // Constructorul de copiere
    ConsumptionRecord(const ConsumptionRecord &other);

    // Destructor
    ~ConsumptionRecord() override;

    // Getters
    const std::string &get_consumption_record_project_name() const;
    const std::string &get_consumption_record_department() const;

    // Functii virtuale
    std::unique_ptr<Transaction> clone() const override;

private:
    std::string project_name;
    std::string department;

    // NVI
    void do_apply(Inventory &inventory) override;
    void do_print(std::ostream &os) const override;
};

class ReturnTransaction : public Transaction {
public:
    // Constructor default
    ReturnTransaction();

    // Constructor cu parametri
    ReturnTransaction(std::string id, std::string date, std::vector<Material> materials, std::string original_transaction_id, std::string reason);

    // Constructor de copiere
    ReturnTransaction(const ReturnTransaction &other);

    // Destructor
    ~ReturnTransaction() override;

    // Getters
    const std::string &get_return_transaction_original_transaction_id() const;
    const std::string &get_return_transaction_reason() const;
    double get_return_transaction_price() const;

    // Functii virtuale
    std::unique_ptr<Transaction> clone() const override;

private:
    std::string original_transaction_id;
    std::string reason;
    double return_amount;

    // NVI
    void do_apply(Inventory &inventory) override;
    void do_print(std::ostream &os) const override;
};

class AdjustmentTransaction : public Transaction {
public:
    // Constructorul default
    AdjustmentTransaction();

    // Constructorul cu parametri
    AdjustmentTransaction(std::string id, std::string date, std::vector<Material> materials, std::string reason);

    // Constructorul de copiere
    AdjustmentTransaction(const AdjustmentTransaction &other);

    // Destructor
    ~AdjustmentTransaction() override;

    // Getters
    const std::string &get_adjustment_transaction_reason() const;

    // Functii virtuale
    std::unique_ptr<Transaction> clone() const override;

private:
    std::string reason;

    // NVI
    void do_apply(Inventory &inventory) override;
    void do_print(std::ostream &os) const override;
};