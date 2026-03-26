#pragma once
#include <iosfwd>

// Definim sablonul pentru clasa Order
// Orice instanta de tip Order va avea propria sa stare bazata pe aceste definitii
class Order {
public:
    // Un enum specific acestei clase pentru a gestiona starea comenzii
    enum class Status { pending, delivered, cancelled, unknown };

    // Constructorul implicit
    Order();

    // Constructorul de copiere
    Order(const Order &other);

    // Constructorul cu parametri
    Order(const char *id, const char *provider_id, const char **materials_id,
          const int &materials_count, const double *quantities,
          const double &total_price, const char *date, const Status &status);

    // Destructorul
    ~Order();

    // Getters
    // Cuvantul cheie const de la final garanteaza ca aceste metode nu vor modifica starea instantei
    [[nodiscard]] char *get_order_id() const; // Returneaza ID-ul comenzii
    [[nodiscard]] char *get_order_provider_id() const; // Returneaza ID-ul furnizorului
    [[nodiscard]] char **get_order_materials_id() const; // Returneaza un array de string-uri (ID-urile materialelor)
    [[nodiscard]] double *get_order_quantities() const; // Returneaza un array cu cantitatile pentru fiecare material
    [[nodiscard]] double get_order_total_price() const; // Returneaza valoarea totala
    [[nodiscard]] char *get_order_date() const; // Returneaza data plasarii comenzii
    [[nodiscard]] Status get_order_status() const; // Returneaza stadiul curent (pending, delivered etc.)
    [[nodiscard]] int get_order_materials_count() const; // Returneaza numarul de materiale din comanda

    // Supraincarcarea operatorilor de I/O
    friend std::ostream &operator<<(std::ostream &os, const Order &order);
    friend std::istream &operator>>(std::istream &is, Order &order);

    // Supraincarcarea operatorului de atribuire
    Order &operator=(const Order &other);

    // Supraincarcarea operatorilor relationali
    bool operator==(const Order &other) const;
    bool operator!=(const Order &other) const;

    // Convertor status la string
    static const char *order_status_to_string(const Status &status);

    // Interschimbare
    static void swap(Order &order1, Order &order2) noexcept;

    // Functii de update
    static void update_order_id(Order &order, const void *new_data);
    static void update_order_provider_id(Order &order, const void *new_data);
    static void update_order_date(Order &order, const void *new_data);
    static void update_order_total_price(Order &order, const void *new_data);
    static void update_order_status(Order &order, const void *new_data);
    static void update_order_materials(Order &order, const void *new_data);
    static void update_order(Order &order, void (*func)(Order &, const void *), const void *new_value);

private:
    char *id; // ID-ul comenzii
    char *provider_id; // ID-ul furnizorului
    char **materials_id; // Un array dinamic de string-uri pentru ID-urile materialelor
    int materials_count; // Numarul de materiale din comanda
    double *quantities; // Un array alocat dinamic pentru a stoca valorile cantitatilor
    double total_price; // Valoarea totala a comenzii
    char *date; // Data in care s-a dat comanda
    Status status; // Starea curenta a comenzii

    // Setters
    void set_order_id(const char *new_order_id);
    void set_order_provider_id(const char *new_order_provider_id);
    void set_order_materials(const char **new_order_materials, const double *new_order_quantities, const int &new_order_materials_count);
    void set_order_total_price(const double &new_order_total_price);
    void set_order_date(const char *new_order_date);
    void set_order_status(const Status &new_order_status);
};