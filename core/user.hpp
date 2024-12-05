#pragma once

#include <bcrypt.h>
#include "logger.hpp"
#include "uuid.hpp"

namespace Core {
    class User {
    public:
        enum class SecurityLevel{ ROOT, ADMIN, SUPERVISOR, USER };
        explicit User(const std::string_view name, const SecurityLevel security_level)
            : UUID(UUID::generate_uuid_v4()), m_username(name), m_security_level(security_level) {
        }
    public://Getter and Setters
        [[nodiscard]] std::string uuid() const
        {
            return UUID;
        }

        void set_name(const std::string_view name) {
            m_username = name;
        }

        [[nodiscard]] std::string name() const {
            return m_username;
        }

        void set_password(const std::string_view password) {
            m_password = generate_hash(password);
        }

        void set_security_level(const SecurityLevel security_level) {
            m_security_level = security_level;
        }

        [[nodiscard]] SecurityLevel security_level() const {
            return m_security_level;
        }

        [[nodiscard]] bool is_logged() const {
            return m_is_logged;
        }

        void set_logged(const bool is_logged) {
            m_is_logged = is_logged;
        }

        [[nodiscard]] bool is_valid_password(const std::string_view password) const
        {
            return bcrypt::validatePassword(fmt::format("{}{}", password.data(), UUID), m_password);
        }

    private:
        std::string generate_hash(const std::string_view password) const
        {
            std::string hash_value = fmt::format("{}{}", password.data(), UUID);
            return bcrypt::generateHash(hash_value, 12);
        }

    private:
        const std::string UUID;
        std::string m_username;
        std::string m_password;
        SecurityLevel m_security_level = SecurityLevel::USER;
        bool m_is_logged = false;

    };
} // Core