#pragma once
#include <iosfwd>

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
    void set_material_unit_price(const double &new_unit_price); // Actualizeaza pretul unitar
    void set_material_quantity(const double &new_material_quantity); // Actualizeaza cantitatea
    void set_material_category(const Category &new_material_category); // Actualizeaza categoria
};