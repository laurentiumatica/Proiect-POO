#pragma once
#include <iosfwd>
#include <string>
#include <vector>

#include "materials.h"

// Definim structura si comportamentul pentru clasa Provider (Furnizor)
class Provider {
public:
    // Constructorul implicit
    Provider();

    // Constructorul de copiere
    Provider(const Provider &other);

    // Constructorul cu parametri
    Provider(std::string id, std::string name, std::string phone, std::string email, std::string address, std::vector<Material> materials);

    // Destructorul
    ~Provider();

    // Getters
    const std::string& get_provider_id() const; // Returneaza un pointer catre ID-ul furnizorului
    const std::string& get_provider_name() const; // Returneaza un pointer catre numele furnizorului
    const std::string& get_provider_phone() const; // Returneaza numarul de telefon
    const std::string& get_provider_email() const; // Returneaza adresa de email
    const std::string& get_provider_address() const; // Returneaza adresa fizica
    const std::vector<Material>& get_provider_materials() const; // Returneaza lista materialelor
    int get_provider_materials_count() const;

    // Supraincarcarea operatorului de atribuire
    Provider &operator=(Provider other);

    // Supraincarcarea operatorilor relationali
    bool operator==(const Provider &other) const; // Returneaza true daca au atributele identice
    bool operator!=(const Provider &other) const; // Returneaza true daca cel putin un atribut difera

    // Supraincarcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Provider &provider);
    friend std::ostream &operator<<(std::ostream &os, const Provider &provider);

    // Interschimbare
    static void swap(Provider &provider1, Provider &provider2) noexcept;

    // Functii helper
    static void print_available_materials(const std::vector<Material> &materials);

private:
    std::string id; // ID-ul furnizorului
    std::string name; // Numele furnizorului
    std::string phone; // Numarul de telefon pentru furnizor
    std::string email; // Email-ul furnizorului
    std::string address; // Adresa furnizorului
    std::vector<Material>materials; // Array pentru materialele disponibile
};