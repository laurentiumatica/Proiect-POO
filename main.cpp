#include "inventory.h"
#include <iostream>

/*
 * SISTEM DE MANAGEMENT INVENTAR - MATERIALE DE CONSTRUCTII
 *
 * PROBLEME REZOLVATE:
 * - Monitorizare stocuri materiale
 * - Gestionare furnizori si relatiile cu acestia
 * - Management complet comenzi (creare, urmarire, procesare)
 * - Raportare (valoare inventar, filtrare categorii, sortare)
 * - Actualizare automata stocuri la consum si receptie comenzi
 *
 * FUNCTIONALITATI:
 * - operatii CRUD pentru materiale, furnizori si comenzi
 * - Receptie comenzi cu adaugare automata de materiale noi
 * - Consum materiale cu validare de cantitate
 * - Identificare stocuri critice
 * - Calcul valoare totala inventar
 * - Sortare/filtrare pe multiple criterii
 */

void print_separator(const char *title) {
    std::cout << "\n====================================================\n";
    std::cout << "  " << title << "\n";
    std::cout << "====================================================\n";
}

int main() {
    const Material material_1("MAT-001", "Cherestea stejar", "m3", 12.5, 3.0, 850.0, Material::Category::wood);
    const Material material_2("MAT-002", "Profil U otel", "m", 200.0, 50.0, 18.5, Material::Category::metal);
    const Material material_3("MAT-003", "Vata minerala", "m2", 80.0, 20.0, 35.0, Material::Category::insulation);
    const Material material_4("MAT-004", "Vopsea alba interior", "l", 45.0, 10.0, 28.0, Material::Category::finishes);
    const Material materials[] = {material_1, material_2, material_3, material_4};

    const char *provider_1_materials[] = {"MAT-001", "MAT-003"};
    const char *provider_2_materials[] = {"MAT-002", "MAT-004"};
    const Provider provider_1("PRV-001", "LemnPro SRL", "0721111111", "contact@lemnpro.ro", "Str. Padurii 10, Cluj", provider_1_materials, 2);
    const Provider provider_2("PRV-002", "MetalTech SA", "0733222222", "vanzari@metaltech.ro", "Bd. Industriei 45, Buc", provider_2_materials, 2);
    const Provider providers[] = {provider_1, provider_2};

    const char *order_1_materials[] = {"MAT-001", "MAT-003"};
    constexpr double order_1_quantities[] = {5.0, 30.0};
    const char *order_2_materials[] = {"MAT-002"};
    constexpr double order_2_quantities[] = {100.0};
    const Order order_1("ORD-001", "PRV-001", order_1_materials, 2, order_1_quantities, 5300.0, "10-01-2025", Order::Status::delivered);
    const Order order_2("ORD-002", "PRV-002", order_2_materials, 1, order_2_quantities, 1850.0, "15-02-2025", Order::Status::pending);
    const Order orders[] = {order_1, order_2};

    Inventory inventory("INV-001", "Depozit Central", "Str. Depozitului 1, Cluj", "0264111111", "depot@central.ro", materials, providers, orders, 4, 2, 2);

    Inventory inventory_copy(inventory);

    print_separator("1. AFISARE MATERIAL (operator<<)");
    std::cout << material_1;

    print_separator("2. AFISARE PROVIDER (operator<<)");
    std::cout << provider_1;

    print_separator("3. AFISARE ORDER (operator<<)");
    std::cout << order_1;

    print_separator("4. AFISARE INVENTORY (operator<<)");
    std::cout << inventory;

    print_separator("5. COPY CONSTRUCTOR & OPERATOR==");
    std::cout << "  Original == Copie: " << (inventory == inventory_copy ? "DA" : "NU") << "\n";
    Inventory::update_inventory(inventory_copy, Inventory::update_inventory_name,"Depozit copie");
    std::cout << "  Dupa modificare copie, Original != Copie: " << (inventory != inventory_copy ? "DA" : "NU") << "\n";

    print_separator("6. OPERATOR= (atribuire)");
    inventory_copy = inventory;
    std::cout << "  Dupa operator=, Original == Copie: " << (inventory == inventory_copy ? "DA" : "NU") << "\n";

    print_separator("7. GETTERS / UPDATE-URI (SETTERS)");
    Material *material_found = inventory.find_material_by_id("MAT-002");
    if (material_found) {
        std::cout << "  MAT-002 inainte: " << material_found->get_material_name()
                  << ", qty=" << material_found->get_material_quantity()
                  << ", price=" << material_found->get_material_unit_price() << "\n";
        Material::update_material(*material_found, Material::update_material_name, "Profil U otel zincat");
        constexpr double new_quantity = 250;
        constexpr double new_price = 21.0;
        Material::update_material(*material_found, Material::update_material_quantity, &new_quantity);
        Material::update_material(*material_found, Material::update_material_unit_price, &new_price);
        std::cout << "  MAT-002 dupa:   " << material_found->get_material_name()
                  << ", qty=" << material_found->get_material_quantity()
                  << ", price=" << material_found->get_material_unit_price() << "\n";
    }

    print_separator("8. ADD MATERIAL / PROVIDER / ORDER");
    const Material material_new("MAT-005", "Adeziv parchet", "kg", 30.0, 5.0, 22.0, Material::Category::finishes);
    inventory.add_material(material_new);
    std::cout << "  Materiale dupa add: " << inventory.get_inventory_materials_count() << "\n";

    const char *provider_new_materials[] = {"MAT-005"};
    const Provider provider_new("PRV-003", "AdeziviRom SRL", "0755999888", "contact@adezivrom.ro", "Str. Chimica 3, Ploiesti", provider_new_materials, 1);
    inventory.add_provider(provider_new);
    std::cout << "  Furnizori dupa add: " << inventory.get_inventory_providers_count() << "\n";

    const char *order_new_materials[] = {"MAT-005"};
    constexpr double order_new_quantities[] = {20.0};
    const Order order_new("ORD-003", "PRV-003", order_new_materials, 1, order_new_quantities, 440.0, "24-03-2025", Order::Status::pending);
    inventory.add_order(order_new);
    std::cout << "  Comenzi dupa add:  " << inventory.get_inventory_orders_count() << "\n";

    print_separator("9. CONSUME_MATERIAL");
    std::cout << "  MAT-001 qty inainte: " << inventory.find_material_by_id("MAT-001")->get_material_quantity() << "\n";
    inventory.consume_material("MAT-001", 2.0);
    std::cout << "  MAT-001 qty dupa:    " << inventory.find_material_by_id("MAT-001")->get_material_quantity() << "\n";
    inventory.consume_material("MAT-001", 99999.0);
    std::cout << "  MAT-001 qty dupa consum invalid: " << inventory.find_material_by_id("MAT-001")->get_material_quantity() << " (neschimbat)\n";

    print_separator("10. RECEIVE_ORDER");
    Order *order_found = inventory.find_order_by_id("ORD-002");
    if (order_found) {
        std::cout << "  ORD-002 status inainte: " << Order::order_status_to_string(order_found->get_order_status()) << "\n";
        inventory.receive_order(order_found);
        std::cout << "  ORD-002 status dupa:    " << Order::order_status_to_string(order_found->get_order_status()) << "\n";
        std::cout << "  MAT-002 qty dupa receptie: " << inventory.find_material_by_id("MAT-002")->get_material_quantity() << "\n";
        inventory.receive_order(order_found);
        std::cout << "  Al doilea apel (delivered): fara efect\n";
    }

    print_separator("11. FIND BY ID");
    const Material *material_find_test = inventory.find_material_by_id("MAT-003");
    std::cout << "  MAT-003: " << (material_find_test ? material_find_test->get_material_name() : "negasit") << "\n";
    std::cout << "  MAT-999: " << (inventory.find_material_by_id("MAT-999") ? "gasit" : "negasit (asteptat)") << "\n";

    const Provider *provider_find_test = inventory.find_provider_by_id("PRV-001");
    std::cout << "  PRV-001: " << (provider_find_test ? provider_find_test->get_provider_name() : "negasit") << "\n";

    const Order *order_find_test = inventory.find_order_by_id("ORD-001");
    std::cout << "  ORD-001: " << (order_find_test ? order_find_test->get_order_id() : "negasit") << "\n";

    print_separator("12. SORTARE");
    inventory.sort_materials_by_name_ascending();
    std::cout << "  Materiale sortate A-Z:\n";
    for (int i = 0; i < inventory.get_inventory_materials_count(); i++)
        std::cout << "    " << inventory.get_inventory_materials()[i].get_material_name() << "\n";

    inventory.sort_materials_by_quantity_descending();
    std::cout << "  Materiale sortate qty DESC:\n";
    for (int i = 0; i < inventory.get_inventory_materials_count(); i++)
        std::cout << "    " << inventory.get_inventory_materials()[i].get_material_name()
                  << " (" << inventory.get_inventory_materials()[i].get_material_quantity() << ")\n";

    inventory.sort_orders_by_total_price_ascending();
    std::cout << "  Comenzi sortate pret ASC:\n";
    for (int i = 0; i < inventory.get_inventory_orders_count(); i++)
        std::cout << "    " << inventory.get_inventory_orders()[i].get_order_id()
                  << " -> " << inventory.get_inventory_orders()[i].get_order_total_price() << " RON\n";

    print_separator("13. FILTRE");
    int result_count = 0;

    Order *orders_by_provider = inventory.get_orders_by_provider_id("PRV-001", result_count);
    std::cout << "  Comenzi PRV-001: " << result_count << "\n";
    delete[] orders_by_provider;

    Material *critical_materials = inventory.get_critical_materials(result_count);
    std::cout << "  Materiale la stoc critic: " << result_count << "\n";
    for (int i = 0; i < result_count; i++)
        std::cout << "    " << critical_materials[i].get_material_name() << "\n";
    delete[] critical_materials;

    Material *materials_by_category = inventory.get_materials_by_category(Material::Category::metal, result_count);
    std::cout << "  Materiale metal: " << result_count << "\n";
    for (int i = 0; i < result_count; i++)
        std::cout << "    " << materials_by_category[i].get_material_name() << "\n";
    delete[] materials_by_category;

    print_separator("14. CALCULATE_INVENTORY_VALUE");
    std::cout << "  Valoare totala stoc: " << inventory.calculate_inventory_value() << " RON\n";

    print_separator("15. SWAP");
    if (inventory.get_inventory_materials_count() >= 2) {
        Material *materials_array = inventory.get_inventory_materials();
        std::cout << "  Inainte: [0]=" << materials_array[0].get_material_name() << "  [1]=" << materials_array[1].get_material_name() << "\n";
        Material::swap(materials_array[0], materials_array[1]);
        std::cout << "  Dupa:    [0]=" << materials_array[0].get_material_name() << "  [1]=" << materials_array[1].get_material_name() << "\n";
    }

    print_separator("FINALIZAT");
    return 0;
}