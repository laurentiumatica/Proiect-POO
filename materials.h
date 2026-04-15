#pragma once
#include <iosfwd>
#include <string>
#include <vector>

class Material {
public:
    // Enum pentru categorii
    enum class Category { wood, metal, insulation, finishes, others};

    // Constructorul implicit (fara parametri)
    Material();

    // Constructorul de copiere
    Material(const Material &other);

    // Constructorul cu parametri
    Material(std::string new_material_id,std::string new_material_name, std::string new_material_measure_unit,\
             double new_material_quantity, double new_material_critical, double new_material_unit_price,
             Category new_material_category);

    // Destructorul clasei
    ~Material();

    // Getters
    // Cuvantul cheie const de la final garanteaza ca aceste metode nu vor modifica starea instantei
    // Const de la inceput garanteaza ca cel care primeste rezultatul nu-l poate modifica
    [[nodiscard]] const std::string& get_material_id() const; // Returneaza identificatorul unic
    [[nodiscard]] const std::string& get_material_name() const; // Returneaza numele materialului
    [[nodiscard]] const std::string& get_material_measure_unit() const; // Returneaza unitatea de masura
    [[nodiscard]] double get_material_critical() const; // Returneaza pragul critic de stoc
    [[nodiscard]] double get_material_unit_price() const; // Returneaza pretul pe unitate
    [[nodiscard]] double get_material_quantity() const; // Returneaza cantitatea curenta disponibila
    [[nodiscard]] Category get_material_category() const; // Returneaza categoria din enumerarea de mai sus

    // Supraincarcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Material &material);
    friend std::ostream &operator<<(std::ostream &os, const Material &material);

    // Supraincarcarea operatorului de atribuire
    Material &operator=(Material other);

    // Supraincarcarea operatorilor relationali
    bool operator==(const Material &other) const; // Verifica egalitatea
    bool operator!=(const Material &other) const; // Verifica inegalitatea

    // Convertor category la string
    static std::string_view material_category_to_string(Category category);

    // Interschimbare
    static void swap(Material &material1, Material &material2) noexcept;

    // Setters
    void set_material_id(std::string new_material_id); // Aloca memorie si actualizeaza ID-ul
    void set_material_name(std::string new_material_name); // Aloca memorie si actualizeaza numele
    void set_material_measure_unit(std::string new_material_measure_unit); // Aloca memorie si actualizeaza unitatea de masura
    void set_material_critical(double new_material_critical); // Actualizeaza limita critica
    void set_material_unit_price(double new_material_unit_price); // Actualizeaza pretul unitar
    void set_material_quantity(double new_material_quantity); // Actualizeaza cantitatea
    void set_material_category(Category new_material_category); // Actualizeaza categoria

private:
    std::string id; // ID-ul materialului
    std::string name; // Numele materialului
    std::string measure_unit; // Unitatea de masura pentru material
    double quantity; // Cantitatea
    double critical; // Limita pentru stocul critic
    double unit_price; // Pretul unitar
    Category category; // Tipul materialului
};