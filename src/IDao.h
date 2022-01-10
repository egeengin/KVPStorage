#ifndef KVPSTORAGE_IDAO_H
#define KVPSTORAGE_IDAO_H

#include <string>

class IDao {
public:
    IDao() {
    };

    virtual bool SetKVP(std::string &key, std::string &value) = 0;

    virtual bool GetKVP(std::string &key) = 0;

    virtual bool DeleteKVP(std::string &key) = 0;

    virtual ~IDao() {
    };
};

#endif //KVPSTORAGE_IDAO_H
