#include <iostream>
#include <deque>

int main()
{
    // declare the sum of books for each stack
    int sum1 = 0, sum2 = 0, sum3 = 0;
    int t1, t2, t3;

    //declare the stacks using deque
    std::deque<int> stack1, stack2, stack3;

    // input the amount of books
    std:: cin >> t1 >> t2 >> t3;
    for (int i =0; i < t1; i++)
    {
        // height = height of each book for stack 1.
        int height;
        std::cin >> height;
        // the total height of each book for stack 1
        sum1 = height + sum1;
        // put heights of each book (behind)
        stack1.push_back(height);
    }

    for (int i =0; i < t2; i++)
    {
        // height = height of each book for stack 2.
        int height;
        std::cin >> height;
        // the total height of each book for stack 2
        sum2 = sum2 + height;

        // put heights of each book (behind)
        stack2.push_back(height);
    }

    for (int i =0; i < t3; i++)
    {
        // height = height of each book for stack 3.
        int height;
        std::cin >> height;
        // the total height of each book for stack 3.
        sum3 = sum3 + height;

        // put heights of each book (behind)
        stack3.push_back(height);
    }

    while (true)
    {
        // if there are no common sum, print 0.
        // How do we know?? by applying the algorithm. if there is 1 stack
        // where the sum of its elements is the biggest compared to the other
        //stacks, then we pop the top element from the biggest stack. we then
        // substract the biggest sum with the popped element. so now we have a
        // new sum. if the sbiggest sum from the stack is still isnt common, we then
        // pop the front element again, and substract the current sum with the popped
        // element. we do this, until we find a common sum. if we dont find a common sum,
        // we continue to pop it until the stack is empty.
        if(stack1.empty() || stack2.empty() || stack3.empty())
        {
            std:: cout << 0;
            return 0;
        }

        //if
        if (sum1 == sum2 && sum2 == sum3)
        {
            std::cout << sum1;
            return 0;
        }

        if (sum1 > sum2 || sum1 > sum3)
        {
            int front = stack1.front();
            sum1 = sum1 - front;
            stack1.pop_front();
        }
        else if (sum2 > sum1 || sum2 > sum3)
        {
            int front = stack2.front();
            sum2 = sum2 - front;
            stack2.pop_front();
        }
        else if (sum3 > sum1 || sum3 > sum2)
        {
            int front = stack3.front();
            sum3 = sum3 - front;
            stack3.pop_front();
        }


    }
    return  0;
}
