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
    Inventory(std::string_view new_inventory_id, std::string_view new_inventory_name, std::string_view new_inventory_address,
              std::string_view new_inventory_phone, std::string_view new_inventory_email,
              std::span<const Material> new_inventory_materials, std::span<const Provider> new_inventory_providers,
              std::span<const Order> new_inventory_orders);

    // Destructor
    ~Inventory();

    // Getters
    [[nodiscard]] const std::string &get_inventory_id() const; // Returnează ID-ul
    [[nodiscard]] const std::string &get_inventory_name() const; // Returnează numele
    [[nodiscard]] const std::string &get_inventory_address() const; // Returnează adresa
    [[nodiscard]] const std::string &get_inventory_phone() const; // Returnează telefonul
    [[nodiscard]] const std::string &get_inventory_email() const; // Returnează email-ul
    [[nodiscard]] const std::vector<Material> &get_inventory_materials() const; // Returnează adresa de început a tabloului de materiale
    [[nodiscard]] const std::vector<Provider> &get_inventory_providers() const; // Returnează tabloul de furnizori
    [[nodiscard]] const std::vector<Order> &get_inventory_orders() const; // Returnează tabloul de comenzi
    [[nodiscard]] int get_inventory_materials_count() const; // Returnează numărul efectiv de materiale stocate în inventar
    [[nodiscard]] int get_inventory_providers_count() const; // Returnează numărul efectiv de furnizori stocați în inventar
    [[nodiscard]] int get_inventory_orders_count() const; // Returnează numărul efectiv de comenzi stocate în inventar

    // Metode care modifică starea obiectului
    void add_material(const Material &material); // Adaugă o copie a obiectului material în inventar
    void register_provider(std::span<const Provider> available_providers); // Adaugă un nou furnizor
    void place_order(); // Înregistrează o comandă nouă
    void consume_material(); // Recalculează cantitatea disponibilă a unui material după consum
    void receive_order(Order *order); // Procesează o comandă și actualizează stocurile corespunzătoare

    // Metode de căutare pe instanța curentă
    // Returnează un pointer către obiectul găsit în interiorul inventarului
    Material *find_material_by_id(std::string_view find_id);
    Provider *find_provider_by_id(std::string_view find_id);
    Order *find_order_by_id(std::string_view find_id);

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
    const std::vector<Order> get_orders_by_provider_id(std::string_view provider_id);
    const std::vector<Material> get_critical_materials();
    const std::vector<Provider> get_materials_by_category(Material::Category category);

    // Supraîncărcarea operatorului de atribuire
    Inventory &operator=(Inventory other);

    // Supraîncărcarea operatorilor relaționali.
    bool operator==(const Inventory &other) const;
    bool operator!=(const Inventory &other) const;

    // Supraîncărcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Inventory &inventory);
    friend std::ostream &operator<<(std::ostream &os, const Inventory &inventory);

    // Setters
    void set_inventory_id(std::string_view new_inventory_id);
    void set_inventory_name(std::string_view new_inventory_name);
    void set_inventory_address(std::string_view new_inventory_address);
    void set_inventory_phone(std::string_view new_inventory_phone);
    void set_inventory_email(std::string_view new_inventory_email);
    void set_inventory_materials(std::span<const Material> new_inventory_materials);
    void set_inventory_providers(std::span<const Provider> new_inventory_providers);
    void set_inventory_orders(std::span<const Order> new_inventory_orders);

private:
    std::string id; // ID-ul inventarului
    std::string name; // Numele inventarului
    std::string address; // Adresa inventarului
    std::string phone; // Numărul de telefon al inventarului
    std::string email; // Email-ul inventarului
    std::vector<Material> materials; // Array-ul de materiale al inventarului
    std::vector<Provider> providers; // Array-ul de furnizori al inventarului
    std::vector<Order> orders; // Array-ul de comenzi al inventarului

    // Functii helper
    static void validate_inventory_id(std::string_view new_inventory_id);
    static void validate_inventory_name(std::string_view new_inventory_name);
    static void validate_inventory_address(std::string_view new_inventory_address);
    static void validate_inventory_phone(std::string_view new_inventory_phone);
    static void validate_inventory_email(std::string_view new_inventory_email);
    static void validate_inventory_materials(std::span<const Material> new_inventory_materials);
    static void validate_inventory_providers(std::span<const Provider> new_inventory_providers);
    static void validate_inventory_orders(std::span<const Order> new_inventory_orders);
    static void read_string(std::string_view prompt, auto setter);
    void print_available_unregistered_providers(std::span<const Provider> available_providers);
    void print_inventory_providers() const;
    void print_inventory_materials() const;
    void print_inventory_orders() const;
};
