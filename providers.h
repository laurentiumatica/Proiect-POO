#pragma once
#include <iosfwd>

// Definim structura și comportamentul pentru clasa Provider (Furnizor)
class Provider {
public:
    // Constructorul implicit
    Provider();

    // Constructorul de copiere
    Provider(const Provider &other);

    // Constructorul cu parametri
    Provider(const char *id, const char *name, const char *phone,
             const char *email, const char *address, const char **materials_id,
             const int &materials_count, const double &discount);

    // Destructorul
    ~Provider();

    // Getters
    [[nodiscard]] char *get_provider_id() const; // Returnează un pointer către ID-ul furnizorului
    [[nodiscard]] char *get_provider_name() const; // Returnează un pointer către numele furnizorului
    [[nodiscard]] char *get_provider_phone() const; // Returnează numărul de telefon
    [[nodiscard]] char *get_provider_email() const; // Returnează adresa de email
    [[nodiscard]] char *get_provider_address() const; // Returnează adresa fizică
    [[nodiscard]] char **get_provider_materials_id() const; // Returnează lista (tabloul de pointeri) cu ID-urile materialelor
    [[nodiscard]] int get_provider_materials_count() const; // Returnează numărul de materiale din lista de mai sus
    [[nodiscard]] double get_provider_discount() const; // Returnează valoarea reducerii aplicate

    // Setters
    void set_provider_id(const char *new_id); // Curăță memoria veche și o alocă pe cea nouă pentru ID
    void set_provider_name(const char *new_name); // Gestionează memoria și setează noul nume
    void set_provider_phone(const char *new_phone); // Gestionează memoria și setează noul telefon
    void set_provider_email(const char *new_email); // Gestionează memoria și setează noul email
    void set_provider_address(const char *new_address); // Gestionează memoria și setează noua adresă
    void set_provider_materials(const char **new_materials, const int &new_materials_count); // Modifică simultan pointerul către matricea de materiale și numărul de materiale
    void set_provider_discount(const double &new_discount); // Setează o nouă valoare pentru reducere

    // Supraîncărcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Provider &provider);
    friend std::ostream &operator<<(std::ostream &os, const Provider &provider);

    // Supraîncărcarea operatorului de atribuire
    Provider &operator=(const Provider &other);

    // Supraîncărcarea operatorilor relaționali
    bool operator==(const Provider &other) const; // Returnează true dacă au atributele identice
    bool operator!=(const Provider &other) const; // Returnează true dacă cel puțin un atribut diferă

    // Interschimbă direct stările interne ale celor două obiecte
    static void swap(Provider &provider1, Provider &provider2) noexcept;

private:
    char *id; // ID-ul furnizorului
    char *name; // Numele furnizorului
    char *phone; // Numărul de telefon pentru furnizor
    char *email; // Email-ul furnizorului
    char *address; // Adresa furnizorului
    char **materials_id; // Array pentru ID-urile materialelor disponibile
    int materials_count; // Numărul de materiale furnizate de provider
    double discount; // Procentul pentru aplicarea unei reduceri
};
