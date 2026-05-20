#pragma once
#include "transactions.h"

class TransactionFactory {
public:
    static std::unique_ptr<Transaction> create_purchase_order(const std::string &id, const std::string &date, const std::vector<Material> &materials,
                                                              const std::string &provider_id, const PurchaseOrder::Status &status) {
        return std::make_unique<PurchaseOrder>(id, date, materials, provider_id, status);
    }

    static std::unique_ptr<Transaction> create_consumption_record(const std::string &id, const std::string &date, const std::vector<Material> &materials,
                                                               const std::string &project_name, const std::string &department) {
        return std::make_unique<ConsumptionRecord>(id, date, materials, project_name, department);
    }

    static std::unique_ptr<Transaction> create_return_transaction(const std::string &id, const std::string &date, const std::vector<Material> &materials,
                                                                   const std::string &original_transaction_id, const std::string &reason) {
        return std::make_unique<ReturnTransaction>(id, date, materials, original_transaction_id, reason);
    }

    static std::unique_ptr<Transaction> create_adjustment_transaction(const std::string &id, const std::string &date, const std::vector<Material> &materials,
                                                                        const std::string &reason) {
        return std::make_unique<AdjustmentTransaction>(id, date, materials, reason);
    }
};