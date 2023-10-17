#ifndef DXUT_AI_PRIORITY_QUEUE_SEARCH_H
#define DXUT_AI_PRIORITY_QUEUE_SEARCH_H

#include "SearchStructure.h"
#include "Node.h"
#include <queue>
using std::priority_queue;

template<typename T>
class PriorityQueueSearch : public SearchStructure<T> {
    struct NodeComparator {
        bool operator()(const Node<T>* a, const Node<T>* b) const {
            return a->Cost() > b->Cost();
        }
    };

private:
    priority_queue<Node<T>*, std::vector<Node<T>*>, NodeComparator> data;

public:

    void        Push(Node<T>* element) override {
        data.push(element);

    }
    Node<T>* Pop() override {
        Node<T>* element = data.top();
        data.pop();
        return element;
    }
    bool        IsEmpty() const override {
        return data.empty();
    }
    bool        Exist(const Node<T>* element) const override {
        priority_queue<Node<T>*, std::vector<Node<T>*>, NodeComparator> tempData = data;
        while (!tempData.empty()) {
            if (tempData.top()->Equal(element)) {
                return true;
            }
            tempData.pop();
        }
        return false;
    }
    bool        ExistLargeThan(Node<T>* element) const {
        priority_queue<Node<T>*, std::vector<Node<T>*>, NodeComparator> tempData = data;
        while (!tempData.empty()) {
            Node<T>* top = tempData.top();
            if (top->GetState()->Equal(element->GetState()) && top->Cost() > element->Cost()) {
                return true;
            }
            tempData.pop();
        }
        return false;
    }
    void        RemoveLargeThanBy(Node<T>* element) {
        vector<Node<T>*> newNodes;
        while (!data.empty()) {
            Node<T>* node = data.top();
            data.pop();

            if (node->GetState() == element->GetState() && node->Cost() < element->Cost()) {
                //node->DeletePath();
                //delete node;
                break;
            }
            newNodes.push_back(node);
        }

        for (Node<T>* node : newNodes) {
            data.push(node);
        }
    }
};

#endif
