#pragma once

#include <algorithm>
#include <vector>

// =============================================================================
// ZERO-CONTAINERS - CONSIGNES
//
// Implementez les conteneurs suivants en ecrivant un minimum de code a l'aide
// de std::vector comme seul container, et des algorithmes de la bibliotheque
// standard. Vous devez ecrire le moins de code possible en suivant la regle du
// zero; par exemple vous ne *devez pas* implementer vous-meme les semantiques
// de transfert ou de copie.
//
// Soyez flemmard-e-s, et n'implementez que les fonctions qui sont decrites pour
// chaque conteneur.
// =============================================================================

// stack_t

//  stack_t &push(T val)
// Rajoute un element en-haut de la pile.

//  T &top()
// Permet d'acceder et de modifier l'element en-haut de la pile.

//  T const &top() const
// Permet d'acceder al'element en-haut de la pile sans le modifier.

//  stack_t &pop()
// Supprime l'element en-haut de la pile.

//  std::size_t size() const
// Renvoie la taille de la pile.

template <typename T>
struct stack_t
{
    std::vector<T> data;

    stack_t &push(T val)
    {
        data.push_back(val);
        return *this;
    }

    T &top() { return data.back(); }

    T const &top() const { return data.back(); }

    stack_t &pop()
    {
        data.pop_back();
        return *this;
    }

    std::size_t size() const { return data.size(); }
};

// circular_buffer_t

//  circular_buffer_t &push_back(T val)
// Ajoute une valeur a la fin du circular buffer.

//  circular_buffer_t &insert(std::size_t pos, T val)
// Insere une valeur a une position donnee dans le circular buffer. L'insertion
// doit pouvoir se faire avec une coordonnee superieure a la taille du
// conteneur, en suivant la meme logique que l'operator[].

//  circular_buffer_t &erase(std::size_t pos)
// Supprime une valeur a une position donnee dans le circular buffer, toujours
// en suivant la meme logique que l'operator[] et insert.

//  T const &operator[](std::size_t i) const
// Permet d'acceder a une reference constante vers l'element d'indice i. Le
// conteneur etant un buffer "circulaire", on considere qu'on revient au debut
// du conteneur lorsqu'on depasse la valeur max de l'indice.

//  T &operator[](std::size_t i)
// Permet d'acceder a une reference vers l'element d'indice i. Le conteneur
// etant un buffer "circulaire", on considere qu'on revient au debut du
// conteneur lorsqu'on depasse la valeur max de l'indice.

//  std::size_t size() const
// Renvoie le nombre d'elements dans le circular buffer.

template <typename T>
struct circular_buffer_t
{
    std::vector<T> data;

    circular_buffer_t &push_back(T val)
    {
        data.push_back(val);
        return *this;
    }

    circular_buffer_t &insert(std::size_t pos, T val)
    {
        data.insert(data.begin() + pos % data.size(), val);
        return *this;
    }

    circular_buffer_t &erase(std::size_t pos)
    {

        data.erase(data.begin() + pos % data.size());
        return *this;
    }

    T const &operator[](std::size_t i) const
    {
        return data[i % data.size()];
    }

    T &operator[](std::size_t i)
    {
        return data[i % data.size()];
    }

    std::size_t size() const { return data.size(); }
};

// sorted_vector_t

//  sorted_vector_t &push_back(T val)
// Ajoute une valeur dans le sorted_vector_t. Le vector doit toujours etre trie
// apres l'appel de cette fonction.

//  T const &operator[](std::size_t i) const
// Renvoie la valeur de rang i dans le vector. On ne permet pas les modifs pour
// eviter que l'ordre soit invalide.

//  sorted_vector_t &erase(std::size_t pos)
// Supprime la valeur au rang pos.

//  auto begin() const
// Renvoie un iterateur au debut du vector.

//  auto end() const
// Renvoie un iterateur a la fin du vector.

// std::size_t size() const
// Renvoie la taille du vector.

template <typename T>
struct sorted_vector_t
{
    std::vector<T> data;

    sorted_vector_t &push_back(T val)
    {
        data.push_back(val);
        std::sort(data.begin(), data.end());
        return *this;
    }

    T const &operator[](std::size_t i) const { return data[i]; }

    sorted_vector_t &erase(std::size_t pos)
    {
        data.erase(data.begin() + pos);
        return *this;
    }

    auto begin() const { return data.begin(); }

    auto end() const { return data.end(); }

    std::size_t size() const { return data.size(); }
};
