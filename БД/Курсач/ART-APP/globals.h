#ifndef GLOBALS_H
#define GLOBALS_H

#pragma once

enum class UserRole {
    Admin,
    Teacher,
    Student
};

// Объявление внешней переменной
extern UserRole currentUserRole;

#endif // GLOBALS_H
