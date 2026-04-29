#pragma once
#include "materials.h"
#include "transactions.h"
#include "providers.h"
#include <memory>
#include <algorithm>
#include <iostream>

class Inventory {
public:
    // Constructor implicit
    Inventory();

    // Constructor de copiere
    Inventory(const Inventory &other);

    // Constructor cu parametri
    Inventory(std::string id, std::string name, std::string address,
              std::string phone, std::string email,
              std::vector<Material> materials, std::vector<Provider> providers,
              std::vector<std::unique_ptr<Transaction>> transactions);

    // Destructor
    ~Inventory();

    // Setters
    void set_inventory_name(std::string set_name);
    void set_inventory_address(std::string set_address);
    void set_inventory_phone(std::string set_phone);
    void set_inventory_email(std::string set_email);
    void set_inventory_materials(std::vector<Material> set_materials);

    // Getters
    const std::string &get_inventory_id() const; // Returnează ID-ul
    const std::string &get_inventory_name() const; // Returnează numele
    const std::string &get_inventory_address() const; // Returnează adresa
    const std::string &get_inventory_phone() const; // Returnează telefonul
    const std::string &get_inventory_email() const; // Returnează email-ul
    const std::vector<Material> &get_inventory_materials() const; // Returnează adresa de început a tabloului de materiale
    const std::vector<Provider> &get_inventory_providers() const; // Returnează tabloul de furnizori
    const std::vector<std::unique_ptr<Transaction>> &get_inventory_transactions() const; // Returnează tabloul de comenzi
    int get_inventory_materials_count() const; // Returnează numărul efectiv de materiale stocate în inventar
    int get_inventory_providers_count() const; // Returnează numărul efectiv de furnizori stocați în inventar
    int get_inventory_transactions_count() const; // Returnează numărul efectiv de comenzi stocate în inventar
    std::vector<PurchaseOrder> get_purchase_orders_by_provider_id(const std::string &provider_id) const;
    std::vector<Material> get_critical_materials() const;
    std::vector<Material> get_materials_by_category(Material::Category category) const;
    double get_inventory_total_refunds() const;
    double get_inventory_total_cost() const;

    // Supraîncărcarea operatorului de atribuire
    Inventory &operator=(Inventory other);

    // Supraîncărcarea operatorului de output
    friend std::ostream &operator<<(std::ostream &os, const Inventory &inventory);

    // Metode care modifică starea obiectului
    void register_provider(const std::vector<Provider> &available_providers); // Adaugă un nou furnizor
    void place_order();
    void record_consumption();
    void register_return();
    void record_adjustment();
    void process_transaction();
    void cancel_order();

    // Metode de căutare pe instanța curentă
    Material *find_material_by_id(const std::string &find_id);
    const Provider *find_provider_by_id(const std::string &find_id) const;
    const Transaction *find_transaction_by_id(const std::string &find_id) const;

    // Metode de sortare specifice instanței curente
    // Modifică ordinea elementelor în tablourile interne
    static void display_selected_materials_by_name(std::vector<Material> selected_materials, auto lambda) {
        std::ranges::sort(selected_materials, lambda);
        print_selected_materials(selected_materials);
    }

    static void display_selected_materials_by_quantity(std::vector<Material> materials, auto lambda) {
        std::ranges::sort(materials, lambda);
        print_selected_materials(materials);
    }

    static void display_selected_purchase_orders_by_total_price(const std::vector<std::unique_ptr<Transaction>> &transactions, auto lambda) {
        std::vector<PurchaseOrder> purchase_orders;
        for (const auto &transaction : transactions) {
            const auto it = dynamic_cast<PurchaseOrder *>(transaction.get());
            if (it != nullptr)
                purchase_orders.push_back(*it);
        }
        std::ranges::sort(purchase_orders, lambda);
        for (const auto &purchase_order : purchase_orders)
            std::cout << purchase_order << '\n';
    }

    // Functii helper
    void print_available_unregistered_providers(const std::vector<Provider> &available_providers) const;
    static void print_selected_providers(const std::vector<Provider> &selected_providers);
    static void print_selected_materials(const std::vector<Material> &selected_materials);
    static void print_selected_purchase_orders(const std::vector<std::unique_ptr<Transaction>> &selected_transactions);
    static void print_selected_transactions(const std::vector<std::unique_ptr<Transaction>> &selected_transactions);


private:
    std::string id; // ID-ul inventarului
    std::string name; // Numele inventarului
    std::string address; // Adresa inventarului
    std::string phone; // Numărul de telefon al inventarului
    std::string email; // Email-ul inventarului
    std::vector<Material> materials; // Array-ul de materiale al inventarului
    std::vector<Provider> providers; // Array-ul de furnizori al inventarului
    std::vector<std::unique_ptr<Transaction>> transactions; // Array-ul de comenzi al inventarului
};