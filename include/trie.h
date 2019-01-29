#ifndef PRACTICE_TRIE_H
#define PRACTICE_TRIE_H

#include <string>

namespace Trie
{
  static const size_t ALPHABET_SIZE = 26; // Only lower case english letters

  struct TrieNode
  {
      int word_count = 0;
      int prefix_count = 0;
      TrieNode* children[ALPHABET_SIZE] = {nullptr};
  };

  void destroy_trie(TrieNode* node);

  void add_word(TrieNode* node, const std::string& word, const int& index = 0);

  bool find_word(TrieNode* node, const std::string& word, const int& index = 0);

  void print_trie(TrieNode* node);
}

#endif //PRACTICE_TRIE_H
