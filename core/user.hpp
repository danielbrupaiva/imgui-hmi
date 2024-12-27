#pragma once

#include <bcrypt.h>
#include "logger.hpp"
#include "uuid.hpp"

namespace Core
{

class User final
{
public:
    enum class SecurityLevel { ROOT = 0, ADMIN, SUPERVISOR, USER };

    explicit User() = default;
    explicit User(const std::string_view name, const std::string_view password = "password", const SecurityLevel& security_level = SecurityLevel::USER)
        : UUID(UUID::generate_uuid_v4()), m_username(name), m_hash_stored_password(generate_hash(password)), m_security_level(security_level)
    {
    }

    virtual std::string operator()() const
    {
        return m_username;
    }

    friend bool operator==(const User& lhs, const User& rhs)
    {
        return lhs.UUID == rhs.UUID;
    }

    //Getter
    [[nodiscard]] std::string uuid() const
    {
        return UUID;
    }

    [[nodiscard]] SecurityLevel security_level() const
    {
        return m_security_level;
    }

    [[nodiscard]] bool is_logged() const
    {
        return m_is_logged;
    }

    [[nodiscard]] std::string name() const
    {
        return m_username;
    }
    //Setter
    void set_name(const std::string_view name)
    {
        m_username = name;
    }

    void set_password(const std::string_view password)
    {
        m_hash_stored_password = password;
    }

    [[nodiscard]] std::string hash_password() const
    {
        return m_hash_stored_password;
    }

    void set_security_level(const SecurityLevel& security_level)
    {
        m_security_level = security_level;
    }

        void set_security_level(int security_level)
    {
        m_security_level = static_cast<SecurityLevel>(security_level);
    }

    bool login(const std::string_view password)
    {
        m_is_logged = is_valid_password(password.data());
        return m_is_logged;
    }

    void logout()
    {
        m_is_logged = false;
    }

private:
    [[nodiscard]] bool is_valid_password(const std::string_view password) const
    {
        return bcrypt::validatePassword(password.data(), m_hash_stored_password);
    }

    [[nodiscard]] static std::string generate_hash(const std::string_view password)
    {
        return bcrypt::generateHash(password.data(), 12);
    }

private:
    uint32_t m_id;
    std::string UUID;
    std::string m_username;
    std::string m_hash_stored_password;
    SecurityLevel m_security_level = SecurityLevel::USER;
    bool m_is_logged = false;
};
} // Core
