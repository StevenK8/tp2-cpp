#include <crtp-clonable.hpp>

#include <iostream>
#include <memory>

/// Structure contenant un champ some_text. Elle a un constructeur par copie.
struct some_struct_t : public enable_clone_t<some_struct_t> {
  std::string some_text;
};

/// Structure contenant un champ some_text. Son constructeur par copie est
/// supprime, on veut pouvoir utiliser enable_clone_t avec cette classe
/// malgre tout car elle fournit clone().
struct some_other_struct_t : public enable_clone_t<some_other_struct_t> {
  some_other_struct_t(some_other_struct_t const &) = delete;
  some_other_struct_t &operator=(some_other_struct_t const &) = delete;

  std::string some_text;

  some_other_struct_t(std::string text) : some_text(std::move(text)) {}

  std::unique_ptr<clonable_t> clone() const override {
    std::unique_ptr<clonable_t> ptr =
        std::make_unique<some_other_struct_t>(some_text);
    return ptr;
  }
};

int main() {
  // On fait un premier pointeur de notre premiere structure ayant un
  // constructeur par copie
  std::unique_ptr<some_struct_t> some_pointer =
      std::make_unique<some_struct_t>();

  some_pointer->some_text = "some_pointer";

  // On clone le premier pointeur
  std::unique_ptr<clonable_t> some_pointer_clone = some_pointer->clone();

  // On affiche le contenu du clone
  std::cout
      << dynamic_cast<some_struct_t *>(some_pointer_clone.get())->some_text
      << '\n';

  // Meme operation, mais avec l'autre structure qui n'a pas de constructeur par
  // copie mais le membre clone().

  std::unique_ptr<some_other_struct_t> some_other_pointer =
      std::make_unique<some_other_struct_t>("some_other_pointer");

  std::unique_ptr<clonable_t> some_other_pointer_clone =
      some_other_pointer->clone();

  std::cout << dynamic_cast<some_other_struct_t *>(
                   some_other_pointer_clone.get())
                   ->some_text
            << '\n';

  return 0;
}
