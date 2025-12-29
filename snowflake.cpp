#include "snowflake.h"

snowflake::snowflake(uint64_t id)
{
    this->id = id;
    timestamp = id >> 22;
    internalWorkerId = id >> 17 & 0b11111;
    internalProcessId = id >> 12 & 0b11111;
    increment = id & 0xFFF;
}

snowflake::snowflake(std::string id)
{
    this->id = strtoull(id.c_str(), nullptr, 0);
    timestamp = this->id >> 22;
    internalWorkerId = this->id >> 17 & 0b11111;
    internalProcessId = this->id >> 12 & 0b11111;
    increment = this->id & 0xFFF;
}

snowflake::snowflake()
{
    this->id = 0;
    timestamp = 0;
    internalWorkerId = 0;
    internalProcessId = 0;
    increment = 0;
}

snowflake getValue(const std::optional<snowflake>& id) { return id.has_value() ? id.value() : snowflake();}

uint64_t snowflake::getTimestamp() const { return timestamp; }
uint16_t snowflake::getInternalWorkerId() const { return internalWorkerId;}
uint16_t snowflake::getInternalProcessId() const { return internalProcessId;}
uint16_t snowflake::getIncrement() const { return increment;}

snowflake::operator uint64_t() const { return id;}

bool snowflake::operator>(uint64_t id) const { return this->id > id;}

bool snowflake::operator<(uint64_t id) const { return this->id < id;}

bool snowflake::operator==(uint64_t id) const { return this->id == id;}

bool snowflake::operator>(const snowflake& other) const { return this->id > other.id;}

bool snowflake::operator<(const snowflake& other) const { return this->id < other.id;}

bool snowflake::operator==(const snowflake& other) const{ return this->id == other.id;}
