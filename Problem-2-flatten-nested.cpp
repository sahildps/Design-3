/*
TC : O (N)
SC : O (N)
 *
 */
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator
{
public:
    stack<vector<NestedInteger>::iterator> beginStack, endStack;
    NestedIterator(vector<NestedInteger> &nestedList)
    {
        beginStack.push(nestedList.begin());
        endStack.push(nestedList.end());
    }

    int next()
    {
        hasNext();
        return (beginStack.top()++)->getInteger();
    }

    bool hasNext()
    {
        while (!beginStack.empty())
        {
            if (beginStack.top() == endStack.top())
            {
                beginStack.pop();
                endStack.pop();
            }
            else if (beginStack.top()->isInteger())
            {
                return true;
            }
            else
            {
                auto &nestedList = beginStack.top()->getList();
                auto it = beginStack.top();

                beginStack.top()++;
                beginStack.push(nestedList.begin());
                endStack.push(nestedList.end());
            }
        }
        return false;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */