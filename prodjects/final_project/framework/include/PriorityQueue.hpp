#ifndef __ILRD_RD132_PRIORITYQUEUE_HPP__
#define __ILRD_RD132_PRIORITYQUEUE_HPP__

#include <queue>

namespace ilrd
{
    template <class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
    class PriorityQueue : private std::priority_queue<T, Container, Compare>
    {
    public:
        explicit PriorityQueue() = default;
        explicit PriorityQueue(const PriorityQueue &other_) = default;
        explicit PriorityQueue(PriorityQueue &&other_) = default;
        PriorityQueue &operator=(const PriorityQueue &other_) = default;
        PriorityQueue &operator=(PriorityQueue &&other_) = default;
        ~PriorityQueue() = default;


        using std::priority_queue<T, Container, Compare>::pop;
        using std::priority_queue<T, Container, Compare>::push;
        using std::priority_queue<T, Container, Compare>::empty;

        const T& front() const
        {
            return (std::priority_queue<T, Container, Compare>::top());
        }

    }; // class PriorityQueue


} // namespace ilrd

#endif /* __ILRD_RD132_PRIORITYQUEUE_HPP__ */
