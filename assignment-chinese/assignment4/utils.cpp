#include <algorithm>
#include <string>
#include <tuple>

bool operator<(const Token& a, const Token& b) {
  return std::tie(a.src_offset, a.content) < std::tie(b.src_offset, b.content);
}

bool operator<(const Misspelling& a, const Misspelling& b) { return a.token < b.token; }

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred) {
  std::vector<Iterator> its{begin};
  for (auto it = begin; it != end; ++it) {
    if (pred(*it))
      its.push_back(it);
  }
  its.push_back(end);
  return its;
}

void Token::clean(const std::string& source) {
  auto begin = source.begin() + src_offset;
  auto end = source.begin() + src_offset + content.size();

  auto left = std::find_if(begin, end, ::isalnum);
  auto right =
      std::find_if(std::make_reverse_iterator(end), std::make_reverse_iterator(begin), ::isalnum)
          .base();
  src_offset += std::distance(begin, left);

  if (left < right) {
    content = std::string(left, right);
  } else {
    content = "";
  }

  std::transform(content.begin(), content.end(), content.begin(), ::tolower);
}

/* ========================================================================= *
 * Damerau–Levenshtein 距离算法                                              *
 *                                                                           *
 * 来源：                                                                    *
 * https://github.com/sp1ff/damerau-levenshtein                              *
 * ========================================================================= */

size_t levenshtein(const std::string& s1, const std::string& s2) {
  /* 如果长度差过大，可以直接确定 D-L 距离大于 1。 */
  size_t diff = std::abs((ptrdiff_t)s1.size() - (ptrdiff_t)s2.size());
  if (diff > 1)
    return diff;

  /* 字符串等长时统计不匹配位置，并在可能的情况下提前退出。 */
  if (diff == 0) {
    size_t mismatches = std::inner_product(s1.begin(), s1.end(), s2.begin(), 0UL, std::plus<>(),
                                           std::not_equal_to<>());
    if (mismatches <= 1)
      return mismatches;
  }

  /* 否则运行优化后的 D-L 动态规划算法；
   * 一旦可能的最小 D-L 距离大于 1，就会提前退出。 */
  const std::size_t l1 = s1.size(), l2 = s2.size();
  std::vector<size_t> col(l2 + 1), prevCol(l2 + 1);
  for (size_t i = 0; i < prevCol.size(); i++)
    prevCol[i] = i;
  for (size_t i = 0; i < l1; i++) {
    col[0] = i + 1;
    size_t row_min = col[0];
    for (size_t j = 0; j < l2; j++) {
      col[j + 1] =
          std::min({prevCol[1 + j] + 1, col[j] + 1, prevCol[j] + (s1[i] == s2[j] ? 0 : 1)});
      row_min = std::min(row_min, col[j + 1]);
    }
    if (row_min > 1)
      return row_min;
    col.swap(prevCol);
  }

  return prevCol[l2];
}
