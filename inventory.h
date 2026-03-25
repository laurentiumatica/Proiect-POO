#pragma once
#include "materials.h"
#include "orders.h"
#include "providers.h"

class Inventory {
public:
    // Constructor implicit
    Inventory();

    // Constructor de copiere
    Inventory(const Inventory &other);

    // Constructor cu parametri
    Inventory(const char *id, const char *name, const char *address, const char *phone, const char *email,
              const Material *materials, const Provider *providers, const Order *orders,
              const int &materials_count, const int &providers_count, const int &orders_count);

    // Destructor
    ~Inventory();

    // Getters
    [[nodiscard]] char *get_inventory_id() const; // Returnează ID-ul
    [[nodiscard]] char *get_inventory_name() const; // Returnează numele
    [[nodiscard]] char *get_inventory_address() const; // Returnează adresa
    [[nodiscard]] char *get_inventory_phone() const; // Returnează telefonul
    [[nodiscard]] char *get_inventory_email() const; // Returnează email-ul
    [[nodiscard]] Material *get_inventory_materials() const; // Returnează adresa de început a tabloului de materiale
    [[nodiscard]] Provider *get_inventory_providers() const; // Returnează tabloul de furnizori
    [[nodiscard]] Order *get_inventory_orders() const; // Returnează tabloul de comenzi
    [[nodiscard]] int get_inventory_materials_count() const; // Returnează numărul efectiv de materiale stocate în inventar
    [[nodiscard]] int get_inventory_providers_count() const; // Returnează numărul efectiv de furnizori stocați în inventar
    [[nodiscard]] int get_inventory_orders_count() const; // Returnează numărul efectiv de comenzi stocate în inventar

    // Setters
    void set_inventory_id(const char *new_inventory_id);
    void set_inventory_name(const char *new_inventory_name);
    void set_inventory_address(const char *new_inventory_address);
    void set_inventory_phone(const char *new_inventory_phone);
    void set_inventory_email(const char *new_inventory_email);
    void set_inventory_materials(const Material *new_inventory_materials, const int &new_inventory_materials_count);
    void set_inventory_providers(const Provider *new_inventory_providers, const int &new_inventory_providers_count);
    void set_inventory_orders(const Order *new_inventory_orders, const int &new_inventory_orders_count);

    // Metode care modifică starea obiectului
    void add_material(const Material &material); // Adaugă o copie a obiectului material în inventar
    void add_provider(const Provider &provider); // Adaugă un nou furnizor
    void add_order(const Order &order); // Înregistrează o comandă nouă
    void consume_material(const char *material_id, const double &quantity); // Recalculează cantitatea disponibilă a unui material după consum
    void receive_order(Order *order); // Procesează o comandă și actualizează stocurile corespunzătoare

    // Metode de căutare pe instanța curentă
    // Returnează un pointer către obiectul găsit în interiorul inventarului
    [[nodiscard]] Material *find_material_by_id(const char *find_id) const;
    [[nodiscard]] Provider *find_provider_by_id(const char *find_id) const;
    [[nodiscard]] Order *find_order_by_id(const char *find_id) const;

    // Calculează valoarea totală iterând prin toate obiectele Material din instanța curentă
    [[nodiscard]] double calculate_inventory_value() const;

    // Metode de sortare specifice instanței curente
    // Modifică ordinea elementelor în tablourile interne
    void sort_materials_by_name_ascending();
    void sort_materials_by_name_descending();
    void sort_materials_by_quantity_ascending();
    void sort_materials_by_quantity_descending();
    void sort_orders_by_total_price_ascending();
    void sort_orders_by_total_price_descending();

    // Filtre
    // Creează și returnează un nou tablou de obiecte care respectă anumite criterii
    // Variabila result_count transmisă prin referință va fi modificată pentru a reflecta dimensiunea noului tablou returnat
    [[nodiscard]] Order *get_orders_by_provider_id(const char *provider_id, int &result_count) const;
    [[nodiscard]] Material *get_critical_materials(int &result_count) const;
    [[nodiscard]] Material *get_materials_by_category(const Material::Category &category, int &result_count) const;

    // Supraîncărcarea operatorului de atribuire
    Inventory &operator=(const Inventory &other);

    // Supraîncărcarea operatorilor relaționali.
    bool operator==(const Inventory &other) const;
    bool operator!=(const Inventory &other) const;

    // Supraîncărcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Inventory &inventory);
    friend std::ostream &operator<<(std::ostream &os, const Inventory &inventory);

private:
    char *id; // ID-ul inventarului
    char *name; // Numele inventarului
    char *address; // Adresa inventarului
    char *phone; // Numărul de telefon al inventarului
    char *email; // Email-ul inventarului
    Material *materials; // Array-ul de materiale al inventarului
    Provider *providers; // Array-ul de furnizori al inventarului
    Order *orders; // Array-ul de comenzi al inventarului
    int materials_count; // Numărul efectiv de materiale din inventar
    int providers_count; // Numărul efectiv de furnizori de la care se poate comanda
    int orders_count; // Numărul efectiv de comenzi existente pentru inventar
};