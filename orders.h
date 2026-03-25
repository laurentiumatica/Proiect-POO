#pragma once
#include <iosfwd>

// Definim șablonul pentru clasa Order
// Orice instanță de tip Order va avea propria sa stare bazată pe aceste definiții
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
          const int &quantity_count, const double &total_price, const char *date);

    // Destructorul
    ~Order();

    // Getters
    [[nodiscard]] char *get_order_id() const; // Returnează ID-ul comenzii
    [[nodiscard]] char *get_order_provider_id() const; // Returnează ID-ul furnizorului
    [[nodiscard]] char **get_order_materials_id() const; // Returnează un array de string-uri (ID-urile materialelor)
    [[nodiscard]] double *get_order_quantities() const; // Returnează un array cu cantitățile pentru fiecare material
    [[nodiscard]] double get_order_total_price() const; // Returnează valoarea totală
    [[nodiscard]] char *get_order_date() const; // Returnează data plasării comenzii
    [[nodiscard]] Status get_order_status() const; // Returnează stadiul curent (pending, delivered etc.)
    [[nodiscard]] int get_order_materials_count() const; // Returnează numărul de materiale din comandă

    // Setters
    void set_order_id(const char *new_id);
    void set_order_provider_id(const char *new_provider_id);
    void set_order_materials_id(const char **new_materials_id, const double *new_quantities, const int &new_materials_count);
    void set_order_total_price(const double &new_total_price);
    void set_order_date(const char *new_date);
    void set_status(const Status &new_status);
    void set_order_materials_count(const int &new_materials_count);
    void set_order_status(const Order::Status &new_status);

    // Supraîncărcarea operatorilor de I/O
    friend std::ostream &operator<<(std::ostream &os, const Order &order);
    friend std::istream &operator>>(std::istream &is, Order &order);

    // Supraîncărcarea operatorului de atribuire
    Order &operator=(const Order &other);

    // Supraîncărcarea operatorilor relaționali
    bool operator==(const Order &other) const;
    bool operator!=(const Order &other) const;

    // Convertește valoarea din enum-ul Status într-un String pentru afișare
    static const char *order_status_to_string(const Status &status);

    // Interschimbare
    static void swap(Order &order1, Order &order2) noexcept;

private:
    char *id; // ID-ul comenzii
    char *provider_id; // ID-ul furnizorului
    char **materials_id; // Un array dinamic de string-uri pentru ID-urile materialelor
    int materials_count; // Numărul de materiale din comandă
    double *quantities; // Un array alocat dinamic pentru a stoca valorile cantităților
    double total_price; // Valoarea totală a comenzii
    char *date; // Data în care s-a dat comanda
    Status status; // Starea curentă a comenzii
};