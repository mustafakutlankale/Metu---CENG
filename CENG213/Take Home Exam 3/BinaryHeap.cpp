#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    // TODO: or not
    theSize = 0;
    HeapElement sentinel;
    sentinel.uniqueId = 0;
    sentinel.weight = 0;
    elements.push_back(sentinel);
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    // TODO:
    for (int i = 1; i < elements.size(); i++)
    {
        if (elements[i].uniqueId == uniqueId)
            return false;
    }
    elements[0].uniqueId = uniqueId;
    elements[0].weight = weight;
    if (theSize + 1 == elements.size())
    {
        elements.resize(elements.size() + 1);
    }

    int hole = ++theSize;
    HeapElement item;
    item.uniqueId = uniqueId;
    item.weight = weight;
    elements[0] = item;
    for (; item.weight < elements[hole / 2].weight; hole /= 2)
        elements[hole] = elements[hole / 2];
    elements[hole] = item;
    return true;
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    // TODO:
    if (theSize == 0)
    {
        return false;
    }

    HeapElement tmp = elements[1];
    outUniqueId = tmp.uniqueId;
    outWeight = tmp.weight;
    elements[1] = elements[theSize--];
    bubbleDown(1);
    return true;
}

void BinaryHeap::bubbleDown(int hole) {
    int child;
    HeapElement tmp = elements[hole];

    for (; hole * 2 <= theSize; hole = child) {
        child = hole * 2;
        if (child != theSize && elements[child + 1].weight < elements[child].weight)
            child++;
        if (elements[child].weight < tmp.weight)
            elements[hole] = elements[child];
        else
            break;
    }
    elements[hole] = tmp;
}

bool BinaryHeap::contains(int uniqueId)
{
    for (int i = 1; i < elements.size(); i++)
    {
        if (elements[i].uniqueId == uniqueId)
            return true;
    }
    return false;
}

bool BinaryHeap::isEmpty() const
{
    return theSize == 0;
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    // TODO:
    if (!contains(uniqueId))
        return false;
    int oldWeight;
    int i = 1;
    for (; i < elements.size(); i++)
    {
        if (elements[i].uniqueId == uniqueId)
        {
            oldWeight = elements[i].weight;
            elements[i].weight = newWeight;
            break;
        }
    }
    HeapElement item;
    item.uniqueId = elements[i].uniqueId;
    item.weight = elements[i].weight;
    if (i != 1 && elements[i].weight < elements[i / 2].weight)
        bubbleUp(i);
    else
    {
        if ((i * 2 <= theSize && elements[i].weight > elements[i * 2].weight)
            || (i * 2 + 1 <= theSize && elements[i].weight > elements[i * 2 + 1].weight))
            bubbleDown(i);
    }
    return true;
}

int BinaryHeap::HeapSize() const
{
    // TODO:
    return theSize;
}

void BinaryHeap::bubbleUp(int hole)
{
    int parent;
    HeapElement tmp = elements[hole];

    for (; hole / 2 > 0 && tmp.weight < elements[hole / 2].weight; hole = parent)
    {
        parent = hole / 2;
        elements[hole] = elements[parent];
    }
    elements[hole] = tmp;
}