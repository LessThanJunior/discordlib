#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H
#include <cstdint>
#include <optional>
#include <string>

class snowflake{
    uint64_t timestamp : 42;
    uint8_t internalWorkerId : 5;
    uint8_t internalProcessId : 5;
    uint16_t increment : 12;
public:
    snowflake(uint64_t id);
    snowflake(std::string id);
    snowflake();
    uint64_t id;
    uint64_t getTimestamp() const;
    uint16_t getInternalWorkerId() const;
    uint16_t getInternalProcessId() const;
    uint16_t getIncrement() const;
    operator uint64_t() const;
    bool operator >(uint64_t id) const;
    bool operator <(uint64_t id) const;
    bool operator ==(uint64_t id) const;
    bool operator >(const snowflake& other) const;
    bool operator <(const snowflake& other) const;
    bool operator ==(const snowflake& other) const;
}__attribute__((packed));

snowflake getValue(const std::optional<snowflake>& id);
#endif