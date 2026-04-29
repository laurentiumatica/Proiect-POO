#pragma once
#include "inventory.h"
#include "providers.h"
#include <vector>

class Menu {
public:
    // Punct de acces unic la instanta Singleton
    static Menu &get_instance();

    // Stergem constructorii de copiere si mutare + operatorii de atribuire
    Menu(const Menu &) = delete;
    Menu(Menu &&) = delete;
    Menu &operator=(const Menu &) = delete;
    Menu &operator=(Menu &&) = delete;

    // Punctul de intrare in aplicatie
    void run();

private:
    // Constructor privat — initializeaza inventarul si furnizorii hardcodati
    Menu();

    // Destructor privat
    ~Menu();

    // Submeniuri
    void inventory_menu();
    void materials_menu();
    void providers_menu();
    void transactions_menu();
    void reports_menu() const;
    void developer_menu();

    // Autentificare developer
    static bool authenticate_developer();

    // Functie helper pentru citirea optiunii din meniu
    static int read_option(const std::string &prompt, int min, int max);

    // Starea aplicatiei
    Inventory inventory;
    std::vector<Provider> available_providers;

    // Parola developer (hardcodata — in productie ar fi hash-uita)
    static constexpr auto DEV_PASSWORD = "admin123";
};
