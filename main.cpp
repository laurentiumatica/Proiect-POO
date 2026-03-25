#include "inventory.h"
#include <iostream>
#include <limits>

// Afișează un separator vizual în consolă
void print_separator(const char *title = nullptr) {
    std::cout << "\n====================================================\n";
    if (title != nullptr)
        std::cout << "  " << title << "\n====================================================\n";
}

// Citește un număr întreg cu validare de bază
int read_int(const char *prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Invalid input. Try again: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

// Afișează lista materialelor din inventar (ID + nume + cantitate + preț)
void print_materials_list(const Inventory &inventory) {
    print_separator("MATERIALS");
    if (inventory.get_inventory_materials_count() == 0) {
        std::cout << "  (no material registered)\n";
        return;
    }
    for (int i = 0; i < inventory.get_inventory_materials_count(); i++)
        std::cout << inventory.get_inventory_materials()[i];
}

// Afișează lista furnizorilor din inventar (ID + nume + contact)
void print_providers_list(const Inventory &inventory) {
    print_separator("PROVIDERS");
    if (inventory.get_inventory_providers_count() == 0) {
        std::cout << "  (no provider registered)\n";
        return;
    }
    for (int i = 0; i < inventory.get_inventory_providers_count(); i++)
        std::cout << inventory.get_inventory_providers()[i];
}

// Afișează lista comenzilor din inventar (ID + status + preț + materiale)
void print_orders_list(const Inventory &inventory) {
    print_separator("ORDRES");
    if (inventory.get_inventory_orders_count() == 0) {
        std::cout << "  (no order registered)\n";
        return;
    }
    for (int i = 0; i < inventory.get_inventory_orders_count(); i++)
        std::cout << inventory.get_inventory_orders()[i];
}

// Construiește și returnează un obiect Inventory complet populat (primul demo)
Inventory build_inventory_alpha() {
    const Material material1("MAT-001", "Cherestea stejar", "m3", 12.5, 3.0, 850.0, Material::Category::wood);
    const Material material2("MAT-002", "Profil U otel", "m", 200.0, 50.0, 18.5, Material::Category::metal);
    const Material material3("MAT-003", "Vata minerala", "m2", 80.0, 20.0, 35.0, Material::Category::insulation);
    const Material material4("MAT-004", "Vopsea alba interior", "l", 45.0, 10.0, 28.0, Material::Category::finishes);
    const Material material5("MAT-005", "Suruburi inox M8", "buc", 500.0, 100.0, 0.75, Material::Category::metal);

    const Material init_materials[] = { material1, material2, material3, material4, material5 };

    const char *provider1_materials[] = { "MAT-001", "MAT-003" };
    const Provider provider1("PRV-001", "LemnPro SRL",   "0721111111", "contact@lemnpro.ro", "Str. Padurii 10, Cluj-Napoca", provider1_materials, 2, 5.0);

    const char *provider2_materials[] = { "MAT-002", "MAT-005" };
    const Provider provider2("PRV-002", "MetalTech SA",  "0733222222", "vanzari@metaltech.ro", "Bd. Industriei 45, Bucuresti", provider2_materials, 2, 3.0);

    const char *provider3_materials[] = { "MAT-004" };
    const Provider provider3("PRV-003", "ColorVibe SRL", "0744333333", "office@colorvibe.ro", "Calea Victoriei 7, Timisoara", provider3_materials, 1, 7.5);

    const Provider providers[] = { provider1, provider2, provider3 };

    const char *order1_materials[] = { "MAT-001", "MAT-003" };
    constexpr double order1_quantities[]  = { 5.0, 30.0 };
    Order order1("ORD-001", "PRV-001", order1_materials, 2, order1_quantities, 2, 5300.0, "10-01-2025");
    order1.set_order_status(Order::Status::delivered);

    const char *order2_materials[] = { "MAT-002", "MAT-005" };
    constexpr double order2_quantities[]  = { 100.0, 200.0 };
    const Order order2("ORD-002", "PRV-002", order2_materials, 2, order2_quantities, 2, 2000.0, "15-02-2025");

    const char *order3_materials[] = { "MAT-004" };
    constexpr double order3_quantities[]  = { 20.0 };
    const Order order3("ORD-003", "PRV-003", order3_materials, 1, order3_quantities, 1, 560.0, "20-03-2025");

    const Order orders[] = { order1, order2, order3 };

    // Construim inventarul cu capacități mai mari decât datele inițiale pentru a lăsa loc operațiunilor de adăugare din meniu
    const Inventory inventory("INV-ALPHA", "Depozit Alpha", "Str. Depozitului 1, Cluj-Napoca", "0264111111", "alpha@depot.ro", init_materials, providers, orders, 5, 3, 3, 10, 8, 10);

    return inventory;
}

// Construiește și returnează al doilea inventar demo (profilul Beta)
Inventory build_inventory_beta() {
    const Material material1("MAT-101", "Placaj 18mm", "m2", 60.0, 15.0, 42.0, Material::Category::wood);
    const Material material2("MAT-102", "Bara rotunda otel", "m", 300.0, 80.0, 12.0, Material::Category::metal);
    const Material material3("MAT-103", "Polistiren expandat", "m2", 120.0, 30.0, 22.5, Material::Category::insulation);

    const Material materials[] = { material1, material2, material3 };

    const char *provider1_materials[] = { "MAT-101" };
    const Provider provider1("PRV-101", "PlaciWood SRL", "0755100100", "info@placiwood.ro", "Str. Lemnului 3, Brasov", provider1_materials, 1, 4.0);

    const char *provider2_materials[] = { "MAT-102" };
    const Provider provider2("PRV-102", "OtelRom SA",    "0766200200", "sales@otelrom.ro", "Calea Metalurgistilor 22, Galati", provider2_materials, 1, 2.0);

    const Provider providers[] = { provider1, provider2 };

    const char *order1_materials[] = { "MAT-101", "MAT-103" };
    constexpr double order1_quantities[]  = { 20.0, 50.0 };
    const Order order1("ORD-101", "PRV-101", order1_materials, 2, order1_quantities, 2, 1965.0, "05-03-2025");

    const Order orders[] = { order1 };

    const Inventory inventory("INV-BETA", "Depozit Beta", "Bd. Constructorilor 88, Brasov", "0268222222", "beta@depot.ro", materials, providers, orders, 3, 2, 1, 10, 8, 10);

    return inventory;
}

void test_constructori(const Inventory &inventory_alpha, const Inventory &inventory_beta) {
    print_separator("TEST 1: CONSTRUCTORI SI OPERATOR<<");

    std::cout << "\n[1a] Material default (fara crash): OK\n";
    Material materials_default;
    std::cout << "  quantity=" << materials_default.get_material_quantity()
              << "  unit_price=" << materials_default.get_material_unit_price() << "\n";

    // Constructor parametrizat Material
    std::cout << "\n[1b] Material parametrizat:\n";
    const Material material_parameters("MAT-TEST", "Caramida rosie", "buc", 1000.0, 200.0, 1.5, Material::Category::others);
    std::cout << material_parameters;

    // Copy constructor Material
    std::cout << "\n[1c] Material copie (copy constructor):\n";
    const Material& material(material_parameters);
    std::cout << material;

    // Constructor default Provider — pointerii interni sunt null
    std::cout << "\n[1d] Provider default (fara crash): OK\n";
    const Provider provider_default;
    std::cout << "  discount=" << provider_default.get_provider_discount()
              << "  materials_count=" << provider_default.get_provider_materials_count() << "\n";

    // Constructor parametrizat Provider
    std::cout << "\n[1e] Provider parametrizat:\n";
    const char *provider_materials[] = { "MAT-TEST" };
    const Provider provider_parameters("PRV-TEST", "TestProv SRL", "0700000000", "test@prov.ro",
                        "Str. Test 1, Bucuresti", provider_materials, 1, 5.0);
    std::cout << provider_parameters;

    // Copy constructor Provider
    std::cout << "\n[1f] Provider copie:\n";
    const Provider& provider_copy(provider_parameters);
    std::cout << provider_copy;

    // Constructor default Order — pointerii interni sunt null
    std::cout << "\n[1g] Order default (fara crash): OK\n";
    const Order order_default;
    std::cout << "  total_price=" << order_default.get_order_total_price() << "  materials_count=" << order_default.get_order_materials_count() << "\n";

    // Constructor parametrizat Order
    std::cout << "\n[1h] Order parametrizat:\n";
    const char *order_materials[] = { "MAT-TEST" };
    constexpr double  order_quantities[]  = { 50.0 };
    const Order order_parameters("ORD-TEST", "PRV-TEST", order_materials, 1, order_quantities, 1, 75.0, "01-01-2025");
    std::cout << order_parameters;

    // Copy constructor Order
    std::cout << "\n[1i] Order copie:\n";
    const Order& order_copy(order_parameters);
    std::cout << order_copy;

    // Constructor default Inventory — pointerii interni sunt null
    std::cout << "\n[1j] Inventory default (fara crash): OK\n";
    const Inventory inventory_default;
    std::cout << "  materials_count=" << inventory_default.get_inventory_materials_count()
              << "  providers_count=" << inventory_default.get_inventory_providers_count()
              << "  orders_count=" << inventory_default.get_inventory_orders_count() << "\n";

    // Copy constructor Inventory
    std::cout << "\n[1k] Inventory copie (inventory_alpha):\n";
    const Inventory& inventory_copy(inventory_alpha);
    std::cout << inventory_copy;

    // Afișare inv_beta prin operator<<
    std::cout << "\n[1l] Inventory Beta prin operator<<:\n";
    std::cout << inventory_beta;
}

void test_atribuire(const Inventory &inventory_alpha) {
    print_separator("TEST 2: OPERATOR= (ATRIBUIRE)");

    std::cout << "\n[2a] Material: atribuire\n";
    Material material1("MAT-A", "Material A", "kg", 10.0, 2.0, 5.0, Material::Category::wood);
    Material material2;
    material2 = material1;
    std::cout << "  Sursa:  "; std::cout << material1;
    std::cout << "  Copie: "; std::cout << material2;

    std::cout << "\n[2b] Provider: atribuire\n";
    const char *provider_materials[] = { "MAT-A" };
    Provider provider1("PRV-A", "ProvA SRL", "0700000001", "a@prov.ro", "Str. A 1", provider_materials, 1, 3.0);
    Provider provider2;
    provider2 = provider1;
    std::cout << "  Sursa:  "; std::cout << provider1;
    std::cout << "  Copie: "; std::cout << provider2;

    std::cout << "\n[2c] Order: atribuire\n";
    const char *order_materials[] = { "MAT-A" };
    constexpr double order_quantities[] = { 5.0 };
    Order order1("ORD-A", "PRV-A", order_materials, 1, order_quantities, 1, 25.0, "01-02-2025");
    Order order2;
    order2 = order1;
    std::cout << "  Sursa:  "; std::cout << order1;
    std::cout << "  Copie: "; std::cout << order2;

    std::cout << "\n[2d] Inventory: atribuire\n";
    Inventory inventory_destination;
    inventory_destination = inventory_alpha;
    std::cout << "  Inventar atribuit:\n" << inventory_destination;
}

void test_egalitate(const Inventory &inventory_alpha) {
    print_separator("TEST 3: OPERATOR== SI OPERATOR!=");

    const Material material1("MAT-X", "Fier beton", "kg", 500.0, 100.0, 3.5, Material::Category::metal);
    const Material& material2(material1);   // copie identică
    const Material material3("MAT-Y", "Cupru", "kg", 100.0, 20.0, 45.0, Material::Category::metal);

    std::cout << "\n[3a] Material m1 == m2 (copie):       " << (material1 == material2 ? "DA" : "NU") << "\n";
    std::cout << "[3b] Material m1 != m3 (diferit):     " << (material1 != material3 ? "DA" : "NU") << "\n";
    std::cout << "[3c] Material m2 == m3 (false):       " << (material2 == material3 ? "DA" : "NU") << "\n";

    const char *provider_materials[] = { "MAT-X" };
    Provider provider1("PRV-X", "ProvX", "0700000002", "x@prov.ro", "Str. X", provider_materials, 1, 5.0);
    const Provider& provider2(provider1);
    const Provider p3("PRV-Z", "ProvZ", "0700000003", "z@prov.ro", "Str. Z", provider_materials, 1, 2.0);

    std::cout << "\n[3d] Provider p1 == p2 (copie):       " << (provider1 == provider2 ? "DA" : "NU") << "\n";
    std::cout << "[3e] Provider p1 != p3 (diferit):     " << (provider1 != p3 ? "DA" : "NU") << "\n";

    const char *order_materials[] = { "MAT-X" };
    constexpr double order_quantities[] = { 10.0 };
    const Order order1("ORD-X", "PRV-X", order_materials, 1, order_quantities, 1, 35.0, "01-03-2025");
    const Order& order2(order1);
    const Order order3("ORD-Z", "PRV-Z", order_materials, 1, order_quantities, 1, 99.0, "15-03-2025");

    std::cout << "\n[3f] Order o1 == o2 (copie):          " << (order1 == order2 ? "DA" : "NU") << "\n";
    std::cout << "[3g] Order o1 != o3 (diferit):        " << (order1 != order3 ? "DA" : "NU") << "\n";

    const Inventory& inventory_copy(inventory_alpha);
    Inventory inventory_modified(inventory_alpha);
    inventory_modified.set_inventory_name("MODIFICAT");

    std::cout << "\n[3h] Inventory == copie exacta:       " << (inventory_alpha == inventory_copy ? "DA" : "NU") << "\n";
    std::cout << "[3i] Inventory != copie modificata:   " << (inventory_alpha != inventory_modified ? "DA" : "NU") << "\n";
}

void test_getters_setters(Inventory &inventory) {
    print_separator("TEST 4: GETTERS SI SETTERS");

    // Material setters
    std::cout << "\n[4a] Material setters:\n";
    Material *material = inventory.find_material_by_id("MAT-002");
    if (material) {
        std::cout << "  set_material_name:         " << material->get_material_name() << " -> ";
        material->set_material_name("Profil U otel zincat");
        std::cout << material->get_material_name() << "\n";

        std::cout << "  set_material_unit_price:   " << material->get_material_unit_price() << " -> ";
        material->set_material_unit_price(21.0);
        std::cout << material->get_material_unit_price() << "\n";

        std::cout << "  set_material_quantity:     " << material->get_material_quantity() << " -> ";
        material->set_material_quantity(250.0);
        std::cout << material->get_material_quantity() << "\n";

        std::cout << "  set_material_critical:     " << material->get_material_critical() << " -> ";
        material->set_material_critical(60.0);
        std::cout << material->get_material_critical() << "\n";

        std::cout << "  set_material_measure_unit: " << material->get_material_measure_unit() << " -> ";
        material->set_material_measure_unit("ml");
        std::cout << material->get_material_measure_unit() << "\n";

        std::cout << "  set_material_category:     "
                  << Material::material_category_to_string(material->get_material_category()) << " -> ";
        material->set_material_category(Material::Category::others);
        std::cout << Material::material_category_to_string(material->get_material_category()) << "\n";

        std::cout << "  set_material_id:           " << material->get_material_id() << " -> ";
        material->set_material_id("MAT-002-V2");
        std::cout << material->get_material_id() << "\n";
    }

    // Provider setters
    std::cout << "\n[4b] Provider setters:\n";
    Provider *provider = inventory.find_provider_by_id("PRV-001");
    if (provider) {
        std::cout << "  set_provider_name:     " << provider->get_provider_name() << " -> ";
        provider->set_provider_name("LemnPro Group");
        std::cout << provider->get_provider_name() << "\n";

        std::cout << "  set_provider_phone:    " << provider->get_provider_phone() << " -> ";
        provider->set_provider_phone("0721000001");
        std::cout << provider->get_provider_phone() << "\n";

        std::cout << "  set_provider_email:    " << provider->get_provider_email() << " -> ";
        provider->set_provider_email("contact@lemnpro-group.ro");
        std::cout << provider->get_provider_email() << "\n";

        std::cout << "  set_provider_address:  " << provider->get_provider_address() << " -> ";
        provider->set_provider_address("Str. Noua 10, Cluj-Napoca");
        std::cout << provider->get_provider_address() << "\n";

        std::cout << "  set_provider_discount: " << provider->get_provider_discount() << " -> ";
        provider->set_provider_discount(8.0);
        std::cout << provider->get_provider_discount() << "\n";

        std::cout << "  set_provider_id:       " << provider->get_provider_id() << " -> ";
        provider->set_provider_id("PRV-001-V2");
        std::cout << provider->get_provider_id() << "\n";
    }

    // Order setters
    std::cout << "\n[4c] Order setters:\n";
    Order *order = inventory.find_order_by_id("ORD-003");
    if (order) {
        std::cout << "  set_order_status:       " << Order::order_status_to_string(order->get_order_status()) << " -> ";
        order->set_order_status(Order::Status::cancelled);
        std::cout << Order::order_status_to_string(order->get_order_status()) << "\n";

        std::cout << "  set_order_total_price:  " << order->get_order_total_price() << " -> ";
        order->set_order_total_price(630.0);
        std::cout << order->get_order_total_price() << "\n";

        std::cout << "  set_order_date:         " << order->get_order_date() << " -> ";
        order->set_order_date("25-03-2025");
        std::cout << order->get_order_date() << "\n";

        std::cout << "  set_order_provider_id:  " << order->get_order_provider_id() << " -> ";
        order->set_order_provider_id("PRV-002");
        std::cout << order->get_order_provider_id() << "\n";

        std::cout << "  set_order_id:           " << order->get_order_id() << " -> ";
        order->set_order_id("ORD-003-V2");
        std::cout << order->get_order_id() << "\n";
    }

    // Inventory setters
    std::cout << "\n[4d] Inventory setters:\n";
    std::cout << "  set_inventory_name:    " << inventory.get_inventory_name() << " -> ";
    inventory.set_inventory_name("Depozit Alpha V2");
    std::cout << inventory.get_inventory_name() << "\n";

    std::cout << "  set_inventory_address: " << inventory.get_inventory_address() << " -> ";
    inventory.set_inventory_address("Str. Noua 99, Cluj-Napoca");
    std::cout << inventory.get_inventory_address() << "\n";

    std::cout << "  set_inventory_phone:   " << inventory.get_inventory_phone() << " -> ";
    inventory.set_inventory_phone("0264999999");
    std::cout << inventory.get_inventory_phone() << "\n";

    std::cout << "  set_inventory_email:   " << inventory.get_inventory_email() << " -> ";
    inventory.set_inventory_email("alpha_v2@depot.ro");
    std::cout << inventory.get_inventory_email() << "\n";

    std::cout << "  set_inventory_id:      " << inventory.get_inventory_id() << " -> ";
    inventory.set_inventory_id("INV-ALPHA-V2");
    std::cout << inventory.get_inventory_id() << "\n";
}

void test_adaugare(Inventory &inventory) {
    print_separator("TEST 5: ADD MATERIAL / PROVIDER / ORDER");

    std::cout << "\n[5a] add_material:\n";
    const Material material_new("MAT-006", "Adeziv parchet", "kg", 30.0, 5.0, 22.0, Material::Category::finishes);
    std::cout << "  Material de adăugat:\n" << material_new;
    bool ok = inventory.add_material(material_new);
    std::cout << "  Rezultat: " << (ok ? "succes" : "EROARE — capacitate plina") << "\n";
    std::cout << "  Materiale count: " << inventory.get_inventory_materials_count() << "\n";

    std::cout << "\n[5b] add_provider:\n";
    const char *pm[] = { "MAT-006" };
    const Provider provider_new("PRV-004", "AdeziviRom SRL", "0755999888", "contact@adezivrom.ro", "Str. Chimica 3, Ploiesti", pm, 1, 6.0);
    std::cout << "  Furnizor de adăugat:\n" << provider_new;
    ok = inventory.add_provider(provider_new);
    std::cout << "  Rezultat: " << (ok ? "succes" : "EROARE — capacitate plina") << "\n";
    std::cout << "  Providers count: " << inventory.get_inventory_providers_count() << "\n";

    std::cout << "\n[5c] add_order:\n";
    const char *order_materials[] = { "MAT-003", "MAT-004" };
    constexpr double order_quantities[] = { 15.0, 10.0 };
    const Order order_new("ORD-004", "PRV-003", order_materials, 2, order_quantities, 2, 805.0, "24-03-2025");
    std::cout << "  Comandă de adăugat:\n" << order_new;
    ok = inventory.add_order(order_new);
    std::cout << "  Rezultat: " << (ok ? "succes" : "EROARE — capacitate plina") << "\n";
    std::cout << "  Orders count: " << inventory.get_inventory_orders_count() << "\n";
}

void test_consum(Inventory &inventory) {
    print_separator("TEST 6: CONSUME_MATERIAL");

    print_materials_list(inventory);

    // Consum valid
    std::cout << "\n[6a] consume_material(\"MAT-001\", 2.0): ";
    std::cout << (inventory.consume_material("MAT-001", 2.0) ? "succes" : "EROARE") << "\n";

    std::cout << "[6b] consume_material(\"MAT-003\", 25.0): ";
    std::cout << (inventory.consume_material("MAT-003", 25.0) ? "succes" : "EROARE") << "\n";

    std::cout << "[6c] consume_material(\"MAT-005\", 150.0): ";
    std::cout << (inventory.consume_material("MAT-005", 150.0) ? "succes" : "EROARE") << "\n";

    // Consum care depășește stocul (eroare așteptată)
    std::cout << "[6d] consume_material(\"MAT-004\", 9999.0) [stoc insuficient, eroare asteptata]: ";
    std::cout << (inventory.consume_material("MAT-004", 9999.0) ? "succes" : "EROARE asteptata — stoc insuficient") << "\n";

    // ID inexistent (eroare așteptată)
    std::cout << "[6e] consume_material(\"MAT-999\", 1.0) [ID inexistent, eroare asteptata]: ";
    std::cout << (inventory.consume_material("MAT-999", 1.0) ? "succes" : "EROARE asteptata — ID negasit") << "\n";

    std::cout << "\n  Materiale dupa consum:\n";
    print_materials_list(inventory);
}

void test_receptie(Inventory &inventory) {
    print_separator("TEST 7: RECEIVE_ORDER");

    print_orders_list(inventory);
    print_materials_list(inventory);

    // Recepție comandă deja livrată (eroare așteptată)
    std::cout << "\n[7a] receive_order(ORD-001) — status delivered, eroare asteptata:\n";
    Order *order1 = inventory.find_order_by_id("ORD-001");
    if (order1) {
        const bool ok = inventory.receive_order(order1);
        std::cout << "  Rezultat: " << (ok ? "succes" : "EROARE asteptata — nu este pending") << "\n";
    } else {
        std::cout << "  [EROARE] Comanda ORD-001 negasita.\n";
    }

    // Recepție comandă pending
    std::cout << "\n[7b] receive_order(ORD-002) — status pending:\n";
    Order *order2 = inventory.find_order_by_id("ORD-002");
    if (order2) {
        const bool ok = inventory.receive_order(order2);
        std::cout << "  Rezultat: " << (ok ? "succes — stocuri actualizate" : "EROARE") << "\n";
    } else {
        std::cout << "  [EROARE] Comanda ORD-002 negasita.\n";
    }

    std::cout << "\n  Materiale dupa receptie ORD-002:\n";
    print_materials_list(inventory);
}

void test_cautare(const Inventory &inventory) {
    print_separator("TEST 8: FIND BY ID (INSTANTA SI STATIC)");

    std::cout << "\n[8a] find_material_by_id(\"MAT-003\") [instanta]:\n";
    const Material *material = inventory.find_material_by_id("MAT-003");
    if (material) std::cout << *material; else std::cout << "  negasit\n";

    std::cout << "[8b] find_material_by_id(\"MAT-999\") [instanta, ID inexistent]:\n";
    material = inventory.find_material_by_id("MAT-999");
    std::cout << (material ? "  gasit" : "  EROARE asteptata — negasit") << "\n";

    std::cout << "\n[8c] find_provider_by_id(\"PRV-002\") [instanta]:\n";
    const Provider *provider = inventory.find_provider_by_id("PRV-002");
    if (provider) std::cout << *provider; else std::cout << "  negasit\n";

    std::cout << "[8d] find_order_by_id(\"ORD-001\") [instanta]:\n";
    const Order *order = inventory.find_order_by_id("ORD-001");
    if (order) std::cout << *order; else std::cout << "  negasit\n";

    std::cout << "\n[8e] Inventory::find_material_by_id(\"MAT-004\") [static]:\n";
    material = Inventory::find_material_by_id(inventory.get_inventory_materials(), inventory.get_inventory_materials_count(), "MAT-004");
    if (material) std::cout << *material; else std::cout << "  negasit\n";

    std::cout << "[8f] Inventory::find_provider_by_id(\"PRV-003\") [static]:\n";
    provider = Inventory::find_provider_by_id(inventory.get_inventory_providers(), inventory.get_inventory_providers_count(), "PRV-003");
    if (provider) std::cout << *provider; else std::cout << "  negasit\n";

    std::cout << "[8g] Inventory::find_order_by_id(\"ORD-002\") [static]:\n";
    order = Inventory::find_order_by_id(inventory.get_inventory_orders(), inventory.get_inventory_orders_count(), "ORD-002");
    if (order) std::cout << *order; else std::cout << "  negasit\n";
}

void test_sortare(Inventory &inventory) {
    print_separator("TEST 9: SORTARE");

    std::cout << "\n[9a] sort_materials_by_name_ascending:\n";
    inventory.sort_materials_by_name_ascending();
    print_materials_list(inventory);

    std::cout << "\n[9b] sort_materials_by_name_descending:\n";
    inventory.sort_materials_by_name_descending();
    print_materials_list(inventory);

    std::cout << "\n[9c] sort_materials_by_quantity_ascending:\n";
    inventory.sort_materials_by_quantity_ascending();
    print_materials_list(inventory);

    std::cout << "\n[9d] sort_materials_by_quantity_descending:\n";
    inventory.sort_materials_by_quantity_descending();
    print_materials_list(inventory);

    std::cout << "\n[9e] sort_orders_by_total_price_ascending:\n";
    inventory.sort_orders_by_total_price_ascending();
    print_orders_list(inventory);

    std::cout << "\n[9f] sort_orders_by_total_price_descending:\n";
    inventory.sort_orders_by_total_price_descending();
    print_orders_list(inventory);

    // Versiuni statice — pe copii separate, inventarul original rămâne nemodificat
    std::cout << "\n[9g] Inventory::sort_materials_by_quantity_descending [static, pe copie]:\n";
    const int materials_count = inventory.get_inventory_materials_count();
    auto *material_copy = new Material[materials_count];
    for (int i = 0; i < materials_count; i++)
        material_copy[i] = inventory.get_inventory_materials()[i];
    Inventory::sort_materials_by_quantity_descending(material_copy, materials_count);
    for (int i = 0; i < materials_count; i++)
        std::cout << material_copy[i];
    delete[] material_copy;

    std::cout << "\n[9h] Inventory::sort_orders_by_total_price_ascending [static, pe copie]:\n";
    const int orders_count = inventory.get_inventory_orders_count();
    auto *order_copy = new Order[orders_count];
    for (int i = 0; i < orders_count; i++)
        order_copy[i] = inventory.get_inventory_orders()[i];
    Inventory::sort_orders_by_total_price_ascending(order_copy, orders_count);
    for (int i = 0; i < orders_count; i++)
        std::cout << order_copy[i];
    delete[] order_copy;
}

void test_filtre(const Inventory &inventory) {
    print_separator("TEST 10: FILTRE");

    // get_orders_by_provider_id
    int cnt = 0;

    std::cout << "\n[10a] get_orders_by_provider_id(\"PRV-001\"):\n";
    const Order *order_provider1 = inventory.get_orders_by_provider_id("PRV-001", cnt);
    std::cout << "  Gasite: " << cnt << "\n";
    for (int i = 0; i < cnt; i++) std::cout << order_provider1[i];
    delete[] order_provider1;

    std::cout << "\n[10b] get_orders_by_provider_id(\"PRV-002\"):\n";
    const Order *order_provider2 = inventory.get_orders_by_provider_id("PRV-002", cnt);
    std::cout << "  Gasite: " << cnt << "\n";
    for (int i = 0; i < cnt; i++) std::cout << order_provider2[i];
    delete[] order_provider2;

    std::cout << "\n[10c] get_orders_by_provider_id(\"PRV-999\") [ID inexistent]:\n";
    const Order *order_provider3 = inventory.get_orders_by_provider_id("PRV-999", cnt);
    std::cout << "  Gasite: " << cnt << "\n";
    delete[] order_provider3;

    // get_critical_materials
    std::cout << "\n[10d] get_critical_materials():\n";
    const Material *critical = inventory.get_critical_materials(cnt);
    std::cout << "  Materiale la nivel critic: " << cnt << "\n";
    for (int i = 0; i < cnt; i++) std::cout << critical[i];
    delete[] critical;

    // get_materials_by_category
    constexpr Material::Category categories[] = { Material::Category::wood, Material::Category::metal, Material::Category::insulation, Material::Category::finishes, Material::Category::others };
    const char *categories_converted[] = { "wood", "metal", "insulation", "finishes", "others" };

    for (int c = 0; c < 5; c++) {
        const Material *category_materials = inventory.get_materials_by_category(categories[c], cnt);
        std::cout << "\n[10e." << (c+1) << "] get_materials_by_category(" << categories_converted[c]
                  << "): " << cnt << " material(e)\n";
        for (int i = 0; i < cnt; i++) std::cout << category_materials[i];
        delete[] category_materials;
    }
}

void test_valoare(const Inventory &inventory) {
    print_separator("TEST 11: CALCULATE_INVENTORY_VALUE");
    print_materials_list(inventory);
    std::cout << "\n  Valoarea totala a stocului: "
              << inventory.calculate_inventory_value() << " RON\n";
}

void test_swap(const Inventory &inventory) {
    print_separator("TEST 12: SWAP");

    // Material swap
    if (inventory.get_inventory_materials_count() >= 2) {
        Material &material0 = inventory.get_inventory_materials()[0];
        Material &material1 = inventory.get_inventory_materials()[1];
        std::cout << "\n[12a] Material::swap([0],[1]):\n";
        std::cout << "  Inainte: [0]=" << material0.get_material_name()
                  << "  [1]=" << material1.get_material_name() << "\n";
        Material::swap(material0, material1);
        std::cout << "  Dupa:    [0]=" << inventory.get_inventory_materials()[0].get_material_name()
                  << "  [1]=" << inventory.get_inventory_materials()[1].get_material_name() << "\n";
    }

    // Provider swap
    if (inventory.get_inventory_providers_count() >= 2) {
        Provider &provider0 = inventory.get_inventory_providers()[0];
        Provider &provider1 = inventory.get_inventory_providers()[1];
        std::cout << "\n[12b] Provider::swap([0],[1]):\n";
        std::cout << "  Inainte: [0]=" << provider0.get_provider_name() << "  [1]=" << provider1.get_provider_name() << "\n";
        Provider::swap(provider0, provider1);
        std::cout << "  Dupa:    [0]=" << inventory.get_inventory_providers()[0].get_provider_name() << "  [1]=" << inventory.get_inventory_providers()[1].get_provider_name() << "\n";
    }

    // Order swap
    if (inventory.get_inventory_orders_count() >= 2) {
        Order &order0 = inventory.get_inventory_orders()[0];
        Order &order1 = inventory.get_inventory_orders()[1];
        std::cout << "\n[12c] Order::swap([0],[1]):\n";
        std::cout << "  Inainte: [0]=" << order0.get_order_id() << "  [1]=" << order1.get_order_id() << "\n";
        Order::swap(order0, order1);
        std::cout << "  Dupa:    [0]=" << inventory.get_inventory_orders()[0].get_order_id() << "  [1]=" << inventory.get_inventory_orders()[1].get_order_id() << "\n";
    }
}

void test_enum_to_string() {
    print_separator("TEST 13: ENUM TO STRING");

    std::cout << "\n[13a] Material::material_category_to_string:\n";
    std::cout << "  wood:       " << Material::material_category_to_string(Material::Category::wood)       << "\n";
    std::cout << "  metal:      " << Material::material_category_to_string(Material::Category::metal)      << "\n";
    std::cout << "  insulation: " << Material::material_category_to_string(Material::Category::insulation) << "\n";
    std::cout << "  finishes:   " << Material::material_category_to_string(Material::Category::finishes)   << "\n";
    std::cout << "  others:     " << Material::material_category_to_string(Material::Category::others)     << "\n";

    std::cout << "\n[13b] Order::order_status_to_string:\n";
    std::cout << "  pending:   " << Order::order_status_to_string(Order::Status::pending)   << "\n";
    std::cout << "  delivered: " << Order::order_status_to_string(Order::Status::delivered) << "\n";
    std::cout << "  cancelled: " << Order::order_status_to_string(Order::Status::cancelled) << "\n";
    std::cout << "  unknown:   " << Order::order_status_to_string(Order::Status::unknown)   << "\n";
}

int main() {
    // Construim cele două inventare demo o singură dată
    Inventory inventory_alpha = build_inventory_alpha();
    Inventory inventory_beta  = build_inventory_beta();

    print_separator("SUITE DE TESTE — SISTEM INVENTAR");
    std::cout << "  inventory_alpha: " << inventory_alpha.get_inventory_name()
              << " (" << inventory_alpha.get_inventory_id() << ")"
              << "  |  " << inventory_alpha.get_inventory_materials_count() << " materials"
              << " / " << inventory_alpha.get_inventory_providers_count() << " providers"
              << " / " << inventory_alpha.get_inventory_orders_count() << " orders\n";
    std::cout << "  inventory_beta:  " << inventory_beta.get_inventory_name()
              << " (" << inventory_beta.get_inventory_id() << ")"
              << "  |  " << inventory_beta.get_inventory_materials_count() << " materials"
              << " / " << inventory_beta.get_inventory_providers_count() << " providers"
              << " / " << inventory_beta.get_inventory_orders_count() << " orders\n";

    test_constructori(inventory_alpha, inventory_beta);
    test_atribuire(inventory_alpha);
    test_egalitate(inventory_alpha);
    test_enum_to_string();

    // Fiecare test primește o copie proaspătă pentru a nu afecta testele ulterioare
    Inventory inventory_copy = inventory_alpha;
    test_getters_setters(inventory_copy);

    inventory_copy = inventory_alpha;
    test_adaugare(inventory_copy);

    inventory_copy = inventory_alpha;
    test_consum(inventory_copy);

    inventory_copy = inventory_alpha;
    test_receptie(inventory_copy);

    test_cautare(inventory_alpha);

    inventory_copy = inventory_alpha;
    test_sortare(inventory_copy);

    test_filtre(inventory_alpha);
    test_valoare(inventory_alpha);

    inventory_copy = inventory_alpha;
    test_swap(inventory_copy);

    print_separator("TESTE PE INVENTORY_BETA");
    test_cautare(inventory_beta);

    inventory_copy = inventory_beta;
    test_sortare(inventory_copy);

    test_filtre(inventory_beta);
    test_valoare(inventory_beta);

    print_separator("TOATE TESTELE AU FOST RULATE");
    return 0;
}