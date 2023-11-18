 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* s1 = new ListNode();
        ListNode* head = s1;

        int sum;
        int carry = 0;

        while (l1 && l2) {
            sum = l1->val + l2->val + carry;
            if (sum > 9) {
                sum = sum - 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            s1->val = sum;
            if (l1->next && l2->next) {
                s1->next = new ListNode();
                s1 = s1->next;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        while (l1 != nullptr) {
            sum = l1->val + carry;
            if (sum > 9) {
                sum = sum - 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            s1->next = new ListNode(sum);
            s1 = s1->next;
            l1 = l1->next;

        }
        while (l2 != nullptr) {
            sum = l2->val + carry;
            if (sum > 9) {
                sum = sum - 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            s1->next = new ListNode(sum);
            s1 = s1->next;
            l2 = l2->next;
        }
        if (carry == 1) s1->next = new ListNode(1);
        if (s1 == nullptr) {
            s1 = new ListNode(0);
        }
        return head;
    }
};

//int main() {
//    Solution s;
//    ListNode* l1 = new ListNode(9);
//    ListNode* ll = l1;
//    ll->next = new ListNode(9);
//    ll = ll->next;
//    ll->next = new ListNode(9); ll = ll->next;
//    ll->next = new ListNode(9); ll = ll->next;
//    ll->next = new ListNode(9); ll = ll->next;
//    ll->next = new ListNode(9); ll = ll->next;
//    ll->next = new ListNode(9);
//
//    ListNode* l2 = new ListNode(9);
//    ListNode* rr = l2;
//    rr->next = new ListNode(9); rr = rr->next;
//    rr->next = new ListNode(9); rr = rr->next;
//    rr->next = new ListNode(9); rr = rr->next;
//
//
//
//    s.addTwoNumbers(l1, l2);
//
//    return 0;
//}