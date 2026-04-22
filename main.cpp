#include <iostream>
#include <cstring>

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

class Material {
public:
    // Definim un enum strict pentru a grupa categoriile posibile ale unui material
    enum class Category { wood, metal, insulation, finishes, others };

    // Constructorul implicit (fara parametri)
    Material();

    // Constructorul de copiere
    Material(const Material &other);

    // Constructorul cu parametri
    Material(const char *id, const char *name, const char *measure_unit,
             const double &quantity, const double &critical,
             const double &unit_price, const Category &category);

    // Destructorul clasei
    ~Material();

    // Getters
    // Cuvantul cheie const de la final garanteaza ca aceste metode nu vor modifica starea instantei
    [[nodiscard]] char *get_material_id() const; // Returneaza identificatorul unic
    [[nodiscard]] char *get_material_name() const; // Returneaza numele materialului
    [[nodiscard]] char *get_material_measure_unit() const; // Returneaza unitatea de masura
    [[nodiscard]] double get_material_critical() const; // Returneaza pragul critic de stoc
    [[nodiscard]] double get_material_unit_price() const; // Returneaza pretul pe unitate
    [[nodiscard]] double get_material_quantity() const; // Returneaza cantitatea curenta disponibila
    [[nodiscard]] Category get_material_category() const; // Returneaza categoria din enumerarea de mai sus

    // Supraincarcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Material &material);
    friend std::ostream &operator<<(std::ostream &os, const Material &material);

    // Supraincarcarea operatorului de atribuire
    Material &operator=(const Material &other);

    // Supraincarcarea operatorilor relationali
    bool operator==(const Material &other) const; // Verifica egalitatea
    bool operator!=(const Material &other) const; // Verifica inegalitatea

    // Convertor category la string
    static const char *material_category_to_string(const Category &category);

    // Interschimbare
    static void swap(Material &material1, Material &material2) noexcept;

    // Functii de update
    static void update_material_id(Material &material, const void *new_id);
    static void update_material_name(Material &material, const void *new_name);
    static void update_material_measure_unit(Material &material, const void *new_measure_unit);
    static void update_material_critical(Material &material, const void *new_critical);
    static void update_material_unit_price(Material &material, const void *new_unit_price);
    static void update_material_quantity(Material &material, const void *new_quantity);
    static void update_material_category(Material &material, const void *new_category);
    static void update_material(Material &material, void (*func)(Material &, const void *), const void *new_value);

private:
    char *id; // ID-ul materialului
    char *name; // Numele materialului
    char *measure_unit; // Unitatea de masura pentru material
    double quantity; // Cantitatea
    double critical; // Limita pentru stocul critic
    double unit_price; // Pretul unitar
    Category category; // Tipul materialului

    // Setters
    void set_material_id(const char *new_material_id); // Aloca memorie si actualizeaza ID-ul
    void set_material_name(const char *new_material_name); // Aloca memorie si actualizeaza numele
    void set_material_measure_unit(const char *new_material_measure_unit); // Aloca memorie si actualizeaza unitatea de masura
    void set_material_critical(const double &new_material_critical); // Actualizeaza limita critica
    void set_material_unit_price(const double &new_material_unit_price); // Actualizeaza pretul unitar
    void set_material_quantity(const double &new_material_quantity); // Actualizeaza cantitatea
    void set_material_category(const Category &new_material_category); // Actualizeaza categoria
};

// Constructorul default
Material::Material() {
    this->id = nullptr;
    this->name = nullptr;
    this->measure_unit = nullptr;
    this->quantity = 0;
    this->critical = 0;
    this->unit_price = 0;
    this->category = Category::others;
}

// Pentru urmatorii constructori folosim setters pentru atribuirea valorilor deoarece implementeaza deja verificarea datelor
// De asemenea initializam pointerii la nullptr pentru a preveni stergerea memoriei de la adrese invalide

// Constructorul cu parametri
Material::Material(const char *id, const char *name, const char *measure_unit,
                   const double &quantity, const double &critical,
                   const double &unit_price, const Category &category) : Material() {
    set_material_id(id);
    set_material_name(name);
    set_material_measure_unit(measure_unit);
    set_material_quantity(quantity);
    set_material_critical(critical);
    set_material_unit_price(unit_price);
    set_material_category(category);
}

// Copy constructorul
Material::Material(const Material &other) : Material() {
    set_material_id(other.id);
    set_material_name(other.name);
    set_material_measure_unit(other.measure_unit);
    set_material_quantity(other.quantity);
    set_material_critical(other.critical);
    set_material_unit_price(other.unit_price);
    set_material_category(other.category);
}

// Destructor
Material::~Material() {
    delete[] this->id;
    delete[] this->name;
    delete[] this->measure_unit;
}

// Getters
char *Material::get_material_id() const { return this->id; }
char *Material::get_material_name() const { return this->name; }
char *Material::get_material_measure_unit() const { return this->measure_unit; }
double Material::get_material_critical() const { return this->critical; }
double Material::get_material_unit_price() const { return this->unit_price; }
double Material::get_material_quantity() const { return this->quantity; }
Material::Category Material::get_material_category() const { return this->category; }

// Setters
void Material::set_material_id(const char *new_material_id) {
    delete[] this->id;
    this->id = (new_material_id != nullptr)
        ? (strcpy(new char[strlen(new_material_id) + 1], new_material_id))
        : nullptr;
}

void Material::set_material_name(const char *new_material_name) {
    delete[] this->name;
    this->name = (new_material_name != nullptr)
        ? (strcpy(new char[strlen(new_material_name) + 1], new_material_name))
        : nullptr;
}

void Material::set_material_measure_unit(const char *new_material_measure_unit) {
    delete[] this->measure_unit;
    this->measure_unit = (new_material_measure_unit != nullptr)
        ? (strcpy(new char[strlen(new_material_measure_unit) + 1], new_material_measure_unit))
        : nullptr;
}

void Material::set_material_critical(const double &new_material_critical) {
    this->critical = (new_material_critical >= 0) ? new_material_critical : 0;
}

void Material::set_material_unit_price(const double &new_material_unit_price) {
    this->unit_price = (new_material_unit_price >= 0) ? new_material_unit_price : 0;
}

void Material::set_material_quantity(const double &new_material_quantity) {
    this->quantity = (new_material_quantity >= 0) ? new_material_quantity : 0;
}

void Material::set_material_category(const Category &new_material_category) {
    this->category = new_material_category;
}

// Metode auxiliare statice
// Ele sunt apelate de functia principala de update pentru a modifica starea materialului
// Sunt dezvoltate pentru implementari si adaptari ulterioare
void Material::update_material_id(Material &material, const void *new_id) {
    material.set_material_id(static_cast<const char *>(new_id));
}

void Material::update_material_name(Material &material, const void *new_name) {
    material.set_material_name(static_cast<const char *>(new_name));
}

void Material::update_material_measure_unit(Material &material, const void *new_measure_unit) {
    material.set_material_measure_unit(static_cast<const char *>(new_measure_unit));
}

void Material::update_material_critical(Material &material, const void *new_critical) {
    material.set_material_critical(*static_cast<const double *>(new_critical));
}

void Material::update_material_unit_price(Material &material, const void *new_unit_price) {
    material.set_material_unit_price(*static_cast<const double *>(new_unit_price));
}

void Material::update_material_quantity(Material &material, const void *new_quantity) {
    material.set_material_quantity(*static_cast<const double *>(new_quantity));
}

void Material::update_material_category(Material &material, const void *new_category) {
    material.set_material_category(*static_cast<const Category *>(new_category));
}

// Functia principala de update
void Material::update_material(Material &material, void (*func)(Material &, const void *), const void *new_value) {
    if (func == nullptr)
        return;
    func(material, new_value);
}

// Supraincarcare operator de atribuire
// Nu mai este nevoie sa initializam pointerii la nullptr pentru ca avem garantia constructorilor ca putem sterge zonele de memorie alocate
Material &Material::operator=(const Material &other) {
    if (this == &other)
        return *this;

    set_material_id(other.id);
    set_material_name(other.name);
    set_material_measure_unit(other.measure_unit);
    set_material_quantity(other.quantity);
    set_material_critical(other.critical);
    set_material_unit_price(other.unit_price);
    set_material_category(other.category);

    return *this;
}

// Supraincarcarea operatorilor relationali
// Aplicam si aici verificari ale validitatii datelor pentru a putea folosi strcmp
bool Material::operator==(const Material &other) const {
    if ((this->id == nullptr) != (other.id == nullptr)) return false;
    if (this->id != nullptr && other.id != nullptr && strcmp(this->id, other.id) != 0) return false;

    if ((this->name == nullptr) != (other.name == nullptr)) return false;
    if (this->name != nullptr && other.name != nullptr && strcmp(this->name, other.name) != 0) return false;

    if ((this->measure_unit == nullptr) != (other.measure_unit == nullptr)) return false;
    if (this->measure_unit != nullptr && other.measure_unit != nullptr && strcmp(this->measure_unit, other.measure_unit) != 0)
        return false;

    return this->quantity == other.quantity &&
           this->critical == other.critical &&
           this->unit_price == other.unit_price &&
           this->category == other.category;
}

bool Material::operator!=(const Material &other) const {
    return !(*this == other);
}

// Interschimbare
void Material::swap(Material &material1, Material &material2) noexcept {
    std::swap(material1.id, material2.id);
    std::swap(material1.name, material2.name);
    std::swap(material1.measure_unit, material2.measure_unit);
    std::swap(material1.quantity, material2.quantity);
    std::swap(material1.critical, material2.critical);
    std::swap(material1.unit_price, material2.unit_price);
    std::swap(material1.category, material2.category);
}

std::ostream &operator<<(std::ostream &os, const Material &material) {
    os << "[ " << (material.id ? material.id : "N/A") << " ] " << (material.name ? material.name : "N/A") << "\n";
    os << "  Category    : " << Material::material_category_to_string(material.category) << "\n";
    os << "  Quantity    : " << material.quantity << " " << (material.measure_unit ? material.measure_unit : "N/A") << "\n";
    os << "  Critical    : " << material.critical << " " << (material.measure_unit ? material.measure_unit : "N/A") << "\n";
    os << "  Price/unit  : " << material.unit_price << " RON\n\n";

    return os;
}

// Supraincarcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Material &material) {
    char material_id[256];
    char material_name[256];
    char material_measure_unit[256];
    int material_category;
    double temp;

    std::cout << "Enter material ID: ";
    is >> material_id;
    material.set_material_id(material_id);

    std::cout << "Enter material name: ";
    is >> material_name;
    material.set_material_name(material_name);

    std::cout << "Enter measure unit: ";
    is >> material_measure_unit;
    material.set_material_measure_unit(material_measure_unit);

    std::cout << "Enter quantity: ";
    is >> temp;
    material.set_material_quantity(temp);

    std::cout << "Enter critical level: ";
    is >> temp;
    material.set_material_critical(temp);

    std::cout << "Enter unit price: ";
    is >> temp;
    material.set_material_unit_price(temp);

    std::cout << "Enter category (0: wood, 1: metal, 2: finishes, 3: insulation, 4: others): ";
    is >> material_category;
    material_category = (material_category >= 0 && material_category <= 4) ? material_category : 4;
    material.set_material_category(static_cast<Material::Category>(material_category));

    return is;
}

// Convertor category la string
const char *Material::material_category_to_string(const Category &category) {
    switch (category) {
        case Category::wood:
            return "wood";
        case Category::metal:
            return "metal";
        case Category::finishes:
            return "finishes";
        case Category::insulation:
            return "insulation";
        default:
            return "others";
    }
}

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
        const double &total_price, const char *date, const Status &status);

  // Destructorul
  ~Order();

  // Getters
  // Cuvantul cheie const de la final garanteaza ca aceste metode nu vor
  // modifica starea instantei
  [[nodiscard]] char *get_order_id() const; // Returneaza ID-ul comenzii
  [[nodiscard]] char *get_order_provider_id() const; // Returneaza ID-ul furnizorului
  [[nodiscard]] char **get_order_materials_id() const; // Returneaza un array de string-uri (ID-urile materialelor)
  [[nodiscard]] double *get_order_quantities() const; // Returneaza un array cu cantitatile pentru fiecare material
  [[nodiscard]] double get_order_total_price() const; // Returneaza valoarea totala
  [[nodiscard]] char *get_order_date() const; // Returneaza data plasarii comenzii
  [[nodiscard]] Status get_order_status() const; // Returneaza stadiul curent (pending, delivered etc.)
  [[nodiscard]] int get_order_materials_count() const; // Returneaza numarul de materiale din comanda

  // Supraincarcarea operatorilor de I/O
  friend std::ostream &operator<<(std::ostream &os, const Order &order);
  friend std::istream &operator>>(std::istream &is, Order &order);

  // Supraincarcarea operatorului de atribuire
  Order &operator=(const Order &other);

  // Supraincarcarea operatorilor relationali
  bool operator==(const Order &other) const;
  bool operator!=(const Order &other) const;

  // Convertor status la string
  static const char *order_status_to_string(const Status &status);

  // Interschimbare
  static void swap(Order &order1, Order &order2) noexcept;

  // Functii de update
  static void update_order_id(Order &order, const void *new_data);
  static void update_order_provider_id(Order &order, const void *new_data);
  static void update_order_date(Order &order, const void *new_data);
  static void update_order_total_price(Order &order, const void *new_data);
  static void update_order_status(Order &order, const void *new_data);
  static void update_order_materials(Order &order, const void *new_data);
  static void update_order(Order &order, void (*func)(Order &, const void *), const void *new_value);

private:
  char *id;            // ID-ul comenzii
  char *provider_id;   // ID-ul furnizorului
  char **materials_id; // Un array dinamic de string-uri pentru ID-urile materialelor
  int materials_count; // Numarul de materiale din comanda
  double *quantities;  // Un array alocat dinamic pentru a stoca valorile cantitatilor
  double total_price;  // Valoarea totala a comenzii
  char *date;          // Data in care s-a dat comanda
  Status status;       // Starea curenta a comenzii

  // Setters
  void set_order_id(const char *new_order_id);
  void set_order_provider_id(const char *new_order_provider_id);
  void set_order_materials(const char **new_order_materials, const double *new_order_quantities, const int &new_order_materials_count);
  void set_order_total_price(const double &new_order_total_price);
  void set_order_date(const char *new_order_date);
  void set_order_status(const Status &new_order_status);

  // Functii helper
  static bool verify_order_date(const char *date) ;
};

Order::Order() {
    this->id = nullptr;
    this->provider_id = nullptr;
    this->materials_id = nullptr;
    this->quantities = nullptr;
    this->date = nullptr;
    this->materials_count = 0;
    this->total_price = 0;
    this->status = Status::unknown;
}

// Constructorul cu parametri
Order::Order(const char *id, const char *provider_id, const char **materials_id,
             const int &materials_count, const double *quantities,
             const double &total_price, const char *date, const Status &status)
    : Order() {
    set_order_id(id);
    set_order_provider_id(provider_id);
    set_order_materials(materials_id, quantities, materials_count);
    set_order_total_price(total_price);
    set_order_date(date);
    set_order_status(status);
}

// Copy constructor
Order::Order(const Order &other) : Order() {
    set_order_id(other.id);
    set_order_provider_id(other.provider_id);
    set_order_date(other.date);
    set_order_total_price(other.total_price);
    set_order_materials(const_cast<const char **>(other.materials_id), other.quantities, other.materials_count);
    set_order_status(other.status);
}

// Destructorul
Order::~Order() {
    delete[] this->id;
    delete[] this->provider_id;
    delete[] this->date;

    if (this->materials_id != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            delete[] this->materials_id[i];

    delete[] this->materials_id;
    delete[] this->quantities;
}

// Getters
char *Order::get_order_id() const { return this->id; }
char *Order::get_order_provider_id() const { return this->provider_id; }
char **Order::get_order_materials_id() const { return this->materials_id; }
double *Order::get_order_quantities() const { return this->quantities; }
double Order::get_order_total_price() const { return this->total_price; }
char *Order::get_order_date() const { return this->date; }
Order::Status Order::get_order_status() const { return this->status; }
int Order::get_order_materials_count() const { return this->materials_count; }

// Setters
void Order::set_order_status(const Status &new_order_status) {
    this->status = new_order_status;
}

void Order::set_order_total_price(const double &new_order_total_price) {
    this->total_price = new_order_total_price >= 0 ? new_order_total_price : 0;
}

void Order::set_order_id(const char *new_order_id) {
    delete[] this->id;
    this->id = (new_order_id != nullptr)
        ? strcpy(new char[strlen(new_order_id) + 1], new_order_id)
        : nullptr;
}

void Order::set_order_provider_id(const char *new_order_provider_id) {
    delete[] this->provider_id;
    this->provider_id = (new_order_provider_id != nullptr)
        ? strcpy(new char[strlen(new_order_provider_id) + 1], new_order_provider_id)
        : nullptr;
}

void Order::set_order_date(const char *new_order_date) {
    delete[] this->date;
    this->date = (new_order_date != nullptr && verify_order_date(new_order_date))
        ? strcpy(new char[strlen(new_order_date) + 1], new_order_date)
        : nullptr;
}

void Order::set_order_materials(const char **new_order_materials,
                                const double *new_order_quantities,
                                const int &new_order_materials_count) {
    // Stergem memoria alocata anterior
    if (materials_id != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            delete[] this->materials_id[i];
    delete[] this->materials_id;
    delete[] this->quantities;

    // Verificam posibilitatea de copiere a noilor valori si efectuam daca se
    // poate
    this->materials_count = (new_order_materials_count >= 0) ? new_order_materials_count : 0;
    if (this->materials_count > 0 && new_order_materials != nullptr && new_order_quantities != nullptr) {
        this->materials_id = new char *[this->materials_count];
        this->quantities = new double[this->materials_count];
        for (int i = 0; i < this->materials_count; i++) {
            this->materials_id[i] = (new_order_materials[i] != nullptr)
                ? (strcpy(new char[strlen(new_order_materials[i]) + 1], new_order_materials[i]))
                : nullptr;
            this->quantities[i] = new_order_quantities[i] >= 0 ? new_order_quantities[i] : 0;
        }
    } else {
        // Altfel declaram inexistenta materialelor
        this->materials_id = nullptr;
        this->quantities = nullptr;
        this->materials_count = 0;
    }
}

void Order::update_order_id(Order &order, const void *new_data) {
    order.set_order_id(static_cast<const char *>(new_data));
}

void Order::update_order_provider_id(Order &order, const void *new_data) {
    order.set_order_provider_id(static_cast<const char *>(new_data));
}

void Order::update_order_date(Order &order, const void *new_data) {
    order.set_order_date(static_cast<const char *>(new_data));
}

void Order::update_order_total_price(Order &order, const void *new_data) {
    order.set_order_total_price(*static_cast<const double *>(new_data));
}

void Order::update_order_status(Order &order, const void *new_data) {
    order.set_order_status(*static_cast<const Status *>(new_data));
}

struct OrderUpdate {
    const char **new_materials_id;
    const double *new_quantities;
    int new_materials_count;
};

void Order::update_order_materials(Order &order, const void *new_data) {
    const auto *u = static_cast<const OrderUpdate *>(new_data);
    order.set_order_materials(u->new_materials_id, u->new_quantities, u->new_materials_count);
}

// Functie generala de update
void Order::update_order(Order &order, void (*func)(Order &, const void *), const void *new_value) {
    if (func == nullptr)
        return;
    func(order, new_value);
}

// Supraincarcarea operatorului de atribuire
// Nu mai este nevoie sa initializam pointerii la nullptr pentru ca avem
// garantia constructorilor ca putem sterge zonele de memorie alocate
Order &Order::operator=(const Order &other) {
    if (this == &other)
        return *this;

    set_order_id(other.id);
    set_order_provider_id(other.provider_id);
    set_order_date(other.date);
    set_order_total_price(other.total_price);
    set_order_status(other.status);
    set_order_materials(const_cast<const char **>(other.materials_id), other.quantities, other.materials_count);

    return *this;
}

// Supraincarcare operatori relationali
// Aplicam si aici verificari ale validitatii datelor pentru a putea folosi
// strcmp
bool Order::operator==(const Order &other) const {
    if ((this->id == nullptr) != (other.id == nullptr)) return false;
    if (this->id != nullptr && other.id != nullptr && strcmp(this->id, other.id) != 0) return false;

    if ((this->provider_id == nullptr) != (other.provider_id == nullptr)) return false;
    if (this->provider_id != nullptr && other.provider_id != nullptr && strcmp(this->provider_id, other.provider_id) != 0) return false;

    if ((this->date == nullptr) != (other.date == nullptr)) return false;
    if (this->date != nullptr && other.date != nullptr && strcmp(this->date, other.date) != 0) return false;

    if (this->materials_count != other.materials_count || this->total_price != other.total_price || this->status != other.status) return false;

    if ((this->materials_id == nullptr) != (other.materials_id == nullptr)) return false;
    if ((this->quantities == nullptr) != (other.quantities == nullptr)) return false;

    if (this->materials_id != nullptr && this->quantities != nullptr && other.materials_id != nullptr && other.quantities != nullptr)
        for (int i = 0; i < this->materials_count; i++) {
            if ((this->materials_id[i] == nullptr) != (other.materials_id[i] == nullptr)) return false;
            if (this->materials_id[i] != nullptr && other.materials_id[i] != nullptr && strcmp(this->materials_id[i], other.materials_id[i]) != 0) return false;
            if (this->quantities[i] != other.quantities[i]) return false;
        }

    return true;
}

bool Order::operator!=(const Order &other) const {
    return !(*this == other);
}

// Interschimbare
void Order::swap(Order &order1, Order &order2) noexcept {
    std::swap(order1.id, order2.id);
    std::swap(order1.provider_id, order2.provider_id);
    std::swap(order1.materials_id, order2.materials_id);
    std::swap(order1.materials_count, order2.materials_count);
    std::swap(order1.quantities, order2.quantities);
    std::swap(order1.total_price, order2.total_price);
    std::swap(order1.date, order2.date);
    std::swap(order1.status, order2.status);
}

// Supraincarcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Order &order) {
    char order_id[256];
    char provider_id[256];
    char order_date[256];
    int order_materials_count;
    int order_status;
    double order_total_price;

    std::cout << "Enter order ID: ";
    is >> order_id;
    order.set_order_id(order_id);

    std::cout << "Enter provider ID: ";
    is >> provider_id;
    order.set_order_provider_id(provider_id);

    std::cout << "Enter date (DD-MM-YYYY): ";
    is >> order_date;
    order.set_order_date(order_date);

    std::cout << "Enter total price: ";
    is >> order_total_price;
    order.set_order_total_price(order_total_price);

    std::cout << "Enter status (0: pending, 1: delivered, 2: cancelled, 3: unknown): ";
    is >> order_status;
    order_status = (order_status >= 0 && order_status <= 3) ? order_status : 3;
    order.set_order_status(static_cast<Order::Status>(order_status));

    std::cout << "Enter number of materials: ";
    is >> order_materials_count;

    if (order_materials_count > 0) {
        auto **order_materials_id = new char *[order_materials_count];
        auto *order_quantities = new double[order_materials_count];

        for (int i = 0; i < order_materials_count; i++) {
            char order_material_id[256];

            std::cout << "Enter material " << i + 1 << " ID: ";
            is >> order_material_id;

            order_materials_id[i] = new char[strlen(order_material_id) + 1];
            strcpy(order_materials_id[i], order_material_id);

            std::cout << "Enter material " << i + 1 << " quantity: ";
            is >> order_quantities[i];
        }

        order.set_order_materials(const_cast<const char **>(order_materials_id), order_quantities, order_materials_count);

        for (int i = 0; i < order_materials_count; i++)
            delete[] order_materials_id[i];
        delete[] order_materials_id;
        delete[] order_quantities;
    } else {
        order.set_order_materials(nullptr, nullptr, 0);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Order &order) {
    os << "[ " << (order.id ? order.id : "N/A") << " ] " << (order.date ? order.date : "N/A") << "\n";
    os << "  Provider    : " << (order.provider_id ? order.provider_id : "N/A") << "\n";
    os << "  Status      : " << Order::order_status_to_string(order.status) << "\n";
    os << "  Total price : " << order.total_price << " RON\n";
    os << "  Materials   : ";

    // Verificam existenta materialelor pentru a le putea afisa
    if (order.materials_id != nullptr && order.quantities != nullptr && order.materials_count > 0)
        for (int i = 0; i < order.materials_count; i++) {
            os << (order.materials_id[i] ? order.materials_id[i] : "N/A") << " x " << order.quantities[i];
            if (i < order.materials_count - 1)
                os << ", ";
        }
    else
        os << "None";
    os << "\n\n";
    return os;
}

// Convertor status la string
const char *Order::order_status_to_string(const Status &status) {
    switch (status) {
        case Status::pending:
            return "pending";
        case Status::delivered:
            return "delivered";
        case Status::cancelled:
            return "cancelled";
        default:
            return "unknown";
    }
}

// Functie helper pentru verificarea validitatii datei
bool Order::verify_order_date(const char *date) {
    if (date == nullptr)
        return false;

    int day, month, year;
    if (sscanf(date, "%d-%d-%d", &day, &month, &year) != 3)
        return false;

    if (year < 2026)
        return false;

    if (month < 1 || month > 12)
        return false;

    if (day < 1 || day > 31)
        return false;

    if (month == 2 && day > 29)
        return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;

    if (!((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) && month == 2 && day > 28)
        return false;

    return true;
}

class Provider {
public:
    // Constructorul implicit
    Provider();

    // Constructorul de copiere
    Provider(const Provider &other);

    // Constructorul cu parametri
    Provider(const char *id, const char *name, const char *phone,
             const char *email, const char *address, const char **materials_id,
             const int &materials_count);

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

    // Functii de update;
    static void update_provider_id(Provider &provider, const void *new_id);
    static void update_provider_name(Provider &provider, const void *new_name);
    static void update_provider_phone(Provider &provider, const void *new_phone);
    static void update_provider_email(Provider &provider, const void *new_email);
    static void update_provider_address(Provider &provider, const void *new_address);
    static void update_provider_materials(Provider &provider, const void *data);
    static void update_provider(Provider &provider, void (*func)(Provider &, const void *), const void *new_data);

private:
    char *id; // ID-ul furnizorului
    char *name; // Numele furnizorului
    char *phone; // Numarul de telefon pentru furnizor
    char *email; // Email-ul furnizorului
    char *address; // Adresa furnizorului
    char **materials_id; // Array pentru ID-urile materialelor disponibile
    int materials_count; // Numarul de materiale furnizate de provider

    // Setters
    void set_provider_id(const char *new_provider_id); // Curata memoria veche si o aloca pe cea noua pentru ID
    void set_provider_name(const char *new_provider_name); // Gestioneaza memoria si seteaza noul nume
    void set_provider_phone(const char *new_provider_phone); // Gestioneaza memoria si seteaza noul telefon
    void set_provider_email(const char *new_provider_email); // Gestioneaza memoria si seteaza noul email
    void set_provider_address(const char *new_provider_address); // Gestioneaza memoria si seteaza noua adresa
    void set_provider_materials(const char **new_provider_materials, const int &new_provider_materials_count); // Modifica simultan pointerul catre matricea de materiale si numarul de materiale

    // Functii helper
    static bool verify_provider_phone(const char *phone);
    static bool verify_provider_email(const char *email);
};

Provider::Provider() {
    this->id = nullptr;
    this->name = nullptr;
    this->phone = nullptr;
    this->email = nullptr;
    this->address = nullptr;
    this->materials_id = nullptr;
    this->materials_count = 0;
}

// Pentru urmatorii constructori folosim setters pentru atribuirea valorilor deoarece implementeaza deja verificarea datelor
// De asemenea initializam pointerii la nullptr pentru a preveni stergerea memoriei de la adrese invalide

// Constructorul cu parametri
Provider::Provider(const char *id, const char *name, const char *phone,
                   const char *email, const char *address,
                   const char **materials_id, const int &materials_count) : Provider() {
    set_provider_id(id);
    set_provider_name(name);
    set_provider_phone(phone);
    set_provider_email(email);
    set_provider_address(address);
    set_provider_materials(materials_id, materials_count);
}

// Copy constructor
Provider::Provider(const Provider &other) : Provider() {
    set_provider_id(other.id);
    set_provider_name(other.name);
    set_provider_phone(other.phone);
    set_provider_email(other.email);
    set_provider_address(other.address);
    set_provider_materials(const_cast<const char **>(other.materials_id), other.materials_count);
}

// Destructorul
Provider::~Provider() {
    delete[] this->id;
    delete[] this->name;
    delete[] this->phone;
    delete[] this->email;
    delete[] this->address;

    if (this->materials_id != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            delete[] this->materials_id[i];
    delete[] this->materials_id;
}

// Getters
char *Provider::get_provider_id() const { return this->id; }
char *Provider::get_provider_name() const { return this->name; }
char *Provider::get_provider_phone() const { return this->phone; }
char *Provider::get_provider_email() const { return this->email; }
char *Provider::get_provider_address() const { return this->address; }
char **Provider::get_provider_materials_id() const { return this->materials_id; }
int Provider::get_provider_materials_count() const { return this->materials_count; }

// Setters
void Provider::set_provider_id(const char *new_provider_id) {
    delete[] this->id;
    this->id = (new_provider_id != nullptr)
        ? (strcpy(new char[strlen(new_provider_id) + 1], new_provider_id))
        : nullptr;
}

void Provider::set_provider_name(const char *new_provider_name) {
    delete[] this->name;
    this->name = (new_provider_name != nullptr)
        ? (strcpy(new char[strlen(new_provider_name) + 1], new_provider_name))
        : nullptr;
}

void Provider::set_provider_phone(const char *new_provider_phone) {
    delete[] this->phone;
    this->phone = (new_provider_phone != nullptr && verify_provider_phone(new_provider_phone))
        ? (strcpy(new char[strlen(new_provider_phone) + 1], new_provider_phone))
        : nullptr;
}

void Provider::set_provider_email(const char *new_provider_email) {
    delete[] this->email;
    this->email = (new_provider_email != nullptr && verify_provider_email(new_provider_email))
        ? (strcpy(new char[strlen(new_provider_email) + 1], new_provider_email))
        : nullptr;
}

void Provider::set_provider_address(const char *new_provider_address) {
    delete[] this->address;
    this->address = (new_provider_address != nullptr)
        ? (strcpy(new char[strlen(new_provider_address) + 1], new_provider_address))
        : nullptr;
}

void Provider::set_provider_materials(const char **new_provider_materials, const int &new_provider_materials_count) {
    // Stergem memoria alocata anterior
    if (materials_id != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            delete[] this->materials_id[i];
    delete[] this->materials_id;

    // Verificam posibilitatea de copiere a noilor valori si efectuam daca se poate
    this->materials_count = (new_provider_materials_count >= 0) ? new_provider_materials_count : 0;
    if (this->materials_count > 0 && new_provider_materials != nullptr) {
        this->materials_id = new char *[this->materials_count];
        for (int i = 0; i < this->materials_count; i++)
            this->materials_id[i] = (new_provider_materials[i] != nullptr)
                ? (strcpy(new char[strlen(new_provider_materials[i]) + 1], new_provider_materials[i]))
                : nullptr;
    } else {
        // Altfel declaram inexistenta materialelor
        this->materials_id = nullptr;
        this->materials_count = 0;
    }
}

// Functii de update
// Ele sunt apelate de functia principala de update petru a modifica starea furnizorului
// Sunt dezvoltate pentru implementari si adaptari ulterioare
void Provider::update_provider_id(Provider &provider, const void *new_id) {
    provider.set_provider_id(static_cast<const char *>(new_id));
}

void Provider::update_provider_name(Provider &provider, const void *new_name) {
    provider.set_provider_name(static_cast<const char *>(new_name));
}

void Provider::update_provider_phone(Provider &provider, const void *new_phone) {
    provider.set_provider_phone(static_cast<const char *>(new_phone));
}

void Provider::update_provider_email(Provider &provider, const void *new_email) {
    provider.set_provider_email(static_cast<const char *>(new_email));
}

void Provider::update_provider_address(Provider &provider, const void *new_address) {
    provider.set_provider_address(static_cast<const char *>(new_address));
}

struct ProviderMaterialsUpdate {
    const char **new_materials_id;
    int new_materials_count;
};

void Provider::update_provider_materials(Provider &provider, const void *data) {
    const auto *u = static_cast<const ProviderMaterialsUpdate *>(data);
    provider.set_provider_materials(u->new_materials_id, u->new_materials_count);
}

void Provider::update_provider(Provider &provider, void (*func)(Provider &, const void *), const void *new_data) {
    if (func == nullptr)
        return;
    func(provider, new_data);
}

// Supraincarcarea operatorului de atribuire
// Nu mai este nevoie sa initializam pointerii la nullptr pentru ca avem garantia constructorilor ca putem sterge zonele de memorie alocate
Provider &Provider::operator=(const Provider &other) {
    if (this == &other)
        return *this;

    set_provider_id(other.id);
    set_provider_name(other.name);
    set_provider_phone(other.phone);
    set_provider_email(other.email);
    set_provider_address(other.address);
    set_provider_materials(const_cast<const char **>(other.materials_id), other.materials_count);

    return *this;
}

// Supraincarcarea operatorilor relationali
// Aplicam si aici verificari ale validitatii datelor pentru a putea folosi strcmp
bool Provider::operator==(const Provider &other) const {
    if ((this->id == nullptr) != (other.id == nullptr)) return false;
    if (this->id != nullptr && other.id != nullptr && strcmp(this->id, other.id) != 0) return false;

    if ((this->name == nullptr) != (other.name == nullptr)) return false;
    if (this->name != nullptr && other.name != nullptr && strcmp(this->name, other.name) != 0) return false;

    if ((this->phone == nullptr) != (other.phone == nullptr)) return false;
    if (this->phone != nullptr && other.phone != nullptr && strcmp(this->phone, other.phone) != 0) return false;

    if ((this->email == nullptr) != (other.email == nullptr)) return false;
    if (this->email != nullptr && other.email != nullptr && strcmp(this->email, other.email) != 0) return false;

    if ((this->address == nullptr) != (other.address == nullptr)) return false;
    if (this->address != nullptr && other.address != nullptr && strcmp(this->address, other.address) != 0) return false;

    if (this->materials_count != other.materials_count) return false;
    if ((this->materials_id == nullptr) != (other.materials_id == nullptr)) return false;
    if (this->materials_id != nullptr)
        for (int i = 0; i < this->materials_count; i++) {
            if ((this->materials_id[i] == nullptr) != (other.materials_id[i] == nullptr)) return false;
            if (this->materials_id[i] != nullptr && other.materials_id[i] != nullptr && strcmp(this->materials_id[i], other.materials_id[i]) != 0) return false;
        }

    return true;
}

// Refolosim codul deja scris pentru operatorul de inegalitate
bool Provider::operator!=(const Provider &other) const {
    return !(*this == other);
}

// Interschimbare
void Provider::swap(Provider &provider1, Provider &provider2) noexcept {
    std::swap(provider1.id, provider2.id);
    std::swap(provider1.name, provider2.name);
    std::swap(provider1.phone, provider2.phone);
    std::swap(provider1.email, provider2.email);
    std::swap(provider1.address, provider2.address);
    std::swap(provider1.materials_id, provider2.materials_id);
    std::swap(provider1.materials_count, provider2.materials_count);
}

// Supraincarcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Provider &provider) {
    char provider_id[256];
    char provider_name[256];
    char provider_phone[256];
    char provider_email[256];
    char provider_address[256];
    int provider_materials_count;

    std::cout << "Enter provider ID: ";
    is >> provider_id;
    provider.set_provider_id(provider_id);

    std::cout << "Enter provider name: ";
    is >> provider_name;
    provider.set_provider_name(provider_name);

    std::cout << "Enter provider phone: ";
    is >> provider_phone;
    provider.set_provider_phone(provider_phone);

    std::cout << "Enter provider email: ";
    is >> provider_email;
    provider.set_provider_email(provider_email);

    std::cout << "Enter provider address: ";
    is >> provider_address;
    provider.set_provider_address(provider_address);

    std::cout << "Enter number of materials: ";
    is >> provider_materials_count;

    if (provider_materials_count > 0) {
        auto **provider_materials_id = new char *[provider_materials_count];

        for (int i = 0; i < provider_materials_count; i++) {
            char provider_material_id[256];
            std::cout << "Enter material " << i + 1 << " ID: ";
            is >> provider_material_id;
            provider_materials_id[i] = new char[strlen(provider_material_id) + 1];
            strcpy(provider_materials_id[i], provider_material_id);
        }

        provider.set_provider_materials(const_cast<const char **>(provider_materials_id), provider_materials_count);

        for (int i = 0; i < provider_materials_count; i++)
            delete[] provider_materials_id[i];
        delete[] provider_materials_id;
    } else {
        provider.set_provider_materials(nullptr, 0);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Provider &provider) {
    os << "[ " << (provider.id ? provider.id : "N/A") << " ] " << (provider.name ? provider.name : "N/A") << "\n";
    os << "  Phone      : " << (provider.phone ? provider.phone : "N/A") << "\n";
    os << "  Email      : " << (provider.email ? provider.email : "N/A") << "\n";
    os << "  Address    : " << (provider.address ? provider.address : "N/A") << "\n";
    os << "  Materials  : ";

    // Verificam existenta materialelor pentru a le putea afisa
    if (provider.materials_id != nullptr && provider.materials_count > 0)
        for (int i = 0; i < provider.materials_count; i++) {
            os << (provider.materials_id[i] ? provider.materials_id[i] : "N/A");
            if (i < provider.materials_count - 1)
                os << ", ";
        }
    else
        os << "None";
    os << "\n\n";

    return os;
}

bool Provider::verify_provider_email(const char *email) {
    if (email == nullptr)
        return false;

    const char *at_pos = strchr(email, '@');
    if (at_pos == nullptr || at_pos == email || at_pos >= email + strlen(email) - 1)
        return false;

    const char *dot_pos = strrchr(at_pos, '.');
    if (dot_pos == nullptr || dot_pos == at_pos + 1 || dot_pos >= email + strlen(email) - 1)
        return false;

    return true;
}

bool Provider::verify_provider_phone(const char *phone) {
    if (phone == nullptr)
        return false;

    if (strlen(phone) != 10)
        return false;

    for (int i = 0; i < 10; i++)
        if (phone[i] < '0' || phone[i] > '9')
            return false;

    return true;
}

class Inventory {
public:
    // Constructor implicit
    Inventory();

    // Constructor de copiere
    Inventory(const Inventory &other);

    // Constructor cu parametri
    Inventory(const char *id, const char *name, const char *address, const char *phone, const char *email,
              const Material *materials, const Provider *providers, const Order *orders,
              const int &materials_count, const int &providers_count, const int &orders_count);

    // Destructor
    ~Inventory();

    // Getters
    [[nodiscard]] char *get_inventory_id() const; // Returnează ID-ul
    [[nodiscard]] char *get_inventory_name() const; // Returnează numele
    [[nodiscard]] char *get_inventory_address() const; // Returnează adresa
    [[nodiscard]] char *get_inventory_phone() const; // Returnează telefonul
    [[nodiscard]] char *get_inventory_email() const; // Returnează email-ul
    [[nodiscard]] Material *get_inventory_materials() const; // Returnează adresa de început a tabloului de materiale
    [[nodiscard]] Provider *get_inventory_providers() const; // Returnează tabloul de furnizori
    [[nodiscard]] Order *get_inventory_orders() const; // Returnează tabloul de comenzi
    [[nodiscard]] int get_inventory_materials_count() const; // Returnează numărul efectiv de materiale stocate în inventar
    [[nodiscard]] int get_inventory_providers_count() const; // Returnează numărul efectiv de furnizori stocați în inventar
    [[nodiscard]] int get_inventory_orders_count() const; // Returnează numărul efectiv de comenzi stocate în inventar

    // Metode care modifică starea obiectului
    void add_material(const Material &material); // Adaugă o copie a obiectului material în inventar
    void add_provider(const Provider &provider); // Adaugă un nou furnizor
    void add_order(const Order &order); // Înregistrează o comandă nouă
    void consume_material(const char *material_id, const double &quantity); // Recalculează cantitatea disponibilă a unui material după consum
    void receive_order(Order *order); // Procesează o comandă și actualizează stocurile corespunzătoare

    // Metode de căutare pe instanța curentă
    // Returnează un pointer către obiectul găsit în interiorul inventarului
    [[nodiscard]] Material *find_material_by_id(const char *find_id) const;
    [[nodiscard]] Provider *find_provider_by_id(const char *find_id) const;
    [[nodiscard]] Order *find_order_by_id(const char *find_id) const;

    // Calculează valoarea totală iterând prin toate obiectele Material din instanța curentă
    [[nodiscard]] double calculate_inventory_value() const;

    // Metode de sortare specifice instanței curente
    // Modifică ordinea elementelor în tablourile interne
    void sort_materials_by_name_ascending();
    void sort_materials_by_name_descending();
    void sort_materials_by_quantity_ascending();
    void sort_materials_by_quantity_descending();
    void sort_orders_by_total_price_ascending();
    void sort_orders_by_total_price_descending();

    // Filtre
    // Creează și returnează un nou tablou de obiecte care respectă anumite criterii
    // Variabila result_count transmisă prin referință va fi modificată pentru a reflecta dimensiunea noului tablou returnat
    [[nodiscard]] Order *get_orders_by_provider_id(const char *provider_id, int &result_count);
    [[nodiscard]] Material *get_critical_materials(int &result_count);
    [[nodiscard]] Material *get_materials_by_category(const Material::Category &category, int &result_count);

    // Supraîncărcarea operatorului de atribuire
    Inventory &operator=(const Inventory &other);

    // Supraîncărcarea operatorilor relaționali.
    bool operator==(const Inventory &other) const;
    bool operator!=(const Inventory &other) const;

    // Supraîncărcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Inventory &inventory);
    friend std::ostream &operator<<(std::ostream &os, const Inventory &inventory);

    // Functii de update
    static void update_inventory_id(Inventory &inventory, const void *new_id);
    static void update_inventory_name(Inventory &inventory, const void *new_name);
    static void update_inventory_address(Inventory &inventory, const void *new_address);
    static void update_inventory_phone(Inventory &inventory, const void *new_phone);
    static void update_inventory_email(Inventory &inventory, const void *new_email);
    static void update_inventory_materials(Inventory &inventory, const void *new_data);
    static void update_inventory_providers(Inventory &inventory, const void *new_data);
    static void update_inventory_orders(Inventory &inventory, const void *new_data);
    static void update_inventory(Inventory &inventory, void (*func)(Inventory &, const void *), const void *new_data);

private:
    char *id; // ID-ul inventarului
    char *name; // Numele inventarului
    char *address; // Adresa inventarului
    char *phone; // Numărul de telefon al inventarului
    char *email; // Email-ul inventarului
    Material *materials; // Array-ul de materiale al inventarului
    Provider *providers; // Array-ul de furnizori al inventarului
    Order *orders; // Array-ul de comenzi al inventarului
    int materials_count; // Numărul efectiv de materiale din inventar
    int providers_count; // Numărul efectiv de furnizori de la care se poate comanda
    int orders_count; // Numărul efectiv de comenzi existente pentru inventar

    // Setters
    void set_inventory_id(const char *new_inventory_id);
    void set_inventory_name(const char *new_inventory_name);
    void set_inventory_address(const char *new_inventory_address);
    void set_inventory_phone(const char *new_inventory_phone);
    void set_inventory_email(const char *new_inventory_email);
    void set_inventory_materials(const Material *new_inventory_materials, const int &new_inventory_materials_count);
    void set_inventory_providers(const Provider *new_inventory_providers, const int &new_inventory_providers_count);
    void set_inventory_orders(const Order *new_inventory_orders, const int &new_inventory_orders_count);

    // Functii helper
    static bool verify_inventory_phone(const char *phone);
    static bool verify_inventory_email(const char *email);
};

Inventory::Inventory() {
    this->id = nullptr;
    this->name = nullptr;
    this->address = nullptr;
    this->phone = nullptr;
    this->email = nullptr;
    this->materials = nullptr;
    this->providers = nullptr;
    this->orders = nullptr;
    this->materials_count = 0;
    this->providers_count = 0;
    this->orders_count = 0;
}

// Copy constructor
Inventory::Inventory(const Inventory &other) : Inventory() {
    set_inventory_id(other.get_inventory_id());
    set_inventory_name(other.get_inventory_name());
    set_inventory_address(other.get_inventory_address());
    set_inventory_phone(other.get_inventory_phone());
    set_inventory_email(other.get_inventory_email());
    set_inventory_materials(other.get_inventory_materials(), other.get_inventory_materials_count());
    set_inventory_providers(other.get_inventory_providers(), other.get_inventory_providers_count());
    set_inventory_orders(other.get_inventory_orders(), other.get_inventory_orders_count());
}

// Constructorul cu parametri
Inventory::Inventory(const char *id, const char *name, const char *address, const char *phone, const char *email,
                     const Material *materials, const Provider *providers, const Order *orders,
                     const int &materials_count, const int &providers_count, const int &orders_count) : Inventory() {
    set_inventory_id(id);
    set_inventory_name(name);
    set_inventory_address(address);
    set_inventory_phone(phone);
    set_inventory_email(email);
    set_inventory_materials(materials, materials_count);
    set_inventory_providers(providers, providers_count);
    set_inventory_orders(orders, orders_count);
}

// Destructor
Inventory::~Inventory() {
    delete[] this->id;
    delete[] this->name;
    delete[] this->address;
    delete[] this->phone;
    delete[] this->email;
    delete[] this->materials;
    delete[] this->providers;
    delete[] this->orders;
}

// Getters
char *Inventory::get_inventory_id() const { return this->id; }
char *Inventory::get_inventory_name() const { return this->name; }
char *Inventory::get_inventory_address() const { return this->address; }
char *Inventory::get_inventory_phone() const { return this->phone; }
char *Inventory::get_inventory_email() const { return this->email; }
Material *Inventory::get_inventory_materials() const { return this->materials; }
Provider *Inventory::get_inventory_providers() const { return this->providers; }
Order *Inventory::get_inventory_orders() const { return this->orders; }
int Inventory::get_inventory_materials_count() const { return this->materials_count; }
int Inventory::get_inventory_providers_count() const { return this->providers_count; }
int Inventory::get_inventory_orders_count() const { return this->orders_count; }

void Inventory::set_inventory_id(const char *new_inventory_id) {
    delete[] this->id;
    this->id = (new_inventory_id != nullptr)
        ? strcpy(new char[strlen(new_inventory_id) + 1], new_inventory_id)
        : nullptr;
}

void Inventory::set_inventory_name(const char *new_inventory_name) {
    delete[] this->name;
    this->name = (new_inventory_name != nullptr)
        ? strcpy(new char[strlen(new_inventory_name) + 1], new_inventory_name)
        : nullptr;
}

void Inventory::set_inventory_address(const char *new_inventory_address) {
    delete[] this->address;
    this->address = (new_inventory_address != nullptr)
        ? strcpy(new char[strlen(new_inventory_address) + 1], new_inventory_address)
        : nullptr;
}

void Inventory::set_inventory_phone(const char *new_inventory_phone) {
    delete[] this->phone;
    this->phone = (new_inventory_phone != nullptr && verify_inventory_phone(new_inventory_phone))
        ? strcpy(new char[strlen(new_inventory_phone) + 1], new_inventory_phone)
        : nullptr;
}

void Inventory::set_inventory_email(const char *new_inventory_email) {
    delete[] this->email;
    this->email = (new_inventory_email != nullptr && verify_inventory_email(new_inventory_email))
        ? strcpy(new char[strlen(new_inventory_email) + 1], new_inventory_email)
        : nullptr;
}

void Inventory::set_inventory_materials(const Material *new_inventory_materials, const int &new_inventory_materials_count) {
    // Nu este nevoie de o stergere mai complexa a memoriei alocate datorita destructorilor obiectului
    delete[] this->materials;

    // Verificam posibilitatea de copiere a noilor valori si efectuam daca se poate
    this->materials_count = (new_inventory_materials_count > 0) ? new_inventory_materials_count : 0;
    if (this->materials_count > 0 && new_inventory_materials != nullptr) {
        this->materials = new Material[this->materials_count];
        for (int i = 0; i < this->materials_count; i++)
            this->materials[i] = new_inventory_materials[i];
    } else {
        this->materials = nullptr;
        this->materials_count = 0;
    }
}

void Inventory::set_inventory_providers(const Provider *new_inventory_providers, const int &new_inventory_providers_count) {
    // Nu este nevoie de o stergere mai complexa a memoriei alocate datorita destructorilor obiectului
    delete[] this->providers;

    // Verificam posibilitatea de copiere a noilor valori si efectuam daca se poate
    this->providers_count = (new_inventory_providers_count > 0) ? new_inventory_providers_count : 0;
    if (this->providers_count > 0 && new_inventory_providers != nullptr) {
        this->providers = new Provider [this->providers_count];
        for (int i = 0; i < this->providers_count; i++)
            this->providers[i] = new_inventory_providers[i];
    } else {
        this->providers = nullptr;
        this->providers_count = 0;
    }
}

void Inventory::set_inventory_orders(const Order *new_inventory_orders, const int &new_inventory_orders_count) {
    // Nu este nevoie de o stergere mai complexa a memoriei alocate datorita destructorilor obiectului
    delete[] this->orders;

    // Verificam posibilitatea de copiere a noilor valori si efectuam daca se poate
    this->orders_count = (new_inventory_orders_count > 0) ? new_inventory_orders_count : 0;
    if (this->orders_count > 0 && new_inventory_orders != nullptr) {
        this->orders = new Order [this->orders_count];
        for (int i = 0; i < this->orders_count; i++)
            this->orders[i] = new_inventory_orders[i];
    } else {
        this->orders = nullptr;
        this->orders_count = 0;
    }
}

// Functii de update
// Ele sunt apelate de functia principala de update petru a modifica starea inventarului
// Sunt dezvoltate pentru implementari si adaptari ulterioare
void Inventory::update_inventory_id(Inventory &inventory, const void *new_id) {
    inventory.set_inventory_id(static_cast<const char *>(new_id));
}

void Inventory::update_inventory_name(Inventory &inventory, const void *new_name) {
    inventory.set_inventory_name(static_cast<const char *>(new_name));
}

void Inventory::update_inventory_address(Inventory &inventory, const void *new_address) {
    inventory.set_inventory_address(static_cast<const char *>(new_address));
}

void Inventory::update_inventory_phone(Inventory &inventory, const void *new_phone) {
    inventory.set_inventory_phone(static_cast<const char *>(new_phone));
}

void Inventory::update_inventory_email(Inventory &inventory, const void *new_email) {
    inventory.set_inventory_email(static_cast<const char *>(new_email));
}

struct InventoryMaterialsUpdate {
    const Material *new_materials;
    int new_materials_count;
};

void Inventory::update_inventory_materials(Inventory &inventory, const void *new_data) {
    const auto *u = static_cast<const InventoryMaterialsUpdate *>(new_data);
    inventory.set_inventory_materials(u->new_materials, u->new_materials_count);
}

struct ProvidersUpdate {
    const Provider *new_providers;
    int new_providers_count;
};

void Inventory::update_inventory_providers(Inventory &inventory, const void *new_data) {
    const auto *u = static_cast<const ProvidersUpdate *>(new_data);
    inventory.set_inventory_providers(u->new_providers, u->new_providers_count);
}

struct OrdersUpdate {
    const Order *new_orders;
    int new_orders_count;
};

void Inventory::update_inventory_orders(Inventory &inventory, const void *new_data) {
    const auto *u = static_cast<const OrdersUpdate *>(new_data);
    inventory.set_inventory_orders(u->new_orders, u->new_orders_count);
}

void Inventory::update_inventory(Inventory &inventory, void (*func)(Inventory &, const void *), const void *new_data) {
    if (func == nullptr)
        return;
    func(inventory, new_data);
}

// Metode care modifica starea obiectului
void Inventory::add_material(const Material &material) {
    // Alocam memorie pentru a putea adauga noul material si copiem materialele vechi
    const auto new_materials = new Material[this->materials_count + 1];
    for (int i = 0; i < this->materials_count; i++)
        new_materials[i] = this->materials[i];
    new_materials[this->materials_count++] = material;

    // Eliberam memoria folosita anterior
    delete[] this->materials;
    this->materials = new_materials;
}

void Inventory::add_provider(const Provider &provider) {
    // Alocam memorie pentru a putea adauga noul furnizor si copiem furnizorii vechi
    const auto new_providers = new Provider[this->providers_count + 1];
    for (int i = 0; i < this->providers_count; i++)
        new_providers[i] = this->providers[i];
    new_providers[this->providers_count++] = provider;

    // Eliberam memoria folosita anterior
    delete[] this->providers;
    this->providers = new_providers;
}

void Inventory::add_order(const Order &order) {
    // Alocam memorie pentru a putea adauga noua comanda si copiem comenzile vechi
    const auto new_orders = new Order[this->orders_count + 1];
    for (int i = 0; i < this->orders_count; i++)
        new_orders[i] = this->orders[i];
    new_orders[this->orders_count++] = order;

    // Eliberam memoria folosita anterior
    delete[] this->orders;
    this->orders = new_orders;
}

Material *Inventory::find_material_by_id(const char *find_id) const {
    if (find_id != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            if (this->materials[i].get_material_id() != nullptr && strcmp(this->materials[i].get_material_id(), find_id) == 0)
                return &this->materials[i];
    return nullptr;
}

Provider *Inventory::find_provider_by_id(const char *find_id) const {
    if (find_id != nullptr)
        for (int i = 0; i < this->providers_count; i++)
            if (this->providers[i].get_provider_id() != nullptr && strcmp(this->providers[i].get_provider_id(), find_id) == 0)
                return &this->providers[i];
    return nullptr;
}

Order *Inventory::find_order_by_id(const char *find_id) const {
    if (find_id != nullptr)
        for (int i = 0; i < this->orders_count; i++)
            if (this->orders[i].get_order_id() != nullptr && strcmp(this->orders[i].get_order_id(), find_id) == 0)
                return &this->orders[i];
    return nullptr;
}

// Logica de sortare pentru atributele instantei curente
void Inventory::sort_materials_by_name_ascending() {
    for (int i = 0; i < this->materials_count - 1; i++)
        for (int j = i + 1; j < this->materials_count; j++) {
            const char *material_name_i = this->materials[i].get_material_name();
            const char *material_name_j = this->materials[j].get_material_name();
            if (material_name_i != nullptr && material_name_j != nullptr) {
                if (strcmp(material_name_i, material_name_j) > 0)
                    Material::swap(this->materials[i], this->materials[j]);
            } else if (material_name_i == nullptr && material_name_j != nullptr)
                Material::swap(this->materials[i], this->materials[j]);
        }
}

void Inventory::sort_materials_by_name_descending() {
    for (int i = 0; i < this->materials_count - 1; i++)
        for (int j = i + 1; j < this->materials_count; j++) {
            const char *material_name_i = this->materials[i].get_material_name();
            const char *material_name_j = this->materials[j].get_material_name();
            if (material_name_i != nullptr && material_name_j != nullptr) {
                if (strcmp(material_name_i, material_name_j) < 0)
                    Material::swap(this->materials[i], this->materials[j]);
            } else if (material_name_i == nullptr && material_name_j != nullptr)
                Material::swap(this->materials[i], this->materials[j]);
        }
}

void Inventory::sort_materials_by_quantity_ascending() {
    for (int i = 0; i < this->materials_count - 1; i++)
        for (int j = i + 1; j < this->materials_count; j++)
            if (this->materials[i].get_material_quantity() > this->materials[j].get_material_quantity())
                Material::swap(this->materials[i], this->materials[j]);
}

void Inventory::sort_materials_by_quantity_descending() {
    for (int i = 0; i < this->materials_count - 1; i++)
        for (int j = i + 1; j < this->materials_count; j++)
            if (this->materials[i].get_material_quantity() < this->materials[j].get_material_quantity())
                Material::swap(this->materials[i], this->materials[j]);
}

void Inventory::sort_orders_by_total_price_ascending() {
    for (int i = 0; i < this->orders_count - 1; i++)
        for (int j = i + 1; j < this->orders_count; j++)
            if (this->orders[i].get_order_total_price() > this->orders[j].get_order_total_price())
                Order::swap(this->orders[i], this->orders[j]);
}

void Inventory::sort_orders_by_total_price_descending() {
    for (int i = 0; i < this->orders_count - 1; i++)
        for (int j = i + 1; j < this->orders_count; j++)
            if (this->orders[i].get_order_total_price() < this->orders[j].get_order_total_price())
                Order::swap(this->orders[i], this->orders[j]);
}

// Extragerea comenzilor in functie de ID-ul furnizorului
Order *Inventory::get_orders_by_provider_id(const char *provider_id, int &result_count) {
    if (provider_id == nullptr) {
        result_count = 0;
        return nullptr;
    }

    const auto *to_search_orders = this->get_inventory_orders();
    result_count = 0;
    for (int i = 0; i < this->orders_count; i++)
        if (to_search_orders[i].get_order_provider_id() != nullptr && strcmp(to_search_orders[i].get_order_provider_id(), provider_id) == 0)
            result_count++;

    if (result_count == 0)
        return nullptr;

    auto *result = new Order[result_count];
    int index = 0;
    for (int i = 0; i < this->orders_count; i++)
        if (to_search_orders[i].get_order_provider_id() != nullptr && strcmp(to_search_orders[i].get_order_provider_id(), provider_id) == 0)
            result[index++] = to_search_orders[i];

    return result;
}

// Extragerea materialelor care au un stoc critic
Material *Inventory::get_critical_materials(int &result_count) {
    result_count = 0;
    auto const *to_search_materials = this->get_inventory_materials();
    for (int i = 0; i < this->get_inventory_materials_count(); i++)
        if (to_search_materials[i].get_material_critical() >= to_search_materials[i].get_material_quantity())
            result_count++;

    if (result_count == 0)
        return nullptr;

    auto *result = new Material[result_count];
    int index = 0;
    for (int i = 0; i < this->get_inventory_materials_count(); i++)
        if (to_search_materials[i].get_material_critical() >= to_search_materials[i].get_material_quantity())
            result[index++] = to_search_materials[i];

    return result;
}

// Extragerea elementelor care fac parte dintr-o categorie anume
Material *Inventory::get_materials_by_category(const Material::Category &category, int &result_count) {
    result_count = 0;
    auto const *to_search_materials = this->get_inventory_materials();

    for (int i = 0; i < this->materials_count; i++)
        if (to_search_materials[i].get_material_category() == category)
            result_count++;

    if (result_count == 0)
        return nullptr;

    auto *result = new Material[result_count];
    int index = 0;
    for (int i = 0; i < this->materials_count; i++)
        if (to_search_materials[i].get_material_category() == category)
            result[index++] = to_search_materials[i];

    return result;
}

// Logica de Business a inventarului
// Modificarea starii obiectelor interconectate
void Inventory::consume_material(const char *material_id, const double &quantity) {
    Material *material = this->find_material_by_id(material_id);

    if (material == nullptr)
        return;

    const double new_quantity = material->get_material_quantity() - quantity;

    if (new_quantity < 0)
        return;

    Material::update_material(*material, Material::update_material_quantity, &new_quantity);
}

// Receptionarea unei comenzi
void Inventory::receive_order(Order *order) {
    // Verificam existenta comenzii
    if (order == nullptr)
        return;

    // Verificam state-ul comenzii
    // Nu o putem procesa de 2 ori sau daca a fost anulata
    if (order->get_order_status() != Order::Status::pending)
        return;

    // Extragem informatia din obiectul order
    char **materials_id = order->get_order_materials_id();
    const double *quantities = order->get_order_quantities();
    const int order_materials_count = order->get_order_materials_count();

    if (materials_id == nullptr || quantities == nullptr || order_materials_count == 0)
        return;

    // Adaugam elementele noi care lipsesc din inventarul curent
    for (int i = 0; i < order_materials_count; i++) {
        if (this->find_material_by_id(materials_id[i]) == nullptr) {
            Material new_material(materials_id[i], "", "", 0.0, 0.0, 0.0, Material::Category::others);
            add_material(new_material);
        }
    }

    // Actualizam quantity pentru toate elementele implicate din comanda
    for (int i = 0; i < order_materials_count; i++) {
        Material *material = this->find_material_by_id(materials_id[i]);
        if (material != nullptr) {
            double new_quantity = material->get_material_quantity() + quantities[i];
            Material::update_material(*material, Material::update_material_quantity, &new_quantity);
        }
    }

    // Finalizam procesul modificand state-ul obiectului Order primit la delivered
    constexpr auto new_status = Order::Status::delivered;
    Order::update_order(*order, Order::update_order_status, &new_status);
}

// Calcularea intregii valori a inventarului
double Inventory::calculate_inventory_value() const {
    double total = 0;
    for (int i = 0; i < this->materials_count; i++)
        total += this->materials[i].get_material_quantity() * this->materials[i].get_material_unit_price();

    return total;
}

// Supraincarcarea operatorului de atribuire
// Nu mai este nevoie sa initializam pointerii la nullptr pentru ca avem garantia constructorilor ca putem sterge zonele de memorie alocate
Inventory &Inventory::operator=(const Inventory &other) {
    if (this == &other)
        return *this;

    set_inventory_id(other.get_inventory_id());
    set_inventory_name(other.get_inventory_name());
    set_inventory_address(other.get_inventory_address());
    set_inventory_phone(other.get_inventory_phone());
    set_inventory_email(other.get_inventory_email());
    set_inventory_materials(other.get_inventory_materials(), other.get_inventory_materials_count());
    set_inventory_providers(other.get_inventory_providers(), other.get_inventory_providers_count());
    set_inventory_orders(other.get_inventory_orders(), other.get_inventory_orders_count());

    return *this;
}

// Supraincarcarea operatorilor relationali
// Aplicam si aici verificari ale validitatii datelor pentru a putea folosi strcmp
bool Inventory::operator==(const Inventory &other) const {
    if ((this->id == nullptr) != (other.id == nullptr)) return false;
    if (this->id != nullptr && other.id != nullptr && strcmp(this->id, other.id) != 0) return false;

    if ((this->name == nullptr) != (other.name == nullptr)) return false;
    if (this->name != nullptr && other.name != nullptr && strcmp(this->name, other.name) != 0) return false;

    if ((this->address == nullptr) != (other.address == nullptr)) return false;
    if (this->address != nullptr && other.address != nullptr && strcmp(this->address, other.address) != 0) return false;

    if ((this->phone == nullptr) != (other.phone == nullptr)) return false;
    if (this->phone != nullptr && other.phone != nullptr && strcmp(this->phone, other.phone) != 0) return false;

    if ((this->email == nullptr) != (other.email == nullptr)) return false;
    if (this->email != nullptr && other.email != nullptr && strcmp(this->email, other.email) != 0) return false;

    if (this->materials_count != other.materials_count) return false;
    if (this->providers_count != other.providers_count) return false;
    if (this->orders_count != other.orders_count) return false;

    if ((this->materials == nullptr) != (other.materials == nullptr)) return false;
    if (this->materials != nullptr)
        for (int i = 0; i < this->materials_count; i++)
            if (this->materials[i] != other.materials[i]) return false;

    if ((this->providers == nullptr) != (other.providers == nullptr)) return false;
    if (this->providers != nullptr)
        for (int i = 0; i < this->providers_count; i++)
            if (this->providers[i] != other.providers[i]) return false;

    if ((this->orders == nullptr) != (other.orders == nullptr)) return false;
    if (this->orders != nullptr)
        for (int i = 0; i < this->orders_count; i++)
            if (this->orders[i] != other.orders[i]) return false;

    return true;
}

bool Inventory::operator!=(const Inventory &other) const {
    return !(*this == other);
}

// Supraincarcarea operatorilor de I/O
std::istream &operator>>(std::istream &is, Inventory &inventory) {
    char inventory_id[256];
    char inventory_name[256];
    char inventory_address[256];
    char inventory_phone[256];
    char inventory_email[256];
    int inventory_materials_count;
    int inventory_providers_count;
    int inventory_orders_count;

    std::cout << "Enter inventory ID: ";
    is >> inventory_id;
    inventory.set_inventory_id(inventory_id);

    std::cout << "Enter inventory name: ";
    is >> inventory_name;
    inventory.set_inventory_name(inventory_name);

    std::cout << "Enter address: ";
    is >> inventory_address;
    inventory.set_inventory_address(inventory_address);

    std::cout << "Enter phone: ";
    is >> inventory_phone;
    inventory.set_inventory_phone(inventory_phone);

    std::cout << "Enter email: ";
    is >> inventory_email;
    inventory.set_inventory_email(inventory_email);

    // Setarea capacitatilor memoriei viitoare
    std::cout << "Enter number of materials: ";
    is >> inventory_materials_count;

    std::cout << "Enter number of providers: ";
    is >> inventory_providers_count;

    std::cout << "Enter number of orders: ";
    is >> inventory_orders_count;

    for (int i = 0; i < inventory_materials_count; i++) {
        std::cout << "\n-- Material " << i + 1 << " --\n";
        Material material;
        is >> material;
        inventory.add_material(material);
    }

    for (int i = 0; i < inventory_providers_count; i++) {
        std::cout << "\n-- Provider " << i + 1 << " --\n";
        Provider provider;
        is >> provider;
        inventory.add_provider(provider);
    }

    for (int i = 0; i < inventory_orders_count; i++) {
        std::cout << "\n-- Order " << i + 1 << " --\n";
        Order order;
        is >> order;
        inventory.add_order(order);
    }

    return is;
}

std::ostream &operator<<(std::ostream &os, const Inventory &inventory) {
    os << "[ " << (inventory.id ? inventory.id : "N/A") << " ] " << (inventory.name ? inventory.name : "N/A") << "\n";
    os << "  Address    : " << (inventory.address ? inventory.address : "N/A") << "\n";
    os << "  Phone      : " << (inventory.phone ? inventory.phone : "N/A") << "\n";
    os << "  Email      : " << (inventory.email ? inventory.email : "N/A") << "\n";
    os << "  Materials  : " << inventory.materials_count << "\n";
    os << "  Providers  : " << inventory.providers_count << "\n";
    os << "  Orders     : " << inventory.orders_count << "\n\n";

    return os;
}

bool Inventory::verify_inventory_email(const char *email) {
    if (email == nullptr)
        return false;

    const char *at_pos = strchr(email, '@');
    if (at_pos == nullptr || at_pos == email || at_pos >= email + strlen(email) - 1)
        return false;

    const char *dot_pos = strrchr(at_pos, '.');
    if (dot_pos == nullptr || dot_pos == at_pos + 1 || dot_pos >= email + strlen(email) - 1)
        return false;

    return true;
}

bool Inventory::verify_inventory_phone(const char *phone) {
    if (phone == nullptr)
        return false;

    if (strlen(phone) != 10)
        return false;

    for (int i = 0; i < 10; i++)
        if (phone[i] < '0' || phone[i] > '9')
            return false;

    return true;
}

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