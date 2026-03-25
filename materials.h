#pragma once
#include <iosfwd>

class Material {
public:
    // Definim un enum strict pentru a grupa categoriile posibile ale unui material
    enum class Category { wood, metal, insulation, finishes, others };

    // Constructorul implicit (fără parametri)
    // Este apelat automat la crearea unui obiect nou dacă nu oferim date de inițializare
    Material();

    // Constructorul de copiere
    // Construiește o instanță nouă copiind exact valorile atributelor dintr-un alt obiect deja existent
    Material(const Material &other);

    // Constructorul cu parametri
    // Folosit pentru a instanția un obiect și a-i seta toate atributele interne într-un singur pas
    Material(const char *id, const char *name, const char *measure_unit,
             const double &quantity, const double &critical,
             const double &unit_price, const Category &category);

    // Destructorul clasei
    // Se apelează automat când un obiect este distrus. Aici eliberăm memoria alocată dinamic
    ~Material();

    // Getters
    // Cuvântul cheie const de la final garantează că aceste metode nu vor modifica starea instanței
    [[nodiscard]] char *get_material_id() const; // Returnează identificatorul unic
    [[nodiscard]] char *get_material_name() const; // Returnează numele materialului
    [[nodiscard]] char *get_material_measure_unit() const; // Returnează unitatea de măsură
    [[nodiscard]] double get_material_critical() const; // Returnează pragul critic de stoc
    [[nodiscard]] double get_material_unit_price() const; // Returnează prețul pe unitate
    [[nodiscard]] double get_material_quantity() const; // Returnează cantitatea curentă disponibilă
    [[nodiscard]] Category get_material_category() const; // Returnează categoria din enumerarea de mai sus

    // Setters
    void set_material_id(const char *new_id); // Alocă memorie și actualizează ID-ul
    void set_material_name(const char *new_name); // Alocă memorie și actualizează numele
    void set_material_measure_unit(const char *new_measure_unit); // Alocă memorie și actualizează unitatea de măsură
    void set_material_critical(const double &new_critical); // Actualizează limita critică
    void set_material_unit_price(const double &new_unit_price); // Actualizează prețul unitar
    void set_material_quantity(const double &new_quantity); // Actualizează cantitatea
    void set_material_category(const Category &new_category); // Actualizează categoria

    // Supraîncărcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Material &material);

    friend std::ostream &operator<<(std::ostream &os, const Material &material);

    // Supraîncărcarea operatorului de atribuire
    Material &operator=(const Material &other);

    // Supraîncărcarea operatorilor relaționali
    bool operator==(const Material &other) const; // Verifică egalitatea
    bool operator!=(const Material &other) const; // Verifică inegalitatea

    static const char *material_category_to_string(const Category &category);

    // Interschimbare
    static void swap(Material &material1, Material &material2) noexcept;

private:
    char *id; // ID-ul materialului
    char *name; // Numele materialului
    char *measure_unit; // Unitatea de măsură pentru material
    double quantity; // Cantitatea
    double critical; // Limita pentru stocul critic
    double unit_price; // Prețul unitar
    Category category; // Tipul materialului
};