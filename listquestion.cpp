#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// 定义链表节点结构
typedef struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
} ListNode;

class Solution {
public:
    ListNode* deleteDuplicatesSec(ListNode* head) {
        // write code here
        // 边界处理：空链表直接返回
        if (!head) {
            return head;
        }
        
        // 创建虚拟头节点，简化边界情况处理
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* prev = dummy;
        ListNode* current = head;
        
        while (current != nullptr) {
            // 检查当前节点是否与下一个节点重复
            bool isDuplicate = false;
            while (current->next != nullptr && current->val == current->next->val) {
                isDuplicate = true;
                // 删除重复节点并释放内存
                ListNode* temp = current->next;
                current->next = current->next->next;
                delete temp;
            }
            
            if (isDuplicate) {
                // 当前节点也是重复的，需要删除
                ListNode* temp = current;
                prev->next = current->next;
                current = current->next;
                delete temp;
            } else {
                // 当前节点不重复，移动到下一个节点
                prev = prev->next;
                current = current->next;
            }
        }
        
        // 获取新的头节点并释放虚拟头节点
        head = dummy->next;
        delete dummy;
        
        return head;
    }
    ListNode* deleteDuplicates(ListNode* head) {
        // write code here
        if (!head) {
            return head;
        }
        
        ListNode* current = head;
        while (current->next != nullptr) {
            if (current->val == current->next->val) {
                // 删除重复节点
                ListNode* temp = current->next;
                current->next = current->next->next;
                delete temp; // 释放内存，避免内存泄漏
            } else {
                // 移动到下一个节点
                current = current->next;
            }
        }
        
        return head;
    }
    ListNode* oddEvenList(ListNode* head) {
        // write code here
        // 边界处理：空链表、单节点或双节点链表直接返回
        if (!head || !head->next) {
            return head;
        }
        
        // 创建奇偶节点的指针
        ListNode* odd = head;  // 奇数位置节点的头指针
        ListNode* even = head->next;  // 偶数位置节点的头指针
        ListNode* evenHead = even;  // 保存偶数链表的头节点
        
        // 遍历链表，分离奇偶节点
        while (even != nullptr && even->next != nullptr) {
            odd->next = even->next;  // 奇数节点指向后一个奇数节点
            odd = odd->next;  // 移动奇数节点指针
            even->next = odd->next;  // 偶数节点指向后一个偶数节点
            even = even->next;  // 移动偶数节点指针
        }
        
        // 将偶数链表连接到奇数链表的末尾
        odd->next = evenHead;
        
        return head;
    }

    // 反转链表中m到n的部分
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        // 创建虚拟头节点，简化边界情况
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        // 找到第m-1个节点（反转的前一个节点）
        ListNode* pre = dummy;
        for(int i=1; i<m; i++) {
            pre = pre->next;
        }
        
        // 反转从m到n的节点
        ListNode* curr = pre->next;
        ListNode* next;
        for(int i=m; i<n; i++) {
            next = curr->next;
            curr->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    
    // 反转链表中每k个节点一组的部分（O(1)空间复杂度）
    ListNode* reverseKGroup(ListNode* head, int k) {
        // 创建虚拟头节点，简化边界情况
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        // pre指向每组反转的前一个节点
        ListNode* pre = dummy;
        // end指向每组反转的最后一个节点
        ListNode* end = dummy;
        
        while(end->next != nullptr) {
            // 移动end到第k个节点
            for(int i=0; i<k && end != nullptr; i++) {
                end = end->next;
            }
            // 如果剩余节点不足k个，结束循环
            if(end == nullptr) break;
            
            // start指向每组反转的第一个节点
            ListNode* start = pre->next;
            // nextGroup指向每组反转的下一组的第一个节点
            ListNode* nextGroup = end->next;
            
            // 将当前组与下一组断开连接
            end->next = nullptr;
            
            // 反转当前组
            pre->next = reverseList(start);
            
            // 将反转后的组与下一组重新连接
            start->next = nextGroup;
            
            // 更新pre和end为下一组反转的前一个节点
            pre = start;
            end = pre;
        }
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    
    // 辅助函数：反转整个链表
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* curr = head;
        while(curr != nullptr) {
            ListNode* next = curr->next;
            curr->next = pre;
            pre = curr;
            curr = next;
        }
        return pre;
    }

    // 合并两个有序链表
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // 创建虚拟头节点，简化边界处理
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        
        // 同时遍历两个链表，将较小的节点添加到结果链表
        while(l1 != nullptr && l2 != nullptr) {
            if(l1->val <= l2->val) {
                curr->next = l1;
                l1 = l1->next;
            } else {
                curr->next = l2;
                l2 = l2->next;
            }
            curr = curr->next;
        }
        
        // 连接剩余节点
        if (l1 != nullptr) {
            curr->next = l1;
        } else {
            curr->next = l2;
        }
        
        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
    
    // 定义优先队列的比较函数（小根堆）
    struct ListNodeCompare {
        bool operator()(ListNode* a, ListNode* b) {
            return a->val > b->val; // 小根堆：值小的优先级高
        }
    };
    
    // 小根堆（优先队列）实现合并k个链表
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 创建小根堆，存储每个链表的当前头节点
        priority_queue<ListNode*, vector<ListNode*>, ListNodeCompare> minHeap;
        
        // 将所有非空链表的头节点加入堆
        for (ListNode* list : lists) {
            if (list != nullptr) {
                minHeap.push(list);
            }
        }
        
        // 虚拟头节点，简化边界处理
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        
        // 不断从堆中取出最小节点，添加到结果链表
        while (!minHeap.empty()) {
            // 取出堆顶（最小）节点
            ListNode* minNode = minHeap.top();
            minHeap.pop();
            
            // 将最小节点添加到结果链表
            curr->next = minNode;
            curr = curr->next;
            
            // 如果该节点所在链表还有后续节点，将其加入堆
            if (minNode->next != nullptr) {
                minHeap.push(minNode->next);
            }
        }
        
        // 获取结果链表的头节点并删除虚拟节点
        ListNode* result = dummy->next;
        delete dummy;
        
        return result;
    }

    // 检测链表中是否有环（Floyd's Tortoise and Hare算法）
    bool hasCycle(ListNode *head) {
        if(head == nullptr) return false;
        
        ListNode* slow = head;  // 慢指针（乌龟），每次移动1步
        ListNode* fast = head;  // 快指针（兔子），每次移动2步
        
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;        // 慢指针移动1步
            fast = fast->next->next;  // 快指针移动2步
            
            if(slow == fast) {  // 如果相遇，说明有环
                return true;
            }
        }
        
        return false;  // 快指针到达链表末尾，说明没有环
    }

    // 找到链表中环的入口节点（Floyd's Tortoise and Hare算法）
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        if(pHead == nullptr) return nullptr;
        
        ListNode* slow = pHead;  // 慢指针，每次移动1步
        ListNode* fast = pHead;  // 快指针，每次移动2步
        
        // 第一步：检测环的存在
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            
            if(slow == fast) {  // 快慢指针相遇，说明有环
                // 第二步：找到环的入口
                slow = pHead;  // 将慢指针重置到链表头部
                while(slow != fast) {  // 两个指针都以相同速度移动，再次相遇点即为环入口
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;  // 返回环的入口节点
            }
        }
        
        return nullptr;  // 快指针到达链表末尾，说明没有环
    }

    // 找到链表中倒数第k个节点（双指针法）
    ListNode* FindKthToTail(ListNode* pHead, int k) {
        // 处理边界情况：链表为空或k<=0
        if(pHead == nullptr || k <= 0) return nullptr;
        
        ListNode* slow = pHead;  // 慢指针，初始指向链表头部
        ListNode* fast = pHead;  // 快指针，初始指向链表头部
        
        // 第一步：让快指针先走k步
        for(int i=0; i<k; i++) {
            if(fast == nullptr) {  // 如果链表长度小于k，返回nullptr
                return nullptr;
            }
            fast = fast->next;
        }
        
        // 第二步：快慢指针同时移动，直到快指针到达链表末尾
        while(fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
        
        return slow;  // 慢指针此时指向倒数第k个节点
    }

    // 删除链表中倒数第n个节点（双指针法）
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 创建虚拟头节点，简化删除头节点的边界情况
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        
        // 慢指针指向虚拟头节点
        ListNode* slow = dummy;
        // 快指针指向虚拟头节点
        ListNode* fast = dummy;
        
        // 快指针先走n+1步，这样快慢指针之间的距离为n+1
        for(int i=0; i<n+1; i++){
            // 题目保证n有效，此检查可以省略，但保留以增强鲁棒性
            if(fast == nullptr){
                return head;
            }
            fast = fast->next;
        }
        
        // 快慢指针同时移动，直到快指针到达链表末尾
        while (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;        
        }
        
        // 此时慢指针指向倒数第n+1个节点，删除倒数第n个节点
        ListNode* toDelete = slow->next;
        slow->next = slow->next->next;
        delete toDelete;  // 释放被删除节点的内存
        
        // 保存新的头节点
        ListNode* newHead = dummy->next;
        // 释放虚拟头节点
        delete dummy;
        return newHead;
    }
    ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) {
        // 双指针交叉遍历法：时间复杂度O(n), 空间复杂度O(1)
        if (pHead1 == nullptr || pHead2 == nullptr) return nullptr;
        
        ListNode* p1 = pHead1;
        ListNode* p2 = pHead2;
        
        // 两个指针同时遍历，当走到末尾时切换到另一个链表的头部
        // 如果有公共节点，它们会在公共节点相遇
        // 如果没有公共节点，最终都会走到nullptr
        while (p1 != p2) {
            p1 = (p1 == nullptr) ? pHead2 : p1->next;
            p2 = (p2 == nullptr) ? pHead1 : p2->next;
        }
        
        return p1;  // 返回公共节点或nullptr
    }

    // 两个链表相加（最优解）
    ListNode* addInList(ListNode* head1, ListNode* head2) {
        // 边界处理
        if (head1 == nullptr) return head2;
        if (head2 == nullptr) return head1;

        // 1. 反转两个链表，使链表头指向原链表的最低位
        ListNode* reversed1 = reverseList(head1);
        ListNode* reversed2 = reverseList(head2);

        // 2. 创建结果链表的虚拟头节点
        ListNode* dummy = new ListNode(0);
        ListNode* curr = dummy;
        int carry = 0;  // 进位

        // 3. 逐位相加，处理进位
        while (reversed1 != nullptr || reversed2 != nullptr || carry != 0) {
            int val1 = (reversed1 != nullptr) ? reversed1->val : 0;
            int val2 = (reversed2 != nullptr) ? reversed2->val : 0;

            // 计算当前位的和与进位
            int sum = val1 + val2 + carry;
            int digit = sum % 10;
            carry = sum / 10;

            // 将结果位添加到新链表
            curr->next = new ListNode(digit);
            curr = curr->next;

            // 移动指针
            if (reversed1 != nullptr) reversed1 = reversed1->next;
            if (reversed2 != nullptr) reversed2 = reversed2->next;
        }

        // 4. 反转结果链表，得到正确的顺序
        ListNode* result = reverseList(dummy->next);
        
        // 恢复原始链表的结构（可选，根据需求决定）
        // reverseList(reversed1); // 恢复head1
        // reverseList(reversed2); // 恢复head2
        
        // 释放虚拟头节点
        delete dummy;

        return result;
    }
    
    // 找到链表的中点（快慢指针法）
    ListNode* findMiddle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        
        ListNode* slow = head;  // 慢指针，每次移动1步
        ListNode* fast = head->next;  // 快指针，每次移动2步
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        return slow;  // 返回中点的前一个节点
    }
    
    // 基于归并排序的链表排序（O(n log n)时间，O(n)空间）
    ListNode* sortInList(ListNode* head) {
        // 边界处理：空链表或只有一个节点的链表已经有序
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        
        // 1. 找到链表的中点，将链表分成两个子链表
        ListNode* mid = findMiddle(head);
        ListNode* secondHalf = mid->next;
        mid->next = nullptr;  // 将链表断开
        
        // 2. 递归地对两个子链表进行排序
        ListNode* left = sortInList(head);
        ListNode* right = sortInList(secondHalf);
        
        // 3. 合并两个已排序的子链表
        return mergeTwoLists(left, right);
    }

    bool isPail(ListNode* head) {
        // write code here
        // 边界处理：空链表或只有一个节点的链表都是回文
        if (head == nullptr || head->next == nullptr) {
            return true;
        }
        
        // 1. 使用快慢指针找到链表中点
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // 2. 反转后半部分链表
        ListNode* secondHalfHead = reverseList(slow);
        ListNode* secondHalfTemp = secondHalfHead; // 保存后半部分反转后的头节点，用于恢复
        
        // 3. 比较前半部分和反转后的后半部分
        bool isPalindrome = true;
        ListNode* firstHalf = head;
        while (secondHalfHead != nullptr) {
            if (firstHalf->val != secondHalfHead->val) {
                isPalindrome = false;
                break;
            }
            firstHalf = firstHalf->next;
            secondHalfHead = secondHalfHead->next;
        }
        
        // 4. 恢复原链表结构（可选，但良好的编程实践）
        reverseList(secondHalfTemp);
        
        // 5. 返回结果
        return isPalindrome;
    }
};

int main(){
    Solution s;
    
    // 测试mergeKLists函数
    // 创建测试用例：三个升序链表
    // 链表1: 1→4→5
    ListNode* list1 = new ListNode(1);
    list1->next = new ListNode(4);
    list1->next->next = new ListNode(5);
    
    // 链表2: 1→3→4
    ListNode* list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);
    
    // 链表3: 2→6
    ListNode* list3 = new ListNode(2);
    list3->next = new ListNode(6);
    
    // 将链表放入vector
    vector<ListNode*> lists;
    lists.push_back(list1);
    lists.push_back(list2);
    lists.push_back(list3);
    
    // 合并链表
    ListNode* mergedList = s.mergeKLists(lists);
    
    // 输出合并结果
    cout << "合并后的链表："; 
    while(mergedList != nullptr){
        cout << mergedList->val << " ";
        mergedList = mergedList->next;
    }
    cout << endl;
    
    // 注意：合并链表直接使用了原始链表的节点，不需要手动释放原始链表内存
    // 如果需要释放内存，应该遍历合并后的链表进行释放
    // 这里为了简化，不进行内存释放操作
    
    // 测试hasCycle函数
    cout << "\n测试hasCycle函数：" << endl;
    
    // 测试用例1：无环链表
    ListNode* noCycleList = new ListNode(1);
    noCycleList->next = new ListNode(2);
    noCycleList->next->next = new ListNode(3);
    bool result1 = s.hasCycle(noCycleList);
    cout << "无环链表测试结果：" << (result1 ? "有环" : "无环") << endl;
    
    // 测试用例2：有环链表（用户提供的示例：{3,2,0,-4}，环入口在索引1的节点）
    ListNode* cycleList = new ListNode(3);
    ListNode* node1 = new ListNode(2);
    ListNode* node2 = new ListNode(0);
    ListNode* node3 = new ListNode(-4);
    
    cycleList->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node1; // 形成环，环入口为node1（索引1）
    
    bool result2 = s.hasCycle(cycleList);
    cout << "有环链表测试结果：" << (result2 ? "有环" : "无环") << endl;
    
    // 测试用例3：边界情况 - 空链表
    bool result3 = s.hasCycle(nullptr);
    cout << "空链表测试结果：" << (result3 ? "有环" : "无环") << endl;
    
    // 测试用例4：边界情况 - 单节点链表（无环）
    ListNode* singleNodeList = new ListNode(5);
    bool result4 = s.hasCycle(singleNodeList);
    cout << "单节点链表测试结果：" << (result4 ? "有环" : "无环") << endl;
    
    // 测试用例5：边界情况 - 两个节点形成的环
    ListNode* twoNodeCycleList = new ListNode(1);
    ListNode* twoNodeCycleNode = new ListNode(2);
    twoNodeCycleList->next = twoNodeCycleNode;
    twoNodeCycleNode->next = twoNodeCycleList; // 形成环
    
    bool result5 = s.hasCycle(twoNodeCycleList);
    cout << "两个节点形成的环测试结果：" << (result5 ? "有环" : "无环") << endl;
    
    // 测试用例6：边界情况 - 两个节点形成的无环
    ListNode* twoNodeList = new ListNode(1);
    ListNode* twoNodeNode = new ListNode(2);
    twoNodeList->next = twoNodeNode;
    
    bool result6 = s.hasCycle(twoNodeList);
    cout << "两个节点形成的环测试结果：" << (result6 ? "有环" : "无环") << endl;
    
    // 测试EntryNodeOfLoop函数
    cout << "\n测试EntryNodeOfLoop函数：" << endl;
    
    // 测试用例1：用户提供的示例 - 输入{1,2},{3,4,5}，环入口为值3的节点
    ListNode* preLoop1 = new ListNode(1);
    ListNode* preLoop2 = new ListNode(2);
    ListNode* loop1 = new ListNode(3);
    ListNode* loop2 = new ListNode(4);
    ListNode* loop3 = new ListNode(5);
    
    preLoop1->next = preLoop2;
    preLoop2->next = loop1;
    loop1->next = loop2;
    loop2->next = loop3;
    loop3->next = loop1; // 形成环，环入口为loop1（值3）
    
    ListNode* entryResult1 = s.EntryNodeOfLoop(preLoop1);
    cout << "用户示例测试结果：" << (entryResult1 ? to_string(entryResult1->val) : "无环") << endl;
    
    // 测试用例2：无环链表
    ListNode* noCycleList2 = new ListNode(1);
    noCycleList2->next = new ListNode(2);
    noCycleList2->next->next = new ListNode(3);
    ListNode* entryResult2 = s.EntryNodeOfLoop(noCycleList2);
    cout << "无环链表测试结果：" << (entryResult2 ? to_string(entryResult2->val) : "无环") << endl;
    
    // 测试用例3：边界情况 - 空链表
    ListNode* entryResult3 = s.EntryNodeOfLoop(nullptr);
    cout << "空链表测试结果：" << (entryResult3 ? to_string(entryResult3->val) : "无环") << endl;
    
    // 测试用例4：边界情况 - 整个链表是一个环（环入口在头节点）
    ListNode* allCycleList = new ListNode(10);
    allCycleList->next = new ListNode(20);
    allCycleList->next->next = allCycleList; // 形成环，环入口为头节点
    ListNode* entryResult4 = s.EntryNodeOfLoop(allCycleList);
    cout << "整个链表是环的测试结果：" << (entryResult4 ? to_string(entryResult4->val) : "无环") << endl;
    
    // 测试FindKthToTail函数
    cout << "\n测试FindKthToTail函数：" << endl;
    
    // 测试用例1：用户提供的示例 - {1,2,3,4,5},2，期望返回值为4的节点
    ListNode* testList = new ListNode(1);
    testList->next = new ListNode(2);
    testList->next->next = new ListNode(3);
    testList->next->next->next = new ListNode(4);
    testList->next->next->next->next = new ListNode(5);
    ListNode* kthResult1 = s.FindKthToTail(testList, 2);
    cout << "用户示例测试结果（倒数第2个节点）：" << (kthResult1 ? to_string(kthResult1->val) : "无此节点") << endl;
    
    // 测试用例2：边界情况 - 空链表
    ListNode* kthResult2 = s.FindKthToTail(nullptr, 1);
    cout << "空链表测试结果：" << (kthResult2 ? to_string(kthResult2->val) : "无此节点") << endl;
    
    // 测试用例3：边界情况 - k=0
    ListNode* kthResult3 = s.FindKthToTail(testList, 0);
    cout << "k=0测试结果：" << (kthResult3 ? to_string(kthResult3->val) : "无此节点") << endl;
    
    // 测试用例4：边界情况 - 链表长度等于k（返回头节点）
    ListNode* kthResult4 = s.FindKthToTail(testList, 5);
    cout << "链表长度等于k测试结果（倒数第5个节点）：" << (kthResult4 ? to_string(kthResult4->val) : "无此节点") << endl;
    
    // 测试用例5：边界情况 - 链表长度小于k（返回nullptr）
    ListNode* kthResult5 = s.FindKthToTail(testList, 6);
    cout << "链表长度小于k测试结果（倒数第6个节点）：" << (kthResult5 ? to_string(kthResult5->val) : "无此节点") << endl;
    
    // 测试用例6：边界情况 - 单节点链表，k=1（返回该节点）
    ListNode* singleNode = new ListNode(100);
    ListNode* kthResult6 = s.FindKthToTail(singleNode, 1);
    cout << "单节点链表k=1测试结果：" << (kthResult6 ? to_string(kthResult6->val) : "无此节点") << endl;
    
    // 测试用例7：边界情况 - 单节点链表，k>1（返回nullptr）
    ListNode* kthResult7 = s.FindKthToTail(singleNode, 2);
    cout << "单节点链表k>1测试结果：" << (kthResult7 ? to_string(kthResult7->val) : "无此节点") << endl;
    
    // 测试reverseBetween函数
    cout << "\n测试reverseBetween函数：" << endl;
    
    // 测试用例1：普通情况 - 反转链表中第2到第4个节点
    ListNode* reverseList = new ListNode(1);
    reverseList->next = new ListNode(2);
    reverseList->next->next = new ListNode(3);
    reverseList->next->next->next = new ListNode(4);
    reverseList->next->next->next->next = new ListNode(5);
    ListNode* reverseResult = s.reverseBetween(reverseList, 2, 4);
    cout << "反转第2到第4个节点结果：";
    while(reverseResult != nullptr) {
        cout << reverseResult->val << " ";
        reverseResult = reverseResult->next;
    }
    cout << endl;
    
    // 测试reverseKGroup函数
    cout << "\n测试reverseKGroup函数：" << endl;
    
    // 测试用例1：k=2 - 反转链表中每2个节点一组
    ListNode* kGroupList1 = new ListNode(1);
    kGroupList1->next = new ListNode(2);
    kGroupList1->next->next = new ListNode(3);
    kGroupList1->next->next->next = new ListNode(4);
    kGroupList1->next->next->next->next = new ListNode(5);
    ListNode* kGroupResult1 = s.reverseKGroup(kGroupList1, 2);
    cout << "k=2反转结果：";
    while(kGroupResult1 != nullptr) {
        cout << kGroupResult1->val << " ";
        kGroupResult1 = kGroupResult1->next;
    }
    cout << endl;
    
    // 测试用例2：k=3 - 反转链表中每3个节点一组
    ListNode* kGroupList2 = new ListNode(1);
    kGroupList2->next = new ListNode(2);
    
    // 测试sortInList函数
    cout << "\n测试sortInList函数：" << endl;
    
    // 测试用例1：无序链表排序
    ListNode* unsortedList = new ListNode(3);
    unsortedList->next = new ListNode(1);
    unsortedList->next->next = new ListNode(4);
    unsortedList->next->next->next = new ListNode(2);
    unsortedList->next->next->next->next = new ListNode(5);
    
    cout << "排序前链表：";
    ListNode* tempNode = unsortedList;
    while(tempNode != nullptr) {
        cout << tempNode->val << " ";
        tempNode = tempNode->next;
    }
    cout << endl;
    
    ListNode* sortedList = s.sortInList(unsortedList);
    
    cout << "排序后链表：";
    tempNode = sortedList;
    while(tempNode != nullptr) {
        cout << tempNode->val << " ";
        tempNode = tempNode->next;
    }
    cout << endl;
    
    // 测试用例2：包含重复元素的链表排序
    ListNode* duplicateList = new ListNode(5);
    duplicateList->next = new ListNode(2);
    duplicateList->next->next = new ListNode(5);
    duplicateList->next->next->next = new ListNode(1);
    duplicateList->next->next->next->next = new ListNode(3);
    
    cout << "\n包含重复元素的排序前链表：";
    tempNode = duplicateList;
    while(tempNode != nullptr) {
        cout << tempNode->val << " ";
        tempNode = tempNode->next;
    }
    cout << endl;
    
    ListNode* sortedDuplicate = s.sortInList(duplicateList);
    
    cout << "排序后链表：";
    tempNode = sortedDuplicate;
    while(tempNode != nullptr) {
        cout << tempNode->val << " ";
        tempNode = tempNode->next;
    }
    cout << endl;
    
    // 测试用例3：空链表或单节点链表
    ListNode* singleNodeTest = new ListNode(10);
    ListNode* emptyList = nullptr;
    
    ListNode* sortedSingle = s.sortInList(singleNodeTest);
    ListNode* sortedEmpty = s.sortInList(emptyList);
    
    cout << "\n单节点链表排序结果：" << (sortedSingle ? to_string(sortedSingle->val) : "空链表") << endl;
    cout << "空链表排序结果：" << (sortedEmpty ? to_string(sortedEmpty->val) : "空链表") << endl;
    kGroupList2->next->next = new ListNode(3);
    kGroupList2->next->next->next = new ListNode(4);
    kGroupList2->next->next->next->next = new ListNode(5);
    ListNode* kGroupResult2 = s.reverseKGroup(kGroupList2, 3);
    cout << "k=3反转结果：";
    while(kGroupResult2 != nullptr) {
        cout << kGroupResult2->val << " ";
        kGroupResult2 = kGroupResult2->next;
    }
    cout << endl;
    
    // 测试removeNthFromEnd函数
    cout << "\n测试removeNthFromEnd函数：" << endl;
    
    // 测试用例1：用户提供的示例 - 链表1→2→3→4→5，n=2，期望结果1→2→3→5
    ListNode* removeList1 = new ListNode(1);
    removeList1->next = new ListNode(2);
    removeList1->next->next = new ListNode(3);
    removeList1->next->next->next = new ListNode(4);
    removeList1->next->next->next->next = new ListNode(5);
    ListNode* removeResult1 = s.removeNthFromEnd(removeList1, 2);
    cout << "删除倒数第2个节点结果：";
    while(removeResult1 != nullptr) {
        cout << removeResult1->val << " ";
        removeResult1 = removeResult1->next;
    }
    cout << endl;
    
    // 测试用例2：边界情况 - 删除头节点，n=5，链表1→2→3→4→5，期望结果2→3→4→5
    ListNode* removeList2 = new ListNode(1);
    removeList2->next = new ListNode(2);
    removeList2->next->next = new ListNode(3);
    removeList2->next->next->next = new ListNode(4);
    removeList2->next->next->next->next = new ListNode(5);
    ListNode* removeResult2 = s.removeNthFromEnd(removeList2, 5);
    cout << "删除头节点（倒数第5个）结果：";
    while(removeResult2 != nullptr) {
        cout << removeResult2->val << " ";
        removeResult2 = removeResult2->next;
    }
    cout << endl;
    
    // 测试用例3：边界情况 - 删除尾节点，n=1，链表1→2→3→4→5，期望结果1→2→3→4
    ListNode* removeList3 = new ListNode(1);
    removeList3->next = new ListNode(2);
    removeList3->next->next = new ListNode(3);
    removeList3->next->next->next = new ListNode(4);
    removeList3->next->next->next->next = new ListNode(5);
    ListNode* removeResult3 = s.removeNthFromEnd(removeList3, 1);
    cout << "删除尾节点（倒数第1个）结果：";
    while(removeResult3 != nullptr) {
        cout << removeResult3->val << " ";
        removeResult3 = removeResult3->next;
    }
    cout << endl;
    
    // 测试用例4：边界情况 - 单节点链表，n=1，期望结果nullptr
    ListNode* removeList4 = new ListNode(1);
    ListNode* removeResult4 = s.removeNthFromEnd(removeList4, 1);
    cout << "单节点链表删除结果：" << (removeResult4 ? to_string(removeResult4->val) : "空链表") << endl;
    
    // 测试FindFirstCommonNode函数
    cout << "\n测试FindFirstCommonNode函数：" << endl;
    
    // 测试用例1：用户提供的示例 - {1,2,3},{4,5},{6,7}
    // 公共节点部分：6→7
    ListNode* common1 = new ListNode(6);
    common1->next = new ListNode(7);
    
    // 第一个链表：1→2→3→6→7
    ListNode* head1 = new ListNode(1);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(3);
    head1->next->next->next = common1;
    
    // 第二个链表：4→5→6→7
    ListNode* head2 = new ListNode(4);
    head2->next = new ListNode(5);
    head2->next->next = common1;
    
    ListNode* commonResult1 = s.FindFirstCommonNode(head1, head2);
    cout << "用户示例测试结果：" << (commonResult1 ? to_string(commonResult1->val) : "无公共节点") << endl;
    
    // 测试用例2：边界情况 - 空链表
    ListNode* commonResult2 = s.FindFirstCommonNode(nullptr, nullptr);
    cout << "两个空链表测试结果：" << (commonResult2 ? to_string(commonResult2->val) : "无公共节点") << endl;
    
    // 测试用例3：边界情况 - 一个链表为空
    ListNode* commonResult3 = s.FindFirstCommonNode(head1, nullptr);
    cout << "一个链表为空测试结果：" << (commonResult3 ? to_string(commonResult3->val) : "无公共节点") << endl;
    
    // 测试用例4：边界情况 - 没有公共节点
    ListNode* listA = new ListNode(1);
    listA->next = new ListNode(2);
    listA->next->next = new ListNode(3);
    
    ListNode* listB = new ListNode(4);
    listB->next = new ListNode(5);
    listB->next->next = new ListNode(6);
    
    ListNode* commonResult4 = s.FindFirstCommonNode(listA, listB);
    cout << "没有公共节点测试结果：" << (commonResult4 ? to_string(commonResult4->val) : "无公共节点") << endl;
    
    // 测试用例5：边界情况 - 其中一个链表完全是另一个链表的公共部分
    ListNode* listC = new ListNode(10);
    listC->next = new ListNode(20);
    listC->next->next = new ListNode(30);
    
    ListNode* commonResult5 = s.FindFirstCommonNode(listC, listC->next);
    cout << "一个链表是另一个链表的公共部分测试结果：" << (commonResult5 ? to_string(commonResult5->val) : "无公共节点") << endl;
    
    // 测试addInList函数
    cout << "\n测试addInList函数：" << endl;
    
    // 测试用例1：用户提供的示例 - 链表1为9->3->7，链表2为6->3，结果应为1->0->0->0
    ListNode* addList1 = new ListNode(9);
    addList1->next = new ListNode(3);
    addList1->next->next = new ListNode(7);
    
    ListNode* addList2 = new ListNode(6);
    addList2->next = new ListNode(3);
    
    ListNode* addResult = s.addInList(addList1, addList2);
    cout << "用户示例测试结果："; 
    while(addResult != nullptr) {
        cout << addResult->val << " ";
        addResult = addResult->next;
    }
    cout << endl;
    
    // 测试用例2：边界情况 - 一个链表为空
    ListNode* addResult2 = s.addInList(addList1, nullptr);
    cout << "一个链表为空测试结果："; 
    while(addResult2 != nullptr) {
        cout << addResult2->val << " ";
        addResult2 = addResult2->next;
    }
    cout << endl;
    
    // 测试用例3：边界情况 - 两个链表都为空
    ListNode* addResult3 = s.addInList(nullptr, nullptr);
    cout << "两个链表都为空测试结果：" << (addResult3 ? to_string(addResult3->val) : "空链表") << endl;
    
    // 测试用例4：边界情况 - 最高位有进位
    ListNode* addList3 = new ListNode(9);
    addList3->next = new ListNode(9);
    addList3->next->next = new ListNode(9);
    
    ListNode* addList4 = new ListNode(1);
    
    ListNode* addResult4 = s.addInList(addList3, addList4);
    cout << "最高位有进位测试结果："; 
    while(addResult4 != nullptr) {
        cout << addResult4->val << " ";
        addResult4 = addResult4->next;
    }
    cout << endl;
    
    return 0;
}