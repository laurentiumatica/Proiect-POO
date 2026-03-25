// INVENTORY

// Pentru implementări și logică viitoare
// // Structuri imbricate
// // Folosite pentru a grupa un tablou de obiecte noi și dimensiunea acestuia, facilitând transmiterea datelor către funcțiile de update
// struct MaterialsUpdate {
//   Material *new_materials;
//   int new_materials_count;
// };
//
// struct ProvidersUpdate {
//   Provider *new_providers;
//   int new_providers_count;
// };
//
// struct OrdersUpdate {
//   Order *new_orders;
//   int new_orders_count;
// };
//
// // Funcții statice pentru actualizarea specifică a atributelor prin callback-uri
// static void update_inventory_id(Inventory &inventory, const void *new_id);
// static void update_inventory_name(Inventory &inventory, const void *new_name);
// static void update_inventory_address(Inventory &inventory, const void *new_address);
// static void update_inventory_phone(Inventory &inventory, const void *new_phone);
// static void update_inventory_email(Inventory &inventory, const void *new_email);
// static void update_inventory_materials(Inventory &inventory, const void *new_data);
// static void update_inventory_providers(Inventory &inventory, const void *new_data);
// static void update_inventory_orders(Inventory &inventory, const void *new_data);
//
// // Funcție generică delegat
// // Primește instanța, pointerul către funcția de mai sus dorită și valoarea nouă
// static void update_inventory(Inventory &inventory, void (*func)(Inventory &, const void *), const void *new_data);

// // Metode de update (pentru implementări și logică viitoare)
// void Inventory::update_inventory_id(Inventory &inventory, const void *new_id) {
//     inventory.set_inventory_id(static_cast<const char *>(new_id));
// }
//
// void Inventory::update_inventory_name(Inventory &inventory, const void *new_name) {
//     inventory.set_inventory_name(static_cast<const char *>(new_name));
// }
//
// void Inventory::update_inventory_address(Inventory &inventory, const void *new_address) {
//     inventory.set_inventory_address(static_cast<const char *>(new_address));
// }
//
// void Inventory::update_inventory_phone(Inventory &inventory, const void *new_phone) {
//     inventory.set_inventory_phone(static_cast<const char *>(new_phone));
// }
//
// void Inventory::update_inventory_email(Inventory &inventory, const void *new_email) {
//     inventory.set_inventory_email(static_cast<const char *>(new_email));
// }
//
// void Inventory::update_inventory_materials(Inventory &inventory, const void *new_data) {
//     const auto *u = static_cast<const MaterialsUpdate *>(new_data);
//     if (u->new_materials_count > inventory.materials_capacity) return; // Validare
//     inventory.set_inventory_materials(u->new_materials, u->new_materials_count);
// }
//
// void Inventory::update_inventory_providers(Inventory &inventory, const void *new_data) {
//     const auto *u = static_cast<const ProvidersUpdate *>(new_data);
//     if (u->new_providers_count > inventory.providers_capacity) return;
//     inventory.set_inventory_providers(u->new_providers, u->new_providers_count);
// }
//
// void Inventory::update_inventory_orders(Inventory &inventory,
//                                         const void *new_data) {
//     const auto *u = static_cast<const OrdersUpdate *>(new_data);
//     if (u->new_orders_count > inventory.orders_capacity) return;
//     inventory.set_inventory_orders(u->new_orders, u->new_orders_count);
// }
//
// void Inventory::update_inventory(Inventory &inventory, void (*func)(Inventory &, const void *), const void *new_data) {
//     func(inventory, new_data);
// }

// // Funcții statice de căutare (supraîncărcare)
// // Nu depind de obiectul Inventory curent
// // Primesc direct un tablou de obiecte în care să caute
// static Material *find_material_by_id(Material *materials, const int &materials_count, const char *find_id);
// static Provider *find_provider_by_id(Provider *providers, const int &providers_count, const char *find_id);
// static Order *find_order_by_id(Order *orders, const int &orders_count, const char *find_id);
//

// Variante statice ale metodelor de sortare
// Utile când vrem să sortăm un tablou oarecare de obiecte
static void sort_materials_by_name_ascending(Material *materials, const int &materials_count);
static void sort_materials_by_name_descending(Material *materials, const int &materials_count);
static void sort_materials_by_quantity_ascending(Material *materials, const int &materials_count);
static void sort_materials_by_quantity_descending(Material *materials, const int &materials_count);
static void sort_orders_by_total_price_ascending(Order *orders, const int &orders_count);
static void sort_orders_by_total_price_descending(Order *orders, const int &orders_count);

Material *Inventory::find_material_by_id(Material *materials, const int &materials_count, const char *find_id) {
for (int i = 0; i < materials_count; i++)
if (strcmp(materials[i].get_material_id(), find_id) == 0)
return &materials[i];

    return nullptr;
}

Provider *Inventory::find_provider_by_id(Provider *providers, const int &providers_count, const char *find_id) {
for (int i = 0; i < providers_count; i++)
if (strcmp(providers[i].get_provider_id(), find_id) == 0)
return &providers[i];

    return nullptr;
}

Order *Inventory::find_order_by_id(Order *orders, const int &orders_count, const char *find_id) {
for (int i = 0; i < orders_count; i++)
if (strcmp(orders[i].get_order_id(), find_id) == 0)
return &orders[i];
return nullptr;
}

// Variante statice ale sortărilor
void Inventory::sort_materials_by_name_ascending(Material *materials, const int &materials_count) {
for (int i = 0; i < materials_count - 1; i++)
for (int j = i + 1; j < materials_count; j++)
if (strcmp(materials[i].get_material_name(), materials[j].get_material_name()) > 0)
Material::swap(materials[i], materials[j]);
}

void Inventory::sort_materials_by_name_descending(Material *materials, const int &materials_count) {
for (int i = 0; i < materials_count - 1; i++)
for (int j = i + 1; j < materials_count; j++)
if (strcmp(materials[i].get_material_name(), materials[j].get_material_name()) < 0)
Material::swap(materials[i], materials[j]);
}

void Inventory::sort_materials_by_quantity_ascending(
Material *materials, const int &materials_count) {
for (int i = 0; i < materials_count - 1; i++)
for (int j = i + 1; j < materials_count; j++)
if (materials[i].get_material_quantity() > materials[j].get_material_quantity())
Material::swap(materials[i], materials[j]);
}

void Inventory::sort_materials_by_quantity_descending(
Material *materials, const int &materials_count) {
for (int i = 0; i < materials_count - 1; i++)
for (int j = i + 1; j < materials_count; j++)
if (materials[i].get_material_quantity() < materials[j].get_material_quantity())
Material::swap(materials[i], materials[j]);
}

void Inventory::sort_orders_by_total_price_ascending(Order *orders, const int &orders_count) {
for (int i = 0; i < orders_count - 1; i++)
for (int j = i + 1; j < orders_count; j++)
if (orders[i].get_order_total_price() > orders[j].get_order_total_price())
Order::swap(orders[i], orders[j]);
}

void Inventory::sort_orders_by_total_price_descending(Order *orders, const int &orders_count) {
for (int i = 0; i < orders_count - 1; i++)
for (int j = i + 1; j < orders_count; j++)
if (orders[i].get_order_total_price() < orders[j].get_order_total_price())
Order::swap(orders[i], orders[j]);
}


// MATERIALS

// // Metode statice (pentru implementari si logica viitoare)
// // Acestea aparțin clasei în sine, nu unei instanțe individuale
// // Deoarece nu au un obiect curent asociat, trebuie să primească instanța pe care o modifică prin referință
// static void update_material_id(Material &material, const void *new_id);
// static void update_material_name(Material &material, const void *new_name);
// static void update_material_measure_unit(Material &material, const void *new_measure_unit);
// static void update_material_critical(Material &material, const void *new_critical);
// static void update_material_unit_price(Material &material, const void *new_unit_price);
// static void update_material_quantity(Material &material, const void *new_quantity);
// static void update_material_category(Material &material, const void *new_category);
//
// // Metodă de actualizare generică
// // Primește acțiunea exactă sub formă de pointer către o funcție (un callback) din lista de mai sus
// static void update_material(Material &material, void (*func)(Material &, const void *), const void *new_value);

// // Metode auxiliare statice
// void Material::update_material_id(Material &material, const void *new_value) {
//   material.set_material_id(static_cast<const char *>(new_value)); // Apelăm setter-ul peste instanța concretă, cu un type casting explicit pe noul atribut
// }
//
// void Material::update_material_name(Material &material, const void *new_name) {
//   material.set_material_name(static_cast<const char *>(new_name));
// }
//
// void Material::update_material_measure_unit(Material &material, const void *new_measure_unit) {
//   material.set_material_measure_unit(static_cast<const char *>(new_measure_unit));
// }
//
// void Material::update_material_critical(Material &material, const void *new_critical) {
//   material.set_material_critical(*static_cast<const double *>(new_critical));
// }
//
// void Material::update_material_unit_price(Material &material, const void *new_unit_price) {
//   material.set_material_unit_price(*static_cast<const double *>(new_unit_price));
// }
//
// void Material::update_material_quantity(Material &material, const void *new_quantity) {
//   material.set_material_quantity(*static_cast<const double *>(new_quantity));
// }
//
// void Material::update_material_category(Material &material, const void *new_category) {
//   material.set_material_category(*static_cast<const Category *>(new_category));
// }
//
// // Metodă generică delegat. Primește instanța, funcția exactă de update ce trebuie apelată și noile date
// void Material::update_material(Material &material, void (*func)(Material &, const void *), const void *new_value) {
//   func(material, new_value);
// }

// PROVIDERS

// // Metode de tip static pentru update (pentru implementări și logică viitoare)
// // Acestea aparțin clasei în sine, nu unei instanțe
// // Modifică atributele unui obiect specificat, primit prin parametru
// static void update_provider_id(Provider &provider, const void *new_id);
// static void update_provider_name(Provider &provider, const void *new_name);
// static void update_provider_phone(Provider &provider, const void *new_phone);
// static void update_provider_email(Provider &provider, const void *new_email);
// static void update_provider_address(Provider &provider, const void *new_address);
// static void update_provider_discount(Provider &provider, const void *new_discount);
//
// // Structură imbricată
// // Folosită exclusiv pentru a grupa lista de ID-uri și numărul lor într-un singur parametru
// struct MaterialsUpdate {
//     const char **ids; // Tablou cu noile ID-uri de materiale
//     int count; // Dimensiunea tabloului de mai sus
// };
//
// // Metodă statică dedicată actualizării listei de materiale, folosind structura definită anterior
// static void update_provider_materials(Provider &provider, const void *data);
//
// // Metodă generică pentru actualizări
// // Primește instanța țintă, un pointer către funcția de update (callback) și noua valoare
// static void update_provider(Provider &provider, void (*func)(Provider &, const void *), const void *new_value);

// // Metode statice delegate pentru actualizarea stării unui object
// void Order::update_order_id(Order &order, const void *new_data) {
//     order.set_order_id(static_cast<const char *>(new_data));
// }
//
// void Order::update_order_provider_id(Order &order, const void *new_data) {
//     order.set_order_provider_id(static_cast<const char *>(new_data));
// }
//
// void Order::update_order_date(Order &order, const void *new_data) {
//     order.set_order_date(static_cast<const char *>(new_data));
// }
//
// void Order::update_order_total_price(Order &order, const void *new_data) {
//     order.set_order_total_price(*static_cast<const double *>(new_data));
// }
//
// void Order::update_order_status(Order &order, const void *new_data) {
//     order.set_status(*static_cast<const Status *>(new_data));
// }
//
// void Order::update_order_materials(Order &order, const void *new_data) {
//     const auto *u = static_cast<const OrderUpdate *>(new_data);
//     order.set_order_materials_id(u->ids, u->count);
//     order.set_order_quantities(u->quantities, u->count);
// }
//
// // Metodă generică delegat. Primește instanța, funcția exactă de update ce trebuie apelată și noile date
// void Order::update_order(Order &order, void (*func)(Order &, const void *),
//                          const void *new_value) {
//     func(order, new_value);
// }

// ORDERS

// // Metode statice pentru update (pentru implementări și logică viitoare)
// static void update_order_id(Order &order, const void *new_data);
// static void update_order_provider_id(Order &order, const void *new_data);
// static void update_order_date(Order &order, const void *new_data);
// static void update_order_total_price(Order &order, const void *new_data);
// static void update_order_status(Order &order, const void *new_data);
//
// // O structură internă care grupează mai multe variabile într-un singur pachet de date
// // Este folosită strict pentru a trimite ușor noile liste de materiale și cantități către metoda de update
// struct OrderUpdate {
//     const char **ids; // Array cu noile ID-uri de materiale
//     const double *quantities; // Array cu noile cantități
//     int count; // Câte elemente au array-urile de mai sus
// };
//
// // Metodă statică ce folosește structura de mai sus (trimisă prin pointerul new_data) pentru a actualiza listele
// static void update_order_materials(Order &order, const void *new_data);
//
// // Metodă generică delegat. Primește instanța, funcția exactă de update ce trebuie apelată și noile date
// static void update_order(Order &order, void (*func)(Order &, const void *), const void *new_value);

// // Metode statice delegate pentru actualizarea stării unui object
// void Order::update_order_id(Order &order, const void *new_data) {
//     order.set_order_id(static_cast<const char *>(new_data));
// }
//
// void Order::update_order_provider_id(Order &order, const void *new_data) {
//     order.set_order_provider_id(static_cast<const char *>(new_data));
// }
//
// void Order::update_order_date(Order &order, const void *new_data) {
//     order.set_order_date(static_cast<const char *>(new_data));
// }
//
// void Order::update_order_total_price(Order &order, const void *new_data) {
//     order.set_order_total_price(*static_cast<const double *>(new_data));
// }
//
// void Order::update_order_status(Order &order, const void *new_data) {
//     order.set_status(*static_cast<const Status *>(new_data));
// }
//
// void Order::update_order_materials(Order &order, const void *new_data) {
//     const auto *u = static_cast<const OrderUpdate *>(new_data);
//     order.set_order_materials_id(u->ids, u->count);
//     order.set_order_quantities(u->quantities, u->count);
// }
//
// // Metodă generică delegat. Primește instanța, funcția exactă de update ce trebuie apelată și noile date
// void Order::update_order(Order &order, void (*func)(Order &, const void *),
//                          const void *new_value) {
//     func(order, new_value);
// }
