#include "trie.h"

#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

namespace Trie
{
  static const unsigned char START_CHAR = 'a';

  // Recursively delete the children of the node if they exist
  void destroy_trie(TrieNode *node)
  {
      assert(node);

      if (node->word_count == 0 || node->prefix_count == 0)
          return;

      int i = 0;
      for(; i < ALPHABET_SIZE; ++i)
      {
          if (node->children[i])
              destroy_trie(node->children[i]);
          delete node->children[i];
      }
  }

  // Recursively navigate the trie to add a word, chopping one char at a time
  void add_word(TrieNode *node, const string& word, const int& index)
  {
      assert(node);
      if (index >= word.size())
      {
          node->word_count++;   // This node finishes a word
          return;
      }
      node->prefix_count++;     // We have an incomplete word
      const int position = word[index] - START_CHAR;
      if (!node->children[position])
            node->children[position] = new TrieNode();
      add_word(node->children[position], word, index + 1);
  }

  bool find_word(TrieNode *node, const string& word, const int& index)
  {
        if (index == word.size())
            return true;  // Base Case: word has been found
        const int position = word[index] - START_CHAR;
        if (node->children[position])
            return find_word(node->children[position], word, index + 1);
        return false;
  }

  void consolidate(TrieNode* node, vector<string>& vec, const int level)
  {
      int i = 0;
      for(; i < ALPHABET_SIZE; ++i)
      {
          if (!node->children[i])
          {
              vec[level].append(1, START_CHAR + i);
              consolidate(node->children[i], vec, level + 1);
          }
      }
  }

  void print_trie(TrieNode* node)
  {
      assert(node);

      static const int max_depth = 10;
      vector<string> levels(max_depth);
      consolidate(node, levels, 0);
      for(const auto& s: levels)
          if (!s.empty())
              cout << s << '\n';
  }
}