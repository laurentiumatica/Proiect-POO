    #include "materials.h"
    #include <algorithm>
    #include <iostream>
    #include <string>
    #include <cmath>
    #include <iomanip>
    #include <regex>

    // Constructorul default
    Material::Material() : quantity(0), critical(0), unit_price(0), category(Category::others) {
    }

    // Constructorul cu parametri
    Material::Material(const std::string_view new_material_id, const std::string_view new_material_name,
                       const std::string_view new_material_measure_unit, const double new_material_quantity,
                       const double new_material_critical, const double new_material_unit_price, const Category new_material_category)
        : id(new_material_id), name(new_material_name),
          measure_unit(new_material_measure_unit), quantity(new_material_quantity),
          critical(new_material_critical), unit_price(new_material_unit_price), category(new_material_category) {
        validate_material_id(id);
        validate_material_name(name);
        validate_material_measure_unit(measure_unit);
        validate_material_quantity(quantity);
        validate_material_critical(critical);
        validate_material_unit_price(unit_price);
    }

    // Copy constructorul
    Material::Material(const Material &other)
        : Material(other.id, other.name, other.measure_unit, other.quantity, other.critical, other.unit_price, other.category) { }

    // Destructor
    Material::~Material() = default;

    // Getters
    const std::string &Material::get_material_id() const { return id; }
    const std::string &Material::get_material_name() const { return name; }
    const std::string &Material::get_material_measure_unit() const { return measure_unit; }
    double Material::get_material_critical() const { return critical; }
    double Material::get_material_unit_price() const { return unit_price; }
    double Material::get_material_quantity() const { return quantity; }
    Material::Category Material::get_material_category() const { return category; }

    // Setters
    void Material::set_material_id(const std::string_view new_material_id) {
        validate_material_id(new_material_id);
        id = new_material_id;
    }

    void Material::set_material_name(const std::string_view new_material_name) {
        validate_material_name(new_material_name);
        name = new_material_name;
    }

    void Material::set_material_measure_unit(const std::string_view new_material_measure_unit) {
        validate_material_measure_unit(new_material_measure_unit);
        measure_unit = new_material_measure_unit;
    }

    void Material::set_material_critical(const double new_material_critical) {
        validate_material_critical(new_material_critical);
        critical = new_material_critical;
    }

    void Material::set_material_unit_price(const double new_material_unit_price) {
        validate_material_unit_price(new_material_unit_price);
        unit_price = new_material_unit_price;
    }

    void Material::set_material_quantity(const double new_material_quantity) {
        validate_material_quantity(new_material_quantity);
        quantity = new_material_quantity;
    }

    void Material::set_material_category(const Category new_material_category) {
        category = new_material_category;
    }

    // Supraincarcare operator de atribuire
    Material &Material::operator=(Material other) {
        std::swap(id, other.id);
        std::swap(name, other.name);
        std::swap(measure_unit, other.measure_unit);
        std::swap(quantity, other.quantity);
        std::swap(critical, other.critical);
        std::swap(unit_price, other.unit_price);
        std::swap(category, other.category);

        return *this;
    }

    // Supraincarcarea operatorilor relationali
    bool Material::operator==(const Material &other) const {
        constexpr double epsilon = 1e-9;

        return id == other.id &&
               name == other.name &&
               measure_unit == other.measure_unit &&
               std::abs(quantity - other.quantity) < epsilon &&
               std::abs(critical - other.critical) < epsilon &&
               std::abs(unit_price - other.unit_price) < epsilon &&
               category == other.category;
    }

    bool Material::operator!=(const Material &other) const { return !(*this == other); }

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

    // Supraincarcarea operatorilor de I/O
    std::ostream &operator<<(std::ostream &os, const Material &material) {
        const std::string_view category = Material::material_category_to_string(material.category);

        os << material.id << "  " << material.name << "\n";
        os << "│  Category   " << category << "\n";
        os << "│  Quantity   " << std::fixed << std::setprecision(2) << material.quantity << " " << material.measure_unit <<
                "\n";
        os << "│  Critical   " << std::fixed << std::setprecision(2) << material.critical << " " << material.measure_unit <<
                "\n";
        os << "│  Price      " << std::fixed << std::setprecision(2) << material.unit_price << " RON\n";
        os << "|_\n\n";

        return os;
    }

    std::istream &operator>>(std::istream &is, Material &material) {

        is.ignore();

        Material::read_string("Enter material ID", [&material](const std::string &s) { material.set_material_id(s); });
        Material::read_string("Enter measure unit", [&material](const std::string &s) { material.set_material_measure_unit(s); });
        Material::read_string("Enter material name", [&material](const std::string &s) { material.set_material_name(s); });
        Material::read_string("Enter material critical level", [&material](const std::string &s) { material.set_material_critical(std::stod(s)); });
        Material::read_string("Enter material unit price", [&material](const std::string &s) { material.set_material_unit_price(std::stod(s)); });
        Material::read_string("Enter material quantity", [&material](const std::string &s) { material.set_material_quantity(std::stod(s)); });
        Material::read_string("Enter material category (0 - wood, 1 - metal, 2 - insulation, 3 - finishes, 4 - others)",
        [&material](const std::string &s) {
            const int cat = std::stoi(s);
            if (cat < 0 || cat > 4)
                throw std::invalid_argument("Category must be between 0 and 4");
            material.set_material_category(static_cast<Material::Category>(cat));
        });

        return is;
    }

    // Convertor category la string
    std::string_view Material::material_category_to_string(const Category category) {
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

    // Functii helper
    void Material::validate_material_id(const std::string_view new_material_id) {
        if (new_material_id.empty()) {
            throw std::invalid_argument("Material ID must not be empty");
        }
        static const std::regex id_regex("^MAT-[0-9]{5}$");
        if (!std::regex_match(new_material_id.begin(), new_material_id.end(), id_regex)) {
            throw std::invalid_argument("Invalid material ID format");
        }
    }

    void Material::validate_material_name(const std::string_view new_material_name) {
        if (new_material_name.empty()) {
            throw std::invalid_argument("Material name must not be empty");
        }
        if (std::ranges::all_of(new_material_name, [](const unsigned char c) { return std::isspace(c); })) {
            throw std::invalid_argument("Material name must contain at least one non-space character");
        }
        if (!std::ranges::all_of(new_material_name,
                                 [](const unsigned char c) { return std::isalnum(c) || std::isspace(c); })) {
            throw std::invalid_argument("Material name must contain only letters, numbers and spaces");
        }
    }

    void Material::validate_material_measure_unit(const std::string_view new_material_measure_unit) {
        if (new_material_measure_unit.empty()) {
            throw std::invalid_argument("Material measure unit must not be empty");
        }
        if (std::ranges::all_of(new_material_measure_unit, [](const unsigned char c) { return std::isspace(c); })) {
            throw std::invalid_argument("Material measure unit must contain at least one non-space character");
        }
        if (!std::ranges::all_of(new_material_measure_unit, [](const unsigned char c) { return std::isalnum(c); })) {
            throw std::invalid_argument("Material measure unit must contain only letters and numbers");
        }
    }

    void Material::validate_material_quantity(const double new_material_quantity) {
        if (new_material_quantity < 0) {
            throw std::invalid_argument("Material quantity must not be negative");
        }
    }

    void Material::validate_material_critical(const double new_material_critical) {
        if (new_material_critical < 0) {
            throw std::invalid_argument("Material critical level must not be negative");
        }
    }

    void Material::validate_material_unit_price(const double new_material_unit_price) {
        if (new_material_unit_price <= 0) {
            throw std::invalid_argument("Material unit price must not be negative or zero");
        }
    }

    void Material::read_string(const std::string_view prompt, auto setter) {
        while (true) {
            try {
                std::cout << prompt << ": ";
                std::string temp;
                std::getline(std::cin, temp);
                setter(temp);
                break;
            } catch (const std::invalid_argument &e) {
                std::cout << "Error: " << e.what() << ". Try again.\n";
            } catch (const std::out_of_range &) {
                std::cout << "Error: value out of range. Try again.\n";
            }
        }
    }
