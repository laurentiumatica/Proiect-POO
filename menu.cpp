#include "menu.h"
#include "exceptions.h"
#include "utils.h"
#include "stock_observer.h"
#include <iostream>
#include <iomanip>
#include <limits>

// Singleton
Menu &Menu::get_instance() {
    static Menu instance;
    return instance;
}

// Constructor privat
Menu::Menu() {
    // Furnizorul 1 — Cherestea si lemn brut
    std::vector<Material> materials_prv1 = {
        Material("MAT-00001", "Cherestea Brad",      "mc", 0, 0, 850.00,  Material::Category::wood),
        Material("MAT-00002", "Cherestea Stejar",    "mc", 0, 0, 1200.00, Material::Category::wood),
        Material("MAT-00003", "Scandura Rindeluita", "mp", 0, 0, 38.00,   Material::Category::wood),
        Material("MAT-00004", "Barna Laminata",      "mc", 0, 0, 1500.00, Material::Category::wood),
        Material("MAT-00005", "Dulapi Molid",        "mc", 0, 0, 780.00,  Material::Category::wood)
    };

    // Furnizorul 2 — Placi si panouri pe baza de lemn
    std::vector<Material> materials_prv2 = {
        Material("MAT-00006", "Placa OSB",        "mp", 0, 0, 45.00,   Material::Category::wood),
        Material("MAT-00007", "PAL Melaminat",    "mp", 0, 0, 62.50,   Material::Category::wood),
        Material("MAT-00008", "Placaj Mesteacan", "mp", 0, 0, 95.00,   Material::Category::wood),
        Material("MAT-00009", "MDF Vopsibil",     "mp", 0, 0, 58.00,   Material::Category::wood),
        Material("MAT-00010", "Placa Fibra Dura", "mp", 0, 0, 32.00,   Material::Category::wood)
    };

    // Furnizorul 3 — Otel si profile metalice
    std::vector<Material> materials_prv3 = {
        Material("MAT-00011", "Otel Beton",         "kg", 0, 0, 4.20,  Material::Category::metal),
        Material("MAT-00012", "Profil Metalic UNP", "ml", 0, 0, 78.00, Material::Category::metal),
        Material("MAT-00013", "Teava Rectangulara", "ml", 0, 0, 32.00, Material::Category::metal),
        Material("MAT-00014", "Platbanda Otel",     "ml", 0, 0, 18.50, Material::Category::metal),
        Material("MAT-00015", "Cornier Laminat",    "ml", 0, 0, 24.00, Material::Category::metal)
    };

    // Furnizorul 4 — Tabla si acoperisuri metalice
    std::vector<Material> materials_prv4 = {
        Material("MAT-00016", "Tabla Zincata",  "mp", 0, 0, 55.00, Material::Category::metal),
        Material("MAT-00017", "Tabla Cutata",   "mp", 0, 0, 48.00, Material::Category::metal),
        Material("MAT-00018", "Tigla Metalica", "mp", 0, 0, 42.00, Material::Category::metal),
        Material("MAT-00019", "Jgheab Metalic", "ml", 0, 0, 35.00, Material::Category::metal),
        Material("MAT-00020", "Burlan Metalic", "ml", 0, 0, 28.00, Material::Category::metal)
    };

    // Furnizorul 5 — Izolatii termice
    std::vector<Material> materials_prv5 = {
        Material("MAT-00021", "Vata Minerala",       "mp", 0, 0, 28.50, Material::Category::insulation),
        Material("MAT-00022", "Polistiren Expandat",  "mp", 0, 0, 22.00, Material::Category::insulation),
        Material("MAT-00023", "Polistiren Extrudat",  "mp", 0, 0, 38.00, Material::Category::insulation),
        Material("MAT-00024", "Spuma Poliuretanica",  "l",  0, 0, 25.00, Material::Category::insulation),
        Material("MAT-00025", "Vata Bazaltica",      "mp", 0, 0, 34.00, Material::Category::insulation)
    };

    // Furnizorul 6 — Izolatii hidro si fonice
    std::vector<Material> materials_prv6 = {
        Material("MAT-00026", "Membrana Bituminoasa", "mp", 0, 0, 18.00, Material::Category::insulation),
        Material("MAT-00027", "Folie Anticondens",   "mp", 0, 0, 8.50,  Material::Category::insulation),
        Material("MAT-00028", "Bariera Vapori",      "mp", 0, 0, 6.20,  Material::Category::insulation),
        Material("MAT-00029", "Izolatie Fonica",     "mp", 0, 0, 42.00, Material::Category::insulation),
        Material("MAT-00030", "Banda Etansare",      "ml", 0, 0, 3.50,  Material::Category::insulation)
    };

    // Furnizorul 7 — Vopsele si grunduri
    std::vector<Material> materials_prv7 = {
        Material("MAT-00031", "Vopsea Lavabila", "l",  0, 0, 18.50, Material::Category::finishes),
        Material("MAT-00032", "Grund Acrilic",   "l",  0, 0, 12.00, Material::Category::finishes),
        Material("MAT-00033", "Vopsea Exterior", "l",  0, 0, 24.00, Material::Category::finishes),
        Material("MAT-00034", "Email Alchidic",  "l",  0, 0, 32.00, Material::Category::finishes),
        Material("MAT-00035", "Lac Parchet",     "l",  0, 0, 45.00, Material::Category::finishes)
    };

    // Furnizorul 8 — Adezivi si mortare de finisaj
    std::vector<Material> materials_prv8 = {
        Material("MAT-00036", "Glet de Finisaj",      "kg", 0, 0, 3.80, Material::Category::finishes),
        Material("MAT-00037", "Adeziv Gresie",        "kg", 0, 0, 2.90, Material::Category::finishes),
        Material("MAT-00038", "Tencuiala Decorativa",  "kg", 0, 0, 8.50, Material::Category::finishes),
        Material("MAT-00039", "Chit Rosturi",         "kg", 0, 0, 12.00, Material::Category::finishes),
        Material("MAT-00040", "Amorsa Perete",        "l",  0, 0, 9.00,  Material::Category::finishes)
    };

    // Furnizorul 9 — Gresie si faianta
    std::vector<Material> materials_prv9 = {
        Material("MAT-00041", "Gresie Portelanata", "mp", 0, 0, 65.00,  Material::Category::finishes),
        Material("MAT-00042", "Faianta Alba",       "mp", 0, 0, 42.00,  Material::Category::finishes),
        Material("MAT-00043", "Gresie Exterior",    "mp", 0, 0, 55.00,  Material::Category::finishes),
        Material("MAT-00044", "Mozaic Sticla",      "mp", 0, 0, 120.00, Material::Category::finishes),
        Material("MAT-00045", "Parchet Laminat",    "mp", 0, 0, 48.00,  Material::Category::finishes)
    };

    // Furnizorul 10 — Materiale generale de constructii
    std::vector<Material> materials_prv10 = {
        Material("MAT-00046", "Ciment Portland",  "kg",  0, 0, 0.85,  Material::Category::others),
        Material("MAT-00047", "Nisip Spalat",     "mc",  0, 0, 120.00, Material::Category::others),
        Material("MAT-00048", "Pietris Concasat", "mc",  0, 0, 95.00,  Material::Category::others),
        Material("MAT-00049", "Caramida Plina",   "buc", 0, 0, 1.20,  Material::Category::others),
        Material("MAT-00050", "BCA Clasic",       "buc", 0, 0, 6.50,  Material::Category::others)
    };

    Provider prv1("PRV-00001",  "Lemnul Verde",   "0723456789", "contact@lemnulverde.ro",   "Strada Padurii 5 Cluj",            materials_prv1);
    Provider prv2("PRV-00002",  "PanouriPlus",    "0723456790", "comenzi@panouriplus.ro",   "Strada Fabricii 12 Timisoara",     materials_prv2);
    Provider prv3("PRV-00003",  "MetalPro",       "0734567890", "comenzi@metalpro.ro",      "Bulevardul Fabricii 22 Sibiu",     materials_prv3);
    Provider prv4("PRV-00004",  "AcoperisTotal",  "0734567891", "office@acoperistotal.ro",  "Strada Industriei 8 Brasov",       materials_prv4);
    Provider prv5("PRV-00005",  "IzoTermica",     "0745678901", "vanzari@izotermica.ro",    "Aleea Constructorilor 3 Arad",     materials_prv5);
    Provider prv6("PRV-00006",  "HidroIzol",      "0745678902", "contact@hidroizol.ro",     "Strada Mecanicilor 15 Deva",       materials_prv6);
    Provider prv7("PRV-00007",  "ColorMax",       "0756789012", "comenzi@colormax.ro",      "Bulevardul Unirii 44 Oradea",     materials_prv7);
    Provider prv8("PRV-00008",  "FinisajExpert",  "0756789013", "office@finisajexpert.ro",  "Aleea Mesteserilor 8 Oradea",      materials_prv8);
    Provider prv9("PRV-00009",  "CeramicaDesign", "0767890123", "vanzari@ceramicadesign.ro","Strada Olarilor 21 Alba Iulia",    materials_prv9);
    Provider prv10("PRV-00010", "ConstructBaza",  "0767890124", "office@constructbaza.ro",  "Strada Depozitului 7 Satu Mare",   materials_prv10);

    // Catalogul complet de furnizori
    available_providers = {prv1, prv2, prv3, prv4, prv5, prv6, prv7, prv8, prv9, prv10};

    // Inventarul porneste cu 3 furnizori inregistrati, fara materiale sau tranzactii
    std::vector<Provider> registered = {prv1, prv3, prv10};

    inventory = Inventory(
        "INV-00001",
        "Depozit Central",
        "Strada Principala 10 Satu Mare",
        "0712345678",
        "depozit@constructii.ro",
        {}, registered
    );
    inventory.add_observer(std::make_unique<LowStockAlert>());
}

// Destructor privat
Menu::~Menu() = default;

// Helper — citeste o optiune numerica validata
int Menu::read_option(const std::string &prompt, const int min, const int max) {
    int option;
    while (true) {
        std::cout << prompt;
        if (std::cin >> option && option >= min && option <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return option;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid option. Please enter a number between " << min << " and " << max << ".\n\n";
    }
}

// Punctul de intrare
void Menu::run() {
    bool running = true;
    while (running) {
        std::cout << "\n==============================\n";
        std::cout << "       MAIN MENU\n";
        std::cout << "==============================\n";
        std::cout << "1. Inventory\n";
        std::cout << "2. Materials\n";
        std::cout << "3. Providers\n";
        std::cout << "4. Transactions\n";
        std::cout << "5. Reports\n";
        std::cout << "6. Developer Mode\n";
        std::cout << "0. Exit\n";
        std::cout << "==============================\n";

        const int option = read_option("Select option: ", 0, 6);

        try {
            switch (option) {
                case 1: inventory_menu(); break;
                case 2: materials_menu(); break;
                case 3: providers_menu(); break;
                case 4: transactions_menu(); break;
                case 5: reports_menu(); break;
                case 6:
                    if (authenticate_developer())
                        developer_menu();
                    break;
                case 0:
                    std::cout << "Exiting...\n";
                    running = false;
                    break;
                default: break;
            }
        } catch (const InventoryException &e) {
            std::cout << "Error: " << e.what() << "\n\n";
        }
    }
}

// Submeniu — Inventar
void Menu::inventory_menu() {
    bool running = true;
    while (running) {
        std::cout << "\n------------------------------\n";
        std::cout << "     INVENTORY MENU\n";
        std::cout << "------------------------------\n";
        std::cout << "1. View inventory details\n";
        std::cout << "2. Edit inventory name\n";
        std::cout << "3. Edit inventory address\n";
        std::cout << "4. Edit inventory phone\n";
        std::cout << "5. Edit inventory email\n";
        std::cout << "0. Back\n";
        std::cout << "------------------------------\n";

        const int option = read_option("Select option: ", 0, 5);

        try {
            switch (option) {
                case 1:
                    std::cout << "\n" << inventory;
                    break;
                case 2:
                    Utils::read_string("Enter new inventory name", [this](const std::string &s) {
                        inventory.set_inventory_name(s);
                    });
                    std::cout << "Inventory name updated.\n";
                    break;
                case 3:
                    Utils::read_string("Enter new inventory address", [this](const std::string &s) {
                        inventory.set_inventory_address(s);
                    });
                    std::cout << "Inventory address updated.\n";
                    break;
                case 4:
                    Utils::read_string("Enter new inventory phone", [this](const std::string &s) {
                        inventory.set_inventory_phone(s);
                    });
                    std::cout << "Inventory phone updated.\n";
                    break;
                case 5:
                    Utils::read_string("Enter new inventory email", [this](const std::string &s) {
                        inventory.set_inventory_email(s);
                    });
                    std::cout << "Inventory email updated.\n";
                    break;
                case 0:
                    running = false;
                    break;
                default: break;
            }
        } catch (const InventoryException &e) {
            std::cout << "Error: " << e.what() << "\n\n";
        }
    }
}

// Submeniu — Materiale
void Menu::materials_menu() {
    bool running = true;
    while (running) {
        std::cout << "\n------------------------------\n";
        std::cout << "     MATERIALS MENU\n";
        std::cout << "------------------------------\n";
        std::cout << "1. List all materials\n";
        std::cout << "2. Find material by ID\n";
        std::cout << "3. View critical materials\n";
        std::cout << "4. Filter by category\n";
        std::cout << "5. Sort by name (ascending)\n";
        std::cout << "6. Sort by name (descending)\n";
        std::cout << "7. Sort by quantity (ascending)\n";
        std::cout << "8. Sort by quantity (descending)\n";
        std::cout << "0. Back\n";
        std::cout << "------------------------------\n";

        const int option = read_option("Select option: ", 0, 8);

        try {
            switch (option) {
                case 1: {
                    if (inventory.get_inventory_materials_count() == 0)
                        std::cout << "No materials in inventory.\n";
                    else
                        Inventory::print_selected_materials(inventory.get_inventory_materials());
                    break;
                }
                case 2: {
                    std::string search_id;
                    Utils::read_string("Enter material ID to search (expected format: MAT-#####)", [&search_id](const std::string &s) {
                        Utils::validate_material_id(s);
                        search_id = s;
                    });
                    const Material *found = inventory.find_material_by_id(search_id);
                    if (found)
                        std::cout << "\n" << *found;
                    else
                        std::cout << "Material not found.\n";
                    break;
                }
                case 3: {
                    std::vector<Material> critical = inventory.get_critical_materials();
                    if (critical.empty())
                        std::cout << "No materials at critical level.\n";
                    else {
                        std::cout << "Materials at critical stock level:\n\n";
                        Inventory::print_selected_materials(critical);
                    }
                    break;
                }
                case 4: {
                    std::cout << "Categories: 0 - wood, 1 - metal, 2 - insulation, 3 - finishes, 4 - others\n";
                    const int cat = read_option("Select category: ", 0, 4);
                    auto category = static_cast<Material::Category>(cat);
                    std::vector<Material> filtered = inventory.get_materials_by_category(category);
                    if (filtered.empty())
                        std::cout << "No materials found in category "
                                  << Material::material_category_to_string(category) << ".\n";
                    else
                        Inventory::print_selected_materials(filtered);
                    break;
                }
                case 5: {
                    if (inventory.get_inventory_materials_count() == 0) {
                        std::cout << "No materials to sort.\n";
                    } else {
                        Inventory::display_selected_materials_by_name(
                            inventory.get_inventory_materials(),
                            [](const Material &a, const Material &b) {
                                return a.get_material_name() < b.get_material_name();
                            });
                    }
                    break;
                }
                case 6: {
                    if (inventory.get_inventory_materials_count() == 0) {
                        std::cout << "No materials to sort.\n";
                    } else {
                        Inventory::display_selected_materials_by_name(
                            inventory.get_inventory_materials(),
                            [](const Material &a, const Material &b) {
                                return a.get_material_name() > b.get_material_name();
                            });
                    }
                    break;
                }
                case 7: {
                    if (inventory.get_inventory_materials_count() == 0) {
                        std::cout << "No materials to sort.\n";
                    } else {
                        Inventory::display_selected_materials_by_quantity(
                            inventory.get_inventory_materials(),
                            [](const Material &a, const Material &b) {
                                return a.get_material_quantity() < b.get_material_quantity();
                            });
                    }
                    break;
                }
                case 8: {
                    if (inventory.get_inventory_materials_count() == 0) {
                        std::cout << "No materials to sort.\n";
                    } else {
                        Inventory::display_selected_materials_by_quantity(
                            inventory.get_inventory_materials(),
                            [](const Material &a, const Material &b) {
                                return a.get_material_quantity() > b.get_material_quantity();
                            });
                    }
                    break;
                }
                case 0:
                    running = false;
                    break;
                default: break;
            }
        } catch (const InventoryException &e) {
            std::cout << "Error: " << e.what() << "\n\n";
        }
    }
}

// Submeniu — Furnizori
void Menu::providers_menu() {
    bool running = true;
    while (running) {
        std::cout << "\n------------------------------\n";
        std::cout << "     PROVIDERS MENU\n";
        std::cout << "------------------------------\n";
        std::cout << "1. List registered providers\n";
        std::cout << "2. List available unregistered providers\n";
        std::cout << "3. Register a provider\n";
        std::cout << "4. Find provider by ID\n";
        std::cout << "0. Back\n";
        std::cout << "------------------------------\n";

        const int option = read_option("Select option: ", 0, 4);

        try {
            switch (option) {
                case 1: {
                    if (inventory.get_inventory_providers_count() == 0)
                        std::cout << "No registered providers.\n";
                    else
                        Inventory::print_selected_providers(inventory.get_inventory_providers());
                    break;
                }
                case 2: {
                    inventory.print_available_unregistered_providers(available_providers);
                    break;
                }
                case 3: {
                    inventory.register_provider(available_providers);
                    std::cout << "Provider registered successfully.\n";
                    break;
                }
                case 4: {
                    std::string search_id;
                    Utils::read_string("Enter provider ID to search (expected format: PRV-#####)", [&search_id](const std::string &s) {
                        Utils::validate_provider_id(s);
                        search_id = s;
                    });
                    const Provider *found = inventory.find_provider_by_id(search_id);
                    if (found)
                        std::cout << "\n" << *found;
                    else
                        std::cout << "Provider not found in registered providers.\n";
                    break;
                }
                case 0:
                    running = false;
                    break;
                default: break;
            }
        } catch (const InventoryException &e) {
            std::cout << "Error: " << e.what() << "\n\n";
        }
    }
}

// Submeniu — Tranzactii
void Menu::transactions_menu() {
    bool running = true;
    while (running) {
        std::cout << "\n------------------------------\n";
        std::cout << "     TRANSACTIONS MENU\n";
        std::cout << "------------------------------\n";
        std::cout << "1. Place purchase order\n";
        std::cout << "2. Record consumption\n";
        std::cout << "3. Register return\n";
        std::cout << "4. Record adjustment\n";
        std::cout << "5. Process transaction\n";
        std::cout << "6. Cancel purchase order\n";
        std::cout << "7. List all transactions\n";
        std::cout << "8. List purchase orders only\n";
        std::cout << "9. Find transaction by ID\n";
        std::cout << "0. Back\n";
        std::cout << "------------------------------\n";

        const int option = read_option("Select option: ", 0, 9);

        try {
            switch (option) {
                case 1: {
                    if (inventory.get_inventory_providers_count() == 0) {
                        std::cout << "No registered providers. Register a provider first.\n";
                    } else {
                        inventory.place_order();
                        std::cout << "Purchase order created successfully.\n";
                    }
                    break;
                }
                case 2: {
                    if (inventory.get_inventory_materials_count() == 0) {
                        std::cout << "No materials in inventory. Process a purchase order first.\n";
                    } else {
                        inventory.record_consumption();
                        std::cout << "Consumption recorded successfully.\n";
                    }
                    break;
                }
                case 3: {
                    if (inventory.get_inventory_materials_count() == 0) {
                        std::cout << "No materials in inventory to return.\n";
                    } else {
                        inventory.register_return();
                        std::cout << "Return registered successfully.\n";
                    }
                    break;
                }
                case 4: {
                    if (inventory.get_inventory_materials_count() == 0) {
                        std::cout << "No materials in inventory to adjust.\n";
                    } else {
                        inventory.record_adjustment();
                        std::cout << "Adjustment recorded successfully.\n";
                    }
                    break;
                }
                case 5: {
                    if (inventory.get_inventory_transactions_count() == 0) {
                        std::cout << "No transactions to process.\n";
                    } else {
                        inventory.process_transaction();
                        std::cout << "Transaction processed successfully.\n";
                    }
                    break;
                }
                case 6: {
                    if (inventory.get_inventory_transactions_count() == 0) {
                        std::cout << "No transactions to cancel.\n";
                    } else {
                        inventory.cancel_order();
                        std::cout << "Purchase order cancelled successfully.\n";
                    }
                    break;
                }
                case 7: {
                    if (inventory.get_inventory_transactions_count() == 0)
                        std::cout << "No transactions recorded.\n";
                    else
                        Inventory::print_selected_transactions(inventory.get_inventory_transactions());
                    break;
                }
                case 8: {
                    if (inventory.get_inventory_transactions_count() == 0)
                        std::cout << "No transactions recorded.\n";
                    else
                        Inventory::print_selected_purchase_orders(inventory.get_inventory_transactions());
                    break;
                }
                case 9: {
                    std::string search_id;
                    Utils::read_string("Enter transaction ID to search (expected format: TRN-#####)", [&search_id](const std::string &s) {
                        Utils::validate_transaction_id(s);
                        search_id = s;
                    });
                    const Transaction *found = inventory.find_transaction_by_id(search_id);
                    if (found)
                        std::cout << "\n" << *found;
                    else
                        std::cout << "Transaction not found.\n";
                    break;
                }
                case 0:
                    running = false;
                    break;
                default: break;
            }
        } catch (const InventoryException &e) {
            std::cout << "Error: " << e.what() << "\n\n";
        }
    }
}

// Submeniu — Rapoarte
void Menu::reports_menu() const {
    bool running = true;
    while (running) {
        std::cout << "\n------------------------------\n";
        std::cout << "     REPORTS MENU\n";
        std::cout << "------------------------------\n";
        std::cout << "1. Total inventory cost\n";
        std::cout << "2. Total refunds\n";
        std::cout << "3. Purchase orders by provider\n";
        std::cout << "4. Sort purchase orders by total price (ascending)\n";
        std::cout << "5. Sort purchase orders by total price (descending)\n";
        std::cout << "0. Back\n";
        std::cout << "------------------------------\n";

        const int option = read_option("Select option: ", 0, 5);

        try {
            switch (option) {
                case 1: {
                    std::cout << "Total inventory cost: " << std::fixed << std::setprecision(2)
                              << inventory.get_inventory_total_cost() << " RON\n";
                    break;
                }
                case 2: {
                    std::cout << "Total refunds: " << std::fixed << std::setprecision(2)
                              << inventory.get_inventory_total_refunds() << " RON\n";
                    break;
                }
                case 3: {
                    if (inventory.get_inventory_providers_count() == 0) {
                        std::cout << "No registered providers.\n";
                    } else {
                        Inventory::print_selected_providers(inventory.get_inventory_providers());
                        std::string provider_id;
                        Utils::read_string("Enter provider ID (expected format: PRV-#####)", [&provider_id, this](const std::string &s) {
                            Utils::validate_provider_id(s);
                            if (inventory.find_provider_by_id(s) == nullptr)
                                throw ResourceNotFoundException("Provider not found in registered providers");
                            provider_id = s;
                        });
                        std::vector<PurchaseOrder> orders = inventory.get_purchase_orders_by_provider_id(provider_id);
                        if (orders.empty())
                            std::cout << "No purchase orders found for this provider.\n";
                        else {
                            std::cout << "\nPurchase orders for provider " << provider_id << ":\n\n";
                            for (const auto &order : orders)
                                std::cout << order;
                        }
                    }
                    break;
                }
                case 4: {
                    if (inventory.get_inventory_transactions_count() == 0) {
                        std::cout << "No transactions recorded.\n";
                    } else {
                        Inventory::display_selected_purchase_orders_by_total_price(
                            inventory.get_inventory_transactions(),
                            [](const PurchaseOrder &a, const PurchaseOrder &b) {
                                return a.get_transaction_total_price() < b.get_transaction_total_price();
                            });
                    }
                    break;
                }
                case 5: {
                    if (inventory.get_inventory_transactions_count() == 0) {
                        std::cout << "No transactions recorded.\n";
                    } else {
                        Inventory::display_selected_purchase_orders_by_total_price(
                            inventory.get_inventory_transactions(),
                            [](const PurchaseOrder &a, const PurchaseOrder &b) {
                                return a.get_transaction_total_price() > b.get_transaction_total_price();
                            });
                    }
                    break;
                }
                case 0:
                    running = false;
                    break;
                default: break;
            }
        } catch (const InventoryException &e) {
            std::cout << "Error: " << e.what() << "\n\n";
        }
    }
}
// Autentificare developer
bool Menu::authenticate_developer() {
    std::string password;
    std::cout << "Enter developer password: ";
    std::getline(std::cin, password);

    if (password != DEV_PASSWORD) {
        std::cout << "Access denied. Incorrect password.\n";
        return false;
    }

    std::cout << "Access granted. Welcome, developer.\n";
    return true;
}

// Submeniu — Developer Mode
void Menu::developer_menu() {
    bool running = true;
    while (running) {
        std::cout << "\n------------------------------\n";
        std::cout << "     DEVELOPER MODE\n";
        std::cout << "------------------------------\n";
        std::cout << "1. List all global providers\n";
        std::cout << "2. View global provider materials\n";
        std::cout << "3. Show system stats\n";
        std::cout << "0. Logout\n";
        std::cout << "------------------------------\n";

        const int option = read_option("Select option: ", 0, 3);

        try {
            switch (option) {
                case 1: {
                    if (available_providers.empty()) {
                        std::cout << "No global providers registered.\n";
                    } else {
                        std::cout << "\nAll global providers (" << available_providers.size() << "):\n\n";
                        for (const auto &provider : available_providers)
                            std::cout << provider;
                    }
                    break;
                }
                case 2: {
                    if (available_providers.empty()) {
                        std::cout << "No global providers registered.\n";
                    } else {
                        std::string provider_id;
                        Utils::read_string("Enter provider ID (expected format: PRV-#####)", [&provider_id](const std::string &s) {
                            Utils::validate_provider_id(s);
                            provider_id = s;
                        });
                        auto it = std::ranges::find_if(available_providers, [&provider_id](const Provider &p) {
                            return p.get_provider_id() == provider_id;
                        });
                        if (it == available_providers.end())
                            throw ResourceNotFoundException("Provider not found in global catalog");

                        std::cout << "\nMaterials supplied by " << it->get_provider_name() << ":\n\n";
                        Provider::print_available_materials(it->get_provider_materials());
                    }
                    break;
                }
                case 3: {
                    std::cout << "\n--- System Stats ---\n";
                    std::cout << "Global providers:       " << available_providers.size() << "\n";
                    int total_materials = 0;
                    for (const auto &provider : available_providers)
                        total_materials += provider.get_provider_materials_count();
                    std::cout << "Total global materials: " << total_materials << "\n";
                    std::cout << "Registered providers:   " << inventory.get_inventory_providers_count() << "\n";
                    std::cout << "Inventory materials:    " << inventory.get_inventory_materials_count() << "\n";
                    std::cout << "Transactions:           " << inventory.get_inventory_transactions_count() << "\n";
                    std::cout << "--------------------\n";
                    break;
                }
                case 0:
                    std::cout << "Logging out of developer mode.\n";
                    running = false;
                    break;
                default: break;
            }
        } catch (const InventoryException &e) {
            std::cout << "Error: " << e.what() << "\n\n";
        }
    }
}
