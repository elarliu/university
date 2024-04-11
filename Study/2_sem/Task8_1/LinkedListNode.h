#pragma once
template <typename T>
struct LinkedListNode
{
    T data;
    LinkedListNode<T> *next;
    LinkedListNode(T data): data{data}, next{nullptr} {}
};