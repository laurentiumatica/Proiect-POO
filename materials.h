#pragma once
#include <iosfwd>
#include <string>

class Material {
public:
    // Enum pentru categorii
    enum class Category { wood, metal, insulation, finishes, others};

    // Constructorul implicit (fara parametri)
    Material();

    // Constructorul de copiere
    Material(const Material &other);

    // Constructorul cu parametri
    Material(std::string id,std::string name, std::string measure_unit,
             double quantity, double critical, double unit_price, Category category);

    // Destructorul clasei
    ~Material();

    // Setters
    void set_material_critical(double set_critical); // Actualizeaza limita critica
    void set_material_unit_price(double set_unit_price); // Actualizeaza pretul unitar
    void set_material_quantity(double set_quantity); // Actualizeaza cantitatea

    // Getters
    const std::string& get_material_id() const; // Returneaza identificatorul unic
    const std::string& get_material_name() const; // Returneaza numele materialului
    const std::string& get_material_measure_unit() const; // Returneaza unitatea de masura
    double get_material_critical() const; // Returneaza pragul critic de stoc
    double get_material_unit_price() const; // Returneaza pretul pe unitate
    double get_material_quantity() const; // Returneaza cantitatea curenta disponibila
    Category get_material_category() const; // Returneaza categoria din enumerarea de mai sus

    // Supraincarcarea operatorului de atribuire
    Material &operator=(Material other);

    // Supraincarcarea operatorilor relationali
    bool operator==(const Material &other) const; // Verifica egalitatea
    bool operator!=(const Material &other) const; // Verifica inegalitatea

    // Supraincarcarea operatorilor de I/O
    friend std::istream &operator>>(std::istream &is, Material &material);
    friend std::ostream &operator<<(std::ostream &os, const Material &material);

    // Interschimbare
    static void swap(Material &material1, Material &material2) noexcept;

    // Convertor category la string
    static std::string material_category_to_string(Category category);

private:
    std::string id; // ID-ul materialului
    std::string name; // Numele materialului
    std::string measure_unit; // Unitatea de masura pentru material
    double quantity; // Cantitatea
    double critical; // Limita pentru stocul critic
    double unit_price; // Pretul unitar
    Category category; // Tipul materialului
};