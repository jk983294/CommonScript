priority_queue<int> q;                               // default big first
priority_queue<int, vector<int>, greater<int> > q1;  // small first

make_heap(iv.begin(), iv.end());                  // default max heap
make_heap(iv.begin(), iv.end(), greater<int>());  // min heap

sort(begin(v), end(v));                  // small to big
sort(begin(v), end(v), greater<int>());  // big to small

for_each(v.begin(), v.end(), [](int& x) { ++x; });                         // all + 1
copy_if(v.begin(), v.end(), target.begin(), [](int x) { return x > 5; });  // copy if x > 5 to target vector

return v.back();  // retun vector's last element, useful for return dp last result

std::vector<int> tick(n, 0);
std::iota(tick.begin(), tick.end(), 1);

/**
 * head node technical get rid of first node null check
 */
ListNode* mergeKListsHeap(vector<ListNode*>& lists) {
    ListNode head(0);
    ListNode* pNode = &head;
    pNode->next = getNode();
    pNode = node->next;
    return head.next;
}

// appending vector to vector, a = a + b
a.insert(a.end(), b.begin(), b.end());
std::copy(b.begin(), b.end(), std::back_inserter(a));

// collect map vaule to vec
std::unordered_map<int, int> m;
std::vector<int> vec_key, vec_value;
std::transform(m.begin(), m.end(), std::back_inserter(vec_key), [](const auto &pair){return pair.first;});
std::transform(m.begin(), m.end(), std::back_inserter(vec_value), [](const auto &pair){return pair.second;});
std::copy_if(v.begin(), v.end(), std::back_inserter(v_to), [](const auto &d){return d > 0;});

static auto anyone = [](auto&& k, auto&&... args) ->bool { return ((args == k) || ...); };
if(anyone(x,'x','X','e','E','.')){
    work();
}

// Sort based on multiple fields
bool CompareData(const T& a, const T& b) { 
   if (a.PrimaryCondition < b.PrimaryCondition) return true;
   if (b.PrimaryCondition < a.PrimaryCondition) return false;

   // a=b for primary condition, go to secondary
   if (a.SecondaryCondition < b.SecondaryCondition) return true;
   if (b.SecondaryCondition < a.SecondaryCondition) return false;

   // ...
   return false;
}

// vector remove nan inplace
x.erase(std::remove_if(std::begin(x), std::end(x), [](const auto& value) { return std::isnan(value); }),
            std::end(x));

// struct field upper bound
struct Data {
    int64_t usec;
};
Data tmp;
tmp.usec = tgt_usec;
auto itr = std::upper_bound(vec.begin(), vec.end(), tmp, [](auto& l, auto& r) {
    return l.usec < r.usec;
});
      