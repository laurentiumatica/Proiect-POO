#pragma once
#include <iosfwd>
#include <span>
#include <string>
#include <vector>

#include "materials.h"

// Definim structura si comportamentul pentru clasa Provider (Furnizor)
class Provider {
public:

    // Informatiile necesare pentru materiale (presupunem ca furnizorii au o cantitate infinita din fiecare material)
    struct ProviderMaterial {
        std::string material_id;
        std::string material_name;
        Material::Category material_category;
        double unit_price;
    };

    // Constructorul implicit
    Provider();

    // Constructorul de copiere
    Provider(const Provider &other);

    // Constructorul cu parametri
    Provider(std::string_view new_provider_id, std::string_view new_provider_name, std::string_view new_provider_phone,
             std::string_view new_provider_email, std::string_view new_provider_address,
             std::span<const ProviderMaterial> new_provider_materials);

    // Destructorul
    ~Provider();

    // Getters
    [[nodiscard]] const std::string& get_provider_id() const; // Returneaza un pointer catre ID-ul furnizorului
    [[nodiscard]] const std::string& get_provider_name() const; // Returneaza un pointer catre numele furnizorului
    [[nodiscard]] const std::string& get_provider_phone() const; // Returneaza numarul de telefon
    [[nodiscard]] const std::string& get_provider_email() const; // Returneaza adresa de email
    [[nodiscard]] const std::string& get_provider_address() const; // Returneaza adresa fizica
    [[nodiscard]] const std::vector<ProviderMaterial>& get_provider_materials() const; // Returneaza lista materialelor
    [[nodiscard]] int get_provider_materials_count() const;

    // Supraincarcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Provider &provider);
    friend std::ostream &operator<<(std::ostream &os, const Provider &provider);

    // Supraincarcarea operatorului de atribuire
    Provider &operator=(Provider other);

    // Supraincarcarea operatorilor relationali
    bool operator==(const Provider &other) const; // Returneaza true daca au atributele identice
    bool operator!=(const Provider &other) const; // Returneaza true daca cel putin un atribut difera

    // Interschimbare
    static void swap(Provider &provider1, Provider &provider2) noexcept;

    // Setters
    void set_provider_id(std::string_view new_provider_id);
    void set_provider_name(std::string_view new_provider_name);
    void set_provider_phone(std::string_view new_provider_phone);
    void set_provider_email(std::string_view new_provider_email);
    void set_provider_address(std::string_view new_provider_address);
    void set_provider_materials(std::span<const ProviderMaterial> new_provider_materials);

    // Functii helper
    static void validate_provider_id(std::string_view new_provider_id);
    static void validate_provider_name(std::string_view new_provider_name);
    static void validate_provider_phone(std::string_view new_provider_phone);
    static void validate_provider_email(std::string_view new_provider_email);
    static void validate_provider_address(std::string_view new_provider_address);
    static void validate_provider_materials(std::span<const ProviderMaterial> new_provider_materials);
    static void validate_provider_materials_number(int new_provider_materials_number);
    static void provider_material_already_exists(std::string_view material_id, std::span<const ProviderMaterial> materials);
    static void read_string(const std::string &prompt, auto setter);
    static void read_material(ProviderMaterial &material, std::span<const ProviderMaterial> materials);

private:
    std::string id; // ID-ul furnizorului
    std::string name; // Numele furnizorului
    std::string phone; // Numarul de telefon pentru furnizor
    std::string email; // Email-ul furnizorului
    std::string address; // Adresa furnizorului
    std::vector<ProviderMaterial>materials; // Array pentru materialele disponibile

    // Functii helper
    static void set_provider_material_id(ProviderMaterial &material, std::string_view new_provider_material_id, std::span<const ProviderMaterial> materials);
    static void set_provider_material_name(ProviderMaterial &material, std::string_view new_provider_material_name);
    static void set_provider_material_unit_price(ProviderMaterial &material, double new_provider_material_unit_price);
};