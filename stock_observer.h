#pragma once
#include "materials.h"
#include <iostream>
#include <iomanip>

class StockObserver {
    public:
    virtual ~StockObserver() = default;

    virtual void on_low_stock(const Material& material) = 0;
};

class LowStockAlert: public StockObserver {
    public:
    void on_low_stock(const Material& material) override {
        std::cout << "LOW STOCK WARNING\n";
        std::cout << "|  " << material.get_material_id() << "  " << material.get_material_name() << "\n";
        std::cout << "|  Quantity   " << std::fixed << std::setprecision(2)
                  << material.get_material_quantity() << " " << material.get_material_measure_unit() << "\n";
        std::cout << "|  Critical   " << std::fixed << std::setprecision(2)
                  << material.get_material_critical() << " " << material.get_material_measure_unit() << "\n";
        std::cout << "|_\n\n";
    }
};