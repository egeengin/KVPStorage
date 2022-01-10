#ifndef KVPSTORAGE_DAOINMEMORY_H
#define KVPSTORAGE_DAOINMEMORY_H

#include <string>
#include <IDao.h>
#include <json.hpp>

class DaoInMemory : public IDao {
public:
    static DaoInMemory &GetInstance();

    DaoInMemory(const DaoInMemory &orig) = delete;

    virtual ~DaoInMemory();

    bool SetKVP(std::string &key, std::string &value) override;

    bool GetKVP(std::string &key) override;

    bool DeleteKVP(std::string &key) override;

private:
    inline static const std::string SettingsFile = "settings.json";

    DaoInMemory() = default;

    bool ReadSettingsFromFile(nlohmann::json &jsonfile, std::string filename);

    bool WriteSettingsToFile(nlohmann::json &jsonfile, std::string filename);

};

#endif //KVPSTORAGE_DAOINMEMORY_H
