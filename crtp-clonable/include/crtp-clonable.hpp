#pragma once

#include <memory>
#include <string>
#include <type_traits>

/// Interface de classe clonable via un membre clone()
struct clonable_t
{
  virtual std::unique_ptr<clonable_t> clone() const = 0;
  virtual ~clonable_t() = default;
};

// Implementez enable_clone_t.

/// enable_clone_t est une classe CRTP qui s'appuie sur le constructeur de copie
/// de la classe fille pour fournir une surcharge de clone() et implementer
/// l'interface clonable_t.
template <typename T> 
struct enable_clone_t : clonable_t
{
  std::unique_ptr<clonable_t> clone() const override
  {
    // Avoids use of deleted function.
    if constexpr (std::is_copy_constructible_v<T>)
    {
      return std::make_unique<T>(*static_cast<const T*>(this));
    }
    else
    {
      return nullptr;
    }     
  }
};
