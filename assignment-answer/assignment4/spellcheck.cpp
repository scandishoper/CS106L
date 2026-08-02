#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  /* TODO: Implement this method */
  Corpus tokens;  
  std::vector<std::string::iterator> space = find_all(source.begin(), source.end(), [](unsigned char c) {return std::isspace(c);});
  std::transform(space.begin(), space.end() - 1, space.begin() + 1, std::inserter(tokens, tokens.end()), [&source](auto left, auto right) {return Token(source, left, right);});
  // std::erase_if(tokens, [](const Token& token) {return token.content.empty();});
  std::erase_if(tokens, [](const Token& token) {
    return token.content.empty();
});
  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  /* TODO: Implement this method */
  namespace rv = std::ranges::views;
  auto view = source 
              | rv::filter([&](const Token& token) {
                  return !dictionary.contains(token.content);
              })
              | rv::transform([&](const Token& token) {
                  auto suggestion_view = dictionary
                  | rv::filter([&](const std::string& word) {
                      return levenshtein(token.content, word) == 1;
                  });
                  std::set<std::string> suggestion (suggestion_view.begin(), suggestion_view.end());
                  return Misspelling{token, suggestion};
              })
              | rv::filter([&](const Misspelling& misspelling) {
                  return !misspelling.suggestions.empty();
              });
  return std::set<Misspelling>(view.begin(), view.end());
};

/* Helper methods */

#include "utils.cpp"