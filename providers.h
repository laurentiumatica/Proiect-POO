#pragma once
#include <iosfwd>

// Definim structura si comportamentul pentru clasa Provider (Furnizor)
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
    [[nodiscard]] char *get_provider_id() const; // Returneaza un pointer catre ID-ul furnizorului
    [[nodiscard]] char *get_provider_name() const; // Returneaza un pointer catre numele furnizorului
    [[nodiscard]] char *get_provider_phone() const; // Returneaza numarul de telefon
    [[nodiscard]] char *get_provider_email() const; // Returneaza adresa de email
    [[nodiscard]] char *get_provider_address() const; // Returneaza adresa fizica
    [[nodiscard]] char **get_provider_materials_id() const; // Returneaza lista (tabloul de pointeri) cu ID-urile materialelor
    [[nodiscard]] int get_provider_materials_count() const; // Returneaza numarul de materiale din lista de mai sus
    [[nodiscard]] double get_provider_discount() const; // Returneaza valoarea reducerii aplicate

    // Setters
    void set_provider_id(const char *new_provider_id); // Curata memoria veche si o aloca pe cea noua pentru ID
    void set_provider_name(const char *new_provider_name); // Gestioneaza memoria si seteaza noul nume
    void set_provider_phone(const char *new_provider_phone); // Gestioneaza memoria si seteaza noul telefon
    void set_provider_email(const char *new_provider_email); // Gestioneaza memoria si seteaza noul email
    void set_provider_address(const char *new_provider_address); // Gestioneaza memoria si seteaza noua adresa
    void set_provider_materials(const char **new_provider_materials, const int &new_provider_materials_count); // Modifica simultan pointerul catre matricea de materiale si numarul de materiale
    void set_provider_discount(const double &new_provider_discount); // Seteaza o noua valoare pentru reducere

    // Supraincarcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Provider &provider);
    friend std::ostream &operator<<(std::ostream &os, const Provider &provider);

    // Supraincarcarea operatorului de atribuire
    Provider &operator=(const Provider &other);

    // Supraincarcarea operatorilor relationali
    bool operator==(const Provider &other) const; // Returneaza true daca au atributele identice
    bool operator!=(const Provider &other) const; // Returneaza true daca cel putin un atribut difera

    // Interschimbare
    static void swap(Provider &provider1, Provider &provider2) noexcept;

private:
    char *id; // ID-ul furnizorului
    char *name; // Numele furnizorului
    char *phone; // Numarul de telefon pentru furnizor
    char *email; // Email-ul furnizorului
    char *address; // Adresa furnizorului
    char **materials_id; // Array pentru ID-urile materialelor disponibile
    int materials_count; // Numarul de materiale furnizate de provider
    double discount; // Procentul pentru aplicarea unei reduceri
};
