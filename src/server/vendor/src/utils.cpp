#include "main.h"

bool isNumerical(string str) {
    try {
        size_t pos;
        stod(str, &pos); // or use std::stod for floating-point numbers
        return pos == str.length(); // Ensure the entire string is consumed
    } catch (const invalid_argument&) {
        return false; // Conversion failed
    } catch (const out_of_range&) {
        return false; // Value is out of the range of int or double
    }
}

bool isIntNumerical(string str) {
    try {
        size_t pos;
        stoi(str, &pos); // or use std::stod for floating-point numbers
        return pos == str.length(); // Ensure the entire string is consumed
    } catch (const invalid_argument&) {
        return false; // Conversion failed
    } catch (const out_of_range&) {
        return false; // Value is out of the range of int or double
    }
}

int messageReturnIdRedis(redisContext *redis, string id_entry, int iduser) {
    redisCommand(redis, "XADD %s * operation_id 1 iduser %d", id_entry.c_str(), iduser);
    return 0;
}

int statusErrMessageRedis(redisContext *redis, string id_entry) {
    redisCommand(redis, "XADD %s * operation_id 2", id_entry);
    return 0;
}

int messageStatusOkRedis(redisContext *redis, string id_entry) {
    redisCommand(redis, "XADD %s * operation_id 3", id_entry);
    return 0;
}